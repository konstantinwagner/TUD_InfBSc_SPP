cmake_minimum_required(VERSION 3.8)
project(Exercise2)

set(CMAKE_C_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCE_FILES_A TaskA/task_a.c)
add_executable(Exc2-TaskA ${SOURCE_FILES_A})

set(SOURCE_FILES_B TaskB/task_b.c)
add_executable(Exc2-TaskB ${SOURCE_FILES_B})

set(SOURCE_FILES_C TaskC/task_c.c)
add_executable(Exc2-TaskC ${SOURCE_FILES_C})
