cmake_minimum_required(VERSION 3.10)
project(acm_ws VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(acm_target main_acm.cpp)

target_include_directories(acm_target PUBLIC
                            "${PROJECT_BINARY_DIR}")
