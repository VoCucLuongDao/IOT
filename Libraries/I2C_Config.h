#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#include "misc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stdint.h"
#include "delay.h"
#define Slave_Address 0x68
#define BufferSIZE 3

#define I2C_SPEED 100000
#define I2C_DUTYCYCLE I2C_DutyCycle_2

void I2C_Config();
void I2cByteWrite(u8 addr, u8 data);
u8 I2cByteRead(u8 nAddr);
#endif