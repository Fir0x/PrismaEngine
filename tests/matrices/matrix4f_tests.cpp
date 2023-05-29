#include <gtest/gtest.h>

#include "core/maths/public/mat4f.h"
#include "core/maths/public/matrix.h"
#include "core/maths/public/vec4f.h"

using namespace PrismaEngine;

#define EPSILON 1e-8

TEST(Matrix4fTest, ScalarInitialization)
{
	{
		constexpr float val = 1.0f;
		Mat4f m(val);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				EXPECT_EQ(m[i][j], i == j ? val : 0.0f);
		}
	}

	{
		constexpr float val = 2.36f;
		Mat4f m(val);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				EXPECT_EQ(m[i][j], i == j ? val : 0.0f);
		}
	}


	{
		constexpr float val = -2.36f;
		Mat4f m(val);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				EXPECT_EQ(m[i][j], i == j ? val : 0.0f);
		}
	}
}

TEST(Matrix4fTest, FullInitialization)
{
	constexpr float x0 = 0.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float x3 = 98.32f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float y3 = 13.56f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;
	constexpr float z3 = 12.02f;
	constexpr float w0 = 23.65f;
	constexpr float w1 = -9.80f;
	constexpr float w2 = 0.036f;
	constexpr float w3 = -1.32f;

	Mat4f m(x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3);

	EXPECT_EQ(m[0][0], x0);
	EXPECT_EQ(m[1][0], x1);
	EXPECT_EQ(m[2][0], x2);
	EXPECT_EQ(m[3][0], x3);

	EXPECT_EQ(m[0][1], y0);
	EXPECT_EQ(m[1][1], y1);
	EXPECT_EQ(m[2][1], y2);
	EXPECT_EQ(m[3][1], y3);

	EXPECT_EQ(m[0][2], z0);
	EXPECT_EQ(m[1][2], z1);
	EXPECT_EQ(m[2][2], z2);
	EXPECT_EQ(m[3][2], z3);

	EXPECT_EQ(m[0][3], w0);
	EXPECT_EQ(m[1][3], w1);
	EXPECT_EQ(m[2][3], w2);
	EXPECT_EQ(m[3][3], w3);
}

TEST(Matrix4fTest, Vector4Initialization)
{
	constexpr float x0 = 0.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float x3 = 98.32f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float y3 = 13.56f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;
	constexpr float z3 = 12.02f;
	constexpr float w0 = 23.65f;
	constexpr float w1 = -9.80f;
	constexpr float w2 = 0.036f;
	constexpr float w3 = -1.32f;

	Vec4f x(x0, x1, x2, x3);
	Vec4f y(y0, y1, y2, y3);
	Vec4f z(z0, z1, z2, z3);
	Vec4f w(w0, w1, w2, w3);

	Mat4f m(x, y, z, w);

	EXPECT_EQ(m[0][0], x0);
	EXPECT_EQ(m[0][1], x1);
	EXPECT_EQ(m[0][2], x2);
	EXPECT_EQ(m[0][3], x3);

	EXPECT_EQ(m[1][0], y0);
	EXPECT_EQ(m[1][1], y1);
	EXPECT_EQ(m[1][2], y2);
	EXPECT_EQ(m[1][3], y3);

	EXPECT_EQ(m[2][0], z0);
	EXPECT_EQ(m[2][1], z1);
	EXPECT_EQ(m[2][2], z2);
	EXPECT_EQ(m[2][3], z3);

	EXPECT_EQ(m[3][0], w0);
	EXPECT_EQ(m[3][1], w1);
	EXPECT_EQ(m[3][2], w2);
	EXPECT_EQ(m[3][3], w3);
}

TEST(Matrix4fTest, ReferenceInitialization)
{
	constexpr float x0 = 0.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float x3 = 98.32f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float y3 = 13.56f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;
	constexpr float z3 = 12.02f;
	constexpr float w0 = 23.65f;
	constexpr float w1 = -9.80f;
	constexpr float w2 = 0.036f;
	constexpr float w3 = -1.32f;

	Vec4f x(x0, x1, x2, x3);
	Vec4f y(y0, y1, y2, y3);
	Vec4f z(z0, z1, z2, z3);
	Vec4f w(w0, w1, w2, w3);

	Mat4f m1(x, y, z, w);
	Mat4f m2(m1);

	EXPECT_EQ(m2[0][0], x0);
	EXPECT_EQ(m2[0][1], x1);
	EXPECT_EQ(m2[0][2], x2);
	EXPECT_EQ(m2[0][3], x3);

	EXPECT_EQ(m2[1][0], y0);
	EXPECT_EQ(m2[1][1], y1);
	EXPECT_EQ(m2[1][2], y2);
	EXPECT_EQ(m2[1][3], y3);

	EXPECT_EQ(m2[2][0], z0);
	EXPECT_EQ(m2[2][1], z1);
	EXPECT_EQ(m2[2][2], z2);
	EXPECT_EQ(m2[2][3], z3);

	EXPECT_EQ(m2[3][0], w0);
	EXPECT_EQ(m2[3][1], w1);
	EXPECT_EQ(m2[3][2], w2);
	EXPECT_EQ(m2[3][3], w3);
}

