cmake_minimum_required(VERSION 3.20)

project(stm32f411_setup
        LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(generic_options)
add_library(options INTERFACE)
target_compile_options(options INTERFACE ${GENERIC_OPTIONS})
target_compile_definitions(options INTERFACE STM32F411xE)

include(build_type)

set(COMPILER_WARNINGS -Wall
                      -Wextra)
add_library(compiler_warnings INTERFACE)
target_compile_options(compiler_warnings INTERFACE ${COMPILER_WARNING})

add_subdirectory(src)

option(ENABLE_TEST "Build Unit Tests" OFF)

if (ENABLE_TEST)
    include(unit_test)
    add_unit_test_lib(options)
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()

