#include "lumos.h"

int main() {
    App app = App(800, 600, "Testing Window");
    app.add_key_callback_system([&](int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            spdlog::info("Escape key pressed");
            app.close();
        }
    });
    app.run();
}