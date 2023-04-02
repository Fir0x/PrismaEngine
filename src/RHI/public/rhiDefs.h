#pragma once

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
}