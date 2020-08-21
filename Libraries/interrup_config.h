#ifndef _INTERRUP_CONFIG_H_
#define _INTERRUP_CONFIG_H_

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stm32f4xx_it.h"

void Led_Config();
void ExitLine7_Config();
void EXTILine0_Config(void);
#endif