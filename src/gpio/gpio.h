#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_H = 7
} GpioPort;

typedef enum {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
} GpioPin;

typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT,
    GPIO_ALTERNATE_FUNCTION,
    GPIO_ANALOG
} GpioType; 

typedef enum {
    EXTI_FALLING_EDGE,
    EXTI_RISING_EDGE,
    EXTI_TRIGGER_BOTH,
} GpioTriggerType;

typedef struct {
    GpioPort port;
    GpioPin pin;
    GpioType type;
    GpioTriggerType trigger_type;
} GpioConfig;

void gpioInit(GpioConfig * config);
void gpioTurnOn(GpioConfig * config);
void gpioTurnOff(GpioConfig * config);
bool gpioReadValue(GpioConfig * config);

void gpioEXTISetUp(GpioConfig * config);

#ifdef __cplusplus
}
#endif

