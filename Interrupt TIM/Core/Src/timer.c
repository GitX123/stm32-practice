#include "timer.h"

#define TIM2EN (1U << 0)

#define CR1_CEN 	(1U << 0)
#define DIER_UIE 	(1U << 0) // update interrupt enable

void tim2_1hz_interrupt_init() {
	// enable clock access to TIM2
	RCC->APB1ENR |= TIM2EN;

	// set prescaler value
	TIM2->PSC = 16000 - 1;
	// set auto-reload value
	TIM2->ARR = 1000 - 1;
	// clear counter
	TIM2->CNT = 0;

	// enable TIM2 counter
	TIM2->CR1 = CR1_CEN;

	// enable TIM2 interrupt
	TIM2->DIER |= DIER_UIE;

	// enable TIM2 interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}
