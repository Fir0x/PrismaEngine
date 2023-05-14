#include "../public/DirectionalLight.h"

#include "RHI/public/utils.h"

namespace PrismaEngine
{
	DirectionalLight::DirectionalLight(const Vec3f& direction, const Vec3f& color, const Material& material)
		: m_direction(glm::normalize(direction)), m_color(color), m_material(material)
	{
	}

	void DirectionalLight::draw(const glm::mat4& viewMatrix) const
	{
		m_material.bind();
		const Vec3f viewspaceDirection = glm::normalize(glm::mat3(viewMatrix) * m_direction);
		m_material.setUniform("lightDirection", viewspaceDirection);
		m_material.setUniform("lightColor", m_color);
		drawTriangles(3);
	}
}