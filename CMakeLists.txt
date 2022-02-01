cmake_minimum_required(VERSION 3.20)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("Lab3-tests")

set("Graphviz/include/graphviz")

include_directories("Graphviz/include/graphviz")


add_executable(Lab3 main.cpp Graph.h UndirGraph.h Function.h Algorithms.h CUtils.h)
