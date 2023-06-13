#include <gtest/gtest.h>

#include "core/maths/public/utils.h"

using namespace PrismaEngine;

TEST(TransformTests, DegressToRadiansFloat)
{
	constexpr float epsilon = 1e-5f;
	EXPECT_EQ(degreesToRadians(0.0f), 0.0f);
	EXPECT_NEAR(degreesToRadians(45.0f), 0.785398f, epsilon);
	EXPECT_NEAR(degreesToRadians(90.0f), 1.5708f, epsilon);
	EXPECT_NEAR(degreesToRadians(135.0f), 2.35619f, epsilon);
	EXPECT_NEAR(degreesToRadians(180.0f), 3.14159f, epsilon);

	EXPECT_NEAR(degreesToRadians(32.56f), 0.5682792044f, epsilon);
	EXPECT_NEAR(degreesToRadians(76.7f), 1.3386675363f, epsilon);
}

TEST(TransformTests, RadiansToDegreesDouble)
{
	constexpr double epsilon = 1e-5;
	EXPECT_EQ(degreesToRadians(0.0), 0.0);
	EXPECT_NEAR(degreesToRadians(45.0), 0.785398, epsilon);
	EXPECT_NEAR(degreesToRadians(90.0), 1.5708, epsilon);
	EXPECT_NEAR(degreesToRadians(135.0), 2.35619, epsilon);
	EXPECT_NEAR(degreesToRadians(180.0), 3.14159, epsilon);

	EXPECT_NEAR(degreesToRadians(32.56), 0.5682792044, epsilon);
	EXPECT_NEAR(degreesToRadians(76.7), 1.3386675363, epsilon);
}

TEST(TransformTests, CosFloat)
{
	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(0.0f)), 1.0f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(45.0f)), 0.70710678f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(90.0f)), 0.0f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(135.0f)), -0.70710678f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(180.0f)), -1.0f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(225.0f)), -0.70710678f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(270.0f)), 0.0f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(315.0f)), 0.70710678f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(360.0f)), 1.0f, epsilon);

	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(32.56f)), 0.84282832f, epsilon);
	EXPECT_NEAR(PrismaEngine::cos(degreesToRadians(76.7f)), 0.23004974f, epsilon);
}

TEST(TransformTests, SinFloat)
{
	constexpr float epsilon = 1e-5f;
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(0.0f)), 0.0f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(45.0f)), 0.70710678f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(90.0f)), 1.0f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(135.0f)), 0.70710678f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(180.0f)), 0.0f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(225.0f)), -0.70710678f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(270.0f)), -1.0f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(315.0f)), -0.70710678f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(360.0f)), 0.0f, epsilon);

	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(32.56f)), 0.53818251f, epsilon);
	EXPECT_NEAR(PrismaEngine::sin(degreesToRadians(76.7f)), 0.97317887f, epsilon);
}

TEST(TransformTests, ClampFloat)
{
	EXPECT_EQ(clamp(-1.0f, -1.0f, 1.0f), -1.0f);
	EXPECT_EQ(clamp(1.0f, -1.0f, 1.0f), 1.0f);
	EXPECT_EQ(clamp(0.0f, -1.0f, 1.0f), 0.0f);
	EXPECT_EQ(clamp(0.2567f, -1.0f, 1.0f), 0.2567f);
	EXPECT_EQ(clamp(-7.235f, -1.0f, 1.0f), -1.0f);
	EXPECT_EQ(clamp(4.569f, -1.0f, 1.0f), 1.0f);
}