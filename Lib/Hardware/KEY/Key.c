#include "Key.h"

KeyState KEY_GetState(void){
	if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET) {
		HAL_Delay(20);
		while (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET);
		HAL_Delay(20);
		return KeyState_Push;
	}
	return KeyState_NoPush;
}
