cmake_minimum_required(VERSION 3.0)

project(opengl_experiment)

# System dependencies
find_package(OpenGL REQUIRED)

# Local dependencies
include("dependencies/glfw.cmake")
include("dependencies/glbinding.cmake")

# index executable
add_executable(index source/index.cpp)
target_include_directories(index
  PUBLIC source
)
target_link_libraries(index
  ${OPENGL_gl_LIBRARY}
  glfw
  glbinding
)
