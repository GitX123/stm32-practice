#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f4xx.h"

#define SR_UIF (1U << 0)

void tim2_1hz_interrupt_init();

#endif
