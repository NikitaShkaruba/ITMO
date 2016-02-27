cmake_minimum_required(VERSION 3.3)
project(cp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/copyFunctions.h src/copyFunctions.cpp)
add_executable(cp ${SOURCE_FILES})