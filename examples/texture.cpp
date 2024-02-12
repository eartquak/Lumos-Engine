#include <cmath>
#include <vector>

#include "lumos.h"
#include "shader.h"
#include "textures.h"


void startupFunc(App& app, Texture& tex) {
    sprite2D(app, glm::vec2(-0.5f, -0.5f), glm::vec2(0.1f, 0.1f), 0, glm::vec3(1.0f, 1.0f, 1.0f), tex); 
    sprite2D(app, glm::vec2(0.5f, 0.5f), glm::vec2(0.1f, 0.1f), 0, glm::vec3(1.0f, 1.0f, 1.0f), tex); 
}

void updateFunc(App& app) {
    renderer* rend = app.m_renderer;
    rend->draw();
}


int main() {
    App app = App(1920, 1080, "Testing Window", false, true);
    spdlog::debug("Setting up rects");
    Texture::initShader();
    spdlog::debug("setup textures");
    Texture* tex = new Texture("./assets/ass.png", GL_RGB, GL_UNSIGNED_BYTE, 0);

    app.add_startup_system([tex] (App& app_in) { startupFunc(app_in, *tex); });
    app.add_update_system([](App& app_in){ updateFunc(app_in); });

    app.run();
}
 
