#include "adc.h"

#define GPIOAEN (1U << 0)
#define ADC1EN	(1U << 8)

#define ADC_CH1 		(1U << 0)	// sequence channel (1 - 0X00)
#define ADC_SEQ_LEN 	(0x00)		// sequence length (1 - 0x00)
#define CR2_ADON 		(1U << 0) 	// ADC on
#define CR2_SWSTART		(1U << 30) 	// software start
#define SR_EOC 			(1U << 1) 	// end of conversion

void pa1_adc_init() {
	/* configure GPIO Pin */
	// enable clock access to GPIO A
	RCC->AHB1ENR |= GPIOAEN;

	// set mode of PA1 to analog
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 3);

	/* configure ADC module */
	// enable clock access to ADC
	RCC->APB2ENR |= ADC1EN;

	// conversion sequence order
	ADC1->SQR3 = ADC_CH1;

	// conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN;

	// enable ADC module
	ADC1->CR2 |= CR2_ADON;
}

void start_conversion() {
	// software start ADC conversion
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read() {
	// wait for conversion to complete
	while (!(ADC1->SR & SR_EOC));

	return ADC1->DR;
}
