#include <gtest/gtest.h>

#include "core/maths/public/Quaternion.h"

namespace PrismaEngineTest
{
	constexpr float epsilon = 1e-6f;

	static constexpr float deg2rad(float x)
	{
		constexpr float conversion = 3.14159265358979323848f / 180.0f;
		return x * conversion;
	}

	static constexpr float rad2deg(float x)
	{
		constexpr float conversion = 180.0f / 3.14159265358979323848f;
		return x * conversion;
	}

	using namespace PrismaEngine;

	// Ref Euler: X=41 Y=37 Z=-23
	constexpr float rotationX = 0.2661885f;
	constexpr float rotationY = 0.3574559f;
	constexpr float rotationZ = -0.0682006f;
	constexpr float rotationW = 0.8925904f;

	static Quaternion generateQRotation()
	{
		return Quaternion(rotationW, rotationX, rotationY, rotationZ);
	}

	constexpr float x1 = 1.2f;
	constexpr float y1 = 4.6f;
	constexpr float z1 = -6.1f;
	constexpr float w1 = -0.03f;

	static Quaternion generateQ1()
	{
		return Quaternion(w1, x1, y1, z1);
	}

	constexpr float x2 = 3.6f;
	constexpr float y2 = -8.1f;
	constexpr float z2 = 12.0f;
	constexpr float w2 = 7.4f;

	static Quaternion generateQ2()
	{
		return Quaternion(w2, x2, y2, z2);
	}


	constexpr float x3 = 5.2f;
	constexpr float y3 = 0.02f;
	constexpr float z3 = -3.6f;
	constexpr float w3 = 4.1f;

	static Quaternion generateQ3()
	{
		return Quaternion(w3, x3, y3, z3);
	}

	TEST(QuaternionTest, Identity)
	{
		const Quaternion q = Quaternion::identity();
		EXPECT_EQ(q.getW(), 1.0f);
		EXPECT_EQ(q.getX(), 0.0f);
		EXPECT_EQ(q.getY(), 0.0f);
		EXPECT_EQ(q.getZ(), 0.0f);
	}

	TEST(QuaternionTest, Initialization_Full)
	{
		const Quaternion q = generateQ1();
		EXPECT_EQ(q.getW(), w1);
		EXPECT_EQ(q.getX(), x1);
		EXPECT_EQ(q.getY(), y1);
		EXPECT_EQ(q.getZ(), z1);
	}

	TEST(QuaternionTest, Initialization_XAxisRotation)
	{
		constexpr float angle = 45.0f;
		const Quaternion q(Vector3f::right(), angle);

		constexpr float halfAngleRad = deg2rad(angle / 2.0f);
		EXPECT_NEAR(q.getW(), std::cos(halfAngleRad), epsilon);
		EXPECT_NEAR(q.getX(), std::sin(halfAngleRad), epsilon);
		EXPECT_NEAR(q.getY(), 0.0f, epsilon);
		EXPECT_NEAR(q.getZ(), 0.0f, epsilon);
	}

	TEST(QuaternionTest, Initialization_YAxisRotation)
	{
		constexpr float angle = 45.0f;
		const Quaternion q(Vector3f::up(), angle);

		constexpr float halfAngleRad = deg2rad(angle / 2.0f);
		EXPECT_NEAR(q.getW(), std::cos(halfAngleRad), epsilon);
		EXPECT_NEAR(q.getX(), 0.0f, epsilon);
		EXPECT_NEAR(q.getY(), std::sin(halfAngleRad), epsilon);
		EXPECT_NEAR(q.getZ(), 0.0f, epsilon);
	}

	TEST(QuaternionTest, Initialization_ZAxisRotation)
	{
		constexpr float angle = 45.0f;
		const Quaternion q(Vector3f::forward(), angle);

		constexpr float halfAngleRad = deg2rad(angle / 2.0f);
		EXPECT_NEAR(q.getW(), std::cos(halfAngleRad), epsilon);
		EXPECT_NEAR(q.getX(), 0.0f, epsilon);
		EXPECT_NEAR(q.getY(), 0.0f, epsilon);
		EXPECT_NEAR(q.getZ(), std::sin(halfAngleRad), epsilon);
	}

