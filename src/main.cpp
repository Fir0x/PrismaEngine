#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <filesystem>

#include "core/maths/public/Vector2.h"
#include "core/maths/public/Vector3.h"
#include "geometry/public/meshUtilities.h"
#include "input/public/inputManager.h"
#include "scene/public/SceneView.h"
#include "RHI/public/utils.h"
#include "RHI/public/FrameBuffer.h"
#include "rendering/public/GUIRenderer.h"
#include "rendering/public/Material.h"

static struct Settings
{
    unsigned int screen_width = 800;
    unsigned int screen_height = 600;
} settings;

static void screen_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    settings.screen_width = width;
    settings.screen_height = height;
}

using namespace PrismaEngine;

int main(void)
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Running at {}", std::filesystem::current_path().string());

    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(settings.screen_width, settings.screen_height, "PrismaEngine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        FATAL("Failed to create window.");
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    spdlog::info("Window initialized.");

    initGraphicsAPI();

    glViewport(0, 0, settings.screen_width, settings.screen_height);

    spdlog::info("Beryl Engine started");

    {
        const float aspectRatio = (float)settings.screen_width / settings.screen_height;
        Scene scene;
        Vector3f cameraPosition = Vector3f(0.0f, 0.0f, 5.0f);
        SceneView sceneView(scene, cameraPosition, aspectRatio);
        linkCamera(&sceneView.camera());
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, screen_size_callback);

        std::string defines[] = { "NO_DEFINES" };
        auto gBufferProgram = Program::fromFiles("shaders/basic.vert", "shaders/deferred_gbuffer.frag", defines);
        //auto albedoTex = Texture::fromFile("uvTestTexture.png", Texture::TextureFormat::RGBA8_UNORM);
        //auto normalTex = Texture::fromFile("brickwall_normal.jpg", Texture::TextureFormat::RGB8_UNORM);
        Material material(gBufferProgram);
        //material.setTexture(0, albedoTex);
        //material.setTexture(1, normalTex);

        auto wireframeProgram = Program::fromFiles("shaders/basic.vert", "shaders/wireframe.geom", "shaders/wireframe.frag");
        Material wireframeMat(wireframeProgram, Material::BlendMode::AlphaTop);
        wireframeMat.setUniform("color", Vector3f(1.0f, 0.0f, 0.0f));

        auto mesh = MeshUtilities::staticCube();//MeshUtilities::staticSphere(32,16);
        MeshRenderer renderer(mesh, wireframeMat);
        SceneObject planeObject(renderer);

        scene.addObject(planeObject);

        GUIRenderer guiRenderer(window);

        auto colorTexture = std::make_shared<Texture>(settings.screen_width, settings.screen_height, Texture::TextureFormat::RGBA8_UNORM);
        auto normalTexture = std::make_shared<Texture>(settings.screen_width, settings.screen_height, Texture::TextureFormat::RGBA8_UNORM);
        auto depthTexture = std::make_shared<Texture>(settings.screen_width, settings.screen_height, Texture::TextureFormat::Depth32_FLOAT);
        Framebuffer gBuffer(depthTexture.get(), std::array{colorTexture.get(), normalTexture.get()});

        auto diretionalLightProgram = Program::fromFiles("shaders/screen.vert", "shaders/lighting/deferred_directionalLight.frag");
        Material directionalLightMat(diretionalLightProgram, Material::BlendMode::Add, Material::DepthMode::Reversed, false);
        directionalLightMat.setTexture(0, colorTexture);
        directionalLightMat.setTexture(1, normalTexture);

        Vector3f sunDirection = Vector3f(0.8f, 0.1f, 0.3f).normalize();
        Vector3f sunColor = Vector3f(0.6f, 0.6f, 0.6f);
        scene.addLight(DirectionalLight(sunDirection, sunColor, directionalLightMat));

        auto pointLightProgram = Program::fromFiles("shaders/basic.vert", "shaders/lighting/deferred_pointLight.frag");
        Material pointLightMat(pointLightProgram, Material::BlendMode::Add, Material::DepthMode::Reversed, false, Material::CullMode::Frontface);
        pointLightMat.setTexture(0, colorTexture);
        pointLightMat.setTexture(1, normalTexture);
        pointLightMat.setTexture(2, depthTexture);

        scene.addLight({ Vector3f(0.0f, 1.3f, 0.0f), 1.0f, Vector3f(1.0f), pointLightMat });

        auto finalColorTexture = std::make_shared<Texture>(settings.screen_width, settings.screen_height, Texture::TextureFormat::RGBA8_UNORM);
        Framebuffer finalColorBuffer(depthTexture.get(), std::array{ finalColorTexture.get() });

        spdlog::info("Main loop start now");
        while (!glfwWindowShouldClose(window))
        {
            processInput(window, guiRenderer);

            const Vector2i windowSizes(settings.screen_width, settings.screen_height);

            gBuffer.bind(true);

            sceneView.renderGeometry(windowSizes);

            finalColorBuffer.bind(true, false);
            sceneView.renderLights(windowSizes);

            guiRenderer.start();
            guiRenderer.finish();

            finalColorBuffer.blit(false);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    glfwTerminate();

    spdlog::info("Exiting application now");

    return 0;
}