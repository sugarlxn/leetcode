cmake_minimum_required(VERSION 3.15)
project(boost_lib)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(accumulator1 accumulator1.cpp)
target_include_directories(accumulator1 PUBLIC 
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_BINARY_DIR})