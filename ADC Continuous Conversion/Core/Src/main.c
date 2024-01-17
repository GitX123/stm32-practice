#include <stdint.h>
#include "stm32f4xx.h"
#include "adc.h"

uint32_t sensor_value;

int main() {

	pa1_adc_init();
	start_conversion();
	while (1) {
		sensor_value = adc_read();
	}

	return 0;
}