	TEST(QuaternionTest, Initialization_RandomAxisRotation)
	{
		constexpr float angle = 134.26f;
		const Vector3f u = Vector3f(1.2f, -0.32f, 2.4f).normalize();
		const Quaternion q(u, angle);

		// Direction cosines
		const float dcx = u.dot(Vector3f::right());
		const float dcy = u.dot(Vector3f::up());
		const float dcz = u.dot(Vector3f::forward());

		constexpr float halfAngleRad = deg2rad(angle / 2.0f);
		const float sineTerm = std::sin(halfAngleRad);
		EXPECT_NEAR(q.getW(), std::cos(halfAngleRad), epsilon);
		EXPECT_NEAR(q.getX(), sineTerm * dcx, epsilon);
		EXPECT_NEAR(q.getY(), sineTerm * dcy, epsilon);
		EXPECT_NEAR(q.getZ(), sineTerm * dcz, epsilon);
	}

	TEST(QuaternionTest, LengthSquared_Identity)
	{
		const Quaternion q = Quaternion::identity();
		EXPECT_NEAR(q.lengthSquared(), 1.0f, epsilon);
	}

	TEST(QuaternionTest, LengthSquared_Rotation)
	{
		const Quaternion q = generateQRotation();
		EXPECT_NEAR(q.lengthSquared(), 1.0f, epsilon);
	}

	TEST(QuaternionTest, LengthSquared_Random)
	{
		const Quaternion q = generateQ1();
		const float expectedLength = w1 * w1 + x1 * x1 + y1 * y1 + z1 * z1;
		EXPECT_NEAR(q.lengthSquared(), expectedLength, epsilon);
	}

	TEST(QuaternionTest, Length_Identity)
	{
		const Quaternion q = Quaternion::identity();
		EXPECT_NEAR(q.length(), 1.0f, epsilon);
	}

	TEST(QuaternionTest, Length_Rotation)
	{
		const Quaternion q = generateQRotation();
		EXPECT_NEAR(q.length(), 1.0f, epsilon);
	}

	TEST(QuaternionTest, Length_Random)
	{
		const Quaternion q = generateQ1();
		const float expectedLength = sqrt(w1 * w1 + x1 * x1 + y1 * y1 + z1 * z1);
		EXPECT_NEAR(q.length(), expectedLength, epsilon);
	}

	TEST(QuaternionTest, IsNormalized_Identity)
	{
		const Quaternion q = Quaternion::identity();
		EXPECT_TRUE(q.isNormalized());
	}

	TEST(QuaternionTest, IsNormalized_Rotation)
	{
		const Quaternion q = generateQRotation();
		EXPECT_TRUE(q.isNormalized());
	}

	TEST(QuaternionTest, IsNormalized_Random)
	{
		const Quaternion q = generateQ1();
		EXPECT_FALSE(q.isNormalized());
	}

	TEST(QuaternionTest, Normalize_Identity)
	{
		Quaternion q = Quaternion::identity();
		q.normalize();
		EXPECT_TRUE(q.isNormalized());
	}

	TEST(QuaternionTest, Normalize_Rotation)
	{
		Quaternion q = generateQRotation();
		q.normalize();
		EXPECT_TRUE(q.isNormalized());
	}

	TEST(QuaternionTest, Normalize_Random)
	{
		Quaternion q = generateQ1();
		EXPECT_FALSE(q.isNormalized());
		q.normalize();
		EXPECT_TRUE(q.isNormalized());
	}

	TEST(QuaternionTest, Add_Zero)
	{
		const Quaternion q1 = generateQ1();

		{
			const Quaternion qResult = q1 + Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
			EXPECT_EQ(qResult.getW(), w1);
			EXPECT_EQ(qResult.getX(), x1);
			EXPECT_EQ(qResult.getY(), y1);
			EXPECT_EQ(qResult.getZ(), z1);
		}

		{
			const Quaternion qResult = Quaternion(0.0f, 0.0f, 0.0f, 0.0f) + q1;
			EXPECT_EQ(qResult.getW(), w1);
			EXPECT_EQ(qResult.getX(), x1);
			EXPECT_EQ(qResult.getY(), y1);
			EXPECT_EQ(qResult.getZ(), z1);
		}
	}

