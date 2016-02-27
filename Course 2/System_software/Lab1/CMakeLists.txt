cmake_minimum_required(VERSION 3.3)
project(Lab1_cp_)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/copyFunctions.h src/copyFunctions.cpp)
add_executable(Lab1_cp_ ${SOURCE_FILES})