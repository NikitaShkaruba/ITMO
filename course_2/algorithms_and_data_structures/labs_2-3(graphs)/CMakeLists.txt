cmake_minimum_required(VERSION 3.3)
project(GraphAlgorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/main.cpp src/algorithms/algorithms.cpp src/algorithms/algorithms.h src/graph/Graph.cpp src/graph/Graph.h src/graph/GraphBuilder.cpp src/graph/GraphBuilder.h)
add_executable(GraphAlgorithms ${SOURCE_FILES})
set_target_properties(GraphAlgorithms PROPERTIES RUNTIME_OUTPUT_DIRECTORY /home/nikita/Code/ITMO/Course\ 2/Algorithms_and_Data_Structures/Labs2-3/workspace/)
