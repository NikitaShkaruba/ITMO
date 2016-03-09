cmake_minimum_required(VERSION 3.3)
project(sort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/main.cpp src/sortAlgorithms/Algorithms.cpp src/sortAlgorithms/Algorithms.h src/memoryManagers/FileMapper.cpp src/memoryManagers/FileMapper.h src/memoryManagers/BasePointerMapper.cpp src/memoryManagers/BasePointerMapper.h)
add_executable(sort ${SOURCE_FILES})
set_target_properties(sort PROPERTIES RUNTIME_OUTPUT_DIRECTORY /home/nikita/Code/ITMO/Course\ 2/System_software/Lab2\(Memory\ allocation\)/workspace/)

