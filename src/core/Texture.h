#pragma once

#include <string>
#include <memory>

namespace BerylEngine
{
	class Texture
	{
	private:
		unsigned int m_id;
		int m_width;
		int m_height;

	public:
		Texture(int width, int height);
		Texture(int width, int height, unsigned char* data);
		~Texture();

		static std::shared_ptr<Texture> fromFile(const std::string& path);

		unsigned int getId() const;

		void bind() const;
		void unbind() const;

		void bindToUnit(const int unit) const;
	};
}