cmake_minimum_required(VERSION 3.22)
project(graphics)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER ${CMAKE_SOURCE_DIR}/src/*.h)

add_executable(graphics
        /home/nic/.config/JetBrains/CLion2022.1/scratches/scratch.cpp)
