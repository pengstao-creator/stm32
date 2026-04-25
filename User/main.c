#include "stm32f10x.h"
#include "SG90.h"
#include "timeDelay.h"
int main()
{
  SG90Init();
  timeInit(72);
  while (1)
  {
      for(int i = 0;i < 181;i++)
      {
        angleControl(i * 11);
        delay_ms(500);
      } 
  }
}

