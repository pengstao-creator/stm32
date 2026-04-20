#ifndef _H_SMG
#define _H_SMG
#include "system.h"
#define LSA PBout(5)
#define LSB PBout(4)
#define LSC PBout(3)
#define LS_PIN  GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5
#define SMG_PIN GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
#define CODE_SIZE 17

extern const u8 gsmg_code[CODE_SIZE];

void smgInit();

void showNum(u8 num);

void setPos(int pos);

#endif
