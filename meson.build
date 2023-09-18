project('opengltest', ['cpp','c'],
  version : '0.1',
  default_options : ['warning_level=1', 'cpp_std=c++20'])
# Enable -Werror
add_project_arguments('-Wall', language: 'cpp')
add_project_arguments('-Werror', language: 'cpp')

compiler = meson.get_compiler('cpp')
openGLDep = dependency('gl')
glewDep = dependency('glew')
glfwDep = dependency('glfw3')

# Define your executable and sources
executable('debug', 'Examples/checkerboard.cpp', dependencies : [glfwDep, glewDep, openGLDep])

