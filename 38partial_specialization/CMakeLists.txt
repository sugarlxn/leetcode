cmake_minimum_required(VERSION 3.15...3.30)
project(partial_specialization LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(partial_specialization main.cpp)
target_include_directories(partial_specialization PRIVATE 
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR})
                