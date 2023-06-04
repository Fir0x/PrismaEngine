#include <gtest/gtest.h>

#include "core/maths/public/Matrix4.h"

using namespace PrismaEngine;

#define EPSILON 1e-8

constexpr float x10Ref = 1.0f;
constexpr float x11Ref = 2.54f;
constexpr float x12Ref = -3.6f;
constexpr float x13Ref = 98.32f;
constexpr float y10Ref = -23.1f;
constexpr float y11Ref = -4.354f;
constexpr float y12Ref = -26.41f;
constexpr float y13Ref = 13.56f;
constexpr float z10Ref = 285.15f;
constexpr float z11Ref = -87.7f;
constexpr float z12Ref = 354.5f;
constexpr float z13Ref = 12.02f;
constexpr float w10Ref = 23.65f;
constexpr float w11Ref = -9.80f;
constexpr float w12Ref = 0.036f;
constexpr float w13Ref = -1.32f;

constexpr float x20Ref = 64.52f;
constexpr float x21Ref = -6.32f;
constexpr float x22Ref = -2.64f;
constexpr float x23Ref = 120.02f;
constexpr float y20Ref = 4.6f;
constexpr float y21Ref = 3.64f;
constexpr float y22Ref = 12.345f;
constexpr float y23Ref = 1.30f;
constexpr float z20Ref = -893.15f;
constexpr float z21Ref = 2.34f;
constexpr float z22Ref = -72.2f;
constexpr float z23Ref = -6.12f;
constexpr float w20Ref = 2.354f;
constexpr float w21Ref = 12.36f;
constexpr float w22Ref = -5.31f;
constexpr float w23Ref = -0.2156f;

static Matrix4f buildM1Ref()
{
	Vector4f x(x10Ref, x11Ref, x12Ref, x13Ref);
	Vector4f y(y10Ref, y11Ref, y12Ref, y13Ref);
	Vector4f z(z10Ref, z11Ref, z12Ref, z13Ref);
	Vector4f w(w10Ref, w11Ref, w12Ref, w13Ref);

	return Matrix4f::fromPlane(x, y, z, w);
}

static Matrix4f buildM2Ref()
{
	Vector4f x(x20Ref, x21Ref, x22Ref, x23Ref);
	Vector4f y(y20Ref, y21Ref, y22Ref, y23Ref);
	Vector4f z(z20Ref, z21Ref, z22Ref, z23Ref);
	Vector4f w(w20Ref, w21Ref, w22Ref, w23Ref);

	return Matrix4f::fromPlane(x, y, z, w);
}

TEST(Matrix4fTest, ScalarInitialization)
{
	{
		constexpr float val = 1.0f;
		Matrix4f m(val);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				EXPECT_EQ(m.data[i][j], i == j ? val : 0.0f);
		}
	}

	{
		constexpr float val = 2.36f;
		Matrix4f m(val);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				EXPECT_EQ(m.data[i][j], i == j ? val : 0.0f);
		}
	}


	{
		constexpr float val = -2.36f;
		Matrix4f m(val);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				EXPECT_EQ(m.data[i][j], i == j ? val : 0.0f);
		}
	}
}

TEST(Matrix4fTest, Vector4Initialization)
{
	Matrix4f m = buildM1Ref();

	EXPECT_EQ(m.data[0][0], x10Ref);
	EXPECT_EQ(m.data[1][0], x11Ref);
	EXPECT_EQ(m.data[2][0], x12Ref);
	EXPECT_EQ(m.data[3][0], x13Ref);

	EXPECT_EQ(m.data[0][1], y10Ref);
	EXPECT_EQ(m.data[1][1], y11Ref);
	EXPECT_EQ(m.data[2][1], y12Ref);
	EXPECT_EQ(m.data[3][1], y13Ref);

	EXPECT_EQ(m.data[0][2], z10Ref);
	EXPECT_EQ(m.data[1][2], z11Ref);
	EXPECT_EQ(m.data[2][2], z12Ref);
	EXPECT_EQ(m.data[3][2], z13Ref);

	EXPECT_EQ(m.data[0][3], w10Ref);
	EXPECT_EQ(m.data[1][3], w11Ref);
	EXPECT_EQ(m.data[2][3], w12Ref);
	EXPECT_EQ(m.data[3][3], w13Ref);
}

