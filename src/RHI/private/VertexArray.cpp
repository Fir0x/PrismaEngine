#include "../public/VertexArray.h"

#include <GL/glew.h>

#include <spdlog/spdlog.h>

namespace PrismaEngine
{
	static unsigned int createHandle()
	{
		unsigned int handle;
		glGenVertexArrays(1, &handle);

		return handle;
	}
	VertexArray::VertexArray(const ByteBuffer& vb, const VertexBufferLayout& layout)
		: m_handle(createHandle())
	{
		glBindVertexArray(m_handle.get());

		vb.bind(BufferUsageType::VertexBuffer);
		const auto& elements = layout.get_elements();
		size_t offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto elm = elements[i];
			glVertexAttribPointer(i, elm.count, elm.type,
				elm.normalized, layout.get_stride(), (const void*)offset);
			glEnableVertexAttribArray(i);

			offset += elm.count * VertexBufferElement::get_type_size(elm.type);
		}

		spdlog::trace("Vertex array {} created", m_handle.get());
	}

	VertexArray::~VertexArray()
	{
		if (unsigned int handle = m_handle.get())
		{
			glDeleteVertexArrays(1, &handle);

			spdlog::trace("Vertex array {} deleted", handle);
		}
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_handle.get());
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
}