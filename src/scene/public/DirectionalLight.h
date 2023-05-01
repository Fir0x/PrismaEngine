#pragma once

#include <glm/vec3.hpp>

#include "rendering/public/Material.h"

namespace PrismaEngine
{
	class DirectionalLight
	{
	public:
		DirectionalLight(const glm::vec3& direction, const glm::vec3& color, const Material& material);

		void draw(const glm::mat4& viewMatrix) const;

	private:
		glm::vec3 m_direction;
		glm::vec3 m_color;
		const Material& m_material;
	};
}