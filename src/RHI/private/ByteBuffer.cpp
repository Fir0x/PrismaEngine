#include "../public/ByteBuffer.h"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "rhiDefs.h"

namespace PrismaEngine
{
	static unsigned int createHandle()
	{
		unsigned int handle = 0;
		glCreateBuffers(1, &handle);

		return handle;
	}

	ByteBuffer::ByteBuffer(const void* data, size_t size)
		: m_handle(createHandle())
	{
		m_size = size;
		glNamedBufferData(m_handle.get(), size, data, GL_STATIC_DRAW);

		spdlog::trace("Buffer {} allocated. Size is {}.", m_handle.get(), size);
	}

	ByteBuffer::ByteBuffer(size_t size)
		: ByteBuffer(nullptr, size)
	{
	}

	ByteBuffer::~ByteBuffer()
	{
		if (unsigned int handle = m_handle.get())
		{
			glDeleteBuffers(1, &handle);

			spdlog::trace("Buffer {} deleted.", handle);
		}
	}

	void ByteBuffer::bind(BufferUsageType usageType) const
	{
		glBindBuffer(usageType2GL(usageType), m_handle.get());
	}

	void ByteBuffer::bind(BufferUsageType usageType, int bindingPoint) const
	{
		glBindBufferBase(usageType2GL(usageType), bindingPoint, m_handle.get());
	}

	void ByteBuffer::setAccess(AccessType accessType) const
	{
		glMapNamedBuffer(m_handle.get(), accessType2GL(accessType));
	}
}