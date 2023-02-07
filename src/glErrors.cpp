#include "glErrors.h"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

namespace BerylEngine
{
    void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCall(const char* function, const char* file, int line)
    {
        if (GLenum error = glGetError())
        {
            spdlog::error("[OpenGL Error] ({}): {} {}:{}", error, function, file, line);
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