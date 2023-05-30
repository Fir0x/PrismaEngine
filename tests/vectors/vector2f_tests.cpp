#include <gtest/gtest.h>

#include <cmath>

#include "core/maths/public/Vector2.h"

using namespace PrismaEngine;

TEST(Vector2fTest, ScalarInitialization) {
	{
		constexpr float s = 0.0f;
		Vector2f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
	}

	{
		constexpr float s = 5.0f;
		Vector2f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
	}

	{
		constexpr float s = -2.0f;
		Vector2f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
	}
}

TEST(Vector2fTest, ClassicInitialization)
{
	constexpr float x = 1.0f;
	constexpr float y = -5.3f;
	Vector2f v(x, y);

	EXPECT_EQ(v.x, x);
	EXPECT_EQ(v.y, y);
}

TEST(Vector2fTest, Vec2Initialization)
{
	Vector2f v1(-2.0f, 4.0f);
	Vector2f v2(v1);

	EXPECT_EQ(v1.x, v2.x);
	EXPECT_EQ(v1.y, v2.y);
}

TEST(Vector2fTest, Add)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -2.0f;
	Vector2f v1(x1, y1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	Vector2f v2(x2, y2);

	{
		Vector2f v3 = v1 + v2;
		EXPECT_EQ(v3.x, x1 + x2);
		EXPECT_EQ(v3.y, y1 + y2);
	}

	{
		Vector2f v3 = v2 + v1;
		EXPECT_EQ(v3.x, x1 + x2);
		EXPECT_EQ(v3.y, y1 + y2);
	}
}

TEST(Vector2fTest, Subtract)
{
	constexpr float x1 = 0.0f;
	constexpr float y1 = -2.0f;
	Vector2f v1(x1, y1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	Vector2f v2(x2, y2);

	EXPECT_EQ(v1.x - v2.x, x1 - x2);
	EXPECT_EQ(v1.y - v2.y, y1 - y2);

	EXPECT_EQ(v2.x - v1.x, x2 - x1);
	EXPECT_EQ(v2.y - v1.y, y2 - y1);
}

TEST(Vector2fTest, ScalarMultiplication)
{
	constexpr float x = 1.0f;
	constexpr float y = -5.3f;
	Vector2f v1(x, y);

	{
		Vector2f v2 = v1 * 0.0f;
		EXPECT_EQ(v2.x, 0.0f);
		EXPECT_EQ(v2.y, 0.0f);
	}

	{
		constexpr float s = 23.45f;
		Vector2f v2 = v1 * s;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
	}

	{
		constexpr float s = 23.45f;
		Vector2f v2 = s * v1;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
	}

	{
		constexpr float s = -2.1f;
		Vector2f v2 = v1 * s;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
	}
}

TEST(Vector2fTest, HadamarProduct)
{
	constexpr float x1 = 0.0f;
	constexpr float y1 = -2.0f;
	Vector2f v1(x1, y1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	Vector2f v2(x2, y2);

	{
		Vector2f v3 = v1 * v2;
		EXPECT_EQ(v3.x, x1 * x2);
		EXPECT_EQ(v3.y, y1 * y2);
	}

	{
		Vector2f v3 = v2 * v1;
		EXPECT_EQ(v3.x, x1 * x2);
		EXPECT_EQ(v3.y, y1 * y2);
	}
}

TEST(Vector2fTest, Magnitude)
{
	{
		float result = Vector2f(0.0f).magnitude();
		EXPECT_EQ(result, 0.0f);
	}

	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		const float expected = std::sqrt(x * x + y * y);

		float result = Vector2f(x, y).magnitude();
		EXPECT_EQ(result, expected);
	}
}

TEST(Vector2fTest, Dot)
{
	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;

		float result = Vector2f(x, y).dot(Vector2f(0.0f));
		EXPECT_EQ(result, 0.0f);
	}

	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		Vector2f v(x, y);

		const float expected = x * x + y * y;

		EXPECT_EQ(v.dot(v), expected);
	}

	{
		constexpr float x1 = 1.0f;
		constexpr float y1 = -5.3f;
		Vector2f v1(x1, y1);

		constexpr float x2 = 7.21f;
		constexpr float y2 = 4.29446f;
		Vector2f v2(x2, y2);

		constexpr float expected = x1 * x2 + y1 * y2;

		EXPECT_EQ(v1.dot(v2), expected);
		EXPECT_EQ(v1.dot(v2), v2.dot(v1));
	}
}

TEST(Vector2fTest, Equality)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -5.3f;
	Vector2f v1(x1, y1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	Vector2f v2(x2, y2);

	EXPECT_TRUE(v1 == v1);
	EXPECT_FALSE(v1 == v2);
}

TEST(Vector2fTest, Inequality)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -5.3f;
	Vector2f v1(x1, y1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	Vector2f v2(x2, y2);

	EXPECT_FALSE(v1 != v1);
	EXPECT_TRUE(v1 != v2);
}