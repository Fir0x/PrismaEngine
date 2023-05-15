#pragma once

#include <glm/glm.hpp>

namespace PrismaEngine
{
	inline glm::vec3 normalize(const glm::vec3& v)
	{
		return glm::normalize(v);
	}

	inline float dot(const glm::vec3& x, const glm::vec3& y)
	{
		return dot(x, y);
	}

	inline glm::vec3 cross(const glm::vec3& x, const glm::vec3& y)
	{
		return cross(x, y);
	}
}