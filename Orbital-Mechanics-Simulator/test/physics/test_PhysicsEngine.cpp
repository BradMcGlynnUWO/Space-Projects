#include <gtest/gtest.h>
#include "Body.h"
#include "PhysicsEngine.h"

const double G = 6.67430e-11; // Gravitational constant
const double SMALL_TOLERANCE = 1e-5;
const double LARGE_TOLERANCE = 1e-2;
const double REASONABLE_MAX_FORCE = 1e12; // Adjust this as necessary

class PhysicsEngineTest : public ::testing::Test {
protected:
    std::shared_ptr<Body> body1;
    std::shared_ptr<Body> body2;
    PhysicsEngine physicsEngine;
    double deltaTime;

    void SetUp() override {
        // Initialize bodies with properties for testing
        body1 = std::make_shared<Body>("Body1", 1000, 1, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        body2 = std::make_shared<Body>("Body2", 2000, 1, Vector3D(10, 0, 0), Vector3D(0, 0, 0));
        deltaTime = 1; // Example time step
    }
};


TEST_F(PhysicsEngineTest, CalculateGravitationalForce) {
    Vector3D force = physicsEngine.calculateGravitationalForce(body1, body2);
    // Calculate expected force based on gravitational law
    double distance = (body2->getPosition() - body1->getPosition()).norm();
    double expectedMagnitude = G * body1->getMass() * body2->getMass() / (distance * distance);
    // Check if the force magnitude is correct
    EXPECT_NEAR(force.norm(), expectedMagnitude, SMALL_TOLERANCE);
}

TEST_F(PhysicsEngineTest, UpdateBody) {
    Vector3D initialPosition = body1->getPosition();
    Vector3D force(10.0, 0.0, 0.0);
    physicsEngine.updateBody(body1, force, deltaTime);

    Vector3D expectedPosition = initialPosition + body1->getVelocity() * deltaTime;
    EXPECT_EQ(body1->getPosition(), expectedPosition);
    // Additional checks for velocity update can be added
}

TEST_F(PhysicsEngineTest, SimulateUniverse) {
    std::vector<std::shared_ptr<Body>> bodies = {body1, body2};
    Vector3D initialPositionBody1 = body1->getPosition();
    Vector3D initialPositionBody2 = body2->getPosition();

    physicsEngine.simulateUniverse(bodies, deltaTime);

    // Check that positions and velocities of bodies are updated
    EXPECT_NE(body1->getPosition(), initialPositionBody1);
    EXPECT_NE(body2->getPosition(), initialPositionBody2);
}

TEST_F(PhysicsEngineTest, AdaptiveTimeStep) {
    double initialTimeStep = 1.0;
    double newTimeStep = physicsEngine.adaptiveTimeStep(initialTimeStep, {body1, body2});

    // Check if the time step was adjusted correctly based on the bodies' positions
    EXPECT_LE(newTimeStep, initialTimeStep);
}

TEST_F(PhysicsEngineTest, ExtremelyCloseBodies) {
    body2->setPosition(Vector3D(1e-9, 0, 0)); // Set body2 very close to body1

    std::vector<std::shared_ptr<Body>> bodies = {body1, body2};
    physicsEngine.simulateUniverse(bodies, deltaTime);

    // Expect the force to be large, but not unreasonably so (avoiding infinite or NaN values)
    Vector3D force = body1->getForce();
    EXPECT_LT(force.norm(), REASONABLE_MAX_FORCE);
    EXPECT_TRUE(std::isfinite(force.norm()));
}

TEST_F(PhysicsEngineTest, HighVelocityBodies) {
    body1->setVelocity(Vector3D(1e+9, 0, 0)); // Set a high velocity for body1

    std::vector<std::shared_ptr<Body>> bodies = {body1, body2};
    physicsEngine.simulateUniverse(bodies, deltaTime);

    // Check that the position and velocity update is stable and does not result in unreasonable values
    EXPECT_TRUE(std::isfinite(body1->getPosition().norm()));
    EXPECT_TRUE(std::isfinite(body1->getVelocity().norm()));
}

TEST_F(PhysicsEngineTest, LargeMassDifference) {
    body1->setMass(1e+30); // Set a very large mass for body1
    body2->setMass(1); // Set a very small mass for body2

    std::vector<std::shared_ptr<Body>> bodies = {body1, body2};
    physicsEngine.simulateUniverse(bodies, deltaTime);

    // The large mass body should exert a significant force on the small mass body
    Vector3D forceOnBody2 = body2->getForce();
    EXPECT_GT(forceOnBody2.norm(), 0); // Force should be non-zero
    EXPECT_TRUE(std::isfinite(forceOnBody2.norm()));
}

TEST_F(PhysicsEngineTest, BodiesInOppositeMotion) {
    body1->setVelocity(Vector3D(1e+5, 0, 0)); // Fast in the +x direction
    body2->setVelocity(Vector3D(-1e+5, 0, 0)); // Fast in the -x direction

    std::vector<std::shared_ptr<Body>> bodies = {body1, body2};
    physicsEngine.simulateUniverse(bodies, deltaTime);

    // Check that the bodies continue to move in their respective directions
    EXPECT_GT(body1->getPosition().x, 0);
    EXPECT_LT(body2->getPosition().x, 10); // Assuming initial position at (10, 0, 0)
}

TEST_F(PhysicsEngineTest, StationaryAndMovingBody) {
    body1->setVelocity(Vector3D(0, 0, 0)); // Stationary

    Vector3D directionToBody1 = body1->getPosition() - body2->getPosition();
    body2->setVelocity(directionToBody1.normalized() * 1.1); // Set a velocity towards body1

    std::vector<std::shared_ptr<Body>> bodies = {body1, body2};
    double initialDistance = (body2->getPosition() - body1->getPosition()).norm();
    physicsEngine.simulateUniverse(bodies, deltaTime);

    // Expect body2 to be attracted towards body1, reducing the distance between them
    double newDistance = (body2->getPosition() - body1->getPosition()).norm();
    EXPECT_LT(newDistance, initialDistance);
}

TEST_F(PhysicsEngineTest, BodiesAtExtremeDistances) {
    body2->setPosition(Vector3D(1e+12, 0, 0)); // Very far from body1

    std::vector<std::shared_ptr<Body>> bodies = {body1, body2};
    physicsEngine.simulateUniverse(bodies, deltaTime);

    // Expect the gravitational force to be very small
    Vector3D force = body1->getForce();
    EXPECT_NEAR(force.norm(), 0, SMALL_TOLERANCE);
}
