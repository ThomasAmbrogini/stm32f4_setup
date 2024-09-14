#include "gpio.h"

#include "stm32f4xx.h"

static void enableGpioBusClock(GpioPort port);
static void configureType(GpioPort port, GpioPin pin, GpioType type);
static void convertPortToHandler(GPIO_TypeDef ** handle, GpioPort port);

/**
 * @brief Configuration of the GPIO pin specified with the given config.
 * @param [in] config: the configuration of the GPIO.
 */
void gpioInit(GpioConfig * config) {
    enableGpioBusClock(config->port);
    configureType(config->port, config->pin, config->type);
}

/**
 * @brief Enables the bus clock to the GPIO port.
 * @param [in] port: enum value of the GPIO port.
 */
void enableGpioBusClock(GpioPort port) {
    switch (port) {
        case GPIO_PORT_A:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
            break;
        case GPIO_PORT_B:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
            break;
        case GPIO_PORT_C:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
            break;
        case GPIO_PORT_D:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
            break;
        case GPIO_PORT_E:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
            break;
        case GPIO_PORT_H:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
            break;
   }
}

/**
 * @brief based on the type, the GPIO is configured.
 * @param [in] port: enum value of the GPIO port.
 * @param [in] pin: enum value of the GPIO pin number.
 * @param [in] type: enum value of the type of the GPIO.
 */
void configureType(GpioPort port, GpioPin pin, GpioType type) {
    GPIO_TypeDef * handle;
    convertPortToHandler(&handle, port);

    switch(type) {
        case GPIO_INPUT:
            handle->MODER &= ~(0x3 << (pin * 2));
            handle->PUPDR &= ~(0x3 << (pin * 2));
            break;
        case GPIO_OUTPUT:
            handle->MODER |= (0x1 << (pin * 2));
            handle->OTYPER &= ~(0x1 << pin);
            handle->PUPDR &= ~(0x3 << (pin * 2));
            break;
        case GPIO_ALTERNATE_FUNCTION:
            break;
        case GPIO_ANALOG:
            break;
    }
}

/**
 * @brief set the value 1 to the GPIO.
 * @details
 *    can only be used on output pins.
 * @param [in] config: the configuration of the GPIO.
 */
void gpioTurnOn(GpioConfig * config) {
    GPIO_TypeDef * handle;
    convertPortToHandler(&handle, config->port);
    handle->ODR |= (0x1 << config->pin);
}

/**
 * @brief set the value 0 to the GPIO.
 * @details
 *    can only be used on output pins.
 * @param [in] config: the configuration of the GPIO.
 */
void gpioTurnOff(GpioConfig * config) {
    GPIO_TypeDef * handle;
    convertPortToHandler(&handle, config->port);
    handle->ODR &= ~(0x1 << config->pin);
}

/**
 * @brief reads the current value of the GPIO.
 * @details
 *    can be used by INPUT and OUTPUT GPIOs.
 * @param [in] config: the configuration of the GPIO.
 * @return true if the value of the bit is 1, 0 otherwise.
 */
bool gpioReadValue(GpioConfig * config) {
    GPIO_TypeDef * handle;
    convertPortToHandler(&handle, config->port);
    bool value = handle->IDR & (0x1 << config->pin);
    return value;
}

/**
 * @brief converts the enum of the GPIO port to the handler of  the address.
 * @param [out] handle: provided from the caller, it will have the pointer to
 *              the address.
 * @param [in] port: the enum value of the GPIO port.
 */
void convertPortToHandler(GPIO_TypeDef ** handle, GpioPort port) {
    switch (port) {
        case GPIO_PORT_A:
            *handle = (GPIO_TypeDef *) GPIOA;
            break;
        case GPIO_PORT_B:
            *handle = (GPIO_TypeDef *) GPIOB;
            break;
        case GPIO_PORT_C:
            *handle = (GPIO_TypeDef *) GPIOC;
            break;
        case GPIO_PORT_D:
            *handle = (GPIO_TypeDef *) GPIOD;
            break;
        case GPIO_PORT_E:
            *handle = (GPIO_TypeDef *) GPIOE;
            break;
        case GPIO_PORT_H:
            *handle = (GPIO_TypeDef *) GPIOH;
            break;
   }
}

