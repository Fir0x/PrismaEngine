#pragma once

#include "ByteBuffer.h"
#include "VertexBufferLayout.h"
#include "core/public/utils.h"

namespace BerylEngine
{
	class VertexArray : NonCopyable
	{
	private:
		unsigned int m_handle;

	public:
		VertexArray() = default;
		VertexArray(const ByteBuffer& vb, const VertexBufferLayout& layout);
		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(VertexArray&&) = default;
		~VertexArray();

		void bind() const;
		void unbind() const;
	};
}