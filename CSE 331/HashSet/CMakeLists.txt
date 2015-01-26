cmake_minimum_required(VERSION 2.8.4)
project(Project4)

set(SOURCE_FILES HashFunc.cpp HashFunc.h Main.cpp HashSet.h)
add_executable(Project4 ${SOURCE_FILES})
add_definitions(-std=c++11)