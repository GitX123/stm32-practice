#include "uart.h"

#define GPIOAEN (1U << 0)
#define UART2EN (1U << 17)

#define CR1_TE 	(1U << 3) // Transmitter enable
#define CR1_UE 	(1U << 13) // UART enable
#define SR_TXE	(1U << 7)

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {
	return (PeriphClk + (BaudRate / 2U)) / BaudRate;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate) {
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

// override printf's internal function
int __io_putchar(int ch) {
	uart2_write(ch);
	return ch;
}

void uart2_tx_init() {
	/* configure GPIO pin */
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set PA2 mode to alternate function (10)
	GPIOA->MODER &= (1U << 4);
	GPIOA->MODER |= (1U << 5);

	// set alternate function type to UART_TX (AF07 0111)
	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	/* configure UART module */
	// enable clock access to UART2
	RCC->APB1ENR |= UART2EN;

	// configure baud rate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure transfer direction
	USART2->CR1 = CR1_TE;

	// enable UART module
	USART2->CR1 |= CR1_UE;
}

void uart2_write(int ch) {
	// make sure transmit data register is empty
	while (!(USART2->SR & SR_TXE));

	USART2->DR = (ch & 0xFF); // 1 byte
}
