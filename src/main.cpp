#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "core/graphics.h"
#include "inputManager.h"
#include "scene/SceneView.h"
#include "extra/meshUtilities.h"

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

        std::string defines[] = { "SHOW_UV" };
        auto program = Program::fromFiles("shaders/basic.vert", "shaders/basic.frag");
        Material material(program);
        auto mesh = MeshUtilities::staticCube();
        MeshRenderer renderer(mesh, material);
        SceneObject planeObject(renderer);

        scene.addObject(planeObject);
        scene.addLight({ glm::vec3(0.0f, 1.3f, 0.0f), 1.0f, glm::vec3(1.0f) });

        spdlog::info("Main loop start now");
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            sceneView.render();

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    glfwTerminate();

    spdlog::info("Exiting application now");

    return 0;
}