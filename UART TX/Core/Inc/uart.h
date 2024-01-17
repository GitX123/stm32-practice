#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void uart2_tx_init();
void uart2_write(int ch);

#endif
