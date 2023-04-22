#include "../public/FrameBuffer.h"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

namespace PrismaEngine
{
	Framebuffer::Framebuffer(Texture* depth) : Framebuffer(depth, nullptr, 0)
	{
	}

    static unsigned int createHandle()
    {
        unsigned int handle;
        glCreateFramebuffers(1, &handle);

        return handle;
    }

	Framebuffer::Framebuffer(Texture* depth, Texture** renderTargets, size_t targetsCount)
        : m_size({0,0}), m_handle(createHandle())
	{
        if (depth) {
            glNamedFramebufferTexture(m_handle.get(), GL_DEPTH_ATTACHMENT, depth->getHandle(), 0);
            m_size = depth->getSize();
        }

        if (targetsCount >= 8)
            FATAL("Too many render targets");

        for (size_t i = 0; i != targetsCount; ++i) {
            glNamedFramebufferTexture(m_handle.get(), GLenum(GL_COLOR_ATTACHMENT0 + i), renderTargets[i]->getHandle(), 0);

            glm::ivec2 targetSize = renderTargets[i]->getSize();
            if (targetSize.x < m_size.x)
                m_size.x = targetSize.x;
            if (targetSize.y < m_size.y)
                m_size.y = targetSize.y;

        }

        const GLenum draw_buffers[] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3,
            GL_COLOR_ATTACHMENT4,
            GL_COLOR_ATTACHMENT5,
            GL_COLOR_ATTACHMENT6,
            GL_COLOR_ATTACHMENT7
        };

        glNamedFramebufferDrawBuffers(m_handle.get(), GLsizei(targetsCount), draw_buffers);
	}

    Framebuffer::~Framebuffer()
    {
        if (unsigned int handle = m_handle.get())
        {
            glDeleteFramebuffers(1, &handle);

            spdlog::trace("Framebuffer {} deleted.", handle);
        }
    }

    void Framebuffer::bind(bool clear) const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_handle.get());
        glViewport(0, 0, m_size.x, m_size.y);

        if (clear)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Framebuffer::bind(bool clearTargets, bool clearDepth) const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_handle.get());
        glViewport(0, 0, m_size.x, m_size.y);

        if (clearTargets || clearDepth)
        {
            GLbitfield clearMask = 0;
            if (clearTargets)
                clearMask |= GL_COLOR_BUFFER_BIT;
            if (clearDepth)
                clearMask |= GL_DEPTH_BUFFER_BIT;

            glClear(clearMask);
        }
    }

    void Framebuffer::blit(bool copyDepth)
    {
        int viewport[4] = {};
        glGetIntegerv(GL_VIEWPORT, viewport);

        glBlitNamedFramebuffer(m_handle.get(), 0,
            0, 0, m_size.x, m_size.y,
            0, 0, viewport[2], viewport[3],
            GL_COLOR_BUFFER_BIT | (copyDepth ? GL_DEPTH_BUFFER : 0),
            GL_NEAREST);
    }
}
