#ifndef __TIME_DELAY_H
#define __TIME_DELAY_H
#include "stm32f10x.h"
#include "misc.h"
void initTime(u8 SYSCLK);

void delay_ms(uint16_t ms);

void delay_us(uint16_t us);

#endif