TEST(Matrix4fTest, ReferenceInitialization)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2(m1);

	EXPECT_EQ(m2.data[0][0], x10Ref);
	EXPECT_EQ(m2.data[1][0], x11Ref);
	EXPECT_EQ(m2.data[2][0], x12Ref);
	EXPECT_EQ(m2.data[3][0], x13Ref);

	EXPECT_EQ(m2.data[0][1], y10Ref);
	EXPECT_EQ(m2.data[1][1], y11Ref);
	EXPECT_EQ(m2.data[2][1], y12Ref);
	EXPECT_EQ(m2.data[3][1], y13Ref);

	EXPECT_EQ(m2.data[0][2], z10Ref);
	EXPECT_EQ(m2.data[1][2], z11Ref);
	EXPECT_EQ(m2.data[2][2], z12Ref);
	EXPECT_EQ(m2.data[3][2], z13Ref);

	EXPECT_EQ(m2.data[0][3], w10Ref);
	EXPECT_EQ(m2.data[1][3], w11Ref);
	EXPECT_EQ(m2.data[2][3], w12Ref);
	EXPECT_EQ(m2.data[3][3], w13Ref);
}

TEST(Matrix4fTest, Identity)
{
	Matrix4f identity = Matrix4f::identity();

	EXPECT_EQ(identity.data[0][0], 1.0f);
	EXPECT_EQ(identity.data[1][0], 0.0f);
	EXPECT_EQ(identity.data[2][0], 0.0f);
	EXPECT_EQ(identity.data[3][0], 0.0f);

	EXPECT_EQ(identity.data[0][1], 0.0f);
	EXPECT_EQ(identity.data[1][1], 1.0f);
	EXPECT_EQ(identity.data[2][1], 0.0f);
	EXPECT_EQ(identity.data[3][1], 0.0f);

	EXPECT_EQ(identity.data[0][2], 0.0f);
	EXPECT_EQ(identity.data[1][2], 0.0f);
	EXPECT_EQ(identity.data[2][2], 1.0f);
	EXPECT_EQ(identity.data[3][2], 0.0f);

	EXPECT_EQ(identity.data[0][3], 0.0f);
	EXPECT_EQ(identity.data[1][3], 0.0f);
	EXPECT_EQ(identity.data[2][3], 0.0f);
	EXPECT_EQ(identity.data[3][3], 1.0f);
}

TEST(Matrix4fTest, AddBasic)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2 = buildM2Ref();

	Matrix4f m3 = m1 + m2;

	EXPECT_EQ(m3.data[0][0], x10Ref + x20Ref);
	EXPECT_EQ(m3.data[1][0], x11Ref + x21Ref);
	EXPECT_EQ(m3.data[2][0], x12Ref + x22Ref);
	EXPECT_EQ(m3.data[3][0], x13Ref + x23Ref);

	EXPECT_EQ(m3.data[0][1], y10Ref + y20Ref);
	EXPECT_EQ(m3.data[1][1], y11Ref + y21Ref);
	EXPECT_EQ(m3.data[2][1], y12Ref + y22Ref);
	EXPECT_EQ(m3.data[3][1], y13Ref + y23Ref);

	EXPECT_EQ(m3.data[0][2], z10Ref + z20Ref);
	EXPECT_EQ(m3.data[1][2], z11Ref + z21Ref);
	EXPECT_EQ(m3.data[2][2], z12Ref + z22Ref);
	EXPECT_EQ(m3.data[3][2], z13Ref + z23Ref);

	EXPECT_EQ(m3.data[0][3], w10Ref + w20Ref);
	EXPECT_EQ(m3.data[1][3], w11Ref + w21Ref);
	EXPECT_EQ(m3.data[2][3], w12Ref + w22Ref);
	EXPECT_EQ(m3.data[3][3], w13Ref + w23Ref);
}

