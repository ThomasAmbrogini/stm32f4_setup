#pragma once

/*
 * ### Procedure to start a transmission 

write
6.  Write the data to send in the USART_DR register
    *   Clears the TXE bit. When this is set it indicates that the
        communication has been started
    *   This has to be repeated in case of single buffer
7.  After all the data has been sent wait for TC=1 to notify that all the data
    has been transmitted

*/

#include <stdint.h>

#define USART6 (0x40001400U)

/* SR bits */
#define TXE 0x07

/* BRR bits */
#define DIV_FRACTION_0  0x0
#define DIV_FRACTION_1  0x1
#define DIV_FRACTION_2  0x2
#define DIV_FRACTION_3  0x3
#define DIV_MANTISSA_0  0x4
#define DIV_MANTISSA_1  0x5
#define DIV_MANTISSA_2  0x6
#define DIV_MANTISSA_3  0x7
#define DIV_MANTISSA_4  0x8
#define DIV_MANTISSA_5  0x9
#define DIV_MANTISSA_6  0xA
#define DIV_MANTISSA_7  0xB
#define DIV_MANTISSA_8  0xC
#define DIV_MANTISSA_9  0xD
#define DIV_MANTISSA_10 0xE
#define DIV_MANTISSA_11 0xF

/* CR1 bits */
#define TE 0x03
#define M  0x0C /* 0: 8 data bits. 1: 0 data bits */
#define UE 0x0D

/* CR2 bits */
#define STOP_BIT_0 0x0C
#define STOP_BIT_1 0x0D

typedef volatile struct __attribute__((__packed__)) {
    uint32_t sr;
    uint32_t dr;
    uint32_t brr;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t cr3;
    uint32_t gtpr;
} Usart;

#ifdef __cplusplus
extern "C" {
#endif

void initStruct(Usart* p_usart_address);
void usartInit(void);
void usartPutchar(char data); 
void usartWrite(const char * data);

#ifdef __cplusplus
}
#endif

