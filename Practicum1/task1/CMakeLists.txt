cmake_minimum_required(VERSION 3.8)
project(prim)

set(CMAKE_C_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCE_FILES_TASK_A TaskA/task-a.c)
add_executable(prim-taskA ${SOURCE_FILES_TASK_A})

set(SOURCE_FILES_TASK_B TaskB/task-b.c)
add_executable(prim-taskB ${SOURCE_FILES_TASK_B})

set(SOURCE_FILES_TASK_D TaskD/task-d.c)
add_executable(prim-taskD ${SOURCE_FILES_TASK_D})

target_link_libraries(prim-taskA m)
target_link_libraries(prim-taskB m)
target_link_libraries(prim-taskD m)