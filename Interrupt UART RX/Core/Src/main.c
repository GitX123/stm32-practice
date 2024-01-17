#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN (1U << 0)
#define GPIOA_5 (1U << 5)
#define LED_PIN GPIOA_5

char key;
static void uart_callback();

int main() {
	// enable output LED pin
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	uart2_rx_interrupt_init();

	while (1) {

	}

	return 0;
}

static void uart_callback() {
	key = USART2->DR;
	if (key == '1') {
		GPIOA->ODR |= LED_PIN;
	} else {
		GPIOA->ODR &= ~LED_PIN;
	}
}

void USART2_IRQHandler() {
	// check if RX buffer is not empty
	if (USART2->SR & SR_RXNE) {
		uart_callback();
	}
}
