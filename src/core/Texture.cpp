#include "Texture.h"

#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <filesystem>
#include <spdlog/spdlog.h>

namespace BerylEngine
{
	Texture::Texture(int width, int height)
	{
		m_width = width;
		m_height = height;

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		spdlog::trace("Texture {} created. Width = {} | Height = {}.", m_id, width, height);
	}

	Texture::Texture(int width, int height, unsigned char* data)
		: Texture(width, height)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	std::shared_ptr<Texture> Texture::fromFile(const std::string& path)
	{
		auto absPath = std::filesystem::absolute(path).string();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (data == nullptr)
		{
			spdlog::error("Failed to load texture from {}.", path);
			return 0;
		}

		auto texture = std::make_shared<Texture>(width, height, data);

		stbi_image_free(data);

		spdlog::trace("Loaded texture from {}.", path);

		return texture;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_id);

		spdlog::trace("Texture {} deleted.", m_id);
	}

	unsigned int Texture::getId() const
	{
		return m_id;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
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
}