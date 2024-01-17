#include "stm32f4xx.h"
#include "timer.h"

#define GPIOAEN (1U << 0)
#define PIN5 	(1U << 5)
#define LED_PIN PIN5

static void tim2_callback();

int main() {
	// enable GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set PA5 to output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	tim2_1hz_interrupt_init();

	while (1) {

	}

	return 0;
}

static void tim2_callback() {
	GPIOA->ODR ^= LED_PIN;
}

void TIM2_IRQHandler() {
	// clear update interrupt flag
	TIM2->SR &= ~SR_UIF;

	tim2_callback();
}
