#include "../public/Quaternion.h"

namespace PrismaEngine
{
	Quaternion::Quaternion(const float w, const float x, const float y, const float z)
		: m_w(w), m_x(x), m_y(y), m_z(z)
	{
	}

	Quaternion::Quaternion(const Vector3f& axis, const float angle)
	{
		identity();
	}

	Quaternion Quaternion::identity()
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Quaternion Quaternion::fromEuler(const float x, const float y, const float z)
	{
		return identity();
	}

	void Quaternion::normalize()
	{
	}

	bool Quaternion::isNormalized() const
	{
		return false;
	}

	float Quaternion::length() const
	{
		return 0.0f;
	}

	Quaternion Quaternion::inverse() const
	{
		return identity();
	}

	Vector3f Quaternion::getRotatedRight() const
	{
		return Vector3f();
	}

	Vector3f Quaternion::getRotatedUp() const
	{
		return Vector3f();
	}

	Vector3f Quaternion::getRotatedForward() const
	{
		return Vector3f();
	}

	Vector3f Quaternion::toEuler() const
	{
		return Vector3f();
	}

	Matrix3f Quaternion::toMatrix() const
	{
		return Matrix3f();
	}

	Quaternion Quaternion::operator+(const Quaternion& rhs) const
	{
		return identity();
	}

	Quaternion Quaternion::operator+=(const Quaternion& rhs)
	{
		return identity();
	}

	Quaternion Quaternion::operator-(const Quaternion& rhs) const
	{
		return identity();
	}

	Quaternion Quaternion::operator-=(const Quaternion& rhs)
	{
		return identity();
	}

	Quaternion Quaternion::operator*(const Quaternion& rhs) const
	{
		return identity();
	}

	Quaternion Quaternion::operator*=(const Quaternion& rhs)
	{
		return identity();
	}

	Quaternion Quaternion::operator*(const float scale) const
	{
		return identity();
	}

	Quaternion Quaternion::operator/(const float scale) const
	{
		return identity();
	}

	Quaternion Quaternion::operator==(const Quaternion& rhs) const
	{
		return identity();
	}

	Quaternion Quaternion::operator!=(const Quaternion& rhs) const
	{
		return identity();
	}

	Quaternion operator*(const float scale, const Quaternion& quat)
	{
		return Quaternion::identity();
	}
}