#pragma once

#include <glm/glm.hpp>

#include "vec4f.h"

namespace PrismaEngine
{

	inline float magnitude(const Vec4f& v)
	{
		return glm::length(v);
	}
}