#ifndef _H_BUZZ
#define _H_BUZZ
#include "timeDelay.h"
#include "system.h"
#define BUZZ PBout(0)
#define BUZZ_PIN GPIO_Pin_0
void buzzInit();
void vibFreqCtrl(u16 t,u16 us);
void musicPlay(u8 scale);
void playTestMelody(void);

#endif
