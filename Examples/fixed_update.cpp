#include <iostream>

#include "../Lumos/lumos.cpp"

void hello_world() {
    spdlog::debug("Hello World");
}

void bye_world() {
    spdlog::debug("Bye World");
}

int main() {
    App app = App();
    app.add_fixed_update(hello_world, 1)
        .add_fixed_update(bye_world, 2)
        .run();
}