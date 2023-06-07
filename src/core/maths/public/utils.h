#pragma once

#define PRISMA_PI 3.14159265358979323846

#include <cmath>

namespace PrismaEngine
{
	inline float degreesToRadians(float x)
	{
		constexpr float ratio = static_cast<float>(PRISMA_PI) / 180.0f;
		return x * ratio;
	}

	inline double degreesToRadians(double x)
	{
		constexpr double ratio = static_cast<double>(PRISMA_PI) / 180.0;
		return x * ratio;
	}

	inline float radiansToDegrees(float x)
	{
		constexpr float ratio = 180.0f / static_cast<float>(PRISMA_PI);
		return x * ratio;
	}

	inline double radiansToDegrees(double x)
	{
		constexpr double ratio = 180.0f / static_cast<double>(PRISMA_PI);
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
}