TEST(Matrix4fTest, Add)
{
	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float x13 = 98.32f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float y13 = 13.56f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;
	constexpr float z13 = 12.02f;
	constexpr float w10 = 23.65f;
	constexpr float w11 = -9.80f;
	constexpr float w12 = 0.036f;
	constexpr float w13 = -1.32f;

	Vec4f x1(x10, x11, x12, x13);
	Vec4f y1(y10, y11, y12, y13);
	Vec4f z1(z10, z11, z12, z13);
	Vec4f w1(w10, w11, w12, w13);

	Mat4f m1(x1, y1, z1, w1);

	constexpr float x20 = 64.52f;
	constexpr float x21 = -6.32f;
	constexpr float x22 = -2.64f;
	constexpr float x23 = 120.02f;
	constexpr float y20 = 4.6f;
	constexpr float y21 = 3.64f;
	constexpr float y22 = 12.345f;
	constexpr float y23 = 1.30f;
	constexpr float z20 = -893.15f;
	constexpr float z21 = 2.34f;
	constexpr float z22 = -72.2f;
	constexpr float z23 = -6.12f;
	constexpr float w20 = 2.354f;
	constexpr float w21 = 12.36f;
	constexpr float w22 = -5.31f;
	constexpr float w23 = -0.2156f;

	Vec4f x2(x20, x21, x22, x23);
	Vec4f y2(y20, y21, y22, y23);
	Vec4f z2(z20, z21, z22, z23);
	Vec4f w2(w20, w21, w22, w23);

	Mat4f m2(x2, y2, z2, w2);

	{
		Mat4f m3 = m1 + m2;

		EXPECT_EQ(m3[0][0], x10 + x20);
		EXPECT_EQ(m3[0][1], x11 + x21);
		EXPECT_EQ(m3[0][2], x12 + x22);
		EXPECT_EQ(m3[0][3], x13 + x23);

		EXPECT_EQ(m3[1][0], y10 + y20);
		EXPECT_EQ(m3[1][1], y11 + y21);
		EXPECT_EQ(m3[1][2], y12 + y22);
		EXPECT_EQ(m3[1][3], y13 + y23);

		EXPECT_EQ(m3[2][0], z10 + z20);
		EXPECT_EQ(m3[2][1], z11 + z21);
		EXPECT_EQ(m3[2][2], z12 + z22);
		EXPECT_EQ(m3[2][3], z13 + z23);

		EXPECT_EQ(m3[3][0], w10 + w20);
		EXPECT_EQ(m3[3][1], w11 + w21);
		EXPECT_EQ(m3[3][2], w12 + w22);
		EXPECT_EQ(m3[3][3], w13 + w23);
	}

	{
		Mat4f m3 = m2 + m1;

		EXPECT_EQ(m3[0][0], x10 + x20);
		EXPECT_EQ(m3[0][1], x11 + x21);
		EXPECT_EQ(m3[0][2], x12 + x22);
		EXPECT_EQ(m3[0][3], x13 + x23);

		EXPECT_EQ(m3[1][0], y10 + y20);
		EXPECT_EQ(m3[1][1], y11 + y21);
		EXPECT_EQ(m3[1][2], y12 + y22);
		EXPECT_EQ(m3[1][3], y13 + y23);

		EXPECT_EQ(m3[2][0], z10 + z20);
		EXPECT_EQ(m3[2][1], z11 + z21);
		EXPECT_EQ(m3[2][2], z12 + z22);
		EXPECT_EQ(m3[2][3], z13 + z23);

		EXPECT_EQ(m3[3][0], w10 + w20);
		EXPECT_EQ(m3[3][1], w11 + w21);
		EXPECT_EQ(m3[3][2], w12 + w22);
		EXPECT_EQ(m3[3][3], w13 + w23);
	}
}

