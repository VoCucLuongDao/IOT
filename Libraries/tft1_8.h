#ifndef _TFT1_8_H_
#define _TFT1_8_H_

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_dma.h"
#include "misc.h"
#include "delay.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "SPI_Config.h"
//#include "font.h

#define RS_WC  GPIO_ResetBits(GPIOB, GPIO_Pin_11);
#define RS_WD  GPIO_SetBits(GPIOB, GPIO_Pin_11);
#define RST_L  GPIO_ResetBits(GPIOB, GPIO_Pin_10);
#define RST_H  GPIO_SetBits(GPIOB, GPIO_Pin_10);

//////////////////////////////////////////////////////////////////////////////////

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define RED         	 0x001F  
#define BRED             0XF81F
#define GRED 		 0XFFE0
#define GBLUE		 0X07FF
#define BLUE           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 	         0xBC40 
#define BRRED 		 0xFC07 
#define GRAY  	         0x8430 
#define DARKBLUE      	 0x01CF	
#define LIGHTBLUE      	 0x7D7C	  
#define GRAYBLUE       	 0x5458 
#define LIGHTGREEN     	 0x841F 
//#define LIGHTGRAY      0xEF5B 
#define LGRAY 		 0xC618
#define LGRAYBLUE        0xA651 
#define LBBLUE           0x2B12 

void LCD_config();
void LCD_WR_CMD2(u16 regval);
void LCD_WR_CMD(u8 regval);
void LCD_WR_DATA2(u16 data);
void LCD_WR_DATA(u8 data);
void LCD_WR_CMD_DATA(u8 LCD_Reg, u8 LCD_RegValue);
void LCD_Init(void);
void LCD_Clear(u16 color);
void LCD_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
uint16_t LCD_Color565(uint8_t r, uint8_t g, uint8_t b);
void LCD_Pixel(uint16_t X, uint16_t Y, uint16_t color);
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LCD_PutChar(uint16_t X, uint16_t Y, char chr, uint16_t color,uint16_t bgcolor);
void LCD_PutStr(uint8_t X, uint8_t Y, char *str, uint16_t color,uint16_t bg_color);
#endif