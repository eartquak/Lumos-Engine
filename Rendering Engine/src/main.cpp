#include "engine.hh"

int main() {
    Window* window = new Window();
    window->create_window();
    // window->register_events(keyboard_event);

    // Shader* shader = new Shader("../src/shaders/vertex.glsl",
    //                             "../src/shaders/fragment.glsl");
    // shader->make_current();

    // std::vector<float> vertices = {{
    //     -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  // Top-left
    //     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // Top-right
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right
    //     -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f  // Bottom-left
    // }};
    // std::vector<int> elements = {{
    //     0, 1, 2,  // first
    //     2, 3, 0,  // second
    // }};

    // // std::vector<float> vertices = {
    // //     // Position           // Color
    // //     -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // Front-bottom-left
    // //     0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,   // Front-bottom-right
    // //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,    // Front-top-right
    // //     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,   // Front-top-left

    // //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Back-bottom-left
    // //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // Back-bottom-right
    // //     0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,    // Back-top-right
    // //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // Back-top-left

    // //     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // Top-front-left
    // //     0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,    // Top-front-right
    // //     0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,   // Top-back-right
    // //     -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // Top-back-left

    // //     -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,   // Bottom-front-left
    // //     0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,    // Bottom-front-right
    // //     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,   // Bottom-back-right
    // //     -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  // Bottom-back-left

    // //     0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // Right-front-bottom
    // //     0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,    // Right-front-top
    // //     0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,   // Right-back-top
    // //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  // Right-back-bottom

    // //     -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,  // Left-front-bottom
    // //     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,   // Left-front-top
    // //     -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  // Left-back-top
    // //     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f  // Left-back-bottom
    // // };

    // // std::vector<int> elements = {
    // //     0, 1, 2, 2, 3, 0,        // Front face
    // //     4, 5, 6, 6, 7, 4,        // Back face
    // //     8, 9, 10, 10, 11, 8,     // Top face
    // //     12, 13, 14, 14, 15, 12,  // Bottom face
    // //     16, 17, 18, 18, 19, 16,  // Right face
    // //     20, 21, 22, 22, 23, 20   // Left face
    // // };

    // Mesh* mesh = new Mesh(vertices, elements, COLOR_MODE);
    // mesh->make_current();

    while (!window->should_close()) {
        window->listen();
        window->clear();
        // shader->update();

        // if (glfwGetKey(window->get_window(), GLFW_KEY_D) == GLFW_PRESS) {
        //     for (int i = 0; i < 4; i++)
        //         mesh->get_vertices()[i * 6] += 0.01f;
        // } else if (glfwGetKey(window->get_window(), GLFW_KEY_A) == GLFW_PRESS) {
        //     for (int i = 0; i < 4; i++)
        //         mesh->get_vertices()[i * 6] -= 0.01f;
        // }
        // mesh->update_buffers();
        // mesh->draw();
        window->update();
    }

    window->wrap_up();
    return 0;
}