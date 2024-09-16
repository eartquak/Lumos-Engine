#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
  public:
    GLFWwindow* window;
    int height, width;
    bool resizable;
    Window(int heigth, int width, std::string title, bool resizable);
    void close();
    bool shouldClose();
    void swapBuffers();
};
