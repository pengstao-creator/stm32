#include "stm32f10x.h"

#define LED(n) (1 << (n))
#define SET1(reg, bit) (*(reg) |= LED(bit))
#define SET0(reg, bit) (*(reg) &= ~LED(bit))

int main(void)
{
    // 1. 使能GPIOC时钟（RCC_APB2ENR，位4）
    SET1((uint32_t *)0x40021018, 4);
    
    // 2. 配置GPIOC Pin13为推挽输出，2MHz
    // CRH寄存器地址：GPIOC基址0x40011000 + 0x04
    uint32_t *crh = (uint32_t *)0x40011004;
    *crh &= ~(0xF << 20);        // 清除CNF13[21:20]和MODE13[23:22]
    *crh |=  (0x2 << 22);        // MODE13 = 10 (2MHz)
    // CNF13默认为00（推挽输出）
    
    // 3. 设置Pin13输出低电平
    SET0((uint32_t *)0x4001100C, 13);
    
    while (1);
}
