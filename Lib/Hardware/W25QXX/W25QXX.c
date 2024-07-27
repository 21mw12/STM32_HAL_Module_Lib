#include "W25QXX.h"
#include "W25QXX_Register.h"
#include "spi.h"

/* SPI片选 */
#define W25QXX_CS_Enable()		HAL_GPIO_WritePin(W25QXX_CS_GPIO_Port, W25QXX_CS_Pin, GPIO_PIN_RESET)		// 起始信号
#define W25QXX_CS_Disable()		HAL_GPIO_WritePin(W25QXX_CS_GPIO_Port, W25QXX_CS_Pin, GPIO_PIN_SET)			// 结束信号

static volatile uint8_t SPI_TX_Complete = 0;
static volatile uint8_t SPI_RX_Complete = 0;
static volatile uint8_t SPI_TXRX_Complete = 0;

/* 回调函数 */
void HAL_SPI_TxCpltCallBack(SPI_HandleTypeDef *hspi) {
	if (hspi == &hspi1) {
		SPI_TX_Complete = 1;
	}
}
void HAL_SPI_RxCpltCallBack(SPI_HandleTypeDef *hspi) {
	if (hspi == &hspi1) {
		SPI_RX_Complete = 1;
	}
}
void HAL_SPI_TxRxCpltCallBack(SPI_HandleTypeDef *hspi) {
	if (hspi == &hspi1) {
		SPI_TXRX_Complete = 1;
	}
}

/* 等待事件结束函数 */
void SPI_WaitTxCplt() {
	uint32_t Timeout = W25QXX_Timeout;
	while (0 == SPI_TX_Complete && Timeout--) HAL_Delay(1);
	SPI_TX_Complete = 0;
}
void SPI_WaitRxCplt() {
	uint32_t Timeout = W25QXX_Timeout;
	while (0 == SPI_RX_Complete && Timeout--) HAL_Delay(1);
	SPI_RX_Complete = 0;
}
void SPI_WaitTxRxCplt() {
	uint32_t Timeout = W25QXX_Timeout;
	while (0 == SPI_TXRX_Complete && Timeout--) HAL_Delay(1);
	SPI_TXRX_Complete = 0;
}

/**
  * @brief W25QXX写使能
  * @return 无
  */
void W25QXX_WriteEnable(void) {
	uint8_t buf[1] = {W25QXX_WRITE_ENABLE};
	
	W25QXX_CS_Enable();
	
	HAL_SPI_Transmit_IT(&hspi1, buf, 1);
	SPI_WaitTxCplt();
	
	W25QXX_CS_Disable();
}

/**
  * @brief W25QXX写失能
  * @return 无
  */
void W25QXX_WriteDisable(void) {
	uint8_t buf[1] = {W25QXX_WRITE_DISABLE};
	
	W25QXX_CS_Enable();
	
	HAL_SPI_Transmit_IT(&hspi1, buf, 1);
	SPI_WaitTxCplt();
	
	W25QXX_CS_Disable();
}

/**
  * @brief 等待芯片空闲
  * @return 无
  */
void W25QXX_WaitBusy(void) {
	uint8_t txbuf[2] = {W25QXX_READ_STATUS_REGISTER_1, W25QXX_DUMMY_BYTE};
	uint8_t rxbuf[2];
	
	HAL_Delay(500);
	W25QXX_CS_Enable();
	
	HAL_SPI_TransmitReceive_IT(&hspi1, txbuf, rxbuf, 2);
	SPI_WaitTxRxCplt();
	
	while(0x01 == (rxbuf[1] & 0x01));
	
	W25QXX_CS_Disable();
}

void W25QXX_ReadID(uint8_t* MID, uint16_t* DID) {
	uint8_t txbuf[4] = {W25QXX_JEDEC_ID, W25QXX_DUMMY_BYTE, W25QXX_DUMMY_BYTE, W25QXX_DUMMY_BYTE};
	uint8_t rxbuf[4];
	
	W25QXX_CS_Enable();
	
	HAL_SPI_TransmitReceive_IT(&hspi1, txbuf, rxbuf, 4);
	SPI_WaitTxRxCplt();
	
	*MID = rxbuf[1];
	*DID = rxbuf[2];
	*DID <<= 8;
	*DID |= rxbuf[3];
	
	W25QXX_CS_Disable();
}

void W25QXX_RelieveWriteProtect(void) {
	uint8_t txbuf[3] = {W25QXX_WRITE_STATUS_REGISTER, 0x00, 0x00};
	
  W25QXX_WriteEnable();

	W25QXX_CS_Enable();
	
	HAL_SPI_Transmit_IT(&hspi1, txbuf, 3);
	SPI_WaitTxCplt();
	
	W25QXX_CS_Disable();
	
	W25QXX_WaitBusy();
}

void W25QXX_WritePage(uint32_t address, uint8_t* dataArray, uint16_t count) {
	uint8_t txbuf[4] = {W25QXX_PAGE_PROGRAM};
	txbuf[1] = (address >> 16) & 0xFF;
	txbuf[2] = (address >> 8) & 0xFF;
	txbuf[3] = address & 0xFF;
	
	W25QXX_WriteEnable();
	
	W25QXX_CS_Enable();
	
	HAL_SPI_Transmit_IT(&hspi1, txbuf, 4);		// 发送命令和地址
	SPI_WaitTxCplt();
	HAL_SPI_Transmit_IT(&hspi1, dataArray, count);	// 发送数据
	SPI_WaitTxCplt();
	
	W25QXX_CS_Disable();
	
	W25QXX_WaitBusy();
}

void W25QXX_ReadPage(uint32_t address, uint8_t* dataArray, uint32_t count) {
	uint8_t txbuf[4] = {W25QXX_READ_DATA};
	txbuf[1] = (address >> 16) & 0xFF;
	txbuf[2] = (address >> 8) & 0xFF;
	txbuf[3] = address & 0xFF;
	
	W25QXX_CS_Enable();
	
	HAL_SPI_Transmit_IT(&hspi1, txbuf, 4);		// 发送命令和地址
	SPI_WaitTxCplt();
	HAL_SPI_Receive_IT(&hspi1, dataArray, count);	// 接收数据
	SPI_WaitRxCplt();
	
	W25QXX_CS_Disable();	// 结束信号
}

void W25QXX_SectorErase(uint32_t address) {
	uint8_t txbuf[4] = {W25QXX_SECTOR_ERASE_4KB};
	txbuf[1] = (address >> 16) & 0xFF;
	txbuf[2] = (address >> 8) & 0xFF;
	txbuf[3] = address & 0xFF;
	
	W25QXX_WriteEnable();
	
	W25QXX_CS_Enable();
	
	HAL_SPI_Transmit_IT(&hspi1, txbuf, 4);
	SPI_WaitTxCplt();
	
	W25QXX_CS_Disable();
	
	W25QXX_WaitBusy();
}

void W25QXX_BlockErase(uint32_t address) {
	uint8_t txbuf[4] = {W25QXX_BLOCK_ERASE_64KB};
	txbuf[1] = (address >> 16) & 0xFF;
	txbuf[2] = (address >> 8) & 0xFF;
	txbuf[3] = address & 0xFF;
	
	W25QXX_WriteEnable();
	
	W25QXX_CS_Enable();
	
	HAL_SPI_Transmit_IT(&hspi1, txbuf, 4);
	SPI_WaitTxCplt();
	
	W25QXX_CS_Disable();
	
	W25QXX_WaitBusy();
}
