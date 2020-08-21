#ifndef _SPI_CONFIG_H_
#define _SPI_CONFIG_H_

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_dma.h"
#include "misc.h"
#include "delay.h"
#include "stdio.h"
 
#define buffsize 15
  void SPI1_Config();
  void SPI2_Config();
  void SS_L();
  void SS_H();
#endif