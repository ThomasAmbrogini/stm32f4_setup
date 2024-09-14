#include "usart.h"
#include "stm32f4xx.h"
int main() {
    const char * msg = "Hello World!\r\n";

    UsartConfig usart_config;
    usart_config.peripheral = USART6_P;
    usart_config.data_bits = 8;
    usart_config.stop_bits = USART_STOP_BIT_1;

    usartInit(&usart_config);
    usartWrite(msg);

    while (1) {
    };

    return 0;
}

