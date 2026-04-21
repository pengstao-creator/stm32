#include "stm32f10x.h"
#include "buzz.h"
// #include "bindKey.h"
#include "exti.h"
int main()
{
	buzzInit();
  // bindKeyInit();
  extiInit();
  while (1)
  {
    // u8 num = monitorMbutton();
    // if(num != NOT_P)
    // {
    //   bindKey(num);
    //   // vibFreqCtrl(250,100);
    // }
    show();
  }
}
