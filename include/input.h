#pragma once

#include "window.h"
#include <spdlog/spdlog.h>

struct inputPos {
    double x = 0;
    double y = 0;
};

class Input {
  public:
    Window& window;
    static inputPos mousePos;
    static inputPos scrollPos;
    int width;
    int height;
    Input(Window& window);
    void pollEvents();

    //Keyboard Handling
    bool isKeyPressed(int key);

    //Mouse Handling
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
    bool isMousePressed(int button);
    inputPos getMousePosition();

    //Scroll Callback
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
   


};