TEST(Matrix4fTest, Subtract)
{
	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float x13 = 98.32f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float y13 = 13.56f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;
	constexpr float z13 = 12.02f;
	constexpr float w10 = 23.65f;
	constexpr float w11 = -9.80f;
	constexpr float w12 = 0.036f;
	constexpr float w13 = -1.32f;

	Vec4f x1(x10, x11, x12, x13);
	Vec4f y1(y10, y11, y12, y13);
	Vec4f z1(z10, z11, z12, z13);
	Vec4f w1(w10, w11, w12, w13);

	Mat4f m1(x1, y1, z1, w1);

	constexpr float x20 = 64.52f;
	constexpr float x21 = -6.32f;
	constexpr float x22 = -2.64f;
	constexpr float x23 = 120.02f;
	constexpr float y20 = 4.6f;
	constexpr float y21 = 3.64f;
	constexpr float y22 = 12.345f;
	constexpr float y23 = 1.30f;
	constexpr float z20 = -893.15f;
	constexpr float z21 = 2.34f;
	constexpr float z22 = -72.2f;
	constexpr float z23 = -6.12f;
	constexpr float w20 = 2.354f;
	constexpr float w21 = 12.36f;
	constexpr float w22 = -5.31f;
	constexpr float w23 = -0.2156f;

	Vec4f x2(x20, x21, x22, x23);
	Vec4f y2(y20, y21, y22, y23);
	Vec4f z2(z20, z21, z22, z23);
	Vec4f w2(w20, w21, w22, w23);

	Mat4f m2(x2, y2, z2, w2);

	{
		Mat4f m3 = m1 - m2;

		EXPECT_EQ(m3[0][0], x10 - x20);
		EXPECT_EQ(m3[0][1], x11 - x21);
		EXPECT_EQ(m3[0][2], x12 - x22);
		EXPECT_EQ(m3[0][3], x13 - x23);

		EXPECT_EQ(m3[1][0], y10 - y20);
		EXPECT_EQ(m3[1][1], y11 - y21);
		EXPECT_EQ(m3[1][2], y12 - y22);
		EXPECT_EQ(m3[1][3], y13 - y23);

		EXPECT_EQ(m3[2][0], z10 - z20);
		EXPECT_EQ(m3[2][1], z11 - z21);
		EXPECT_EQ(m3[2][2], z12 - z22);
		EXPECT_EQ(m3[2][3], z13 - z23);

		EXPECT_EQ(m3[3][0], w10 - w20);
		EXPECT_EQ(m3[3][1], w11 - w21);
		EXPECT_EQ(m3[3][2], w12 - w22);
		EXPECT_EQ(m3[3][3], w13 - w23);
	}

	{
		Mat4f m3 = m2 - m1;

		EXPECT_EQ(m3[0][0], x20 - x10);
		EXPECT_EQ(m3[0][1], x21 - x11);
		EXPECT_EQ(m3[0][2], x22 - x12);
		EXPECT_EQ(m3[0][3], x23 - x13);

		EXPECT_EQ(m3[1][0], y20 - y10);
		EXPECT_EQ(m3[1][1], y21 - y11);
		EXPECT_EQ(m3[1][2], y22 - y12);
		EXPECT_EQ(m3[1][3], y23 - y13);

		EXPECT_EQ(m3[2][0], z20 - z10);
		EXPECT_EQ(m3[2][1], z21 - z11);
		EXPECT_EQ(m3[2][2], z22 - z12);
		EXPECT_EQ(m3[2][3], z23 - z13);

		EXPECT_EQ(m3[3][0], w20 - w10);
		EXPECT_EQ(m3[3][1], w21 - w11);
		EXPECT_EQ(m3[3][2], w22 - w12);
		EXPECT_EQ(m3[3][3], w23 - w13);
	}
}

