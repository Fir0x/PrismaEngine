#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <imgui/imgui.h>

#include "core/graphics.h"
#include "inputManager.h"
#include "scene/SceneView.h"
#include "extra/meshUtilities.h"
#include "GUIRenderer.h"

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
        float aspectRatio = (float)settings.screen_width / settings.screen_height;
        Scene scene;
        SceneView sceneView(scene, glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f), glm::vec3(0.0f, 0.0f, 5.0f));
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
        auto mesh = MeshUtilities::staticPlane();
        MeshRenderer renderer(mesh, material);
        SceneObject planeObject(renderer);

        scene.addObject(planeObject);
        scene.addLight({ glm::vec3(0.0f, 0.4f, 0.0f), 1.0f, glm::vec3(1.0f) });

        GUIRenderer guiRenderer(window);

        spdlog::info("Main loop start now");
        while (!glfwWindowShouldClose(window))
        {
            processInput(window, guiRenderer);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            sceneView.render();

            guiRenderer.start();
            {
                ImGui::ShowDemoWindow();
            }
            guiRenderer.finish();

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    glfwTerminate();

    spdlog::info("Exiting application now");

    return 0;
}