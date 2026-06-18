cmake_minimum_required(VERSION 3.15)
project(iterator_traits)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加调试参数
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(iterator_traits main.cpp)
target_include_directories(iterator_traits PRIVATE 
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR})
