#ifndef _H_MATRIX_KEY
#define _H_MATRIX_KEY
#include "system.h"
#include "timeDelay.h"
#define MATRIX_PIN_H1 GPIO_Pin_8
#define MATRIX_PIN_H2 GPIO_Pin_9
#define MATRIX_PIN_H3 GPIO_Pin_10
#define MATRIX_PIN_H4 GPIO_Pin_11
#define MATRIX_PIN_H  (MATRIX_PIN_H1 | MATRIX_PIN_H2 | MATRIX_PIN_H3 | MATRIX_PIN_H4)
#define MATRIX_PIN_L1 GPIO_Pin_12
#define MATRIX_PIN_L2 GPIO_Pin_13
#define MATRIX_PIN_L3 GPIO_Pin_14
#define MATRIX_PIN_L4 GPIO_Pin_15
#define MATRIX_PIN_L (MATRIX_PIN_L1 | MATRIX_PIN_L2 | MATRIX_PIN_L3 | MATRIX_PIN_L4)
#define NOT_P 16 //表示没有按键按下
void matrixInit();

u8 monitorMbutton();

#endif