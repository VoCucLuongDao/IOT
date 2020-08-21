#ifndef _LIB_DS18B20_H_
#define _LIB_DS18B20_H_
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"

void GPIO_Pin_Output();
void GPIO_Pin_Input();
uint8_t ds18b20_init (void);
uint8_t read_ds18b20 (void);
void write_ds18b20 (uint8_t data);
float get_temperature();

#endif