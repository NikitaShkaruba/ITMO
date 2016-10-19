cmake_minimum_required(VERSION 3.3)
project(Lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/main.cpp src/CodeParser.cpp src/headers/CodeParser.h src/OrderedList.cpp src/headers/OrderedList.h src/HashTable.cpp src/headers/HashTable.h)

install(DIRECTORY share/ DESTINATION share)
add_executable(Lab1 ${SOURCE_FILES})

