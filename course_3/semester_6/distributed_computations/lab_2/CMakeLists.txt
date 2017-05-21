cmake_minimum_required(VERSION 3.7)
project(lab_2)

set(CMAKE_CXX_STANDARD 11)

add_library(libruntime STATIC IMPORTED)
# Add path to your provided library here
set_property(TARGET libruntime PROPERTY IMPORTED_LOCATION /home/sigma/code/ITMO/course_3/semester_6/distributed_computations/lab_2/lib64/libruntime.so)

set(SOURCE_FILES
        src/lib/vendor/bank_robbery.c
        src/lib/vendor/banking.h
        src/lib/vendor/common.h
        src/lib/ipc.c
        src/lib/vendor/ipc.h
        src/main.c
        src/lib/vendor/pa2345.h
        src/lib/structs.h)

add_executable(lab_2 ${SOURCE_FILES})
target_link_libraries(lab_2 libruntime)
