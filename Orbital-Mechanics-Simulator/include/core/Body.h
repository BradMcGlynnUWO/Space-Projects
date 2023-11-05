#ifndef BODY_H
#define BODY_H

#include "Vector3D.h"
#include <string>

// Forward declaration
class PhysicsEngine;

class Body {
private:
    Vector3D position;
    Vector3D velocity;
    Vector3D force;
    double mass;
    double radius;
    std::string name;

public:
    // Constructor
    Body(const std::string& name, double mass, double radius, const Vector3D& position, const Vector3D& velocity);

    // Getters
    const Vector3D& getPosition() const;
    const Vector3D& getVelocity() const;
    const Vector3D& getForce() const;
    double getMass() const;
    double getRadius() const;
    const std::string& getName() const;

    // Setters
    void setPosition(const Vector3D& newPosition);
    void setVelocity(const Vector3D& newVelocity);
    void setForce(const Vector3D& newForce);
    void setMass(double newMass);
    void setRadius(double newRadius);

    // Physics methods
    void addForce(const Vector3D& additionalForce);
    void resetForce();

    // Update the motion of the body based on its force and a time step
    void update(PhysicsEngine& engine, double deltaTime);
};

#endif // BODY_H
