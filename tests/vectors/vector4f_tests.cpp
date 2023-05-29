#include <gtest/gtest.h>

#include <cmath>

#include "core/maths/public/vec4f.h"
#include "core/maths/public/vector.h"

using namespace PrismaEngine;

TEST(Vector4fTest, ScalarInitialization) {
	{
		constexpr float s = 0.0f;
		Vec4f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
		EXPECT_EQ(v.z, s);
		EXPECT_EQ(v.w, s);
	}

	{
		constexpr float s = 5.0f;
		Vec4f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
		EXPECT_EQ(v.z, s);
		EXPECT_EQ(v.w, s);
	}

	{
		constexpr float s = -2.0f;
		Vec4f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
		EXPECT_EQ(v.z, s);
		EXPECT_EQ(v.w, s);
	}
}

TEST(Vector4fTest, ClassicInitialization)
{
	constexpr float x = 1.0f;
	constexpr float y = -5.3f;
	constexpr float z = 0.0f;
	constexpr float w = 71.127f;
	Vec4f v(x, y, z, w);

	EXPECT_EQ(v.x, x);
	EXPECT_EQ(v.y, y);
	EXPECT_EQ(v.z, z);
	EXPECT_EQ(v.w, w);
}

TEST(Vector4fTest, Vec3Initialization)
{
	Vec4f v1(-2.0f, 4.0f, 7.0f, 0.1f);
	Vec4f v2(v1);

	EXPECT_EQ(v1.x, v2.x);
	EXPECT_EQ(v1.y, v2.y);
	EXPECT_EQ(v1.z, v2.z);
	EXPECT_EQ(v1.w, v2.w);
}

TEST(Vector4fTest, Add)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -2.0f;
	constexpr float z1 = 64.87f;
	constexpr float w1 = -3.12f;
	Vec4f v1(x1, y1, z1, w1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	constexpr float w2 = 0.12f;
	Vec4f v2(x2, y2, z2, w2);

	{
		Vec4f v3 = v1 + v2;
		EXPECT_EQ(v3.x, x1 + x2);
		EXPECT_EQ(v3.y, y1 + y2);
		EXPECT_EQ(v3.z, z1 + z2);
		EXPECT_EQ(v3.w, w1 + w2);
	}

	{
		Vec4f v3 = v2 + v1;
		EXPECT_EQ(v3.x, x1 + x2);
		EXPECT_EQ(v3.y, y1 + y2);
		EXPECT_EQ(v3.z, z1 + z2);
		EXPECT_EQ(v3.w, w1 + w2);
	}
}

