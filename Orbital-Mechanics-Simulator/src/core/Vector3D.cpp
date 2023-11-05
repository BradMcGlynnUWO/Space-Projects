#include "Vector3D.h"
#include <cmath>

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

// Scalar multiplication and division
Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D& Vector3D::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3D Vector3D::operator/(double scalar) const {
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

Vector3D& Vector3D::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
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
    if (n > 0.0) {
        x /= n;
        y /= n;
        z /= n;
    }
    return *this;
}

// Utility function for distance between two vectors
double Vector3D::distance(const Vector3D& v1, const Vector3D& v2) {
    return (v1 - v2).norm();
}
