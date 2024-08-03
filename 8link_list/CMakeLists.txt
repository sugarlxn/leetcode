cmake_minimum_required(VERSION 3.15)
project(linkList)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(linkList linkList.cpp)
target_include_directories(linkList PUBLIC 
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_BINARY_DIR})
