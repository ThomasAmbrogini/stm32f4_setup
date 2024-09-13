#include "usart.h"
#include "stm32f4xx.h"

int a = 1;

int main() {
    const char * msg = "Hello World!";
    a = 5;

    usartInit();
    usartWrite(msg);

    while (1) {
    };

    return 0;
}

