cmake_minimum_required(VERSION 3.27.0 FATAL_ERROR)

project(
    S_fixed
    VERSION 0.1.0
    DESCRIPTION "Header-only 16.16 fixed-point math library for C"
    LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(S_FIXED_LIB_NAME ${PROJECT_NAME} CACHE INTERNAL "S_fixed library target name")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_library(${S_FIXED_LIB_NAME} INTERFACE ${SOURCE_DIR}/S_fixed.h)
target_include_directories(${S_FIXED_LIB_NAME} INTERFACE ${SOURCE_DIR})

set(TEST_NAME ${S_FIXED_LIB_NAME}Test)
option(S_FIXED_BUILD_TEST "Build the ${TEST_NAME} executable?" ON)
if(S_FIXED_BUILD_TEST)
    add_executable(${TEST_NAME} ${SOURCE_DIR}/S_fixedTests.c)
    target_link_libraries(${TEST_NAME} PRIVATE ${S_FIXED_TEST_NAME})
endif()