TEST(Matrix4fTest, AddCommutative)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2 = buildM2Ref();

	Matrix4f m3 = m2 + m1;

	EXPECT_EQ(m3.data[0][0], x10Ref + x20Ref);
	EXPECT_EQ(m3.data[1][0], x11Ref + x21Ref);
	EXPECT_EQ(m3.data[2][0], x12Ref + x22Ref);
	EXPECT_EQ(m3.data[3][0], x13Ref + x23Ref);

	EXPECT_EQ(m3.data[0][1], y10Ref + y20Ref);
	EXPECT_EQ(m3.data[1][1], y11Ref + y21Ref);
	EXPECT_EQ(m3.data[2][1], y12Ref + y22Ref);
	EXPECT_EQ(m3.data[3][1], y13Ref + y23Ref);

	EXPECT_EQ(m3.data[0][2], z10Ref + z20Ref);
	EXPECT_EQ(m3.data[1][2], z11Ref + z21Ref);
	EXPECT_EQ(m3.data[2][2], z12Ref + z22Ref);
	EXPECT_EQ(m3.data[3][2], z13Ref + z23Ref);

	EXPECT_EQ(m3.data[0][3], w10Ref + w20Ref);
	EXPECT_EQ(m3.data[1][3], w11Ref + w21Ref);
	EXPECT_EQ(m3.data[2][3], w12Ref + w22Ref);
	EXPECT_EQ(m3.data[3][3], w13Ref + w23Ref);
}

TEST(Matrix4fTest, SubtractBasic)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2 = buildM2Ref();

	Matrix4f m3 = m1 - m2;

	EXPECT_EQ(m3.data[0][0], x10Ref - x20Ref);
	EXPECT_EQ(m3.data[1][0], x11Ref - x21Ref);
	EXPECT_EQ(m3.data[2][0], x12Ref - x22Ref);
	EXPECT_EQ(m3.data[3][0], x13Ref - x23Ref);

	EXPECT_EQ(m3.data[0][1], y10Ref - y20Ref);
	EXPECT_EQ(m3.data[1][1], y11Ref - y21Ref);
	EXPECT_EQ(m3.data[2][1], y12Ref - y22Ref);
	EXPECT_EQ(m3.data[3][1], y13Ref - y23Ref);

	EXPECT_EQ(m3.data[0][2], z10Ref - z20Ref);
	EXPECT_EQ(m3.data[1][2], z11Ref - z21Ref);
	EXPECT_EQ(m3.data[2][2], z12Ref - z22Ref);
	EXPECT_EQ(m3.data[3][2], z13Ref - z23Ref);

	EXPECT_EQ(m3.data[0][3], w10Ref - w20Ref);
	EXPECT_EQ(m3.data[1][3], w11Ref - w21Ref);
	EXPECT_EQ(m3.data[2][3], w12Ref - w22Ref);
	EXPECT_EQ(m3.data[3][3], w13Ref - w23Ref);
}

TEST(Matrix4fTest, SubtractNotCommutative)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2 = buildM2Ref();

	Matrix4f m3 = m2 - m1;

	EXPECT_EQ(m3.data[0][0], x20Ref - x10Ref);
	EXPECT_EQ(m3.data[1][0], x21Ref - x11Ref);
	EXPECT_EQ(m3.data[2][0], x22Ref - x12Ref);
	EXPECT_EQ(m3.data[3][0], x23Ref - x13Ref);

	EXPECT_EQ(m3.data[0][1], y20Ref - y10Ref);
	EXPECT_EQ(m3.data[1][1], y21Ref - y11Ref);
	EXPECT_EQ(m3.data[2][1], y22Ref - y12Ref);
	EXPECT_EQ(m3.data[3][1], y23Ref - y13Ref);

	EXPECT_EQ(m3.data[0][2], z20Ref - z10Ref);
	EXPECT_EQ(m3.data[1][2], z21Ref - z11Ref);
	EXPECT_EQ(m3.data[2][2], z22Ref - z12Ref);
	EXPECT_EQ(m3.data[3][2], z23Ref - z13Ref);

	EXPECT_EQ(m3.data[0][3], w20Ref - w10Ref);
	EXPECT_EQ(m3.data[1][3], w21Ref - w11Ref);
	EXPECT_EQ(m3.data[2][3], w22Ref - w12Ref);
	EXPECT_EQ(m3.data[3][3], w23Ref - w13Ref);
}

