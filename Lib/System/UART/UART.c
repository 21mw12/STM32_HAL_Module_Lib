#include "UART.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

uint8_t ch;
uint8_t ch_r;

// 重定向printf()函数到串口
int fputc(int c, FILE * f) {
	ch=c;
	HAL_UART_Transmit(&huart1,&ch,1,1000);
	return c;
}

// 重定向scanf()函数到串口
int fgetc(FILE * F) {
	HAL_UART_Receive (&huart1,&ch_r,1,0xffff);
	return ch_r;
}


uint8_t USART1_RxData[USART1_DataPackage_Length];
uint8_t USART2_RxData[USART2_DataPackage_Length];
uint8_t USART3_RxData[USART3_DataPackage_Length];

void USART_Init(void) {
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, USART1_RxData, USART1_DataPackage_Length);
	HAL_UARTEx_ReceiveToIdle_IT(&huart2, USART2_RxData, USART2_DataPackage_Length);
	HAL_UARTEx_ReceiveToIdle_IT(&huart3, USART3_RxData, USART3_DataPackage_Length);
}

/**
  * @brief UART中断回调函数（所有串口都会触发该中断）
  * @param huart 中断串口
  * @param Size 数据量
  * @return 无
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	
	if(huart == &huart1) {
		
		/* 自定义串口1功能代码 BEGIN */
		HAL_UART_Transmit_IT(&huart1, USART1_RxData, Size);
		/* 自定义串口1功能代码 END */

		HAL_UARTEx_ReceiveToIdle_IT(&huart1, USART1_RxData, USART1_DataPackage_Length);
	}

	if(huart == &huart2) {

		/* 自定义串口2功能代码 BEGIN */
		HAL_UART_Transmit_IT(&huart2, USART2_RxData, Size);
		/* 自定义串口2功能代码 END */

		HAL_UART_Receive_IT(&huart2, USART2_RxData, USART2_DataPackage_Length);
	}
	
	if(huart == &huart3) {

		/* 自定义串口3功能代码 BEGIN */
		HAL_UART_Transmit_IT(&huart3, USART3_RxData, Size);
		/* 自定义串口3功能代码 END */

		HAL_UART_Receive_IT(&huart3, USART3_RxData, USART3_DataPackage_Length);
	}
}
