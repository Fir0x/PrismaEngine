#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <imgui/imgui.h>

#include "geometry/public/meshUtilities.h"
#include "input/public/inputManager.h"
#include "scene/public/SceneView.h"
#include "RHI/public/graphics.h"
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

using namespace BerylEngine;

int main(void)
{
    spdlog::set_level(spdlog::level::debug);

    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(settings.screen_width, settings.screen_height, "BerylEngine", NULL, NULL);
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
        SceneView sceneView(scene, glm::vec3(0.0f, 0.0f, 5.0f), aspectRatio);
        linkCamera(&sceneView.camera());
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, screen_size_callback);

        std::string defines[] = { "NO_DEFINES" };
        auto program = Program::fromFiles("shaders/basic.vert", "shaders/basic.frag", defines);
        //auto albedoTex = Texture::fromFile("uvTestTexture.png", Texture::TextureFormat::RGBA8_UNORM);
        //auto normalTex = Texture::fromFile("brickwall_normal.jpg", Texture::TextureFormat::RGB8_UNORM);
        Material material(program);
        //material.setTexture(0, albedoTex);
        //material.setTexture(1, normalTex);
        auto mesh = MeshUtilities::staticCube();
        MeshRenderer renderer(mesh, material);
        SceneObject planeObject(renderer);

        scene.addObject(planeObject);
        scene.addLight({ glm::vec3(0.0f, 0.7f, 0.0f), 1.0f, glm::vec3(1.0f) });

        GUIRenderer guiRenderer(window);

        Texture colorTexture(settings.screen_width, settings.screen_height, Texture::TextureFormat::RGBA8_UNORM);
        Texture depthTexture(settings.screen_width, settings.screen_height, Texture::TextureFormat::Depth32_FLOAT);
        Framebuffer mainFramebuffer(&depthTexture, std::array{&colorTexture});

        spdlog::info("Main loop start now");
        while (!glfwWindowShouldClose(window))
        {
            processInput(window, guiRenderer);

            mainFramebuffer.bind(true);

            sceneView.render();

            guiRenderer.start();
            guiRenderer.finish();

            mainFramebuffer.blit(false);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    glfwTerminate();

    spdlog::info("Exiting application now");

    return 0;
}