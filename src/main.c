#include "usart.h"
#include "stm32f4xx.h"

int main() {
    const char * msg = "Start reception!\r\n";
    char buffer[10] = {0};
    char c;

    UsartConfig usart_config;
    usart_config.peripheral = USART6_P;
    usart_config.data_bits = 8;
    usart_config.stop_bits = USART_STOP_BIT_1;

    usartInit(&usart_config);
    usartWrite(msg);

    while (1) {
        c = usartRead();

        if (c == '\r') {
            buffer[0] = '\r';
            buffer[1] = '\n';
        } else {
            buffer[0] = c;
            buffer[1] = '\0';
        }

        usartWrite(buffer);
    };

    return 0;
}

