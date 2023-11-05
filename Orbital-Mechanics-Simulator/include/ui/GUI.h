#ifndef GUI_H
#define GUI_H

#include <vector>
#include <memory>

// Forward declaration
class Body;

class GUI {
public:
    GUI();
    ~GUI();

    // Initialize the GUI system
    void initialize(GLFWwindow* window);

    // Render the GUI elements
    void render(const std::vector<std::shared_ptr<Body>>& bodies);

    // Shutdown the GUI system
    void shutdown();

private:
    // Any private members for GUI state
};

#endif // GUI_H
