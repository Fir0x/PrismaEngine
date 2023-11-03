#include <gtest/gtest.h>

#include "core/maths/public/Matrix3.h"
#include "core/maths/public/Matrix4.h"
#include "core/maths/public/Vector3.h"
#include "core/maths/public/utils.h"
#include "scene/public/Transform.h"

using namespace PrismaEngine;

TEST(TransformTests, DefaultInitialization)
{
	Transform transform;
	const Matrix4f& matrix = transform.getMatrix();

	EXPECT_EQ(matrix.getValue(0,0), 1.0f);
	EXPECT_EQ(matrix.getValue(0,1), 0.0f);
	EXPECT_EQ(matrix.getValue(0,2), 0.0f);
	EXPECT_EQ(matrix.getValue(0,3), 0.0f);

	EXPECT_EQ(matrix.getValue(1,0), 0.0f);
	EXPECT_EQ(matrix.getValue(1,1), 1.0f);
	EXPECT_EQ(matrix.getValue(1,2), 0.0f);
	EXPECT_EQ(matrix.getValue(1,3), 0.0f);

	EXPECT_EQ(matrix.getValue(2,0), 0.0f);
	EXPECT_EQ(matrix.getValue(2,1), 0.0f);
	EXPECT_EQ(matrix.getValue(2,2), 1.0f);
	EXPECT_EQ(matrix.getValue(2,3), 0.0f);

	EXPECT_EQ(matrix.getValue(3,0), 0.0f);
	EXPECT_EQ(matrix.getValue(3,1), 0.0f);
	EXPECT_EQ(matrix.getValue(3,2), 0.0f);
	EXPECT_EQ(matrix.getValue(3,3), 1.0f);
}

