cmake_minimum_required(VERSION 3.6)
project(lab6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Main.cpp BinaryHeap.h dsexceptions.h DisjSets.h Vertex.h Edge.h MinimumSpanningTree.h)

add_executable(lab6 ${SOURCE_FILES})