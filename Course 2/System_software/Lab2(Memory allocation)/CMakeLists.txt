cmake_minimum_required(VERSION 3.3)
project(Lab2_Memory_allocation_)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Algorithms.cpp src/Algorithms.h src/MemoryMapper.cpp src/MemoryMapper.h)
add_executable(Lab2_Memory_allocation_ ${SOURCE_FILES})