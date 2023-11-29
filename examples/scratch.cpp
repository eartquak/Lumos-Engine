// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
// #include <iostream>

// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

// int main() {
//     // Initialize GLFW
//     if (!glfwInit()) {
//         std::cerr << "Failed to initialize GLFW" << std::endl;
//         return -1;
//     }

//     // Create a GLFW window
//     GLFWwindow* window = glfwCreateWindow(800, 600, "Rectangle Example", nullptr, nullptr);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     // Make the OpenGL context current
//     glfwMakeContextCurrent(window);

//     // Initialize GLEW (or other OpenGL loader)
//     if (glewInit() != GLEW_OK) {
//         std::cerr << "Failed to initialize GLEW" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     // Set up the viewport and callback for window resizing
//     int width, height;
//     glfwGetFramebufferSize(window, &width, &height);
//     glViewport(0, 0, width, height);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // Define vertices for the rectangle
//     float vertices[] = {
//         // Positions         // Colors
//          0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top Right
//          0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom Right
//         -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // Bottom Left
//         -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f  // Top Left
//     };

//     // Define indices to draw the rectangle
//     unsigned int indices[] = {
//         0, 1, 3, // First Triangle
//         1, 2, 3  // Second Triangle
//     };

//     // Create Vertex Array Object (VAO), Vertex Buffer Object (VBO), and Element Buffer Object (EBO)
//     unsigned int VAO, VBO, EBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     // Bind the VAO
//     glBindVertexArray(VAO);

//     // Bind and set up the VBO
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // Bind and set up the EBO
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     // Set vertex attribute pointers
//     // Position attribute
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     // Color attribute
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     // Unbind VBO and VAO
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

//     // Shader program (you need to create vertex and fragment shader programs)

//     const char* vertexShaderSource = R"(
//         #version 330 core
//         layout(location = 0) in vec3 aPos;
//         layout(location = 1) in vec3 aColor;
//         out vec3 color;
//         void main() {
//             gl_Position = vec4(aPos, 1.0);
//             color = aColor;
//         }
//     )";

//     const char* fragmentShaderSource = R"(
//         #version 330 core
//         in vec3 color;
//         out vec4 FragColor;
//         void main() {
//             FragColor = vec4(color, 1.0);
//         }
//     )";

//     // Compile and link shaders, create shader program

//     // Create the shader program, attach shaders, and link
//     unsigned int shaderProgram;
//     int success;
//     char infoLog[512];

//     // Vertex shader
//     unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertexShader);
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
//     }

//     // Fragment shader
//     unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragmentShader);
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
//     }

//     // Shader program
//     shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
//     }
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     // Rendering loop
//     while (!glfwWindowShouldClose(window)) {
//         // Process input
//         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//             glfwSetWindowShouldClose(window, true);

//         // Rendering commands
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Use the shader program
//         glUseProgram(shaderProgram);

//         // Bind the VAO
//         glBindVertexArray(VAO);

//         // Draw the rectangle
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//         // Unbind the VAO
//         glBindVertexArray(0);

//         // Swap the front and back buffers
//         glfwSwapBuffers(window);

//         // Poll for and process events
//         glfwPollEvents();
//     }

//     // Clean up
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);
//     glDeleteProgram(shaderProgram);

//     // Terminate GLFW
//     glfwTerminate();
//     return 0;
// }

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum PrimitiveType {
    POINT,
    RECTANGLE,
    // Add more primitive types as needed
};


void drawPrimitive(PrimitiveType type) {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (type) {
        case POINT:
            glBegin(GL_POINTS);
            glVertex2f(0.0f, 0.0f); // Replace with the coordinates of your point
            glEnd();
            break;

        case RECTANGLE:
            glBegin(GL_QUADS);
            glVertex2f(-0.5f, -0.5f); // Replace with the coordinates of your rectangle
            glVertex2f(0.5f, -0.5f);
            glVertex2f(0.5f, 0.5f);
            glVertex2f(-0.5f, 0.5f);
            glEnd();
            break;

        // Add cases for other primitive types

        default:
            break;
    }

    glFlush();
}

int main() {
    if (!glfwInit()) {
        // Handle GLFW initialization error
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Primitives", nullptr, nullptr);
    if (!window) {
        // Handle window creation error
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        // Handle GLEW initialization error
        return -1;
    }    

    while (!glfwWindowShouldClose(window)) {
        drawPrimitive(RECTANGLE);
        // drawPrimitive(POINT); // Change to the desired primitive type
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
