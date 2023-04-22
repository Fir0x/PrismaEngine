#pragma once

#include "ByteBuffer.h"
#include "VertexBufferLayout.h"
#include "core/public/utils.h"

#include "APIHandle.h"

namespace PrismaEngine
{
	class VertexArray : NonCopyable
	{
	public:
		VertexArray() = default;
		VertexArray(const ByteBuffer& vb, const VertexBufferLayout& layout);
		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(VertexArray&&) = default;
		~VertexArray();

		void bind() const;
		void unbind() const;

	private:
		GLHandle m_handle;
	};
}