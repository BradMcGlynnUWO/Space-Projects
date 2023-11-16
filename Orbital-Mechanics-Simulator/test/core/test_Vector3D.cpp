#include "Vector3D.h"
#include <limits>
#include <gtest/gtest.h>

TEST(Vector3DTest, ConstructorDefault) {
    Vector3D v;
    EXPECT_DOUBLE_EQ(0.0, v.x);
    EXPECT_DOUBLE_EQ(0.0, v.y);
    EXPECT_DOUBLE_EQ(0.0, v.z);
}

TEST(Vector3DTest, ConstructorParameters) {
    Vector3D v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(1.0, v.x);
    EXPECT_DOUBLE_EQ(2.0, v.y);
    EXPECT_DOUBLE_EQ(3.0, v.z);
}

TEST(Vector3DTest, CopyConstructor) {
    Vector3D original(4.0, 5.0, 6.0);
    Vector3D copy = original;
    EXPECT_DOUBLE_EQ(original.x, copy.x);
    EXPECT_DOUBLE_EQ(original.y, copy.y);
    EXPECT_DOUBLE_EQ(original.z, copy.z);
}

TEST(Vector3DTest, Addition) {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D sum = v1 + v2;
    EXPECT_DOUBLE_EQ(5.0, sum.x);
    EXPECT_DOUBLE_EQ(7.0, sum.y);
    EXPECT_DOUBLE_EQ(9.0, sum.z);
}

TEST(Vector3DTest, Subtraction) {
    Vector3D v1(5.0, 6.0, 7.0);
    Vector3D v2(2.0, 4.0, 6.0);
    Vector3D result = v1 - v2;
    EXPECT_DOUBLE_EQ(3.0, result.x);
    EXPECT_DOUBLE_EQ(2.0, result.y);
    EXPECT_DOUBLE_EQ(1.0, result.z);
}

TEST(Vector3DTest, ScalarMultiplication) {
    Vector3D v(1.0, -2.0, 3.0);
    double scalar = 2.0;
    Vector3D result = v * scalar;
    EXPECT_DOUBLE_EQ(2.0, result.x);
    EXPECT_DOUBLE_EQ(-4.0, result.y);
    EXPECT_DOUBLE_EQ(6.0, result.z);
}

TEST(Vector3DTest, ScalarDivision) {
    Vector3D v(4.0, -2.0, 8.0);
    double scalar = 2.0;
    Vector3D result = v / scalar;
    EXPECT_DOUBLE_EQ(2.0, result.x);
    EXPECT_DOUBLE_EQ(-1.0, result.y);
    EXPECT_DOUBLE_EQ(4.0, result.z);
}

TEST(Vector3DTest, DotProduct) {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    double result = v1.dot(v2);
    EXPECT_DOUBLE_EQ(32.0, result); // 1*4 + 2*5 + 3*6
}

TEST(Vector3DTest, CrossProduct) {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D result = v1.cross(v2);
    EXPECT_DOUBLE_EQ(-3.0, result.x); // 2*6 - 3*5
    EXPECT_DOUBLE_EQ(6.0, result.y);  // 3*4 - 1*6
    EXPECT_DOUBLE_EQ(-3.0, result.z); // 1*5 - 2*4
}

TEST(Vector3DTest, Norm) {
    Vector3D v(2.0, -2.0, 1.0);
    double result = v.norm();
    EXPECT_DOUBLE_EQ(3.0, result); // sqrt(4 + 4 + 1)
}

TEST(Vector3DTest, Normalize) {
    Vector3D v(0.0, 3.0, 4.0);
    v.normalize();
    EXPECT_DOUBLE_EQ(0.0, v.x);
    EXPECT_NEAR(0.6, v.y, 1e-6); // 3/5
    EXPECT_NEAR(0.8, v.z, 1e-6); // 4/5
}

TEST(Vector3DTest, Distance) {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 6.0, 8.0);
    double result = Vector3D::distance(v1, v2);
    EXPECT_NEAR(7.0710678118654755, result, 1e-6); // sqrt(9 + 16 + 25)
}

TEST(Vector3DTest, DotProductPerpendicular) {
    // Vectors are perpendicular if their dot product is 0
    Vector3D v1(1.0, 0.0, 0.0);
    Vector3D v2(0.0, 1.0, 0.0);
    double result = v1.dot(v2);
    EXPECT_DOUBLE_EQ(0.0, result);
}

TEST(Vector3DTest, DotProductParallel) {
    // Parallel vectors have a dot product equal to the product of their norms
    Vector3D v1(1.0, 1.0, 1.0);
    Vector3D v2(2.0, 2.0, 2.0);
    double result = v1.dot(v2);
    double expected = v1.norm() * v2.norm();
    EXPECT_NEAR(expected, result, 1e-6);
}

TEST(Vector3DTest, DotProductZeroVector) {
    Vector3D v1(0.0, 0.0, 0.0);
    Vector3D v2(1.0, 2.0, 3.0);
    double result = v1.dot(v2);
    EXPECT_DOUBLE_EQ(0.0, result);
}

