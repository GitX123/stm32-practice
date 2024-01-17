#include "stm32f4xx.h"

#define GPIOAEN (1U << 0)
#define GPIOCEN (1U << 2)

#define PIN5	(1U << 5)
#define PIN13	(1U << 13)

#define LED_PIN PIN5
#define BTN_PIN PIN13

int main() {
	// enable clock access
	RCC->AHB1ENR |= GPIOAEN | GPIOCEN;

	// set PIN5 as output pin
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	// set PIN13 as input pin
	GPIOC->MODER &= ~(1U << 10);
	GPIOC->MODER &= ~(1U << 11);

	while (1) {
		if (GPIOC->IDR & BTN_PIN) {
			GPIOA->BSRR = LED_PIN;
		} else {
			GPIOA->BSRR = (LED_PIN << 16);
		}
	}

	return 0;
}
