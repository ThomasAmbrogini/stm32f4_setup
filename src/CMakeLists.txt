set(STARTUP startup.c)
add_library(startup ${STARTUP})
target_link_libraries(startup compiler_warnings)
target_link_libraries(startup board_options)
# In this way there is no warning about missing main for startup file
target_compile_options(startup PRIVATE -Wno-implicit-function-declaration)

set(SOURCES main.c)
add_executable(main ${SOURCES})
set_target_properties(main PROPERTIES OUTPUT_NAME "main.elf")
target_link_libraries(main board_options)
target_link_libraries(main compiler_warnings)
target_link_libraries(main linker_options)
target_link_libraries(main startup)

add_custom_command(TARGET main
                   POST_BUILD
                   COMMAND ${CMAKE_OBJCOPY} -O binary main.elf main.bin 
                   COMMENT "Converting ELF to binary")

# Create the info directory
set(INFO_DIR "${CMAKE_BINARY_DIR}/info")
file(MAKE_DIRECTORY ${INFO_DIR})

add_custom_command(TARGET main
                   POST_BUILD
                   COMMAND ${CMAKE_OBJDUMP} -D main.elf > ${INFO_DIR}/disassembly
                   COMMENT "Generating disassembly")

add_custom_command(TARGET main
                   POST_BUILD
                   COMMAND ${CMAKE_OBJDUMP} -h main.elf > ${INFO_DIR}/sections
                   COMMENT "Generating sections")

add_custom_command(TARGET main
                   POST_BUILD
                   COMMAND ${CMAKE_OBJDUMP} -t main.elf > ${INFO_DIR}/symbols
                   COMMENT "Generating symbols")

