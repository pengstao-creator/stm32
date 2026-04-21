#ifndef _H_BUZZ
#define _H_BUZZ
#include "timeDelay.h"
#include "system.h"
#define BUZZ PBout(0)
#define BUZZ_PIN GPIO_Pin_0
void buzzInit();
void vibFreqCtrl(u8 t,u8 us);

#endif
