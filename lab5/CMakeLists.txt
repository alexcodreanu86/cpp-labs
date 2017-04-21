cmake_minimum_required(VERSION 3.6)
project(lab5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Main.cpp BinaryHeap.h dsexceptions.h)

add_executable(lab5 ${SOURCE_FILES})