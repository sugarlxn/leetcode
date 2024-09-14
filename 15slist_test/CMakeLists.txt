cmake_minimum_required(VERSION 3.15)
project(15slist_test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(slist_test slist_test.cpp)
target_include_directories(slist_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})
