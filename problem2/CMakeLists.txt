cmake_minimum_required(VERSION 3.21)
project(problem2 C)

set(CMAKE_C_STANDARD 99)

add_executable(problem2 main.c)
target_link_libraries(problem2 m)