	TEST(QuaternionTest, Add_Commutativity)
	{
		const Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();

		{
			const Quaternion qResult = q1 + q2;
			EXPECT_EQ(qResult.getW(), w1 + w2);
			EXPECT_EQ(qResult.getX(), x1 + x2);
			EXPECT_EQ(qResult.getY(), y1 + y2);
			EXPECT_EQ(qResult.getZ(), z1 + z2);
		}

		{
			const Quaternion qResult = q2 + q1;
			EXPECT_EQ(qResult.getW(), w1 + w2);
			EXPECT_EQ(qResult.getX(), x1 + x2);
			EXPECT_EQ(qResult.getY(), y1 + y2);
			EXPECT_EQ(qResult.getZ(), z1 + z2);
		}
	}

	TEST(QuaternionTest, Add_Associativity)
	{
		const Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();
		const Quaternion q3 = generateQ3();

		{
			const Quaternion qResult = (q1 + q2) + q3;
			EXPECT_NEAR(qResult.getW(), w1 + w2 + w3, epsilon);
			EXPECT_NEAR(qResult.getX(), x1 + x2 + x3, epsilon);
			EXPECT_NEAR(qResult.getY(), y1 + y2 + y3, epsilon);
			EXPECT_NEAR(qResult.getZ(), z1 + z2 + z3, epsilon);
		}

		{
			const Quaternion qResult = q1 + (q2 + q3);
			EXPECT_NEAR(qResult.getW(), w1 + w2 + w3, epsilon);
			EXPECT_NEAR(qResult.getX(), x1 + x2 + x3, epsilon);
			EXPECT_NEAR(qResult.getY(), y1 + y2 + y3, epsilon);
			EXPECT_NEAR(qResult.getZ(), z1 + z2 + z3, epsilon);
		}
	}

	TEST(QuaternionTest, Add_Attribution)
	{
		Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();

		q1 += q2;
		EXPECT_NEAR(q1.getW(), w1 + w2, epsilon);
		EXPECT_NEAR(q1.getX(), x1 + x2, epsilon);
		EXPECT_NEAR(q1.getY(), y1 + y2, epsilon);
		EXPECT_NEAR(q1.getZ(), z1 + z2, epsilon);
	}

	TEST(QuaternionTest, Subtract_Zero)
	{
		const Quaternion q1 = generateQ1();

		{
			const Quaternion qResult = q1 - Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
			EXPECT_NEAR(qResult.getW(), w1, epsilon);
			EXPECT_NEAR(qResult.getX(), x1, epsilon);
			EXPECT_NEAR(qResult.getY(), y1, epsilon);
			EXPECT_NEAR(qResult.getZ(), z1, epsilon);
		}

		{
			const Quaternion qResult = Quaternion(0.0f, 0.0f, 0.0f, 0.0f) - q1;
			EXPECT_NEAR(qResult.getW(), -w1, epsilon);
			EXPECT_NEAR(qResult.getX(), -x1, epsilon);
			EXPECT_NEAR(qResult.getY(), -y1, epsilon);
			EXPECT_NEAR(qResult.getZ(), -z1, epsilon);
		}
	}

	TEST(QuaternionTest, Subtract)
	{
		const Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();

		const Quaternion qResult = q1 - q2;
		EXPECT_NEAR(qResult.getW(), w1 - w2, epsilon);
		EXPECT_NEAR(qResult.getX(), x1 - x2, epsilon);
		EXPECT_NEAR(qResult.getY(), y1 - y2, epsilon);
		EXPECT_NEAR(qResult.getZ(), z1 - z2, epsilon);
	}

