set(SOURCES gpio.c)
add_library(gpio ${SOURCES})
target_include_directories(gpio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gpio options)
target_link_libraries(gpio chip_definitions)

