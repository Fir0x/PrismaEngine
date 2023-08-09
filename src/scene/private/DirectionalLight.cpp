#include "../public/DirectionalLight.h"

#include "core/maths/public/Matrix3.h"
#include "RHI/public/utils.h"
#include "scene/public/Transform.h"

namespace PrismaEngine
{
	DirectionalLight::DirectionalLight(const Vector3f& direction, const Vector3f& color, const Material& material)
		: m_direction(direction.normalize()), m_color(color), m_material(material)
	{
	}

	void DirectionalLight::draw(const Matrix4f& viewMatrix) const
	{
		m_material.bind();
		const Vector3f viewspaceDirection = Transform::transformDirection(viewMatrix, m_direction).normalize();
		m_material.setUniform("lightDirection", viewspaceDirection);
		m_material.setUniform("lightColor", m_color);
		drawTriangles(3);
	}
}