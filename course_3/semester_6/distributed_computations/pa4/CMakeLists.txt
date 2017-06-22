cmake_minimum_required(VERSION 3.7)
project(lab_4)

set(CMAKE_CXX_STANDARD 11)

add_library(libruntime STATIC IMPORTED)
# Add path to your provided library here
set_property(TARGET libruntime PROPERTY IMPORTED_LOCATION /Users/sigma/code/ITMO/course_3/semester_6/distributed_computations/resources/lib64/libruntime.so)

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

        mutex.lib.c
        priority_queue.c
        priority_queue.h

        main.c)
add_executable(lab_4 ${SOURCE_FILES})
target_link_libraries(lab_4 libruntime)
