cmake_minimum_required(VERSION 2.8.4)
project(Project5)

set(SOURCE_FILES main.cpp MMU.h PageTableEntry.h FrameTable.h)
add_executable(PROG05 ${SOURCE_FILES})
add_definitions(-std=c++11)