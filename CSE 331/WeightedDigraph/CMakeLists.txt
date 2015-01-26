cmake_minimum_required(VERSION 2.8.4)
project(Project6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES project6/Main.cpp project6/WeightedDigraph.h project6/WeightedDigraph.cpp project6/HashList.h)
add_executable(Project6 ${SOURCE_FILES})