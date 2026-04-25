#include "pwm.h"

void pwmInit(u16 per,u16 psc)
{
    RCC_APB2PeriphClockCmd(PWM_GPIO_CLK | RCC_APB2Periph_TIM1, ENABLE);
    //初始化GPIO
    GPIO_InitTypeDef gpioDef;
    gpioDef.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioDef.GPIO_Pin = PWM_PIN;
    gpioDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PWM_GPIO_PORT, &gpioDef);

    //初始化pwm
    TIM_TimeBaseInitTypeDef timDef;
    timDef.TIM_Period = per;//寄存器从0开始计数
    timDef.TIM_Prescaler = psc;
    timDef.TIM_ClockDivision = TIM_CKD_DIV1;
    timDef.TIM_CounterMode = TIM_CounterMode_Up;
    timDef.TIM_RepetitionCounter = 0;//降低更新中断频率
    TIM_TimeBaseInit(TIM1,&timDef);

    //初始化通道
    TIM_OCInitTypeDef ocDef;
    ocDef.TIM_OCMode = TIM_OCMode_PWM1;
    ocDef.TIM_OCPolarity = TIM_OCPolarity_High;
    ocDef.TIM_OutputState = TIM_OutputState_Enable;
    ocDef.TIM_OutputNState = TIM_OutputState_Disable;
    ocDef.TIM_OCIdleState = TIM_OCIdleState_Reset;
    ocDef.TIM_Pulse = per / 2;
    TIM_OC1Init(TIM1,&ocDef); 

    TIM_OC1PolarityConfig(TIM1, TIM_OCPolarity_High);
    TIM_ARRPreloadConfig(TIM1,ENABLE);

    TIM_Cmd(TIM1,ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
