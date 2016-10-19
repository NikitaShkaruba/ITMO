cmake_minimum_required(VERSION 3.6)
project(lab_3_thread_synchronization_)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(lab_3_thread_synchronization_ ${SOURCE_FILES})