#ifndef UART_USART_H_
#define UART_USART_H_

///////////////////////////////////////////////////////////
//
// 文件功能：LED的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/06
//
// 注：已重写printf()函数
//     具体功能实现在.c文件中的回调函数内改写
//
///////////////////////////////////////////////////////////

#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>

/* USART数据包相关配置 */
#define USART1_DataPackage_Length		10
#define USART2_DataPackage_Length		10
#define USART3_DataPackage_Length		10

/**
  * @brief 串口初始化
  * @return 无
  */
void USART_Init(void);

#endif /* UART_USART_H_ */
