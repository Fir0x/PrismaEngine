#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "mat4f.h"
#include "vec3f.h"
#include "vec4f.h"

namespace PrismaEngine
{
	inline Mat4f transpose(const Mat4f& m)
	{
		return glm::transpose(m);
	}

	inline Mat4f inverse(const Mat4f& m)
	{
		return glm::inverse(m);
	}

	inline float determinant(const Mat4f& m)
	{
		return glm::determinant(m);
	}

	inline Mat4f translate(const Mat4f& m, const Vec3f& v)
	{
		return glm::translate(m, v);
	}

	inline Mat4f rotate(const Mat4f& m, float angle, const Vec3f& axe)
	{
		return glm::rotate(m, angle, axe);
	}

	inline Mat4f scale(const Mat4f& m, const Vec3f& v)
	{
		return glm::scale(m, v);
	}

	inline Vec4f column(const Mat4f& m, int i)
	{
		return glm::column(m, i);
	}

	inline Vec4f row(const Mat4f& m, int i)
	{
		return glm::row(m, i);
	}

	inline Mat4f lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up)
	{
		return glm::lookAt(eye, center, up);
	}

	inline Mat4f perspective(float fovy, float aspect, float near, float far)
	{
		return glm::perspective(fovy, aspect, near, far);
	}

	inline const glm::f32* value_ptr(const Mat4f& m)
	{
		return glm::value_ptr(m);
	}
}