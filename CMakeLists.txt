cmake_minimum_required(VERSION 3.0.0)
project(Lumos-Engine VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(Lumos-Engine 
    src/main.cpp 
    src/glad.c
)

target_include_directories(Lumos-Engine PRIVATE dependencies)
target_link_libraries(Lumos-Engine glfw OpenGL::GL)
