project('Lumos', ['cpp', 'c'],
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++20','debug_flags=-g']
)

compiler = meson.get_compiler('cpp')
openGLDep = dependency('gl')
glewDep = dependency('glew')
glfwDep = dependency('glfw3')
spdlogDep = dependency('spdlog')
incdir = include_directories('include')
extdir = include_directories('external')

executable('debug', ['examples/sand_sim.cpp', 'src/lumos.cpp', 'src/shapes.cpp'], dependencies: [glfwDep, glewDep, openGLDep, spdlogDep], include_directories : [incdir, extdir])
