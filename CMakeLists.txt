cmake_minimum_required(VERSION 3.20)

project(stm32f411_setup
        LANGUAGES C)

set(DEBUG_OPTIONS -g)
add_library(debug_options INTERFACE)
target_compile_options(debug_options INTERFACE ${DEBUG_OPTIONS})

set(BOARD_OPTIONS -mcpu=cortex-m4
                  -mfpu=fpv4-sp-d16 
                  -mthumb
                  -mfloat-abi=hard 
                  -std=gnu11
                  -nostdlib
                  --specs=nano.specs
                  -ffunction-sections 
                  -fdata-sections 
                  -fstack-usage )
add_library(board_options INTERFACE)
target_compile_options(board_options INTERFACE ${BOARD_OPTIONS})
target_link_libraries(board_options INTERFACE debug_options)

set(COMPILER_WARNINGS -Wall
                      -Wextra)
add_library(compiler_warnings INTERFACE)
target_compile_options(compiler_warnings INTERFACE ${COMPILER_WARNING})

add_library(linker_options INTERFACE)
target_link_options(linker_options INTERFACE
    -T ${CMAKE_SOURCE_DIR}/tools/linkscript.ld
    ${BOARD_OPTIONS}
    LINKER:-Map=${CMAKE_BINARY_DIR}/info/main.map
)

add_subdirectory(src)

