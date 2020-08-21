#include "LCD_txt.h"

void GPIO_Config()
{
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOB,&GPIO_InitStruct);
}
void LCD_Enable()
{ 
  GPIO_WriteBit(Port_EN,Pin_EN,Bit_SET);
  delayus(50);
  GPIO_WriteBit(Port_EN,Pin_EN,Bit_RESET);
  delayus(50); 
}
void LCD_Send4Bit(unsigned char Data)
{
    GPIO_WriteBit(Port_D4,Pin_D4,(Data&0x01)?Bit_SET:Bit_RESET);
    GPIO_WriteBit(Port_D5,Pin_D5,((Data>>1)&0x01)?Bit_SET:Bit_RESET);	
    GPIO_WriteBit(Port_D6,Pin_D6,((Data>>2)&0x01)?Bit_SET:Bit_RESET);	
    GPIO_WriteBit(Port_D7,Pin_D7,((Data>>3)&0x01)?Bit_SET:Bit_RESET);
}

void LCD_SendCommand(unsigned char command)
{
	LCD_Send4Bit(command >>4);
	LCD_Enable();
	LCD_Send4Bit(command);
	LCD_Enable();
        delayus(50);
}

void LCD_Clear()
{
 	LCD_SendCommand(0x01);  
        delayms(2);	
}

void LCD_Init()
{
        GPIO_Config();
        
  	GPIO_WriteBit(Port_RS,Pin_RS,Bit_RESET);
        delayms(20);
	LCD_Send4Bit(0x03);
        LCD_Enable();
        delayms(2);
	LCD_Send4Bit(0x03);
        LCD_Enable();
        delayms(2);	
	LCD_Send4Bit(0x03);
        LCD_Enable();
        delayms(2);
        LCD_Send4Bit(0x02);
        LCD_Enable();
        delayms(2);
	LCD_SendCommand(0x28);
	LCD_SendCommand(0x0C);
	LCD_SendCommand(0x06);
	LCD_SendCommand(0x01);
        LCD_SendCommand(0x80);
        delayms(2);
}

void LCD_Gotoxy(unsigned char y, unsigned char x)
{
    unsigned char address;
    if(y==0)
    address=0x80;
    else if(y==1)
    {
        address=0xc0;
    }
    else if(y==2)
    {
        address=0x94;
    }
    else
        address=0xd4;
    address+=x;
    delayus(500);
    LCD_SendCommand(address);
    delayus(50);
}

void LCD_PutChar(unsigned char Data)
{
    GPIO_WriteBit(Port_RS,Pin_RS,Bit_SET);
    LCD_SendCommand(Data);
    GPIO_WriteBit(Port_RS,Pin_RS,Bit_RESET);
}

void LCD_Puts(char *s)
{
   	while (*s){
      	LCD_PutChar(*s);
     	s++;
   	}
}
