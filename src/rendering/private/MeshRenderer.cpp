#include "../public/MeshRenderer.h"

namespace PrismaEngine
{
	MeshRenderer::MeshRenderer(std::shared_ptr<const StaticMesh> mesh, const Material& material)
		: m_mesh(mesh), m_material(material)
	{
	}

	void MeshRenderer::draw(const Matrix4f& model) const
	{
		m_material.setUniform("modelMatrix", model);
		m_material.bind();
		m_mesh->draw();
	}
}