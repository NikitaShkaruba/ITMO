cmake_minimum_required(VERSION 3.8)
project(lab_2_opengl_)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.

set(SOURCE_FILES src/main.cpp src/lib/Painter.cpp src/lib/include/Painter.h src/lib/Game.cpp src/lib/include/Game.h src/lib/include/include.h)
add_executable(lab_2_opengl_ ${SOURCE_FILES})