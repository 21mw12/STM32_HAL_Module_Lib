#ifndef BUZZER_BUZZER_H_
#define BUZZER_BUZZER_H_

///////////////////////////////////////////////////////////
//
// 文件功能：无源蜂鸣器的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/06
//
///////////////////////////////////////////////////////////

#include "main.h"
#include "stm32f1xx_hal.h"

/**
  * @brief 蜂鸣器响
  * @param soundCircle 声音周期
  * @param soundLength 声音长度
  * @return 无
  */
void Buzzer_Loud(uint16_t soundCircle, uint16_t soundLength);

#endif /* BUZZER_BUZZER_H_ */
