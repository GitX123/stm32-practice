#include "adc.h"

#define GPIOAEN (1U << 0)

#define ADC1EN 				(1U << 8)
// CR
#define CR1_EOCIE 			(1U << 5)
#define CR2_ADON			(1U << 0)
#define CR2_CONT			(1U << 1)
#define CR2_SWSTART			(1U << 30)
// SQR
#define ADC_CH1 			(1U << 0)
#define ADC_SEQ_LENGTH_1	0x00

void pa1_adc_interrupt_init() {
	/* configure GPIO */
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set mode of PA1 to analog (11)
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 3);

	/* configure ADC module */
	// enable clock access to ADC module
	RCC->APB2ENR |= ADC1EN;

	// enable ADC end-of-conversion interrupt
	ADC1->CR1 |= CR1_EOCIE;

	// enable ADC interrupt in NVIC
	NVIC_EnableIRQ(ADC_IRQn);

	// conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	// conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LENGTH_1;

	// enable ADC module
	ADC1->CR2 |= CR2_ADON;
}

void start_conversion() {
	// enable continuous conversion
	ADC1->CR2 |= CR2_CONT;

	// start conversion
	ADC1->CR2 |= CR2_SWSTART;
}
