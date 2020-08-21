/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides all exceptions handler and peripherals interrupt
  *          service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "adc_config.h"
#include "main.h"

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  
  
}

/******************************************************************************/
/*                 STM32Fxxx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32fxxx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles EXTI0_IRQ Handler.
  * @param  None
  * @retval None
  */

int cnt1, cnt2, cnt_neww ;
extern int PWM_period, hh, decrem,cnt_nmbr,Nmbr_turns,Sampling,macro, limites,steps,test;



void TIM2_IRQHandler(void)
{
 /* if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
  }*/
}


void TIM3_IRQHandler(void)
{
    
 
}
/*extern  uint16_t ADC_values[ARRAYSIZE];
extern  uint16_t  value_mult;
void TIM6_DAC_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
  {
  //  if (( ADC_values[1]/4095)<0.5)  value_mult= 2048;
    //  else
        value_mult = ADC_values[0];
       //loc thong voi value_mult//   
    DMA_Cmd(DMA1_Stream6, ENABLE);
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
  }
    
}*/

void TIM1_CC_IRQHandler(void) 
{
 /* if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
    GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
    count++;
  }*/
}      
  
int index=0;
char Buff[100];
void USART1_IRQHandler(void) 
{
  /* char ch; 
   if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
     ch= USART_ReceiveData(USART1); 
     Buff[index]=ch;
     index++; 
   }*/
}  


void EXTI9_5_IRQHandler()
{
  /*
  if(EXTI_GetITStatus(EXTI_Line7)!= RESET){
     GPIO_ToggleBits(GPIOA, GPIO_Pin_10);
     EXTI_ClearITPendingBit(EXTI_Line7);
  }
*/
}

void EXTI0_IRQHandler(void)
{
  /*
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
 {
      GPIO_ToggleBits(GPIOA, GPIO_Pin_10);
      EXTI_ClearITPendingBit(EXTI_Line0);
 }
*/
}

/*extern uint16_t  value_mult ;
extern uint16_t  ADC_values[ARRAYSIZE];

void DMA2_Channel0_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0)!=RESET)
  {   
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    if (( ADC_values/4095)<0.5)
          value_mult= 2048;
     else
          value_mult = ADC_values;
     DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
  }
}*/

/**
  * @brief  This function handles EXTI15_10_IRQ Handler.
  * @param  None
  * @retval None
*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
