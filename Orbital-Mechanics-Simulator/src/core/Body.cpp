#include "Body.h"
#include "PhysicsEngine.h"

// Constructor
Body::Body(const std::string& name, double mass, double radius, const Vector3D& position, const Vector3D& velocity)
    : name(name), mass(mass), radius(radius), position(position), velocity(velocity), force(0.0, 0.0, 0.0) {}

// Getters
const Vector3D& Body::getPosition() const { return position; }
const Vector3D& Body::getVelocity() const { return velocity; }
const Vector3D& Body::getForce() const { return force; }
double Body::getMass() const { return mass; }
double Body::getRadius() const { return radius; }
const std::string& Body::getName() const { return name; }

// Setters
void Body::setPosition(const Vector3D& newPosition) { position = newPosition; }
void Body::setVelocity(const Vector3D& newVelocity) { velocity = newVelocity; }
void Body::setForce(const Vector3D& newForce) { force = newForce; }
void Body::setMass(double newMass) { mass = newMass; }
void Body::setRadius(double newRadius) { radius = newRadius; }

// Physics methods

// Add a force to the body
void Body::addForce(const Vector3D& additionalForce) {
    force += additionalForce;
}

// Reset the force on the body to zero
void Body::resetForce() {
    force = Vector3D(0.0, 0.0, 0.0);
}

// Update the motion of the body based on its force and a time step
void Body::update(PhysicsEngine& engine, double deltaTime) {
    engine.updateBody(shared_from_this(), force, deltaTime);
}