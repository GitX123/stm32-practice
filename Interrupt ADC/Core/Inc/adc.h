#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f4xx.h"

#define SR_EOC (1U << 1)

void pa1_adc_interrupt_init();
void start_conversion();

#endif
