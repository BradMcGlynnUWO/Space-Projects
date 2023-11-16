#include <gtest/gtest.h>
#include "Universe.h"
#include "PhysicsEngine.h"

const double SMALL_TOLERANCE = 1e-5;
const double LARGE_TOLERANCE = 1e-2;
const double REASONABLE_MAX_FORCE = 1e12; // Adjust this as necessary


class UniverseTest : public ::testing::Test {
protected:
    Universe universe;
    PhysicsEngine physicsEngine;
    double deltaTime;

    void SetUp() override {
        deltaTime = 1; // 1 second for simplicity
        // Add more setup if needed
    }
};

TEST_F(UniverseTest, AddRemoveBody) {
    auto body = std::make_shared<Body>("TestBody", 1000, 1, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
    universe.addBody(body);
    
    EXPECT_EQ(universe.getBodies().size(), 1); // Check if body is added

    universe.removeBody("TestBody");
    EXPECT_TRUE(universe.getBodies().empty()); // Check if body is removed
}

TEST_F(UniverseTest, UpdateUniverse) {
    auto body1 = std::make_shared<Body>("Body1", 1000, 1, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
    auto body2 = std::make_shared<Body>("Body2", 2000, 1, Vector3D(10, 0, 0), Vector3D(0, 0, 0));
    universe.addBody(body1);
    universe.addBody(body2);

    universe.update(physicsEngine, deltaTime);

    // Check if positions and velocities of bodies are updated
    EXPECT_NE(body1->getPosition(), Vector3D(0, 0, 0));
    EXPECT_NE(body2->getPosition(), Vector3D(10, 0, 0));
}

TEST_F(UniverseTest, CollisionHandling) {
    auto body1 = std::make_shared<Body>("Body1", 1000, 1, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
    auto body2 = std::make_shared<Body>("Body2", 1000, 1, Vector3D(1.9, 0, 0), Vector3D(0, 0, 0)); // Positioned to collide with body1
    universe.addBody(body1);
    universe.addBody(body2);

    universe.update(physicsEngine, deltaTime);

    // Check if the collision resulted in a single body
    EXPECT_EQ(universe.getBodies().size(), 1);
    // Further checks can be added to validate the properties of the new merged body
}

