#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "core/public/utils.h"
#include "APIHandle.h"

namespace PrismaEngine
{
	class Texture : public NonCopyable
	{
	public:
		enum class TextureFormat
		{
			RGBA8_UNORM,
			RGB8_UNORM,

			Depth32_FLOAT
		};

		Texture(int width, int height, TextureFormat format);
		Texture(int width, int height, TextureFormat format, unsigned char* data);
		~Texture();

		static std::shared_ptr<Texture> fromFile(const std::string& path, TextureFormat textureFormat);

		unsigned int getHandle() const;
		glm::ivec2 getSize() const;

		void bind() const;
		void unbind() const;

		void bindToUnit(const int unit) const;

	private:
		GLHandle m_handle;
		int m_width;
		int m_height;

		int getMipLevel(int width, int height) const;
	};
}