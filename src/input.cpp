#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_PRESS)
        if (key == GLFW_KEY_ESCAPE)
            quit(window);
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key)
{
    if (key == 'q')
        quit(window);
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
        if (action == GLFW_PRESS)
            return;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    float d = 0.05;
    screen_zoom += d * yoffset;
    screen_zoom = max(screen_zoom, d * 2);
    screen_zoom = min(screen_zoom, d * 3);
    reset_screen();
}
