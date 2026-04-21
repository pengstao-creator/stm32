#include "exti.h"
#define LED PAout(7)
#define ADD_NUM 50
int16_t brightness = 0;
u8 open = 0;
void extiInit()
{   
    timeInit(72);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,INDEPENDENT_BUTTON_PIN);
    NVIC_InitTypeDef nvicDef;
    nvicDef.NVIC_IRQChannel = EXTI15_10_IRQn;
    nvicDef.NVIC_IRQChannelCmd = ENABLE;
    nvicDef.NVIC_IRQChannelPreemptionPriority = 2;
    nvicDef.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&nvicDef);
    EXTI_InitTypeDef extiDef;
    extiDef.EXTI_Line = INDEPENDENT_BUTTON_PIN;
    extiDef.EXTI_LineCmd = ENABLE;
    extiDef.EXTI_Mode = EXTI_Mode_Interrupt;
    extiDef.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&extiDef);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
    GPIO_InitTypeDef gpioDef;
    gpioDef.GPIO_Pin = GPIO_Pin_7;
    gpioDef.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&gpioDef);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    TIM_DeInit(TIM3);  // 复位所有寄存器到默认值
    TIM_TimeBaseInitTypeDef timDef;
    timDef.TIM_CounterMode = TIM_CounterMode_Up;
    timDef.TIM_ClockDivision = TIM_CKD_DIV1;
    timDef.TIM_Period = 999;
    timDef.TIM_Prescaler = 71;
    TIM_TimeBaseInit(TIM3,&timDef);
    //配置PWM通道
    TIM_OCInitTypeDef ocDef;
    ocDef.TIM_OCMode      = TIM_OCMode_PWM1;          // PWM 模式 1
    ocDef.TIM_OutputState = TIM_OutputState_Enable;   // 输出使能
    ocDef.TIM_Pulse       = 1000;                      // 初始占空比（比较值）
    ocDef.TIM_OCPolarity  = TIM_OCPolarity_High;      // 输出极性
    TIM_OC2Init(TIM3,&ocDef);
    TIM_Cmd(TIM3,ENABLE);
}


void EXTI15_10_IRQHandler()
{

    if(EXTI_GetITStatus(EXTI_Line12) == SET)
    {
        //控制开关
        open = !open;
        if(open)
        {
            brightness = 1;
        }
        else
        {
            brightness = 1000;
        }
        TIM_SetCompare2(TIM3,brightness);
    }
    else if(EXTI_GetITStatus(EXTI_Line13) == SET)
    {
        //增加亮度
        brightness-=ADD_NUM;
        if(brightness < 0)brightness = 1;
    }
    else if(EXTI_GetITStatus(EXTI_Line14) == SET)
    {
        
    }
    else if(EXTI_GetITStatus(EXTI_Line15) == SET)
    {
        brightness+=ADD_NUM;
        if(brightness > 1000)brightness = 1000;
    }
    if(open)TIM_SetCompare2(TIM3,brightness);
    EXTI_ClearITPendingBit(EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15);
}

