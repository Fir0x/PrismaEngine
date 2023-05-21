#pragma once

#include <glm/glm.hpp>

#include "vec2f.h"
#include "vec3f.h"
#include "vec4f.h"

namespace PrismaEngine
{

	inline float magnitude(const Vec2f& v)
	{
		return glm::length(v);
	}

	inline Vec2f normalize(const Vec2f& v)
	{
		return glm::normalize(v);
	}

	inline float dot(const Vec2f& x, const Vec2f& y)
	{
		return glm::dot(x, y);
	}

	inline float magnitude(const Vec3f& v)
	{
		return glm::length(v);
	}

	inline Vec3f normalize(const Vec3f& v)
	{
		return glm::normalize(v);
	}

	inline float dot(const Vec3f& x, const Vec3f& y)
	{
		return glm::dot(x, y);
	}

	inline Vec3f cross(const Vec3f& x, const Vec3f& y)
	{
		return glm::cross(x, y);
	}

	inline float magnitude(const Vec4f& v)
	{
		return glm::length(v);
	}
}