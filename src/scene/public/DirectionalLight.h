#pragma once

#include <glm/vec3.hpp>

#include "core/maths/public/vec3f.h"
#include "rendering/public/Material.h"

namespace PrismaEngine
{
	class DirectionalLight
	{
	public:
		DirectionalLight(const Vec3f& direction, const Vec3f& color, const Material& material);

		void draw(const glm::mat4& viewMatrix) const;

	private:
		Vec3f m_direction;
		Vec3f m_color;
		const Material& m_material;
	};
}