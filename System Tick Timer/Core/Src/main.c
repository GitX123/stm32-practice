#include "stm32f4xx.h"
#include "systick.h"

#define GPIOAEN (1U << 0)
#define PIN5 	(1U << 5)
#define LED_PIN PIN5

int main() {
	// enable GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set input mode on PIN5
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while (1) {
		// toggle LED pin
		GPIOA->ODR ^= LED_PIN;
		systickDelayMs(1000);
	}

	return 0;
}
