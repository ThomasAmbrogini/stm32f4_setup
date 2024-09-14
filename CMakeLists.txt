cmake_minimum_required(VERSION 3.20)

project(stm32f411_setup
        LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(ENABLE_DEBUG_OPTIONS "Add Debug Options to the compilation" ON)
option(EMBEDDED_TARGET "Use the compiler for the embedded target" ON)

include(generic_options)
add_library(options INTERFACE)
target_compile_options(options INTERFACE ${GENERIC_OPTIONS})
target_compile_definitions(options INTERFACE STM32F411xE)

if (EMBEDDED_TARGET)
    include(board_options)
    target_compile_options(options INTERFACE ${BOARD_OPTIONS})
endif ()

if (ENABLE_DEBUG_OPTIONS)
    include(debug_options)
    target_link_libraries(options INTERFACE debug_options)
endif ()

set(COMPILER_WARNINGS -Wall
                      -Wextra)
add_library(compiler_warnings INTERFACE)
target_compile_options(compiler_warnings INTERFACE ${COMPILER_WARNING})

add_library(linker_options INTERFACE)
target_link_options(linker_options INTERFACE
    LINKER:-Map=${CMAKE_BINARY_DIR}/info/main.map
)

if (EMBEDDED_TARGET)
    set(BOARD_LINKER_OPTIONS ${BOARD_OPTIONS} 
                             -T ${CMAKE_SOURCE_DIR}/tools/linkscript.ld)
    target_link_libraries(linker_options INTERFACE "-Wl,--gc-sections")
    target_link_options(linker_options INTERFACE ${BOARD_LINKER_OPTIONS})
endif ()

add_subdirectory(src)

option(ENABLE_TEST "Build Unit Tests" OFF)

if (ENABLE_TEST)
    include(unit_test)
    add_unit_test_lib(options)
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()

