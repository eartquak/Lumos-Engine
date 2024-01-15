/**
 * @file lumos.h
 * @brief  Defines the main Lumos application class (App) responsible for window management, system updates, and running the main loop.
 */
#pragma once

#include <spdlog/spdlog.h>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "data.h"
#include "shapes.h"

/**
 * @enum SystemType
 * Enumerates the types of systems that can be added by the application.
 */
enum SystemType {
    Startup,      ///< Startup system executed once at the beginning.
    Update,       ///< Update system executed every frame.
    FixedUpdate   ///< FixedUpdate system executed at fixed intervals.
};

/**
 * @class App
 * @brief Main class representing the Lumos application.
 *
 * The App class manages the main loop, window creation, and system updates in the Lumos application.
 */
class App {
private:
    const char* window_title;                   ///< Title of the application window.
    GLFWwindow* window;                         ///< GLFW window object.
    std::vector<std::function<void()>> startup_functions;                        ///< List of startup functions.
    std::vector<std::function<void()>> update_functions;                         ///< List of update functions.
    std::vector<std::pair<std::function<void()>, int>> fixed_update_functions;   ///< List of fixed update functions with intervals.
    static std::vector<std::thread> fixed_update_threads;                       ///< List of fixed update threads.
    bool resizable;                             ///< Flag indicating if the window is resizable.
    bool headless = false;                      ///< Flag indicating headless mode.
    
    /**
     * @brief Creates the application window using GLFW.
     *
     * If the application is in headless mode, no window is created.
     */
    void create_window();

public:
    /**
     * @brief Constructor for the App class.
     * @param window_width Width of the application window.
     * @param window_height Height of the application window.
     * @param window_title Title of the application window.
     * @param resizable Flag indicating if the window is resizable (default is false).
     * @param debug Flag indicating if the application is in debug mode (default is true).
     */
    App(int window_width, int window_height, const char* window_title, bool resizable = false, bool debug = true);

    /**
     * @brief Constructor for headless mode of the App class.
     * @param debug Flag indicating if the application is in debug mode (default is true).
     */
    App(bool debug = true);

    /**
     * @brief Destructor for the App class.
     */
    ~App();

    /**
     * @brief Adds a system to the Lumos application.
     * @param type Type of the system (Startup, Update, or FixedUpdate).
     * @param function Function representing the system.
     * @return Reference to the current App instance for method chaining.
     */
    App& add_system(SystemType type, std::function<void()> function);

    /**
     * @brief Adds a fixed update system to the Lumos application with a specified interval.
     * @param type Type of the system (FixedUpdate).
     * @param function Function representing the system.
     * @param seconds Interval at which the fixed update system should run.
     * @return Reference to the current App instance for method chaining.
     */
    App& add_system(SystemType type, std::function<void()> function, int milliseconds);

    /**
     * @brief Runs the Lumos application.
     *
     * This method initializes the window, runs startup functions, fixed update functions,
     * and enters the main loop for update functions until the application is closed.
     */
    void run();
};
