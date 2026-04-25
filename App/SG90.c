#include "SG90.h"


void SG90Init()
{
    //20ms周期
    pwmInit(36000 - 1,40 -1);
}

void angleControl(u8 ang)
{
    if(ang > 180) ang = 180;
    u16 ccr = 900 + (u16)ang * 20;   // 零点偏移 900，每度 20
    TIM_SetCompare1(TIM1, ccr);
}