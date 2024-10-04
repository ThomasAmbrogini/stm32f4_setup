#include "gpio.h"

#include "stm32f4xx.h"

static void enableGpioBusClock(GpioPort port);
static void configureType(GpioPort port, GpioPin pin, GpioType type);
static void convertPortToHandler(GPIO_TypeDef ** handle, GpioPort port);
static int getEXTIValue(GpioPin pin);
static void setEXTILineSetting(GpioPin pin, GpioPort port);
static int getMaskInterruptLine(GpioPin pin);
static void setEXTITriggerType(GpioTriggerType trigger_type, GpioPin pin);
static void enableIRQ(GpioPin pin);
static int getIRQNumber(GpioPin pin);

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

/**
 * @brief set up a GPIO pin to an interrupt line.
 * @details
 *    The pin of every port is associated to the same interrupt line. The gpio configuration is enough to know which of
 *    interrupt lines has to be enabled.
 *    Based on the pin the correct line will be selected.
 *    Based on the port the correct bit inside the register of the syscfg can be selected.
 * @param [in] config: the configuration of the GPIO.
 */
void gpioEXTISetUp(GpioConfig * config) {
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    setEXTILineSetting(config->pin, config->port);
    EXTI->IMR |= 1U << config->pin;
    setEXTITriggerType(config->trigger_type, config->pin);
    enableIRQ(config->pin);
}

/**
 * @brief set the settings of an interrupt line by selecting the correct port which "owns" the interrupt.
 * @details
 *    In the M4 core, the registers for the EXTICR inside the SYSCFG are placed in 4 different arrays.
 *    Every array has 4 interrupt lines associated and each line has 4 bits which have to be configured based on the
 *    port.
 * @param[in] pin: the pin for which the line has to be configured.
 * @param[in] port: the port for which the line has to be configured.
 */
void setEXTILineSetting(GpioPin pin, GpioPort port) {
    const int index_exticr = pin / 4;
    SYSCFG->EXTICR[index_exticr] &= ~(getMaskInterruptLine(pin));
    SYSCFG->EXTICR[index_exticr] |= (port << (pin % 4));
}

/**
 * @brief reset the settings of an interrupt line by placing all zeroes on the mask.
 * @details
 *    In the M4 core, the registers for the EXTICR inside the SYSCFG are placed in 4 different arrays.
 *    Every array has 4 interrupt lines associated and each line has 4 bits.
 * @param[in] pin: the pin for which the settings have to be resetted.
 */
int getMaskInterruptLine(GpioPin pin) {
    return (0xFUL << ((pin % 4) * 4));
}

/**
 * @brief set the EXTI register to detect the correct trigger (falling/rising edge of the signal).
 * @param[in] trigger_type: falling, rising or both.
 * @param[in] pin: pin number of the gpio which is begin configured.
 */
void setEXTITriggerType(GpioTriggerType trigger_type, GpioPin pin) {
    switch (trigger_type) {
        case EXTI_FALLING_EDGE:
            EXTI->RTSR |= (1 << pin);
            break;
        case EXTI_RISING_EDGE:
            EXTI->FTSR |= (1 << pin);
            break;
        case EXTI_TRIGGER_BOTH:
            EXTI->RTSR |= (1 << pin);
            EXTI->FTSR |= (1 << pin);
            break;
    }
}

/**
 * @brief calls the CMSIS function to enable an interrupt on the NVIC.
 * @param[in] pin: pin for which the exti has to be set.
 */
void enableIRQ(GpioPin pin) {
    NVIC_EnableIRQ(getIRQNumber(pin));
}

/**
 * @brief convert the pin to the number of the IRQ.
 * @param[in] pin: pin for which the exti has to be set.
 * @return the value of the IRQn.
 */
int getIRQNumber(GpioPin pin) {
    int ret = -1;

    switch (pin) {
        case GPIO_PIN_0:
            ret = EXTI0_IRQn;
            break;
        case GPIO_PIN_1:
            ret = EXTI1_IRQn;
            break;
        case GPIO_PIN_2:
            ret = EXTI2_IRQn;
            break;
        case GPIO_PIN_3:
            ret = EXTI3_IRQn;
            break;
        case GPIO_PIN_4:
            ret = EXTI4_IRQn;
            break;
        case GPIO_PIN_5:
        case GPIO_PIN_6:
        case GPIO_PIN_7:
        case GPIO_PIN_8:
        case GPIO_PIN_9:
            ret = EXTI9_5_IRQn;
            break;
        case GPIO_PIN_10:
        case GPIO_PIN_11:
        case GPIO_PIN_12:
        case GPIO_PIN_13:
        case GPIO_PIN_14:
        case GPIO_PIN_15:
            ret = EXTI15_10_IRQn;
            break;
    }

    return ret;
}

