cmake_minimum_required(VERSION 3.22)
project(graphics)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(graphics
        ${SRC}
        tests/other/simple_demo.cpp)
