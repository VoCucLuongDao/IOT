/**********Giao tiep stm32f407 vs tft 1.8 inch*********************************/
// SPI2_SCK - PB13 vs tft _SCL //
// SPI2_MOSI- PB15 vs tft _SDA //
// SPI2_PB10       vs tft_RST  //
// SPI2_PB111       vs tft_D/C  // D la write Data // C la write command
// SPI2_CS_ PB12   vs tft CS   //
/*****************************************************************************/

#include "tft1_8.h"
#include "font5x7.h"

void LCD_config() // cau hinh chan cho LCD
{
      SPI2_Config();
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
      GPIO_Init(GPIOB,&GPIO_InitStructure);
      RST_H;
      RS_WD;
      SS_H();
      LCD_Init();
      
}

void LCD_WR_CMD2(u16 regval)  // write lenh command 16 bit
{ 
	
         SS_L();  //LCD_CS=0
         RS_WC;
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         
         SPI_I2S_SendData(SPI2,regval>>8);
         while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         
         SPI_I2S_SendData(SPI2,regval);
         while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         SS_H();	   		 
}

void LCD_WR_CMD(u8 regval) //write command 8 bit
{        
         SS_L();  //LCD_CS=0
         RS_WC;
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         SPI_I2S_SendData(SPI2,regval);
         while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);
         SS_H();
}

void LCD_WR_DATA2(u16 data)
{        
 	 SS_L();  //LCD_CS=0
         RS_WD;
         
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         
         SPI_I2S_SendData(SPI2,data>>8&0xff);
         while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         
         SPI_I2S_SendData(SPI2,data&0xff);
         while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         SS_H();		
}
void LCD_WR_DATA(u8 data)
{       	
         SS_L();  //LCD_C
         RS_WD;
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         SPI_I2S_SendData(SPI2,data&0xff);
         while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
         while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
         SPI_I2S_ClearFlag(SPI2,SPI_I2S_FLAG_TXE);
         SS_H();	
}
void LCD_WR_CMD_DATA(u8 LCD_Reg, u8 LCD_RegValue)
{
	LCD_WR_CMD(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}
	
void LCD_Init(void)
{ 	 	
        SS_H();
	RST_H;		 
 	delayms(50); // delay 20 ms 
   	RST_L;		 
 	delayms(50); // delay 20 ms 
        RST_H;	//LCD_RST=0
	delayms(50); // delay 20 ms 
        
	LCD_WR_CMD(0x11); //Sleep out
	delayms(250); //Delay least 120ms
  
//------------------------------------ST7735S Frame Rate-----------------------------------------//
	LCD_WR_CMD(0xB1);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
        
	LCD_WR_CMD(0xB2);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
        
	LCD_WR_CMD(0xB3);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	//------------------------------------End ST7735S Frame Rate-----------------------------------------//
	LCD_WR_CMD(0xB4); //Dot inversion
	LCD_WR_DATA(0x07);
        
	LCD_WR_CMD(0xC0);
	LCD_WR_DATA(0xA2);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x84);
        
	LCD_WR_CMD(0xC1);
	LCD_WR_DATA(0xC5);
        
	LCD_WR_CMD(0xC2);
	LCD_WR_DATA(0xA0);
	LCD_WR_DATA(0x00);
        
	LCD_WR_CMD(0xC3);
	LCD_WR_DATA(0x8A);
	LCD_WR_DATA(0x2A);
	LCD_WR_CMD(0xC4);
	LCD_WR_DATA(0x8A);
	LCD_WR_DATA(0xEE);
	//---------------------------------End ST7735S Power Sequence-------------------------------------//
	LCD_WR_CMD(0xC5); //VCOM
	LCD_WR_DATA(0x0E);
	LCD_WR_CMD(0x36); //MX, MY, RGB mode
	//LCD_WR_DATA(0x00);    // Normal: Top to Bottom; Left to Right; RGB
        //LCD_WR_DATA(0x80);  // Y-Mirror: Bottom to top; Left to Right; RGB
        //LCD_WR_DATA(0x40);  // X-Mirror: Top to Bottom; Right to Left; RGB
        LCD_WR_DATA(0xc0);  // X-Mirror,Y-Mirror: Bottom to top; Right to left; RGB
        //LCD_WR_DATA(0x20);  // X-Y Exchange: X and Y changed positions
        //LCD_WR_DATA(0xA0);  // X-Y Exchange,Y-Mirror
        //LCD_WR_DATA(0x60);  // X-Y Exchange,X-Mirror
        //LCD_WR_DATA(0xE0);  // X-Y Exchange,X-Mirror,Y-Mirror
	//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
	LCD_WR_CMD(0xE0);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x1A);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x2F);
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x20);
	LCD_WR_DATA(0x22);
	LCD_WR_DATA(0x1F);
	LCD_WR_DATA(0x1B);
	LCD_WR_DATA(0x23);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x07);
        LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x10);
        
	LCD_WR_CMD(0xE1);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x1B);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x33);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x29);
	LCD_WR_DATA(0x2e);
	LCD_WR_DATA(0x30);
	LCD_WR_DATA(0x30);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x3f);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x10);
        
        LCD_WR_CMD(0x2a);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x7f);

	LCD_WR_CMD(0x2b);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x9f);
	
	LCD_WR_CMD(0xF0); //Enable test command  
	LCD_WR_DATA(0x01); 
	LCD_WR_CMD(0xF6); //Disable ram power save mode 
	LCD_WR_DATA(0x00); 
	//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
	LCD_WR_CMD(0x3A); //65k mode
	LCD_WR_DATA(0x05);
	LCD_WR_CMD(0x29); //Display on
	LCD_Clear(WHITE);
}

