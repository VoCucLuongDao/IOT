#ifndef _UART_CONFIG_H_
#define _UART_CONFIG_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "string.h"


void USART_PutChar(USART_TypeDef* USARTx, char c);
void USART_Send_string(USART_TypeDef* USARTx, char *s);

void USART1_init(uint32_t Baudrate);
void USART3_init(uint32_t Baudrate);
#endif
