#include <stdint.h>

#define SRAM_START 0x20000000
#define SRAM_SIZE (128U * 1024) /* 128 KB */
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define RESERVED SRAM_END

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

uint32_t vector_table[] __attribute__((section (".vector_table") )) = {
    RESERVED,
    (uint32_t)resetHandler,
    (uint32_t)hardFaultHandler,
    (uint32_t)memManageHandler,
    (uint32_t)busFaultHandler,
    (uint32_t)usageFaultHandler,
    RESERVED,
    (uint32_t)SVCallHandler,
    (uint32_t)debugMonitorHandler,
    RESERVED,
    (uint32_t)pendSVHandler,
    (uint32_t)sysTickHandler,
    (uint32_t)WWDGHandler,
    (uint32_t)EXTI16_PVDHandler,
    (uint32_t)EXTI21_Tamp_StampHandler,
    (uint32_t)EXTI22_RTCWakeUpHandler,
    (uint32_t)FlashHandler,
    (uint32_t)RCCHandler,
    (uint32_t)EXTI0Handler,
    (uint32_t)EXTI1Handler,
    (uint32_t)EXTI2Handler,
    (uint32_t)EXTI3Handler,
    (uint32_t)EXTI4Handler,
    (uint32_t)DMA1Stream0Handler,
    (uint32_t)DMA1Stream1Handler,
    (uint32_t)DMA1Stream2Handler,
    (uint32_t)DMA1Stream3Handler,
    (uint32_t)DMA1Stream4Handler,
    (uint32_t)DMA1Stream5Handler,
    (uint32_t)DMA1Stream6Handler,
    (uint32_t)ADCHandler,
    (uint32_t)EXTI9_5Handler,
    (uint32_t)TIM1Break_TIM9Handler,
    (uint32_t)TIM1Up_TIM10Handler,
    (uint32_t)TIM1TrgComm_TIM11Handler,
    (uint32_t)TIM1CCHandler,
    (uint32_t)TIM2Handler,
    (uint32_t)TIM3Handler,
    (uint32_t)TIM4Handler,
    (uint32_t)I2C1EvHandler,
    (uint32_t)I2C1ErrHandler,
    (uint32_t)I2C2EvHandler,
    (uint32_t)I2C2ErrHandler,
    (uint32_t)SPI1Handler,
    (uint32_t)SPI2Handler,
    (uint32_t)USART1Handler,
    (uint32_t)USART2Handler,
    (uint32_t)EXTI15_10Handler,
    (uint32_t)EXTI17_RTCAlarmHandler,
    (uint32_t)EXTI18_OTGFSWkUpHandler,
    (uint32_t)DMA1Stream7Handler,
    (uint32_t)SDIOHandler,
    (uint32_t)TIM5Handler,
    (uint32_t)SPI3Handler,
    (uint32_t)DMA2Stream0Handler,
    (uint32_t)DMA2Stream1Handler,
    (uint32_t)DMA2Stream2Handler,
    (uint32_t)DMA2Stream3Handler,
    (uint32_t)DMA2Stream4Handler,
    (uint32_t)OTGFSHandler,
    (uint32_t)DMA2Stream5Handler,
    (uint32_t)DMA2Stream6Handler,
    (uint32_t)DMA2Stream7Handler,
    (uint32_t)USART6Handler,
    (uint32_t)I2C3EvHandler,
    (uint32_t)I2C3ErrHandler,
    (uint32_t)FPUHandler,
    (uint32_t)SPI4Handler,
    (uint32_t)SPI5Handler,
};

void defaultHandler(void) {
    while(1) {}
}

void resetHandler() {
}

