#include "engine.hh"

Window::Window() {
    if (!glfwInit()) {
        std::cout << "GLFW couldn't start" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // todo these two are supposed to help in transparency but are giving seg faults
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::wrap_up() {
    glfwTerminate();
}

void Window::create_window() {
    this->window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);
    if (this->window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(this->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glClearColor(0.44f, 0.44f, 0.44f, 1.0f);
}

GLFWwindow* Window::get_window() {
    return this->window;
}

bool Window::should_close() {
    return glfwWindowShouldClose(this->window);
}

void Window::listen() {
    glfwPollEvents();
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update() {
    glfwSwapBuffers(this->window);
}