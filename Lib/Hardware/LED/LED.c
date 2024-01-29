#include "LED.h"

void LED_ON(void) {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}

void LED_OFF(void) {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}

void LED_Turn(void) {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, !HAL_GPIO_ReadPin(LED_GPIO_Port, LED_Pin));
}

void LED_Flash(uint32_t Delay) {
	LED_Turn();
	HAL_Delay(Delay);
}