	TEST(QuaternionTest, Multiply_Zero)
	{
		const Quaternion q1 = generateQ1();

		{
			const Quaternion qResult = q1 * Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
			EXPECT_EQ(qResult.getW(), 0.0f);
			EXPECT_EQ(qResult.getX(), 0.0f);
			EXPECT_EQ(qResult.getY(), 0.0f);
			EXPECT_EQ(qResult.getZ(), 0.0f);
		}

		{
			const Quaternion qResult = Quaternion(0.0f, 0.0f, 0.0f, 0.0f) * q1;
			EXPECT_EQ(qResult.getW(), 0.0f);
			EXPECT_EQ(qResult.getX(), 0.0f);
			EXPECT_EQ(qResult.getY(), 0.0f);
			EXPECT_EQ(qResult.getZ(), 0.0f);
		}
	}

	TEST(QuaternionTest, Multiply_Identity)
	{
		const Quaternion q1 = generateQ1();

		{
			const Quaternion qResult = q1 * Quaternion::identity();
			EXPECT_EQ(qResult.getW(), w1);
			EXPECT_EQ(qResult.getX(), x1);
			EXPECT_EQ(qResult.getY(), y1);
			EXPECT_EQ(qResult.getZ(), z1);
		}

		{
			const Quaternion qResult = Quaternion::identity() * q1;
			EXPECT_EQ(qResult.getW(), w1);
			EXPECT_EQ(qResult.getX(), x1);
			EXPECT_EQ(qResult.getY(), y1);
			EXPECT_EQ(qResult.getZ(), z1);
		}
	}

	struct DummyQuat
	{
		float w;
		float x;
		float y;
		float z;
	};

	static DummyQuat quatToDummy(const Quaternion& q)
	{
		return { q.getW(), q.getX(), q.getY(), q.getZ() };
	}

	static DummyQuat computeComponentMultiplication(const DummyQuat& q1, const DummyQuat& q2)
	{
		float w = q1.w * q2.w - (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);
		float x = q1.w * q2.x + q2.w * q1.x + (q1.y * q2.z - q1.z * q2.y);
		float y = q1.w * q2.y + q2.w * q1.y + (q1.z * q2.x - q1.x * q2.z);
		float z = q1.w * q2.z + q2.w * q1.z + (q1.x * q2.y - q1.y * q2.x);

		return { w, x, y, z };
	}

	TEST(QuaternionTest, Multiply_NonCommutativity)
	{
		const Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();

		{
			const Quaternion qResult = q1 * q2;
			const DummyQuat qExpected = computeComponentMultiplication(quatToDummy(q1), quatToDummy(q2));

			EXPECT_NEAR(qResult.getW(), qExpected.w, epsilon);
			EXPECT_NEAR(qResult.getX(), qExpected.x, epsilon);
			EXPECT_NEAR(qResult.getY(), qExpected.y, epsilon);
			EXPECT_NEAR(qResult.getZ(), qExpected.z, epsilon);
		}

		{
			const Quaternion qResult = q2 * q1;
			const DummyQuat qExpected = computeComponentMultiplication(quatToDummy(q2), quatToDummy(q1));

			EXPECT_NEAR(qResult.getW(), qExpected.w, epsilon);
			EXPECT_NEAR(qResult.getX(), qExpected.x, epsilon);
			EXPECT_NEAR(qResult.getY(), qExpected.y, epsilon);
			EXPECT_NEAR(qResult.getZ(), qExpected.z, epsilon);
		}
	}

	TEST(QuaternionTest, Multiply_Associativity)
	{
		const Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();
		const Quaternion q3 = generateQ3();

		{
			const Quaternion qResult = (q1 * q2) * q3;
			const DummyQuat tmp = computeComponentMultiplication(quatToDummy(q1), quatToDummy(q2));
			const DummyQuat qExpected = computeComponentMultiplication(tmp, quatToDummy(q3));

			EXPECT_NEAR(qResult.getW(), qExpected.w, epsilon);
			EXPECT_NEAR(qResult.getX(), qExpected.x, epsilon);
			EXPECT_NEAR(qResult.getY(), qExpected.y, epsilon);
			EXPECT_NEAR(qResult.getZ(), qExpected.z, epsilon);
		}

		{
			const Quaternion qResult = q1 * (q2 * q3);
			const DummyQuat tmp = computeComponentMultiplication(quatToDummy(q2), quatToDummy(q3));
			const DummyQuat qExpected = computeComponentMultiplication(quatToDummy(q1), tmp);

			EXPECT_NEAR(qResult.getW(), qExpected.w, epsilon);
			EXPECT_NEAR(qResult.getX(), qExpected.x, epsilon);
			EXPECT_NEAR(qResult.getY(), qExpected.y, epsilon);
			EXPECT_NEAR(qResult.getZ(), qExpected.z, epsilon);
		}
	}

