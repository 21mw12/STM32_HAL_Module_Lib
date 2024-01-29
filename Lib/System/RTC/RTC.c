#include "RTC.h"
#include <time.h>

extern RTC_HandleTypeDef hrtc;
struct tm RTC_Time_Date;

void RTC_Init(void) {
	hrtc.Instance = RTC;
	hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
	
  if (HAL_RTC_Init(&hrtc) != HAL_OK) {
    Error_Handler();
  }
	
  if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x5050) {
	   HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5050);
  }
}

uint32_t RTC_GetCounter(void) {
	uint32_t time;
	
	time = RTC->CNTH;
	time <<= 16;
	time += RTC->CNTL;
	
	return time;
}

void RTC_SetTime(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second) {
	time_t time_cnt;
	
	RTC_Time_Date.tm_year = Year - 1900;
	RTC_Time_Date.tm_mon = Month - 1;
	RTC_Time_Date.tm_mday = Day;
	RTC_Time_Date.tm_hour = Hour;
	RTC_Time_Date.tm_min = Minute;
	RTC_Time_Date.tm_sec = Second;
	
	time_cnt = mktime(&RTC_Time_Date);
	
	RTC->CRL |= 1 << 4;
	RTC->CNTL = time_cnt & 0xFFFF;
	RTC->CNTH = time_cnt >> 16;
	RTC->CRL &= ~(1<<4);
	while (!(RTC->CRL & (1<<5)));
}

void RTC_RefreshTime(int8_t TimeZone) {
	time_t time_cnt = RTC_GetCounter();
	
	time_cnt += TimeZone * 60 * 60;
	
	RTC_Time_Date = *localtime(&time_cnt);
}

uint16_t RTC_GetYear(void) {
	return RTC_Time_Date.tm_year + 1900;
}

uint8_t RTC_GetMonth(void) {
	return RTC_Time_Date.tm_mon;
}

uint8_t RTC_GetDay(void) {
	return RTC_Time_Date.tm_mday;
}

uint8_t RTC_GetHour(void) {
	return RTC_Time_Date.tm_hour;
}

uint8_t RTC_GetMinute(void) {
	return RTC_Time_Date.tm_min;
}

uint8_t RTC_GetSecond(void) {
	return RTC_Time_Date.tm_sec;
}

