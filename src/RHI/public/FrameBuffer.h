#pragma once

#include <array>
#include <memory>
#include <glm/vec2.hpp>

#include "core/public/utils.h"
#include "Texture.h"
#include "APIHandle.h"

namespace BerylEngine
{
	class Framebuffer : NonCopyable
	{
	public:
		template <size_t N>
		Framebuffer(Texture* depth, std::array<Texture*, N> renderTargets) : Framebuffer(depth, renderTargets.data(), renderTargets.size())
		{
		}

		Framebuffer() = default;
		Framebuffer(Texture* depth);

		~Framebuffer();

		void bind(bool clear) const;
		void bind(bool clearTargets, bool clearDepth) const;
		void blit(bool copyDepth);

	private:
		Framebuffer(Texture* depth, Texture** renderTargets, size_t targetsCount);

		GLHandle m_handle;
		glm::ivec2 m_size;

	};
}
