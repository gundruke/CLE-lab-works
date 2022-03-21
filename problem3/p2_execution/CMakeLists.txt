cmake_minimum_required(VERSION 3.21)
project(p2_execution C)

set(CMAKE_C_STANDARD 99)

add_executable(p2_execution main.c)
target_link_libraries(p2_execution m)