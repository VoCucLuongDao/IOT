#ifndef _LCD_TXT_H_
#define _LCD_TXT_H_
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"

#define Port_EN GPIOB
#define Port_RS GPIOB
#define Port_D4 GPIOB
#define Port_D5 GPIOB
#define Port_D6 GPIOB
#define Port_D7 GPIOB

#define Pin_EN GPIO_Pin_0
#define Pin_RS GPIO_Pin_1
#define Pin_D4 GPIO_Pin_11
#define Pin_D5 GPIO_Pin_12
#define Pin_D6 GPIO_Pin_13
#define Pin_D7 GPIO_Pin_14

void GPIO_Config();
void LCD_Init();
void LCD_Send4Bit(unsigned char Data);
void LCD_Clear();
void LCD_Gotoxy(unsigned char y, unsigned char x);
void LCD_PutChar(unsigned char Data);
void LCD_Puts(char *s);
void LCD_SendCommand(unsigned char command);

#endif