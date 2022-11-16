cmake_minimum_required(VERSION 3.22)
project(dz3)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(1)
add_executable(2 2.cpp)
add_executable(3 3.cpp 1/ArcGraph.cpp)
add_executable(4 4.cpp)
add_executable(4_1 4_1.cpp)
add_subdirectory(5)
add_executable(5_1 5.cpp)
