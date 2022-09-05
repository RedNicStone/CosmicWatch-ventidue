cmake_minimum_required(VERSION 3.22)
project(graphics)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER ${CMAKE_SOURCE_DIR}/src/*.h)

add_compile_options(-Wa,-alh)

add_executable(graphics
        ${SRC}
        tests/other/simple_demo.cpp)
