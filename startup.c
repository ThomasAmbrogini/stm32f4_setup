#include <stdint.h>

#define RESERVED 0

int b;
int c;
int d;

/* Linker scritp definitions */
extern uint32_t END_STACK;
extern uint32_t _stored_data;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

void resetHandler(void);
void NMIHandler(void) __attribute__((weak, alias("defaultHandler")));
void hardFaultHandler(void) __attribute__((weak, alias("defaultHandler")));
void memManageHandler(void) __attribute__((weak, alias("defaultHandler")));
void busFaultHandler(void) __attribute__((weak, alias("defaultHandler")));
void usageFaultHandler(void) __attribute__((weak, alias("defaultHandler")));
void SVCallHandler(void) __attribute__((weak, alias("defaultHandler")));
void debugMonitorHandler(void) __attribute__((weak, alias("defaultHandler")));
void pendSVHandler(void) __attribute__((weak, alias("defaultHandler")));
void sysTickHandler(void) __attribute__((weak, alias("defaultHandler")));
void WWDGHandler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI16_PVDHandler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI21_Tamp_StampHandler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI22_RTCWakeUpHandler(void) __attribute__((weak, alias("defaultHandler")));
void FlashHandler(void) __attribute__((weak, alias("defaultHandler")));
void RCCHandler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI0Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI1Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI2Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI3Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI4Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1Stream0Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1Stream1Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1Stream2Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1Stream3Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1Stream4Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1Stream5Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1Stream6Handler(void) __attribute__((weak, alias("defaultHandler")));
void ADCHandler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI9_5Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM1Break_TIM9Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM1Up_TIM10Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM1TrgComm_TIM11Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM1CCHandler(void) __attribute__((weak, alias("defaultHandler")));
void TIM2Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM3Handler(void) __attribute__((weak, alias("defaultHandler")));
void TIM4Handler(void) __attribute__((weak, alias("defaultHandler")));
void I2C1EvHandler(void) __attribute__((weak, alias("defaultHandler")));
void I2C1ErrHandler(void) __attribute__((weak, alias("defaultHandler")));
void I2C2EvHandler(void) __attribute__((weak, alias("defaultHandler")));
void I2C2ErrHandler(void) __attribute__((weak, alias("defaultHandler")));
void SPI1Handler(void) __attribute__((weak, alias("defaultHandler")));
void SPI2Handler(void) __attribute__((weak, alias("defaultHandler")));
void USART1Handler(void) __attribute__((weak, alias("defaultHandler")));
void USART2Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI15_10Handler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI17_RTCAlarmHandler(void) __attribute__((weak, alias("defaultHandler")));
void EXTI18_OTGFSWkUpHandler(void) __attribute__((weak, alias("defaultHandler")));
void DMA1Stream7Handler(void) __attribute__((weak, alias("defaultHandler")));
void SDIOHandler(void) __attribute__((weak, alias("defaultHandler")));
void TIM5Handler(void) __attribute__((weak, alias("defaultHandler")));
void SPI3Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2Stream0Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2Stream1Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2Stream2Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2Stream3Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2Stream4Handler(void) __attribute__((weak, alias("defaultHandler")));
void OTGFSHandler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2Stream5Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2Stream6Handler(void) __attribute__((weak, alias("defaultHandler")));
void DMA2Stream7Handler(void) __attribute__((weak, alias("defaultHandler")));
void USART6Handler(void) __attribute__((weak, alias("defaultHandler")));
void I2C3EvHandler(void) __attribute__((weak, alias("defaultHandler")));
void I2C3ErrHandler(void) __attribute__((weak, alias("defaultHandler")));
void FPUHandler(void) __attribute__((weak, alias("defaultHandler")));
void SPI4Handler(void) __attribute__((weak, alias("defaultHandler")));
void SPI5Handler(void) __attribute__((weak, alias("defaultHandler")));

