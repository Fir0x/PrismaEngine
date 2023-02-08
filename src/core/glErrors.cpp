#include "glErrors.h"

#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <string>

namespace BerylEngine
{
    void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    static std::string_view glError2Str(GLenum error)
    {
        switch (error)
        {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_CONTEXT_LOST:
            return "GL_CONTEXT_LOST";
        default:
            return "GL_UNKNOWN_ERROR";
        }
    }

    bool GLLogCall(const char* function, const char* file, int line)
    {
        if (GLenum error = glGetError())
        {
            spdlog::error("[OpenGL Error] ({}): {} {}:{}", glError2Str(error), function, file, line);
            return false;
        }

        return true;
    }

    bool GLLogCall(const char* file, int line)
    {
        if (GLenum error = glGetError())
        {
            spdlog::error("[OpenGL Error] ({}): {}:{}", error, file, line);
            return false;
        }

        return true;
    }
}