TEST(Matrix4fTest, ProductIdentity)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f identity = Matrix4f::identity();

	Matrix4f m3 = m1 * identity;
	EXPECT_EQ(m3.data[0][0], x10Ref);
	EXPECT_EQ(m3.data[1][0], x11Ref);
	EXPECT_EQ(m3.data[2][0], x12Ref);
	EXPECT_EQ(m3.data[3][0], x13Ref);

	EXPECT_EQ(m3.data[0][1], y10Ref);
	EXPECT_EQ(m3.data[1][1], y11Ref);
	EXPECT_EQ(m3.data[2][1], y12Ref);
	EXPECT_EQ(m3.data[3][1], y13Ref);

	EXPECT_EQ(m3.data[0][2], z10Ref);
	EXPECT_EQ(m3.data[1][2], z11Ref);
	EXPECT_EQ(m3.data[2][2], z12Ref);
	EXPECT_EQ(m3.data[3][2], z13Ref);

	EXPECT_EQ(m3.data[0][3], w10Ref);
	EXPECT_EQ(m3.data[1][3], w11Ref);
	EXPECT_EQ(m3.data[2][3], w12Ref);
	EXPECT_EQ(m3.data[3][3], w13Ref);
}

TEST(Matrix4fTest, ProductBasic)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2 = buildM2Ref();

	Matrix4f m3 = m1 * m2;
	const float x30 = x10Ref * x20Ref + y10Ref * x21Ref + z10Ref * x22Ref + w10Ref * x23Ref;
	const float x31 = x11Ref * x20Ref + y11Ref * x21Ref + z11Ref * x22Ref + w11Ref * x23Ref;
	const float x32 = x12Ref * x20Ref + y12Ref * x21Ref + z12Ref * x22Ref + w12Ref * x23Ref;
	const float x33 = x13Ref * x20Ref + y13Ref * x21Ref + z13Ref * x22Ref + w13Ref * x23Ref;
	const float y30 = x10Ref * y20Ref + y10Ref * y21Ref + z10Ref * y22Ref + w10Ref * y23Ref;
	const float y31 = x11Ref * y20Ref + y11Ref * y21Ref + z11Ref * y22Ref + w11Ref * y23Ref;
	const float y32 = x12Ref * y20Ref + y12Ref * y21Ref + z12Ref * y22Ref + w12Ref * y23Ref;
	const float y33 = x13Ref * y20Ref + y13Ref * y21Ref + z13Ref * y22Ref + w13Ref * y23Ref;
	const float z30 = x10Ref * z20Ref + y10Ref * z21Ref + z10Ref * z22Ref + w10Ref * z23Ref;
	const float z31 = x11Ref * z20Ref + y11Ref * z21Ref + z11Ref * z22Ref + w11Ref * z23Ref;
	const float z32 = x12Ref * z20Ref + y12Ref * z21Ref + z12Ref * z22Ref + w12Ref * z23Ref;
	const float z33 = x13Ref * z20Ref + y13Ref * z21Ref + z13Ref * z22Ref + w13Ref * z23Ref;
	const float w30 = x10Ref * w20Ref + y10Ref * w21Ref + z10Ref * w22Ref + w10Ref * w23Ref;
	const float w31 = x11Ref * w20Ref + y11Ref * w21Ref + z11Ref * w22Ref + w11Ref * w23Ref;
	const float w32 = x12Ref * w20Ref + y12Ref * w21Ref + z12Ref * w22Ref + w12Ref * w23Ref;
	const float w33 = x13Ref * w20Ref + y13Ref * w21Ref + z13Ref * w22Ref + w13Ref * w23Ref;

	EXPECT_EQ(m3.data[0][0], x30);
	EXPECT_EQ(m3.data[1][0], x31);
	EXPECT_EQ(m3.data[2][0], x32);
	EXPECT_EQ(m3.data[3][0], x33);

	EXPECT_EQ(m3.data[0][1], y30);
	EXPECT_EQ(m3.data[1][1], y31);
	EXPECT_EQ(m3.data[2][1], y32);
	EXPECT_EQ(m3.data[3][1], y33);

	EXPECT_EQ(m3.data[0][2], z30);
	EXPECT_EQ(m3.data[1][2], z31);
	EXPECT_EQ(m3.data[2][2], z32);
	EXPECT_EQ(m3.data[3][2], z33);

	EXPECT_EQ(m3.data[0][3], w30);
	EXPECT_EQ(m3.data[1][3], w31);
	EXPECT_EQ(m3.data[2][3], w32);
	EXPECT_EQ(m3.data[3][3], w33);
}

