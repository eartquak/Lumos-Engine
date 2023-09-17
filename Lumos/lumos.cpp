#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <vector>

#include "shapes.cpp"
#include "data.cpp"
int WINDOW_HEIGHT;
int WINDOW_WIDTH;

enum SystemType {
    Startup,
    Update,
    FixedUpdate
};

class App {
   private:
    const char* window_title;
    GLFWwindow* window;
    std::vector<std::function<void()>> startup_functions;
    std::vector<std::function<void()>> update_functions;

    void create_window() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            // Handle initialization failure
            // return -1;
        }

        // Create a GLFW window
        GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, this->window_title, nullptr, nullptr);
        this->window = window;

        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            // Handle window creation failure
            // return -1;
        }

        // Make the OpenGL context current
        glfwMakeContextCurrent(window);

        // Initialize GLEW (or other OpenGL loader) after creating the context
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            fprintf(stderr, "GLEW error: %s\n", glewGetErrorString(err));
            glfwTerminate();
            // Handle GLEW initialization failure
        }
    }

   public:
    App(int window_width, int window_height, const char* window_title) {
        WINDOW_WIDTH = window_width;
        WINDOW_HEIGHT = window_height;
        this->window_title = window_title;
    }

    ~App() {
        std::cout << "Exiting the application..." << std::endl;
    }

    App& add_system(SystemType type, std::function<void()> function) {
        switch (type) {
            case SystemType::Startup:
                this->startup_functions.push_back(function);
                break;
            case SystemType::Update:
                this->update_functions.push_back(function);
                break;
            default:
                break;
        }
        return *this;
    }

    void run() {
        std::cout << "Running the application..." << std::endl;
        this->create_window();
        glClear(GL_COLOR_BUFFER_BIT);

        // Physics, Rendering, etc. here
        for (std::function<void()>& function : startup_functions) {
            function();
        }

        // Main loop
        while (!glfwWindowShouldClose(this->window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            // Render here
            for (std::function<void()>& function : update_functions) {
                function();
            }

            // Swap front and back buffers
            glfwSwapBuffers(this->window);

            // Poll for and process events
            glfwPollEvents();
        }

        // Clean up GLFW
        glfwTerminate();
    }
};