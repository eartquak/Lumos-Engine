#include "input.h"

inputPos Input::mousePos = {0, 0};
inputPos Input::scrollPos = {0, 0};

Input::Input(Window& window) : window(window) {
    glfwGetWindowSize(window.window, &width, &height);
    glfwSetInputMode(window.window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window.window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetCursorPosCallback(window.window, cursorCallback);
    glfwSetScrollCallback(window.window, scrollCallback);
    spdlog::info("Input Initialized");
}

bool Input::isKeyPressed(int key) {
    return (glfwGetKey(window.window, key) == GLFW_PRESS);
}

void Input::cursorCallback(GLFWwindow*, double xpos, double ypos) {
    mousePos.x = xpos;
    mousePos.y = ypos;
}

bool Input::isMousePressed(int button) {
    return (glfwGetMouseButton(window.window, button) == GLFW_PRESS);
}

inputPos Input::getMousePosition() {
    return {mousePos.x, height - mousePos.y};
}

void Input::scrollCallback(GLFWwindow*, double xoffset, double yoffset) {
    scrollPos.x += xoffset;
    scrollPos.y += yoffset;
}

void Input::pollEvents() {
    glfwPollEvents();
}
