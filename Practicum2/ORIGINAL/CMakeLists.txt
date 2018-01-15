cmake_minimum_required(VERSION 3.8)
project(ORIGINAL)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_ONE
        calibrate.h
        task1.c
        timing.h)

set(SOURCE_FILES_TWO
        task2.c)

add_executable(TASK1 ${SOURCE_FILES_ONE})
add_executable(TASK2 ${SOURCE_FILES_TWO})

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(TASK1 ${MPI_C_LIBRARIES})
target_link_libraries(TASK2 ${MPI_C_LIBRARIES})

target_link_libraries(TASK2 m)