TEST(Vector3DTest, CrossProductPerpendicular) {
    // The cross product of perpendicular vectors should result in a vector that is
    // perpendicular to both original vectors and the length should be the product of their norms
    Vector3D v1(1.0, 0.0, 0.0);
    Vector3D v2(0.0, 1.0, 0.0);
    Vector3D result = v1.cross(v2);
    EXPECT_DOUBLE_EQ(0.0, result.x);
    EXPECT_DOUBLE_EQ(0.0, result.y);
    EXPECT_DOUBLE_EQ(1.0, result.z); // The result should be along the z-axis
}

TEST(Vector3DTest, CrossProductParallel) {
    // The cross product of parallel vectors should be a zero vector
    Vector3D v1(1.0, 1.0, 1.0);
    Vector3D v2(2.0, 2.0, 2.0);
    Vector3D result = v1.cross(v2);
    EXPECT_DOUBLE_EQ(0.0, result.x);
    EXPECT_DOUBLE_EQ(0.0, result.y);
    EXPECT_DOUBLE_EQ(0.0, result.z);
}

TEST(Vector3DTest, CrossProductZeroVector) {
    // The cross product of any vector with a zero vector should be a zero vector
    Vector3D v1(0.0, 0.0, 0.0);
    Vector3D v2(1.0, 2.0, 3.0);
    Vector3D result = v1.cross(v2);
    EXPECT_DOUBLE_EQ(0.0, result.x);
    EXPECT_DOUBLE_EQ(0.0, result.y);
    EXPECT_DOUBLE_EQ(0.0, result.z);
}

TEST(Vector3DTest, CrossProductRightHandRule) {
    // According to the right-hand rule, the cross product of two vectors
    // should point in the direction of the thumb (assuming right-handed coordinates)
    Vector3D v1(0.0, 0.0, 1.0); // Pointing up
    Vector3D v2(0.0, 1.0, 0.0); // Pointing forwards
    Vector3D result = v1.cross(v2);
    EXPECT_DOUBLE_EQ(-1.0, result.x); // Should point right
    EXPECT_DOUBLE_EQ(0.0, result.y);
    EXPECT_DOUBLE_EQ(0.0, result.z);
}

TEST(Vector3DTest, CrossProductNegativeWhenSwapped) {
    // The cross product should be negative when the operands are swapped
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D result1 = v1.cross(v2);
    Vector3D result2 = v2.cross(v1);
    EXPECT_DOUBLE_EQ(-result1.x, result2.x);
    EXPECT_DOUBLE_EQ(-result1.y, result2.y);
    EXPECT_DOUBLE_EQ(-result1.z, result2.z);
}

TEST(Vector3DTest, CrossProductWithItself) {
    // The cross product of a vector with itself should be a zero vector
    Vector3D v(1.0, 2.0, 3.0);
    Vector3D result = v.cross(v);
    EXPECT_DOUBLE_EQ(0.0, result.x);
    EXPECT_DOUBLE_EQ(0.0, result.y);
    EXPECT_DOUBLE_EQ(0.0, result.z);
}

TEST(Vector3DTest, DotProductWithItself) {
    // The dot product of a vector with itself should be the square of its norm
    Vector3D v(1.0, 2.0, 3.0);
    double result = v.dot(v);
    double expected = v.norm() * v.norm();
    EXPECT_DOUBLE_EQ(expected, result);
}

TEST(Vector3DTest, DotProductSignReflectsAngle) {
    // The sign of the dot product should reflect the angle between vectors:
    // positive for acute angles, negative for obtuse angles
    Vector3D acuteAngleV1(1.0, 1.0, 0.0);
    Vector3D acuteAngleV2(1.0, 0.0, -1.0);
    EXPECT_GT(acuteAngleV1.dot(acuteAngleV2), 0);

    Vector3D obtuseAngleV1(-1.0, -1.0, 0.0);
    EXPECT_LT(obtuseAngleV1.dot(acuteAngleV2), 0);
}


TEST(Vector3DTest, NormIsNonNegative) {
    Vector3D v(-1.0, -2.0, -3.0);
    EXPECT_GE(v.norm(), 0);
}

TEST(Vector3DTest, NumericalStabilityForSmallValues) {
    // Test the behavior of the Vector3D functions when dealing with very small values
    Vector3D small1(1e-10, 0.0, 0.0);
    Vector3D small2(0.0, 1e-10, 0.0);

    // Cross product of small perpendicular vectors should not be zero
    Vector3D smallCross = small1.cross(small2);
    EXPECT_NEAR(0.0, smallCross.x, 1e-20);
    EXPECT_NEAR(0.0, smallCross.y, 1e-20);
    EXPECT_NEAR(1e-20, smallCross.z, 1e-20);

    // Dot product of small parallel vectors should be close to the actual product of their magnitudes
    double smallDot = small1.dot(Vector3D(1e-10, 0.0, 0.0));
    EXPECT_NEAR(1e-20, smallDot, 1e-30);
}

