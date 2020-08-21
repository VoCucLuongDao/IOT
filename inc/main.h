#ifndef _MAIN_H_
#define _MAIN_H_

#include "Lib_ds18b20.h"
#include "Lib_rtc.h"
#include "tft1_8.h"
#include "esp_01.h"
#include "iwdg.h"
#include "SPI_Config.h"
#include "button.h"
#include "delay.h"
#include "timer_config.h"
#include "adc_config.h"
 uint8_t *time_process(char *timeon, char *timeoff);
 void load_image(int count);
#endif
