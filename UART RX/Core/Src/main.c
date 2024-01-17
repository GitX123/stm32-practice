#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN (1U << 0)
#define GPIOA_5 (1U << 5)
#define LED_PIN GPIOA_5

char ch;

int main() {
	// enable output LED pin
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	uart2_rx_init();

	while (1) {
		ch = uart2_read();
		if (ch == '1') {
			GPIOA->ODR |= LED_PIN;
		} else {
			GPIOA->ODR &= ~LED_PIN;
		}
	}

	return 0;
}
