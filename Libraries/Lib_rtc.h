#ifndef _LIB_RTC_H_
#define _LIB_RTC_H_
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_exti.h"
#include "stdio.h"
#include "button.h"

void Config_RTC();
void TimeShow(void);
void DateShow(void);
void AlarmShow();
void RTC_Settime(uint8_t yyyy, uint8_t mm, uint8_t dd, uint8_t wd, uint8_t h, uint8_t m, uint8_t s);
void setAlarm(u8 wd, u8 h , u8 m, u8 s);

#endif