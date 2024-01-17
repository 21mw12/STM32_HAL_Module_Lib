#include "Relay.h"

void Relay_Close(void) {
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
}

void Relay_Release(void) {
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
}

void Relay_Turn(void) {
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, !HAL_GPIO_ReadPin(RELAY_GPIO_Port, RELAY_Pin));
}
