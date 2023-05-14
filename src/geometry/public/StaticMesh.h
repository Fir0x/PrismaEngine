#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "core/maths/public/vec2f.h"
#include "core/maths/public/vec3f.h"
#include "core/maths/public/vec4f.h"
#include "RHI/public/TypedBuffer.h"
#include "RHI/public/VertexArray.h"

namespace PrismaEngine
{
	class StaticMesh
	{
	public:
		struct Vertex
		{
			Vec3f position;
			Vec3f normal;
			Vec2f uvs;
			Vec4f tangentData; // Tangent vector + bitangent sign
		};

		StaticMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

		void draw() const;

	private:
		TypedBuffer<StaticMesh::Vertex> m_vbo;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<TypedBuffer<unsigned int>> m_ibo;
	};
}