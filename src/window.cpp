#include "window.h"
#include "spdlog/spdlog.h"

Window::Window(int width, int height, std::string title, bool resizable) { 
    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW");
        return;
    }

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    #ifdef DEBUG

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    #endif

    

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    this->window = window;


    glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable);

    if (!window) {
        spdlog::error("Failed to create GLFW window");
        return;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);
    this->height = height;
    this->width = width;
    this->resizable = resizable;
    spdlog::info("Created Window");
}

void Window::close() {
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(this->window);
}
