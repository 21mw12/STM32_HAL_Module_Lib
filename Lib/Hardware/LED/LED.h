#ifndef LED_LED_H_
#define LED_LED_H_

///////////////////////////////////////////////////////////
//
// 文件功能：LED的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/06
//
// 端口配置：输出模式，上拉电阻
//
///////////////////////////////////////////////////////////

#include "main.h"
#include "stm32f4xx_hal.h"

/**
  * @brief LED点亮
  * @return 无
  */
void LED_ON(void);

/**
  * @brief LED熄灭
  * @return 无
  */
void LED_OFF(void);

/**
  * @brief LED状态反转
  * @return 无
  */
void LED_Turn(void);

/**
  * @brief LED闪烁
  * @param Delay 闪烁间隔
  * @return 无
  */
void LED_Flash(uint32_t Delay);

#endif /* LED_LED_H_ */
