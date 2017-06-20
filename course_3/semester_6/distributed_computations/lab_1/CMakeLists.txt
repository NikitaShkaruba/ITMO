cmake_minimum_required(VERSION 3.7)
project(lab_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/lib/headers/vendor/common.h
        src/lib/headers/vendor/ipc.h
        src/lib/headers/vendor/pa1.h
        src/lib/processes/ipc.c
        src/lib/headers/structs.h
        src/lib/processes/init.lib.c
        src/lib/headers/init.lib.h
        src/main.c
        src/lib/processes/run.lib.c
        src/lib/headers/run.lib.h
        src/lib/headers/include.h)

add_executable(lab_1 ${SOURCE_FILES})