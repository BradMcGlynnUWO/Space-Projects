#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "Vector3D.h"
#include "Body.h"
#include <vector>
#include <memory>
#include <cmath>

class PhysicsEngine {
public:
    static constexpr double G = 6.67430e-11;

    static Vector3D calculateGravitationalForce(const std::shared_ptr<Body>& a, const std::shared_ptr<Body>& b);
    static void updateBody(std::shared_ptr<Body>& body, const Vector3D& force, double deltaTime);
    static void simulateUniverse(std::vector<std::shared_ptr<Body>>& bodies, double deltaTime);
    static double adaptiveTimeStep(double initialTimeStep, const std::vector<std::shared_ptr<Body>>& bodies);
};

#endif // PHYSICSENGINE_H
