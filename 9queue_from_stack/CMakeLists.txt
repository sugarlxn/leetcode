cmake_minimum_required(VERSION 3.15)
project(queue_from_stack)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(queue_from_stack queue_from_stack.cpp)
target_include_directories(queue_from_stack PUBLIC 
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_BINARY_DIR})