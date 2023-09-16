# Lumos-Engine
A 2-D game engine written in C++.

# How to run
1. Run `meson setup build` to create the build directory
2. Go to build directory with `cd build`
3. Run `meson compile && ./debug`
4. To change target file change the same in `meson.build`

# Dependencies
1. For GLFW and GLEW: `sudo apt-get install libglfw3-dev libglew-dev`

# File structure
1. The engine code is present in `Lumos` directory
2. Testing out feature can be done by making another file in `Test` folder (change the target in `meson.build`)
