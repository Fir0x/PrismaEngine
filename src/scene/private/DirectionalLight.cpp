#include "../public/DirectionalLight.h"

#include "core/maths/public/mat3f.h"
#include "core/maths/public/vector.h"
#include "RHI/public/utils.h"

namespace PrismaEngine
{
	DirectionalLight::DirectionalLight(const Vec3f& direction, const Vec3f& color, const Material& material)
		: m_direction(normalize(direction)), m_color(color), m_material(material)
	{
	}

	void DirectionalLight::draw(const Mat4f& viewMatrix) const
	{
		m_material.bind();
		const Vec3f viewspaceDirection = normalize(Mat3f(viewMatrix) * m_direction);
		m_material.setUniform("lightDirection", viewspaceDirection);
		m_material.setUniform("lightColor", m_color);
		drawTriangles(3);
	}
}