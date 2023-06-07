#pragma once

#include <glm/glm.hpp>
#include "core/maths/public/Matrix4.h"
#include "core/maths/public/Vector3.h"

namespace PrismaEngine
{
	/**
	 * @brief Scale, Rotation and Translation.
	 * Transform matrix is in row layout, meaning for example the translation is stored as the bottom row, not right-most column.
	*/
	class Transform
	{
	public:
		Transform();
		Transform(const Vector3f& position);

		// TODO
		// Create tests
		void translate(const Vector3f& translation);
		void rotate(float angleX, float angleY, float angleZ);
		void setRotation(const Matrix3f& rotation);
		void scale(float scaleX, float scaleY, float scaleZ);

		/**
		 * @brief Uniform scaling on all axes
		 * @param factor 
		*/
		void scale(float factor);

		const Matrix4f& getMatrix() const;
		const Vector3f getRight() const;
		const Vector3f getUp() const;
		const Vector3f getForward() const;

	private:
		Matrix4f m_transforms;
	};
}