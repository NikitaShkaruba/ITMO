cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
project(entranse_task)

include_directories(/run/media/trionprog/ccc6f104-abca-49ec-8db7-303c8e38ab37/ITMO/course_4/io_systems/lab_1/systemc-2.3.1a/include) # Set your include path from lib here if version is not 2.3.1a
set(SOURCE_FILES
        src/main.cpp

        src/lib/src/core.cpp
        src/lib/include/core.h

        src/lib/include/bus.h
        src/lib/include/addresses.h

        src/lib/input_capture.cpp
        src/lib/include/input_capture/input_capture.h
        src/lib/include/input_capture/config.h
        src/lib/include/timer1.h src/lib/include/common.h src/lib/src/timer1.cpp src/lib/src/icconf.cpp src/lib/include/icconf.h src/lib/src/bus.cpp src/lib/include/edge_detector.h src/lib/src/edge_detector.cpp src/lib/include/prescaler.h src/lib/src/prescaler.cpp)

add_executable(lab_1 ${SOURCE_FILES})

add_library(systemc_lib STATIC IMPORTED)
set_property(TARGET systemc_lib PROPERTY IMPORTED_LOCATION /run/media/trionprog/ccc6f104-abca-49ec-8db7-303c8e38ab37/ITMO/course_4/io_systems/lab_1/systemc-2.3.1a/lib-linux64/libsystemc.so) # Set your lib path here
target_link_libraries(lab_1 systemc_lib)