#include <gtest/gtest.h>

#include "core/maths/public/Matrix3.h"

using namespace PrismaEngine;

constexpr float x10Ref = 1.0f;
constexpr float x11Ref = 2.54f;
constexpr float x12Ref = -3.6f;
constexpr float y10Ref = -23.1f;
constexpr float y11Ref = -4.354f;
constexpr float y12Ref = -26.41f;
constexpr float z10Ref = 285.15f;
constexpr float z11Ref = -87.7f;
constexpr float z12Ref = 354.5f;

constexpr float x20Ref = 64.52f;
constexpr float x21Ref = -6.32f;
constexpr float x22Ref = -2.64f;
constexpr float y20Ref = 4.6f;
constexpr float y21Ref = 3.64f;
constexpr float y22Ref = 12.345f;
constexpr float z20Ref = -893.15f;
constexpr float z21Ref = 2.34f;
constexpr float z22Ref = -72.2f;

static Matrix3f buildM1Ref()
{
	Vector3f x(x10Ref, x11Ref, x12Ref);
	Vector3f y(y10Ref, y11Ref, y12Ref);
	Vector3f z(z10Ref, z11Ref, z12Ref);

	return Matrix3f::fromPlane(x, y, z);
}

static Matrix3f buildM2Ref()
{
	Vector3f x2(x20Ref, x21Ref, x22Ref);
	Vector3f y2(y20Ref, y21Ref, y22Ref);
	Vector3f z2(z20Ref, z21Ref, z22Ref);

	return Matrix3f::fromPlane(x2, y2, z2);
}

TEST(Matrix3fTest, ScalarInitialization)
{
	{
		constexpr float val = 1.0f;
		Matrix3f m(val);
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
				EXPECT_EQ(m.getValue(row, column), row == column ? val : 0.0f);
		}
	}

	{
		constexpr float val = 2.36f;
		Matrix3f m(val);
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
				EXPECT_EQ(m.getValue(row, column), row == column ? val : 0.0f);
		}
	}


	{
		constexpr float val = -2.36f;
		Matrix3f m(val);
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
				EXPECT_EQ(m.getValue(row, column), row == column ? val : 0.0f);
		}
	}
}

TEST(Matrix3fTest, PlaneInitialization)
{
	Matrix3f m = buildM1Ref();

	EXPECT_EQ(m.getValue(0, 0), x10Ref);
	EXPECT_EQ(m.getValue(1, 0), x11Ref);
	EXPECT_EQ(m.getValue(2, 0), x12Ref);

	EXPECT_EQ(m.getValue(0, 1), y10Ref);
	EXPECT_EQ(m.getValue(1, 1), y11Ref);
	EXPECT_EQ(m.getValue(2, 1), y12Ref);

	EXPECT_EQ(m.getValue(0, 2), z10Ref);
	EXPECT_EQ(m.getValue(1, 2), z11Ref);
	EXPECT_EQ(m.getValue(2, 2), z12Ref);
}

TEST(Matrix3fTest, ReferenceInitialization)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2(m1);

	EXPECT_EQ(m2.getValue(0, 0), x10Ref);
	EXPECT_EQ(m2.getValue(1, 0), x11Ref);
	EXPECT_EQ(m2.getValue(2, 0), x12Ref);

	EXPECT_EQ(m2.getValue(0, 1), y10Ref);
	EXPECT_EQ(m2.getValue(1, 1), y11Ref);
	EXPECT_EQ(m2.getValue(2, 1), y12Ref);

	EXPECT_EQ(m2.getValue(0, 2), z10Ref);
	EXPECT_EQ(m2.getValue(1, 2), z11Ref);
	EXPECT_EQ(m2.getValue(2, 2), z12Ref);
}

TEST(Matrix3fTest, Identity)
{
	Matrix3f identity = Matrix3f::identity();

	EXPECT_EQ(identity.data[0][0], 1.0f);
	EXPECT_EQ(identity.data[1][0], 0.0f);
	EXPECT_EQ(identity.data[2][0], 0.0f);

	EXPECT_EQ(identity.data[0][1], 0.0f);
	EXPECT_EQ(identity.data[1][1], 1.0f);
	EXPECT_EQ(identity.data[2][1], 0.0f);

	EXPECT_EQ(identity.data[0][2], 0.0f);
	EXPECT_EQ(identity.data[1][2], 0.0f);
	EXPECT_EQ(identity.data[2][2], 1.0f);
}

