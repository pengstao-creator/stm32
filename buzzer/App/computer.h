#ifndef _H_COMPUTER
#define _H_COMPUTER
#include "system.h"
#include "smg.h"
#include "timeDelay.h"
#define NUM_NULL CODE_SIZE
#define MAX_NUM  99999999
void computerInit();
int toInt(u8 * arry);  
void add();
void sub();
void mul();
void div();

void showResult();
void showArryA();
void showArryB();
void showArry(u8 * arry);
void showError();

void setReArry(u8 * ary,u8 * arry);
void setReArryA(u8 * ary);
void setReArryB(u8 * ary);
void setArryA(u32 num);
void setArryB(u32 num);
void setArry(u8 * arry,u32 num);
void setError();

void clearArryAll(u8 * arry);
void clearArryCnt(u8 * arry,u8 count);
void clearAll();

u8 getArrySize(u8 * arry);
#endif
