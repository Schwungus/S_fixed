cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

project(S_fixed
    VERSION 0.1.0
    DESCRIPTION "Header-only 16.16 fixed-point math library for C"
    LANGUAGES C)

option(S_FIXED_BUILD_TEST "Build the S_fixed test executable?" ${PROJECT_IS_TOP_LEVEL})

if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(S_fixed INTERFACE ${INCLUDE_DIR}/S_fixed.h)
target_include_directories(S_fixed INTERFACE ${INCLUDE_DIR})

if(S_FIXED_BUILD_TEST)
    add_executable(S_fixedTest ${CMAKE_CURRENT_SOURCE_DIR}/src/S_fixedTests.c)
    target_link_libraries(S_fixedTest PRIVATE S_fixed)
    target_compile_features(S_fixedTest PRIVATE c_std_11)
endif()
