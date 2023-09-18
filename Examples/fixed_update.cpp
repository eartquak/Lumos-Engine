#include <iostream>

#include "../Lumos/lumos.cpp"

void hello_world() {
    std::cout << "Hello World" << std::endl;
}

void bye_world() {
    std::cout << "Bye World" << std::endl;
}

int main() {
    App app = App(500, 500, "Testing Window");
    app.add_system(SystemType::FixedUpdate, hello_world, 1)
        .add_system(SystemType::FixedUpdate, bye_world, 2)
        .run();
}