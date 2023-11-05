#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Body.h"
#include <memory>
#include <vector>
#include <string>
#include "Shader.h"  // A class that wraps OpenGL shader operations
#include "Camera.h"  // A class that handles the viewpoint and projection

class Renderer {
private:
    GLFWwindow* window;
    Shader shader; // Shader program for rendering bodies
    Camera camera; // Camera to control the view
    GLuint VAO, VBO; // Vertex Array Object and Vertex Buffer Object

    // Internal method to setup models, textures, etc.
    void setupRenderingData();

public:
    Renderer(int windowWidth, int windowHeight, const std::string& windowTitle);
    ~Renderer();

    // Initialize OpenGL context, setup shaders, etc.
    void initialize();

    // Method to draw all celestial bodies
    void renderBodies(const std::vector<std::shared_ptr<Body>>& bodies);

    // Method to handle UI rendering and interactions
    void renderUI();

    // Main loop of the graphics application
    void runMainLoop(std::vector<std::shared_ptr<Body>>& bodies);

    // Method to add a new body via UI
    void addBodyUI(const std::vector<std::shared_ptr<Body>>& bodies);

    // Method to remove a body via UI
    void removeBodyUI(std::vector<std::shared_ptr<Body>>& bodies);
};

#endif // RENDERER_H
