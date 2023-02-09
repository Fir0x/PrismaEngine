#include "ByteBuffer.h"

#include <spdlog/spdlog.h>

#include "glErrors.h"

namespace BerylEngine
{

	ByteBuffer::ByteBuffer(const void* data, size_t size)
	{
		m_size = size;
		GL_CALL(glCreateBuffers(1, &m_id));
		GL_CALL(glNamedBufferData(m_id, size, data, GL_STATIC_DRAW));

		spdlog::trace("Buffer {} allocated. Size is {}.", m_id, size);
	}

	ByteBuffer::ByteBuffer(size_t size)
		: ByteBuffer(nullptr, size)
	{
	}

	ByteBuffer::~ByteBuffer()
	{
		glDeleteBuffers(1, &m_id);

		spdlog::trace("Buffer {} deleted.", m_id);
	}

	void ByteBuffer::bind(BufferUsageType usageType) const
	{
		GL_CALL(glBindBuffer(usageType2GL(usageType), m_id));
	}

	void ByteBuffer::setAccess(BufferAccessType accessType) const
	{
		GL_CALL(glMapNamedBuffer(m_id, accessType2GL(accessType)));
	}
}