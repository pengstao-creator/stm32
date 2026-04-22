#include "adc.h"

void acdInit()
{
    ADC_InitTypeDef adcDef;
    
    ADC_Init(ADC1,&adcDef);
}