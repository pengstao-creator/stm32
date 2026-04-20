#include "key.h"


void keyInit()
{   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef initDef;
    initDef.GPIO_Mode = GPIO_Mode_IPU;
    initDef.GPIO_Pin = INDEPENDENT_BUTTON_PIN;
    initDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&initDef);
}

int monitorKButton()
{
    int flag = 1;
    if(flag&&KEY1 == 0)
    {
        flag = 0;
        return 1;
    }
    if(flag&&KEY2 == 0)
    {
        flag = 0;
        return 2;
    }
    if(flag&&KEY3 == 0)
    {
        flag = 0;
        return 3;
    }
    if(flag&&KEY4 == 0)
    {
        flag = 0;
        return 4;
    }
    return -1;
}
