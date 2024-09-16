#include "lumos.h"


std::vector<std::thread> App::fixed_update_threads;

App::App(int height, int width, std::string title, bool resizable) :
    window(height, width, title, resizable),
    renderer(window),
    input(window),
    ECS() {
        
    spdlog::info("Starting Lumos Engine 🌕");

#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif
}

// Opens app in headless mode
/*
App::App() {
    spdlog::info("Starting Lumos Engine 🌕");
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif
}
*/

App::~App() { spdlog::info("Closing Lumos Engine 🌑"); }

App& App::add_startup_system(std::function<void(App&)> function) {
    this->startup_functions.push_back(function);
    return *this;
}

App& App::add_update_system(std::function<void(App&)> function) {
    this->update_functions.push_back(function);
    return *this;
}

App& App::add_fixed_update_system(std::function<void(App&)> function,
                                  int milliseconds) {
    this->fixed_update_functions.push_back({function, milliseconds});
    return *this;
}

void App::close() {
    window.close();
    running = false;
}

void App::run() {
    //this->create_window();

    this->renderer.clear();
    

    spdlog::info("Running the startup functions");
    for (const std::function<void(App&)>& function : startup_functions) {
        function(*this);
    }

    spdlog::info("Running the fixed update functions");
    for (const std::pair<std::function<void(App&)>, int>& function_pair :
         fixed_update_functions) {
        const std::function<void(App&)>& function = function_pair.first;
        int milliseconds = function_pair.second;

        // Create and start a thread for the fixed update function
        fixed_update_threads.emplace_back([&]() {
            while (!this->window.shouldClose()) {
                function(*this);
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(milliseconds));
            }
        });
    }

    spdlog::info("Running the main loop");
    // Main loop
    running = true;

    while (!this->window.shouldClose() && running) {

        // Poll for and process events
        this->input.pollEvents();

        this->renderer.clear();
        // Update Functions (update every frame i.e every loop)
        for (std::function<void(App&)>& function : update_functions) {
            function(*this);
        }
        #ifndef LEGACY
        draw();
        #endif
        // Swap front and back buffers
        this->window.swapBuffers();
        this->renderer.markFrameTermination();
    }

    spdlog::info("Terminating the fixed update functions");
    // Set the termination flag for fixed update threads
    for (auto& thread : fixed_update_threads) {
        if (thread.joinable()) {
            thread.join();  // Wait for each fixed update thread to finish
        }
    }

    spdlog::info("Cleaning up opengl");
    // Clean up GLFW
    this->close();
}

App& App::draw() {
    auto view = ECS.reg.view<Position, Canvas, ColInfo>(); 
    for(auto entity: view) {
        auto [position, canv, colInfo] = view.get<Position, Canvas, ColInfo>(entity);
        renderer.drawCanvasCol(position, canv, colInfo);
    }
    renderer.draw();
    return *this;

}

