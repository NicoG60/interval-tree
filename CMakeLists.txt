cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(interval_tree_test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include)
add_subdirectory(./third_party/Catch2)

enable_testing()

add_executable(${PROJECT_NAME} test/main.cpp)
target_link_libraries(${PROJECT_NAME} Catch2::Catch2)

include(CTest)
include(./third_party/Catch2/contrib/Catch.cmake)
catch_discover_tests(${PROJECT_NAME} TEST_SPEC "[test]")
