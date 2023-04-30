#include "../public/StaticMesh.h"

#include <spdlog/spdlog.h>

#include "core/public/utils.h"
#include "RHI/public/utils.h"

namespace PrismaEngine
{
	StaticMesh::StaticMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		: m_vbo(vertices.data(), vertices.size())
	{
		VertexBufferLayout layout;
		layout.Add<float>(3);
		layout.Add<float>(3);
		layout.Add<float>(2);
		layout.Add<float>(4);

		m_vao = std::make_unique<VertexArray>(m_vbo, layout);
		m_ibo = std::make_unique<TypedBuffer<unsigned int>>(indices.data(), indices.size());

		spdlog::trace("Static mesh created with {} vertices for {} triangles.",
						vertices.size(), indices.size() / 3);
	}

	void StaticMesh::draw() const
	{
		m_vao->bind();
		m_ibo->bind(BufferUsageType::IndexBuffer);
		drawIndexedTriangles((unsigned int)m_ibo->getCount());
	}
}