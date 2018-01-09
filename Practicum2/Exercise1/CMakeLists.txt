cmake_minimum_required(VERSION 3.8)
project(Exercise1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        task1.c
        timing.h
        calibrate.h)

add_executable(Exercise1 ${SOURCE_FILES})
find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(Exercise1 ${MPI_C_LIBRARIES})