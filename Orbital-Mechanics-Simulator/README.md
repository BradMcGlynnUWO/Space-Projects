# Orbital Simulator

Orbital Simulator is a 3D simulation of celestial bodies that demonstrates the basics of orbital mechanics using OpenGL. The project includes realistic physics calculations, user interaction through an intuitive GUI, and visual representation of various celestial bodies and their orbits.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

Before building and running the project, you need to have the following software installed on your machine:

- A C++ compiler (e.g., GCC, Clang)
- Make
- OpenGL libraries
- GLFW
- GLEW
- GLM
- Dear ImGui (bundled with the project)

### Installing

To install and run the project, follow these steps:

1. Clone the repository to your local machine:

```bash
git clone https://github.com/BradMcGlynnUWO/Space-Projects/Orbital-Mechanics-Simulator.git
```

2. Navigate to the project directory:
```bash
cd Orbital-Mechanics-Simulator
```

3. Build the project usinf the `make` command:
```bash
make all
```

This will compile all the necessary files and create an executable in the `/bin` directory.

## Running the Simulation
To run the simulator, you can use the following command:
```bash
./bin/Orbital-Mechanics-Simulator
```

This will launch the simulation window where you can interact with the simulation through the GUI.

## Project Structure

The project is organized into several directories:

- `/src`: Source code of the project.
  - `/core`: Core classes like `Vector3D`, `Body`, and `Universe`.
  - `/physics`: The physics engine with gravitational calculations.
  - `/rendering`: OpenGL rendering related classes including `Renderer` and `Camera`.
  - `/gui`: User interface handling, built with Dear ImGui.
  - `/simulation`: Contains the `SimulationController` for managing the simulation flow.
  - `/file`: For file input/output operations with `FileManager`.
- `/assets`: Contains static resources like textures and models.
- `/external`: External dependencies such as GLFW and GLM.
- `/bin`: Contains the executable files after build.
- `/docs`: Documentation for the project.

## Classes Overview

- `Vector3D`: Handles mathematical operations in three-dimensional space.
- `Body`: Represents a celestial body with mass, position, velocity, and force.
- `Universe`: Manages the collection of `Body` instances and simulates their interactions.
- `PhysicsEngine`: A static class that provides essential physics calculations.
- `Renderer`: Interfaces with OpenGL to render the simulation.
- `Camera`: Controls the viewport into the simulation, handling user input for navigation.
- `GUI`: Manages the Dear ImGui implementation for user interaction.
- `SimulationController`: Coordinates between the physics, rendering, and GUI elements.
- `FileManager`: Reads and writes simulation data, such as initial state configurations.

## Contributing

Please read [CONTRIBUTING.md](/docs/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Authors

- **Bradley McGlynn** - *Initial work* - [BradMcGlynnUWO](https://github.com/BradMcGlynnUWO)

See also the list of [contributors](https://github.com/yourusername/OrbitalSimulator/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- Hat tip to anyone whose code was used
- Inspiration
- etc.
