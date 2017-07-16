cmake_minimum_required(VERSION 3.3)
project(Fall2016_CSI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES CycleTestCases.c)
add_executable(Fall2016_CSI ${SOURCE_FILES})