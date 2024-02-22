#include "OLED.h"
#include "OLED_Font.h"
#include "OLED_Instruct.h"
#if isSPIAgreement == 1

#else
#include "i2c.h"
#endif

/* ����OLED�Ĵ�С */
#define OLED_Line				 64
#define OLED_Column			 128

/**
  * @brief OLEDд��һ���ֽ�
  * @param ComType ��������
  * @param Data ����
  * @return ��
  */
void OLED_Write(uint8_t ComType, uint8_t Data) {
#if isSPIAgreement == 1
//	/* ָ������� */
//	if(ComType == OLED_Data) {
//		GPIO_SetBits(GPIOB, OLED_DC_Pin);
//	} else {
//	  GPIO_ResetBits(GPIOB, OLED_DC_Pin);	
//	}

//	/* Ƭѡ���������� */
//	GPIO_ResetBits(GPIOB, OLED_CS_Pin);
//	SPI_Software_SwapByte(Data);
//  GPIO_SetBits(GPIOB, OLED_CS_Pin);
//	
//	GPIO_SetBits(GPIOB, OLED_DC_Pin);
#else
	uint8_t writeBuf[2] = {ComType, Data};
	
	HAL_I2C_Master_Transmit(&hi2c1, (20<<1)|OLED_ADDRESS, writeBuf, 2, 1000);
#endif
}

/**
  * @brief  OLED���ù��λ��
  * @param  Y �����Ͻ�Ϊԭ�㣬���·�������꣬��Χ��0~7
  * @param  X �����Ͻ�Ϊԭ�㣬���ҷ�������꣬��Χ��0~127
  * @retval ��
  */
void OLED_SetCursor(uint8_t X,uint8_t Y) {
	OLED_Write(OLED_Command, 0xB0 | Y);					//����Yλ��
	OLED_Write(OLED_Command, 0x10 | ((X & 0xF0) >> 4));	//����Xλ�õ�4λ
	OLED_Write(OLED_Command, 0x00 | (X & 0x0F));			//����Xλ�ø�4λ
}

/**
  * @brief  �η�����
  * @retval ����a��b�η�
  */
uint32_t Pow(uint32_t a, uint32_t b) {
	uint32_t Result = 1;
	while (b--) {
		Result *= a;
	}
	return Result;
}
			    
void OLED_Init(void) {
#if isSPIAgreement == 1
	RCC_APB2PeriphClockCmd(OLED_Periph, ENABLE);
 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_DC_Pin | OLED_RES_Pin | OLED_CS_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(OLED_Port, &GPIO_InitStructure);

 	GPIO_SetBits(OLED_Port, OLED_DC_Pin | OLED_RES_Pin | OLED_CS_Pin);
	
	HAL_Delay(1000);
	
	GPIO_ResetBits(OLED_Port, OLED_RES_Pin);
	HAL_Delay(200);
  GPIO_SetBits(OLED_Port, OLED_RES_Pin);
#else
	HAL_Delay(1000);
	
	OLED_Write(OLED_Command, Display_OFF);
#endif

	
	/* Ĭ������ */
	OLED_Write(OLED_Command, Set_Display_RefreshRate);
	OLED_Write(OLED_Command, 0xF0);
	OLED_Write(OLED_Command, Set_Display_Multiplexing);
	OLED_Write(OLED_Command, 0x3F);
	OLED_Write(OLED_Command, Set_Display_Skew);			// ������ʾƫ��
	OLED_Write(OLED_Command, 0x00);
	OLED_Write(OLED_Command, Display_Start_Line);		// ������ʾ��ʼ��
	OLED_Write(OLED_Command, Set_Display_ChargingCycle);
	OLED_Write(OLED_Command, 0xF1);
	OLED_Write(OLED_Command, Set_Display_VCOMH);
	OLED_Write(OLED_Command, 0x30);
	OLED_Write(OLED_Command, Set_Display_ChargePump);
	OLED_Write(OLED_Command, 0x14);
	OLED_Write(OLED_Command, Display_VideoMemory_ON);
	
	/* Ĭ������ */
	OLED_Write(OLED_Command, Set_Display_Luminance);	// ��������ֵ����Χ��0x00 ~ 0xFF��
	OLED_Write(OLED_Command, 0x7F);;
	OLED_Write(OLED_Command, Display_Left_Right_Nomal);// ������ʾ��������ģʽ
	OLED_Write(OLED_Command, Display_Up_Down_Nomal);
	OLED_Write(OLED_Command, Display_Color_Nomal);		// ������Ļ�Ƿ�ɫ
	
	/* �����Դ��ַģʽ */
	// 0x00 -	ˮƽ��ַģʽ ("֮"����)
	// 0x01 - ��ֱ��ַģʽ ��"N"�ͣ�
	// 0x02 - ҳ��ַģʽ (����˳������)
	OLED_Write(OLED_Command, Display_SetAddressPattern);
	OLED_Write(OLED_Command, 0x00);
	
	/* ���������� */
	// 0x02 - �ֱ���Ϊ128*32��0.91�磩
	// 0x12 - �ֱ���Ϊ128*64��0.96�磩
	OLED_Write(OLED_Command, Set_Display_ColumnPinConfig);
	OLED_Write(OLED_Command, 0x12);
	
	OLED_Write(OLED_Command, Display_ON);
	
	OLED_Clear();
}
  
