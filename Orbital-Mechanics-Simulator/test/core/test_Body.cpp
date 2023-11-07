#include <gtest/gtest.h>
#include "Body.h"
#include "PhysicsEngine.h"

const double SMALL_TOLERANCE = 1e-5;
const double LARGE_TOLERANCE = 1e-2;
const double REASONABLE_MAX_FORCE = 1e12; // Adjust this as necessary

class BodyTest : public ::testing::Test {
protected:
    std::shared_ptr<Body> body1;
    std::shared_ptr<Body> body2;
    PhysicsEngine physicsEngine;
    double deltaTime;

    void SetUp() override {
        // Initialize two bodies with different properties
        body1 = std::make_shared<Body>("Body1", 1000, 1, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        body2 = std::make_shared<Body>("Body2", 2000, 1, Vector3D(10, 0, 0), Vector3D(0, 0, 0));
        deltaTime = 1; // 1 second for simplicity
    }
};

TEST_F(BodyTest, Instantiation) {
    Vector3D position(100.0, 200.0, 300.0);
    Vector3D velocity(1.0, 1.0, 1.0);
    Body body("Earth", 5.972e24, 6371.0, position, velocity);

    EXPECT_EQ(body.getName(), "Earth");
    EXPECT_DOUBLE_EQ(body.getMass(), 5.972e24);
    EXPECT_DOUBLE_EQ(body.getRadius(), 6371.0);
    EXPECT_TRUE(body.getPosition() == position);
    EXPECT_TRUE(body.getVelocity() == velocity);
}

TEST_F(BodyTest, ForceApplicationAndReset) {
    Vector3D force(10.0, 0.0, 0.0);

    body1->addForce(force);
    EXPECT_TRUE(body1->getForce() == force);

    body1->resetForce();
    EXPECT_TRUE(body1->getForce() == Vector3D());
}

TEST_F(BodyTest, MassAndRadiusUpdate) {
    body1->setMass(2.0);
    EXPECT_DOUBLE_EQ(body1->getMass(), 2.0);

    body1->setRadius(2.0);
    EXPECT_DOUBLE_EQ(body1->getRadius(), 2.0);
}

TEST_F(BodyTest, PositionAndVelocityUpdate) {
    Vector3D newPosition(50.0, 50.0, 50.0);
    Vector3D newVelocity(5.0, 5.0, 5.0);

    body1->setPosition(newPosition);
    EXPECT_TRUE(body1->getPosition() == newPosition);

    body1->setVelocity(newVelocity);
    EXPECT_TRUE(body1->getVelocity() == newVelocity);
}

TEST_F(BodyTest, MotionUpdate) {
    Vector3D force(10.0, 0.0, 0.0);

    body1->addForce(force);
    physicsEngine.updateBody(body1->get(), body1->getForce(), deltaTime);
    
    // Verify the body's velocity and position have been updated appropriately
    Vector3D expectedVelocity = force / body1->getMass() * deltaTime;
    Vector3D expectedPosition = body1->getPosition() + expectedVelocity * deltaTime;
    
    EXPECT_NEAR(body1->getVelocity().x, expectedVelocity.x, 1e-5);
    EXPECT_NEAR(body1->getPosition().x, expectedPosition.x, 1e-5);
}

TEST_F(BodyTest, ZeroAndNegativeMass) {
    Body zeroMassBody("ZeroMass", 0.0, 1.0, Vector3D(), Vector3D());
    Body negativeMassBody("NegativeMass", -1.0, 1.0, Vector3D(), Vector3D());

    EXPECT_GT(zeroMassBody.getMass(), 0.0);
    EXPECT_GT(negativeMassBody.getMass(), 0.0);
}

TEST_F(BodyTest, PositionUpdateWithDeltaTime) {
    body1->setVelocity(Vector3D(10.0, 10.0, 10.0));
    double smallDeltaTime = 1e-9; // Very small time step
    double largeDeltaTime = 1e3;  // Very large time step

    physicsEngine.updateBody(body1->get(), body1->getForce(), smallDeltaTime);
    EXPECT_NEAR(body1->getPosition().x, smallDeltaTime * 10.0, 1e-5);

    physicsEngine.updateBody(body1->get(), body1->getForce(), largeDeltaTime);
    EXPECT_NEAR(body1->getPosition().x, largeDeltaTime * 10.0, 1e-5);
}

TEST_F(BodyTest, DivisionByZeroInForces) {
    //Body body3("Body3", 1e24, 1e6, Vector3D(), Vector3D()); // Same position as body1
    // make a shared_ptr version of body3
    std::shared_ptr<Body> body3_ptr = std::make_shared<Body>(("Body3", 1e24, 1e6, Vector3D(), Vector3D()));
    
    
    Vector3D force = physicsEngine.calculateGravitationalForce(body1->get(), body3->get());

    EXPECT_FALSE(std::isinf(force.x));
    EXPECT_FALSE(std::isnan(force.x));
    EXPECT_TRUE(force == Vector3D());
}

TEST_F(BodyTestFixture, PositionUpdateWithDeltaTime) {
    double smallDeltaTime = 1e-9; // Very small time step
    double largeDeltaTime = 1e3;  // Very large time step

    engine.updateBody(body1->get(), Vector3D(), smallDeltaTime);
    EXPECT_NEAR(body1->getPosition().x, smallDeltaTime * body1->getVelocity().x, SMALL_TOLERANCE);

    engine.updateBody(body1->get(), Vector3D(), largeDeltaTime);
    EXPECT_NEAR(body1->getPosition().x, largeDeltaTime * body1->getVelocity().x, LARGE_TOLERANCE);
}

TEST_F(BodyTestFixture, CloseProximityForces) {
    Vector3D force = calculateGravitationalForce(body1->get(), body2->get());
    body1->addForce(force);
    EXPECT_NE(force, Vector3D(std::numeric_limits<double>::infinity(), 0.0, 0.0));
    EXPECT_LT(force.norm(), REASONABLE_MAX_FORCE);
}

// Test extreme gravitational forces
TEST_F(BodyTest, ExtremeGravitationalForce) {
    // Update body positions to be very close
    body2->setPosition(Vector3D(1e-3, 0, 0));

    // Simulate the universe
    physicsEngine.simulateUniverse({body1->get(), body2->get()}, deltaTime);

    // Check if the force is not unreasonably high
    Vector3D force = body1->getForce();
    EXPECT_LE(force.norm(), REASONABLE_MAX_FORCE);
}

// Test extended period motion
TEST_F(BodyTest, ExtendedPeriodMotion) {
    // Simulate the universe for an extended period
    for (int i = 0; i < 10000; ++i) {
        physicsEngine.simulateUniverse({body1->get(), body2->get()}, deltaTime);
    }

    // Expect the bodies to not drift to infinity or collapse into each other
    double distance = (body2->getPosition() - body1->getPosition()).norm();
    EXPECT_GT(distance, 0.0);
    EXPECT_LT(distance, std::numeric_limits<double>::max());
}

// Test series of forces
TEST_F(BodyTest, SeriesOfForces) {
    Vector3D force1(100, 0, 0);
    Vector3D force2(0, 100, 0);
    Vector3D force3(0, 0, 100);

    // Apply a series of forces to the body
    body1->addForce(force1);
    body1->addForce(force2);
    body1->addForce(force3);

    physicsEngine.updateBody(body1->get(), body1->getForce(), deltaTime);

    // Check the net force is the sum of the individual forces
    Vector3D expectedForce = force1 + force2 + force3;
    EXPECT_NEAR(body1->getForce().x, expectedForce.x, SMALL_TOLERANCE);
    EXPECT_NEAR(body1->getForce().y, expectedForce.y, SMALL_TOLERANCE);
    EXPECT_NEAR(body1->getForce().z, expectedForce.z, SMALL_TOLERANCE);
}

// Test close pass calculations
TEST_F(BodyTest, ClosePassCalculations) {
    // Bring two bodies very close to each other
    body2->setPosition(Vector3D(1e-5, 0, 0));

    // Simulate the universe
    physicsEngine.simulateUniverse({body1->get(), body2->get()}, deltaTime);

    // Ensure that forces do not become infinite or NaN
    Vector3D force = body1->getForce();
    EXPECT_FALSE(std::isinf(force.norm()));
    EXPECT_FALSE(std::isnan(force.norm()));
    EXPECT_GT(force.norm(), 0.0); // Should be a significant force, but not infinite
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}