TEST(Matrix4fTest, ProductNotCommutative)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2 = buildM2Ref();

	Matrix4f m3 = m2 * m1;
	const float x30 = x20Ref * x10Ref + y20Ref * x11Ref + z20Ref * x12Ref + w20Ref * x13Ref;
	const float x31 = x21Ref * x10Ref + y21Ref * x11Ref + z21Ref * x12Ref + w21Ref * x13Ref;
	const float x32 = x22Ref * x10Ref + y22Ref * x11Ref + z22Ref * x12Ref + w22Ref * x13Ref;
	const float x33 = x23Ref * x10Ref + y23Ref * x11Ref + z23Ref * x12Ref + w23Ref * x13Ref;
	const float y30 = x20Ref * y10Ref + y20Ref * y11Ref + z20Ref * y12Ref + w20Ref * y13Ref;
	const float y31 = x21Ref * y10Ref + y21Ref * y11Ref + z21Ref * y12Ref + w21Ref * y13Ref;
	const float y32 = x22Ref * y10Ref + y22Ref * y11Ref + z22Ref * y12Ref + w22Ref * y13Ref;
	const float y33 = x23Ref * y10Ref + y23Ref * y11Ref + z23Ref * y12Ref + w23Ref * y13Ref;
	const float z30 = x20Ref * z10Ref + y20Ref * z11Ref + z20Ref * z12Ref + w20Ref * z13Ref;
	const float z31 = x21Ref * z10Ref + y21Ref * z11Ref + z21Ref * z12Ref + w21Ref * z13Ref;
	const float z32 = x22Ref * z10Ref + y22Ref * z11Ref + z22Ref * z12Ref + w22Ref * z13Ref;
	const float z33 = x23Ref * z10Ref + y23Ref * z11Ref + z23Ref * z12Ref + w23Ref * z13Ref;
	const float w30 = x20Ref * w10Ref + y20Ref * w11Ref + z20Ref * w12Ref + w20Ref * w13Ref;
	const float w31 = x21Ref * w10Ref + y21Ref * w11Ref + z21Ref * w12Ref + w21Ref * w13Ref;
	const float w32 = x22Ref * w10Ref + y22Ref * w11Ref + z22Ref * w12Ref + w22Ref * w13Ref;
	const float w33 = x23Ref * w10Ref + y23Ref * w11Ref + z23Ref * w12Ref + w23Ref * w13Ref;

	EXPECT_EQ(m3.data[0][0], x30);
	EXPECT_EQ(m3.data[1][0], x31);
	EXPECT_EQ(m3.data[2][0], x32);
	EXPECT_EQ(m3.data[3][0], x33);

	EXPECT_EQ(m3.data[0][1], y30);
	EXPECT_EQ(m3.data[1][1], y31);
	EXPECT_EQ(m3.data[2][1], y32);
	EXPECT_EQ(m3.data[3][1], y33);

	EXPECT_EQ(m3.data[0][2], z30);
	EXPECT_EQ(m3.data[1][2], z31);
	EXPECT_EQ(m3.data[2][2], z32);
	EXPECT_EQ(m3.data[3][2], z33);

	EXPECT_EQ(m3.data[0][3], w30);
	EXPECT_EQ(m3.data[1][3], w31);
	EXPECT_EQ(m3.data[2][3], w32);
	EXPECT_EQ(m3.data[3][3], w33);
}

TEST(Matrix4fTest, TransposeIdentity)
{
	Matrix4f identity = Matrix4f::identity();
	Matrix4f mTransposed = identity.transpose();

	EXPECT_EQ(mTransposed.data[0][0], 1.0f);
	EXPECT_EQ(mTransposed.data[1][0], 0.0f);
	EXPECT_EQ(mTransposed.data[2][0], 0.0f);
	EXPECT_EQ(mTransposed.data[3][0], 0.0f);

	EXPECT_EQ(mTransposed.data[0][1], 0.0f);
	EXPECT_EQ(mTransposed.data[1][1], 1.0f);
	EXPECT_EQ(mTransposed.data[2][1], 0.0f);
	EXPECT_EQ(mTransposed.data[3][1], 0.0f);

	EXPECT_EQ(mTransposed.data[0][2], 0.0f);
	EXPECT_EQ(mTransposed.data[1][2], 0.0f);
	EXPECT_EQ(mTransposed.data[2][2], 1.0f);
	EXPECT_EQ(mTransposed.data[3][2], 0.0f);

	EXPECT_EQ(mTransposed.data[0][3], 0.0f);
	EXPECT_EQ(mTransposed.data[1][3], 0.0f);
	EXPECT_EQ(mTransposed.data[2][3], 0.0f);
	EXPECT_EQ(mTransposed.data[3][3], 1.0f);
}