TEST(TransformTests, InitializationWithPosition)
{
	constexpr float x = 1.2f;
	constexpr float y = 5.3f;
	constexpr float z = -3.4f;

	Transform transform(Vector3f(x, y, z));
	const Matrix4f matrixRef = Matrix4f(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	EXPECT_EQ(matrix.getValue(0,0), matrixRef.getValue(0,0));
	EXPECT_EQ(matrix.getValue(0,1), matrixRef.getValue(0,1));
	EXPECT_EQ(matrix.getValue(0,2), matrixRef.getValue(0,2));
	EXPECT_EQ(matrix.getValue(0,3), matrixRef.getValue(0,3));

	EXPECT_EQ(matrix.getValue(1,0), matrixRef.getValue(1,0));
	EXPECT_EQ(matrix.getValue(1,1), matrixRef.getValue(1,1));
	EXPECT_EQ(matrix.getValue(1,2), matrixRef.getValue(1,2));
	EXPECT_EQ(matrix.getValue(1,3), matrixRef.getValue(1,3));

	EXPECT_EQ(matrix.getValue(2,0), matrixRef.getValue(2,0));
	EXPECT_EQ(matrix.getValue(2,1), matrixRef.getValue(2,1));
	EXPECT_EQ(matrix.getValue(2,2), matrixRef.getValue(2,2));
	EXPECT_EQ(matrix.getValue(2,3), matrixRef.getValue(2,3));

	EXPECT_EQ(matrix.getValue(3,0), matrixRef.getValue(3,0));
	EXPECT_EQ(matrix.getValue(3,1), matrixRef.getValue(3,1));
	EXPECT_EQ(matrix.getValue(3,2), matrixRef.getValue(3,2));
	EXPECT_EQ(matrix.getValue(3,3), matrixRef.getValue(3,3));
}

TEST(TransformTests, Translation)
{
	Transform transform;

	constexpr float x = 1.2f;
	constexpr float y = 5.3f;
	constexpr float z = -3.4f;
	transform.translate(x, y, z);

	const Matrix4f matrixRef = Matrix4f(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	EXPECT_EQ(matrix, matrixRef);
}

TEST(TransformTests, RotateWorldXSimple)
{
	Transform transform;
	Matrix4f matrixRef = Matrix4f::identity();

	{
		constexpr float angle = 90.0f;
		transform.rotate(angle, 0.0f, 0.0f);

		matrixRef = matrixRef * Matrix4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}

	{
		constexpr float angle = 90.0f;
		transform.rotate(angle, 0.0f, 0.0f);

		matrixRef = matrixRef * Matrix4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}
}

TEST(TransformTests, RotateWorldX)
{
	Transform transform;
	Matrix4f matrixRef = Matrix4f::identity();

	{
		constexpr float angle = 36.42f;
		const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
		transform.rotate(angle, 0.0f, 0.0f);

		matrixRef = matrixRef * Matrix4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, angleCos, angleSin, 0.0f,
			0.0f, -angleSin, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}

	{
		constexpr float angle = -13.21f;
		const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
		transform.rotate(angle, 0.0f, 0.0f);

		matrixRef = matrixRef * Matrix4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, angleCos, angleSin, 0.0f,
			0.0f, -angleSin, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}
}

TEST(TransformTests, RotateWorldYSimple)
{
	Transform transform;
	Matrix4f matrixRef = Matrix4f::identity();

	{
		constexpr float angle = 90.0f;
		transform.rotate(0.0f, angle, 0.0f);

		matrixRef = matrixRef * Matrix4f(
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}

	{
		constexpr float angle = 90.0f;
		transform.rotate(0.0f, angle, 0.0f);

		matrixRef = matrixRef * Matrix4f(
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}
}

TEST(TransformTests, RotateWorldY)
{
	Transform transform;
	Matrix4f matrixRef = Matrix4f::identity();

	{
		constexpr float angle = 36.42f;
		const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
		transform.rotate(0.0f, angle, 0.0f);

		matrixRef = matrixRef * Matrix4f(
			angleCos, 0.0f, -angleSin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			angleSin, 0.0f, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;

		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}

	{
		constexpr float angle = -13.21f;
		const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
		transform.rotate(0.0f, angle, 0.0f);

		matrixRef = matrixRef * Matrix4f(
			angleCos, 0.0f, -angleSin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			angleSin, 0.0f, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;

		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}
}

TEST(TransformTests, RotateWorldZSimple)
{
	Transform transform;
	Matrix4f matrixRef = Matrix4f::identity();

	{
		constexpr float angle = 90.0f;
		transform.rotate(0.0f, 0.0f, angle);

		matrixRef = matrixRef * Matrix4f(
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}

	{
		constexpr float angle = 90.0f;
		transform.rotate(0.0f, 0.0f, angle);

		matrixRef = matrixRef * Matrix4f(
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}
}

TEST(TransformTests, RotateWorldZ)
{
	Transform transform;
	Matrix4f matrixRef = Matrix4f::identity();

	{
		constexpr float angle = 36.42f;
		const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
		transform.rotate(0.0f, 0.0f, angle);

		matrixRef = matrixRef * Matrix4f(
			angleCos, angleSin, 0.0f, 0.0f,
			-angleSin, angleCos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}

	{
		constexpr float angle = -13.21f;
		const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
		transform.rotate(0.0f, 0.0f, angle);

		matrixRef = matrixRef * Matrix4f(
			angleCos, angleSin, 0.0f, 0.0f,
			-angleSin, angleCos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}
}

TEST(TransformTests, RotateWorldCombine)
{
	Transform transform;

	constexpr float angleX = 23.5f;
	constexpr float angleY = 75.3f;
	constexpr float angleZ = -3.21f;
	transform.rotate(angleX, angleY, angleZ);

	Matrix4f matrixRef = Matrix4f::identity();
	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleZ));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleZ));

		const Matrix4f rotationMatrix = Matrix4f(
			angleCos, angleSin, 0.0f, 0.0f,
			-angleSin, angleCos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}


	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleY));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleY));

		const Matrix4f rotationMatrix = Matrix4f(
			angleCos, 0.0f, -angleSin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			angleSin, 0.0f, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}


	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleX));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleX));

		const Matrix4f rotationMatrix = Matrix4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, angleCos, angleSin, 0.0f,
			0.0f, -angleSin, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}

	transform.rotate(angleX, angleY, angleZ);

	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleZ));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleZ));

		const Matrix4f rotationMatrix = Matrix4f(
			angleCos, angleSin, 0.0f, 0.0f,
			-angleSin, angleCos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}


	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleY));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleY));

		const Matrix4f rotationMatrix = Matrix4f(
			angleCos, 0.0f, -angleSin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			angleSin, 0.0f, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}


	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleX));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleX));

		const Matrix4f rotationMatrix = Matrix4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, angleCos, angleSin, 0.0f,
			0.0f, -angleSin, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
	EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
	EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
	EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

	EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
	EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
	EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
	EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

	EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
	EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
	EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
	EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

	EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
	EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
	EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
	EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
}

TEST(TransformTests, SetRotationFloat)
{
	Transform transform;
	Matrix4f matrixRef = Matrix4f::identity();

	constexpr float angleX = 23.5f;
	constexpr float angleY = 75.3f;
	constexpr float angleZ = -3.21f;
	transform.setRotation(angleX, angleY, angleZ);

	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleZ));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleZ));

		const Matrix4f rotationMatrix = Matrix4f(
			angleCos, angleSin, 0.0f, 0.0f,
			-angleSin, angleCos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}


	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleY));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleY));

		const Matrix4f rotationMatrix = Matrix4f(
			angleCos, 0.0f, -angleSin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			angleSin, 0.0f, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}


	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleX));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleX));

		const Matrix4f rotationMatrix = Matrix4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, angleCos, angleSin, 0.0f,
			0.0f, -angleSin, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}

	{
		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}

	transform.setRotation(angleX, angleY, angleZ);

	{
		const Matrix4f& matrix = transform.getMatrix();

		constexpr float epsilon = 1e-5f;
		EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
		EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
		EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
		EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

		EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
		EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
		EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
		EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

		EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
		EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
		EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
		EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

		EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
		EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
		EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
		EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
	}
}

