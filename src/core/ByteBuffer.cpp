#include "ByteBuffer.h"

#include <spdlog/spdlog.h>

namespace BerylEngine
{

	ByteBuffer::ByteBuffer(const void* data, size_t size)
	{
		m_size = size;
		glCreateBuffers(1, &m_id);
		glNamedBufferData(m_id, size, data, GL_STATIC_DRAW);

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
		glBindBuffer(usageType2GL(usageType), m_id);
	}

	void ByteBuffer::setAccess(AccessType accessType) const
	{
		glMapNamedBuffer(m_id, accessType2GL(accessType));
	}
}