TEST(Matrix4fTest, Product)
{

	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float x13 = 98.32f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float y13 = 13.56f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;
	constexpr float z13 = 12.02f;
	constexpr float w10 = 23.65f;
	constexpr float w11 = -9.80f;
	constexpr float w12 = 0.036f;
	constexpr float w13 = -1.32f;

	Vec4f x1(x10, x11, x12, x13);
	Vec4f y1(y10, y11, y12, y13);
	Vec4f z1(z10, z11, z12, z13);
	Vec4f w1(w10, w11, w12, w13);

	Mat4f m1(x1, y1, z1, w1);

	{
		Vec4f x2(1.0f, 0.0f, 0.0f, 0.0f);
		Vec4f y2(0.0f, 1.0f, 0.0f, 0.0f);
		Vec4f z2(0.0f, 0.0f, 1.0f, 0.0f);
		Vec4f w2(0.0f, 0.0f, 0.0f, 1.0f);

		Mat4f identity(x2, y2, z2, w2);

		{
			Mat4f m3 = m1 * identity;
			EXPECT_EQ(m3[0][0], x10);
			EXPECT_EQ(m3[0][1], x11);
			EXPECT_EQ(m3[0][2], x12);
			EXPECT_EQ(m3[0][3], x13);

			EXPECT_EQ(m3[1][0], y10);
			EXPECT_EQ(m3[1][1], y11);
			EXPECT_EQ(m3[1][2], y12);
			EXPECT_EQ(m3[1][3], y13);

			EXPECT_EQ(m3[2][0], z10);
			EXPECT_EQ(m3[2][1], z11);
			EXPECT_EQ(m3[2][2], z12);
			EXPECT_EQ(m3[2][3], z13);

			EXPECT_EQ(m3[3][0], w10);
			EXPECT_EQ(m3[3][1], w11);
			EXPECT_EQ(m3[3][2], w12);
			EXPECT_EQ(m3[3][3], w13);
		}

		{
			Mat4f m3 = identity * m1;
			EXPECT_EQ(m3[0][0], x10);
			EXPECT_EQ(m3[0][1], x11);
			EXPECT_EQ(m3[0][2], x12);
			EXPECT_EQ(m3[0][3], x13);

			EXPECT_EQ(m3[1][0], y10);
			EXPECT_EQ(m3[1][1], y11);
			EXPECT_EQ(m3[1][2], y12);
			EXPECT_EQ(m3[1][3], y13);

			EXPECT_EQ(m3[2][0], z10);
			EXPECT_EQ(m3[2][1], z11);
			EXPECT_EQ(m3[2][2], z12);
			EXPECT_EQ(m3[2][3], z13);

			EXPECT_EQ(m3[3][0], w10);
			EXPECT_EQ(m3[3][1], w11);
			EXPECT_EQ(m3[3][2], w12);
			EXPECT_EQ(m3[3][3], w13);
		}
	}

	{
		constexpr float x20 = 64.52f;
		constexpr float x21 = -6.32f;
		constexpr float x22 = -2.64f;
		constexpr float x23 = 120.02f;
		constexpr float y20 = 4.6f;
		constexpr float y21 = 3.64f;
		constexpr float y22 = 12.345f;
		constexpr float y23 = 1.30f;
		constexpr float z20 = -893.15f;
		constexpr float z21 = 2.34f;
		constexpr float z22 = -72.2f;
		constexpr float z23 = -6.12f;
		constexpr float w20 = 2.354f;
		constexpr float w21 = 12.36f;
		constexpr float w22 = -5.31f;
		constexpr float w23 = -0.2156f;

		Vec4f x2(x20, x21, x22, x23);
		Vec4f y2(y20, y21, y22, y23);
		Vec4f z2(z20, z21, z22, z23);
		Vec4f w2(w20, w21, w22, w23);

		Mat4f m2(x2, y2, z2, w2);

		{
			Mat4f m3 = m1 * m2;
			const float x30 = x10 * x20 + y10 * x21 + z10 * x22 + w10 * x23;
			const float x31 = x11 * x20 + y11 * x21 + z11 * x22 + w11 * x23;
			const float x32 = x12 * x20 + y12 * x21 + z12 * x22 + w12 * x23;
			const float x33 = x13 * x20 + y13 * x21 + z13 * x22 + w13 * x23;
			const float y30 = x10 * y20 + y10 * y21 + z10 * y22 + w10 * y23;
			const float y31 = x11 * y20 + y11 * y21 + z11 * y22 + w11 * y23;
			const float y32 = x12 * y20 + y12 * y21 + z12 * y22 + w12 * y23;
			const float y33 = x13 * y20 + y13 * y21 + z13 * y22 + w13 * y23;
			const float z30 = x10 * z20 + y10 * z21 + z10 * z22 + w10 * z23;
			const float z31 = x11 * z20 + y11 * z21 + z11 * z22 + w11 * z23;
			const float z32 = x12 * z20 + y12 * z21 + z12 * z22 + w12 * z23;
			const float z33 = x13 * z20 + y13 * z21 + z13 * z22 + w13 * z23;
			const float w30 = x10 * w20 + y10 * w21 + z10 * w22 + w10 * w23;
			const float w31 = x11 * w20 + y11 * w21 + z11 * w22 + w11 * w23;
			const float w32 = x12 * w20 + y12 * w21 + z12 * w22 + w12 * w23;
			const float w33 = x13 * w20 + y13 * w21 + z13 * w22 + w13 * w23;

			EXPECT_EQ(m3[0][0], x30);
			EXPECT_EQ(m3[0][1], x31);
			EXPECT_EQ(m3[0][2], x32);
			EXPECT_EQ(m3[0][3], x33);

			EXPECT_EQ(m3[1][0], y30);
			EXPECT_EQ(m3[1][1], y31);
			EXPECT_EQ(m3[1][2], y32);
			EXPECT_EQ(m3[1][3], y33);

			EXPECT_EQ(m3[2][0], z30);
			EXPECT_EQ(m3[2][1], z31);
			EXPECT_EQ(m3[2][2], z32);
			EXPECT_EQ(m3[2][3], z33);

			EXPECT_EQ(m3[3][0], w30);
			EXPECT_EQ(m3[3][1], w31);
			EXPECT_EQ(m3[3][2], w32);
			EXPECT_EQ(m3[3][3], w33);
		}


		{
			Mat4f m3 = m2 * m1;
			const float x30 = x20 * x10 + y20 * x11 + z20 * x12 + w20 * x13;
			const float x31 = x21 * x10 + y21 * x11 + z21 * x12 + w21 * x13;
			const float x32 = x22 * x10 + y22 * x11 + z22 * x12 + w22 * x13;
			const float x33 = x23 * x10 + y23 * x11 + z23 * x12 + w23 * x13;
			const float y30 = x20 * y10 + y20 * y11 + z20 * y12 + w20 * y13;
			const float y31 = x21 * y10 + y21 * y11 + z21 * y12 + w21 * y13;
			const float y32 = x22 * y10 + y22 * y11 + z22 * y12 + w22 * y13;
			const float y33 = x23 * y10 + y23 * y11 + z23 * y12 + w23 * y13;
			const float z30 = x20 * z10 + y20 * z11 + z20 * z12 + w20 * z13;
			const float z31 = x21 * z10 + y21 * z11 + z21 * z12 + w21 * z13;
			const float z32 = x22 * z10 + y22 * z11 + z22 * z12 + w22 * z13;
			const float z33 = x23 * z10 + y23 * z11 + z23 * z12 + w23 * z13;
			const float w30 = x20 * w10 + y20 * w11 + z20 * w12 + w20 * w13;
			const float w31 = x21 * w10 + y21 * w11 + z21 * w12 + w21 * w13;
			const float w32 = x22 * w10 + y22 * w11 + z22 * w12 + w22 * w13;
			const float w33 = x23 * w10 + y23 * w11 + z23 * w12 + w23 * w13;

			EXPECT_EQ(m3[0][0], x30);
			EXPECT_EQ(m3[0][1], x31);
			EXPECT_EQ(m3[0][2], x32);
			EXPECT_EQ(m3[0][3], x33);

			EXPECT_EQ(m3[1][0], y30);
			EXPECT_EQ(m3[1][1], y31);
			EXPECT_EQ(m3[1][2], y32);
			EXPECT_EQ(m3[1][3], y33);

			EXPECT_EQ(m3[2][0], z30);
			EXPECT_EQ(m3[2][1], z31);
			EXPECT_EQ(m3[2][2], z32);
			EXPECT_EQ(m3[2][3], z33);

			EXPECT_EQ(m3[3][0], w30);
			EXPECT_EQ(m3[3][1], w31);
			EXPECT_EQ(m3[3][2], w32);
			EXPECT_EQ(m3[3][3], w33);
		}
	}
}