	TEST(QuaternionTest, Multiply_Distributivity)
	{
		const Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();
		const Quaternion q3 = generateQ3();

		{
			const Quaternion qResult = q1 * (q2 + q3);
			const DummyQuat qExpected = computeComponentMultiplication(quatToDummy(q1), { w2 + w3, x2 + x3, y2 + y3, z2 + z3 });

			EXPECT_NEAR(qResult.getW(), qExpected.w, epsilon);
			EXPECT_NEAR(qResult.getX(), qExpected.x, epsilon);
			EXPECT_NEAR(qResult.getY(), qExpected.y, epsilon);
			EXPECT_NEAR(qResult.getZ(), qExpected.z, epsilon);
		}

		{
			const Quaternion qResult = (q2 + q3) * q1;
			const DummyQuat qExpected = computeComponentMultiplication({ w2 + w3, x2 + x3, y2 + y3, z2 + z3 }, quatToDummy(q1));

			EXPECT_NEAR(qResult.getW(), qExpected.w, epsilon);
			EXPECT_NEAR(qResult.getX(), qExpected.x, epsilon);
			EXPECT_NEAR(qResult.getY(), qExpected.y, epsilon);
			EXPECT_NEAR(qResult.getZ(), qExpected.z, epsilon);
		}
	}

	TEST(QuaternionTest, Multiply_Attribution)
	{
		Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();

		const DummyQuat qExpected = computeComponentMultiplication(quatToDummy(q1), quatToDummy(q2));
		q1 *= q2;

		EXPECT_NEAR(q1.getW(), qExpected.w, epsilon);
		EXPECT_NEAR(q1.getX(), qExpected.x, epsilon);
		EXPECT_NEAR(q1.getY(), qExpected.y, epsilon);
		EXPECT_NEAR(q1.getZ(), qExpected.z, epsilon);
	}

	TEST(QuaternionTest, Scale_Multiply)
	{
		constexpr float s = 1.3f;

		const Quaternion q = generateQ1();

		{
			const Quaternion qResult = s * q;

			EXPECT_NEAR(qResult.getW(), s * w1, epsilon);
			EXPECT_NEAR(qResult.getX(), s * x1, epsilon);
			EXPECT_NEAR(qResult.getY(), s * y1, epsilon);
			EXPECT_NEAR(qResult.getZ(), s * z1, epsilon);
		}

		{
			const Quaternion qResult = q * s;

			EXPECT_NEAR(qResult.getW(), s * w1, epsilon);
			EXPECT_NEAR(qResult.getX(), s * x1, epsilon);
			EXPECT_NEAR(qResult.getY(), s * y1, epsilon);
			EXPECT_NEAR(qResult.getZ(), s * z1, epsilon);
		}
	}

	TEST(QuaternionTest, Scale_Multiply_Attribution)
	{
		constexpr float s = 1.3f;

		Quaternion q = generateQ1();
		q *= s;

		EXPECT_NEAR(q.getW(), s * w1, epsilon);
		EXPECT_NEAR(q.getX(), s * x1, epsilon);
		EXPECT_NEAR(q.getY(), s * y1, epsilon);
		EXPECT_NEAR(q.getZ(), s * z1, epsilon);
	}

	TEST(QuaternionTest, Scale_Division)
	{
		constexpr float s = 1.3f;

		const Quaternion q = generateQ1();
		const Quaternion qResult = q / s;

		EXPECT_NEAR(qResult.getW(), w1 / s, epsilon);
		EXPECT_NEAR(qResult.getX(), x1 / s, epsilon);
		EXPECT_NEAR(qResult.getY(), y1 / s, epsilon);
		EXPECT_NEAR(qResult.getZ(), z1 / s, epsilon);
	}

