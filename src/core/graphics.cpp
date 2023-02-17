#include "graphics.h"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "utils.h"

namespace BerylEngine
{
    static void debugCallback(GLenum, GLenum type, GLuint, GLenum sev, GLsizei, const char* msg, const void*)
    {
        if (sev == GL_DEBUG_SEVERITY_NOTIFICATION) {
            return;
        }

        const bool isError = type == GL_DEBUG_TYPE_ERROR;
        std::string header = sev == GL_DEBUG_SEVERITY_HIGH ? "[OpenGL][HIGH]" : "[OpenGL]";
        if (isError)
        {
            spdlog::error("{} {}", header, msg);
            debugBreak();
        }
        else
            spdlog::warn("{} {}", header, msg);
    }

    void initGraphicsAPI()
    {
        if (glewInit() != GLEW_OK)
        {
            spdlog::critical("Failed to init GLEW");
            std::terminate();
        }

        spdlog::info("OpenGL version: {}", (char*)glGetString(GL_VERSION));

        glDebugMessageCallback(&debugCallback, nullptr);

        glEnable(GL_DEBUG_OUTPUT);
        if (isDebuggerPresent())
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDepthRange(0.0, 1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

        spdlog::info("Graphics API initialized.");
    }
}