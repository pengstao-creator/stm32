#ifndef __usart_H
#define __usart_H
#include "system.h"
#include "stm32f10x_usart.h"
#define RECV_BYTE_SIZE 200
extern u8 data[RECV_BYTE_SIZE];
extern u16 CONTROL_FLAG;

#define GET_END_FLAG_R(X) ((X)&(0x0400))
#define GET_END_FLAG_N(X) ((X)&(0x8000))
#define GET_DATA_INDEX ((CONTROL_FLAG)&(0x03FF))
#define SET_END_FLAG_R ((CONTROL_FLAG)|=0x0400)
#define SET_END_FLAG_N ((CONTROL_FLAG)|=0x8000)
#define SET_DATA_INDEX_ADD1 (++CONTROL_FLAG)
#define CLEAN_CONTROL_FLAG (CONTROL_FLAG = 0)
#define RECV_DATA_END ((GET_END_FLAG_R(CONTROL_FLAG)&&(GET_END_FLAG_N(CONTROL_FLAG))))

void usartInit(u32 BaudRate);


#endif
