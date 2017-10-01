cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
project(entranse_task)

include_directories(../lib/systemc-2.3.1a/include) # Set your include path from lib here if version is not 2.3.1a
set(
  SOURCE_FILES
  src/main.cpp
  src/mem.cpp
  src/mem.h
  src/mips32.h
  src/mips32.cpp
)
add_executable(lab_1 ${SOURCE_FILES})

add_library(systemc_lib STATIC IMPORTED)
set_property(TARGET systemc_lib PROPERTY IMPORTED_LOCATION /Users/sigma/code/ITMO/course_4/io_systems/lib/systemc-2.3.1a/lib-macosx64/libsystemc.dylib) # Set your lib path here
target_link_libraries(lab_1 systemc_lib)
