#pragma once

#include <array>
#include <memory>
#include <glm/vec2.hpp>

#include "Texture.h"

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

		unsigned int m_handle;
		glm::ivec2 m_size;

	};
}
