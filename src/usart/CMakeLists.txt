set(SOURCES usart.c)
add_library(usart ${SOURCES})
target_include_directories(usart INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(usart options)
target_link_libraries(usart linker_options)
target_link_libraries(usart chip_definitions)

