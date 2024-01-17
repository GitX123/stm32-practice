#include <stdint.h>
#include "stm32f4xx.h"
#include "adc.h"

static void adc_callback();
uint32_t sensor_value;

int main() {
	pa1_adc_interrupt_init();
	start_conversion();

	while (1) {

	}

	return 0;
}

static void adc_callback() {
	sensor_value = ADC1->DR;
}

void ADC_IRQHandler() {
	// interrupt from EOC
	if((ADC1->SR & SR_EOC)) {
//		ADC1->SR &= ~SR_EOC; // cleared by reading DR
		adc_callback();
	}
}
