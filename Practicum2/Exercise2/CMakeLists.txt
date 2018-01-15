cmake_minimum_required(VERSION 3.8)
project(Exercise2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES task2.c)

add_executable(Exercise2 ${SOURCE_FILES})

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(Exercise2 ${MPI_C_LIBRARIES})

target_link_libraries(Exercise2 m)