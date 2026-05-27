cmake_minimum_required(VERSION 3.15...3.30)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(tenant_py NB_STATIC csrc/tenant_py.cpp)
install(TARGETS tenant_py LIBRARY DESTINATION .)