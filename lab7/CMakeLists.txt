cmake_minimum_required(VERSION 3.6)
project(lab7)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp TreeNode.cpp TreeNode.h BinaryHeap.h dsexceptions.h FileCompressor.cpp FileCompressor.h FileDecompressor.cpp FileDecompressor.h)

add_executable(lab7 ${SOURCE_FILES})