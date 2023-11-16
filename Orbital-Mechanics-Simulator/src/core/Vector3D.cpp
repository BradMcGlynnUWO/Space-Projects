#include "Vector3D.h"
#include <cmath>
#include <limits>

// Helper function to check if a number is a valid operand
bool isValidOperand(double value) {
    // Check if the value is not infinity or NaN
    return !std::isinf(value) && !std::isnan(value);
}

// Constructors
Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {}
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

// Copy constructor
Vector3D::Vector3D(const Vector3D& v) : x(v.x), y(v.y), z(v.z) {}

// Assignment operator
Vector3D& Vector3D::operator=(const Vector3D& v) {
    if (this != &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    return *this;
}

// Vector addition and subtraction
Vector3D Vector3D::operator+(const Vector3D& v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D& Vector3D::operator+=(const Vector3D& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D& Vector3D::operator-=(const Vector3D& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3D Vector3D::operator*(double scalar) const {
    if (!isValidOperand(scalar)) return Vector3D(scalar, scalar, scalar);
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D& Vector3D::operator*=(double scalar) {
    if (!isValidOperand(scalar)) {
        x = y = z = scalar;
    } else {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }
    return *this;
}

Vector3D Vector3D::operator/(double scalar) const {
    if (scalar == 0.0 || !isValidOperand(scalar)) {
        return Vector3D(std::numeric_limits<double>::quiet_NaN(),
                        std::numeric_limits<double>::quiet_NaN(),
                        std::numeric_limits<double>::quiet_NaN());
    }
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

Vector3D& Vector3D::operator/=(double scalar) {
    if (scalar == 0.0 || !isValidOperand(scalar)) {
        x = y = z = std::numeric_limits<double>::quiet_NaN();
    } else {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
    return *this;
}

// Equality
bool Vector3D::operator==(const Vector3D& v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool Vector3D::operator!=(const Vector3D& v) const {
    return !(*this == v);
}

// Dot product
double Vector3D::dot(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// Cross product
Vector3D Vector3D::cross(const Vector3D& v) const {
    return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

// Norm (length of the vector)
double Vector3D::norm() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize the vector (make it unit length)
Vector3D& Vector3D::normalize() {
    double n = norm();
    if (n > 0.0 && isValidOperand(n)) {
        x /= n;
        y /= n;
        z /= n;
    } else {
        x = y = z = std::numeric_limits<double>::quiet_NaN();
    }
    return *this;
}

// Utility function for distance between two vectors
double Vector3D::distance(const Vector3D& v1, const Vector3D& v2) {
    return (v1 - v2).norm();
}

// Utility function for angle between two vectors
double Vector3D::angle(const Vector3D& v1, const Vector3D& v2) {
    double n1 = v1.norm();
    double n2 = v2.norm();
    if (n1 == 0.0 || n2 == 0.0 || !isValidOperand(n1) || !isValidOperand(n2)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return std::acos(v1.dot(v2) / (n1 * n2));
}

// Calculate and return the squared magnitude of the vector
double Vector3D::squaredMagnitude() const {
    return x * x + y * y + z * z;
}

// Return a normalized version of the vector
Vector3D Vector3D::normalized() const {
    double mag = std::sqrt(squaredMagnitude());
    return (mag > 0) ? Vector3D(x / mag, y / mag, z / mag) : Vector3D();
}
