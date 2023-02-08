#include "MeshRenderer.h"

#include "../../core/glErrors.h"

namespace BerylEngine
{
	MeshRenderer::MeshRenderer(std::shared_ptr<const StaticMesh> mesh, const Material& material)
		: m_mesh(mesh), m_material(material)
	{
	}

	void MeshRenderer::draw(const glm::mat4& model) const
	{
		m_material.setUniform("modelMatrix", model);
		m_material.bind();
		m_mesh->draw();
	}
}