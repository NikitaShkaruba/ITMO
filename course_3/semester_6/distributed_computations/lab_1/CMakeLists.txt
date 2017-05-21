cmake_minimum_required(VERSION 3.7)
project(lab_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/lib/vendor/common.h
        src/lib/vendor/ipc.h
        src/main.c
        src/lib/vendor/pa1.h
        src/lib/ipc.c
        src/lib/structs.h
        )

add_executable(lab_1 ${SOURCE_FILES})