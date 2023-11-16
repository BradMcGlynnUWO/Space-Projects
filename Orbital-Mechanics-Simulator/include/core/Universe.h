#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "Body.h"
#include <vector>
#include <memory>

// Forward declaration
class PhysicsEngine;

class Universe {
private:
    std::vector<std::shared_ptr<Body>> bodies; // Using shared_ptr for shared ownership

public:
    void addBody(std::shared_ptr<Body> body);
    void removeBody(const std::string& bodyName);
    void update(PhysicsEngine& engine, double deltaTime);
    void checkCollisions();
    void handleCollision(std::shared_ptr<Body>& a, std::shared_ptr<Body>& b);
    bool isColliding(const std::shared_ptr<Body>& a, const std::shared_ptr<Body>& b) const; 
    const std::vector<std::shared_ptr<Body>>& getBodies() const;
};

#endif // UNIVERSE_H