__attribute__((section(".isr_vector"))) 
void (* const isr_vector[]) (void) = {
    (void(* )(void))(&END_STACK),
    resetHandler,
    NMIHandler,
    hardFaultHandler,
    memManageHandler,
    busFaultHandler,
    usageFaultHandler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    SVCallHandler,
    debugMonitorHandler,
    RESERVED,
    pendSVHandler,
    sysTickHandler,
    WWDGHandler,
    EXTI16_PVDHandler,
    EXTI21_Tamp_StampHandler,
    EXTI22_RTCWakeUpHandler,
    FlashHandler,
    RCCHandler,
    EXTI0Handler,
    EXTI1Handler,
    EXTI2Handler,
    EXTI3Handler,
    EXTI4Handler,
    DMA1Stream0Handler,
    DMA1Stream1Handler,
    DMA1Stream2Handler,
    DMA1Stream3Handler,
    DMA1Stream4Handler,
    DMA1Stream5Handler,
    DMA1Stream6Handler,
    ADCHandler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    EXTI9_5Handler,
    TIM1Break_TIM9Handler,
    TIM1Up_TIM10Handler,
    TIM1TrgComm_TIM11Handler,
    TIM1CCHandler,
    TIM2Handler,
    TIM3Handler,
    TIM4Handler,
    I2C1EvHandler,
    I2C1ErrHandler,
    I2C2EvHandler,
    I2C2ErrHandler,
    SPI1Handler,
    SPI2Handler,
    USART1Handler,
    USART2Handler,
    RESERVED,
    EXTI15_10Handler,
    EXTI17_RTCAlarmHandler,
    EXTI18_OTGFSWkUpHandler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    DMA1Stream7Handler,
    RESERVED,
    SDIOHandler,
    TIM5Handler,
    SPI3Handler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    DMA2Stream0Handler,
    DMA2Stream1Handler,
    DMA2Stream2Handler,
    DMA2Stream3Handler,
    DMA2Stream4Handler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    OTGFSHandler,
    DMA2Stream5Handler,
    DMA2Stream6Handler,
    DMA2Stream7Handler,
    USART6Handler,
    I2C3EvHandler,
    I2C3ErrHandler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    FPUHandler,
    RESERVED,
    RESERVED,
    SPI4Handler,
    SPI5Handler,
};

void systemInit(void);
void copyDataSectionToRAM(void);
void initializeBSS(void);

void defaultHandler(void) {
    while(1) {}
}

void resetHandler() {
    systemInit();
    initializeBSS();
    copyDataSectionToRAM();

    /* Standard library call */
    //__libc_init_array();

    /* Launch main */
    main();
}

void initializeBSS(void) {
    uint32_t *dst;

    dst = (uint32_t *) &_start_bss;

    while (dst != (uint32_t *) &_end_bss) {
        *dst = 0;
        ++dst;
    }
}

void copyDataSectionToRAM(void) {
    uint32_t *src;
    uint32_t *dst;

    src = (uint32_t *) &_stored_data;
    dst = (uint32_t *) &_start_data;

    while (dst != (uint32_t *) &_end_data) {
        *dst = *src;
        ++src;
        ++dst;
    }
}

/**
  * @brief  Setup the microcontroller system
  *         Initialize the FPU setting, vector table location and External
  *         memory configuration.
  * @param  None
  * @retval None
  */
void systemInit(void) {
//    /* Something for the FPU */
//    /* set CP10 and CP11 Full Access */
//    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
//
//    /* Reset the RCC clock configuration to the default reset state ---------*/
//    /* Set HSION bit */
//    RCC->CR |= (uint32_t)0x00000001;
//
//    /* Reset CFGR register */
//    RCC->CFGR = 0x00000000;
//
//    /* Reset HSEON, CSSON and PLLON bits */
//    RCC->CR &= (uint32_t)0xFEF6FFFF;
//
//    /* Reset PLLCFGR register */
//    RCC->PLLCFGR = 0x24003010;
//
//    /* Reset HSEBYP bit */
//    RCC->CR &= (uint32_t)0xFFFBFFFF;
//
//    /* Disable all interrupts */
//    RCC->CIR = 0x00000000;
//
//    /* Vector Table Relocation in Internal FLASH */
//    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;
}