	TEST(QuaternionTest, Scale_Division_Attribution)
	{
		constexpr float s = 1.3f;

		Quaternion q = generateQ1();
		q /= s;

		EXPECT_NEAR(q.getW(), w1 / s, epsilon);
		EXPECT_NEAR(q.getX(), x1 / s, epsilon);
		EXPECT_NEAR(q.getY(), y1 / s, epsilon);
		EXPECT_NEAR(q.getZ(), z1 / s, epsilon);
	}

	TEST(QuaternionTest, Inverse)
	{
		const Quaternion q = generateQ1();

		const Quaternion qResult = q.inverse();

		constexpr float oneOnQuotient = 1.0f / (w1 * w1 + x1 * x1 + y1 * y1 + z1 * z1);
		EXPECT_NEAR(qResult.getW(), w1 * oneOnQuotient, epsilon);
		EXPECT_NEAR(qResult.getX(), -x1 * oneOnQuotient, epsilon);
		EXPECT_NEAR(qResult.getY(), -y1 * oneOnQuotient, epsilon);
		EXPECT_NEAR(qResult.getZ(), -z1 * oneOnQuotient, epsilon);

		{
			const Quaternion p = q * qResult;
			EXPECT_NEAR(p.getW(), 1.0f, epsilon);
			EXPECT_NEAR(p.getX(), 0.0f, epsilon);
			EXPECT_NEAR(p.getY(), 0.0f, epsilon);
			EXPECT_NEAR(p.getZ(), 0.0f, epsilon);
		}

		{
			const Quaternion p = qResult * q;
			EXPECT_NEAR(p.getW(), 1.0f, epsilon);
			EXPECT_NEAR(p.getX(), 0.0f, epsilon);
			EXPECT_NEAR(p.getY(), 0.0f, epsilon);
			EXPECT_NEAR(p.getZ(), 0.0f, epsilon);
		}
	}

	TEST(QuaternionTest, FromEuler)
	{
		constexpr float angleX = 37.2f;
		constexpr float angleY = -13.4f;
		constexpr float angleZ = 156.7f;

		const Quaternion q = Quaternion::fromEuler(angleX, angleY, angleZ);
		const float resultW = q.getW();
		const float resultX = q.getX();
		const float resultY = q.getY();
		const float resultZ = q.getZ();

		const float resultAngleX = rad2deg(std::asin(2.0f * (resultY * resultZ + resultW * resultX)));
		EXPECT_NEAR(resultAngleX, angleX, 5e-5);

		const float resultAngleY = rad2deg(std::atan2(-2.0f * (resultX * resultZ - resultW * resultY), 1.0f - 2.0f * (resultX * resultX + resultY * resultY)));
		EXPECT_NEAR(resultAngleY, angleY, 5e-5);

		const float resultAngleZ = rad2deg(std::atan2(-2.0f * (resultX * resultY - resultW * resultZ), 1.0f - 2.0f * (resultX * resultX + resultZ * resultZ)));
		EXPECT_NEAR(resultAngleZ, angleZ, 5e-5);
	}

	TEST(QuaternionTest, ToEuler)
	{
		constexpr float angleX = 37.2f;
		constexpr float angleY = -13.4f;
		constexpr float angleZ = 156.7f;

		const float cx = std::cos(deg2rad(angleX * 0.5f));
		const float sx = std::sin(deg2rad(angleX * 0.5f));
		const float cy = std::cos(deg2rad(angleY * 0.5f));
		const float sy = std::sin(deg2rad(angleY * 0.5f));
		const float cz = std::cos(deg2rad(angleZ * 0.5f));
		const float sz = std::sin(deg2rad(angleZ * 0.5f));
		const float w = cz * cx * cy - sz * sx * sy;
		const float x = sx * cz * cy - sz * sy * cx;
		const float y = sz * sx * cy + sy * cz * cx;
		const float z = sz * cx * cy + sx * sy * cz;

		const Quaternion q(w, x, y, z);

		const Vector3f result = q.toEuler();
		EXPECT_NEAR(result.x, angleX, 5e-6);
		EXPECT_NEAR(result.y, angleY, 5e-6);
		EXPECT_NEAR(result.z, angleZ, 5e-6);
	}

