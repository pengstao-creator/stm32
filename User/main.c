#include "stm32f10x.h"
#include "usart.h"
int main()
{
  usartInit(115200);
  u16 len;
  while (1)
  {
      if(RECV_DATA_END)
      {
        len = GET_DATA_INDEX;
        for(u16 i = 0;i < len;i++)
        {
          while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
          USART_SendData(USART1,data[i]);
        }
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1,'e');
        CLEAN_CONTROL_FLAG;
      }
  }
}
