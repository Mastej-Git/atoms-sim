cmake_minimum_required(VERSION 3.10)
project(atoms-sim)

cmake_policy(SET CMP0072 NEW)
set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(atoms-sim main.cpp glad.c)

target_include_directories(atoms-sim PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(atoms-sim glfw OpenGL::GL ${CMAKE_DL_LIBS})