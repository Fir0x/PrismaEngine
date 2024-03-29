#pragma once

#include <glm/glm.hpp>

namespace BerylEngine
{
	class PointLight
	{
	public:
		PointLight() = default;
		PointLight(const glm::vec3& position, float radius, const glm::vec3& color);

		void setPosition(const glm::vec3& position);
		void setRadius(float radius);
		void setColor(const glm::vec3& color);

		const glm::vec3& position() const;
		float radius() const;
		const glm::vec3& color() const;
		/// <summary>
		/// Give the light's attenuation coefficients
		/// </summary>
		/// <param name="linear"></param>
		/// <param name="quadratic"></param>
		void coefficients(float& linear, float& quadratic) const;

	private:
		glm::vec3 m_position;
		float m_radius;
		glm::vec3 m_color;
	};
}