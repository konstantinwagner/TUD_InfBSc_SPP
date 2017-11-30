cmake_minimum_required(VERSION 3.8)
project(prim)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(prim ${SOURCE_FILES})

target_link_libraries(prim m)