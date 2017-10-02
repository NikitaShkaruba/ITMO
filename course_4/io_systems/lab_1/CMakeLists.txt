cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
project(entranse_task)

include_directories(../lib/systemc-2.3.1a/include) # Set your include path from lib here if version is not 2.3.1a
include_directories(../src) # Set your include path from lib here if version is not 2.3.1a
set(
  SOURCE_FILES

        src/main.cpp
        src/lib/mem.cpp
        src/lib/include/mem.h
        src/lib/include/mips32.h
        src/lib/mips32.cpp
        src/lib/bus.cpp
        src/lib/include/bus.h
        src/lib/include/common.h
        src/lib/fifo.cpp
        src/lib/include/fifo.h
        src/lib/icconf.cpp
        src/lib/input_capture.cpp
        src/lib/include/input_capture.h
        src/lib/ins.cpp
        src/lib/include/ins.h
        src/lib/mux_control.cpp
        src/lib/include/mux_control.h
        src/lib/prescaler.cpp
        src/lib/include/prescaler.h
        src/lib/timer.cpp
        src/lib/include/timer.h
        src/lib/include/icconf.h
)
add_executable(lab_1 ${SOURCE_FILES})

add_library(systemc_lib STATIC IMPORTED)
set_property(TARGET systemc_lib PROPERTY IMPORTED_LOCATION /Users/sigma/code/ITMO/course_4/io_systems/lib/systemc-2.3.1a/lib-macosx64/libsystemc.dylib) # Set your lib path here
target_link_libraries(lab_1 systemc_lib)
