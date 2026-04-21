#include "exti.h"


void extiInit()
{
    bindKeyInit();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   
    NVIC_InitTypeDef nvicDef;
    nvicDef.NVIC_IRQChannel = EXTI15_10_IRQn;
    nvicDef.NVIC_IRQChannelCmd = ENABLE;
    nvicDef.NVIC_IRQChannelPreemptionPriority = 2;
    nvicDef.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&nvicDef);
    EXTI_InitTypeDef extiDef;
    extiDef.EXTI_Line = MATRIX_PIN;
    extiDef.EXTI_LineCmd = ENABLE;
    extiDef.EXTI_Mode = EXTI_Mode_Interrupt;
    extiDef.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&extiDef);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,MATRIX_PIN);
}

void run()
{
    int num = monitorMbutton();
    if(num != NOT_P)
    {
        bindKey(num);
    }
}

void EXTI15_10_IRQHandler()
{
    run();
    
}

void EXTI9_5_IRQHandler()
{
    run();
}