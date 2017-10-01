cmake_minimum_required(VERSION 3.8)
project(entranse_task)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/mem.cpp
        src/mem.h
        src/mips32.cpp
        src/mips32.h)

add_executable(entranse_task ${SOURCE_FILES})