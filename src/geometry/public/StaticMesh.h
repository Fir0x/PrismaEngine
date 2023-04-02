#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "RHI/public/TypedBuffer.h"
#include "RHI/public/VertexArray.h"

namespace BerylEngine
{
	class StaticMesh
	{
	public:
		struct Vertex
		{
			glm::vec3 coords;
			glm::vec3 normals;
			glm::vec2 uvs;
			glm::vec4 tangentData; // Tangent vector + bitangent sign
		};

	private:
		TypedBuffer<StaticMesh::Vertex> m_vbo;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<TypedBuffer<unsigned int>> m_ibo;

	public:
		StaticMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

		void draw() const;
	};
}