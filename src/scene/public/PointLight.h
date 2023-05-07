#pragma once

#include <glm/glm.hpp>

#include "rendering/public/Material.h"

namespace PrismaEngine
{
	class PointLight
	{
	public:
		PointLight(const Material& material);
		PointLight(const glm::vec3& position, float radius, const glm::vec3& color, const Material& material);

		void setPosition(const glm::vec3& position);
		void setRadius(float radius);
		void setColor(const glm::vec3& color);

		const glm::vec3& position() const;
		float radius() const;
		const glm::vec3& color() const;
		/**
		 * @brief Give the light's attenuation coefficients
		 * @param linear 
		 * @param quadratic 
		*/
		void coefficients(float& linear, float& quadratic) const;

		void draw(unsigned int index) const;

	private:
		glm::vec3 m_position;
		float m_radius;
		glm::vec3 m_color;
		const Material& m_material;
	};
}