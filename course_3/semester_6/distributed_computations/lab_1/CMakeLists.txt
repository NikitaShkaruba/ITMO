cmake_minimum_required(VERSION 3.7)
project(lab_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/lib/vendor/common.h
        src/lib/vendor/ipc.h
        src/lib/vendor/pa1.h
        src/lib/ipc.c
        src/lib/structs.h
        src/lib/init.lib.c
        src/lib/init.lib.h
        src/main.c
        src/lib/run.lib.c
        src/lib/run.lib.h
        src/lib/include.h)

add_executable(lab_1 ${SOURCE_FILES})