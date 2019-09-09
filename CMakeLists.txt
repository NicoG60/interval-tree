cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(interval_tree_test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include)
include_directories(./third_party/Catch2/single_include)

add_executable(${PROJECT_NAME} test/main.cpp)
