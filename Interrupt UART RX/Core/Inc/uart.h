#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdint.h>
#include "stm32f4xx.h"
#define SR_RXNE (1U << 5)

void uart2_rx_interrupt_init();

#endif
