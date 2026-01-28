cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

project(S_fixed VERSION 0.1.0
    DESCRIPTION "Header-only 16.16 fixed-point math library for C"
    LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(S_fixed INTERFACE ${INCLUDE_DIR}/S_fixed.h)
target_include_directories(S_fixed INTERFACE ${INCLUDE_DIR})

option(S_FIXED_BUILD_TEST "Build the S_fixed test executable?")
if(S_FIXED_BUILD_TEST)
    add_executable(S_fixedTest
        ${CMAKE_CURRENT_SOURCE_DIR}/src/S_fixedTests.c)
    target_link_libraries(S_fixedTest PRIVATE S_fixed)
endif()
