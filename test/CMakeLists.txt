set(SOURCES_TEST uart_test.cpp)
add_executable(uart_test ${SOURCES_TEST})
target_link_libraries(uart_test usart Catch2::Catch2WithMain)