TEST(Matrix4fTest, Transpose)
{
	{
		Vec4f x(1.0f, 0.0f, 0.0f, 0.0f);
		Vec4f y(0.0f, 1.0f, 0.0f, 0.0f);
		Vec4f z(0.0f, 0.0f, 1.0f, 0.0f);
		Vec4f w(0.0f, 0.0f, 0.0f, 1.0f);

		Mat4f m(x, y, z, w);
		Mat4f mTransposed = transpose(m);

		EXPECT_EQ(mTransposed[0][0], 1.0f);
		EXPECT_EQ(mTransposed[0][1], 0.0f);
		EXPECT_EQ(mTransposed[0][2], 0.0f);
		EXPECT_EQ(mTransposed[0][3], 0.0f);

		EXPECT_EQ(mTransposed[1][0], 0.0f);
		EXPECT_EQ(mTransposed[1][1], 1.0f);
		EXPECT_EQ(mTransposed[1][2], 0.0f);
		EXPECT_EQ(mTransposed[1][3], 0.0f);

		EXPECT_EQ(mTransposed[2][0], 0.0f);
		EXPECT_EQ(mTransposed[2][1], 0.0f);
		EXPECT_EQ(mTransposed[2][2], 1.0f);
		EXPECT_EQ(mTransposed[2][3], 0.0f);

		EXPECT_EQ(mTransposed[3][0], 0.0f);
		EXPECT_EQ(mTransposed[3][1], 0.0f);
		EXPECT_EQ(mTransposed[3][2], 0.0f);
		EXPECT_EQ(mTransposed[3][3], 1.0f);
	}

	{
		constexpr float x0 = 0.0f;
		constexpr float x1 = 2.54f;
		constexpr float x2 = -3.6f;
		constexpr float x3 = 98.32f;
		constexpr float y0 = -23.1f;
		constexpr float y1 = -4.354f;
		constexpr float y2 = -26.41f;
		constexpr float y3 = 13.56f;
		constexpr float z0 = 285.15f;
		constexpr float z1 = -87.7f;
		constexpr float z2 = 354.5f;
		constexpr float z3 = 12.02f;
		constexpr float w0 = 23.65f;
		constexpr float w1 = -9.80f;
		constexpr float w2 = 0.036f;
		constexpr float w3 = -1.32f;

		Vec4f x(x0, x1, x2, x3);
		Vec4f y(y0, y1, y2, y3);
		Vec4f z(z0, z1, z2, z3);
		Vec4f w(w0, w1, w2, w3);

		Mat4f m(x, y, z, w);
		Mat4f mTransposed = transpose(m);

		EXPECT_EQ(mTransposed[0][0], x0);
		EXPECT_EQ(mTransposed[0][1], y0);
		EXPECT_EQ(mTransposed[0][2], z0);
		EXPECT_EQ(mTransposed[0][3], w0);

		EXPECT_EQ(mTransposed[1][0], x1);
		EXPECT_EQ(mTransposed[1][1], y1);
		EXPECT_EQ(mTransposed[1][2], z1);
		EXPECT_EQ(mTransposed[1][3], w1);

		EXPECT_EQ(mTransposed[2][0], x2);
		EXPECT_EQ(mTransposed[2][1], y2);
		EXPECT_EQ(mTransposed[2][2], z2);
		EXPECT_EQ(mTransposed[2][3], w2);

		EXPECT_EQ(mTransposed[3][0], x3);
		EXPECT_EQ(mTransposed[3][1], y3);
		EXPECT_EQ(mTransposed[3][2], z3);
		EXPECT_EQ(mTransposed[3][3], w3);
	}
}