TEST(Matrix4fTest, TransposeBasic)
{
	Matrix4f m = buildM1Ref();
	Matrix4f mTransposed = m.transpose();

	EXPECT_EQ(mTransposed.data[0][0], x10Ref);
	EXPECT_EQ(mTransposed.data[1][0], y10Ref);
	EXPECT_EQ(mTransposed.data[2][0], z10Ref);
	EXPECT_EQ(mTransposed.data[3][0], w10Ref);

	EXPECT_EQ(mTransposed.data[0][1], x11Ref);
	EXPECT_EQ(mTransposed.data[1][1], y11Ref);
	EXPECT_EQ(mTransposed.data[2][1], z11Ref);
	EXPECT_EQ(mTransposed.data[3][1], w11Ref);

	EXPECT_EQ(mTransposed.data[0][2], x12Ref);
	EXPECT_EQ(mTransposed.data[1][2], y12Ref);
	EXPECT_EQ(mTransposed.data[2][2], z12Ref);
	EXPECT_EQ(mTransposed.data[3][2], w12Ref);

	EXPECT_EQ(mTransposed.data[0][3], x13Ref);
	EXPECT_EQ(mTransposed.data[1][3], y13Ref);
	EXPECT_EQ(mTransposed.data[2][3], z13Ref);
	EXPECT_EQ(mTransposed.data[3][3], w13Ref);
}

TEST(Matrix4fTest, Determinant)
{
	Matrix4f m = buildM1Ref();

	float det = m.determinant();

	constexpr float subSubFactor01 = z10Ref * w11Ref - z11Ref * w10Ref;
	constexpr float subSubFactor12 = z11Ref * w12Ref - z12Ref * w11Ref;
	constexpr float subSubFactor23 = z12Ref * w13Ref - z13Ref * w12Ref;
	constexpr float subSubFactor02 = z10Ref * w12Ref - z12Ref * w10Ref;
	constexpr float subSubFactor13 = z11Ref * w13Ref - z13Ref * w11Ref;
	constexpr float subSubFactor03 = z10Ref * w13Ref - z13Ref * w10Ref;

	constexpr float subFactor0 = y11Ref * subSubFactor23 - y12Ref * subSubFactor13 + y13Ref * subSubFactor12;
	constexpr float subFactor1 = y10Ref * subSubFactor23 - y12Ref * subSubFactor03 + y13Ref * subSubFactor02;
	constexpr float subFactor2 = y10Ref * subSubFactor13 - y11Ref * subSubFactor03 + y13Ref * subSubFactor01;
	constexpr float subFactor3 = y10Ref * subSubFactor12 - y11Ref * subSubFactor02 + y12Ref * subSubFactor01;

	constexpr float detRef = x10Ref * subFactor0 - x11Ref * subFactor1 + x12Ref * subFactor2 - x13Ref * subFactor3;

	EXPECT_EQ(det, detRef);
}

TEST(Matrix4fTest, InverseIdentity)
{
	Matrix4f identity = Matrix4f::identity();
	Matrix4f mInverted = identity.inverse();

	EXPECT_EQ(mInverted.data[0][0], 1.0f);
	EXPECT_EQ(mInverted.data[1][0], 0.0f);
	EXPECT_EQ(mInverted.data[2][0], 0.0f);
	EXPECT_EQ(mInverted.data[3][0], 0.0f);

	EXPECT_EQ(mInverted.data[0][1], 0.0f);
	EXPECT_EQ(mInverted.data[1][1], 1.0f);
	EXPECT_EQ(mInverted.data[2][1], 0.0f);
	EXPECT_EQ(mInverted.data[3][1], 0.0f);

	EXPECT_EQ(mInverted.data[0][2], 0.0f);
	EXPECT_EQ(mInverted.data[1][2], 0.0f);
	EXPECT_EQ(mInverted.data[2][2], 1.0f);
	EXPECT_EQ(mInverted.data[3][2], 0.0f);

	EXPECT_EQ(mInverted.data[0][3], 0.0f);
	EXPECT_EQ(mInverted.data[1][3], 0.0f);
	EXPECT_EQ(mInverted.data[2][3], 0.0f);
	EXPECT_EQ(mInverted.data[3][3], 1.0f);
}

