#include <gtest/gtest.h>

#include "core/maths/public/Matrix3.h"

using namespace PrismaEngine;

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
	constexpr float x0 = 0.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;

	Vector3f x(x0, x1, x2);
	Vector3f y(y0, y1, y2);
	Vector3f z(z0, z1, z2);

	Matrix3f m = Matrix3f::fromPlane(x, y, z);

	EXPECT_EQ(m.getValue(0, 0), x0);
	EXPECT_EQ(m.getValue(1, 0), x1);
	EXPECT_EQ(m.getValue(2, 0), x2);

	EXPECT_EQ(m.getValue(0, 1), y0);
	EXPECT_EQ(m.getValue(1, 1), y1);
	EXPECT_EQ(m.getValue(2, 1), y2);

	EXPECT_EQ(m.getValue(0, 2), z0);
	EXPECT_EQ(m.getValue(1, 2), z1);
	EXPECT_EQ(m.getValue(2, 2), z2);
}

TEST(Matrix3fTest, ReferenceInitialization)
{
	constexpr float x0 = 0.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;

	Vector3f x(x0, x1, x2);
	Vector3f y(y0, y1, y2);
	Vector3f z(z0, z1, z2);

	Matrix3f m1 = Matrix3f::fromPlane(x, y, z);
	Matrix3f m2(m1);

	EXPECT_EQ(m2.getValue(0, 0), x0);
	EXPECT_EQ(m2.getValue(1, 0), x1);
	EXPECT_EQ(m2.getValue(2, 0), x2);

	EXPECT_EQ(m2.getValue(0, 1), y0);
	EXPECT_EQ(m2.getValue(1, 1), y1);
	EXPECT_EQ(m2.getValue(2, 1), y2);

	EXPECT_EQ(m2.getValue(0, 2), z0);
	EXPECT_EQ(m2.getValue(1, 2), z1);
	EXPECT_EQ(m2.getValue(2, 2), z2);
}

TEST(Matrix3fTest, Add)
{
	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;

	Vector3f x1(x10, x11, x12);
	Vector3f y1(y10, y11, y12);
	Vector3f z1(z10, z11, z12);

	Matrix3f m1 = Matrix3f::fromPlane(x1, y1, z1);

	constexpr float x20 = 64.52f;
	constexpr float x21 = -6.32f;
	constexpr float x22 = -2.64f;
	constexpr float y20 = 4.6f;
	constexpr float y21 = 3.64f;
	constexpr float y22 = 12.345f;
	constexpr float z20 = -893.15f;
	constexpr float z21 = 2.34f;
	constexpr float z22 = -72.2f;

	Vector3f x2(x20, x21, x22);
	Vector3f y2(y20, y21, y22);
	Vector3f z2(z20, z21, z22);

	Matrix3f m2 = Matrix3f::fromPlane(x2, y2, z2);

	{
		Matrix3f m3 = m1 + m2;

		EXPECT_EQ(m3.getValue(0, 0), x10 + x20);
		EXPECT_EQ(m3.getValue(1, 0), x11 + x21);
		EXPECT_EQ(m3.getValue(2, 0), x12 + x22);

		EXPECT_EQ(m3.getValue(0, 1), y10 + y20);
		EXPECT_EQ(m3.getValue(1, 1), y11 + y21);
		EXPECT_EQ(m3.getValue(2, 1), y12 + y22);

		EXPECT_EQ(m3.getValue(0, 2), z10 + z20);
		EXPECT_EQ(m3.getValue(1, 2), z11 + z21);
		EXPECT_EQ(m3.getValue(2, 2), z12 + z22);
	}

	{
		Matrix3f m3 = m2 + m1;

		EXPECT_EQ(m3.getValue(0, 0), x10 + x20);
		EXPECT_EQ(m3.getValue(1, 0), x11 + x21);
		EXPECT_EQ(m3.getValue(2, 0), x12 + x22);

		EXPECT_EQ(m3.getValue(0, 1), y10 + y20);
		EXPECT_EQ(m3.getValue(1, 1), y11 + y21);
		EXPECT_EQ(m3.getValue(2, 1), y12 + y22);

		EXPECT_EQ(m3.getValue(0, 2), z10 + z20);
		EXPECT_EQ(m3.getValue(1, 2), z11 + z21);
		EXPECT_EQ(m3.getValue(2, 2), z12 + z22);
	}
}

