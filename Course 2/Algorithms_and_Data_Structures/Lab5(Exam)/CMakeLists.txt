cmake_minimum_required(VERSION 3.3)
project(Exam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/graph/Graph.cpp src/graph/Graph.h src/graph/GraphBuilder.h src/graph/GraphBuilder.cpp)
add_executable(Exam ${SOURCE_FILES})
set_target_properties(Exam PROPERTIES RUNTIME_OUTPUT_DIRECTORY /home/nikita/Code/ITMO/Course\ 2/Algorithms_and_Data_Structures/Lab5\(Exam\)/workspace/)
