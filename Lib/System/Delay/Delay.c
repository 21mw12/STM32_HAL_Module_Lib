#include "Delay.h"

void Delay_us(uint32_t us) {
	uint32_t time = (HAL_RCC_GetHCLKFreq() / 8000000 * us);

	while (time--);
}
