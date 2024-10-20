cmake_minimum_required(VERSION 3.0)
project(json_test VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# json embedded supported
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json-3.11.3)
# add_library(json_test json_test.cpp)

add_executable(json_test json_test.cpp)
target_include_directories(json_test PUBLIC
            "${PROJECT_BINARY_DIR}"
            "${PROJECT_SOURCE_DIR}"
            "${PROJECT_SOURCE_DIR}/../json-3.11.3/include/")

target_link_libraries(json_test PRIVATE nlohmann_json::nlohmann_json)