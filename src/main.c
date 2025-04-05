#include "gpio.h"
#include "usart.h"

#include "stm32f4xx.h"

#define ASSERT(expr) ((expr) ? (void)0 : assert_failed(__FILE__, __LINE__))

void assert_failed(const char *file, int line) {
    // You can log the error, stop execution, or trigger a breakpoint
    // In bare-metal, this could be sending output via UART, flashing an LED, or halting
    while (true) {
        // Implement your desired behavior here
        // Example: halt the system or enter an infinite loop
    }
}

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
    volatile size_t v_num = num;
    while (v_num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    // Copy n bytes from src to dest
    while (n--) {
        *d++ = *s++;
    }

    return dest;
}

static Command interpretMessage(const char * buffer);
static void executeCommand(Command com);

static GpioConfig led_config;
static GpioConfig button_config;
static GpioConfig analyze_pin_config;

volatile static bool previous_value = false;
volatile static bool analyze_value = false;

void EXTI0Handler(void) {
    gpioTurnOn(&analyze_pin_config);

    if (EXTI->PR & (1 << GPIO_PIN_0)) {
        // Clear the EXTI status flag.
        EXTI->PR |= (1 << GPIO_PIN_0);

        if (previous_value) {
            gpioTurnOff(&led_config);
        } else {
            gpioTurnOn(&led_config);
        }

        previous_value = !previous_value;
    }

    gpioTurnOff(&analyze_pin_config);
}

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

    analyze_pin_config.port = GPIO_PORT_A;
    analyze_pin_config.pin = GPIO_PIN_8;
    analyze_pin_config.type = GPIO_OUTPUT;
    gpioInit(&analyze_pin_config);

    button_config.port = GPIO_PORT_A;
    button_config.pin = GPIO_PIN_0;
    button_config.type = GPIO_INPUT;
    button_config.trigger_type = EXTI_RISING_EDGE;
    gpioInit(&button_config);
    gpioEXTISetUp(&button_config);

    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY)) { }

    while (1) {
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

    ASSERT(com != COMMAND_INVALID);

    return com;
}

void executeCommand(Command com) {
    switch (com) {
        case COMMAND_LED_TURN_ON:
            gpioTurnOn(&led_config);
            previous_value = true;
            break;
        case COMMAND_LED_TURN_OFF:
            gpioTurnOff(&led_config);
            previous_value = false;
            break;
        default:
            break;
    }
}

