cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled
        main.cpp
        src/Parser.cpp
        src/Parser.h
        src/Menu.cpp
        src/Menu.h
        src/KnapsackSolver.cpp
        src/KnapsackSolver.h
)