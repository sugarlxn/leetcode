cmake_minimum_required(VERSION 3.10)
project(acm_template VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(acm_template 2a+b2.cpp)

target_include_directories(acm_template PUBLIC
                            "${PROJECT_BINARY_DIR}")
