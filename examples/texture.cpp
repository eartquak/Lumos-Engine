#include <cmath>
#include <vector>

#include "lumos.h"


void startupFunc(App& app, Texture& tex, renderer& rend) {
    rect rect_in = { {glm::vec2(PIXEL(0, WINDOW_WIDTH), PIXEL(0, WINDOW_HEIGHT))}, {glm::vec2(PIXEL(1920, WINDOW_WIDTH), PIXEL(1080, WINDOW_HEIGHT))}, 0, {glm::vec3(1.0f, 1.0f, 1.0f)} };
    //rect rect_in = { {glm::vec2(0.01f, 0.01f)}, {glm::vec2(0.5f, 0.5f)}, 0, {glm::vec3(1.0f, 1.0f, 1.0f)} };
    sprite2D(app, rend,rect_in, tex, true); 
    //rect rect_in_2 = { {glm::vec2(0.5f, 0.5f)}, {glm::vec2(0.1f, 0.1f)}, 0, {glm::vec3(1.0f, 1.0f, 1.0f)}};
    //sprite2D(app, rend, rect_in_2, true); 
}

/*
void updateFunc(App& app, renderer& rend) {
    rend.draw();
}
*/


int main() {
    App app = App(1920, 1080, "Testing Window", false, true);
    spdlog::debug("Setting up rects");
    spdlog::debug("setup textures");
    renderer rend;
    printf("updated vbo into renderer at %p\n", (void*)&rend);
    Texture tex("./assets/ass.png", GL_RGB, GL_UNSIGNED_BYTE, 0, rend);
    app.add_startup_system([&tex, &rend] (App& app_in) { startupFunc(app_in, tex, rend); });
    //app.add_update_system([&rend](App& app_in){ updateFunc(app_in, rend); });

    app.run();
}
 
