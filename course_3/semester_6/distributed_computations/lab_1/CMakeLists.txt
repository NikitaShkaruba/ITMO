cmake_minimum_required(VERSION 3.7)
project(lab_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        common.h
        ipc.h
        main.c
        pa1.h)

add_executable(lab_1 ${SOURCE_FILES})