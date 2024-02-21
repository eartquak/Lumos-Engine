#include "input.h"

inputPos input::mousePos = {0, 0};
inputPos input::scrollPos = {0, 0};

input::input(GLFWwindow* window) {
    //initialize window pointer;
    this->window = window;
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetCursorPosCallback(window, cursorCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

bool input::isKeyPressed(int key) {
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void input::cursorCallback(GLFWwindow*, double xpos, double ypos) {
    mousePos.x = xpos;
    mousePos.y = ypos;
}

bool input::isMousePressed(int button) {
    return (glfwGetMouseButton(window, button) == GLFW_PRESS);
}

void input::scrollCallback(GLFWwindow*, double xoffset, double yoffset) {
    scrollPos.x = xoffset;
    scrollPos.y = yoffset;
}
