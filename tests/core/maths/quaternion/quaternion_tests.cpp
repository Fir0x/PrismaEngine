#include <gtest/gtest.h>

#include "core/maths/public/Quaternion.h"

namespace PrismaEngineTest
{
	constexpr float epsilon = 0.0000005f;

	using namespace PrismaEngine;

	static Quaternion generateQRotation()
	{
		constexpr float x = 0.682f;
		constexpr float y = 0.178f;
		constexpr float z = 0.692f;
		constexpr float w = 0.153f;

		return Quaternion(w, x, y, z);
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

		constexpr float halfAngle = angle / 2.0f;
		EXPECT_NEAR(q.getW(), std::cos(halfAngle), epsilon);
		EXPECT_NEAR(q.getX(), std::sin(halfAngle), epsilon);
		EXPECT_NEAR(q.getY(), 0.0f, epsilon);
		EXPECT_NEAR(q.getZ(), 0.0f, epsilon);
	}

	TEST(QuaternionTest, Initialization_YAxisRotation)
	{
		constexpr float angle = 45.0f;
		const Quaternion q(Vector3f::right(), angle);

		constexpr float halfAngle = angle / 2.0f;
		EXPECT_NEAR(q.getW(), std::cos(halfAngle), epsilon);
		EXPECT_NEAR(q.getX(), 0.0f, epsilon);
		EXPECT_NEAR(q.getY(), std::sin(halfAngle), epsilon);
		EXPECT_NEAR(q.getZ(), 0.0f, epsilon);
	}

	TEST(QuaternionTest, Initialization_ZAxisRotation)
	{
		constexpr float angle = 45.0f;
		const Quaternion q(Vector3f::right(), angle);

		constexpr float halfAngle = angle / 2.0f;
		EXPECT_NEAR(q.getW(), std::cos(halfAngle), epsilon);
		EXPECT_NEAR(q.getX(), 0.0f, epsilon);
		EXPECT_NEAR(q.getY(), 0.0f, epsilon);
		EXPECT_NEAR(q.getZ(), std::sin(halfAngle), epsilon);
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

		constexpr float halfAngle = angle / 2.0f;
		const float sineTerm = std::sin(halfAngle);
		EXPECT_NEAR(q.getW(), std::cos(halfAngle), epsilon);
		EXPECT_NEAR(q.getX(), sineTerm * dcx, epsilon);
		EXPECT_NEAR(q.getY(), sineTerm * dcy, epsilon);
		EXPECT_NEAR(q.getZ(), sineTerm * dcz, epsilon);
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
		EXPECT_NEAR(q.length(), 7.734f, epsilon);
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
			EXPECT_EQ(qResult.getW(), w1 + w2 + w3);
			EXPECT_EQ(qResult.getX(), x1 + x2 + x3);
			EXPECT_EQ(qResult.getY(), y1 + y2 + y3);
			EXPECT_EQ(qResult.getZ(), z1 + z2 + z3);
		}

