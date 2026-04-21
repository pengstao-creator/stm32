#include "smg.h"
#include "stm32f10x_gpio.h"

const u8 gsmg_code[CODE_SIZE]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
            0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};


void smgInit()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    GPIO_InitTypeDef initDef;
    initDef.GPIO_Mode = GPIO_Mode_Out_PP;
    initDef.GPIO_Pin = SMG_PIN;
    initDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&initDef);
    initDef.GPIO_Pin = LS_PIN;
    GPIO_Init(GPIOB,&initDef);

    // GPIO_Write(GPIOA, (GPIO_ReadOutputData(GPIOA) | 0x00FF));
    // GPIO_Write(GPIOB, (GPIO_ReadOutputData(GPIOB) | 0x0038));
}

void showNum(u8 num)
{
    GPIO_Write(GPIOA, (GPIO_ReadOutputData(GPIOA) & 0xFF00) | num);
    // for(int i  = 0;i < 8;i++)
    // {
    //     if((num >> i)&(0x01))
    //     {
    //         GPIO_WriteBit(GPIOA,(GPIO_Pin_0 << i),1);
    //     }
    //     else
    //     {
    //         GPIO_WriteBit(GPIOA,(GPIO_Pin_0 << i),0);
    //     }
    // }
}

void setPos(int pos)
{
    switch (pos)
    {
    case 1:LSA = 0;LSB = 0;LSC = 0;break;
    case 2:LSA = 1;LSB = 0;LSC = 0;break;
    case 3:LSA = 0;LSB = 1;LSC = 0;break;
    case 4:LSA = 1;LSB = 1;LSC = 0;break;
    case 5:LSA = 0;LSB = 0;LSC = 1;break;
    case 6:LSA = 1;LSB = 0;LSC = 1;break;
    case 7:LSA = 0;LSB = 1;LSC = 1;break;
    case 8:LSA = 1;LSB = 1;LSC = 1;break;
    default:break;
    }
}
