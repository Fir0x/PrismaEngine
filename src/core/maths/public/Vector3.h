#pragma once

#include "Vector2.h"

namespace PrismaEngine
{
	template<typename T>
	class Vector3
	{
	public:
		Vector3() = default;

		Vector3(const T& inX)
			: x(inX), y(inX), z(inX)
		{
		}

		Vector3(const T& inX, const T& inY)
			: x(inX), y(inY), z(static_cast<T>(0))
		{
		}

		Vector3(const T& inX, const T& inY, const T& inZ)
			: x(inX), y(inY), z(inZ)
		{
		}

		Vector3(const Vector2<T>& v)
			: Vector3(v.x, v.y)
		{
		}

		Vector3<T> operator+(const Vector3& rhs) const
		{
			return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector3<T> operator-(const Vector3& rhs) const
		{
			return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector3<T> operator*(const Vector3& rhs) const
		{
			return Vector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		Vector3<T> operator*(const T& rhs) const
		{
			return Vector3<T>(x * rhs, y * rhs, z * rhs);
		}

		Vector3<T> operator/(const Vector3& rhs) const
		{
			return Vector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		bool operator==(const Vector3& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool operator!=(const Vector3& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		float magnitude() const
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		float dot(const Vector3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		Vector3<T> cross(const Vector3& other) const
		{
			T newX = y * other.z - z * other.y;
			T newY = z * other.x - x * other.z;
			T newZ = x * other.y - y * other.x;

			return Vector3<T>(newX, newY, newZ);
		}

	public:
		union
		{
			T x;
			T r;
		};

		union
		{
			T y;
			T g;
		};

		union
		{
			T z;
			T b;
		};
	};

	template<typename T>
	Vector3<T> operator*(const T& lhs, const Vector3<T>& rhs)
	{
		return Vector3<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
	}

	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
}