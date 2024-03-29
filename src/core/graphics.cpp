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
            FATAL("Failed to init GLEW");

        spdlog::info("OpenGL version: {}", (char*)glGetString(GL_VERSION));

        glDebugMessageCallback(&debugCallback, nullptr);

        glEnable(GL_DEBUG_OUTPUT);
        if (isDebuggerPresent())
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

        // Reverse-Z
        glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
        glClearDepth(0.0f);

        //glDepthRange(0.0, 1.0);

        spdlog::info("Graphics API initialized.");
    }
}