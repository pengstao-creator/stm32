#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "timeDelay.h"
#include "system.h"
#define LED PCout(13)
int main()
{
	
		//设置时钟,开启GPIOC
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
			
		//设置输出模式
		GPIO_InitTypeDef init_gpioc;
		init_gpioc.GPIO_Mode = GPIO_Mode_Out_PP;
		init_gpioc.GPIO_Pin = GPIO_Pin_13;
		init_gpioc.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOC,&init_gpioc);
		
		LED=1;
		
		initTime(72);
    while (1)
    {
			
			delay_ms(3000);
			LED=!LED;
			//设置输出端口,将GPIOC_pin_13设置为低电平
			//GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			//delay_ms(1000);
			//GPIO_SetBits(GPIOC,GPIO_Pin_13);
			//delay_ms(1000);
    }
}
