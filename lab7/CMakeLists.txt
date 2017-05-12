cmake_minimum_required(VERSION 3.6)
project(lab7)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp HashTableGenerationTest.h TreeNode.cpp TreeNode.h BinaryHeap.h dsexceptions.h)

add_executable(lab7 ${SOURCE_FILES})