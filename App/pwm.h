#ifndef __PWM_H
#define __PWM_H

#include "system.h"
#define PWM_PIN GPIO_Pin_8
#define PWM_GPIO_PORT GPIOA
#define PWM_GPIO_CLK RCC_APB2Periph_GPIOA
void pwmInit(u16 per,u16 psc);

#endif