TEST(Matrix4fTest, InverseBasic)
{
	Matrix4f m = buildM1Ref();

	Matrix4f mInverted = m.inverse();

	// Naming: coef<column><coef id>
	constexpr float coef01 = y12Ref * z13Ref - z12Ref * y13Ref;
	constexpr float coef02 = y12Ref * w13Ref - w12Ref * y13Ref;
	constexpr float coef03 = z12Ref * w13Ref - w12Ref * z13Ref;
	constexpr float coef04 = x12Ref * z13Ref - z12Ref * x13Ref;
	constexpr float coef05 = x12Ref * w13Ref - w12Ref * x13Ref;
	constexpr float coef06 = x12Ref * y13Ref - y12Ref * x13Ref;

	constexpr float coef21 = y11Ref * z13Ref - z11Ref * y13Ref;
	constexpr float coef22 = y11Ref * w13Ref - w11Ref * y13Ref;
	constexpr float coef23 = z11Ref * w13Ref - w11Ref * z13Ref;
	constexpr float coef24 = x11Ref * z13Ref - z11Ref * x13Ref;
	constexpr float coef25 = x11Ref * w13Ref - w11Ref * x13Ref;
	constexpr float coef26 = x11Ref * y13Ref - y11Ref * x13Ref;

	constexpr float coef31 = y11Ref * z12Ref - z11Ref * y12Ref;
	constexpr float coef32 = y11Ref * w12Ref - w11Ref * y12Ref;
	constexpr float coef33 = z11Ref * w12Ref - w11Ref * z12Ref;
	constexpr float coef34 = x11Ref * z12Ref - z11Ref * x12Ref;
	constexpr float coef35 = x11Ref * w12Ref - w11Ref * x12Ref;
	constexpr float coef36 = x11Ref * y12Ref - y11Ref * x12Ref;

	constexpr float adjugateX0 = +(y11Ref * coef03 - z11Ref * coef02 + w11Ref * coef01);
	constexpr float adjugateX1 = -(x11Ref * coef03 - z11Ref * coef05 + w11Ref * coef04);
	constexpr float adjugateX2 = +(x11Ref * coef02 - y11Ref * coef05 + w11Ref * coef06);
	constexpr float adjugateX3 = -(x11Ref * coef01 - y11Ref * coef04 + z11Ref * coef06);

	constexpr float adjugateY0 = -(y10Ref * coef03 - z10Ref * coef02 + w10Ref * coef01);
	constexpr float adjugateY1 = +(x10Ref * coef03 - z10Ref * coef05 + w10Ref * coef04);
	constexpr float adjugateY2 = -(x10Ref * coef02 - y10Ref * coef05 + w10Ref * coef06);
	constexpr float adjugateY3 = +(x10Ref * coef01 - y10Ref * coef04 + z10Ref * coef06);

	constexpr float adjugateZ0 = +(y10Ref * coef23 - z10Ref * coef22 + w10Ref * coef21);
	constexpr float adjugateZ1 = -(x10Ref * coef23 - z10Ref * coef25 + w10Ref * coef24);
	constexpr float adjugateZ2 = +(x10Ref * coef22 - y10Ref * coef25 + w10Ref * coef26);
	constexpr float adjugateZ3 = -(x10Ref * coef21 - y10Ref * coef24 + z10Ref * coef26);

	constexpr float adjugateW0 = -(y10Ref * coef33 - z10Ref * coef32 + w10Ref * coef31);
	constexpr float adjugateW1 = +(x10Ref * coef33 - z10Ref * coef35 + w10Ref * coef34);
	constexpr float adjugateW2 = -(x10Ref * coef32 - y10Ref * coef35 + w10Ref * coef36);
	constexpr float adjugateW3 = +(x10Ref * coef31 - y10Ref * coef34 + z10Ref * coef36);

	constexpr float determinant = x10Ref * adjugateX0 + y10Ref * adjugateX1 + z10Ref * adjugateX2 + w10Ref * adjugateX3;
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

	EXPECT_NEAR(mInverted.data[0][0], inverseX0, EPSILON);
	EXPECT_NEAR(mInverted.data[1][0], inverseX1, EPSILON);
	EXPECT_NEAR(mInverted.data[2][0], inverseX2, EPSILON);
	EXPECT_NEAR(mInverted.data[3][0], inverseX3, EPSILON);

	EXPECT_NEAR(mInverted.data[0][1], inverseY0, EPSILON);
	EXPECT_NEAR(mInverted.data[1][1], inverseY1, EPSILON);
	EXPECT_NEAR(mInverted.data[2][1], inverseY2, EPSILON);
	EXPECT_NEAR(mInverted.data[3][1], inverseY3, EPSILON);

	EXPECT_NEAR(mInverted.data[0][2], inverseZ0, EPSILON);
	EXPECT_NEAR(mInverted.data[1][2], inverseZ1, EPSILON);
	EXPECT_NEAR(mInverted.data[2][2], inverseZ2, EPSILON);
	EXPECT_NEAR(mInverted.data[3][2], inverseZ3, EPSILON);

	EXPECT_NEAR(mInverted.data[0][3], inverseW0, EPSILON);
	EXPECT_NEAR(mInverted.data[1][3], inverseW1, EPSILON);
	EXPECT_NEAR(mInverted.data[2][3], inverseW2, EPSILON);
	EXPECT_NEAR(mInverted.data[3][3], inverseW3, EPSILON);
}

