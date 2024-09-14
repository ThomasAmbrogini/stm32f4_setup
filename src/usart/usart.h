#pragma once

#include <stddef.h>
#include <stdint.h>

#define TX_PIN 0x06U
#define RX_PIN 0x07U

typedef struct {
    volatile uint32_t sr;
    volatile uint32_t dr;
    volatile uint32_t brr;
    volatile uint32_t cr1;
    volatile uint32_t cr2;
    volatile uint32_t cr3;
    volatile uint32_t gtpr;
} Usart;

/* The _P after the name is due to the fact that the name already exist */
typedef enum {
    USART1_P,
    USART2_P,
    USART6_P
} UsartPeripheral;

typedef enum {
    USART_STOP_BIT_0_5,
    USART_STOP_BIT_1,
    USART_STOP_BIT_1_5,
    USART_STOP_BIT_2
} UsartStopBits;

typedef struct {
    UsartPeripheral peripheral;
    uint32_t data_bits;
    uint32_t baud_rate_hz;
    UsartStopBits stop_bits;
    uint32_t parity_bits;
} UsartConfig;

#ifdef __cplusplus
extern "C" {
#endif

void initStruct(Usart * p_usart_address);
void usartInit(UsartConfig * config);
void usartWrite(const char * data);
char usartRead(void);
void usartPutchar(char data);

#ifdef __cplusplus
}
#endif

