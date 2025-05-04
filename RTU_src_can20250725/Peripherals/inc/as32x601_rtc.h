/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):    Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	 as32x601_rtc.h
 * Author:           ANSILIC APPLICATION GROUP
 * Version:          V1.0
 * Date:             2024/09/09
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/09/09     1.0     build this module
 * Description:     This file contains all the functions prototypes for the RTC firmware library.
 */

#ifndef AS32X601_RTC_H
#define AS32X601_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_rtc_regs.h"

/* 
 * @brief  RTC Time structure definition  
 */
typedef struct
{
    uint8_t RTC_Hours;              /* Specifies the RTC Time Hour.
                                    This parameter must be set to a value in the 0-23 range. */
    uint8_t RTC_Minutes;            /* Specifies the RTC Time Minutes.
                                    This parameter must be set to a value in the 0-59 range. */
    uint8_t RTC_Seconds;            /* Specifies the RTC Time Seconds.
                                    This parameter must be set to a value in the 0-59 range. */
    uint8_t RTC_TenthOfSecond;      /* Specify one tenth of the RTC time in seconds.
                                    This parameter must be set to a value in the 0-9 range. */
}RTC_TimeTypeDef; 

/* 
 * @brief  RTC Date structure definition  
 */
typedef struct
{
    uint8_t RTC_WeekDay;        /* Specifies the RTC Date WeekDay. */
    uint8_t RTC_Century;        /* Specifies the RTC Date Century.
                                This parameter must be set to a value in the 0-99 range. */
    uint8_t RTC_Year;           /* Specifies the RTC Date Year.
                                This parameter must be set to a value in the 0-99 range. */
    uint8_t RTC_Month;          /* Specifies the RTC Date Month.
                                This parameter must be set to a value in the 1-12 range. */
    uint8_t RTC_Date;           /* Specifies the RTC Date.
                                This parameter must be set to a value in the 1-31 range. */
}RTC_DateTypeDef;

/** 
  * @brief  RTC Alarm structure definition  
  */
typedef struct
{
    RTC_TimeTypeDef RTC_AlarmTime;      /* Specifies the RTC Alarm Time members. */
    RTC_DateTypeDef RTC_AlarmDate;      /* Specifies the RTC Alarm Date members. */
    uint32_t RTC_AlarmTimeCompEn;       /* Specifies the RTC Alarm Time Comparison Enable. */
    uint32_t RTC_AlarmDataCompEn;       /* Specifies the RTC Alarm Date Comparison Enable. */
}RTC_AlarmTypeDef;

/*
 * @defgroup RTC Frequency divider coefficient Definitions
 */ 
#define IS_RTC_DIVISION(DIVISION)       ((DIVISION) <= 0x7FFFFFF)

/*
 * @defgroup RTC Hours Date Definitions
 */ 
#define IS_RTC_HOURS(HOURS)             ((HOURS) <= 23)

/*
 * @defgroup RTC Minutes Date Definitions
 */ 
#define IS_RTC_MINUTES(MINUTES)         ((MINUTES) <= 59)

/*
 * @defgroup RTC Seconds Date Definitions
 */ 
#define IS_RTC_SECONDS(SECONDS)         ((SECONDS) <= 59)

/*
 * @defgroup RTC Tenth Of Second Date Definitions
 */ 
#define IS_RTC_TENOFSECOND(TENOFSECOND) ((TENOFSECOND) <= 9)

/*
 * @defgroup RTC Century Date Definitions
 */ 
#define IS_RTC_CENTURY(CENTURY)         ((CENTURY) <= 99)

/*
 * @defgroup RTC Year Date Definitions
 */ 
#define IS_RTC_YEAR(YEAR)               ((YEAR) <= 99)

/*
 * @defgroup RTC Month Date Definitions
 */
#define RTC_Month_January               ((uint8_t)0x01)
#define RTC_Month_February              ((uint8_t)0x02)
#define RTC_Month_March                 ((uint8_t)0x03)
#define RTC_Month_April                 ((uint8_t)0x04)
#define RTC_Month_May                   ((uint8_t)0x05)
#define RTC_Month_June                  ((uint8_t)0x06)
#define RTC_Month_July                  ((uint8_t)0x07)
#define RTC_Month_August                ((uint8_t)0x08)
#define RTC_Month_September             ((uint8_t)0x09)
#define RTC_Month_October               ((uint8_t)0x10)
#define RTC_Month_November              ((uint8_t)0x11)
#define RTC_Month_December              ((uint8_t)0x12)
#define IS_RTC_MONTH(MONTH)             (((MONTH) >= 1) && ((MONTH) <= 12))
#define IS_RTC_DATE(DATE)               (((DATE) >= 1) && ((DATE) <= 31))

/*
 * @defgroup RTC WeekDay Definitions
 */ 
#define RTC_Weekday_Monday              ((uint8_t)0x02)
#define RTC_Weekday_Tuesday             ((uint8_t)0x03)
#define RTC_Weekday_Wednesday           ((uint8_t)0x04)
#define RTC_Weekday_Thursday            ((uint8_t)0x05)
#define RTC_Weekday_Friday              ((uint8_t)0x06)
#define RTC_Weekday_Saturday            ((uint8_t)0x07)
#define RTC_Weekday_Sunday              ((uint8_t)0x01)
#define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday)    || \
                                 ((WEEKDAY) == RTC_Weekday_Tuesday)   || \
                                 ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                 ((WEEKDAY) == RTC_Weekday_Thursday)  || \
                                 ((WEEKDAY) == RTC_Weekday_Friday)    || \
                                 ((WEEKDAY) == RTC_Weekday_Saturday)  || \
                                 ((WEEKDAY) == RTC_Weekday_Sunday))

/*
 * @defgroup RTC Alarm Definitions
 */
#define RTC_Alarm_None                  ((uint32_t)0x00000000)
#define RTC_AlarmTime_WeekDay           ((uint32_t)0x80000000)
#define RTC_AlarmTime_Hours             ((uint32_t)0x40000000)
#define RTC_AlarmTime_Minutes           ((uint32_t)0x20008000)
#define RTC_AlarmTime_Seconds           ((uint32_t)0x10000000)
#define RTC_AlarmTime_TenOfSecond       ((uint32_t)0x08000000)
#define RTC_AlarmDate_Century           ((uint32_t)0x40000000)
#define RTC_AlarmDate_Year              ((uint32_t)0x20000000)
#define RTC_AlarmDate_Month             ((uint32_t)0x10000000)
#define RTC_AlarmDate_Date              ((uint32_t)0x08000000)
#define IS_RTC_ALARMTIME(ALARMTIME) (((ALARMTIME) & 0x07FFFFFF) == (uint32_t)RESET)
#define IS_RTC_ALARMDATE(ALARMDATE) (((ALARMDATE) & 0x87FFFFFF) == (uint32_t)RESET)

/*
 * @brief Function declaration
 */
void RTC_Init(uint32_t Division);
void RTC_SetTime(RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_GetTime(RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_SetDate(RTC_DateTypeDef* RTC_DateStruct);
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct);
void RTC_GetDate(RTC_DateTypeDef* RTC_DateStruct);
void RTC_SetAlarm(RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_GetAlarm(RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_ITConfig(EnState NewState);
FlagStatus RTC_GetFlagStatus(void);
FlagStatus RTC_GetITStatus(void);
void RTC_ClearITPendingBit(void);
void RTC_Cmd(FunctionalState NewState);
void RTC_WakeUpCmd(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
