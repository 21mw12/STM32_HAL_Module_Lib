#ifndef __CIRCLE_BUFFER_H
#define __CIRCLE_BUFFER_H

///////////////////////////////////////////////////////////
//
// 文件功能：环形缓冲区的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/02/22
//
///////////////////////////////////////////////////////////

#include "stm32f4xx_hal.h"

/* 环形缓冲区中的数据类型 */
#define CBuf_Type		uint16_t

/* 环形缓冲区结构体 */
typedef struct {
	uint32_t pRead;
	uint32_t pWrite;
	uint32_t len;
	CBuf_Type* buf;	
} sCircleBuffer;

/**
  * @brief 环形缓冲区初始化
  * @param pCBuf 环形缓冲区结构体
  * @param Len 缓冲区大小
  * @param Buf 缓冲区地址
  * @return 无
  */
void CircleBuffer_Init(sCircleBuffer* pCBuf, uint32_t Len, CBuf_Type* Buf);

/**
  * @brief 环形缓冲区读数据
  * @param pCBuf 环形缓冲区结构体
  * @param Val 读出的值
  * @return 1 为操作成功
	* 				0 为操作失败
  */
uint8_t CircleBuffer_Read(sCircleBuffer* pCBuf, CBuf_Type* Val);

/**
  * @brief 环形缓冲区写数据
  * @param pCBuf 环形缓冲区结构体
  * @param Val 写入的值
  * @return 1 为操作成功
	* 				0 为操作失败
  */
uint8_t CircleBuffer_Write(sCircleBuffer* pCBuf, CBuf_Type Val);

#endif