TEST(Matrix3fTest, AddBasic)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2 = buildM2Ref();

	{
		Matrix3f m3 = m1 + m2;

		EXPECT_EQ(m3.getValue(0, 0), x10Ref + x20Ref);
		EXPECT_EQ(m3.getValue(1, 0), x11Ref + x21Ref);
		EXPECT_EQ(m3.getValue(2, 0), x12Ref + x22Ref);

		EXPECT_EQ(m3.getValue(0, 1), y10Ref + y20Ref);
		EXPECT_EQ(m3.getValue(1, 1), y11Ref + y21Ref);
		EXPECT_EQ(m3.getValue(2, 1), y12Ref + y22Ref);

		EXPECT_EQ(m3.getValue(0, 2), z10Ref + z20Ref);
		EXPECT_EQ(m3.getValue(1, 2), z11Ref + z21Ref);
		EXPECT_EQ(m3.getValue(2, 2), z12Ref + z22Ref);
	}
}

TEST(Matrix3fTest, AddCommutative)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2 = buildM2Ref();

	{
		Matrix3f m3 = m2 + m1;

		EXPECT_EQ(m3.getValue(0, 0), x10Ref + x20Ref);
		EXPECT_EQ(m3.getValue(1, 0), x11Ref + x21Ref);
		EXPECT_EQ(m3.getValue(2, 0), x12Ref + x22Ref);

		EXPECT_EQ(m3.getValue(0, 1), y10Ref + y20Ref);
		EXPECT_EQ(m3.getValue(1, 1), y11Ref + y21Ref);
		EXPECT_EQ(m3.getValue(2, 1), y12Ref + y22Ref);

		EXPECT_EQ(m3.getValue(0, 2), z10Ref + z20Ref);
		EXPECT_EQ(m3.getValue(1, 2), z11Ref + z21Ref);
		EXPECT_EQ(m3.getValue(2, 2), z12Ref + z22Ref);
	}
}

TEST(Matrix3fTest, SubtractBasic)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2 = buildM2Ref();

	{
		Matrix3f m3 = m1 - m2;

		EXPECT_EQ(m3.getValue(0, 0), x10Ref - x20Ref);
		EXPECT_EQ(m3.getValue(1, 0), x11Ref - x21Ref);
		EXPECT_EQ(m3.getValue(2, 0), x12Ref - x22Ref);

		EXPECT_EQ(m3.getValue(0, 1), y10Ref - y20Ref);
		EXPECT_EQ(m3.getValue(1, 1), y11Ref - y21Ref);
		EXPECT_EQ(m3.getValue(2, 1), y12Ref - y22Ref);

		EXPECT_EQ(m3.getValue(0, 2), z10Ref - z20Ref);
		EXPECT_EQ(m3.getValue(1, 2), z11Ref - z21Ref);
		EXPECT_EQ(m3.getValue(2, 2), z12Ref - z22Ref);
	}
}

TEST(Matrix3fTest, SubtractNotCommutative)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2 = buildM2Ref();

	{
		Matrix3f m3 = m2 - m1;

		EXPECT_EQ(m3.getValue(0, 0), x20Ref - x10Ref);
		EXPECT_EQ(m3.getValue(1, 0), x21Ref - x11Ref);
		EXPECT_EQ(m3.getValue(2, 0), x22Ref - x12Ref);

		EXPECT_EQ(m3.getValue(0, 1), y20Ref - y10Ref);
		EXPECT_EQ(m3.getValue(1, 1), y21Ref - y11Ref);
		EXPECT_EQ(m3.getValue(2, 1), y22Ref - y12Ref);

		EXPECT_EQ(m3.getValue(0, 2), z20Ref - z10Ref);
		EXPECT_EQ(m3.getValue(1, 2), z21Ref - z11Ref);
		EXPECT_EQ(m3.getValue(2, 2), z22Ref - z12Ref);
	}
}

