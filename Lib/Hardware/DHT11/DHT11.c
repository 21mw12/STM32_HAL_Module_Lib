#include "DHT11.h"
#include "Delay.h"

/**
  * @brief 将端口变为输出
  * @return 无
  */
void DHT11_IO_OUT (void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_DA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief 将端口变为输出
  * @return 无
  */
void DHT11_IO_IN (void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_DA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief DHT11端口复位，发出起始信号
  * @return 无
  */
void DHT11_RST (void){
	DHT11_IO_OUT();
	
	HAL_GPIO_WritePin(GPIOB, DHT11_DA_Pin, GPIO_PIN_RESET);
	HAL_Delay(20); 	// 拉低至少18ms
	HAL_GPIO_WritePin(GPIOB, DHT11_DA_Pin, GPIO_PIN_SET);
	Delay_us(30); 	// 主机拉高20~40us
}

/**
  * @brief 等待DHT11回应
  * @return 检测状态			1：未检测到DHT11
	* 										0：成功检测到DHT11
  */
uint8_t DHT11_Check(void){
	uint8_t timeout = 0;
	
	DHT11_IO_IN();
	
	while (HAL_GPIO_ReadPin(GPIOB, DHT11_DA_Pin) && (timeout <100)){		// DHT11会拉低40~80us
			timeout++;
			Delay_us(1);
	}
	if(timeout >= 100) {
		return 1;
	}
	
	timeout = 0;	
	while (!HAL_GPIO_ReadPin(GPIOB, DHT11_DA_Pin) && (timeout <100)){		// DHT11拉低后会再次拉高40~80us
			timeout++;
			Delay_us(1);
	}
	if(timeout >= 100) {
		return 1;
	}
	return 0;
}

/**
  * @brief 从DHT11读取一位数据
  * @return 数据1或0
  */
uint8_t DHT11_ReadBit(void) {
	uint8_t timeout = 0;
	
	while(HAL_GPIO_ReadPin(GPIOB, DHT11_DA_Pin) && (timeout < 100)) {		// 等待变为低电平
			timeout++;
			Delay_us(1);
	}
	timeout=0;
	while(!HAL_GPIO_ReadPin(GPIOB, DHT11_DA_Pin) && (timeout < 100)){		// 等待变高电平
			timeout++;
			Delay_us(1);
	}
	Delay_us(40);	//等待40us
	
	return HAL_GPIO_ReadPin(GPIOB,DHT11_DA_Pin);
}


/**
  * @brief 从DHT11读取一字节数据
  * @return 读到的数据
  */
uint8_t DHT11_ReadByte(void) {
	uint8_t data = 0;
	for (uint8_t i = 0; i < 8; i++){
			data <<= 1;
			data |= DHT11_ReadBit();
	}
	return data;
}

uint8_t DHT11_Init(void){
	HAL_Delay(500);	// 等待器件稳定
	DHT11_RST();
	HAL_Delay(1500);	// 等待器件初始化完成
	
	return !DHT11_Check();
}

uint8_t DHT11_ReadData(uint8_t *Temp, uint8_t *Hum){
	uint8_t buf[5];
	
	DHT11_RST();//DHT11端口复位，发出起始信号
	
	if(DHT11_Check() == 0){ //等待DHT11回应
		
		for(uint8_t i = 0; i < 5; i++){
				buf[i] = DHT11_ReadByte();
		}
		/* 数据校验 */
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]){
				*Hum = buf[0];
				*Temp = buf[2];
		}
	} else {
		return 0;
	}
	return 1;
}

