#pragma once

#include "RHI/public/rhiDefs.h"
#include "RHI/public/APIHandle.h"

#include "core/public/utils.h"

namespace PrismaEngine
{
	class ByteBuffer : NonCopyable
	{
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
			bind(U, bindingPoint);
		}

		void setAccess(AccessType accessType) const;

	protected:
		size_t m_size;

	private:
		/// <summary>
		/// This methods exists to hide implementation dtails of its templated version.
		/// </summary>
		/// <param name="usageType"></param>
		/// <param name="bindingPoint"></param>
		void bind(BufferUsageType usageType, int bindingPoint) const;

		GLHandle m_handle;
	};
}