TEST(Matrix3fTest, ProductIdentity)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f identity = Matrix3f::identity();

	Matrix3f m3 = m1 * identity;
	EXPECT_EQ(m3.getValue(0, 0), x10Ref);
	EXPECT_EQ(m3.getValue(1, 0), x11Ref);
	EXPECT_EQ(m3.getValue(2, 0), x12Ref);

	EXPECT_EQ(m3.getValue(0, 1), y10Ref);
	EXPECT_EQ(m3.getValue(1, 1), y11Ref);
	EXPECT_EQ(m3.getValue(2, 1), y12Ref);

	EXPECT_EQ(m3.getValue(0, 2), z10Ref);
	EXPECT_EQ(m3.getValue(1, 2), z11Ref);
	EXPECT_EQ(m3.getValue(2, 2), z12Ref);
}

TEST(Matrix3fTest, ProductBasic)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2 = buildM2Ref();

	Matrix3f m3 = m1 * m2;
	const float x30 = x10Ref * x20Ref + y10Ref * x21Ref + z10Ref * x22Ref;
	const float x31 = x11Ref * x20Ref + y11Ref * x21Ref + z11Ref * x22Ref;
	const float x32 = x12Ref * x20Ref + y12Ref * x21Ref + z12Ref * x22Ref;
	const float y30 = x10Ref * y20Ref + y10Ref * y21Ref + z10Ref * y22Ref;
	const float y31 = x11Ref * y20Ref + y11Ref * y21Ref + z11Ref * y22Ref;
	const float y32 = x12Ref * y20Ref + y12Ref * y21Ref + z12Ref * y22Ref;
	const float z30 = x10Ref * z20Ref + y10Ref * z21Ref + z10Ref * z22Ref;
	const float z31 = x11Ref * z20Ref + y11Ref * z21Ref + z11Ref * z22Ref;
	const float z32 = x12Ref * z20Ref + y12Ref * z21Ref + z12Ref * z22Ref;

	EXPECT_EQ(m3.getValue(0, 0), x30);
	EXPECT_EQ(m3.getValue(1, 0), x31);
	EXPECT_EQ(m3.getValue(2, 0), x32);

	EXPECT_EQ(m3.getValue(0, 1), y30);
	EXPECT_EQ(m3.getValue(1, 1), y31);
	EXPECT_EQ(m3.getValue(2, 1), y32);

	EXPECT_EQ(m3.getValue(0, 2), z30);
	EXPECT_EQ(m3.getValue(1, 2), z31);
	EXPECT_EQ(m3.getValue(2, 2), z32);
}

TEST(Matrix3fTest, ProductNotCommutative)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2 = buildM2Ref();

	Matrix3f m3 = m2 * m1;
	const float x30 = x20Ref * x10Ref + y20Ref * x11Ref + z20Ref * x12Ref;
	const float x31 = x21Ref * x10Ref + y21Ref * x11Ref + z21Ref * x12Ref;
	const float x32 = x22Ref * x10Ref + y22Ref * x11Ref + z22Ref * x12Ref;
	const float y30 = x20Ref * y10Ref + y20Ref * y11Ref + z20Ref * y12Ref;
	const float y31 = x21Ref * y10Ref + y21Ref * y11Ref + z21Ref * y12Ref;
	const float y32 = x22Ref * y10Ref + y22Ref * y11Ref + z22Ref * y12Ref;
	const float z30 = x20Ref * z10Ref + y20Ref * z11Ref + z20Ref * z12Ref;
	const float z31 = x21Ref * z10Ref + y21Ref * z11Ref + z21Ref * z12Ref;
	const float z32 = x22Ref * z10Ref + y22Ref * z11Ref + z22Ref * z12Ref;

	EXPECT_EQ(m3.getValue(0, 0), x30);
	EXPECT_EQ(m3.getValue(1, 0), x31);
	EXPECT_EQ(m3.getValue(2, 0), x32);

	EXPECT_EQ(m3.getValue(0, 1), y30);
	EXPECT_EQ(m3.getValue(1, 1), y31);
	EXPECT_EQ(m3.getValue(2, 1), y32);

	EXPECT_EQ(m3.getValue(0, 2), z30);
	EXPECT_EQ(m3.getValue(1, 2), z31);
	EXPECT_EQ(m3.getValue(2, 2), z32);
}

