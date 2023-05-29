#include <gtest/gtest.h>

#include <cmath>

#include "core/maths/public/vec3f.h"
#include "core/maths/public/vector.h"

using namespace PrismaEngine;

TEST(Vector3fTest, ScalarInitialization) {
	{
		constexpr float s = 0.0f;
		Vec3f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
		EXPECT_EQ(v.z, s);
	}

	{
		constexpr float s = 5.0f;
		Vec3f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
		EXPECT_EQ(v.z, s);
	}

	{
		constexpr float s = -2.0f;
		Vec3f v(s);

		EXPECT_EQ(v.x, s);
		EXPECT_EQ(v.y, s);
		EXPECT_EQ(v.z, s);
	}
}

TEST(Vector3fTest, ClassicInitialization)
{
	constexpr float x = 1.0f;
	constexpr float y = -5.3f;
	constexpr float z = 0.0f;
	Vec3f v(x, y, z);

	EXPECT_EQ(v.x, x);
	EXPECT_EQ(v.y, y);
	EXPECT_EQ(v.z, z);
}

TEST(Vector3fTest, Vec3Initialization)
{
	Vec3f v1(-2.0f, 4.0f, 7.0f);
	Vec3f v2(v1);

	EXPECT_EQ(v1.x, v2.x);
	EXPECT_EQ(v1.y, v2.y);
	EXPECT_EQ(v1.z, v2.z);
}

TEST(Vector3fTest, Add)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -2.0f;
	constexpr float z1 = 64.87f;
	Vec3f v1(x1, y1, z1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	Vec3f v2(x2, y2, z2);

	{
		Vec3f v3 = v1 + v2;
		EXPECT_EQ(v3.x, x1 + x2);
		EXPECT_EQ(v3.y, y1 + y2);
		EXPECT_EQ(v3.z, z1 + z2);
	}

	{
		Vec3f v3 = v2 + v1;
		EXPECT_EQ(v3.x, x1 + x2);
		EXPECT_EQ(v3.y, y1 + y2);
		EXPECT_EQ(v3.z, z1 + z2);
	}
}

TEST(Vector3fTest, Subtract)
{
	constexpr float x1 = 0.0f;
	constexpr float y1 = -2.0f;
	constexpr float z1 = 64.87f;
	Vec3f v1(x1, y1, z1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	Vec3f v2(x2, y2, z2);

	EXPECT_EQ(v1.x - v2.x, x1 - x2);
	EXPECT_EQ(v1.y - v2.y, y1 - y2);
	EXPECT_EQ(v1.z - v2.z, z1 - z2);

	EXPECT_EQ(v2.x - v1.x, x2 - x1);
	EXPECT_EQ(v2.y - v1.y, y2 - y1);
	EXPECT_EQ(v2.z - v1.z, z2 - z1);
}

TEST(Vector3fTest, ScalarMultiplication)
{
	constexpr float x = 1.0f;
	constexpr float y = -5.3f;
	constexpr float z = 0.0f;
	Vec3f v1(x, y, z);

	{
		Vec3f v2 = v1 * 0.0f;
		EXPECT_EQ(v2.x, 0.0f);
		EXPECT_EQ(v2.y, 0.0f);
		EXPECT_EQ(v2.z, 0.0f);
	}

	{
		constexpr float s = 23.45f;
		Vec3f v2 = v1 * s;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
		EXPECT_EQ(v2.z, z * s);
	}

	{
		constexpr float s = -2.1f;
		Vec3f v2 = v1 * s;
		EXPECT_EQ(v2.x, x * s);
		EXPECT_EQ(v2.y, y * s);
		EXPECT_EQ(v2.z, z * s);
	}
}

TEST(Vector3fTest, HadamarProduct)
{
	constexpr float x1 = 0.0f;
	constexpr float y1 = -2.0f;
	constexpr float z1 = 64.87f;
	Vec3f v1(x1, y1, z1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	Vec3f v2(x2, y2, z2);

	{
		Vec3f v3 = v1 * v2;
		EXPECT_EQ(v3.x, x1 * x2);
		EXPECT_EQ(v3.y, y1 * y2);
		EXPECT_EQ(v3.z, z1 * z2);
	}

	{
		Vec3f v3 = v2 * v1;
		EXPECT_EQ(v3.x, x1 * x2);
		EXPECT_EQ(v3.y, y1 * y2);
		EXPECT_EQ(v3.z, z1 * z2);
	}
}

TEST(Vector3fTest, Magnitude)
{
	{
		float result = magnitude(Vec3f(0.0f));
		EXPECT_EQ(result, 0.0f);
	}

	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		constexpr float z = 0.0f;
		const float expected = std::sqrt(x * x + y * y + z * z);

		float result = magnitude(Vec3f(x, y, z));
		EXPECT_EQ(result, expected);
	}
}

TEST(Vector3fTest, Dot)
{
	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		constexpr float z = 0.0f;

		float result = dot(Vec3f(x, y, z), Vec3f(0.0f));
		EXPECT_EQ(result, 0.0f);
	}

	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		constexpr float z = 0.0f;
		Vec3f v(x, y, z);

		const float expected = x * x + y * y + z * z;

		EXPECT_EQ(dot(v, v), expected);
	}

	{
		constexpr float x1 = 1.0f;
		constexpr float y1 = -5.3f;
		constexpr float z1 = 0.0f;
		Vec3f v1(x1, y1, z1);

		constexpr float x2 = 7.21f;
		constexpr float y2 = 4.29446f;
		constexpr float z2 = -86.13f;
		Vec3f v2(x2, y2, z2);

		const float expected = x1 * x2 + y1 * y2 + z1 * z2;

		EXPECT_EQ(dot(v1, v2), expected);
		EXPECT_EQ(dot(v1, v2), dot(v2, v1));
	}
}

