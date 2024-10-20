cmake_minimum_required(VERSION 3.5)
project(functor)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(functor functor.cpp)
target_include_directories(functor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                           ${CMAKE_BINARY_SOURCE_DIR})