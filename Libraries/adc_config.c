#include "adc_config.h"
uint16_t ADC_value;

void DMA2_Init(void){
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  DMA_InitTypeDef       DMA_InitStructure;
  
  DMA_DeInit(DMA2_Stream0);
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC_value;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 9; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure); 
  
  DMA_ITConfig(DMA2_Stream0, DMA_IT_TC | DMA_IT_HT, ENABLE); 
  DMA_Cmd(DMA2_Stream0, ENABLE);
}


void ADC1_DMA_init()
{    
     DMA2_Init();
     TIM8_Init();
     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
     GPIO_InitTypeDef GPIO_InitStruct;
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN; 
     GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOC,&GPIO_InitStruct);
     
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
     
     ADC_InitTypeDef  ADC_InitStruct;  
     ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
     ADC_InitStruct.ADC_ContinuousConvMode =  DISABLE;
     ADC_InitStruct.ADC_ScanConvMode = ENABLE;
     ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T8_TRGO;
     ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising ;
     ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
     ADC_InitStruct.ADC_NbrOfConversion = 1;
     ADC_Init(ADC1, &ADC_InitStruct);

     ADC_RegularChannelConfig(ADC1, ADC_Channel_10,1,  ADC_SampleTime_15Cycles);
     //ADC_RegularChannelConfig(ADC1, ADC_Channel_11,2, ADC_SampleTime_15Cycles);
     //ADC_RegularChannelConfig(ADC1, ADC_Channel_12,3, ADC_SampleTime_15Cycles);
    
     ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
     ADC_DMACmd(ADC1, ENABLE);
     ADC_Cmd(ADC1, ENABLE); 
     ADC_SoftwareStartConv(ADC1);
}
