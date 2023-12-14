#include "../public/Quaternion.h"

#include "core/maths/public/utils.h"

namespace PrismaEngine
{
	Quaternion::Quaternion(const float w, const float x, const float y, const float z)
		: m_w(w), m_x(x), m_y(y), m_z(z)
	{
	}

	Quaternion::Quaternion(const Vector3f& axis, const float angleDegree)
	{
		const float halfAngle = degreesToRadians(angleDegree * 0.5f);
		m_w = cos(halfAngle);

		const float sinTerm = sin(halfAngle);
		m_x = sinTerm * axis.dot(Vector3f::right());
		m_y = sinTerm * axis.dot(Vector3f::up());
		m_z = sinTerm * axis.dot(Vector3f::forward());
	}

	Quaternion::Quaternion(const Matrix3f& matrix)
	{
		if (abs(1.0f - matrix.determinant()) > 1e-6f)
		{
			*this = Quaternion::identity();
			return;
		}

		float trace = matrix.trace();
		if (trace > 0.0f)
		{
			const float s = 2.0f * sqrt(trace + 1.0f);
			m_w = 0.25f * s;
			const float oneOnS = 1.0f / s;
			m_x = (matrix.getValue(1, 2) - matrix.getValue(2, 1)) * oneOnS;
			m_y = (matrix.getValue(2, 0) - matrix.getValue(0, 2)) * oneOnS;
			m_z = (matrix.getValue(0, 1) - matrix.getValue(1, 0)) * oneOnS;
		}
		else
		{
			int i = 0;
			if (matrix.getValue(1, 1) > matrix.getValue(0, 0))
				i = 1;

			if (matrix.getValue(2, 2) > matrix.getValue(i, i))
				i = 2;

			static constexpr int next[3] = { 1, 2, 0 };
			const int j = next[i];
			const int k = next[j];

			float s = sqrt(matrix.getValue(i, i) - matrix.getValue(j, j) - matrix.getValue(k, k) + 1.0f);

			float* qt = &m_x;
			qt[i] = 0.5f * s;

			if (s != 0.0f)
				s = 0.5f / s;

			m_w = (matrix.getValue(j, k) - matrix.getValue(k, j)) * s;
			qt[j] = (matrix.getValue(i, j) + matrix.getValue(j, i)) * s;
			qt[k] = (matrix.getValue(i, k) + matrix.getValue(k, i)) * s;
		}
	}

	Quaternion Quaternion::identity()
	{
		return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	}

	Quaternion Quaternion::fromEuler(const float x, const float y, const float z)
	{
		const float halfRadX = degreesToRadians(x * 0.5f);
		const float cx = cos(halfRadX);
		const float sx = sin(halfRadX);

		const float halfRadY = degreesToRadians(y * 0.5f);
		const float cy = cos(halfRadY);
		const float sy = sin(halfRadY);

		const float halfRadZ = degreesToRadians(z * 0.5f);
		const float cz = cos(halfRadZ);
		const float sz = sin(halfRadZ);

		const float qw = sy * sx * sz + cy * cx * cz;
		const float qx = sy * sz * cx + sx * cy * cz;
		const float qy = sy * cx * cz - sx * sz * cy;
		const float qz = sz * cy * cx - sy * sx * cz;

		return Quaternion(qw, qx, qy, qz);
	}

	void Quaternion::normalize()
	{
		const float oneOnLength = 1.0f / length();
		m_w *= oneOnLength;
		m_x *= oneOnLength;
		m_y *= oneOnLength;
		m_z *= oneOnLength;
	}

	bool Quaternion::isNormalized() const
	{
		const float lengthSquared = m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;

		return lengthSquared - 1.0f <= 1e-6;
	}

	float Quaternion::lengthSquared() const
	{
		return m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;
	}

	float Quaternion::length() const
	{
		return sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
	}

	Quaternion Quaternion::inverse() const
	{
		const Vector3f vectorPart(m_x, m_y, m_z);
		float vectorDot = vectorPart.dot(vectorPart);
		
		const float quotient = 1.0f / (m_w * m_w + vectorDot);
		const Vector3f newVectorPart = -vectorPart * quotient;
		const float newW = m_w * quotient;

		return Quaternion(newW, newVectorPart.x, newVectorPart.y, newVectorPart.z);
	}

	Vector3f Quaternion::getRotatedRight() const
	{
		return Vector3f(1.0f - 2.0f * (m_y * m_y + m_z * m_z), 2.0f * (m_x * m_y + m_w * m_z), 2.0f * (m_x * m_z - m_w * m_y));
	}

	Vector3f Quaternion::getRotatedUp() const
	{
		return Vector3f(2.0f * (m_x * m_y - m_w * m_z), 1.0f - 2.0f * (m_x * m_x + m_z * m_z), 2.0f * (m_y * m_z + m_w * m_x));
	}