TEST(Matrix3fTest, Subtract)
{
	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;

	Vector3f x1(x10, x11, x12);
	Vector3f y1(y10, y11, y12);
	Vector3f z1(z10, z11, z12);

	Matrix3f m1 = Matrix3f::fromPlane(x1, y1, z1);

	constexpr float x20 = 64.52f;
	constexpr float x21 = -6.32f;
	constexpr float x22 = -2.64f;
	constexpr float y20 = 4.6f;
	constexpr float y21 = 3.64f;
	constexpr float y22 = 12.345f;
	constexpr float z20 = -893.15f;
	constexpr float z21 = 2.34f;
	constexpr float z22 = -72.2f;

	Vector3f x2(x20, x21, x22);
	Vector3f y2(y20, y21, y22);
	Vector3f z2(z20, z21, z22);

	Matrix3f m2 = Matrix3f::fromPlane(x2, y2, z2);

	{
		Matrix3f m3 = m1 - m2;

		EXPECT_EQ(m3.getValue(0, 0), x10 - x20);
		EXPECT_EQ(m3.getValue(1, 0), x11 - x21);
		EXPECT_EQ(m3.getValue(2, 0), x12 - x22);

		EXPECT_EQ(m3.getValue(0, 1), y10 - y20);
		EXPECT_EQ(m3.getValue(1, 1), y11 - y21);
		EXPECT_EQ(m3.getValue(2, 1), y12 - y22);

		EXPECT_EQ(m3.getValue(0, 2), z10 - z20);
		EXPECT_EQ(m3.getValue(1, 2), z11 - z21);
		EXPECT_EQ(m3.getValue(2, 2), z12 - z22);
	}

	{
		Matrix3f m3 = m2 - m1;

		EXPECT_EQ(m3.getValue(0, 0), x20 - x10);
		EXPECT_EQ(m3.getValue(1, 0), x21 - x11);
		EXPECT_EQ(m3.getValue(2, 0), x22 - x12);

		EXPECT_EQ(m3.getValue(0, 1), y20 - y10);
		EXPECT_EQ(m3.getValue(1, 1), y21 - y11);
		EXPECT_EQ(m3.getValue(2, 1), y22 - y12);

		EXPECT_EQ(m3.getValue(0, 2), z20 - z10);
		EXPECT_EQ(m3.getValue(1, 2), z21 - z11);
		EXPECT_EQ(m3.getValue(2, 2), z22 - z12);
	}
}