TEST(Matrix4fTest, RowAccess)
{
	Matrix4f m = buildM1Ref();

	Vector4f r0 = m.getRow(0);
	EXPECT_EQ(r0.x, x10Ref);
	EXPECT_EQ(r0.y, y10Ref);
	EXPECT_EQ(r0.z, z10Ref);
	EXPECT_EQ(r0.w, w10Ref);

	Vector4f r1 = m.getRow(1);
	EXPECT_EQ(r1.x, x11Ref);
	EXPECT_EQ(r1.y, y11Ref);
	EXPECT_EQ(r1.z, z11Ref);
	EXPECT_EQ(r1.w, w11Ref);

	Vector4f r2 = m.getRow(2);
	EXPECT_EQ(r2.x, x12Ref);
	EXPECT_EQ(r2.y, y12Ref);
	EXPECT_EQ(r2.z, z12Ref);
	EXPECT_EQ(r2.w, w12Ref);

	Vector4f r3 = m.getRow(3);
	EXPECT_EQ(r3.x, x13Ref);
	EXPECT_EQ(r3.y, y13Ref);
	EXPECT_EQ(r3.z, z13Ref);
	EXPECT_EQ(r3.w, w13Ref);
}

TEST(Matrix4fTest, ColumnAccess)
{
	Matrix4f m = buildM1Ref();

	Vector4f c0 = m.getColumn(0);
	EXPECT_EQ(c0.x, x10Ref);
	EXPECT_EQ(c0.y, x11Ref);
	EXPECT_EQ(c0.z, x12Ref);
	EXPECT_EQ(c0.w, x13Ref);

	Vector4f c1 = m.getColumn(1);
	EXPECT_EQ(c1.x, y10Ref);
	EXPECT_EQ(c1.y, y11Ref);
	EXPECT_EQ(c1.z, y12Ref);
	EXPECT_EQ(c1.w, y13Ref);

	Vector4f c2 = m.getColumn(2);
	EXPECT_EQ(c2.x, z10Ref);
	EXPECT_EQ(c2.y, z11Ref);
	EXPECT_EQ(c2.z, z12Ref);
	EXPECT_EQ(c2.w, z13Ref);

	Vector4f c3 = m.getColumn(3);
	EXPECT_EQ(c3.x, w10Ref);
	EXPECT_EQ(c3.y, w11Ref);
	EXPECT_EQ(c3.z, w12Ref);
	EXPECT_EQ(c3.w, w13Ref);
}

TEST(Matrix4fTest, Equality)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2 = buildM2Ref();

	EXPECT_TRUE(m1 == m1);
	EXPECT_FALSE(m1 == m2);
}

TEST(Matrix4fTest, Inequality)
{
	Matrix4f m1 = buildM1Ref();
	Matrix4f m2 = buildM2Ref();

	EXPECT_FALSE(m1 != m1);
	EXPECT_TRUE(m1 != m2);
}