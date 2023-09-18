#include <iostream>

#include "../Lumos/lumos.cpp"

void hello_world() {
    spdlog::info("Hello World");
}

void bye_world() {
    spdlog::info("Bye World");
}

int main() {
    App app = App();
    app.add_fixed_update(hello_world, 1)
        .add_fixed_update(bye_world, 2)
        .run();
}