TEST(Matrix3fTest, Product)
{

	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;

	Vector3f x1(x10, x11, x12);
	Vector3f y1(y10, y11, y12);
	Vector3f z1(z10, z11, z12);

	Matrix3f m1 = Matrix3f::fromPlane(x1, y1, z1);

	{
		Matrix3f identity = Matrix3f::identity();

		{
			Matrix3f m3 = m1 * identity;
			EXPECT_EQ(m3.getValue(0, 0), x10);
			EXPECT_EQ(m3.getValue(1, 0), x11);
			EXPECT_EQ(m3.getValue(2, 0), x12);

			EXPECT_EQ(m3.getValue(0, 1), y10);
			EXPECT_EQ(m3.getValue(1, 1), y11);
			EXPECT_EQ(m3.getValue(2, 1), y12);

			EXPECT_EQ(m3.getValue(0, 2), z10);
			EXPECT_EQ(m3.getValue(1, 2), z11);
			EXPECT_EQ(m3.getValue(2, 2), z12);
		}

		{
			Matrix3f m3 = identity * m1;
			EXPECT_EQ(m3.getValue(0, 0), x10);
			EXPECT_EQ(m3.getValue(1, 0), x11);
			EXPECT_EQ(m3.getValue(2, 0), x12);

			EXPECT_EQ(m3.getValue(0, 1), y10);
			EXPECT_EQ(m3.getValue(1, 1), y11);
			EXPECT_EQ(m3.getValue(2, 1), y12);

			EXPECT_EQ(m3.getValue(0, 2), z10);
			EXPECT_EQ(m3.getValue(1, 2), z11);
			EXPECT_EQ(m3.getValue(2, 2), z12);
		}
	}

	{
		constexpr float x20 = 64.52f;
		constexpr float x21 = -6.32f;
		constexpr float x22 = -2.64f;
		constexpr float y20 = 4.6f;
		constexpr float y21 = 3.64f;
		constexpr float y22 = 12.345f;
		constexpr float z20 = -893.15f;
		constexpr float z21 = 2.34f;
		constexpr float z22 = -72.2f;

		Vector3f x2(x20, x21, x22);
		Vector3f y2(y20, y21, y22);
		Vector3f z2(z20, z21, z22);

		Matrix3f m2 = Matrix3f::fromPlane(x2, y2, z2);

		{
			Matrix3f m3 = m1 * m2;
			const float x30 = x10 * x20 + y10 * x21 + z10 * x22;
			const float x31 = x11 * x20 + y11 * x21 + z11 * x22;
			const float x32 = x12 * x20 + y12 * x21 + z12 * x22;
			const float y30 = x10 * y20 + y10 * y21 + z10 * y22;
			const float y31 = x11 * y20 + y11 * y21 + z11 * y22;
			const float y32 = x12 * y20 + y12 * y21 + z12 * y22;
			const float z30 = x10 * z20 + y10 * z21 + z10 * z22;
			const float z31 = x11 * z20 + y11 * z21 + z11 * z22;
			const float z32 = x12 * z20 + y12 * z21 + z12 * z22;

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


		{
			Matrix3f m3 = m2 * m1;
			const float x30 = x20 * x10 + y20 * x11 + z20 * x12;
			const float x31 = x21 * x10 + y21 * x11 + z21 * x12;
			const float x32 = x22 * x10 + y22 * x11 + z22 * x12;
			const float y30 = x20 * y10 + y20 * y11 + z20 * y12;
			const float y31 = x21 * y10 + y21 * y11 + z21 * y12;
			const float y32 = x22 * y10 + y22 * y11 + z22 * y12;
			const float z30 = x20 * z10 + y20 * z11 + z20 * z12;
			const float z31 = x21 * z10 + y21 * z11 + z21 * z12;
			const float z32 = x22 * z10 + y22 * z11 + z22 * z12;

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
	}
}

TEST(Matrix3fTest, Transpose)
{
	{
		Vector3f x(1.0f, 0.0f, 0.0f);
		Vector3f y(0.0f, 1.0f, 0.0f);
		Vector3f z(0.0f, 0.0f, 1.0f);

		Matrix3f m = Matrix3f::fromPlane(x, y, z);
		Matrix3f mTransposed = m.transpose();

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

	{
		constexpr float x0 = 0.0f;
		constexpr float x1 = 2.54f;
		constexpr float x2 = -3.6f;
		constexpr float y0 = -23.1f;
		constexpr float y1 = -4.354f;
		constexpr float y2 = -26.41f;
		constexpr float z0 = 285.15f;
		constexpr float z1 = -87.7f;
		constexpr float z2 = 354.5f;

		Vector3f x(x0, x1, x2);
		Vector3f y(y0, y1, y2);
		Vector3f z(z0, z1, z2);

		Matrix3f m = Matrix3f::fromPlane(x, y, z);
		Matrix3f mTransposed = m.transpose();

		EXPECT_EQ(mTransposed.getValue(0, 0), x0);
		EXPECT_EQ(mTransposed.getValue(1, 0), y0);
		EXPECT_EQ(mTransposed.getValue(2, 0), z0);

		EXPECT_EQ(mTransposed.getValue(0, 1), x1);
		EXPECT_EQ(mTransposed.getValue(1, 1), y1);
		EXPECT_EQ(mTransposed.getValue(2, 1), z1);

		EXPECT_EQ(mTransposed.getValue(0, 2), x2);
		EXPECT_EQ(mTransposed.getValue(1, 2), y2);
		EXPECT_EQ(mTransposed.getValue(2, 2), z2);
	}
}

TEST(Matrix3fTest, Determinant)
{
	constexpr float x0 = 1.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;

	Vector3f x(x0, x1, x2);
	Vector3f y(y0, y1, y2);
	Vector3f z(z0, z1, z2);

	Matrix3f m = Matrix3f::fromPlane(x, y, z);

	float det = m.determinant();
	constexpr float factor1 = y0 * z1 - y1 * z0;
	constexpr float factor2 = y0 * z2 - y2 * z0;
	constexpr float factor3 = y1 * z2 - z1 * y2;

	constexpr float detRef = x0 * factor3 - x1 * factor2 + x2 * factor1;

	constexpr float epsilon = 0.002;

	EXPECT_NEAR(det, detRef, epsilon);
}

TEST(Matrix3fTest, Inverse)
{
	constexpr float x0 = 1.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;

	Vector3f x(x0, x1, x2);
	Vector3f y(y0, y1, y2);
	Vector3f z(z0, z1, z2);

	Matrix3f m = Matrix3f::fromPlane(x, y, z);

	Matrix3f mInverted = m.inverse();

	constexpr float adjugateX0 = +(y1 * z2 - z1 * y2);
	constexpr float adjugateX1 = -(x1 * z2 - z1 * x2);
	constexpr float adjugateX2 = +(x1 * y2 - y1 * x2);

	constexpr float adjugateY0 = -(y0 * z2 - z0 * y2);
	constexpr float adjugateY1 = +(x0 * z2 - z0 * x2);
	constexpr float adjugateY2 = -(x0 * y2 - y0 * x2);

	constexpr float adjugateZ0 = +(y0 * z1 - z0 * y1);
	constexpr float adjugateZ1 = -(x0 * z1 - z0 * x1);
	constexpr float adjugateZ2 = +(x0 * y1 - y0 * x1);

	constexpr float determinant = x0 * adjugateX0 + y0 * adjugateX1 + z0 * adjugateX2;
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

	constexpr float epsilon = 1e-8;

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
	constexpr float x0 = 1.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;

	Vector3f x(x0, x1, x2);
	Vector3f y(y0, y1, y2);
	Vector3f z(z0, z1, z2);

	Matrix3f m = Matrix3f::fromPlane(x, y, z);

	Vector3f r0 = m.getRow(0);
	EXPECT_EQ(r0.x, x0);
	EXPECT_EQ(r0.y, y0);
	EXPECT_EQ(r0.z, z0);

	Vector3f r1 = m.getRow(1);
	EXPECT_EQ(r1.x, x1);
	EXPECT_EQ(r1.y, y1);
	EXPECT_EQ(r1.z, z1);

	Vector3f r2 = m.getRow(2);
	EXPECT_EQ(r2.x, x2);
	EXPECT_EQ(r2.y, y2);
	EXPECT_EQ(r2.z, z2);
}

TEST(Matrix3fTest, ColumnAccess)
{

	constexpr float x0 = 1.0f;
	constexpr float x1 = 2.54f;
	constexpr float x2 = -3.6f;
	constexpr float y0 = -23.1f;
	constexpr float y1 = -4.354f;
	constexpr float y2 = -26.41f;
	constexpr float z0 = 285.15f;
	constexpr float z1 = -87.7f;
	constexpr float z2 = 354.5f;

	Vector3f x(x0, x1, x2);
	Vector3f y(y0, y1, y2);
	Vector3f z(z0, z1, z2);

	Matrix3f m = Matrix3f::fromPlane(x, y, z);

	Vector3f c0 = m.getColumn(0);
	EXPECT_EQ(c0.x, x0);
	EXPECT_EQ(c0.y, x1);
	EXPECT_EQ(c0.z, x2);

	Vector3f c1 = m.getColumn(1);
	EXPECT_EQ(c1.x, y0);
	EXPECT_EQ(c1.y, y1);
	EXPECT_EQ(c1.z, y2);

	Vector3f c2 = m.getColumn(2);
	EXPECT_EQ(c2.x, z0);
	EXPECT_EQ(c2.y, z1);
	EXPECT_EQ(c2.z, z2);
}

TEST(Matrix3fTest, Equality)
{
	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;

	Vector3f x1(x10, x11, x12);
	Vector3f y1(y10, y11, y12);
	Vector3f z1(z10, z11, z12);

	Matrix3f m1 = Matrix3f::fromPlane(x1, y1, z1);

	constexpr float x20 = 64.52f;
	constexpr float x21 = -6.32f;
	constexpr float x22 = -2.64f;
	constexpr float y20 = 4.6f;
	constexpr float y21 = 3.64f;
	constexpr float y22 = 12.345f;
	constexpr float z20 = -893.15f;
	constexpr float z21 = 2.34f;
	constexpr float z22 = -72.2f;

	Vector3f x2(x20, x21, x22);
	Vector3f y2(y20, y21, y22);
	Vector3f z2(z20, z21, z22);

	Matrix3f m2(x2, y2, z2);

	EXPECT_TRUE(m1 == m1);
	EXPECT_FALSE(m1 == m2);
}

TEST(Matrix3fTest, Inequality)
{
	constexpr float x10 = 0.0f;
	constexpr float x11 = 2.54f;
	constexpr float x12 = -3.6f;
	constexpr float y10 = -23.1f;
	constexpr float y11 = -4.354f;
	constexpr float y12 = -26.41f;
	constexpr float z10 = 285.15f;
	constexpr float z11 = -87.7f;
	constexpr float z12 = 354.5f;

	Vector3f x1(x10, x11, x12);
	Vector3f y1(y10, y11, y12);
	Vector3f z1(z10, z11, z12);

	Matrix3f m1 = Matrix3f::fromPlane(x1, y1, z1);

	constexpr float x20 = 64.52f;
	constexpr float x21 = -6.32f;
	constexpr float x22 = -2.64f;
	constexpr float y20 = 4.6f;
	constexpr float y21 = 3.64f;
	constexpr float y22 = 12.345f;
	constexpr float z20 = -893.15f;
	constexpr float z21 = 2.34f;
	constexpr float z22 = -72.2f;

	Vector3f x2(x20, x21, x22);
	Vector3f y2(y20, y21, y22);
	Vector3f z2(z20, z21, z22);

	Matrix3f m2 = Matrix3f::fromPlane(x2, y2, z2);

	EXPECT_FALSE(m1 != m1);
	EXPECT_TRUE(m1 != m2);
}