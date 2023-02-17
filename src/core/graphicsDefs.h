#pragma once

#include <GL/glew.h>

namespace BerylEngine
{
	enum BufferUsageType
	{
		VertexBuffer,
		IndexBuffer,
		UniformBuffer,
		ShaderStorage,
	};

	enum AccessType
	{
		Read,
		Write,
		Read_Write
	};

	GLenum usageType2GL(BufferUsageType usageType);
	GLenum accessType2GL(AccessType accessType);
}