TEST(Vector3fTest, Cross)
{
	{
		constexpr float x = 1.0f;
		constexpr float y = -5.3f;
		constexpr float z = 0.0f;

		Vec3f result = cross(Vec3f(x, y, z), Vec3f(0.0f));
		EXPECT_EQ(result.x, 0.0f);
		EXPECT_EQ(result.y, 0.0f);
		EXPECT_EQ(result.z, 0.0f);
	}

	{
		constexpr float x1 = 1.0f;
		constexpr float y1 = -5.3f;
		constexpr float z1 = 0.0f;
		Vec3f v1(x1, y1, z1);

		constexpr float x2 = 7.21f;
		constexpr float y2 = 4.29446f;
		constexpr float z2 = -86.13f;
		Vec3f v2(x2, y2, z2);

		constexpr float xExpect = y1 * z2 - z1 * y2;
		constexpr float yExpect = z1 * x2 - x1 * z2;
		constexpr float zExpect = x1 * y2 - y1 * x2;

		{
			Vec3f v3 = cross(v1, v2);
			EXPECT_EQ(v3.x, xExpect);
			EXPECT_EQ(v3.y, yExpect);
			EXPECT_EQ(v3.z, zExpect);
		}

		{
			Vec3f v3 = cross(v2, v1);
			EXPECT_EQ(v3.x, -xExpect);
			EXPECT_EQ(v3.y, -yExpect);
			EXPECT_EQ(v3.z, -zExpect);
		}
	}
}

TEST(Vector3fTest, Equality)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -5.3f;
	constexpr float z1 = 0.0f;
	Vec3f v1(x1, y1, z1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	Vec3f v2(x2, y2, z2);

	EXPECT_TRUE(v1 == v1);
	EXPECT_FALSE(v1 == v2);
}

TEST(Vector3fTest, Inequality)
{
	constexpr float x1 = 1.0f;
	constexpr float y1 = -5.3f;
	constexpr float z1 = 0.0f;
	Vec3f v1(x1, y1, z1);

	constexpr float x2 = 7.21f;
	constexpr float y2 = 4.29446f;
	constexpr float z2 = -86.13f;
	Vec3f v2(x2, y2, z2);

	EXPECT_FALSE(v1 != v1);
	EXPECT_TRUE(v1 != v2);
}