#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "misc.h"
#include "timer_config.h"

#define ADC1_DR_ADDRESS    (uint32_t)0x4001204C
void ADC1_DMA_init();
void DMA2_Init();

#endif
