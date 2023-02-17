#include "VertexArray.h"

#include <GL/glew.h>

#include <spdlog/spdlog.h>

namespace BerylEngine
{
	VertexArray::VertexArray(const ByteBuffer& vb, const VertexBufferLayout& layout)
	{
		glGenVertexArrays(1, &m_id);
		glBindVertexArray(m_id);

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

		spdlog::trace("Vertex array {} created", m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);

		spdlog::trace("Vertex array {} deleted", m_id);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
}