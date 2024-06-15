cmake_minimum_required(VERSION 3.10)
project(leetcode VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(leetcode main.cpp)

target_include_directories(leetcode PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/Linklist")
