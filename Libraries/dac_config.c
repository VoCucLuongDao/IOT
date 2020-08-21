#include "dac_config.h"
#include "main.h"

void DAC2_init()
{
	/* Initialize proper GPIO pin */
         GPIO_InitTypeDef GPIO_InitStruct;
         RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
         GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
         GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
         GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
         GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
         GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
         GPIO_Init(GPIOA,&GPIO_InitStruct);
	/* Enable DAC clock */
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	/* Set DAC options */
        DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
        DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bits2_0;
	
	/* Init and enable proper DAC */
	DAC_Init(DAC_Channel_2, &DAC_InitStruct);
	/* Enable DAC channel 2 */
	DAC->CR |= DAC_CR_EN2;
        DAC_Cmd(DAC_Channel_2, ENABLE);
        DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);

}
