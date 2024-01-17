#include <stdint.h>

#define PERIPHERAL_BASE (0x40000000UL)
#define AHB1_OFFSET 	(0x00020000UL)
#define AHB1_BASE 		(PERIPHERAL_BASE + AHB1_OFFSET)

// reset and clock control
typedef struct {
	volatile uint32_t SKIP[12];
	volatile uint32_t AHB1EN;
} RCC_TypeDef;
#define RCC_OFFSET 	(0x3800UL)
#define RCC_BASE 	(AHB1_BASE + RCC_OFFSET)
#define RCC	((RCC_TypeDef*) RCC_BASE)

// general purpose IO
typedef struct {
	volatile uint32_t MODE;
	volatile uint32_t SKIP[4];
	volatile uint32_t OD;
} GPIO_TypeDef;
#define GPIOA_OFFSET 	(0x0000UL)
#define GPIOA_BASE 		(AHB1_BASE + GPIOA_OFFSET)
#define GPIOA 			((GPIO_TypeDef*) GPIOA_BASE)

#define GPIOAEN (1U << 0)
#define PIN5 (1U << 5)
#define LED_PIN PIN5

int main(void)
{
	// enable clock
	RCC->AHB1EN |= GPIOAEN;

	// set output mode
	GPIOA->MODE |= (1U << 10);
	GPIOA->MODE &= ~(1U << 11);

    while (1) {
    	// toggle output value
    	GPIOA->OD ^= LED_PIN;
    	for (int i = 0; i < 1000000; i++);
    }

    return 0;
}
