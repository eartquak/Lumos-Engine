/**
 * @file lumos.h
 * @brief  Defines the main Lumos application class (App) responsible for window
 * management, system updates, and running the main loop.
 */
#pragma once

#include <spdlog/spdlog.h>
#include "gl_stuff.h"
#include "window.h"
#include <functional>
#include <thread>
#include <vector>
#include "ecs.h"
#include "input.h"
#include <ctime>


/**
 * @class App
 * @brief Main class representing the Lumos application.
 *
 * The App class manages the main loop, window creation, and system updates in
 * the Lumos application.
 */


class App {
    private:
        std::vector<std::function<void(App&)>>
            startup_functions;  ///< List of startup functions.
        std::vector<std::function<void(App&)>>
            update_functions;  ///< List of update functions.
        std::vector<std::pair<std::function<void(App&)>, int>>
            fixed_update_functions;  ///< List of fixed update functions with
                                     ///< intervals.
        static std::vector<std::thread>
            fixed_update_threads;  ///< List of fixed update threads.


        bool running = false;

    public:

        /**
         * @brief Constructor for the App class.
         * @param window_width Width of the application window.
         * @param window_height Height of the application window.
         * @param window_title Title of the application window.
         * @param resizable Flag indicating if the window is resizable (default is
         * false).
         * @param debug Flag indicating if the application is in debug mode (default
         * is true).
         */
        App(int window_width, int window_height, std::string window_title, bool resizable = false);

        /**
         * @brief Constructor for headless mode of the App class.
         * @param debug Flag indicating if the application is in debug mode (default
         * is true).
         */
        App();

        /**
         * @brief Destructor for the App class.
         */
        ~App();

        App& add_startup_system(std::function<void(App&)> function);
        App& add_update_system(std::function<void(App&)> function);
        App& add_fixed_update_system(std::function<void(App&)> function,
                int milliseconds = 1000 / 60);
        //App& add_key_callback_system(std::function<void(int, int, int, int)> function);
        //App& add_mouse_callback_system(std::function<void(int, int)> function);
        //App& add_scroll_callback_system(std::function<void(int, int, int)> function);
        App& draw();

        //std::pair<double, double> get_mouse_position();
        //bool is_mouse_pressed();
        Window window;
        Renderer renderer;
        Input input;
        ecs ECS;
        /**
         * @brief Runs the Lumos application.
         *
         * This method initializes the window, runs startup functions, fixed update
         * functions, and enters the main loop for update functions until the
         * application is closed.
         */
        void run();

        void close();
};
