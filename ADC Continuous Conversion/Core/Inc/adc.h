#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdint.h>
#include "stm32f4xx.h"

void pa1_adc_init();
void start_conversion();
uint32_t adc_read();

#endif
