#pragma once

#include "ByteBuffer.h"

namespace BerylEngine
{
	template <typename T>
	class TypedBuffer : public ByteBuffer
	{
	public:
		TypedBuffer() = default;

		TypedBuffer(size_t count) : ByteBuffer(count * sizeof(T))
		{
		}

		TypedBuffer(const T* data, size_t count) : ByteBuffer(data, count * sizeof(T))
		{
		}

		size_t getCount() const
		{
			return m_size / sizeof(T);
		}
	};
}