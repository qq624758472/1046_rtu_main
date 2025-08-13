/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_rtc.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2024/09/10
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/09/10     1.0     build this module
 * Description:     This file provides firmware functions to manage the functionalities of the RTC peripheral.
 */

#include "as32x601_rtc.h"

/* Masks Definition */
#define RTC_TR_RESERVED_MASK        ((uint32_t)0x00FFFFFF)
#define RTC_DR_RESERVED_MASK        ((uint32_t)0x07FFFFFF)
#define RTC_ALRMTR_RESERVED_MASK    ((uint32_t)0xF8000000) 
#define RTC_ALRMDR_RESERVED_MASK    ((uint32_t)0x78000000) 

/* Private function prototypes -----------------------------------------------*/
static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/*
 * Function:        RTC_Init
 * Description:     Initialize RTC clock divider.
 * Param:           Division: Set the frequency divider coefficient, it is recommended to set it to 1638.
 * Return:          None.
 */
void RTC_Init(uint32_t Division)
{
    uint32_t tmpreg = 0x00;
  
    /* Check the parameters */
    assert_param(IS_RTC_DIVISION(Division));

    tmpreg = RTC->CR;

    /* Set RTC divider coefficient */
    tmpreg &= ~((uint32_t)RTC_CR_DIV);
    tmpreg |= ((uint32_t)Division << RTC_CR_DIV_Pos);

    /* Clear RTC one tenth second block bit */
    tmpreg &= ~((uint32_t)RTC_CR_TOSB);

    /* Write to RTC CR */
    RTC->CR = (uint32_t)tmpreg;
}

/*
 * Function:        RTC_SetTime
 * Description:     Set the RTC current time.
 * Param:           RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that contains 
 *                  the time configuration information for the RTC.
 * Return:          None.
 */
void RTC_SetTime(RTC_TimeTypeDef* RTC_TimeStruct)
{
    uint32_t tmpreg = 0;
    
    /* Check the parameters */
    assert_param(IS_RTC_HOURS(RTC_TimeStruct->RTC_Hours));
    assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
    assert_param(IS_RTC_TENOFSECOND(RTC_TimeStruct->RTC_TenthOfSecond));

    tmpreg = RTC->TR;

    /* Set RTC hours */
    tmpreg &= ~((uint32_t)(RTC_TR_HT | RTC_TR_HU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Hours) << RTC_TR_HU_Pos);

    /* Set RTC minutes */
    tmpreg &= ~((uint32_t)(RTC_TR_MNT | RTC_TR_MNU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Minutes) << RTC_TR_MNU_Pos);

    /* Set RTC seconds */
    tmpreg &= ~((uint32_t)(RTC_TR_ST | RTC_TR_SU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Seconds) << RTC_TR_SU_Pos);

    /* Set RTC hours */
    tmpreg &= ~((uint32_t)RTC_TR_TOS);
    tmpreg |= ((uint32_t)RTC_TimeStruct->RTC_TenthOfSecond << RTC_TR_TOS_Pos);

    /* Write to RTC TR */
    RTC->TR = tmpreg;
}

/*
 * Function:        RTC_TimeStructInit
 * Description:     Fills each RTC_TimeStruct member with its default value(Time = 00h:00min:00sec:00ms).
 * Param:           RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure which will be initialized.
 * Return:          None.
 */
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct)
{
    /* Time = 00h:00min:00sec:00ms */
    RTC_TimeStruct->RTC_Hours = 0;
    RTC_TimeStruct->RTC_Minutes = 0;
    RTC_TimeStruct->RTC_Seconds = 0;
    RTC_TimeStruct->RTC_TenthOfSecond = 0;
}

/*
 * Function:        RTC_GetTime
 * Description:     Get the RTC current Time.
 * Param:           RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that will 
 *                  contain the returned current time configuration.
 * Return:          None.
 */
void RTC_GetTime(RTC_TimeTypeDef* RTC_TimeStruct)
{
    uint32_t tmpreg = 0;

    /* Get the RTC_TR register */
    tmpreg = (uint32_t)(RTC->TR & RTC_TR_RESERVED_MASK); 

    /* Fill the structure fields with the read parameters */
    RTC_TimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_TR_HT | RTC_TR_HU)) >> RTC_TR_HU_Pos);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_TR_MNT | RTC_TR_MNU)) >> RTC_TR_MNU_Pos);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_TR_ST | RTC_TR_SU)) >> RTC_TR_SU_Pos);
    RTC_TimeStruct->RTC_TenthOfSecond = (uint8_t)((tmpreg & (RTC_TR_TOS)) >> RTC_TR_TOS_Pos);
}

