#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D {
public:
    double x, y, z;

    // Constructors
    Vector3D();
    Vector3D(double x, double y, double z);

    // Copy constructor
    Vector3D(const Vector3D& v);

    // Assignment operator
    Vector3D& operator=(const Vector3D& v);

    // Vector addition and subtraction
    Vector3D operator+(const Vector3D& v) const;
    Vector3D& operator+=(const Vector3D& v);
    Vector3D operator-(const Vector3D& v) const;
    Vector3D& operator-=(const Vector3D& v);

    // Scalar multiplication and division
    Vector3D operator*(double scalar) const;
    Vector3D& operator*=(double scalar);
    Vector3D operator/(double scalar) const;
    Vector3D& operator/=(double scalar);

    // Dot product
    double dot(const Vector3D& v) const;

    // Cross product
    Vector3D cross(const Vector3D& v) const;

    // Norm (length of the vector)
    double norm() const;

    // Normalize the vector (make it unit length)
    Vector3D& normalize();

    // Utility function for distance between two vectors
    static double distance(const Vector3D& v1, const Vector3D& v2);
};

#endif // VECTOR3D_H