TEST(Matrix4fTest, Determinant)
{
	constexpr float x0 = 1.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float x3 = 98.32f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float y3 = 13.56f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;
	constexpr float z3 = 12.02f;
	constexpr float w0 = 23.65f;
	constexpr float w1 = -9.80f;
	constexpr float w2 = 0.036f;
	constexpr float w3 = -1.32f;

	Vec4f x(x0, x1, x2, x3);
	Vec4f y(y0, y1, y2, y3);
	Vec4f z(z0, z1, z2, z3);
	Vec4f w(w0, w1, w2, w3);

	Mat4f m(x, y, z, w);

	float det = determinant(m);

	constexpr float subSubFactor01 = z0 * w1 - z1 * w0;
	constexpr float subSubFactor12 = z1 * w2 - z2 * w1;
	constexpr float subSubFactor23 = z2 * w3 - z3 * w2;
	constexpr float subSubFactor02 = z0 * w2 - z2 * w0;
	constexpr float subSubFactor13 = z1 * w3 - z3 * w1;
	constexpr float subSubFactor03 = z0 * w3 - z3 * w0;

	constexpr float subFactor0 = y1 * subSubFactor23 - y2 * subSubFactor13 + y3 * subSubFactor12;
	constexpr float subFactor1 = y0 * subSubFactor23 - y2 * subSubFactor03 + y3 * subSubFactor02;
	constexpr float subFactor2 = y0 * subSubFactor13 - y1 * subSubFactor03 + y3 * subSubFactor01;
	constexpr float subFactor3 = y0 * subSubFactor12 - y1 * subSubFactor02 + y2 * subSubFactor01;

	constexpr float detRef = x0 * subFactor0 - x1 * subFactor1 + x2 * subFactor2 - x3 * subFactor3;

	EXPECT_EQ(det, detRef);
}

