#include "KeyInterrupt.h"

void Key_HandleFunc(void* atgs);

sTimerSoft key_Timer = {UINT32_MAX, NULL, Key_HandleFunc};

#if KEY_BUFFER == ENABLE
static uint16_t buf[KEY_BUFFER_SIZE];
static sCircleBuffer key_CBufs;

void Key_Init(void) {
	CircleBuffer_Init(&key_CBufs, KEY_BUFFER_SIZE, buf);
}

uint8_t Key_Check(void) {
	uint16_t result = 0;
	if (CircleBuffer_Read(&key_CBufs, &result)) {
		return result;
	}
	return 0;
}

#endif

void Key_HandleFunc(void* atgs) {
#if KEY_BUFFER == ENABLE
	CircleBuffer_Write(&key_CBufs, KEY1_Pin);	// �򻺳�����д�밴���Ķ˿�
#else
	/* ���밴��������� */
	
#endif
	
	TIMSoft_Clear(&key_Timer);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == KEY1_Pin) {
		TIMSoft_SetTimeOut(&key_Timer, KEY_JITTER_DELAY);
	}
}
