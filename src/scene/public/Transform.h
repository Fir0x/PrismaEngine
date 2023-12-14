#pragma once

#include "core/maths/public/Matrix4.h"
#include "core/maths/public/Vector3.h"
#include "core/maths/public/Quaternion.h"

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
		/**
		 * @brief Rotation is set in YXZ order.
		 * @param angleX 
		 * @param angleY 
		 * @param angleZ 
		*/
		void setRotation(float angleX, float angleY, float angleZ);
		void setRotation(const Vector3f& rotation);
		void setRotation(const Vector3f& right, const Vector3f& up, const Vector3f& forward);
		void setRotation(const Matrix3f& rotationMatrix);

		/**
		 * @brief Uniform scaling on all axes
		 * @param factor 
		*/
		void scale(float factor);
		void scale(float scaleX, float scaleY, float scaleZ);

		Matrix4f getMatrix() const;
		Vector3f getRight() const;
		Vector3f getUp() const;
		Vector3f getForward() const;

		const Vector3f& getPosition() const;
		Matrix3f getRotation() const;
		void getRotation(float& pitch, float& yaw);
		const Vector3f& getScale() const;

		Transform getInverse() const;

		static Vector3f transformPoint(const Matrix4f& m, const Vector3f& p);
		static Vector3f transformDirection(const Matrix4f& m, const Vector3f& direction);

	private:
		Vector3f m_position;
		Quaternion m_quaternion;
		Vector3f m_scale;
	};
}