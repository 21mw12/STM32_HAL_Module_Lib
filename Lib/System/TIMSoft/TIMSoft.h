#ifndef __TIM_SOFT_H
#define __TIM_SOFT_H

#include "stm32f4xx_hal.h"

/* 软件定时器结构体 */
typedef struct {
	uint32_t timeout;			// 超时时间
	void* args;						// 传入参数
	void (*func)(void*);	// 超时函数
} sTimerSoft;

/**
  * @brief 设置超时时间
  * @param pTimer 软件定时器结构体
  * @param Timeout 超时时间
  * @return 无
  */
void TIMSoft_SetTimeOut(sTimerSoft* pTimer, uint32_t Timeout);

/**
  * @brief 检查是否超时
  * @param pTimer 软件定时器结构体
  * @return 无
  */
void TIMSoft_Check(sTimerSoft pTimer);

/**
  * @brief 清除超时时间
  * @param pTimer 软件定时器结构体
  * @return 无
  */
void TIMSoft_Clear(sTimerSoft* pTimer);

#endif