	TEST(QuaternionTest, FromEuler_ToEuler)
	{
		constexpr float angleX = 37.2f;
		constexpr float angleY = -13.4f;
		constexpr float angleZ = 156.7f;

		const Vector3f result = Quaternion::fromEuler(angleX, angleY, angleZ).toEuler();
		EXPECT_NEAR(result.x, angleX, 5e-6);
		EXPECT_NEAR(result.y, angleY, 5e-6);
		EXPECT_NEAR(result.z, angleZ, 5e-6);
	}

	TEST(QuaternionTest, GetRotatedRight_Identity)
	{
		const Quaternion q = Quaternion::identity();

		const Vector3f result = q.getRotatedRight();
		EXPECT_NEAR(result.x, 1.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, 0.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedRight_RotateY0)
	{
		const Quaternion q(Vector3f::up(), 0.0f);

		const Vector3f result = q.getRotatedRight();
		EXPECT_NEAR(result.x, 1.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, 0.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedRight_RotateY90)
	{
		const Quaternion q(Vector3f::up(), 90.0f);

		const Vector3f result = q.getRotatedRight();
		EXPECT_NEAR(result.x, 0.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, -1.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedUp_Identity)
	{
		const Quaternion q = Quaternion::identity();

		const Vector3f result = q.getRotatedUp();
		EXPECT_NEAR(result.x, 0.0f, epsilon);
		EXPECT_NEAR(result.y, 1.0f, epsilon);
		EXPECT_NEAR(result.z, 0.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedUp_RotateX0)
	{
		const Quaternion q(Vector3f::right(), 0.0f);

		const Vector3f result = q.getRotatedUp();
		EXPECT_NEAR(result.x, 0.0f, epsilon);
		EXPECT_NEAR(result.y, 1.0f, epsilon);
		EXPECT_NEAR(result.z, 0.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedUp_RotateX90)
	{
		const Quaternion q(Vector3f::right(), 90.0f);

		const Vector3f result = q.getRotatedUp();
		EXPECT_NEAR(result.x, 0.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, 1.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedForward_Identity)
	{
		const Quaternion q = Quaternion::identity();

		const Vector3f result = q.getRotatedForward();
		EXPECT_NEAR(result.x, 0.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, 1.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedForward_RotateY0)
	{
		const Quaternion q(Vector3f::up(), 0.0f);

		const Vector3f result = q.getRotatedForward();
		EXPECT_NEAR(result.x, 0.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, 1.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedForward_RotateY90)
	{
		const Quaternion q(Vector3f::up(), 90.0f);

		const Vector3f result = q.getRotatedForward();
		EXPECT_NEAR(result.x, 1.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, 0.0f, epsilon);
	}

	TEST(QuaternionTest, ToMatrix_Identity)
	{
		const Quaternion q = Quaternion::identity();
		const Matrix3f result = q.toMatrix();

		EXPECT_NEAR(result.getValue(0, 0), 1.0f, epsilon);
		EXPECT_NEAR(result.getValue(0, 1), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(0, 2), 0.0f, epsilon);

		EXPECT_NEAR(result.getValue(1, 0), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(1, 1), 1.0f, epsilon);
		EXPECT_NEAR(result.getValue(1, 2), 0.0f, epsilon);

		EXPECT_NEAR(result.getValue(2, 0), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(2, 1), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(2, 2), 1.0f, epsilon);
	}

	TEST(QuaternionTest, ToMatrix_RotateX90)
	{
		const Quaternion q(Vector3f::right(), 90.0f);
		const Matrix3f result = q.toMatrix();

		EXPECT_NEAR(result.getValue(0, 0), 1.0f, epsilon);
		EXPECT_NEAR(result.getValue(0, 1), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(0, 2), 0.0f, epsilon);

		EXPECT_NEAR(result.getValue(1, 0), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(1, 1), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(1, 2), 1.0f, epsilon);

		EXPECT_NEAR(result.getValue(2, 0), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(2, 1), -1.0f, epsilon);
		EXPECT_NEAR(result.getValue(2, 2), 0.0f, epsilon);
	}

	TEST(QuaternionTest, ToMatrix_RotateY90)
	{
		const Quaternion q(Vector3f::up(), 90.0f);
		const Matrix3f result = q.toMatrix();

		EXPECT_NEAR(result.getValue(0, 0), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(0, 1), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(0, 2), -1.0f, epsilon);

		EXPECT_NEAR(result.getValue(1, 0), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(1, 1), 1.0f, epsilon);
		EXPECT_NEAR(result.getValue(1, 2), 0.0f, epsilon);

		EXPECT_NEAR(result.getValue(2, 0), 1.0f, epsilon);
		EXPECT_NEAR(result.getValue(2, 1), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(2, 2), 0.0f, epsilon);
	}

	TEST(QuaternionTest, ToMatrix_RotateZ90)
	{
		const Quaternion q(Vector3f::forward(), 90.0f);
		const Matrix3f result = q.toMatrix();

		EXPECT_NEAR(result.getValue(0, 0), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(0, 1), 1.0f, epsilon);
		EXPECT_NEAR(result.getValue(0, 2), 0.0f, epsilon);

		EXPECT_NEAR(result.getValue(1, 0), -1.0f, epsilon);
		EXPECT_NEAR(result.getValue(1, 1), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(1, 2), 0.0f, epsilon);

		EXPECT_NEAR(result.getValue(2, 0), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(2, 1), 0.0f, epsilon);
		EXPECT_NEAR(result.getValue(2, 2), 1.0f, epsilon);
	}

	TEST(QuaternionTest, ToMatrix_Random)
	{
		const Quaternion q = generateQRotation();
		const Matrix3f result = q.toMatrix();

		constexpr float m00 = 1.0f - 2.0f * (rotationY * rotationY + rotationZ * rotationZ);
		constexpr float m01 = 2.0f * (rotationX * rotationY + rotationW * rotationZ);
		constexpr float m02 = 2.0f * (rotationX * rotationZ - rotationW * rotationY);
		EXPECT_NEAR(result.getValue(0, 0), m00, epsilon);
		EXPECT_NEAR(result.getValue(0, 1), m01, epsilon);
		EXPECT_NEAR(result.getValue(0, 2), m02, epsilon);

		constexpr float m10 = 2.0f * (rotationX * rotationY - rotationW * rotationZ);
		constexpr float m11 = 1.0f - 2.0f * (rotationX * rotationX + rotationZ * rotationZ);
		constexpr float m12 = 2.0f * (rotationY * rotationZ + rotationW * rotationX);
		EXPECT_NEAR(result.getValue(1, 0), m10, epsilon);
		EXPECT_NEAR(result.getValue(1, 1), m11, epsilon);
		EXPECT_NEAR(result.getValue(1, 2), m12, epsilon);

		constexpr float m20 = 2.0f * (rotationX * rotationZ + rotationW * rotationY);
		constexpr float m21 = 2.0f * (rotationY * rotationZ - rotationW * rotationX);
		constexpr float m22 = 1.0f - 2.0f * (rotationX * rotationX + rotationY * rotationY);
		EXPECT_NEAR(result.getValue(2, 0), m20, epsilon);
		EXPECT_NEAR(result.getValue(2, 1), m21, epsilon);
		EXPECT_NEAR(result.getValue(2, 2), m22, epsilon);
	}

	TEST(QuaternionTest, FromMatrix_Identity)
	{
		const Quaternion q(Matrix3f::identity());
		EXPECT_NEAR(q.getW(), 1.0f, epsilon);
		EXPECT_NEAR(q.getX(), 0.0f, epsilon);
		EXPECT_NEAR(q.getY(), 0.0f, epsilon);
		EXPECT_NEAR(q.getZ(), 0.0f, epsilon);
	}
}