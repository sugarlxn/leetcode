cmake_minimum_required(VERSION 3.15)
project(virtual_function)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(virtual_function virtual_function.cpp)

target_include_directories(virtual_function PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
