#include "usart.h"

#include "stm32f4xx.h"

static Usart * p_usart = (Usart *) USART6;

static void configureGpio(void);

/**
  * @brief Used for testing to place a different value to the usart pointer.
  * @param [in] p_usart_address address passed from the software to not use the
  *             fixed one of the actual peripheral.
  */
void initStruct(Usart* p_usart_address) {
    p_usart = p_usart_address;
}

/**
 * @brief Initialization of the usart driver.
 * @details
 *    1. clock of the USART peripheral has to be enabled.
 *    2. set the UE bit in CR1 register to 1 to enable the peripheral.
 *    3. set the M bit in CR1 register to decide the number of data bits.
 *    4. set the number of stop bits in CR2 register.
 *    5. set the baud rate in BRR register.
 *    6. set the TE bit in CR1 register (sends an idle frame as first
 *       transmission).
 * @param [in] config: configuration to apply to the USART driver.
 */
void usartInit(UsartConfig * config) {
    configureGpio();

    switch(config->peripheral) {
        case USART1_P:
            RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
            p_usart = (Usart *) USART1;
            break;
        case USART2_P:
            RCC->APB2ENR |= RCC_APB1ENR_USART2EN;
            p_usart = (Usart *) USART2;
            break;
        case USART6_P:
            RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
            p_usart = (Usart *) USART6;
            break;
    }

    p_usart->cr1 |= USART_CR1_UE;

    switch(config->data_bits) {
        case 8:
            p_usart->cr1 &= ~(USART_CR1_M);
            break;
        case 9:
            p_usart->cr1 |= USART_CR1_M;
            break;
    }

    switch(config->stop_bits) {
        case USART_STOP_BIT_0_5:
            p_usart->cr2 &= ~(USART_CR2_STOP);
            p_usart->cr2 |= (USART_CR2_STOP_0);
            break;
        case USART_STOP_BIT_1:
            p_usart->cr2 &= ~(USART_CR2_STOP);
            break;
        case USART_STOP_BIT_1_5:
            p_usart->cr2 |= (USART_CR2_STOP);
            break;
        case USART_STOP_BIT_2:
            p_usart->cr2 &= ~(USART_CR2_STOP);
            p_usart->cr2 |= (USART_CR2_STOP_1);
            break;
    }

    p_usart->brr = 0x0683;

    p_usart->cr1 |= (USART_CR1_TE);
    p_usart->cr1 |= (USART_CR1_RE);
}

/**
 * @brief Function used to send data
 * @details
 *    Once the data is written it waits for the TC bit to be set by the
 *    hardware, it is needed to wait for the TC once the last data has been
 *    written to the DR register.
 */
void usartWrite(const char * data) {
    while (*data) {
        usartPutchar(*data);
        ++data;
    }
    while (!(p_usart->sr & USART_SR_TC));
}

/**
 * @brief utility function used by usartWrite to send a char at a time.
 * @details
 *    It waits for the TXE bit to be set, which means that the DR register can
 *    be written, since the previous data has already been send to the shift
 *    register.
 */
void usartPutchar(char data) {
    while (!(p_usart->sr & USART_SR_TXE));
    p_usart->dr = data;
}

/**
 * @brief read a single char from the USART
 * @details
 *    When the RXNE bit in the status register is set it means that the value
 *    has been shifted to the DR and it can be read.
 * @params [out] the read character
 */
char usartRead(void) {
    while (!(p_usart->sr & USART_SR_RXNE));
    char c = p_usart->dr;
    return c;
}

/**
 * @brief sets the configuration for the TX and RX pin to be used.
 * @details
 *    1.  Enables the clock for the GPIO port.
 *    2.  Configures the GPIO pins: moder to AF, OTYPER push/pull and without
 *        pull up and push down resistors.
 *    3.  Set the GPIO to use the alternate function of the USART.
 */
void configureGpio(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~(0x3 << (TX_PIN * 2));
    GPIOC->MODER |= (0x2 << (TX_PIN * 2));

    GPIOC->OTYPER &= ~(0x1 << (TX_PIN));

    GPIOC->PUPDR &= ~(0x3 << (TX_PIN * 2));
    GPIOC->PUPDR |= (0x0 << (TX_PIN * 2));

    GPIOC->MODER &= ~(0x3 << (RX_PIN * 2));
    GPIOC->MODER |= (0x2 << (RX_PIN * 2));

    GPIOC->OTYPER &= ~(0x1 << (RX_PIN));

    GPIOC->PUPDR &= ~(0x3 << (RX_PIN * 2));
    GPIOC->PUPDR |= (0x0 << (RX_PIN * 2));

    GPIOC->AFR[0] &= ~(0xF << (TX_PIN * 4)); 
    GPIOC->AFR[0] |= (0x8 << (TX_PIN * 4));

    GPIOC->AFR[0] &= ~(0xF << (RX_PIN * 4)); 
    GPIOC->AFR[0] |= (0x8 << (RX_PIN * 4));
}

