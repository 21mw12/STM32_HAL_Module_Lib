#ifndef __UART_H
#define __UART_H

///////////////////////////////////////////////////////////
//
// 文件功能：UART的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/02/23
//
// 注：已重写printf()函数
//     具体功能实现在.c文件中的回调函数内改写
//
///////////////////////////////////////////////////////////

#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

/* USART相关配置 */
#define UART_TX_DMA										DISABLE
#define UART_RX_DMA										DISABLE
#define UART_PRINTF_TIMEOUT						1000
#define USART1_DataPackage_Length			10

extern uint8_t UART1_RxData[USART1_DataPackage_Length];

/**
  * @brief 串口初始化
  * @return 无
  */
void UART_Init(void);

/**
  * @brief 串口1发送数据
  * @param Data 要发送的数据
  * @param Size 要发送的数据长度
  * @return 无
  */
void UART1_SendData(uint8_t* Data, uint16_t Size);

#endif
