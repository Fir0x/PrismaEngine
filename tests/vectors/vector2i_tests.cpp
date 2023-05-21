#include <gtest/gtest.h>

#include <cmath>

#include "core/maths/public/vec2i.h"
#include "core/maths/public/vector.h"

using namespace PrismaEngine;

TEST(Vector2iTest, ScalarInitialization)
{
	{
		constexpr int s = 0;
		Vec2i v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
	}

	{
		constexpr int s = 5;
		Vec2i v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
	}

	{
		constexpr int s = -2;
		Vec2i v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
	}
}

TEST(Vector2iTest, ClassicInitialization)
{
	constexpr int x = 1;
	constexpr int y = -5;
	Vec2i v(x, y);

	EXPECT_EQ(v.x, x);
	EXPECT_EQ(v.y, y);
}

TEST(Vector2iTest, Vec2Initialization)
{
	Vec2i v1(-2, 4);
	Vec2i v2(v1);

	EXPECT_EQ(v1.x, v2.x);
	EXPECT_EQ(v1.y, v2.y);
}

TEST(Vector2iTest, Add)
{
	constexpr int x1 = 1;
	constexpr int y1 = -2;
	Vec2i v1(x1, y1);

	constexpr int x2 = 7;
	constexpr int y2 = 4;
	Vec2i v2(x2, y2);

	{
		Vec2i v3 = v1 + v2;
		EXPECT_EQ(v3.x, x1 + x2);
		EXPECT_EQ(v3.y, y1 + y2);
	}

	{
		Vec2i v3 = v2 + v1;
		EXPECT_EQ(v3.x, x1 + x2);
		EXPECT_EQ(v3.y, y1 + y2);
	}
}

TEST(Vector2iTest, Subtract)
{
	constexpr int x1 = 0;
	constexpr int y1 = -2;
	Vec2i v1(x1, y1);

	constexpr int x2 = 7;
	constexpr int y2 = 4;
	Vec2i v2(x2, y2);

	EXPECT_EQ(v1.x - v2.x, x1 - x2);
	EXPECT_EQ(v1.y - v2.y, y1 - y2);

	EXPECT_EQ(v2.x - v1.x, x2 - x1);
	EXPECT_EQ(v2.y - v1.y, y2 - y1);
}

TEST(Vector2iTest, ScalarMultiplication)
{
	constexpr int x = 1;
	constexpr int y = -5;
	Vec2i v1(x, y);

	{
		Vec2i v2 = v1 * 0;
		EXPECT_EQ(v2.x, 0);
		EXPECT_EQ(v2.y, 0);
	}

	{
		constexpr int s = 23;
		Vec2i v2 = v1 * s;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
	}

	{
		constexpr int s = -2;
		Vec2i v2 = v1 * s;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
	}
}

TEST(Vector2iTest, HadamarProduct)
{
	constexpr int x1 = 0;
	constexpr int y1 = -2;
	Vec2i v1(x1, y1);

	constexpr int x2 = 7;
	constexpr int y2 = 4;
	Vec2i v2(x2, y2);

	{
		Vec2i v3 = v1 * v2;
		EXPECT_EQ(v3.x, x1 * x2);
		EXPECT_EQ(v3.y, y1 * y2);
	}

	{
		Vec2i v3 = v2 * v1;
		EXPECT_EQ(v3.x, x1 * x2);
		EXPECT_EQ(v3.y, y1 * y2);
	}
}

TEST(Vector2iTest, Magnitude)
{
	{
		int result = magnitude(Vec2i(0));
		EXPECT_EQ(result, 0);
	}

	{
		constexpr int x = 1;
		constexpr int y = -5;
		const int expected = std::sqrt(x * x + y * y);

		int result = magnitude(Vec2i(x, y));
		EXPECT_EQ(result, expected);
	}
}