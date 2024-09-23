cmake_minimum_required(VERSION 3.15)
project(16test_set)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(test_set test_set.cpp)
target_include_directories(test_set PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})