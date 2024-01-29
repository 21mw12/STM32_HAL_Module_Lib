#ifndef RELAY_RELAY_H_
#define RELAY_RELAY_H_

///////////////////////////////////////////////////////////
//
// 文件功能：继电器的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/06
//
///////////////////////////////////////////////////////////

#include "main.h"
#include "stm32f1xx_hal.h"

/**
  * @brief 继电器吸合
  * @return 无
  */
void Relay_Close(void);

/**
  * @brief 继电器释放
  * @return 无
  */
void Relay_Release(void);

/**
  * @brief 继电器状态反转
  * @return 无
  */
void Relay_Turn(void);

#endif /* RELAY_RELAY_H_ */
