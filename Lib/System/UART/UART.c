#include "UART.h"
#include "usart.h"

uint8_t ch;
uint8_t ch_r;

// 重定向printf()函数到串口
int fputc(int c, FILE * f) {
	ch = c;
	HAL_UART_Transmit(&huart1, &ch, 1, UART_PRINTF_TIMEOUT);
	return c;
}

// 重定向scanf()函数到串口
int fgetc(FILE * F) {
	HAL_UART_Receive(&huart1, &ch_r, 1, UART_PRINTF_TIMEOUT);
	return ch_r;
}

#if UART_TX_DMA == ENABLE
#define UART_Transmit			HAL_UART_Transmit_DMA
#else
#define UART_Transmit			HAL_UART_Transmit_IT
#endif
#if UART_RX_DMA == ENABLE
#define UART_Receive			HAL_UARTEx_ReceiveToIdle_DMA
#else
#define UART_Receive			HAL_UARTEx_ReceiveToIdle_IT
#endif

uint8_t UART1_RxData[USART1_DataPackage_Length];

void UART_Init(void) {
	UART_Receive(&huart1, UART1_RxData, USART1_DataPackage_Length);
}

void UART1_SendData(uint8_t* Data, uint16_t Size) {
	UART_Transmit(&huart1, Data, Size);
}

/**
  * @brief UART中断回调函数（所有串口都会触发该中断）
  * @param huart 中断串口
  * @param Size 数据量
  * @return 无
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	
	if(huart == &huart1) {
		
		/* 插入串口处理代码 */
//		UART_Transmit(&huart1, UART1_RxData, Size);

		UART_Receive(&huart1, UART1_RxData, USART1_DataPackage_Length);
	}
}
