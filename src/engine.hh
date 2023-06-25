#pragma once
#include <iostream>

#include "../dependencies/glad/glad/glad.h"
// #include <GLFW/glfw3.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <glm/glm.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../dependencies/glfw-3.3.8/include/GLFW/glfw3.h"

class Window {
   private:
    GLFWwindow* window;

   public:
    Window();
    void wrap_up();
    void create_window();
    GLFWwindow* get_window();
    bool should_close();
    void listen();
    void clear();
    void update();
};

class Shader {
   private:
    uint shader;
    int time_location;

   public:
    Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
    ~Shader();
    void make_current();
    uint make_shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
    uint make_module(const std::string& filepath, uint module_type);
    void update();
};

class Mesh {
   private:
    std::vector<float> vertices;
    std::vector<int> elements;
    uint vertex_count;
    uint vertex_array_object;
    uint vertex_buffer_object;
    uint element_array_buffer;

   public:
    Mesh(std::vector<float> vertex_vector, std::vector<int> elements_vector, uint mode);
    void update_buffers();
    void draw();
    void make_current();
    std::vector<float>& get_vertices();
};

class Camera {
   private:
    glm::vec3 position;
    float yaw;
    float pitch;
    float movement_speed;
    float mouse_sensitivity;

   public:
    Camera();
};

// class Window {
//    private:
//     GLFWwindow* window;

//    public:
//     Window() {
//         if (!glfwInit()) {
//             std::cout << "GLFW couldn't start" << std::endl;
//             exit(EXIT_FAILURE);
//         }
//         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//         glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//         // todo these two are supposed to help in transparency but are giving seg faults
//         // glEnable(GL_BLEND);
//         // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     }

//     void wrap_up() {
//         glfwTerminate();
//     }

//     void create_window() {
//         this->window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);
//         if (this->window == NULL) {
//             std::cout << "Failed to create GLFW window" << std::endl;
//             glfwTerminate();
//             exit(EXIT_FAILURE);
//         }

//         glfwMakeContextCurrent(this->window);
//         if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//             std::cout << "Failed to initialize GLAD" << std::endl;
//             glfwTerminate();
//             exit(EXIT_FAILURE);
//         }

//         glClearColor(0.44f, 0.44f, 0.44f, 1.0f);
//     }

//     GLFWwindow* get_window() {
//         return this->window;
//     }

//     bool should_close() {
//         return glfwWindowShouldClose(this->window);
//     }

//     void listen() {
//         glfwPollEvents();
//     }

//     void clear() {
//         glClear(GL_COLOR_BUFFER_BIT);
//     }

//     void update() {
//         glfwSwapBuffers(this->window);
//     }
// };

// class Shader {
//    private:
//     uint shader;
//     int time_location;

//    public:
//     Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath) {
//         this->shader = make_shader(
//             vertex_shader_filepath,
//             fragment_shader_filepath);
//     }

//     ~Shader() {
//         glDeleteProgram(this->shader);
//     }

//     void make_current() {
//         // forces opengl to use this shader as the current shader
//         glUseProgram(this->shader);
//     }

//     uint make_shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath) {
//         std::vector<uint> modules;
//         modules.push_back(make_module(vertex_shader_filepath, GL_VERTEX_SHADER));
//         modules.push_back(make_module(fragment_shader_filepath, GL_FRAGMENT_SHADER));

//         uint shader = glCreateProgram();
//         for (uint shaderModule : modules) {
//             glAttachShader(shader, shaderModule);
//         }
//         glLinkProgram(shader);

//         int success;
//         glGetProgramiv(shader, GL_LINK_STATUS, &success);
//         if (!success) {
//             char errorLog[1024];
//             glGetShaderInfoLog(shader, 1024, NULL, errorLog);
//             std::cout << "Shader module linking error:\n"
//                       << errorLog << std::endl;
//         }

//         for (uint shaderModule : modules) {
//             glDeleteShader(shaderModule);
//         }

//         return shader;
//     }

//     uint make_module(const std::string& filepath, uint module_type) {
//         std::ifstream file;
//         std::stringstream bufferedLines;
//         std::string line;

//         file.open(filepath);
//         while (std::getline(file, line)) {
//             bufferedLines << line << "\n";
//         }

//         std::string shaderSource = bufferedLines.str();
//         const char* shaderSrc = shaderSource.c_str();
//         bufferedLines.str("");

//         // RAII will close it anyways
//         file.close();

//         uint shaderModule = glCreateShader(module_type);
//         glShaderSource(shaderModule, 1, &shaderSrc, NULL);
//         glCompileShader(shaderModule);

//         int success;
//         glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
//         if (!success) {
//             char errorLog[1024];
//             glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
//             std::cout << "Shader module compilation error:\n"
//                       << errorLog << std::endl;
//         }

//         return shaderModule;
//     }

//     // Updates every frame to update the time variable
//     void update() {
//         this->time_location = glGetUniformLocation(this->shader, "time");

//         // Set the value of the uniform variable to the current time
//         float currentTime = glfwGetTime();
//         glUniform1f(this->time_location, currentTime);
//     }
// };

// // color mode means the mesh will take in rgb data
// // texture mode mean the mesh will draw from a texture
// // todo all this btw
// #define COLOR_MODE 0
// #define TEXTURE_MODE 1
// class Mesh {
//    private:
//     std::vector<float> vertices;
//     std::vector<int> elements;
//     uint vertex_count;
//     uint vertex_array_object;
//     uint vertex_buffer_object;
//     uint element_array_buffer;

//    public:
//     Mesh(std::vector<float> vertex_vector, std::vector<int> elements_vector, uint mode) {
//         this->vertices = vertex_vector;
//         this->elements = elements_vector;
//         this->vertex_count = this->elements.size();
//         this->update_buffers();
//     }

//     void update_buffers() {
//         // Create and bind the vertex array object (VAO)
//         glGenVertexArrays(1, &this->vertex_array_object);
//         glBindVertexArray(this->vertex_array_object);

//         // Create and bind the vertex buffer object (VBO)
//         glGenBuffers(1, &this->vertex_buffer_object);
//         glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object);

//         // Create and bind the vertex buffer object (EAB)
//         glGenBuffers(1, &this->element_array_buffer);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->element_array_buffer);

//         // Set the vertex data into the buffer
//         glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof(int), this->elements.data(), GL_STATIC_DRAW);

//         // Specify the vertex attribute pointers
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//         glEnableVertexAttribArray(1);
//     }

//     void draw() {
//         // glDrawArrays(GL_TRIANGLES, 0, vertexCount);
//         glDrawElements(GL_TRIANGLES, this->vertex_count, GL_UNSIGNED_INT, 0);
//     }

//     void make_current() {
//         glBindVertexArray(this->vertex_array_object);
//     }

//     std::vector<float>& get_vertices() {
//         return this->vertices;
//     }
// };

// class Camera {
//    private:
//     glm::vec3 position;

//     float yaw;
//     float pitch;

//     float movement_speed;
//     float mouse_sensitivity;

//    public:
//     Camera() {
//     }
// };