cmake_minimum_required(VERSION 3.21)
project(producersConsumers C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(producersConsumers
        fifo.c
        fifo.h
        probConst.h
        producersConsumers.c)