/*
 * Function:        RTC_SetDate
 * Description:     Set the RTC current date.
 * Param:           RTC_DateStruct: pointer to a RTC_DateTypeDef structure that contains 
 *                  the date configuration information for the RTC.
 * Return:          None.
 */
void RTC_SetDate(RTC_DateTypeDef* RTC_DateStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->RTC_WeekDay));
    assert_param(IS_RTC_CENTURY(RTC_DateStruct->RTC_Century));
    assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
    assert_param(IS_RTC_MONTH(RTC_DateStruct->RTC_Month));
    assert_param(IS_RTC_DATE(RTC_DateStruct->RTC_Date));

    tmpreg = RTC->TR;

    /* Set RTC weekday */
    tmpreg &= ~((uint32_t)RTC_TR_WDU);
    tmpreg |= ((uint32_t)RTC_DateStruct->RTC_WeekDay << RTC_TR_WDU_Pos);

    /* Write to RTC TR */
    RTC->TR = tmpreg;

    tmpreg = 0;

    tmpreg = RTC->DR;

    /* Set RTC century */
    tmpreg &= ~((uint32_t)(RTC_DR_CT | RTC_DR_CU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Century) << RTC_DR_CU_Pos);

    /* Set RTC year */
    tmpreg &= ~((uint32_t)(RTC_DR_YT | RTC_DR_YU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Year) << RTC_DR_YU_Pos);

    /* Set RTC month */
    tmpreg &= ~((uint32_t)(RTC_DR_MT | RTC_DR_MU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Month) << RTC_DR_MU_Pos);

    /* Set RTC date */
    tmpreg &= ~((uint32_t)(RTC_DR_DT | RTC_DR_DU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Date) << RTC_DR_DU_Pos);
    
    /* Write to RTC DR */
    RTC->DR = tmpreg;
}

/*
 * Function:        RTC_DateStructInit
 * Description:     Fills each RTC_DateStruct member with its default value (Monday, January 01 0000).
 * Param:           RTC_DateStruct: pointer to a RTC_DateTypeDef structure which will be initialized.
 * Return:          None.
 */
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct)
{
    /* Monday, January 01 0000 */
    RTC_DateStruct->RTC_WeekDay = RTC_Weekday_Monday;
    RTC_DateStruct->RTC_Date = 1;
    RTC_DateStruct->RTC_Month = RTC_Month_January;
    RTC_DateStruct->RTC_Year = 0;
    RTC_DateStruct->RTC_Century = 0;
}

/*
 * Function:        RTC_GetDate
 * Description:     Get the RTC current date.
 * Param:           RTC_DateStruct: pointer to a RTC_DateTypeDef structure that will 
 *                  contain the returned current date configuration.
 * Return:          None.
 */
void RTC_GetDate(RTC_DateTypeDef* RTC_DateStruct)
{
    uint32_t tmpreg = 0;

    /* Get the RTC_TR register */
    tmpreg = (uint32_t)(RTC->TR & RTC_TR_WDU);

    /* Fill the structure fields with the read parameters */
    RTC_DateStruct->RTC_WeekDay = (uint8_t)((tmpreg & (RTC_TR_WDU)) >> RTC_TR_WDU_Pos);

    /* Get the RTC_DR register */
    tmpreg = (uint32_t)(RTC->DR & RTC_DR_RESERVED_MASK); 

    /* Fill the structure fields with the read parameters */
    RTC_DateStruct->RTC_Century = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_DR_CT | RTC_DR_CU)) >> RTC_DR_CU_Pos);
    RTC_DateStruct->RTC_Year = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_DR_YT | RTC_DR_YU)) >> RTC_DR_YU_Pos);
    RTC_DateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_DR_MT | RTC_DR_MU)) >> RTC_DR_MU_Pos);
    RTC_DateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_DR_DT | RTC_DR_DU)) >> RTC_DR_DU_Pos);
}

/*
 * Function:        RTC_SetAlarm
 * Description:     Set the specified RTC Alarm.
 * Param:           RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that 
 *                  contains the alarm configuration parameters.
 * Return:          None.
 */
