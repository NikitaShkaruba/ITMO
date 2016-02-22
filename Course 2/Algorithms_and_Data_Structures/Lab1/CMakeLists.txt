cmake_minimum_required(VERSION 3.3)
project(Lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/OrderedList/CodeParser.cpp src/OrderedList/headers/CodeParser.h src/OrderedList/OrderedList.cpp src/OrderedList/headers/OrderedList.h src/OrderedList/HashTable.cpp src/OrderedList/headers/HashTable.h)
add_executable(Lab1 ${SOURCE_FILES})

