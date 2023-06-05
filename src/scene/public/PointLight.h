#pragma once

#include <glm/glm.hpp>

#include "core/maths/public/Matrix4.h"
#include "core/maths/public/Vector3.h"
#include "rendering/public/Material.h"

namespace PrismaEngine
{
	class PointLight
	{
	public:
		PointLight(const Material& material);
		PointLight(const Vector3f& position, float radius, const Vector3f& color, const Material& material);

		void setPosition(const Vector3f& position);
		void setRadius(float radius);
		void setColor(const Vector3f& color);

		const Vector3f& position() const;
		float radius() const;
		const Vector3f& color() const;
		/**
		 * @brief Give the light's attenuation coefficients
		 * @param linear 
		 * @param quadratic 
		*/
		void coefficients(float& linear, float& quadratic) const;

		void draw(unsigned int index) const;

	private:
		Vector3f m_position;
		float m_radius;
		Vector3f m_color;
		const Material& m_material;
	};
}