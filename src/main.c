#include "gpio.h"
#include "usart.h"

typedef enum {
    COMMAND_INVALID,
    COMMAND_LED_TURN_ON,
    COMMAND_LED_TURN_OFF
} Command;

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void *memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

static Command interpretMessage(const char * buffer);
static void executeCommand(Command com);

static GpioConfig led_config;
static GpioConfig button_config;

int main() {
    const char * msg = "Start reception!\r\n";
    char buffer[100] = {0};
    size_t count = 0;
    char c;
    bool previous_value;

    UsartConfig usart_config;
    usart_config.peripheral = USART6_P;
    usart_config.data_bits = 8;
    usart_config.stop_bits = USART_STOP_BIT_1;

    usartInit(&usart_config);
    usartWrite(msg);

    led_config.port = GPIO_PORT_D;
    led_config.pin = GPIO_PIN_13;
    led_config.type = GPIO_OUTPUT;
    gpioInit(&led_config);

    button_config.port = GPIO_PORT_A;
    button_config.pin = GPIO_PIN_0;
    button_config.type = GPIO_INPUT;
    gpioInit(&button_config);

    while (1) {
        if (gpioReadValue(&button_config)) {
            if (!previous_value) {
                gpioTurnOn(&led_config); 
                previous_value = true;
            }
        } else {
            if (previous_value) {
                gpioTurnOff(&led_config);
                previous_value = false;
            }
        }

        c = usartRead();

        if (c == '\r') {
            Command com = interpretMessage(buffer);
            if (com != COMMAND_INVALID) {
                executeCommand(com);
            }

            usartPutchar('\r');
            usartPutchar('\n');
            count = 0;
            memset(buffer, 0, sizeof(buffer));
        } else {
            buffer[count++] = c;
            usartPutchar(c);
        }
    };

    return 0;
}

Command interpretMessage(const char * buffer) {
    Command com = COMMAND_INVALID;

    if (strcmp(buffer, "led_on") == 0) {
        com = COMMAND_LED_TURN_ON;
    } else if (strcmp(buffer, "led_off") == 0) {
        com = COMMAND_LED_TURN_OFF;
    }

    return com;
}

void executeCommand(Command com) {
    switch (com) {
        case COMMAND_LED_TURN_ON:
            gpioTurnOn(&led_config);
            break;
        case COMMAND_LED_TURN_OFF:
            gpioTurnOff(&led_config);
            break;
        default:
            break;
    }
}

