cmake_minimum_required(VERSION 3.15)
project(proxy_class)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)   

add_executable(proxy_class_target proxy_class.cpp)
target_include_directories(proxy_class_target PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            )
