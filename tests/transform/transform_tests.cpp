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
	EXPECT_EQ(matrix, Matrix4f::identity());
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

	EXPECT_EQ(matrix, matrixRef);
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

	constexpr float angle = 90.0f;
	transform.rotate(angle, 0.0f, 0.0f);

	const Matrix4f matrixRef = Matrix4f(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
}

TEST(TransformTests, RotateWorldX)
{
	Transform transform;

	constexpr float angle = 36.42f;
	const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
	const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
	transform.rotate(angle, 0.0f, 0.0f);

	const Matrix4f matrixRef = Matrix4f(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, angleCos, -angleSin, 0.0f,
		0.0f, angleSin, angleCos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
}

TEST(TransformTests, RotateWorldYSimple)
{
	Transform transform;

	constexpr float angle = 90.0f;
	transform.rotate(0.0f, angle, 0.0f);

	const Matrix4f matrixRef = Matrix4f(
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
}

TEST(TransformTests, RotateWorldY)
{
	Transform transform;

	constexpr float angle = 36.42f;
	const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
	const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
	transform.rotate(0.0f, angle, 0.0f);

	const Matrix4f matrixRef = Matrix4f(
		angleCos, 0.0f, angleSin, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-angleSin, 0.0f, angleCos, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
}

TEST(TransformTests, RotateWorldZSimple)
{
	Transform transform;

	constexpr float angle = 90.0f;
	transform.rotate(0.0f, angle, 0.0f);

	const Matrix4f matrixRef = Matrix4f(
		0.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
}

TEST(TransformTests, RotateWorldZ)
{
	Transform transform;

	constexpr float angle = 36.42f;
	const float angleCos = PrismaEngine::cos(degreesToRadians(angle));
	const float angleSin = PrismaEngine::sin(degreesToRadians(angle));
	transform.rotate(0.0f, 0.0f, angle);

	const Matrix4f matrixRef = Matrix4f(
		angleCos, -angleSin, 0.0f, 0.0f,
		angleSin, angleCos, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
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
			angleCos, -angleSin, 0.0f, 0.0f,
			angleSin, angleCos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}


	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleY));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleY));

		const Matrix4f rotationMatrix = Matrix4f(
			angleCos, 0.0f, angleSin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-angleSin, 0.0f, angleCos, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}


	{
		const float angleCos = PrismaEngine::cos(degreesToRadians(angleX));
		const float angleSin = PrismaEngine::sin(degreesToRadians(angleX));

		const Matrix4f rotationMatrix = Matrix4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, angleCos, -angleSin, 0.0f,
			0.0f, angleSin, angleCos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		matrixRef = rotationMatrix * matrixRef;
	}

	const Matrix4f& matrix = transform.getMatrix();

	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
}

TEST(TransformTests, SetRotationFloat)
{

}

TEST(TransformTests, SetRotationMatrix)
{

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
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
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
	EXPECT_NEAR(matrix.data[0][0], matrixRef.data[0][0], epsilon);
	EXPECT_NEAR(matrix.data[0][1], matrixRef.data[0][1], epsilon);
	EXPECT_NEAR(matrix.data[0][2], matrixRef.data[0][2], epsilon);
	EXPECT_NEAR(matrix.data[0][3], matrixRef.data[0][3], epsilon);

	EXPECT_NEAR(matrix.data[1][0], matrixRef.data[1][0], epsilon);
	EXPECT_NEAR(matrix.data[1][1], matrixRef.data[1][1], epsilon);
	EXPECT_NEAR(matrix.data[1][2], matrixRef.data[1][2], epsilon);
	EXPECT_NEAR(matrix.data[1][3], matrixRef.data[1][3], epsilon);

	EXPECT_NEAR(matrix.data[2][0], matrixRef.data[2][0], epsilon);
	EXPECT_NEAR(matrix.data[2][1], matrixRef.data[2][1], epsilon);
	EXPECT_NEAR(matrix.data[2][2], matrixRef.data[2][2], epsilon);
	EXPECT_NEAR(matrix.data[2][3], matrixRef.data[2][3], epsilon);

	EXPECT_NEAR(matrix.data[3][0], matrixRef.data[3][0], epsilon);
	EXPECT_NEAR(matrix.data[3][1], matrixRef.data[3][1], epsilon);
	EXPECT_NEAR(matrix.data[3][2], matrixRef.data[3][2], epsilon);
	EXPECT_NEAR(matrix.data[3][3], matrixRef.data[3][3], epsilon);
}

TEST(TransformTests, GetBasisVectorsIdentity)
{

}

TEST(TransformTests, GetBasisVectorsModified)
{

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

}