#include "usart.h"

int a = 1;

int main() {
    const char * msg = "Hello World!";
    a = 5;

    usartWrite(msg);

    while (1) {
    };
    return 0;
}

