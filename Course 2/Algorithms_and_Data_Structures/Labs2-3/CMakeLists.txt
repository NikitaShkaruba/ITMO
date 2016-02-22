cmake_minimum_required(VERSION 3.3)
project(Labs2-3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/algorithms/algorithms.cpp src/algorithms/algorithms.h src/graph/Graph.cpp src/graph/Graph.h)
add_executable(Labs2-3 ${SOURCE_FILES})