void RTC_SetAlarm(RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_ALARMTIME(RTC_AlarmStruct->RTC_AlarmTimeCompEn));
    assert_param(IS_RTC_ALARMDATE(RTC_AlarmStruct->RTC_AlarmDataCompEn));
    assert_param(IS_RTC_WEEKDAY(RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay));
    assert_param(IS_RTC_CENTURY(RTC_AlarmStruct->RTC_AlarmDate.RTC_Century));
    assert_param(IS_RTC_YEAR(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year));
    assert_param(IS_RTC_MONTH(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month));
    assert_param(IS_RTC_DATE(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date));
    assert_param(IS_RTC_HOURS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
    assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));
    assert_param(IS_RTC_TENOFSECOND(RTC_AlarmStruct->RTC_AlarmTime.RTC_TenthOfSecond));
    
    tmpreg = RTC->ALRMTR;

    /* Set RTC time comparison */
    tmpreg &= ~((uint32_t)RTC_ALRMTR_RESERVED_MASK);
    tmpreg |= ((uint32_t)RTC_AlarmStruct->RTC_AlarmTimeCompEn);

    /* Set RTC week comparison */
    tmpreg &= ~((uint32_t)RTC_ALRMTR_WDU);
    tmpreg |= ((uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay << RTC_ALRMTR_WDU_Pos);

    /* Set RTC hour comparison */
    tmpreg &= ~((uint32_t)(RTC_ALRMTR_HT | RTC_ALRMTR_HU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << RTC_ALRMTR_HU_Pos);

    /* Set RTC minute comparison */
    tmpreg &= ~((uint32_t)(RTC_ALRMTR_MNT | RTC_ALRMTR_MNU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << RTC_ALRMTR_MNU_Pos);

    /* Set RTC Second comparison */
    tmpreg &= ~((uint32_t)(RTC_ALRMTR_ST | RTC_ALRMTR_SU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds) << RTC_ALRMTR_SU_Pos);

    /* Set RTC tenth of a second comparison */
    tmpreg &= ~((uint32_t)RTC_ALRMTR_TOS);
    tmpreg |= ((uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_TenthOfSecond << RTC_ALRMTR_TOS_Pos);

    /* Write to RTC ALRMTR */
    RTC->ALRMTR = tmpreg;

    tmpreg = 0;

    tmpreg = RTC->ALRMDR;

    /* Set RTC data comparison */
    tmpreg &= ~((uint32_t)RTC_ALRMDR_RESERVED_MASK);
    tmpreg |= ((uint32_t)RTC_AlarmStruct->RTC_AlarmDataCompEn);

    /* Set RTC century comparison */
    tmpreg &= ~((uint32_t)(RTC_ALRMDR_CT | RTC_ALRMDR_CU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Century) << RTC_ALRMDR_CU_Pos);

    /* Set RTC year comparison */
    tmpreg &= ~((uint32_t)(RTC_ALRMDR_YT | RTC_ALRMDR_YU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year) << RTC_ALRMDR_YU_Pos);

    /* Set RTC month comparison */
    tmpreg &= ~((uint32_t)(RTC_ALRMDR_MT | RTC_ALRMDR_MU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month) << RTC_ALRMDR_MU_Pos);

    /* Set RTC date comparison */
    tmpreg &= ~((uint32_t)(RTC_ALRMDR_DT | RTC_ALRMDR_DU));
    tmpreg |= ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date) << RTC_ALRMDR_DU_Pos);

    /* Write to RTC ALRMDR */
    RTC->ALRMDR = tmpreg;
}

/*
 * Function:        RTC_AlarmStructInit
 * Description:     Fills each RTC_AlarmStruct member with its default value.
 *                  (Time = 00h:00mn:00sec:00ms / Date = Monday, January 01 0000 /
 *                  Comparison = all fields are not comparison).
 * Param:           RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that 
 *                  contains the alarm configuration parameters.
 * Return:          None.
 */
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    /* Alarm Time Settings : Time = 00h:00mn:00sec:00ms */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_TenthOfSecond = 0;

    /* Alarm Date Settings : Date = Monday, January 01 0000 */
    RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay = RTC_Weekday_Monday;
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Century = 0;
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = 0;
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = RTC_Month_January;
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = 1;

    /* Alarm Masks Settings : Comparison = all fields are not comparison */
    RTC_AlarmStruct->RTC_AlarmTimeCompEn = RTC_Alarm_None;
    RTC_AlarmStruct->RTC_AlarmDataCompEn = RTC_Alarm_None;
}

/*
 * Function:        RTC_GetAlarm
 * Description:     Get the RTC Alarm value and masks.
 * Param:           RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that will 
 *                  contains the output alarm configuration values.
 * Return:          None.
 */
