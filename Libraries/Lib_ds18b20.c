#include "Lib_ds18b20.h"
#include "stdio.h"
void GPIO_Pin_Input()
{
  GPIO_DeInit(GPIOD);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void GPIO_Pin_Output()
{
  GPIO_DeInit(GPIOD);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
// GPIOD Configuration
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);  // pull the pin LOW
}

uint8_t ds18b20_init (void)
{
    GPIO_Pin_Output();   // set the pin as output
    GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);  // pull the pin LOW
    delayus(480);   // delay according to datasheet
    GPIO_Pin_Input();    // set the pin as input
    delayus(80);
    if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))    // if the pin is low i.e the presence pulse is there
    {
        delayus (400); // wait for 400 us
     //    printf("Khoi tao hoan tat \n");
        return 0;
    }
    else
    {
        delayus (400);  // wait for 400 us
       //  printf("Khoi tao loi \n");
        return 1;
    }
}

void write_ds18b20 (uint8_t data)
{
    GPIO_Pin_Output ();   // set as output
    for (int i=0; i<8; i++)
    {
        if (data >> i & 0x01)  // if the bit is high
        {
            // write 1
            GPIO_Pin_Output ();  // set as output
            GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);  // pull the pin LOW
            delayus (1);  // wait for  us
            GPIO_Pin_Input();  // set as input
            delayus (60);  // wait for 60 us
        }
        else  // if the bit is low
        {
            // write 0
            GPIO_Pin_Output ();
            GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);  // pull the pin LOW
            delayus (50);  // wait for 60 us
            GPIO_Pin_Input ();
            delayus (10);
        }
    }
}

uint8_t read_ds18b20 (void)
{
	uint8_t value=0;
	GPIO_Pin_Input();
	for (int i=0;i<8;i++)
	{
		GPIO_Pin_Output();   // set as output

		GPIO_WriteBit (GPIOD, GPIO_Pin_0, Bit_RESET);  // pull the data pin LOW
		delayus (5);  // wait for 5 us
		GPIO_Pin_Input ();  // set as input
		if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delayus (55);  // wait for 60 us
	}
	return value;
}


float get_temperature(){   
    uint16_t temp=0;
    float temperature=0;
    uint8_t  temp_l=0, temp_h=0;
  
    ds18b20_init(); 
    write_ds18b20(0xCC);
    write_ds18b20(0x44);
    delayms(100);    
    
    ds18b20_init();
    write_ds18b20(0xCC);
    write_ds18b20(0xBE);
   
    temp_l = read_ds18b20();
    temp_h = read_ds18b20();
    temp = (temp_h<<8)|temp_l;
    temperature = (float)temp/16;
    return temperature;
}