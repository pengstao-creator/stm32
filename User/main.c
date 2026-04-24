#include "stm32f10x.h"
#include "buzz.h"

int main()
{
  buzzInit();
  
  while (1)
  {
    playTestMelody();
    delay_ms(1000);
  }
}