	Vector3f Quaternion::getRotatedForward() const
	{
		return Vector3f(2.0f * (m_x * m_z + m_w * m_y), 2.0f * (m_y * m_z - m_w * m_x), 1.0f - 2.0f * (m_x * m_x + m_y * m_y));
	}

	Vector3f Quaternion::rotateVector(const Vector3f& v) const
	{
		Quaternion vecAsQuat(0.0f, v.x, v.y, v.z);
		Quaternion tmp = (*this * vecAsQuat) * this->inverse();

		return Vector3f(tmp.m_x, tmp.m_y, tmp.m_z);
	}

	Vector3f Quaternion::Quaternion::toEuler() const
	{
		const float angleX = radiansToDegrees(asin(2.0f * (m_w * m_x - m_y * m_z)));
		const float angleY = radiansToDegrees(atan2(2.0f * (m_x * m_z + m_w * m_y), 1.0f - 2.0f * (m_x * m_x + m_y * m_y)));
		const float angleZ = radiansToDegrees(atan2(2.0f * (m_x * m_y + m_w * m_z), 1.0f - 2.0f * (m_x * m_x + m_z * m_z)));
		
		return Vector3f(angleX, angleY, angleZ);
	}

	Matrix3f Quaternion::toMatrix() const
	{
		Vector3f row0 = getRotatedRight();
		Vector3f row1 = getRotatedUp();
		Vector3f row2 = getRotatedForward();

		return Matrix3f(row0, row1, row2);
	}

	float Quaternion::getX() const
	{
		return m_x;
	}

	float Quaternion::getY() const
	{
		return m_y;
	}

	float Quaternion::getZ() const
	{
		return m_z;
	}

	float Quaternion::getW() const
	{
		return m_w;
	}

	Quaternion Quaternion::operator+(const Quaternion& rhs) const
	{
		return Quaternion(m_w + rhs.m_w, m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& rhs)
	{
		m_w += rhs.m_w;
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;

		return *this;
	}

	Quaternion Quaternion::operator-(const Quaternion& rhs) const
	{
		return Quaternion(m_w - rhs.m_w, m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
	}

	Quaternion& Quaternion::operator-=(const Quaternion& rhs)
	{
		m_w -= rhs.m_w;
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;

		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& rhs) const
	{
		const Vector3f vectorPart(m_x, m_y, m_z);
		const Vector3f rhsVectorPart(rhs.m_x, rhs.m_y, rhs.m_z);

		const float resultW = m_w * rhs.m_w - vectorPart.dot(rhsVectorPart);
		const Vector3f resultVectorPart = rhs.m_w * vectorPart + m_w * rhsVectorPart + vectorPart.cross(rhsVectorPart);

		return Quaternion(resultW, resultVectorPart.x, resultVectorPart.y, resultVectorPart.z);
	}

	Quaternion& Quaternion::operator*=(const Quaternion& rhs)
	{
		const Vector3f vectorPart(m_x, m_y, m_z);
		const Vector3f rhsVectorPart(rhs.m_x, rhs.m_y, rhs.m_z);

		const Vector3f newVectorPart = rhs.m_w * vectorPart + m_w * rhsVectorPart + vectorPart.cross(rhsVectorPart);
		m_w = m_w * rhs.m_w - vectorPart.dot(rhsVectorPart);
		m_x = newVectorPart.x;
		m_y = newVectorPart.y;
		m_z = newVectorPart.z;

		return *this;
	}

	Quaternion Quaternion::operator*(const float scale) const
	{
		return Quaternion(m_w * scale, m_x * scale, m_y * scale, m_z * scale);
	}
	
	Quaternion operator*(const float scale, const Quaternion& quat)
	{
		return quat * scale;
	}

	Quaternion& Quaternion::operator*=(const float scale)
	{
		m_w *= scale;
		m_x *= scale;
		m_y *= scale;
		m_z *= scale;

		return *this;
	}

	Quaternion Quaternion::operator/(const float scale) const
	{
		const float oneOnScale = 1.0f / scale;
		return Quaternion(m_w * oneOnScale, m_x * oneOnScale, m_y * oneOnScale, m_z * oneOnScale);
	}

	Quaternion& Quaternion::operator/=(const float scale)
	{
		const float oneOnScale = 1.0f / scale;
		m_w *= oneOnScale;
		m_x *= oneOnScale;
		m_y *= oneOnScale;
		m_z *= oneOnScale;

		return *this;
	}

	bool Quaternion::operator==(const Quaternion& rhs) const
	{
		return m_w == rhs.m_w && m_x == rhs.m_x && m_y == rhs.m_y && m_z == rhs.m_z;
	}

	bool Quaternion::operator!=(const Quaternion& rhs) const
	{
		return m_w != rhs.m_w || m_x != rhs.m_x || m_y != rhs.m_y || m_z != rhs.m_z;
	}

}