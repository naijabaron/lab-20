cmake_minimum_required(VERSION 3.26)
project(lab20 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab20 main.c
        libs/solutions/lab20/lab_20_solutions.h
        libs/solutions/lab20/lab_20_solutions.c)

add_subdirectory(libs)

target_link_libraries(solutions)