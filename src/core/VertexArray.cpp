#include "VertexArray.h"

#include <GL/glew.h>

#include "glErrors.h"

#include <spdlog/spdlog.h>

namespace BerylEngine
{
	VertexArray::VertexArray(const ByteBuffer& vb, const VertexBufferLayout& layout)
	{
		GL_CALL(glGenVertexArrays(1, &m_id));
		GL_CALL(glBindVertexArray(m_id));

		vb.bind(BufferUsageType::VertexBuffer);
		const auto& elements = layout.get_elements();
		size_t offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto elm = elements[i];
			GL_CALL(glVertexAttribPointer(i, elm.count, elm.type,
				elm.normalized, layout.get_stride(), (const void*)offset));
			GL_CALL(glEnableVertexAttribArray(i));

			offset += elm.count * VertexBufferElement::get_type_size(elm.type);
		}

		spdlog::trace("Vertex array {} created", m_id);
	}

	VertexArray::~VertexArray()
	{
		spdlog::trace("Vertex array {} destroyed", m_id);
		GL_CALL(glDeleteVertexArrays(1, &m_id));
	}

	void VertexArray::bind() const
	{
		GL_CALL(glBindVertexArray(m_id));
	}

	void VertexArray::unbind() const
	{
		GL_CALL(glBindVertexArray(0));
	}
}