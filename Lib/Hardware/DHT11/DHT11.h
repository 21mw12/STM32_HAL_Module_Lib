#ifndef DHT11_DHT11_H
#define DHT11_DHT11_H

///////////////////////////////////////////////////////////
//
// 文件功能：DHT11温湿度传感器模块的功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/29
//
///////////////////////////////////////////////////////////

#include "stm32f1xx_hal.h"
#include "main.h"

/**
  * @brief 温湿传感器初始化
  * @return 初始化状态		0：失败 
	* 										1：成功
  */
uint8_t DHT11_Init(void);

/**
  * @brief 读取一次数据
  * @param temp 温度值 范围:0°~50°
  * @param humi 湿度值 范围:20%~90%
  * @return 数据接收状态		0：失败 
	* 											1：正常
  */
uint8_t DHT11_ReadData(uint8_t *Temp, uint8_t *Hum);

#endif