void LCD_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end) // cho vung de hien thi
{		
	LCD_WR_CMD(0x2a);         // set adress of x
	LCD_WR_DATA2(x_start);  //bat dau tu cot x_start
	LCD_WR_DATA2(x_end);    //ket thuc o cot x_end+2

	LCD_WR_CMD(0x2b);         // set adress of y
	LCD_WR_DATA2(y_start);   //bat dau tu dong y_start+3
	LCD_WR_DATA2(y_end);     //ket thuc o cot y_end+3
	
	LCD_WR_CMD(0x2c);               //send command for tft/lcd

}

void LCD_Clear(u16 color)
{
         LCD_SetRegion(0,0,128-1,160-1);
         for(u16 i=0;i<128*160;i++){
              LCD_WR_DATA2(color);
         }
}  
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{  
        LCD_SetRegion(sx,sy,ex,ey);
 	for(u8 i=0;i<(ey-sy+3);i++)
	{
 	    for(u8 j=0;j<ex-sx+3;j++)
	      {
 		LCD_WR_DATA2(color);
	      }
	}	  
} 
void LCD_Pixel(uint16_t X, uint16_t Y, uint16_t color) {
	LCD_SetRegion(X,Y,X,Y);
	LCD_WR_DATA2(color);
}
uint16_t LCD_Color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void LCD_PutChar(uint16_t X, uint16_t Y, char chr, uint16_t color,uint16_t bgcolor) {
  //char duoc hien thi o toa do (X,Y) voi mau color va mau nen bgcolor//
	uint16_t i,j;
	uint8_t buffer[5];
	memcpy(buffer,&Font5x7[(chr - 32) * 5],5);

	LCD_SetRegion(X,Y,X + 5 - 1,Y + 7 -1);
	for (j = 0; j < 7; j++) {
		for (i = 0; i < 5; i++) {
			if ((buffer[i] >> j) & 0x01) LCD_WR_DATA2(color);
		        else  LCD_WR_DATA2(bgcolor);
		}
	}
}

void LCD_PutStr(uint8_t X, uint8_t Y, char *str, uint16_t color,uint16_t bg_color) {
	while (*str) {
		LCD_PutChar(X,Y,*str++,color,bg_color);
		if (X < 128 - (5-1)) { X += 5 + 1; } else if (Y < 160 - 7 + 1) {Y += 7 + 1; } else { X = 0; Y = 0; }
	};
}