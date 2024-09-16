#include "lumos.h"



entt::entity entt1;

void start(App& app) {
    Position pos = { glm::vec4(0, 0, 0.0f, 1.0f) };
    Canvas canv = { glm::vec2(0.0f, 0.0f), //offset
        glm::vec2(1, 1), //dimesions
        glm::vec2(1.0, 1.0), //scales
        glm::float32(4.71238898038f) //angle
    };
    ColInfo colInfo = { { glm::vec4(1.0f), glm::vec4(1.0f), glm::vec4(1.0f) } };
    app.ECS.createEntity<Canvas, ColInfo>(pos, canv, colInfo);
}

void update(App& app) {
    auto& canv = app.ECS.get<Canvas>(entt1);
    canv.angle = canv.angle + 0.1;
}


int main() {
    App app(300, 300, "New Rect");

    app.add_startup_system(start).add_fixed_update_system(update, 10).run();
}
