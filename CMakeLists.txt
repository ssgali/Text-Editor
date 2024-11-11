cmake_minimum_required(VERSION 3.29)
project(Assignment_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assignment_4 main.cpp
        classes.h
        functions.h)

target_link_libraries(Assignment_4 pdcurses)