		{
			const Quaternion qResult = q1 + (q2 + q3);
			EXPECT_EQ(qResult.getW(), w1 + w2 + w3);
			EXPECT_EQ(qResult.getX(), x1 + x2 + x3);
			EXPECT_EQ(qResult.getY(), y1 + y2 + y3);
			EXPECT_EQ(qResult.getZ(), z1 + z2 + z3);
		}
	}

	TEST(QuaternionTest, Add_Attribution)
	{
		Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();

		q1 += q2;
		EXPECT_EQ(q1.getW(), w1 + w2 + w3);
		EXPECT_EQ(q1.getX(), x1 + x2 + x3);
		EXPECT_EQ(q1.getY(), y1 + y2 + y3);
		EXPECT_EQ(q1.getZ(), z1 + z2 + z3);
	}

	TEST(QuaternionTest, Subtract_Zero)
	{
		const Quaternion q1 = generateQ1();

		{
			const Quaternion qResult = q1 - Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
			EXPECT_EQ(qResult.getW(), w1);
			EXPECT_EQ(qResult.getX(), x1);
			EXPECT_EQ(qResult.getY(), y1);
			EXPECT_EQ(qResult.getZ(), z1);
		}

		{
			const Quaternion qResult = Quaternion(0.0f, 0.0f, 0.0f, 0.0f) - q1;
			EXPECT_EQ(qResult.getW(), -w1);
			EXPECT_EQ(qResult.getX(), -x1);
			EXPECT_EQ(qResult.getY(), -y1);
			EXPECT_EQ(qResult.getZ(), -z1);
		}
	}

	TEST(QuaternionTest, Subtract)
	{
		const Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();

		const Quaternion qResult = q1 - q2;
		EXPECT_EQ(qResult.getW(), w1 - w2);
		EXPECT_EQ(qResult.getX(), x1 - x2);
		EXPECT_EQ(qResult.getY(), y1 - y2);
		EXPECT_EQ(qResult.getZ(), z1 - z2);
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

			EXPECT_EQ(qResult.getW(), qExpected.w);
			EXPECT_EQ(qResult.getX(), qExpected.x);
			EXPECT_EQ(qResult.getY(), qExpected.y);
			EXPECT_EQ(qResult.getZ(), qExpected.z);
		}

		{
			const Quaternion qResult = q2 * q1;
			const DummyQuat qExpected = computeComponentMultiplication(quatToDummy(q2), quatToDummy(q1));

			EXPECT_EQ(qResult.getW(), qExpected.w);
			EXPECT_EQ(qResult.getX(), qExpected.x);
			EXPECT_EQ(qResult.getY(), qExpected.y);
			EXPECT_EQ(qResult.getZ(), qExpected.z);
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

			EXPECT_EQ(qResult.getW(), qExpected.w);
			EXPECT_EQ(qResult.getX(), qExpected.x);
			EXPECT_EQ(qResult.getY(), qExpected.y);
			EXPECT_EQ(qResult.getZ(), qExpected.z);
		}

		{
			const Quaternion qResult = q1 * (q2 * q3);
			const DummyQuat tmp = computeComponentMultiplication(quatToDummy(q2), quatToDummy(q3));
			const DummyQuat qExpected = computeComponentMultiplication(quatToDummy(q1), tmp);

			EXPECT_EQ(qResult.getW(), qExpected.w);
			EXPECT_EQ(qResult.getX(), qExpected.x);
			EXPECT_EQ(qResult.getY(), qExpected.y);
			EXPECT_EQ(qResult.getZ(), qExpected.z);
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

			EXPECT_EQ(qResult.getW(), qExpected.w);
			EXPECT_EQ(qResult.getX(), qExpected.x);
			EXPECT_EQ(qResult.getY(), qExpected.y);
			EXPECT_EQ(qResult.getZ(), qExpected.z);
		}

		{
			const Quaternion qResult = (q2 + q3) * q1;
			const DummyQuat qExpected = computeComponentMultiplication({ w2 + w3, x2 + x3, y2 + y3, z2 + z3 }, quatToDummy(q1));

			EXPECT_EQ(qResult.getX(), qExpected.x);
			EXPECT_EQ(qResult.getY(), qExpected.y);
			EXPECT_EQ(qResult.getZ(), qExpected.z);
			EXPECT_EQ(qResult.getW(), qExpected.w);
		}
	}

	TEST(QuaternionTest, Multiply_Attribution)
	{
		Quaternion q1 = generateQ1();
		const Quaternion q2 = generateQ2();

		q1 *= q2;
		const DummyQuat qExpected = computeComponentMultiplication(quatToDummy(q1), quatToDummy(q2));

		EXPECT_EQ(q1.getW(), qExpected.w);
		EXPECT_EQ(q1.getX(), qExpected.x);
		EXPECT_EQ(q1.getY(), qExpected.y);
		EXPECT_EQ(q1.getZ(), qExpected.z);
	}

	TEST(QuaternionTest, Scale_Multiply)
	{
		constexpr float s = 1.3f;

		const Quaternion q = generateQ1();

		{
			const Quaternion qResult = s * q;

			EXPECT_EQ(qResult.getW(), s * w1);
			EXPECT_EQ(qResult.getX(), s * x1);
			EXPECT_EQ(qResult.getY(), s * y1);
			EXPECT_EQ(qResult.getZ(), s * z1);
		}

		{
			const Quaternion qResult = q * s;

			EXPECT_EQ(qResult.getW(), s * w1);
			EXPECT_EQ(qResult.getX(), s * x1);
			EXPECT_EQ(qResult.getY(), s * y1);
			EXPECT_EQ(qResult.getZ(), s * z1);
		}
	}

	TEST(QuaternionTest, Scale_Multiply_Attribution)
	{
		constexpr float s = 1.3f;

		Quaternion q = generateQ1();
		q *= s;

		EXPECT_EQ(q.getW(), s * w1);
		EXPECT_EQ(q.getX(), s * x1);
		EXPECT_EQ(q.getY(), s * y1);
		EXPECT_EQ(q.getZ(), s * z1);
	}

	TEST(QuaternionTest, Scale_Division)
	{
		constexpr float s = 1.3f;

		const Quaternion q = generateQ1();
		const Quaternion qResult = q / s;

		EXPECT_EQ(qResult.getW(), w1 / s);
		EXPECT_EQ(qResult.getX(), x1 / s);
		EXPECT_EQ(qResult.getY(), y1 / s);
		EXPECT_EQ(qResult.getZ(), z1 / s);
	}

	TEST(QuaternionTest, Scale_Division_Attribution)
	{
		constexpr float s = 1.3f;

		Quaternion q = generateQ1();
		q /= s;

		EXPECT_EQ(q.getW(), w1 / s);
		EXPECT_EQ(q.getX(), x1 / s);
		EXPECT_EQ(q.getY(), y1 / s);
		EXPECT_EQ(q.getZ(), z1 / s);
	}

	TEST(QuaternionTest, Inverse)
	{
		const Quaternion q = generateQ1();

		const Quaternion qResult = q.inverse();

		constexpr float quotient = w1 * w1 + x1 * x1 + y1 * y1 + z1 * z1;
		EXPECT_NEAR(qResult.getW(), w1 / quotient, epsilon);
		EXPECT_NEAR(qResult.getX(), -x1 / quotient, epsilon);
		EXPECT_NEAR(qResult.getY(), -y1 / quotient, epsilon);
		EXPECT_NEAR(qResult.getZ(), -z1 / quotient, epsilon);

		{
			const Quaternion p = q * qResult;
			EXPECT_EQ(p.getW(), 0.0f);
			EXPECT_EQ(p.getX(), 0.0f);
			EXPECT_EQ(p.getY(), 0.0f);
			EXPECT_EQ(p.getZ(), 0.0f);
		}

		{
			const Quaternion p = qResult * q;
			EXPECT_EQ(p.getW(), 0.0f);
			EXPECT_EQ(p.getX(), 0.0f);
			EXPECT_EQ(p.getY(), 0.0f);
			EXPECT_EQ(p.getZ(), 0.0f);
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

		const float resultAngleX = std::atan2(2 * (resultW * resultX + resultY * resultZ), 1 - 2 * (resultX * resultX + resultY * resultY));
		EXPECT_NEAR(resultAngleX, angleX, epsilon);

		const float resultAngleY = std::asin(2 * (resultW * resultY - resultX * resultZ));
		EXPECT_NEAR(resultAngleY, angleY, epsilon);

		const float resultAngleZ = std::atan2(2 * (resultW * resultZ + resultX * resultY), 1 - 2 * (resultY * resultY + resultZ * resultZ));
		EXPECT_NEAR(resultAngleZ, angleZ, epsilon);
	}

	TEST(QuaternionTest, ToEuler)
	{
		constexpr float angleX = 37.2f;
		constexpr float angleY = -13.4f;
		constexpr float angleZ = 156.7f;

		const float cr = std::cos(angleX * 0.5f);
		const float sr = std::sin(angleX * 0.5f);
		const float cp = std::cos(angleZ * 0.5f);
		const float sp = std::sin(angleZ * 0.5f);
		const float cy = std::cos(angleY * 0.5f);
		const float sy = std::sin(angleY * 0.5f);
		const float w = cr * cp * cy + sr * sp * sy;
		const float x = sr * cp * cy - cr * sp * sy;
		const float y = cr * sp * cy + sr * cp * sy;
		const float z = cr * cp * sy - sr * sp * cy;

		const Quaternion q(w, x, y, z);

		const Vector3f result = q.toEuler();
		EXPECT_NEAR(result.x, angleX, epsilon);
		EXPECT_NEAR(result.y, angleY, epsilon);
		EXPECT_NEAR(result.z, angleZ, epsilon);
	}

	TEST(QuaternionTest, GetRotatedRight)
	{
		constexpr float angle = 90.0f;
		const Quaternion q(Vector3f::up(), angle);

		const Vector3f result = q.getRotatedRight();
		EXPECT_NEAR(result.x, 0.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, 1.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedUp)
	{
		constexpr float angle = 90.0f;
		const Quaternion q(Vector3f::right(), angle);

		const Vector3f result = q.getRotatedRight();
		EXPECT_NEAR(result.x, 0.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, -1.0f, epsilon);
	}

	TEST(QuaternionTest, GetRotatedForward)
	{
		constexpr float angle = 90.0f;
		const Quaternion q(Vector3f::forward(), angle);

		const Vector3f result = q.getRotatedRight();
		EXPECT_NEAR(result.x, -1.0f, epsilon);
		EXPECT_NEAR(result.y, 0.0f, epsilon);
		EXPECT_NEAR(result.z, 0.0f, epsilon);
	}

	TEST(QuaternionTest, ToMatrix)
	{
		// Ref euler: x=45 y=12 z=34
		constexpr float w = -0.8488065f;
		constexpr float x = -0.4125998f;
		constexpr float y = -0.1100266f;
		constexpr float z = -0.3117421f;

		const Quaternion q(w, x, y, z);
		const Matrix3f result = q.toMatrix();

		constexpr float m00 = 1.0f - 2.0f * y * y - 2.0f * z * z;
		constexpr float m01 = 2.0f * x * y - 2.0f * w * z;
		constexpr float m02 = 2.0f * x * z + 2.0f * w * y;
		EXPECT_NEAR(result.getValue(0, 0), m00, epsilon);
		EXPECT_NEAR(result.getValue(0, 1), m01, epsilon);
		EXPECT_NEAR(result.getValue(0, 1), m02, epsilon);

		constexpr float m10 = 2.0f * x * y + 2.0f * w * z;
		constexpr float m11 = 1.0f - 2.0f * x * x - 2.0f * z * z;
		constexpr float m12 = 2.0f * y * z - 2.0f * w * x;
		EXPECT_NEAR(result.getValue(1, 0), m10, epsilon);
		EXPECT_NEAR(result.getValue(1, 1), m11, epsilon);
		EXPECT_NEAR(result.getValue(1, 1), m12, epsilon);

		constexpr float m20 = 2.0f * x * z - 2.0f * w * y;
		constexpr float m21 = 2.0f * y * z + 2.0f * w * x;
		constexpr float m22 = 1.0f - 2.0f * x * x - 2.0f * y * y;
		EXPECT_NEAR(result.getValue(2, 0), m20, epsilon);
		EXPECT_NEAR(result.getValue(2, 1), m21, epsilon);
		EXPECT_NEAR(result.getValue(2, 1), m22, epsilon);
	}
}