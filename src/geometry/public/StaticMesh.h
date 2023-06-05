#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "core/maths/public/Vector2.h"
#include "core/maths/public/Vector3.h"
#include "core/maths/public/Vector4.h"
#include "RHI/public/TypedBuffer.h"
#include "RHI/public/VertexArray.h"

namespace PrismaEngine
{
	class StaticMesh
	{
	public:
		struct Vertex
		{
			Vector3f position;
			Vector3f normal;
			Vector2f uvs;
			Vector4f tangentData; // Tangent vector + bitangent sign
		};

		StaticMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

		void draw() const;

	private:
		TypedBuffer<StaticMesh::Vertex> m_vbo;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<TypedBuffer<unsigned int>> m_ibo;
	};
}