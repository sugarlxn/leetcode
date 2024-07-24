cmake_minimum_required(VERSION 3.10)
project(reference_counter VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(reference_counter_target reference_conter.cpp)
target_include_directories(reference_counter_target PUBLIC
                            "${PROJECT_BINARY_DIR}")