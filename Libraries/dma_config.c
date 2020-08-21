#include "dma_config.h"
#include "main.h"

extern uint16_t source[SIN_RES];
extern uint16_t source2[SQUARE_RES];

void DMA1_init()
{
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

DMA_DeInit(DMA1_Stream5);
DMA_InitTypeDef DMA_InitStructure;
DMA_InitStructure.DMA_Channel = DMA_Channel_7;
DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)DAC_DHR12R1_ADDR;
DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)source;
DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
DMA_InitStructure.DMA_BufferSize = SIN_RES;
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
DMA_InitStructure.DMA_MemoryBurst =  DMA_MemoryBurst_Single;
DMA_InitStructure.DMA_Priority = DMA_Priority_High;
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
DMA_InitStructure.DMA_FIFOMode =DMA_FIFOMode_Disable;  
DMA_InitStructure.DMA_FIFOThreshold= DMA_FIFOThreshold_HalfFull;
DMA_Init(DMA1_Stream5, &DMA_InitStructure);

DMA_Cmd(DMA1_Stream5, ENABLE);
}

void DMA2_init()
{
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

DMA_DeInit(DMA2_Stream3);
DMA_InitTypeDef DMA_InitStructure;
DMA_InitStructure.DMA_Channel = DMA_Channel_1;
DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)DAC_DHR12R1_ADDR;
DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)source2;
DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
DMA_InitStructure.DMA_BufferSize = SQUARE_RES;
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
DMA_InitStructure.DMA_MemoryBurst =  DMA_MemoryBurst_Single;
DMA_InitStructure.DMA_Priority = DMA_Priority_High;
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
DMA_InitStructure.DMA_FIFOMode =DMA_FIFOMode_Disable;  
DMA_InitStructure.DMA_FIFOThreshold= DMA_FIFOThreshold_HalfFull;
DMA_Init(DMA1_Stream3, &DMA_InitStructure);

DMA_Cmd(DMA1_Stream3, ENABLE);
}