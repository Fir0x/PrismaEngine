#include "../public/FrameBuffer.h"

#include <GL/glew.h>

namespace BerylEngine
{
	Framebuffer::Framebuffer(Texture* depth) : Framebuffer(depth, nullptr, 0)
	{
	}

	Framebuffer::Framebuffer(Texture* depth, Texture** renderTargets, size_t targetsCount)
        : m_size({0,0})
	{
        glCreateFramebuffers(1, &m_handle);

        if (depth) {
            glNamedFramebufferTexture(m_handle, GL_DEPTH_ATTACHMENT, depth->getId(), 0);
            m_size = depth->getSize();
        }

        if (targetsCount >= 8)
            FATAL("Too many render targets");

        for (size_t i = 0; i != targetsCount; ++i) {
            glNamedFramebufferTexture(m_handle, GLenum(GL_COLOR_ATTACHMENT0 + i), renderTargets[i]->getId(), 0);

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

        glNamedFramebufferDrawBuffers(m_handle, GLsizei(targetsCount), draw_buffers);
	}

    Framebuffer::~Framebuffer()
    {
        if (m_handle != 0)
            glDeleteFramebuffers(1, &m_handle);
    }

    void Framebuffer::bind(bool clear) const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
        glViewport(0, 0, m_size.x, m_size.y);

        if (clear)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Framebuffer::bind(bool clearTargets, bool clearDepth) const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
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

        glBlitNamedFramebuffer(m_handle, 0,
            0, 0, m_size.x, m_size.y,
            0, 0, viewport[2], viewport[3],
            GL_COLOR_BUFFER_BIT | (copyDepth ? GL_DEPTH_BUFFER : 0),
            GL_NEAREST);
    }
}
