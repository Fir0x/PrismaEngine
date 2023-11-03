#pragma once

#include "Matrix3.h"
#include "Vector3.h"

namespace PrismaEngine
{
	class Quaternion
	{
	public:
		Quaternion(const float w, const float x, const float y, const float z);
		/// <summary>
		/// Initialize quaternion with a rotation around an axis.
		/// </summary>
		/// <param name="axis"></param>
		/// <param name="angle"></param>
		Quaternion(const Vector3f& axis, const float angleDegree);
		Quaternion(const Matrix3f& matrix);
		/// <summary>
		/// Return identity quaternion.
		/// </summary>
		/// <returns></returns>
		static Quaternion identity();
		static Quaternion fromEuler(const float x, const float y, const float z);

		void normalize();
		bool isNormalized() const;
		float lengthSquared() const;
		float length() const;

		Quaternion inverse() const;

		Vector3f getRotatedRight() const;
		Vector3f getRotatedUp() const;
		Vector3f getRotatedForward() const;
		Vector3f toEuler() const;
		Matrix3f toMatrix() const;

		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		Quaternion operator+(const Quaternion& rhs) const;
		Quaternion& operator+=(const Quaternion& rhs);
		Quaternion operator-(const Quaternion& rhs) const;
		Quaternion& operator-=(const Quaternion& rhs);
		Quaternion operator*(const Quaternion& rhs) const;
		Quaternion& operator*=(const Quaternion& rhs);
		Quaternion operator*(const float scale) const;
		Quaternion& operator*=(const float scale);
		Quaternion operator/(const float scale) const;
		Quaternion& operator/=(const float scale);
		bool operator==(const Quaternion& rhs) const;
		bool operator!=(const Quaternion& rhs) const;

	private:
		float m_w;
		float m_x;
		float m_y;
		float m_z;
	};

	Quaternion operator*(const float scale, const Quaternion& quat);
}