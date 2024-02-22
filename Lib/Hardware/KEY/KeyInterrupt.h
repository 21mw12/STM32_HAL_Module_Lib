#ifndef KEY_KEY_H_
#define KEY_KEY_H_

///////////////////////////////////////////////////////////
//
// 文件功能：按键的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/02/22
//
// 端口配置：中断触发，上拉电阻
//
// 注：要在stm32f4xx_it.c中的SysTick_Handler()函数中
//		 在SysTick_IRQn 1代码段中添加如下代码
//				extern sTimerSoft key_Timer;
// 				TIMSoft_Check(key_Timer);
//		 并在函数上导入TIMSoft.h文件
//
///////////////////////////////////////////////////////////

#include "main.h"
#include "stm32f4xx_hal.h"
#include "TIMSoft.h"

/* 是否开启按键缓冲区 */
#define KEY_BUFFER					ENABLE
/* 设置按键消抖时长 */
#define KEY_JITTER_DELAY		20
/* 按键消抖定时器结构体 */
extern sTimerSoft key_Timer;

#if KEY_BUFFER == ENABLE
#include "CircleBuffer.h"

/* 设置按键缓冲区大小 */
#define KEY_BUFFER_SIZE			100

/**
  * @brief 初始化带缓冲区的按键
  * @return 无
  */
void Key_Init(void);

/**
  * @brief 检查按键
  * @return 缓冲区中的数据（默认是按下按键的端口值）
  */
uint8_t Key_Check(void);

#endif

#endif
