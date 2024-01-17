#include "Buzzer.h"

void Buzzer_Delay_us(uint32_t us) {
	uint32_t delay = (HAL_RCC_GetHCLKFreq() / 8000000 * us);
	while (delay--);
}

void Buzzer_Loud(uint16_t soundCircle, uint16_t soundLength) {
	for (uint16_t i = 0; i < soundLength; i++) {
	   HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
	   Buzzer_Delay_us(soundCircle);
	   HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
	   Buzzer_Delay_us(soundCircle);
	}
}
