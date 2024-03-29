#pragma once

#include "graphicsDefs.h"

#include "utils.h"

namespace BerylEngine
{
	class ByteBuffer : NonCopyable
	{
	private:
		unsigned int m_handle;

	protected:
		size_t m_size;

	public:
		ByteBuffer() = default;

		ByteBuffer(const void* data, size_t size);
		ByteBuffer(size_t size);

		ByteBuffer(ByteBuffer&&) = default;
		ByteBuffer& operator=(ByteBuffer&&) = default;
		~ByteBuffer();

		void bind(BufferUsageType usageType) const;
		template<BufferUsageType U>
		void bind(int bindingPoint) const
		{
			static_assert(U == BufferUsageType::UniformBuffer || U == BufferUsageType::ShaderStorage, "Bad usage type");
			glBindBufferBase(usageType2GL(U), bindingPoint, m_handle);
		}

		void setAccess(AccessType accessType) const;
	};
}