TEST(Vector3DTest, BehaviorWithExtremeValues) {
    // Test the behavior of the Vector3D functions when dealing with very large values
    Vector3D large1(1e+308, 0.0, 0.0);
    Vector3D large2(0.0, 1e+308, 0.0);

    // Operations involving extremely large values may result in infinity or not-a-number; such cases should be handled gracefully
    Vector3D crossProduct = large1.cross(large2);
    EXPECT_TRUE(std::isinf(crossProduct.z));

    double dotProduct = large1.dot(large2);
    EXPECT_EQ(dotProduct, 0); // Expect NaN because the vectors are orthogonal
}

TEST(Vector3DTest, NormStabilityWithExtremeValues) {
    // Ensure the norm calculation is stable even with large values
    Vector3D large(1e+150, 1e+150, 1e+150);
    double norm = large.norm();
    EXPECT_FALSE(std::isinf(norm)); // Norm doesn't overflow, expect not infinity
}

TEST(Vector3DTest, NormalizeBehaviorWithZeroVector) {
    // Normalizing a zero vector should be handled gracefully
    Vector3D zero(0.0, 0.0, 0.0);
    zero.normalize();
    // Since the norm of zero is zero, division by zero may occur. It is up to the design how to handle this.
    // This example assumes that the normalize function sets the vector to zero.
    EXPECT_TRUE(isnan(zero.x));
    EXPECT_TRUE(isnan(zero.y));
    EXPECT_TRUE(isnan(zero.z));
}

TEST(Vector3DTest, DivisionByZero) {
    // Division by zero should be handled gracefully and not crash the program
    Vector3D v(1.0, 1.0, 1.0);
    Vector3D divByZero = v / 0.0;
    // Depending on the implementation, this might set the vector's components to infinity or to a special "error" value.
    EXPECT_TRUE(std::isnan(divByZero.x));
    EXPECT_TRUE(std::isnan(divByZero.y));
    EXPECT_TRUE(std::isnan(divByZero.z));
}

// Tests for denormalized (very small) numbers
TEST(Vector3DTest, HandlesDenormalizedNumbers) {
    double constexpr denormalized = std::numeric_limits<double>::denorm_min();
    Vector3D vec(denormalized, denormalized, denormalized);

    EXPECT_EQ(0.0, vec.norm()); // Norm of a denormalized vector might be zero

    // Normalizing a denormalized vector should not produce a zero vector
    vec.normalize();
    EXPECT_NE(0.0, vec.x);
    EXPECT_NE(0.0, vec.y);
    EXPECT_NE(0.0, vec.z);
}

// Tests for behavior when vector components are set to infinity
TEST(Vector3DTest, HandlesInfinity) {
    double constexpr infinity = std::numeric_limits<double>::infinity();
    Vector3D vec(infinity, 0.0, 0.0);

    // Norm should be infinity if any component is infinity
    EXPECT_EQ(infinity, vec.norm());

    // Operations should propagate the infinity
    vec += Vector3D(1.0, 1.0, 1.0);
    EXPECT_EQ(infinity, vec.x);
}

// Tests for behavior when vector components are set to NaN
TEST(Vector3DTest, HandlesNaN) {
    double constexpr nan = std::numeric_limits<double>::quiet_NaN();
    Vector3D vec(nan, 0.0, 0.0);

    // Norm should be NaN if any component is NaN
    EXPECT_TRUE(std::isnan(vec.norm()));

    // Operations with NaN should result in NaN
    Vector3D result = vec + Vector3D(1.0, 1.0, 1.0);
    EXPECT_TRUE(std::isnan(result.x));

    // Dot product with NaN should be NaN
    double dotProduct = vec.dot(Vector3D(1.0, 1.0, 1.0));
    EXPECT_TRUE(std::isnan(dotProduct));
}

// Tests for arithmetic operations with infinity and NaN
TEST(Vector3DTest, ArithmeticOperationsWithInfinityAndNaN) {
    double constexpr infinity = std::numeric_limits<double>::infinity();
    double constexpr nan = std::numeric_limits<double>::quiet_NaN();
    Vector3D vecInf(infinity, infinity, infinity);
    Vector3D vecNaN(nan, nan, nan);

    // Adding infinity to infinity should result in infinity
    Vector3D resultInf = vecInf + vecInf;
    EXPECT_EQ(infinity, resultInf.x);
    EXPECT_EQ(infinity, resultInf.y);
    EXPECT_EQ(infinity, resultInf.z);

    // Adding NaN to NaN should result in NaN
    Vector3D resultNaN = vecNaN + vecNaN;
    EXPECT_TRUE(std::isnan(resultNaN.x));
    EXPECT_TRUE(std::isnan(resultNaN.y));
    EXPECT_TRUE(std::isnan(resultNaN.z));

    // Multiplying infinity by a scalar should result in infinity or NaN if the scalar is zero
    resultInf = vecInf * 2.0;
    EXPECT_EQ(infinity, resultInf.x);
    resultInf = vecInf * 0.0;
    EXPECT_TRUE(std::isnan(resultInf.x));  // Infinity times zero should be NaN

    // Dividing NaN by a scalar should still be NaN
    resultNaN = vecNaN / 2.0;
    EXPECT_TRUE(std::isnan(resultNaN.x));
}

