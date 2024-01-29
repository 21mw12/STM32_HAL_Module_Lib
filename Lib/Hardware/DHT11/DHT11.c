#include "DHT11.h"
#include "Delay.h"

/**
  * @brief ���˿ڱ�Ϊ���
  * @return ��
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
  * @brief ���˿ڱ�Ϊ���
  * @return ��
  */
void DHT11_IO_IN (void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_DA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief DHT11�˿ڸ�λ��������ʼ�ź�
  * @return ��
  */
void DHT11_RST (void){
	DHT11_IO_OUT();
	
	HAL_GPIO_WritePin(GPIOB, DHT11_DA_Pin, GPIO_PIN_RESET);
	HAL_Delay(20); 	// ��������18ms
	HAL_GPIO_WritePin(GPIOB, DHT11_DA_Pin, GPIO_PIN_SET);
	Delay_us(30); 	// ��������20~40us
}

/**
  * @brief �ȴ�DHT11��Ӧ
  * @return ���״̬			1��δ��⵽DHT11
	* 										0���ɹ���⵽DHT11
  */
uint8_t DHT11_Check(void){
	uint8_t timeout = 0;
	
	DHT11_IO_IN();
	
	while (HAL_GPIO_ReadPin(GPIOB, DHT11_DA_Pin) && (timeout <100)){		// DHT11������40~80us
			timeout++;
			Delay_us(1);
	}
	if(timeout >= 100) {
		return 1;
	}
	
	timeout = 0;	
	while (!HAL_GPIO_ReadPin(GPIOB, DHT11_DA_Pin) && (timeout <100)){		// DHT11���ͺ���ٴ�����40~80us
			timeout++;
			Delay_us(1);
	}
	if(timeout >= 100) {
		return 1;
	}
	return 0;
}

/**
  * @brief ��DHT11��ȡһλ����
  * @return ����1��0
  */
uint8_t DHT11_ReadBit(void) {
	uint8_t timeout = 0;
	
	while(HAL_GPIO_ReadPin(GPIOB, DHT11_DA_Pin) && (timeout < 100)) {		// �ȴ���Ϊ�͵�ƽ
			timeout++;
			Delay_us(1);
	}
	timeout=0;
	while(!HAL_GPIO_ReadPin(GPIOB, DHT11_DA_Pin) && (timeout < 100)){		// �ȴ���ߵ�ƽ
			timeout++;
			Delay_us(1);
	}
	Delay_us(40);	//�ȴ�40us
	
	return HAL_GPIO_ReadPin(GPIOB,DHT11_DA_Pin);
}


/**
  * @brief ��DHT11��ȡһ�ֽ�����
  * @return ����������
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
	HAL_Delay(500);	// �ȴ������ȶ�
	DHT11_RST();
	HAL_Delay(1500);	// �ȴ�������ʼ�����
	
	return !DHT11_Check();
}

uint8_t DHT11_ReadData(uint8_t *Temp, uint8_t *Hum){
	uint8_t buf[5];
	
	DHT11_RST();//DHT11�˿ڸ�λ��������ʼ�ź�
	
	if(DHT11_Check() == 0){ //�ȴ�DHT11��Ӧ
		
		for(uint8_t i = 0; i < 5; i++){
				buf[i] = DHT11_ReadByte();
		}
		/* ����У�� */
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]){
				*Hum = buf[0];
				*Temp = buf[2];
		}
	} else {
		return 0;
	}
	return 1;
}

