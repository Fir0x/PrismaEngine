#pragma once

#include <glm/glm.hpp>

namespace PrismaEngine
{
	template<typename T>
	class Vector2
	{
	public:
		Vector2() = default;

		Vector2(const T& inX)
			: x(inX), y(inX)
		{
		}

		Vector2(const T& inX, const T& inY)
			: x(inX), y(inY)
		{
		}

		Vector2<T> operator+(const Vector2& rhs) const
		{
			return Vector2<T>(x + rhs.x, y + rhs.y);
		}

		Vector2<T> operator-(const Vector2& rhs) const
		{
			return Vector2<T>(x - rhs.x, y - rhs.y);
		}

		Vector2<T> operator*(const Vector2& rhs) const
		{
			return Vector2<T>(x * rhs.x, y * rhs.y);
		}

		Vector2<T> operator*(const T& rhs) const
		{
			return Vector2<T>(x * rhs, y * rhs);
		}

		Vector2<T> operator/(const Vector2& rhs) const
		{
			return Vector2<T>(x / rhs.x, y / rhs.y);
		}

		bool operator==(const Vector2& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		bool operator!=(const Vector2& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}

		float magnitude() const
		{
			return std::sqrt(x * x + y * y);
		}

		float dot(const Vector2& other)
		{
			return x * other.x + y * other.y;
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
	};

	template<typename T>
	Vector2<T> operator*(const T& lhs, const Vector2<T>& rhs)
	{
		return Vector2<T>(lhs * rhs.x, lhs * rhs.y);
	}

	typedef Vector2<int> Vector2i;
	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
}