TEST(TransformTests, SetRotationMatrix)
{
	Vector3f position(14.2f, -32.16f, 0.235f);
	Transform transform(position);

	Vector3f axisX(0.4507615f, -0.3335759f, 0.8279741f);
	Vector3f axisY(-0.0102292f, 0.9255608f, 0.3784608f);
	Vector3f axisZ(-0.8925858f, -0.1790651f, 0.4137949f);
	Matrix3f rotationMatrix(axisX, axisY, axisZ);

	transform.setRotation(rotationMatrix);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.getValue(0,0), axisX.x, epsilon);
	EXPECT_NEAR(matrix.getValue(0,1), axisX.y, epsilon);
	EXPECT_NEAR(matrix.getValue(0,2), axisX.z, epsilon);
	EXPECT_NEAR(matrix.getValue(0,3), 0.0f, epsilon);

	EXPECT_NEAR(matrix.getValue(1,0), axisY.x, epsilon);
	EXPECT_NEAR(matrix.getValue(1,1), axisY.y, epsilon);
	EXPECT_NEAR(matrix.getValue(1,2), axisY.z, epsilon);
	EXPECT_NEAR(matrix.getValue(1,3), 0.0f, epsilon);

	EXPECT_NEAR(matrix.getValue(2,0), axisZ.x, epsilon);
	EXPECT_NEAR(matrix.getValue(2,1), axisZ.y, epsilon);
	EXPECT_NEAR(matrix.getValue(2,2), axisZ.z, epsilon);
	EXPECT_NEAR(matrix.getValue(2,3), 0.0f, epsilon);

	EXPECT_NEAR(matrix.getValue(3,0), position.x, epsilon);
	EXPECT_NEAR(matrix.getValue(3,1), position.y, epsilon);
	EXPECT_NEAR(matrix.getValue(3,2), position.z, epsilon);
	EXPECT_NEAR(matrix.getValue(3,3), 1.0f, epsilon);
}

