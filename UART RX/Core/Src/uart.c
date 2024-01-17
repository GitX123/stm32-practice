#include "uart.h"

#define GPIOAEN (1U << 0)
#define UART2EN (1U << 17)

#define CR1_RE 	(1U << 2) // receiver enable
#define CR1_UE 	(1U << 13) // UART enable
#define SR_RXNE	(1U << 5)

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {
	return (PeriphClk + (BaudRate / 2U)) / BaudRate;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate) {
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

void uart2_rx_init() {
	/* configure GPIO pin */
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set PA3 mode to alternate function (10)
	GPIOA->MODER &= ~(1U << 6);
	GPIOA->MODER |= (1U << 7);

	// set PA3 alternate function type to UART_TX (AF07 0111)
	GPIOA->AFR[0] |= (1U << 12);
	GPIOA->AFR[0] |= (1U << 13);
	GPIOA->AFR[0] |= (1U << 14);
	GPIOA->AFR[0] &= ~(1U << 15);

	/* configure UART module */
	// enable clock access to UART2
	RCC->APB1ENR |= UART2EN;

	// configure baud rate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure transfer direction
	USART2->CR1 = CR1_RE;

	// enable UART module
	USART2->CR1 |= CR1_UE;
}

char uart2_read() {
	// make sure receive data register is not empty
	while (!(USART2->SR & SR_RXNE));

	return USART2->DR;
}
