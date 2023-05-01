#include "../public/DirectionalLight.h"

namespace PrismaEngine
{
	DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, const Material& material)
		: m_direction(glm::normalize(direction)), m_color(color), m_material(material)
	{
	}

	void DirectionalLight::draw(const glm::mat4& viewMatrix) const
	{
		m_material.bind();
		const glm::vec3 viewspaceDirection = glm::normalize(glm::mat3(viewMatrix) * m_direction);
		m_material.setUniform("lightDirection", viewspaceDirection);
		m_material.setUniform("lightColor", m_color);
	}
}