TEST(TransformTests, ScaleUniform)
{
	Transform transform;

	constexpr float scale = 2.0f;
	transform.scale(scale, scale, scale);

	const Matrix4f matrixRef = Matrix4f(
		scale, 0.0f, 0.0f, 0.0f,
		0.0f, scale, 0.0f, 0.0f,
		0.0f, 0.0f, scale, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
	EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
	EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
	EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

	EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
	EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
	EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
	EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

	EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
	EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
	EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
	EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

	EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
	EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
	EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
	EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
}

TEST(TransformTests, ScaleNonUniform)
{
	Transform transform;

	constexpr float scaleX = 2.0f;
	constexpr float scaleY = -1.3f;
	constexpr float scaleZ = 42.3f;
	transform.scale(scaleX, scaleY, scaleZ);

	const Matrix4f matrixRef = Matrix4f(
		scaleX, 0.0f, 0.0f, 0.0f,
		0.0f, scaleY, 0.0f, 0.0f,
		0.0f, 0.0f, scaleZ, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.getValue(0,0), matrixRef.getValue(0,0), epsilon);
	EXPECT_NEAR(matrix.getValue(0,1), matrixRef.getValue(0,1), epsilon);
	EXPECT_NEAR(matrix.getValue(0,2), matrixRef.getValue(0,2), epsilon);
	EXPECT_NEAR(matrix.getValue(0,3), matrixRef.getValue(0,3), epsilon);

	EXPECT_NEAR(matrix.getValue(1,0), matrixRef.getValue(1,0), epsilon);
	EXPECT_NEAR(matrix.getValue(1,1), matrixRef.getValue(1,1), epsilon);
	EXPECT_NEAR(matrix.getValue(1,2), matrixRef.getValue(1,2), epsilon);
	EXPECT_NEAR(matrix.getValue(1,3), matrixRef.getValue(1,3), epsilon);

	EXPECT_NEAR(matrix.getValue(2,0), matrixRef.getValue(2,0), epsilon);
	EXPECT_NEAR(matrix.getValue(2,1), matrixRef.getValue(2,1), epsilon);
	EXPECT_NEAR(matrix.getValue(2,2), matrixRef.getValue(2,2), epsilon);
	EXPECT_NEAR(matrix.getValue(2,3), matrixRef.getValue(2,3), epsilon);

	EXPECT_NEAR(matrix.getValue(3,0), matrixRef.getValue(3,0), epsilon);
	EXPECT_NEAR(matrix.getValue(3,1), matrixRef.getValue(3,1), epsilon);
	EXPECT_NEAR(matrix.getValue(3,2), matrixRef.getValue(3,2), epsilon);
	EXPECT_NEAR(matrix.getValue(3,3), matrixRef.getValue(3,3), epsilon);
}

TEST(TransformTests, GetBasisVectorsIdentity)
{
	Transform transform;

	{
		const Vector3f axis = transform.getRight();

		EXPECT_EQ(axis.x, 1.0f);
		EXPECT_EQ(axis.y, 0.0f);
		EXPECT_EQ(axis.z, 0.0f);
	}

	{
		const Vector3f axis = transform.getUp();

		EXPECT_EQ(axis.x, 0.0f);
		EXPECT_EQ(axis.y, 1.0f);
		EXPECT_EQ(axis.z, 0.0f);
	}

	{
		const Vector3f axis = transform.getForward();

		EXPECT_EQ(axis.x, 0.0f);
		EXPECT_EQ(axis.y, 0.0f);
		EXPECT_EQ(axis.z, 1.0f);
	}
}

TEST(TransformTests, GetBasisVectorsModified)
{
	Vector3f position(14.2f, -32.16f, 0.235f);
	Transform transform(position);

	Vector3f axisX(0.4507615f, -0.3335759f, 0.8279741f);
	Vector3f axisY(-0.0102292f, 0.9255608f, 0.3784608f);
	Vector3f axisZ(-0.8925858f, -0.1790651f, 0.4137949f);
	Matrix3f rotationMatrix(axisX, axisY, axisZ);

	transform.setRotation(rotationMatrix);

	constexpr float epsilon = 1e-5f;
	{
		const Vector3f axis = transform.getRight();

		EXPECT_NEAR(axis.x, axisX.x, epsilon);
		EXPECT_NEAR(axis.y, axisX.y, epsilon);
		EXPECT_NEAR(axis.z, axisX.z, epsilon);
	}

	{
		const Vector3f axis = transform.getUp();

		EXPECT_NEAR(axis.x, axisY.x, epsilon);
		EXPECT_NEAR(axis.y, axisY.y, epsilon);
		EXPECT_NEAR(axis.z, axisY.z, epsilon);
	}

	{
		const Vector3f axis = transform.getForward();

		EXPECT_NEAR(axis.x, axisZ.x, epsilon);
		EXPECT_NEAR(axis.y, axisZ.y, epsilon);
		EXPECT_NEAR(axis.z, axisZ.z, epsilon);
	}
}

TEST(TransformTests, GetPosition)
{
	const Vector3f positionRef(1.2f, -0.36f, 74.12f);
	Transform transform(positionRef);

	const Vector3f position = transform.getPosition();

	EXPECT_EQ(position.x, positionRef.x);
	EXPECT_EQ(position.y, positionRef.y);
	EXPECT_EQ(position.z, positionRef.z);
}

TEST(TransformTests, GetRotation)
{
	Vector3f position(14.2f, -32.16f, 0.235f);
	Transform transform(position);

	Vector3f axisX(0.4507615f, -0.3335759f, 0.8279741f);
	Vector3f axisY(-0.0102292f, 0.9255608f, 0.3784608f);
	Vector3f axisZ(-0.8925858f, -0.1790651f, 0.4137949f);
	Matrix3f rotationMatrixRef(axisX, axisY, axisZ);

	transform.setRotation(rotationMatrixRef);

	const Matrix3f rotationMatrix = transform.getRotation();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(rotationMatrix.getValue(0,0), rotationMatrixRef.getValue(0,0), epsilon);
	EXPECT_NEAR(rotationMatrix.getValue(0,1), rotationMatrixRef.getValue(0,1), epsilon);
	EXPECT_NEAR(rotationMatrix.getValue(0,2), rotationMatrixRef.getValue(0,2), epsilon);

	EXPECT_NEAR(rotationMatrix.getValue(1,0), rotationMatrixRef.getValue(1,0), epsilon);
	EXPECT_NEAR(rotationMatrix.getValue(1,1), rotationMatrixRef.getValue(1,1), epsilon);
	EXPECT_NEAR(rotationMatrix.getValue(1,2), rotationMatrixRef.getValue(1,2), epsilon);

	EXPECT_NEAR(rotationMatrix.getValue(2,0), rotationMatrixRef.getValue(2,0), epsilon);
	EXPECT_NEAR(rotationMatrix.getValue(2,1), rotationMatrixRef.getValue(2,1), epsilon);
	EXPECT_NEAR(rotationMatrix.getValue(2,2), rotationMatrixRef.getValue(2,2), epsilon);
}