TEST(Vector4fTest, Subtract)
{
	constexpr float x1 = 0.0f;
	constexpr float y1 = -2.0f;
	constexpr float z1 = 64.87f;
	constexpr float w1 = -3.12f;
	Vec4f v1(x1, y1, z1, w1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	constexpr float w2 = 0.12f;
	Vec4f v2(x2, y2, z2, w2);

	EXPECT_EQ(v1.x - v2.x, x1 - x2);
	EXPECT_EQ(v1.y - v2.y, y1 - y2);
	EXPECT_EQ(v1.z - v2.z, z1 - z2);
	EXPECT_EQ(v1.w - v2.w, w1 - w2);

	EXPECT_EQ(v2.x - v1.x, x2 - x1);
	EXPECT_EQ(v2.y - v1.y, y2 - y1);
	EXPECT_EQ(v2.z - v1.z, z2 - z1);
	EXPECT_EQ(v2.w - v1.w, w2 - w1);
}

TEST(Vector4fTest, ScalarMultiplication)
{
	constexpr float x = 1.0f;
	constexpr float y = -5.3f;
	constexpr float z = 0.0f;
	constexpr float w = 71.127f;
	Vec4f v1(x, y, z, w);

	{
		Vec4f v2 = v1 * 0.0f;
		EXPECT_EQ(v2.x, 0.0f);
		EXPECT_EQ(v2.y, 0.0f);
		EXPECT_EQ(v2.z, 0.0f);
		EXPECT_EQ(v2.w, 0.0f);
	}

	{
		constexpr float s = 23.45f;
		Vec4f v2 = v1 * s;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
		EXPECT_EQ(v2.z, z * s);
		EXPECT_EQ(v2.w, w * s);
	}

	{
		constexpr float s = -2.1f;
		Vec4f v2 = v1 * s;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
		EXPECT_EQ(v2.z, z * s);
		EXPECT_EQ(v2.w, w * s);
	}
}

TEST(Vector4fTest, HadamarProduct)
{
	constexpr float x1 = 0.0f;
	constexpr float y1 = -2.0f;
	constexpr float z1 = 64.87f;
	constexpr float w1 = -3.12f;
	Vec4f v1(x1, y1, z1, w1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	constexpr float w2 = 0.12f;
	Vec4f v2(x2, y2, z2, w2);

	{
		Vec4f v3 = v1 * v2;
		EXPECT_EQ(v3.x, x1 * x2);
		EXPECT_EQ(v3.y, y1 * y2);
		EXPECT_EQ(v3.z, z1 * z2);
		EXPECT_EQ(v3.w, w1 * w2);
	}

	{
		Vec4f v3 = v2 * v1;
		EXPECT_EQ(v3.x, x1 * x2);
		EXPECT_EQ(v3.y, y1 * y2);
		EXPECT_EQ(v3.z, z1 * z2);
		EXPECT_EQ(v3.w, w1 * w2);
	}
}

TEST(Vector4fTest, Magnitude)
{
	{
		float result = magnitude(Vec4f(0.0f));
		EXPECT_EQ(result, 0.0f);
	}

	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		constexpr float z = 0.0f;
		constexpr float w = 71.127f;
		const float expected = std::sqrt(x * x + y * y + z * z + w * w);

		float result = magnitude(Vec4f(x, y, z, w));
		EXPECT_EQ(result, expected);
	}
}

TEST(Vector4fTest, Dot)
{
	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		constexpr float z = 0.0f;
		constexpr float w = 71.127f;

		float result = dot(Vec4f(x, y, z, w), Vec4f(0.0f));
		EXPECT_EQ(result, 0.0f);
	}

	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		constexpr float z = 0.0f;
		constexpr float w = 71.127f;
		Vec4f v(x, y, z, w);

		const float expected = x * x + y * y + z * z + w * w;

		EXPECT_EQ(dot(v, v), expected);
	}

	{
		constexpr float x1 = 1.0f;
		constexpr float y1 = -5.3f;
		constexpr float z1 = 0.0f;
		constexpr float w1 = -3.12f;
		Vec4f v1(x1, y1, z1, w1);

		constexpr float x2 = 7.21f;
		constexpr float y2 = 4.29446f;
		constexpr float z2 = -86.13f;
		constexpr float w2 = 0.12f;
		Vec4f v2(x2, y2, z2, w2);

		const float expected = x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2;

		EXPECT_EQ(dot(v1, v2), expected);
		EXPECT_EQ(dot(v1, v2), dot(v2, v1));
	}
}

TEST(Vector4fTest, Equality)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -5.3f;
	constexpr float z1 = 0.0f;
	constexpr float w1 = -3.12f;
	Vec4f v1(x1, y1, z1, w1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	constexpr float w2 = 0.12f;
	Vec4f v2(x2, y2, z2, w2);

	EXPECT_TRUE(v1 == v1);
	EXPECT_FALSE(v1 == v2);
}

TEST(Vector4fTest, Inequality)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -5.3f;
	constexpr float z1 = 0.0f;
	constexpr float w1 = -3.12f;
	Vec4f v1(x1, y1, z1, w1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	constexpr float w2 = 0.12f;
	Vec4f v2(x2, y2, z2, w2);

	EXPECT_FALSE(v1 != v1);
	EXPECT_TRUE(v1 != v2);
}