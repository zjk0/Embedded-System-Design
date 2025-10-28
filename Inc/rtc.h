/**
  ******************************************************************************
  * File Name          : RTC.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __rtc_H
#define __rtc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <time.h>
/* USER CODE END Includes */

extern RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN Private defines */
typedef struct {
  uint8_t year;    // 年份 (0-99, 表示2000-2099)
  uint8_t month;   // 月份 (1-12)
  uint8_t day;     // 日 (1-31)
  uint8_t weekday; // 星期 (1-7, 1=周一, 7=周日)
  uint8_t hour;    // 时 (0-23)
  uint8_t minute;  // 分 (0-59)
  uint8_t second;  // 秒 (0-59)
} Calendar_TypeDef;
/* USER CODE END Private defines */

void MX_RTC_Init(void);

/* USER CODE BEGIN Prototypes */
uint8_t is_leap_year(uint16_t year);
uint8_t get_days_in_month(uint8_t month, uint16_t year);
void get_current_calendar(Calendar_TypeDef *calendar);
void set_calendar(Calendar_TypeDef *calendar);
void calendar_add_days(Calendar_TypeDef *calendar, int days);
void calendar_add_months(Calendar_TypeDef *calendar, int months);
void calendar_add_years(Calendar_TypeDef *calendar, int years);
const char* get_weekday_name(uint8_t weekday);
const char* get_month_name(uint8_t month);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ rtc_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
