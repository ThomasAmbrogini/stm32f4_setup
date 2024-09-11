#include "usart.h"

static Usart * p_usart = (Usart *) USART6;

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
    p_usart->cr1 |= 1 << UE;
    p_usart->cr1 &= ~(1 << M);

    p_usart->cr2 &= ~(1 << STOP_BIT_0);
    p_usart->cr2 &= ~(1 << STOP_BIT_1);

    p_usart->brr = 0x0683;

    p_usart->cr1 |= (1 << TE);
}

void usartPutchar(char data) {
    while (p_usart->sr & TXE);
    p_usart->dr = data;
}

void usartWrite(const char * data) {
    while (*data) {
        usartPutchar(*data);
        ++data;
    }
}

