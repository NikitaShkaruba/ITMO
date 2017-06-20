cmake_minimum_required(VERSION 3.7)
project(lab_4)

set(CMAKE_CXX_STANDARD 11)

add_library(libruntime STATIC IMPORTED)
# Add path to your provided library here
set_property(TARGET libruntime PROPERTY IMPORTED_LOCATION /Users/sigma/code/ITMO/course_3/semester_6/distributed_computations/resources/lib64/libruntime.so)

set(SOURCE_FILES
        src/lib/vendor/common.h
        src/lib/vendor/ipc.h
        src/lib/vendor/bank_robbery.c
        src/lib/vendor/pa2345.h
        src/lib/vendor/banking.h

        src/lib/core/ipc.c
        src/lib/core/headers/structs.h
        src/lib/core/init.lib.c
        src/lib/core/headers/init.lib.h
        src/lib/core/run.lib.c
        src/lib/core/headers/run.lib.h
        src/lib/core/headers/include.h
        src/lib/core/banking.c
        src/lib/core/util.c
        src/lib/core/headers/util.h
        src/lib/core/headers/lamport.h

        src/lib/core/mutex.lib.c
        src/lib/core/headers/mutex.lib.h
        src/lib/data_structures/priority_queue.c
        src/lib/data_structures/priority_queue.h

        src/main.c)
add_executable(lab_4 ${SOURCE_FILES})
target_link_libraries(lab_4 libruntime)