TEST(Matrix4fTest, Inverse)
{
	constexpr float x0 = 1.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float x3 = 98.32f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float y3 = 13.56f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;
	constexpr float z3 = 12.02f;
	constexpr float w0 = 23.65f;
	constexpr float w1 = -9.80f;
	constexpr float w2 = 0.036f;
	constexpr float w3 = -1.32f;

	Vec4f x(x0, x1, x2, x3);
	Vec4f y(y0, y1, y2, y3);
	Vec4f z(z0, z1, z2, z3);
	Vec4f w(w0, w1, w2, w3);

	Mat4f m(x, y, z, w);

	Mat4f mInverted = inverse(m);

	// Naming: coef<column><coef id>
	constexpr float coef01 = y2 * z3 - z2 * y3;
	constexpr float coef02 = y2 * w3 - w2 * y3;
	constexpr float coef03 = z2 * w3 - w2 * z3;
	constexpr float coef04 = x2 * z3 - z2 * x3;
	constexpr float coef05 = x2 * w3 - w2 * x3;
	constexpr float coef06 = x2 * y3 - y2 * x3;

	constexpr float coef21 = y1 * z3 - z1 * y3;
	constexpr float coef22 = y1 * w3 - w1 * y3;
	constexpr float coef23 = z1 * w3 - w1 * z3;
	constexpr float coef24 = x1 * z3 - z1 * x3;
	constexpr float coef25 = x1 * w3 - w1 * x3;
	constexpr float coef26 = x1 * y3 - y1 * x3;

	constexpr float coef31 = y1 * z2 - z1 * y2;
	constexpr float coef32 = y1 * w2 - w1 * y2;
	constexpr float coef33 = z1 * w2 - w1 * z2;
	constexpr float coef34 = x1 * z2 - z1 * x2;
	constexpr float coef35 = x1 * w2 - w1 * x2;
	constexpr float coef36 = x1 * y2 - y1 * x2;

	constexpr float adjugateX0 = +(y1 * coef03 - z1 * coef02 + w1 * coef01);
	constexpr float adjugateX1 = -(x1 * coef03 - z1 * coef05 + w1 * coef04);
	constexpr float adjugateX2 = +(x1 * coef02 - y1 * coef05 + w1 * coef06);
	constexpr float adjugateX3 = -(x1 * coef01 - y1 * coef04 + z1 * coef06);

	constexpr float adjugateY0 = -(y0 * coef03 - z0 * coef02 + w0 * coef01);
	constexpr float adjugateY1 = +(x0 * coef03 - z0 * coef05 + w0 * coef04);
	constexpr float adjugateY2 = -(x0 * coef02 - y0 * coef05 + w0 * coef06);
	constexpr float adjugateY3 = +(x0 * coef01 - y0 * coef04 + z0 * coef06);

	constexpr float adjugateZ0 = +(y0 * coef23 - z0 * coef22 + w0 * coef21);
	constexpr float adjugateZ1 = -(x0 * coef23 - z0 * coef25 + w0 * coef24);
	constexpr float adjugateZ2 = +(x0 * coef22 - y0 * coef25 + w0 * coef26);
	constexpr float adjugateZ3 = -(x0 * coef21 - y0 * coef24 + z0 * coef26);

	constexpr float adjugateW0 = -(y0 * coef33 - z0 * coef32 + w0 * coef31);
	constexpr float adjugateW1 = +(x0 * coef33 - z0 * coef35 + w0 * coef34);
	constexpr float adjugateW2 = -(x0 * coef32 - y0 * coef35 + w0 * coef36);
	constexpr float adjugateW3 = +(x0 * coef31 - y0 * coef34 + z0 * coef36);

	constexpr float determinant = x0 * adjugateX0 + y0 * adjugateX1 + z0 * adjugateX2 + w0 * adjugateX3;
	constexpr float oneOverDeterminant = 1.0f / determinant;

	constexpr float inverseX0 = oneOverDeterminant * adjugateX0;
	constexpr float inverseX1 = oneOverDeterminant * adjugateX1;
	constexpr float inverseX2 = oneOverDeterminant * adjugateX2;
	constexpr float inverseX3 = oneOverDeterminant * adjugateX3;
	constexpr float inverseY0 = oneOverDeterminant * adjugateY0;
	constexpr float inverseY1 = oneOverDeterminant * adjugateY1;
	constexpr float inverseY2 = oneOverDeterminant * adjugateY2;
	constexpr float inverseY3 = oneOverDeterminant * adjugateY3;
	constexpr float inverseZ0 = oneOverDeterminant * adjugateZ0;
	constexpr float inverseZ1 = oneOverDeterminant * adjugateZ1;
	constexpr float inverseZ2 = oneOverDeterminant * adjugateZ2;
	constexpr float inverseZ3 = oneOverDeterminant * adjugateZ3;
	constexpr float inverseW0 = oneOverDeterminant * adjugateW0;
	constexpr float inverseW1 = oneOverDeterminant * adjugateW1;
	constexpr float inverseW2 = oneOverDeterminant * adjugateW2;
	constexpr float inverseW3 = oneOverDeterminant * adjugateW3;

	EXPECT_NEAR(mInverted[0][0], inverseX0, EPSILON);
	EXPECT_NEAR(mInverted[0][1], inverseX1, EPSILON);
	EXPECT_NEAR(mInverted[0][2], inverseX2, EPSILON);
	EXPECT_NEAR(mInverted[0][3], inverseX3, EPSILON);

	EXPECT_NEAR(mInverted[1][0], inverseY0, EPSILON);
	EXPECT_NEAR(mInverted[1][1], inverseY1, EPSILON);
	EXPECT_NEAR(mInverted[1][2], inverseY2, EPSILON);
	EXPECT_NEAR(mInverted[1][3], inverseY3, EPSILON);

	EXPECT_NEAR(mInverted[2][0], inverseZ0, EPSILON);
	EXPECT_NEAR(mInverted[2][1], inverseZ1, EPSILON);
	EXPECT_NEAR(mInverted[2][2], inverseZ2, EPSILON);
	EXPECT_NEAR(mInverted[2][3], inverseZ3, EPSILON);

	EXPECT_NEAR(mInverted[3][0], inverseW0, EPSILON);
	EXPECT_NEAR(mInverted[3][1], inverseW1, EPSILON);
	EXPECT_NEAR(mInverted[3][2], inverseW2, EPSILON);
	EXPECT_NEAR(mInverted[3][3], inverseW3, EPSILON);
}

TEST(Matrix4fTest, RowAccess)
{
	constexpr float x0 = 1.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float x3 = 98.32f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float y3 = 13.56f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;
	constexpr float z3 = 12.02f;
	constexpr float w0 = 23.65f;
	constexpr float w1 = -9.80f;
	constexpr float w2 = 0.036f;
	constexpr float w3 = -1.32f;

	Vec4f x(x0, x1, x2, x3);
	Vec4f y(y0, y1, y2, y3);
	Vec4f z(z0, z1, z2, z3);
	Vec4f w(w0, w1, w2, w3);

	Mat4f m(x, y, z, w);

	Vec4f r0 = row(m, 0);
	EXPECT_EQ(r0[0], x0);
	EXPECT_EQ(r0[1], y0);
	EXPECT_EQ(r0[2], z0);
	EXPECT_EQ(r0[3], w0);

	Vec4f r1 = row(m, 1);
	EXPECT_EQ(r1[0], x1);
	EXPECT_EQ(r1[1], y1);
	EXPECT_EQ(r1[2], z1);
	EXPECT_EQ(r1[3], w1);

	Vec4f r2 = row(m, 2);
	EXPECT_EQ(r2[0], x2);
	EXPECT_EQ(r2[1], y2);
	EXPECT_EQ(r2[2], z2);
	EXPECT_EQ(r2[3], w2);

	Vec4f r3 = row(m, 3);
	EXPECT_EQ(r3[0], x3);
	EXPECT_EQ(r3[1], y3);
	EXPECT_EQ(r3[2], z3);
	EXPECT_EQ(r3[3], w3);
}

