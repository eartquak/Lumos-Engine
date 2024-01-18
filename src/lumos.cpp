#include "lumos.h"

int WINDOW_HEIGHT;
int WINDOW_WIDTH;
std::vector<std::thread> App::fixed_update_threads;

void App::create_window() {
    if (this->headless) {
        spdlog::debug("Creating headless window");
        this->window = nullptr;
        return;
    }

    spdlog::trace("Creating window");

    // Initialize GLFW
    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW");
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          this->window_title, nullptr, nullptr);
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
        spdlog::error("GLEW error: {}", glewGetErrorString(err));
        glfwTerminate();
        // Handle GLEW initialization failure
    }

    spdlog::info("Using OpenGL version {}, and C++ version {} ",
                 glGetString(GL_VERSION), __cplusplus);
}
App::App(int window_width, int window_height, const char* window_title,
         bool resizable, bool debug) {
    spdlog::info("Starting Lumos Engine 🌕");
    if (debug) {
        spdlog::set_level(spdlog::level::debug);
    }
    WINDOW_WIDTH = window_width;
    WINDOW_HEIGHT = window_height;
    this->window_title = window_title;
    this->resizable = resizable;
}

// Opens app in headless mode
App::App(bool debug) {
    spdlog::info("Starting Lumos Engine 🌕");
    if (debug) {
        spdlog::set_level(spdlog::level::debug);
    }
    this->headless = true;
}

App::~App() { spdlog::info("Closing Lumos Engine 🌑"); }

App& App::add_startup_system(std::function<void()> function) {
    this->startup_functions.push_back(function);
    return *this;
}

App& App::add_update_system(std::function<void()> function) {
    this->update_functions.push_back(function);
    return *this;
}

App& App::add_fixed_update_system(std::function<void()> function,
                                  int milliseconds) {
    this->fixed_update_functions.push_back({function, milliseconds});
    return *this;
}

App& App::add_key_callback_system(
    std::function<void(int, int, int, int)> function) {
    this->key_callback_functions.push_back(function);
    return *this;
}

App& App::add_mouse_callback_system(std::function<void(int, int)> function) {
    this->mouse_callback_functions.push_back(function);
    return *this;
}

App& App::add_scroll_callback_system(std::function<void(int, int, int)> function) {
    this->scroll_callback_functions.push_back(function);
    return *this;
}

void App::close() {
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
    glfwTerminate();
}

void App::run() {
    this->create_window();

    if (!this->headless) {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwSetWindowUserPointer(this->window, this);

    spdlog::info("Registering key callback functions");
    glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key,
                                        int scancode, int action, int mods) {
        spdlog::trace("Key callback function called");
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        for (std::function<void(int, int, int, int)>& function :
             app->key_callback_functions) {
            function(key, scancode, action, mods);
        }
    });

    spdlog::info("Registering mouse callback functions");
    glfwSetMouseButtonCallback(
        this->window, [](GLFWwindow* window, int button, int action, int mods) {
            spdlog::trace("Mouse callback function called");
            App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
            for (std::function<void(int, int)>& function :
                 app->mouse_callback_functions) {
                function(button, action);
            }
        });
    
    spdlog::info("Registering scroll callback functions");
    glfwSetScrollCallback(
        this->window, [](GLFWwindow* window, double xoffset, double yoffset) {
            spdlog::trace("Scroll callback function called");
            App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
            for (std::function<void(int, int, int)>& function :
                 app->scroll_callback_functions) {
                function(xoffset, yoffset, 0);
            }
        });

    spdlog::info("Running the startup functions");
    // Functions run in the beginning
    for (const std::function<void()>& function : startup_functions) {
        function();
    }

    spdlog::info("Running the fixed update functions");
    // Fixed update functions
    for (const std::pair<std::function<void()>, int>& function_pair :
         fixed_update_functions) {
        const std::function<void()>& function = function_pair.first;
        int milliseconds = function_pair.second;

        // Create and start a thread for the fixed update function
        fixed_update_threads.emplace_back([&]() {
            while (!glfwWindowShouldClose(this->window)) {
                function();
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(milliseconds));
            }
        });
    }

    spdlog::info("Running the main loop (contains update function loop)");
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

    spdlog::info("Terminating the fixed update functions");
    // Set the termination flag for fixed update threads
    for (auto& thread : fixed_update_threads) {
        if (thread.joinable()) {
            thread.join();  // Wait for each fixed update thread to finish
        }
    }

    // Clean up GLFW
    this->close();
}