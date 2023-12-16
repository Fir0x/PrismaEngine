#pragma once

#define PRISMA_PI 3.14159265358979323846

#include <cmath>

namespace PrismaEngine
{
	inline float degreesToRadians(float x)
	{
		constexpr float ratio = static_cast<float>(PRISMA_PI / 180.0);
		return x * ratio;
	}

	inline double degreesToRadians(double x)
	{
		constexpr double ratio = PRISMA_PI / 180.0;
		return x * ratio;
	}

	inline float radiansToDegrees(float x)
	{
		constexpr float ratio = static_cast<float>(180.0 / PRISMA_PI);
		return x * ratio;
	}

	inline double radiansToDegrees(double x)
	{
		constexpr double ratio = 180.0 / PRISMA_PI;
		return x * ratio;
	}

	/**
	 * @brief 
	 * @param x Angle in radians
	 * @return 
	*/
	inline float sin(float x)
	{
		return std::sin(x);
	}

	/**
	 * @brief
	 * @param x Angle in radians
	 * @return
	*/
	inline float cos(float x)
	{
		return std::cos(x);
	}

	/**
	 * @brief
	 * @param x Angle in radians
	 * @return
	*/
	inline float asin(float x)
	{
		return std::asin(x);
	}

	/**
	 * @brief
	 * @param x Angle in radians
	 * @return
	*/
	inline float acos(float x)
	{
		return std::acos(x);
	}

	inline float atan2(float y, float x)
	{
		return std::atan2f(y, x);
	}

	inline float clamp(float x, float min, float max)
	{
		if (x < min)
			return min;

		if (x > max)
			return max;

		return x;
	}

	inline float abs(float x)
	{
		return x < 0.0f ? -x : x;
	}
}