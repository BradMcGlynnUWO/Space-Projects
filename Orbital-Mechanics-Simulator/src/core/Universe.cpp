#include "Universe.h"
#include "PhysicsEngine.h"
#include <algorithm>

void Universe::addBody(std::shared_ptr<Body> body) {
    bodies.push_back(std::move(body));
}

void Universe::removeBody(const std::string& bodyName) {
    bodies.erase(
        std::remove_if(bodies.begin(), bodies.end(),
                       [&bodyName](const std::shared_ptr<Body>& body) {
                           return body->getName() == bodyName;
                       }),
        bodies.end());
}

void Universe::update(PhysicsEngine& engine, double deltaTime) {
    // PhysicsEngine now calculates forces
    engine.simulateUniverse(bodies, deltaTime);

    // Check for collisions
    checkCollisions();
}

void Universe::checkCollisions() {
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            if (bodies[i]->isColliding(*bodies[j])) {
                handleCollision(*bodies[i], *bodies[j]);
            }
        }
    }
}

bool Universe::isColliding(const std::shared_ptr<Body>& a, const std::shared_ptr<Body>& b) const {
    double distance = Vector3D::distance(a->getPosition(), b->getPosition());
    return distance < (a->getRadius() + b->getRadius()); 
}

void Universe::handleCollision(std::shared_ptr<Body>& a, std::shared_ptr<Body>& b) {
     // For a simple model where bodies merge:
    double totalMass = a->getMass() + b->getMass();
    Vector3D newPosition = (a->getPosition() * a->getMass() + b->getPosition() * b->getMass()) / totalMass;
    Vector3D newVelocity = (a->getVelocity() * a->getMass() + b->getVelocity() * b->getMass()) / totalMass;
    
    // Calculate the new radius by taking the larger radius of the two bodies
    double newRadius = std::max(a->getRadius(), b->getRadius());

    // Create a new body with combined mass, calculated velocity, and new radius
    std::shared_ptr<Body> newBody = std::make_shared<Body>("MergedBody", totalMass, newRadius, newPosition, newVelocity);
    
    // Add the new body to the simulation and remove the old ones
    addBody(newBody);
    removeBody(a);
    removeBody(b);
}

const std::vector<std::shared_ptr<Body>>& Universe::getBodies() const {
    return bodies;
}
