cmake_minimum_required(VERSION 3.15)
project(auto_ptr)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(auto_ptr_target main.cpp)
target_include_directories(auto_ptr_target PUBLIC
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            )