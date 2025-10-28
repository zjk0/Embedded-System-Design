/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
void my_rtc_init(void)
{
   RTC_DateTypeDef sDate;
  RTC_TimeTypeDef sTime;

  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 12;      // Сʱ (0-23)
  sTime.Minutes = 30;    // ���� (0-59)
  sTime.Seconds = 45;    // �� (0-59)
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  
  sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;  // ������ (1=��һ, 7=����)
  sDate.Month = RTC_MONTH_OCTOBER;        // ʮ�� (1=һ��, 12=ʮ����)
  sDate.Date = 8;                         // 8�� (1-31)
  sDate.Year = 25;                        // 2025�� (0-99��ʾ2000-2099)
  
  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */
 
  /* USER CODE END RTC_MspInit 0 */
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
// �ж��Ƿ�Ϊ����
uint8_t is_leap_year(uint16_t year) {
    if (year % 4 != 0) return 0;
    if (year % 100 != 0) return 1;
    if (year % 400 != 0) return 0;
    return 1;
}

// ��ȡĳ�µ�����
uint8_t get_days_in_month(uint8_t month, uint16_t year) {
    static const uint8_t days_per_month[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    
    if (month >= 1 && month <= 12) {
        return days_per_month[month - 1];
    }
    
    return 0;
}

// ��ȡ��ǰ����
void get_current_calendar(Calendar_TypeDef *calendar) {
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;
    
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
    
    calendar->year = date.Year;
    calendar->month = date.Month;
    calendar->day = date.Date;
    calendar->weekday = date.WeekDay;
    calendar->hour = time.Hours;
    calendar->minute = time.Minutes;
    calendar->second = time.Seconds;
}

// ��������
void set_calendar(Calendar_TypeDef *calendar) {
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;
    
    time.Hours = calendar->hour;
    time.Minutes = calendar->minute;
    time.Seconds = calendar->second;
    time.TimeFormat = RTC_HOURFORMAT_24;
    time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    time.StoreOperation = RTC_STOREOPERATION_RESET;
    
    if (HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN) != HAL_OK) {
        Error_Handler();
    }
    
    date.WeekDay = calendar->weekday;
    date.Month = calendar->month;
    date.Date = calendar->day;
    date.Year = calendar->year;
    
    if (HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN) != HAL_OK) {
        Error_Handler();
    }
}

// �������
void calendar_add_days(Calendar_TypeDef *calendar, int days) {
    while (days > 0) {
        uint8_t days_in_month = get_days_in_month(calendar->month, 2000 + calendar->year);
        
        if (calendar->day < days_in_month) {
            calendar->day++;
        } else {
            calendar->day = 1;
            calendar_add_months(calendar, 1);
        }
        
        calendar->weekday = (calendar->weekday % 7) + 1;
        days--;
    }
    
    while (days < 0) {
        if (calendar->day > 1) {
            calendar->day--;
        } else {
            calendar_add_months(calendar, -1);
            calendar->day = get_days_in_month(calendar->month, 2000 + calendar->year);
        }
        
        calendar->weekday = (calendar->weekday == 1) ? 7 : calendar->weekday - 1;
        days++;
    }
}

// �������
void calendar_add_months(Calendar_TypeDef *calendar, int months) {
    int total_months = calendar->year * 12 + (calendar->month - 1) + months;
    
    calendar->year = total_months / 12;
    calendar->month = (total_months % 12) + 1;
    
    // �������ڣ���ֹ��Ч���ڣ���2��30�գ�
    uint8_t days_in_month = get_days_in_month(calendar->month, 2000 + calendar->year);
    if (calendar->day > days_in_month) {
        calendar->day = days_in_month;
    }
}

// �������
void calendar_add_years(Calendar_TypeDef *calendar, int years) {
    calendar->year += years;
    
    // ��������2��29�յ����
    if (calendar->month == 2 && calendar->day == 29 && !is_leap_year(2000 + calendar->year)) {
        calendar->day = 28;
    }
}

const char Mon_chinese[] = "\xe6\x98\x9f\xe6\x9c\x9f\xe4\xb8\x80";
const char Tue_chinese[] = "\xe6\x98\x9f\xe6\x9c\x9f\xe4\xba\x8c";
const char Wed_chinese[] = "\xe6\x98\x9f\xe6\x9c\x9f\xe4\xb8\x89";
const char Thu_chinese[] = "\xe6\x98\x9f\xe6\x9c\x9f\xe5\x9b\x9b";
const char Fri_chinese[] = "\xe6\x98\x9f\xe6\x9c\x9f\xe4\xba\x94";
const char Sat_chinese[] = "\xe6\x98\x9f\xe6\x9c\x9f\xe5\x85\xad";
const char Sun_chinese[] = "\xe6\x98\x9f\xe6\x9c\x9f\xe6\x97\xa5";

// ��ȡ��������
const char* get_weekday_name(uint8_t weekday) {
    static const char* weekdays[] = {
        Mon_chinese, Tue_chinese, Wed_chinese, Thu_chinese, Fri_chinese, Sat_chinese, Sun_chinese
    };
    
    if (weekday >= 1 && weekday <= 7) {
        return weekdays[weekday - 1];
    }
    
    return "Unknown";
}

// ��ȡ�·�����
const char* get_month_name(uint8_t month) {
    static const char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    
    if (month >= 1 && month <= 12) {
        return months[month - 1];
    }
    
    return "Unknown";
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
