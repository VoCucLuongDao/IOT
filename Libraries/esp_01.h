#ifndef ESP_01_H_
#define ESP_01_H_
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "uart_config.h"
#include "delay.h"

void esp_01_init(void);
void esp_01_transmit(char *str);
void clear_Buff();
int chek_connect();
#endif
