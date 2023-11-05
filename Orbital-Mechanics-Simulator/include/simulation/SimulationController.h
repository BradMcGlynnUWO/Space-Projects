#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include "Universe.h"
#include <string>

class SimulationController {
private:
    Universe universe;             // The simulation environment
    double currentTime;            // Current time within the simulation
    double timeStep;               // The time increment for each simulation step
    bool isRunning;                // Status of the simulation run

    // Other private members as needed for handling events, logging, etc.

public:
    SimulationController(double initialTimeStep);

    void initializeSimulation();   // Setup the simulation environment
    void startSimulation();        // Begin or resume the simulation
    void pauseSimulation();        // Pause the simulation
    void stepSimulation();         // Advance the simulation by one timeStep
    void resetSimulation();        // Reset the simulation to initial conditions

    void addBodyToUniverse(const Body& body);     // Add a new body to the universe
    void removeBodyFromUniverse(const Body& body); // Remove a body from the universe

    void setUniverse(const Universe& newUniverse); // Set a new universe state
    const Universe& getUniverse() const;           // Get the current universe state

    void saveSimulationState(const std::string& filePath);  // Save state to file
    void loadSimulationState(const std::string& filePath);  // Load state from file

    void update(double deltaTime);  // The main update method called each cycle

    // Register a renderer with the simulation controller
    void registerRenderer(RendererInterface* renderer);

    // Register a GUI with the simulation controller
    void registerGUI(GUIInterface* gui);

    // Register a Camera with the simulation controller
    void registerCamera(CameraInterface* camera);

    // Notify renderer of changes in the simulation for visual update
    void updateRenderer();

    // Notify GUI of changes in simulation state for UI update
    void updateGUI();

    // Notify Camera of user input for view changes
    void updateCamera();
    
    // Additional methods for user interaction, logging, etc.
};

#endif // SIMULATIONCONTROLLER_H
