cmake_minimum_required(VERSION 3.27.0 FATAL_ERROR)

project(
    S_fixed
    VERSION 0.1.0
    DESCRIPTION "Header-only 16.16 fixed-point math library for C"
    LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(S_fixed INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/S_fixed.h)
target_include_directories(S_fixed INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

option(S_FIXED_BUILD_TEST "Build the S_fixed test executable?" ON)
if(S_FIXED_BUILD_TEST)
    add_executable(S_fixedTest ${CMAKE_CURRENT_SOURCE_DIR}/S_fixedTests.c)
    target_link_libraries(S_fixedTest PRIVATE S_fixed)
endif()
