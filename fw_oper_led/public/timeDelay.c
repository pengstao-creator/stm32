#include "timeDelay.h"
u8 fac_ms;
u16 fac_us;


void initTime(u8 SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	
	fac_us = SYSCLK/8;
	fac_ms = fac_ms*1000;
}
void delay_ms(uint16_t ms)
{
	while(ms--)
	{
		delay_us(1000);
	}
	 
}

void delay_us(uint16_t us)
{
	SysTick->LOAD = us*fac_us;
	//清空用于记时寄存器
	SysTick->VAL = 0x00;
	//开启控制SYSCLK寄存器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	uint32_t ctrl;
	do
	{
		 ctrl = SysTick->CTRL;
	}while((ctrl & 0x01) &&!(ctrl & SysTick_CTRL_COUNTFLAG_Msk));
	
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0x00;
	
}