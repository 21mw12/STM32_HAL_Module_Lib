#ifndef KEY_KEY_H_
#define KEY_KEY_H_

///////////////////////////////////////////////////////////
//
// 文件功能：按键的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/06
//
///////////////////////////////////////////////////////////

#include "main.h"
#include "stm32f1xx_hal.h"

typedef enum {
	KeyState_NoPush = 0,	// 按键未被按下
	KeyState_Push			// 按键被按下
} KeyState;

/**
  * @brief 获得按键的状态
  * @return 按键状态
  */
KeyState KEY_GetState(void);

#endif /* KEY_KEY_H_ */
