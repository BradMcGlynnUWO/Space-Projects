#include "PhysicsEngine.h"

// Calculate the gravitational force between two bodies
Vector3D PhysicsEngine::calculateGravitationalForce(const std::shared_ptr<Body>& a, const std::shared_ptr<Body>& b) {
    Vector3D r = b->getPosition() - a->getPosition();
    double distanceSquared = r.squaredMagnitude();
    double forceMagnitude = (G * a->getMass() * b->getMass()) / distanceSquared;
    Vector3D force = r.normalized() * forceMagnitude;
    return force;
}

// Update the velocity and position of a body using the calculated force
void PhysicsEngine::updateBody(std::shared_ptr<Body>& body, const Vector3D& force, double deltaTime) {
    Vector3D acceleration = force / body->getMass();
    body->setVelocity(body->getVelocity() + acceleration * deltaTime);
    body->setPosition(body->getPosition() + body->getVelocity() * deltaTime);
}

// Function to simulate all bodies within a universe for a time step
void PhysicsEngine::simulateUniverse(std::vector<std::shared_ptr<Body>>& bodies, double deltaTime) {
    for (size_t i = 0; i < bodies.size(); i++) {
        for (size_t j = i + 1; j < bodies.size(); j++) {
            Vector3D force = calculateGravitationalForce(bodies[i], bodies[j]);
            bodies[i]->addForce(force);
            bodies[j]->addForce(-force); // Newton's third law
        }
    }

    for (auto& body : bodies) {
        updateBody(body, body->getForce(), deltaTime);
        body->resetForce();
    }
}
