#ifndef _H_KEY
#define _H_KEY
#include "system.h"
#define INDEPENDENT_BUTTON_PIN GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12
#define KEY1 PAin(12)
#define KEY2 PAin(13)
#define KEY3 PAin(14)
#define KEY4 PAin(15)
void keyInit();

int monitorButton();

#endif
