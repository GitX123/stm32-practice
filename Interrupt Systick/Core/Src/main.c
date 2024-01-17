#include "stm32f4xx.h"
#include "systick.h"

#define GPIOAEN (1U << 0)
#define PIN5 	(1U << 5)
#define LED_PIN PIN5

static void systick_callback();

int main() {
	// enable GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set input mode on PIN5
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	systick_1hz_interrupt();

	while (1) {

	}

	return 0;
}

static void systick_callback() {
	GPIOA->ODR ^= LED_PIN;
}

void SysTick_Handler() {
	systick_callback();
}
