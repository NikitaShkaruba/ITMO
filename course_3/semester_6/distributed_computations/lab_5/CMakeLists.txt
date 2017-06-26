cmake_minimum_required(VERSION 3.7)
project(lab_5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        common.h
        ipc.h
        bank_robbery.c
        pa2345.h
        banking.h

        ipc.c
        structs.h
        init.lib.c
        init.lib.h
        run.lib.c
        run.lib.h
        include.h
        banking.c
        util.c
        util.h
        lamport.h

        main.c)

add_executable(lab_5 ${SOURCE_FILES})
