#include "stm32f4xx.h"
#include "timer.h"

#define GPIOAEN (1U << 0)
#define PIN5 	(1U << 5)
#define LED_PIN PIN5

int main() {
	// enable GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set input mode on PIN5
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	tim2_1hz_init();

	while (1) {
		// wait for update interrupt
		while (!(TIM2->SR & SR_UIF));
		// clear UIF
		TIM2->SR &= ~SR_UIF;

		// toggle LED pin
		GPIOA->ODR ^= LED_PIN;
	}

	return 0;
}
