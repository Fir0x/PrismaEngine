#include "../public/ByteBuffer.h"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "rhiDefs.h"

namespace BerylEngine
{
	ByteBuffer::ByteBuffer(const void* data, size_t size)
	{
		m_size = size;
		glCreateBuffers(1, &m_handle);
		glNamedBufferData(m_handle, size, data, GL_STATIC_DRAW);

		spdlog::trace("Buffer {} allocated. Size is {}.", m_handle, size);
	}

	ByteBuffer::ByteBuffer(size_t size)
		: ByteBuffer(nullptr, size)
	{
	}

	ByteBuffer::~ByteBuffer()
	{
		glDeleteBuffers(1, &m_handle);

		spdlog::trace("Buffer {} deleted.", m_handle);
	}

	void ByteBuffer::bind(BufferUsageType usageType) const
	{
		glBindBuffer(usageType2GL(usageType), m_handle);
	}

	void ByteBuffer::bind(BufferUsageType usageType, int bindingPoint) const
	{
		glBindBufferBase(usageType2GL(usageType), bindingPoint, m_handle);
	}

	void ByteBuffer::setAccess(AccessType accessType) const
	{
		glMapNamedBuffer(m_handle, accessType2GL(accessType));
	}
}