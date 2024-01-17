#include "stm32f4xx.h"
#include "timer.h"

#define GPIOAEN 		(1U << 0)
#define AFR5_TIM2_CH1 	(1U << 20)
#define AFR6_TIM3_CH1	(1U << 25)

#define TIM2EN			(1U << 0)
#define TIM3EN 			(1U << 1)
#define OC1M_TOGGLE 	((1U << 4) | (1U << 5)) // output compare 1 mode toggle (011)
#define CC1S_TI1		(1U << 0)
#define CCER_CC1NP		(1U << 3)
#define CCER_CC1P		(1U << 1)
#define CCER_CC1E 		(1U << 0)
#define CR1_CEN			(1U << 0)

void tim2_1hz_pa5_output_compare() {
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

	// enable TIM2 CH1
	TIM2->CCER |= CCER_CC1E;
	// enable timer
	TIM2->CR1 = CR1_CEN;
}

void tim3_pa6_input_capture() {
	/* Configure GPIO */
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set PA6 mode to alternate function (10)
	GPIOA->MODER &= ~(1U << 12);
	GPIOA->MODER |= (1U << 13);

	// set alternate function type to TIM3_CH1 (AF02)
	GPIOA->AFR[0] |= AFR6_TIM3_CH1;

	/* Configure TIM3 */
	// enable clock access to TIM3
	RCC->APB1ENR |= TIM3EN;

	// set prescaler value
	TIM3->PSC = 16000 - 1;
	// set ch1 to input capture mode
	TIM3->CCMR1 = CC1S_TI1;

	// enable TIM3 CH1 (detect both edges)
	TIM3->CCER |= CCER_CC1NP | CCER_CC1P | CCER_CC1E;
	// enable timer
	TIM3->CR1 = CR1_CEN;
}