TEST(Matrix3fTest, TransposeIdentity)
{
	Matrix3f identity = Matrix3f::identity();
	Matrix3f mTransposed = identity.transpose();

	EXPECT_EQ(mTransposed.getValue(0, 0), 1.0f);
	EXPECT_EQ(mTransposed.getValue(1, 0), 0.0f);
	EXPECT_EQ(mTransposed.getValue(2, 0), 0.0f);

	EXPECT_EQ(mTransposed.getValue(0, 1), 0.0f);
	EXPECT_EQ(mTransposed.getValue(1, 1), 1.0f);
	EXPECT_EQ(mTransposed.getValue(2, 1), 0.0f);

	EXPECT_EQ(mTransposed.getValue(0, 2), 0.0f);
	EXPECT_EQ(mTransposed.getValue(1, 2), 0.0f);
	EXPECT_EQ(mTransposed.getValue(2, 2), 1.0f);
}

TEST(Matrix3fTest, TransposeBasic)
{
	Matrix3f m = buildM1Ref();
	Matrix3f mTransposed = m.transpose();

	EXPECT_EQ(mTransposed.getValue(0, 0), x10Ref);
	EXPECT_EQ(mTransposed.getValue(1, 0), y10Ref);
	EXPECT_EQ(mTransposed.getValue(2, 0), z10Ref);

	EXPECT_EQ(mTransposed.getValue(0, 1), x11Ref);
	EXPECT_EQ(mTransposed.getValue(1, 1), y11Ref);
	EXPECT_EQ(mTransposed.getValue(2, 1), z11Ref);

	EXPECT_EQ(mTransposed.getValue(0, 2), x12Ref);
	EXPECT_EQ(mTransposed.getValue(1, 2), y12Ref);
	EXPECT_EQ(mTransposed.getValue(2, 2), z12Ref);
}

TEST(Matrix3fTest, Determinant)
{
	Matrix3f m = buildM1Ref();

	float det = m.determinant();
	constexpr float factor1 = y10Ref * z11Ref - y11Ref * z10Ref;
	constexpr float factor2 = y10Ref * z12Ref - y12Ref * z10Ref;
	constexpr float factor3 = y11Ref * z12Ref - z11Ref * y12Ref;

	constexpr float detRef = x10Ref * factor3 - x11Ref * factor2 + x12Ref * factor1;

	constexpr float epsilon = 0.002f;

	EXPECT_NEAR(det, detRef, epsilon);
}

TEST(Matrix3fTest, InverseIdentity)
{
	Matrix3f identity = Matrix3f::identity();
	Matrix3f mInverted = identity.inverse();

	EXPECT_EQ(mInverted.data[0][0], 1.0f);
	EXPECT_EQ(mInverted.data[1][0], 0.0f);
	EXPECT_EQ(mInverted.data[2][0], 0.0f);

	EXPECT_EQ(mInverted.data[0][1], 0.0f);
	EXPECT_EQ(mInverted.data[1][1], 1.0f);
	EXPECT_EQ(mInverted.data[2][1], 0.0f);

	EXPECT_EQ(mInverted.data[0][2], 0.0f);
	EXPECT_EQ(mInverted.data[1][2], 0.0f);
	EXPECT_EQ(mInverted.data[2][2], 1.0f);
}

