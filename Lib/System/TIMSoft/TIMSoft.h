#ifndef __TIM_SOFT_H
#define __TIM_SOFT_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ������ʱ��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/02/22
//
///////////////////////////////////////////////////////////

#include "stm32f4xx_hal.h"

/* �����ʱ���ṹ�� */
typedef struct {
	uint32_t timeout;			// ��ʱʱ��
	void* args;						// �������
	void (*func)(void*);	// ��ʱ����
} sTimerSoft;

/**
  * @brief ���ó�ʱʱ��
  * @param pTimer �����ʱ���ṹ��
  * @param Timeout ��ʱʱ��
  * @return ��
  */
void TIMSoft_SetTimeOut(sTimerSoft* pTimer, uint32_t Timeout);

/**
  * @brief ����Ƿ�ʱ
  * @param pTimer �����ʱ���ṹ��
  * @return ��
  */
void TIMSoft_Check(sTimerSoft pTimer);

/**
  * @brief �����ʱʱ��
  * @param pTimer �����ʱ���ṹ��
  * @return ��
  */
void TIMSoft_Clear(sTimerSoft* pTimer);

#endif
