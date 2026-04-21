#include "stm32f10x.h"
#include "exti.h"
int main()
{
  extiInit();
  // uint16_t brightness = 0;
  // uint8_t direction = 1;
  while (1)
  {
    // if (direction)
    // {
    //   brightness++;
    //   if (brightness >= 1000)
    //     direction = 0;
    // }
    // else
    // {
    //   brightness--;
    //   if (brightness == 0)
    //     direction = 1;
    // }
    // TIM_SetCompare2(TIM3, brightness);
    // delay_ms(2);
  }
}
