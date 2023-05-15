#pragma once

#include <glm/glm.hpp>
#include "core/maths/public/mat4f.h"
#include "core/maths/public/vec3f.h"

namespace PrismaEngine
{
	class Transform
	{
	public:
		Transform();
		Transform(const Vec3f& position);

		void translate(const Vec3f& translation);
		void rotate(float angleX, float angleY, float angleZ);
		void scale(float scaleX, float scaleY, float scaleZ);

		/**
		 * @brief Uniform scaling on all axes
		 * @param factor 
		*/
		void scale(float factor);

		const Mat4f& getMatrix() const;
		const Vec3f getRight() const;
		const Vec3f getUp() const;
		const Vec3f getForward() const;

	private:
		Mat4f m_transforms;
	};
}