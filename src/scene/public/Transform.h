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

		void translate(const Vector3f& translation);
		void translate(float x, float y, float z);
		void rotate(float angleX, float angleY, float angleZ);
		void setRotation(float angleX, float angleY, float angleZ);
		void setRotation(const Matrix3f& rotation);
		void setMatrix(const Matrix4f& matrix);

		/**
		 * @brief Uniform scaling on all axes
		 * @param factor 
		*/
		void scale(float factor);
		void scale(float scaleX, float scaleY, float scaleZ);

		const Matrix4f& getMatrix() const;
		Vector3f getRight() const;
		Vector3f getUp() const;
		Vector3f getForward() const;

		Vector3f getPosition() const;
		Matrix3f getRotation() const;
		void getRotation(float& pitch, float& yaw);

	private:
		Matrix4f m_matrix;
	};
}