void RTC_GetAlarm(RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    uint32_t tmpreg = 0;

    /* Get the RTC_ALRMTR register */
    tmpreg = (uint32_t)(RTC->ALRMTR); 

    /* Fill the structure fields with the read parameters */
    RTC_AlarmStruct->RTC_AlarmTimeCompEn = ((uint32_t)(tmpreg & RTC_ALRMTR_RESERVED_MASK));
    RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay = (uint8_t)((tmpreg & (RTC_ALRMTR_WDU)) >> RTC_ALRMTR_WDU_Pos);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_ALRMTR_HT | RTC_ALRMTR_HU)) >> RTC_ALRMTR_HU_Pos);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_ALRMTR_MNT | RTC_ALRMTR_MNU)) >> RTC_ALRMTR_MNU_Pos);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_ALRMTR_ST | RTC_ALRMTR_SU)) >> RTC_ALRMTR_SU_Pos);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_TenthOfSecond = (uint8_t)((tmpreg & (RTC_ALRMTR_TOS)) >> RTC_ALRMTR_TOS_Pos);

    tmpreg = 0;

    /* Get the RTC_ALRMDR register */
    tmpreg = (uint32_t)(RTC->ALRMDR); 

    /* Fill the structure fields with the read parameters */
    RTC_AlarmStruct->RTC_AlarmDataCompEn = ((uint32_t)(tmpreg & RTC_ALRMDR_RESERVED_MASK));
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Century = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_ALRMDR_CT | RTC_ALRMDR_CU)) >> RTC_ALRMDR_CU_Pos);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_ALRMDR_YT | RTC_ALRMDR_YU)) >> RTC_ALRMDR_YU_Pos);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_ALRMDR_MT | RTC_ALRMDR_MU)) >> RTC_ALRMDR_MU_Pos);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = (uint8_t)RTC_Bcd2ToByte((tmpreg & (RTC_ALRMDR_DT | RTC_ALRMDR_DU)) >> RTC_ALRMDR_DU_Pos);
}

/*
 * Function:        RTC_ITConfig
 * Description:     Enables or disables the specified RTC interrupts.
 * Param:           NewState: new state of the Update disable.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None
 */
void RTC_ITConfig(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != DISABLE) 
    {
        /* Enable the interrupt */
        RTC->CR |= ((uint32_t)RTC_CR_IE);
    } 
    else 
    {
        /* Disable the interrupt */
        RTC->CR &= ~((uint32_t)RTC_CR_IE);
    }
}

/*
 * Function:        RTC_GetFlagStatus
 * Description:     Check whether the specified RTC interrupt has occurred or not.
 * param:           None.
 * Return:          RTC IT status.
 *                   This parameter can be one of the following values:
 *                    SET or RESET.
 */
FlagStatus RTC_GetFlagStatus(void)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */

    if((RTC->CR & RTC_CR_ALRMT) != RESET) 
    {
        bitstatus = SET;
    }
    else 
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/*
 * Function:        RTC_GetITStatus
 * Description:     Check whether the specified RTC interrupt source is enabled or not.
 * Param:           None.
 * Return:          The new state of RTC_IT (SET or RESET).
 */
FlagStatus RTC_GetITStatus(void)
{
    FlagStatus bitstatus = RESET;

    if((RTC->CR & RTC_CR_IE) != RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/*
 * Function:        RTC_ClearITPendingBit
 * Description:     Clear the interrupt pending bits of the specified RTC.
 * Param:           None.
 * Return:          None.
 */
void RTC_ClearITPendingBit(void)
{
    RTC->CR &= ~((uint32_t)RTC_CR_ALRMT);
}

/*
 * Function:        RTC_Cmd
 * Description:     Enables or disables the specified RTC peripheral.
 * Param:           NewState: new state of the RTC peripheral.
 *                  This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void RTC_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FunctionalState_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected RTC by setting the EN bit in the CR register */
        RTC->CR |= ((uint32_t)RTC_CR_EN);
    }
    else
    {
        /* Disable the selected RTC by setting the EN bit in the CR register */
        RTC->CR &= ~((uint32_t)RTC_CR_EN);
    }
}

/*
 * Function:        RTC_WakeUpCmd
 * Description:     Enables or disables the specified RTC Wakeup.
 * Param:           NewState: new state of the RTC Wakeup.
 *                  This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void RTC_WakeUpCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FunctionalState_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected RTC by setting the WUTE bit in the WUCR register */
        RTC->WUCR |= ((uint32_t)RTC_WUCR_WUTE);
    }
    else
    {
        /* Disable the selected RTC by setting the WUTE bit in the WUCR register */
        RTC->WUCR &= ~((uint32_t)RTC_WUCR_WUTE);
    }
}

/*
 * Function:        RTC_ByteToBcd2
 * Description:     Converts a 2 digit decimal to BCD format.
 * Param:           Value: Byte to be converted.
 * Return:          Converted byte.
 */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
    uint8_t bcdhigh = 0;

    while (Value >= 10)
    {
        bcdhigh++;
        Value -= 10;
    }

    return ((uint8_t)(bcdhigh << 4) | Value);
}

/*
 * Function:        RTC_Bcd2ToByte
 * Description:     Convert from 2 digit BCD to Binary.
 * Param:           Value: BCD value to be converted.
 * Return:          Converted word.
 */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
    uint8_t tmp = 0;
    tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (Value & (uint8_t)0x0F));
}

/*****END OF FILE*****/
