#include "StaticMesh.h"

#include <spdlog/spdlog.h>

#include "utils.h"

namespace BerylEngine
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
		glDrawElements(GL_TRIANGLES, (unsigned int)m_ibo->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}