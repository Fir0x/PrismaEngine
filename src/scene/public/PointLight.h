#pragma once

#include <glm/glm.hpp>

#include "core/maths/public/mat4f.h"
#include "core/maths/public/vec3f.h"
#include "rendering/public/Material.h"

namespace PrismaEngine
{
	class PointLight
	{
	public:
		PointLight(const Material& material);
		PointLight(const Vec3f& position, float radius, const Vec3f& color, const Material& material);

		void setPosition(const Vec3f& position);
		void setRadius(float radius);
		void setColor(const Vec3f& color);

		const Vec3f& position() const;
		float radius() const;
		const Vec3f& color() const;
		/**
		 * @brief Give the light's attenuation coefficients
		 * @param linear 
		 * @param quadratic 
		*/
		void coefficients(float& linear, float& quadratic) const;

		void draw(unsigned int index) const;

	private:
		Vec3f m_position;
		float m_radius;
		Vec3f m_color;
		const Material& m_material;
	};
}