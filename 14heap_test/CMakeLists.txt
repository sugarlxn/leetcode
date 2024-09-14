cmake_minimum_required(VERSION 3.15)
project(14heap_test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(heap_test heap_test.cpp)
target_include_directories(heap_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})   