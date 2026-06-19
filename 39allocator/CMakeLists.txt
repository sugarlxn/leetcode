cmake_minimum_required(VERSION 3.15...3.30)
project(allocator LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(allocator main.cpp)
target_include_directories(allocator PRIVATE
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR})
                