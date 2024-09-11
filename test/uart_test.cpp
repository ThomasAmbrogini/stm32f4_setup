#include <catch2/catch_test_macros.hpp>

#include "usart.h"

constexpr int BIT_MASK = 0x1;

TEST_CASE("UE bit is set at usartInit", "[usartInit]") {
    Usart usart = {0};
    initStruct(&usart);
    usartInit();  
    REQUIRE(((usart.cr1 >> UE) & BIT_MASK) == 0x1);
}

TEST_CASE("M bit is set to 0", "[usartInit]") {
    Usart usart = {0};
    initStruct(&usart);
    usartInit();  
    REQUIRE(((usart.cr1 >> M) & BIT_MASK) == 0x0);
}

TEST_CASE("Both stop bits are 0", "[usartInit]") {
    Usart usart = {0};
    initStruct(&usart);
    usartInit();  
    REQUIRE(((usart.cr2 >> STOP_BIT_0) & BIT_MASK) == 0x0);
    REQUIRE(((usart.cr2 >> STOP_BIT_1) & BIT_MASK) == 0x0);
}

TEST_CASE("Baud rate set to 115200", "[usartInit]") {
    Usart usart = {0};
    initStruct(&usart);
    usartInit();  
    REQUIRE(usart.brr == 0x0364);
}

TEST_CASE("TE bit set to 1", "[usartInit]") {
    Usart usart = {0};
    initStruct(&usart);
    usartInit();  
    REQUIRE(((usart.cr1 >> TE) & BIT_MASK) == 0x1);
}

