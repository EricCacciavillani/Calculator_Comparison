cmake_minimum_required(VERSION 3.10)
project(Final_Binary_Tree_ASM)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Final_Binary_Tree_ASM
        Binary_Cal_Tree.cpp
        Binary_Cal_Tree.h
        main.cpp)
