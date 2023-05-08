#include "../public/PointLight.h"

#include <glm/ext.hpp>

#include "geometry/public/meshUtilities.h"

namespace PrismaEngine
{
	PointLight::PointLight(const Material& material)
		: m_position(glm::vec3(0.0f)), m_radius(1.0f),
		m_color(glm::vec3(1.0f)), m_material(material)
	{
	}

	PointLight::PointLight(const glm::vec3& position, float radius, const glm::vec3& color, const Material& material)
		: m_position(position), m_radius(radius),
		m_color(color), m_material(material)
	{
	}

	void PointLight::setPosition(const glm::vec3& position)
	{
		m_position = position;
	}

	void PointLight::setRadius(float radius)
	{
		m_radius = radius;
	}

	void PointLight::setColor(const glm::vec3& color)
	{
		m_color = color;
	}

	const glm::vec3& PointLight::position() const
	{
		return m_position;
	}

	float PointLight::radius() const
	{
		return m_radius;
	}

	const glm::vec3& PointLight::color() const
	{
		return m_color;
	}

	static float lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}

	static float getLerpT(float a, float b, float x)
	{
		return 1 - (b - x) / (b - a);
	}

	void PointLight::coefficients(float& linear, float& quadratic) const
	{
		// Values based OGRE engine (https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation)
		// Lerp is used to allow intermediate radius values between thresholds.
		if (m_radius <= 7)
		{
			linear = 0.7f;
			quadratic = 1.8f;
		}
		else if (m_radius <= 13)
		{
			float lerpCoef = getLerpT(7, 13, m_radius);
			linear = lerp(0.7f, 0.35f, lerpCoef);
			quadratic = lerp(1.8f, 0.44f, lerpCoef);
		}
		else if (m_radius <= 20)
		{
			float lerpCoef = getLerpT(13, 20, m_radius);
			linear = lerp(0.35f, 0.22f, lerpCoef);
			quadratic = lerp(0.44f, 0.20f, lerpCoef);
		}
		else if (m_radius <= 32)
		{
			float lerpCoef = getLerpT(20, 32, m_radius);
			linear = lerp(0.22f, 0.14f, lerpCoef);
			quadratic = lerp(0.20f, 0.07f, lerpCoef);
		}
		else if (m_radius <= 50)
		{
			float lerpCoef = getLerpT(32, 50, m_radius);
			linear = lerp(0.14f, 0.09f, lerpCoef);
			quadratic = lerp(0.07f, 0.032f, lerpCoef);
		}
		else if (m_radius <= 65)
		{
			float lerpCoef = getLerpT(50, 65, m_radius);
			linear = lerp(0.09f, 0.07f, lerpCoef);
			quadratic = lerp(0.032f, 0.017f, lerpCoef);
		}
		else if (m_radius <= 100)
		{
			float lerpCoef = getLerpT(65, 100, m_radius);
			linear = lerp(0.09f, 0.045f, lerpCoef);
			quadratic = lerp(0.017f, 0.0075f, lerpCoef);
		}
		else if (m_radius <= 160)
		{
			float lerpCoef = getLerpT(100, 160, m_radius);
			linear = lerp(0.045f, 0.027f, lerpCoef);
			quadratic = lerp(0.0075f, 0.0028f, lerpCoef);
		}
		else if (m_radius <= 200)
		{
			float lerpCoef = getLerpT(160, 200, m_radius);
			linear = lerp(0.027f, 0.022f, lerpCoef);
			quadratic = lerp(0.0028f, 0.0019f, lerpCoef);
		}
		else if (m_radius <= 325)
		{
			float lerpCoef = getLerpT(200, 325, m_radius);
			linear = lerp(0.022f, 0.014f, lerpCoef);
			quadratic = lerp(0.0019f, 0.0007f, lerpCoef);
		}
		else if (m_radius <= 600)
		{
			float lerpCoef = getLerpT(325, 600, m_radius);
			linear = lerp(0.014f, 0.007f, lerpCoef);
			quadratic = lerp(0.0007f, 0.0002f, lerpCoef);
		}
		else
		{
			linear = 0.0014f;
			quadratic = 0.000007f;
		}
	}

	void PointLight::draw(unsigned int index) const
	{
		m_material.bind();
		glm::mat4 modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), m_position), glm::vec3(m_radius));
		m_material.setUniform("modelMatrix", modelMatrix);
		m_material.setUniform("lightIndex", index);
		auto ligthVolume = MeshUtilities::staticSphere(16, 8);
		ligthVolume->draw();
	}
}