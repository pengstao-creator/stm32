#include "buzz.h"
#include "stm32f10x_gpio.h"

void buzzInit()
{
    timeInit(72);
    //设置时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef initDef;
    initDef.GPIO_Mode = GPIO_Mode_Out_PP;
    initDef.GPIO_Pin = BUZZ_PIN;
    initDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&initDef);
}

void vibFreqCtrl(u8 t,u8 us)
{
    while(t--)
    {
        BUZZ=!BUZZ;
        delay_us(us);
    }
}