void OLED_Clear(void) {  
	uint8_t X, Y;
	for (Y = 0; Y < OLED_Line / 8; Y++) {
		OLED_SetCursor(0, Y);
		for(X = 0; X < OLED_Column; X++) {
			OLED_Write(OLED_Data, 0x00);
		}
	}
}

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char, uint8_t Front_size)  {
	uint8_t i, j;
	uint8_t Y = (Line - 1) * 2;
	uint8_t X = (Column - 1) * 8;
	
	if (Front_size == 8) {
		for (i = 0; i < 2; i++) {
			// ���ù��λ����ÿһ��Ŀ�ʼλ��
			OLED_SetCursor(X, Y + i);
			for (j = 0; j < Front_size; j++) {
				OLED_Write(OLED_Data, OLED_F8x16[Char - ' '][i * Front_size + j]);
			}
		}
	}
	else if (Front_size == 16) {
		for (i = 0; i < 4; i++) {
			// ���ù��λ����ÿһ��Ŀ�ʼλ��
			OLED_SetCursor(X, Y + i);
			for (j = 0; j < Front_size; j++) {
				OLED_Write(OLED_Data, OLED_F16x32[Char - '0'][i * Front_size + j]);
			}
		}
	}
}

void OLED_ShowString(uint8_t Line, uint8_t Column, char *String, uint8_t Front_size) {
	uint8_t i;
	
	// ������ʾ�ַ����е�ÿ���ַ�����
	for (i = 0; String[i] != '\0'; i++) {
		OLED_ShowChar(Line, Column + i, String[i], Front_size);
	}
}

void OLED_ShowNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	// ����Ǹ�������ʾ����
	if (Number < 0) {
		OLED_ShowChar(Line, Column, '-', Front_size);
		Number = -Number;
		Column++;
	}
	
	for (i = 1; i <= Length; i++) {
		// �������Ҫ��ʾ������
		showNumber = Number % 10 + '0';
		// ��ʾ����Ļ�ϣ��Ӻ���ǰ��ʾ��
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		// ��ȥ��ʾ��������
		Number /= 10;
	}
}

void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	if (Number < 0) {
		OLED_ShowChar(Line, Column, '-', Front_size);
		Number = -Number;
		Column++;
	}
	
	for (i = 1; i <= Length; i++) {
		showNumber = Number % 8 + '0';
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 8;
	}
}

void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i, SingleNumber;
	
	for (i = 1; i <= Length; i++) {
		SingleNumber = Number % 16;
		if (SingleNumber < 10) {
			OLED_ShowChar(Line, Column + Length - i, SingleNumber + '0', Front_size);
		} else {
			OLED_ShowChar(Line, Column + Length - i, SingleNumber - 10 + 'A', Front_size);
		}
		Number /= 16;
	}
}

void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	for (i = 1; i <= Length; i++) {
		showNumber = Number % 2 + '0';		
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 2;
	}
}