#include "stm32f4xx.h"
#include "timer.h"

#define GPIOAEN 	(1U << 0)
#define AFR5_TIM2_CH1 	(1U << 20)

#define TIM2EN			(1U << 0)
#define OC1M_TOGGLE 	((1U << 4) | (1U << 5)) // output compare 1 mode toggle (011)
#define CCER_CC1E 		(1U << 0) //
#define CR1_CEN			(1U << 0)

void tim2_pa5_output_compare() {
	/* Configure GPIO */
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set PA5 mode to alternate function (10)
	GPIOA->MODER &= ~(1U << 10);
	GPIOA->MODER |= (1U << 11);

	// set alternate function type to TIM2_CH1 (AF01)
	GPIOA->AFR[0] |= AFR5_TIM2_CH1;

	/* Configure TIM2 */
	// enable clock access to TIM2
	RCC->APB1ENR |= TIM2EN;

	// set prescaler value
	TIM2->PSC = 16000 - 1;
	// set auto-reload value
	TIM2->ARR = 1000 - 1;
	// set output compare toggle mode
	TIM2->CCMR1 = OC1M_TOGGLE;
	// clear counter
	TIM2->CNT = 0;

	// enable TIM2 CH1 output
	TIM2->CCER |= CCER_CC1E;
	// enable timer
	TIM2->CR1 = CR1_CEN;
}
