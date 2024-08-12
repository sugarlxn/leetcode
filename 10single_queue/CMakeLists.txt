cmake_minimum_required(VERSION 3.15)
project(single_queue)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(single_queue single_queue.cpp)
target_include_directories(single_queue PUBLIC 
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_BINARY_DIR})