#include "../public/graphicsDefs.h"

namespace BerylEngine
{
	GLenum usageType2GL(BufferUsageType usageType)
	{
		switch (usageType)
		{
		case BufferUsageType::VertexBuffer:
			return GL_ARRAY_BUFFER;
		case BufferUsageType::IndexBuffer:
			return GL_ELEMENT_ARRAY_BUFFER;
		case BufferUsageType::UniformBuffer:
			return GL_UNIFORM_BUFFER;
		case BufferUsageType::ShaderStorage:
			return GL_SHADER_STORAGE_BUFFER;
		default:
			return GL_INVALID_ENUM;
		}
	}

	GLenum accessType2GL(AccessType accessType)
	{
		if (accessType == AccessType::Read)
			return GL_READ_ONLY;
		else if (accessType == AccessType::Write)
			return GL_WRITE_ONLY;
		else
			return GL_READ_WRITE;
	}
}