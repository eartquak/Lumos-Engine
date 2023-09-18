#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "data.cpp"
#include "shapes.cpp"

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
    std::vector<std::pair<std::function<void()>, int>> fixed_update_functions;
    std::vector<std::thread> fixed_update_threads;
    bool resizable;
    bool headless = false;

    void create_window() {
        if (this->headless) {
            spdlog::info("Creating headless window");
            this->window = nullptr;
            return;
        }

        spdlog::info("Creating window");

        // Initialize GLFW
        if (!glfwInit()) {
            spdlog::error("Failed to initialize GLFW");
        }

        GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, this->window_title, nullptr, nullptr);
        this->window = window;
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, this->resizable);

        if (!window) {
            spdlog::error("Failed to create GLFW window");
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
    App(int window_width, int window_height, const char* window_title, bool resizable = false, bool debug = true) {
        if (debug) {
            spdlog::set_level(spdlog::level::debug);
        }
        WINDOW_WIDTH = window_width;
        WINDOW_HEIGHT = window_height;
        this->window_title = window_title;
        this->resizable = resizable;
    }

    // Opens app in headless mode
    App(bool debug = true) {
        if (debug) {
            spdlog::set_level(spdlog::level::debug);
        }
        this->headless = true;
    }

    ~App() {
        spdlog::info("Exiting the application...");
    }

    App& add_system(SystemType type, std::function<void()> function) {
        std::string system_type;
        switch (type) {
            case SystemType::Startup:
                this->startup_functions.push_back(function);
                system_type = "Startup";
                break;
            case SystemType::Update:
                this->update_functions.push_back(function);
                system_type = "Update";
                break;
            default:
                break;
        }
        spdlog::debug("Adding system of type {}", system_type);
        return *this;
    }

    App& add_fixed_update(std::function<void()> function, int seconds = 0) {
        spdlog::debug("Adding system of type FixedUpdate");
        this->fixed_update_functions.push_back({function, seconds});
        return *this;
    }

    void run() {
        spdlog::debug("Running the application...");

        this->create_window();

        if (!this->headless) {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        // Functions run in the beginning
        for (const std::function<void()>& function : startup_functions) {
            function();
        }

        // Fixed update functions
        for (const std::pair<std::function<void()>, int>& function_pair : fixed_update_functions) {
            const std::function<void()>& function = function_pair.first;
            int seconds = function_pair.second;

            // Create and start a thread for the fixed update function
            fixed_update_threads.emplace_back([function, seconds]() {
                while (true) {
                    function();
                    std::this_thread::sleep_for(std::chrono::seconds(seconds));
                }
            });
        }

        if (!this->headless) {
            // Main loop
            while (!glfwWindowShouldClose(this->window)) {
                glClear(GL_COLOR_BUFFER_BIT);
                // Update Functions (update every frame i.e every loop)
                for (std::function<void()>& function : update_functions) {
                    function();
                }

                // Swap front and back buffers
                glfwSwapBuffers(this->window);

                // Poll for and process events
                glfwPollEvents();
            }
        }

        // Set the termination flag for fixed update threads
        for (auto& thread : fixed_update_threads) {
            if (thread.joinable()) {
                thread.join();  // Wait for each fixed update thread to finish
            }
        }

        // Clean up GLFW
        glfwTerminate();
    }
};