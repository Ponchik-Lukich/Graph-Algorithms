cmake_minimum_required(VERSION 3.20)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("Lab3-tests")

add_executable(Lab3 main.cpp Graph.h UndirGraph.h Function.h Algorithms.h)