TEST(Matrix4fTest, ColumnAccess)
{

	constexpr float x0 = 1.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float x3 = 98.32f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float y3 = 13.56f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;
	constexpr float z3 = 12.02f;
	constexpr float w0 = 23.65f;
	constexpr float w1 = -9.80f;
	constexpr float w2 = 0.036f;
	constexpr float w3 = -1.32f;

	Vec4f x(x0, x1, x2, x3);
	Vec4f y(y0, y1, y2, y3);
	Vec4f z(z0, z1, z2, z3);
	Vec4f w(w0, w1, w2, w3);

	Mat4f m(x, y, z, w);

	Vec4f c0 = column(m, 0);
	EXPECT_EQ(c0[0], x0);
	EXPECT_EQ(c0[1], x1);
	EXPECT_EQ(c0[2], x2);
	EXPECT_EQ(c0[3], x3);

	Vec4f c1 = column(m, 1);
	EXPECT_EQ(c1[0], y0);
	EXPECT_EQ(c1[1], y1);
	EXPECT_EQ(c1[2], y2);
	EXPECT_EQ(c1[3], y3);

	Vec4f c2 = column(m, 2);
	EXPECT_EQ(c2[0], z0);
	EXPECT_EQ(c2[1], z1);
	EXPECT_EQ(c2[2], z2);
	EXPECT_EQ(c2[3], z3);

	Vec4f c3 = column(m, 3);
	EXPECT_EQ(c3[0], w0);
	EXPECT_EQ(c3[1], w1);
	EXPECT_EQ(c3[2], w2);
	EXPECT_EQ(c3[3], w3);
}

TEST(Matrix4fTest, Equality)
{
	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float x13 = 98.32f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float y13 = 13.56f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;
	constexpr float z13 = 12.02f;
	constexpr float w10 = 23.65f;
	constexpr float w11 = -9.80f;
	constexpr float w12 = 0.036f;
	constexpr float w13 = -1.32f;

	Vec4f x1(x10, x11, x12, x13);
	Vec4f y1(y10, y11, y12, y13);
	Vec4f z1(z10, z11, z12, z13);
	Vec4f w1(w10, w11, w12, w13);

	Mat4f m1(x1, y1, z1, w1);

	constexpr float x20 = 64.52f;
	constexpr float x21 = -6.32f;
	constexpr float x22 = -2.64f;
	constexpr float x23 = 120.02f;
	constexpr float y20 = 4.6f;
	constexpr float y21 = 3.64f;
	constexpr float y22 = 12.345f;
	constexpr float y23 = 1.30f;
	constexpr float z20 = -893.15f;
	constexpr float z21 = 2.34f;
	constexpr float z22 = -72.2f;
	constexpr float z23 = -6.12f;
	constexpr float w20 = 2.354f;
	constexpr float w21 = 12.36f;
	constexpr float w22 = -5.31f;
	constexpr float w23 = -0.2156f;

	Vec4f x2(x20, x21, x22, x23);
	Vec4f y2(y20, y21, y22, y23);
	Vec4f z2(z20, z21, z22, z23);
	Vec4f w2(w20, w21, w22, w23);

	Mat4f m2(x2, y2, z2, w2);

	EXPECT_TRUE(m1 == m1);
	EXPECT_FALSE(m1 == m2);
}

TEST(Matrix4fTest, Inequality)
{
	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float x13 = 98.32f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float y13 = 13.56f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;
	constexpr float z13 = 12.02f;
	constexpr float w10 = 23.65f;
	constexpr float w11 = -9.80f;
	constexpr float w12 = 0.036f;
	constexpr float w13 = -1.32f;

	Vec4f x1(x10, x11, x12, x13);
	Vec4f y1(y10, y11, y12, y13);
	Vec4f z1(z10, z11, z12, z13);
	Vec4f w1(w10, w11, w12, w13);

	Mat4f m1(x1, y1, z1, w1);

	constexpr float x20 = 64.52f;
	constexpr float x21 = -6.32f;
	constexpr float x22 = -2.64f;
	constexpr float x23 = 120.02f;
	constexpr float y20 = 4.6f;
	constexpr float y21 = 3.64f;
	constexpr float y22 = 12.345f;
	constexpr float y23 = 1.30f;
	constexpr float z20 = -893.15f;
	constexpr float z21 = 2.34f;
	constexpr float z22 = -72.2f;
	constexpr float z23 = -6.12f;
	constexpr float w20 = 2.354f;
	constexpr float w21 = 12.36f;
	constexpr float w22 = -5.31f;
	constexpr float w23 = -0.2156f;

	Vec4f x2(x20, x21, x22, x23);
	Vec4f y2(y20, y21, y22, y23);
	Vec4f z2(z20, z21, z22, z23);
	Vec4f w2(w20, w21, w22, w23);

	Mat4f m2(x2, y2, z2, w2);

	EXPECT_FALSE(m1 != m1);
	EXPECT_TRUE(m1 != m2);
}