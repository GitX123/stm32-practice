#include <stdint.h>
#include "stm32f4xx.h"
#include "exti.h"

#define GPIOAEN (1U << 0)
#define PIN5 	(1U << 5)
#define LED_PIN PIN5

static void exti_callback();

int main(void)
{
	// enable GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set input mode on PIN5
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	pc13_exti_init();

	while (1) {

	}
}

static void exti_callback() {
	GPIOA->ODR ^= LED_PIN;
}

void EXTI15_10_IRQHandler() {
	if (EXTI->PR & EXTI_PR_PR13) {
		// clear PR flag (rc_w1)
		EXTI->PR |= EXTI_PR_PR13;
		exti_callback();
	}
}
