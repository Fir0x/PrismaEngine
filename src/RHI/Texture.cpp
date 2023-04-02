#include "Texture.h"

#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <filesystem>
#include <spdlog/spdlog.h>

#include "../core/utils.h"

namespace BerylEngine
{
	struct TextureFormatGL
	{
		unsigned int format;
		unsigned int internalFormat;
		unsigned int componentType;
	};

	static TextureFormatGL textureFormat2GL(Texture::TextureFormat format)
	{
		switch (format)
		{
		case Texture::TextureFormat::RGB8_UNORM:
			return { GL_RGB, GL_RGB8, GL_UNSIGNED_BYTE };
		case Texture::TextureFormat::RGBA8_UNORM:
			return { GL_RGBA, GL_RGBA8, GL_UNSIGNED_BYTE };
		case Texture::TextureFormat::Depth32_FLOAT:
			return { GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32F, GL_FLOAT };
		default:
			FATAL("Unknown texture fomat");
		}
	}

	Texture::Texture(int width, int height, TextureFormat format)
		: m_width(width), m_height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);

		TextureFormatGL formatGL = textureFormat2GL(format);
		glTextureStorage2D(m_handle, 1, formatGL.internalFormat, width, height);

		spdlog::trace("Texture {} created. Width = {} | Height = {}.", m_handle, width, height);
	}

	Texture::Texture(int width, int height, TextureFormat format, unsigned char* data)
		: m_width(width), m_height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);

		TextureFormatGL formatGL = textureFormat2GL(format);
		glTextureStorage2D(m_handle, getMipLevel(width, height), formatGL.internalFormat, width, height);
		glTextureSubImage2D(m_handle, 0, 0, 0, width, height, formatGL.format, formatGL.componentType, data);
		glGenerateTextureMipmap(m_handle);
	}

	std::shared_ptr<Texture> Texture::fromFile(const std::string& path, TextureFormat textureFormat)
	{
		auto absPath = std::filesystem::absolute(path).string();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (data == nullptr)
		{
			spdlog::error("Failed to load texture from {}.", path);
			return nullptr;
		}

		auto texture = std::make_shared<Texture>(width, height, textureFormat, data);

		stbi_image_free(data);

		spdlog::trace("Loaded texture from {}.", path);

		return texture;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_handle);

		spdlog::trace("Texture {} deleted.", m_handle);
	}

	unsigned int Texture::getId() const
	{
		return m_handle;
	}

	glm::ivec2 Texture::getSize() const
	{
		return glm::ivec2(m_width, m_height);
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_handle);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::bindToUnit(const int unit) const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		bind();
	}

	int Texture::getMipLevel(int width, int height) const
	{
		unsigned int maxSize = std::max(width, height);
		return 1 + int(std::floor(std::log2(maxSize)));
	}
}