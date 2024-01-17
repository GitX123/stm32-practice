#include "exti.h"

#define GPIOCEN 	(1U << 2)
#define SYSCFGEN 	(1U << 14)

void pc13_exti_init() {
	// disable global interrupts
	__disable_irq();

	/* configure GPIO */
	// enable clock access to GPIOC
	RCC->AHB1ENR |= GPIOCEN;

	// set PC13 as input
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

	/* configure EXTI */
	// enable clock access to SYSCFG
	RCC->APB2ENR |= SYSCFGEN;

	// select Port C for EXTI13
	SYSCFG->EXTICR[3] |= (1U << 5); // EXTI14 (0010)

	// un-mask EXTI13
	EXTI->IMR |= (1U << 13);

	// enable falling edge trigger on EXTI13
	EXTI->FTSR |= (1U << 13);

	// enable EXTI13 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// enable global interrupts
	__enable_irq();
}
