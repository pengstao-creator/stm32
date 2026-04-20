#include "matrixKey.h"

u16 matrixPinH[4] = {MATRIX_PIN_H1,MATRIX_PIN_H2,MATRIX_PIN_H3,MATRIX_PIN_H4};
u16 matrixPinL[4] = {MATRIX_PIN_L1,MATRIX_PIN_L2,MATRIX_PIN_L3,MATRIX_PIN_L4};
void matrixInit()
{
    timeInit(72);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    GPIO_InitTypeDef initDef;
    initDef.GPIO_Mode = GPIO_Mode_Out_PP;
    initDef.GPIO_Pin = MATRIX_PIN_H;
    initDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&initDef);
    initDef.GPIO_Mode = GPIO_Mode_IPU;
    initDef.GPIO_Pin = MATRIX_PIN_L;
    GPIO_Init(GPIOB,&initDef);
    // 初始化行为低电平，未扫描时不导通
    GPIO_Write(GPIOB, (GPIO_ReadOutputData(GPIOB) & 0x00FF));
}

u8 monitorH(u8 row)
{
    GPIO_Write(GPIOB, (GPIO_ReadOutputData(GPIOB) & 0x00FF));
    GPIO_Write(GPIOB, (GPIO_ReadOutputData(GPIOB) | matrixPinH[row]));
    delay_us(5);
    for(u8 i = 0;i < 4;i++)
    {
        if(GPIO_ReadInputDataBit(GPIOB,matrixPinL[i]) == 1)
        {
            // 消抖二次确认
            delay_ms(10);
            if(GPIO_ReadInputDataBit(GPIOB,matrixPinL[i]) != 1)
            {
                continue;
            }
            // 等待按键释放
            while(GPIO_ReadInputDataBit(GPIOB,matrixPinL[i]))
            {
                delay_ms(1);
            }
            return i;
        }
    }
    
    return NOT_P;
}

u8 getPos(u8 row,u8 col)
{
    return row * 4 + col;
}

u8 monitorMbutton()
{
    for(u8 i = 0;i < 4;i++)
    {
        u8 col = monitorH(i);
        if(col != NOT_P)
        {
            return getPos(i,col);
        }
    }
    return NOT_P;
}
