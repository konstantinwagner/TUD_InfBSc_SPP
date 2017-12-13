cmake_minimum_required(VERSION 3.8)
project(Aufgabe5)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCE_FILES_TASK_B TaskB/task-b.cpp komplex.cpp komplex.h ppmwrite.cpp ppmwrite.h)
add_executable(Aufgabe5_TaskB ${SOURCE_FILES_TASK_B})

set(SOURCE_FILES_TASK_C TaskC/task-c.cpp komplex.cpp komplex.h ppmwrite.cpp ppmwrite.h)
add_executable(Aufgabe5_TaskC ${SOURCE_FILES_TASK_C})