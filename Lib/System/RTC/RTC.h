#ifndef RTC_RTC_H_
#define RTC_RTC_H_

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�RTC����ع��ܺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/29
//
// ע����CubeMX��Ҫ����RTC���������ɳ�ʼ������
//
///////////////////////////////////////////////////////////

#include "stm32f1xx_hal.h"
#include "main.h"

/**
  * @brief RTC��ʼ��
  * @return ��
  */
void RTC_Init(void);

/**
  * @brief ��ȡʱ���
  * @return ʱ���
  */
uint32_t RTC_GetCounter(void);

/**
  * @brief ����RTC��׼ʱ��
  * @param Year ���
  * @param Month �·�
  * @param Day ����
  * @param Hour Сʱ
  * @param Minute ����
  * @param Second ��
  * @return ��
  */
void RTC_SetTime(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second);

/**
  * @brief ˢ��RTCʱ�ӣ���Ҫ��ʱ���ת��Ϊ����ʱ�����ٵ��ã�
  * @param TimeZone ʱ�������磺����Ϊ��8����
  * @return ��
  */
void RTC_RefreshTime(int8_t TimeZone);

/**
  * @brief ��ȡRTCʱ�ӵ����
  * @return ���
  */
uint16_t RTC_GetYear(void);

/**
  * @brief ��ȡRTCʱ�ӵ��·�
  * @return �·�
  */
uint8_t RTC_GetMonth(void);

/**
  * @brief ��ȡRTCʱ�ӵ�����
  * @return ����
  */
uint8_t RTC_GetDay(void);

/**
  * @brief ��ȡRTCʱ�ӵ�Сʱ
  * @return Сʱ
  */
uint8_t RTC_GetHour(void);

/**
  * @brief ��ȡRTCʱ�ӵķ���
  * @return ����
  */
uint8_t RTC_GetMinute(void);

/**
  * @brief ��ȡRTCʱ�ӵ���
  * @return ��
  */
uint8_t RTC_GetSecond(void);

#endif
