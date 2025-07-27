cmake_minimum_required(VERSION 3.27.0 FATAL_ERROR)

project(
    S_fixed
    VERSION 0.1.0
    DESCRIPTION "Header-only 16.16 fixed-point math library for C"
    LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_library(${PROJECT_NAME} INTERFACE ${SOURCE_DIR}/S_fixed.h)
target_include_directories(${PROJECT_NAME} INTERFACE ${SOURCE_DIR})

set(TEST_NAME ${PROJECT_NAME}Test)
add_executable(${TEST_NAME} ${SOURCE_DIR}/S_fixedTests.c)
target_link_libraries(${TEST_NAME} PRIVATE ${PROJECT_NAME})
