cmake_minimum_required(VERSION 3.3)
project(keylogger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/keytables.h src/keytables.cpp)
add_executable(keylogger ${SOURCE_FILES})
set_target_properties(keylogger PROPERTIES RUNTIME_OUTPUT_DIRECTORY /home/nikita/Code/ITMO/Course\ 2/System_software/Lab6\(Keylogger\)/workspace/)

