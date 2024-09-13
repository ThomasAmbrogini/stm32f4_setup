#include "usart.h"

#include "stm32f4xx.h"

static Usart * p_usart = (Usart *) USART6;

static void configureGpio(void);

/**
  * @brief Used for testing to place a different value to the usart 
  * pointer
  */
void initStruct(Usart* p_usart_address) {
    p_usart = p_usart_address;
}

/**
  * @brief Initialization of the usart driver
  * @description 1. set the UE bit in CR1 register to 1
  *              2. set the M bit in CR1 register to 0 for 8 data bits
  *              3. set the number of stop bits (00 to have 1) in CR2 register
  *              4. set the baud rate in BRR register: right now for 9600
  *              5. set the TE bit in CR1 register (sends an idle frame as 
  *                 first transmission)
  *
  */
void usartInit(void) {
    /* the clock of the peripheral has to be enabled */
    RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

    configureGpio();

    p_usart->cr1 |= 1 << UE;
    p_usart->cr1 &= ~(1 << M);

    p_usart->cr2 &= ~(1 << STOP_BIT_0);
    p_usart->cr2 &= ~(1 << STOP_BIT_1);

    p_usart->brr = 0x0683;

    p_usart->cr1 |= (1 << TE);
}

void usartPutchar(char data) {
    while (!(p_usart->sr & (1 << TXE)));
    p_usart->dr = data;
    while (!(p_usart->sr & (1 << TC)));
}

void usartWrite(const char * data) {
    while (*data) {
        usartPutchar(*data);
        ++data;
    }
}

void configureGpio(void) {
    /* The clock of the GPIO pins that will be used for the TX/RX has to be
     * enabled 
     */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /* Moder of the TX pin should be configured as AF */
    GPIOC->MODER &= ~(0x3 << (TX_PIN * 2));
    GPIOC->MODER |= (0x2 << (TX_PIN * 2));

    /* The output type is Push/pull */
    GPIOC->OTYPER &= ~(0x1 << (TX_PIN));

    GPIOC->PUPDR &= ~(0x3 << (TX_PIN * 2));
    GPIOC->PUPDR |= (0x0 << (TX_PIN * 2));

    /* Moder of the RX pin should be configured as AF */
    GPIOC->MODER &= ~(0x3 << (RX_PIN * 2));
    GPIOC->MODER |= (0x2 << (RX_PIN * 2));

    /* The output type is Push/pull */
    GPIOC->OTYPER &= ~(0x1 << (RX_PIN));

    GPIOC->PUPDR &= ~(0x3 << (RX_PIN * 2));
    GPIOC->PUPDR |= (0x0 << (RX_PIN * 2));

    /* Pinmuxing for the TX pin, 0x8 is UART6 AF */
    GPIOC->AFR[0] &= ~(0xF << (TX_PIN * 4)); 
    GPIOC->AFR[0] |= (0x8 << (TX_PIN * 4));

    /* Pinmuxing for the RX pin, 0x8 is UART6 AF */
    GPIOC->AFR[0] &= ~(0xF << (RX_PIN * 4)); 
    GPIOC->AFR[0] |= (0x8 << (RX_PIN * 4));
}

