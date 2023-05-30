#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace PrismaEngine
{
	template<typename T>
	class Vector4
	{
	public:
		Vector4() = default;

		Vector4(const T& inX)
			: x(inX), y(inX), z(inX), w(inX)
		{
		}

		Vector4(const T& inX, const T& inY)
			: x(inX), y(inY), z(static_cast<T>(0)), w(static_cast<T>(0))
		{
		}

		Vector4(const T& inX, const T& inY, const T& inZ)
			: x(inX), y(inY), z(inZ), w(static_cast<T>(0))
		{
		}

		Vector4(const T& inX, const T& inY, const T& inZ, const T& inW)
			: x(inX), y(inY), z(inZ), w(inW)
		{
		}

		Vector4(const Vector2<T>& v)
			: Vector4(v.x, v.y)
		{
		}

		Vector4(const Vector3<T>& v)
			: Vector4(v.x, v.y, v.z)
		{
		}

		Vector4<T> operator+(const Vector4& rhs) const
		{
			return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		Vector4<T> operator-(const Vector4& rhs) const
		{
			return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		Vector4<T> operator*(const Vector4& rhs) const
		{
			return Vector4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
		}

		Vector4<T> operator*(const T& rhs) const
		{
			return Vector4<T>(x * rhs, y * rhs, z * rhs, w * rhs);
		}

		Vector4<T> operator/(const Vector4& rhs) const
		{
			return Vector4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		}

		bool operator==(const Vector4& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		bool operator!=(const Vector4& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
		}

		float magnitude() const
		{
			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		float dot(const Vector4& other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
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

		union
		{
			T w;
			T a;
		};
	};

	template<typename T>
	Vector4<T> operator*(const T& lhs, const Vector4<T>& rhs)
	{
		return Vector4<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
	}

	typedef Vector4<float> Vector4f;
	typedef Vector4<double> Vector4d;
}