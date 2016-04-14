cmake_minimum_required(VERSION 3.3)
project(SortAndFind)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/main.cpp src/sortAlgorithms/Algorithms.cpp src/sortAlgorithms/Algorithms.h)
add_executable(SortAndFind ${SOURCE_FILES})
set_target_properties(SortAndFind PROPERTIES RUNTIME_OUTPUT_DIRECTORY /home/nikita/Code/ITMO/Course\ 2/System_software/Lab4\(Processes\)/workspace/)