TEST(Matrix3fTest, InverseBasic)
{
	Matrix3f m = buildM1Ref();

	Matrix3f mInverted = m.inverse();

	constexpr float adjugateX0 = +(y11Ref * z12Ref - z11Ref * y12Ref);
	constexpr float adjugateX1 = -(x11Ref * z12Ref - z11Ref * x12Ref);
	constexpr float adjugateX2 = +(x11Ref * y12Ref - y11Ref * x12Ref);

	constexpr float adjugateY0 = -(y10Ref * z12Ref - z10Ref * y12Ref);
	constexpr float adjugateY1 = +(x10Ref * z12Ref - z10Ref * x12Ref);
	constexpr float adjugateY2 = -(x10Ref * y12Ref - y10Ref * x12Ref);

	constexpr float adjugateZ0 = +(y10Ref * z11Ref - z10Ref * y11Ref);
	constexpr float adjugateZ1 = -(x10Ref * z11Ref - z10Ref * x11Ref);
	constexpr float adjugateZ2 = +(x10Ref * y11Ref - y10Ref * x11Ref);

	constexpr float determinant = x10Ref * adjugateX0 + y10Ref * adjugateX1 + z10Ref * adjugateX2;
	constexpr float oneOverDeterminant = 1.0f / determinant;

	constexpr float inverseX0 = oneOverDeterminant * adjugateX0;
	constexpr float inverseX1 = oneOverDeterminant * adjugateX1;
	constexpr float inverseX2 = oneOverDeterminant * adjugateX2;

	constexpr float inverseY0 = oneOverDeterminant * adjugateY0;
	constexpr float inverseY1 = oneOverDeterminant * adjugateY1;
	constexpr float inverseY2 = oneOverDeterminant * adjugateY2;

	constexpr float inverseZ0 = oneOverDeterminant * adjugateZ0;
	constexpr float inverseZ1 = oneOverDeterminant * adjugateZ1;
	constexpr float inverseZ2 = oneOverDeterminant * adjugateZ2;

	constexpr float epsilon = 1e-7f;

	EXPECT_NEAR(mInverted.getValue(0, 0), inverseX0, epsilon);
	EXPECT_NEAR(mInverted.getValue(1, 0), inverseX1, epsilon);
	EXPECT_NEAR(mInverted.getValue(2, 0), inverseX2, epsilon);

	EXPECT_NEAR(mInverted.getValue(0, 1), inverseY0, epsilon);
	EXPECT_NEAR(mInverted.getValue(1, 1), inverseY1, epsilon);
	EXPECT_NEAR(mInverted.getValue(2, 1), inverseY2, epsilon);

	EXPECT_NEAR(mInverted.getValue(0, 2), inverseZ0, epsilon);
	EXPECT_NEAR(mInverted.getValue(1, 2), inverseZ1, epsilon);
	EXPECT_NEAR(mInverted.getValue(2, 2), inverseZ2, epsilon);
}

TEST(Matrix3fTest, RowAccess)
{
	Matrix3f m = buildM1Ref();

	Vector3f r0 = m.getRow(0);
	EXPECT_EQ(r0.x, x10Ref);
	EXPECT_EQ(r0.y, y10Ref);
	EXPECT_EQ(r0.z, z10Ref);

	Vector3f r1 = m.getRow(1);
	EXPECT_EQ(r1.x, x11Ref);
	EXPECT_EQ(r1.y, y11Ref);
	EXPECT_EQ(r1.z, z11Ref);

	Vector3f r2 = m.getRow(2);
	EXPECT_EQ(r2.x, x12Ref);
	EXPECT_EQ(r2.y, y12Ref);
	EXPECT_EQ(r2.z, z12Ref);
}

TEST(Matrix3fTest, ColumnAccess)
{
	Matrix3f m = buildM1Ref();

	Vector3f c0 = m.getColumn(0);
	EXPECT_EQ(c0.x, x10Ref);
	EXPECT_EQ(c0.y, x11Ref);
	EXPECT_EQ(c0.z, x12Ref);

	Vector3f c1 = m.getColumn(1);
	EXPECT_EQ(c1.x, y10Ref);
	EXPECT_EQ(c1.y, y11Ref);
	EXPECT_EQ(c1.z, y12Ref);

	Vector3f c2 = m.getColumn(2);
	EXPECT_EQ(c2.x, z10Ref);
	EXPECT_EQ(c2.y, z11Ref);
	EXPECT_EQ(c2.z, z12Ref);
}

TEST(Matrix3fTest, Equality)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2 = buildM2Ref();

	EXPECT_TRUE(m1 == m1);
	EXPECT_FALSE(m1 == m2);
}

TEST(Matrix3fTest, Inequality)
{
	Matrix3f m1 = buildM1Ref();
	Matrix3f m2 = buildM2Ref();

	EXPECT_FALSE(m1 != m1);
	EXPECT_TRUE(m1 != m2);
}