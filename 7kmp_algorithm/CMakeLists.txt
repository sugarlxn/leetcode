cmake_minimum_required(VERSION 3.15)
project(kmp_algorithm)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(kmp kmp.cpp)
target_include_directories(kmp PUBLIC 
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_BINARY_DIR})