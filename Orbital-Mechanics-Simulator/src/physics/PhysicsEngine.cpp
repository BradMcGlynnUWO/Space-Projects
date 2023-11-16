#include "PhysicsEngine.h"
#include <algorithm>
#include <iostream>

const double G = 6.67430e-11; // Gravitational constant

// Calculate the gravitational force between two bodies
Vector3D PhysicsEngine::calculateGravitationalForce(const std::shared_ptr<Body>& a, const std::shared_ptr<Body>& b) {
    Vector3D r = b->getPosition() - a->getPosition();
    double distanceSquared = std::max(r.squaredMagnitude(), a->getRadius() * b->getRadius()); // Avoid division by zero or too small distances
    double forceMagnitude = (G * a->getMass() * b->getMass()) / distanceSquared;
    Vector3D force = r.normalized() * forceMagnitude;
    return force;
}

// Update the velocity and position of a body using the calculated force
void PhysicsEngine::updateBody(std::shared_ptr<Body>& body, const Vector3D& force, double deltaTime) {
    if(body->getMass() == 0) return; // Skip update for zero mass body
    Vector3D acceleration = force / body->getMass();
    // Semi-implicit Euler method for integration, which is symplectic and better for conservation
    body->setVelocity(body->getVelocity() + acceleration * deltaTime);
    body->setPosition(body->getPosition() + body->getVelocity() * deltaTime);
}

// Function to simulate all bodies within a universe for a time step
void PhysicsEngine::simulateUniverse(std::vector<std::shared_ptr<Body>>& bodies, double deltaTime) {
    // Reset forces before calculation
    for (auto& body : bodies) {
        body->resetForce();
    }

    // Calculate forces
    for (size_t i = 0; i < bodies.size(); i++) {
        for (size_t j = i + 1; j < bodies.size(); j++) {
            Vector3D force = calculateGravitationalForce(bodies[i], bodies[j]);
            bodies[i]->addForce(force);
            bodies[j]->addForce(force * -1); // Newton's third law
        }
    }

    // Update body states
    for (auto& body : bodies) {
        updateBody(body, body->getForce(), deltaTime);
    }
}

// Adaptive time-stepping can be implemented by varying deltaTime based on the dynamics of the system
// For example, during close encounters or high-velocity events, deltaTime can be reduced
double PhysicsEngine::adaptiveTimeStep(double initialTimeStep, const std::vector<std::shared_ptr<Body>>& bodies) {
    // Simple example - refine based on specific criteria relevant to your simulation
    double minDistanceSquared = std::numeric_limits<double>::max();
    for (size_t i = 0; i < bodies.size(); i++) {
        for (size_t j = i + 1; j < bodies.size(); j++) {
            double distanceSquared = (bodies[i]->getPosition() - bodies[j]->getPosition()).squaredMagnitude();
            minDistanceSquared = std::min(minDistanceSquared, distanceSquared);
        }
    }

    // Adjust time step based on the closest pair of bodies
    double factor = std::sqrt(minDistanceSquared);
    return std::min(initialTimeStep, factor / 1000.0); // Arbitrary factor for safety
}
