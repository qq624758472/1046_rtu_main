/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_pmu.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:			2024/08/26
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/26     1.0     build this module
 * Description:     This file contains all the functions prototypes for the PMU firmware library.
 */

#ifndef AS32X601_PMU_H
#define AS32X601_PMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_pmu_regs.h"

/*
 * @brief PMU power mode enumeration
 */
typedef enum 
{
    PMU_PowerMode_INIT      = 0x00,     /* Start initial mode */
    PMU_PowerMode_DeepSleep = 0x01,     /* Deep sleep mode */
    PMU_PowerMode_Sleep     = 0x02,     /* Sleep mode */
    PMU_PowerMode_Normal    = 0x03      /* Normal mode */
} PMUPowerMode_TypeDef;
#define IS_PMU_POWERMODE(POWERMODE) (((POWERMODE) == PMU_PowerMode_DeepSleep) || ((POWERMODE) == PMU_PowerMode_Sleep))

/*
 * @brief PMU wake up source enumeration
 */
typedef enum 
{
    PMU_WKSource_IWDG = 0x00,           /* The wake-up source is IWDG */
    PMU_WKSource_RTC  = 0x03,           /* The wake-up source is RTC */
    PMU_WKSource_PH0  = 0x04,           /* The wake-up source is PH0 */
    PMU_WKSource_PH1  = 0x05,           /* The wake-up source is PH1 */
    PMU_WKSource_PH2  = 0x06,           /* The wake-up source is PH2 */
    PMU_WKSource_PH3  = 0x07,           /* The wake-up source is PH3 */
    PMU_WKSource_PH4  = 0x08,           /* The wake-up source is PH4 */
    PMU_WKSource_PH5  = 0x09,           /* The wake-up source is PH5 */
    PMU_WKSource_PH6  = 0x0A,           /* The wake-up source is PH6 */
    PMU_WKSource_PH7  = 0x0B,           /* The wake-up source is PH7 */
    PMU_WKSource_PH8  = 0x0C,           /* The wake-up source is PH8 */
    PMU_WKSource_PH9  = 0x0D            /* The wake-up source is PH9 */
} PMUWKSource_TypeDef;
#define IS_PMU_WKSOURCE(WKSOURCE) (((WKSOURCE) == PMU_WKSource_IWDG) || ((WKSOURCE) == PMU_WKSource_RTC) || \
                                   ((WKSOURCE) == PMU_WKSource_PH0)  || ((WKSOURCE) == PMU_WKSource_PH1) || \
                                   ((WKSOURCE) == PMU_WKSource_PH2)  || ((WKSOURCE) == PMU_WKSource_PH3) || \
                                   ((WKSOURCE) == PMU_WKSource_PH4)  || ((WKSOURCE) == PMU_WKSource_PH5) || \
                                   ((WKSOURCE) == PMU_WKSource_PH6)  || ((WKSOURCE) == PMU_WKSource_PH7) || \
                                   ((WKSOURCE) == PMU_WKSource_PH8)  || ((WKSOURCE) == PMU_WKSource_PH9))

/*
 * @defgroup Adjust 3.3v voltage definition
 */
#define PMU_VO33_2V90           ((uint32_t)0x00000000)          /* Adjust voltage to 2.90v */
#define PMU_VO33_2V95           ((uint32_t)0x00000001)          /* Adjust voltage to 2.95v */
#define PMU_VO33_3V00           ((uint32_t)0x00000002)          /* Adjust voltage to 3.00v */
#define PMU_VO33_3V05           ((uint32_t)0x00000003)          /* Adjust voltage to 3.05v */
#define PMU_VO33_3V10           ((uint32_t)0x00000004)          /* Adjust voltage to 3.10v */
#define PMU_VO33_3V15           ((uint32_t)0x00000005)          /* Adjust voltage to 3.15v */
#define PMU_VO33_3V20           ((uint32_t)0x00000006)          /* Adjust voltage to 3.20v */
#define PMU_VO33_3V25           ((uint32_t)0x00000007)          /* Adjust voltage to 3.25v */
#define PMU_VO33_3V30           ((uint32_t)0x00000008)          /* Adjust voltage to 3.30v(default) */
#define PMU_VO33_3V35           ((uint32_t)0x00000009)          /* Adjust voltage to 3.35v */
#define PMU_VO33_3V40           ((uint32_t)0x0000000A)          /* Adjust voltage to 3.40v */
#define PMU_VO33_3V45           ((uint32_t)0x0000000B)          /* Adjust voltage to 3.45v */
#define PMU_VO33_3V50           ((uint32_t)0x0000000C)          /* Adjust voltage to 3.50v */
#define PMU_VO33_3V55           ((uint32_t)0x0000000D)          /* Adjust voltage to 3.55v */
#define PMU_VO33_3V60           ((uint32_t)0x0000000E)          /* Adjust voltage to 3.60v */
#define PMU_VO33_3V65           ((uint32_t)0x0000000F)          /* Adjust voltage to 3.65v */
#define IS_PMU_VOS3V3(VOS3V3) (((VOS3V3) == PMU_VO33_2V90) || ((VOS3V3) == PMU_VO33_2V95) || \
                               ((VOS3V3) == PMU_VO33_3V00) || ((VOS3V3) == PMU_VO33_3V05) || \
                               ((VOS3V3) == PMU_VO33_3V10) || ((VOS3V3) == PMU_VO33_3V15) || \
                               ((VOS3V3) == PMU_VO33_3V20) || ((VOS3V3) == PMU_VO33_3V25) || \
                               ((VOS3V3) == PMU_VO33_3V30) || ((VOS3V3) == PMU_VO33_3V35) || \
                               ((VOS3V3) == PMU_VO33_3V40) || ((VOS3V3) == PMU_VO33_3V45) || \
                               ((VOS3V3) == PMU_VO33_3V50) || ((VOS3V3) == PMU_VO33_3V55) || \
                               ((VOS3V3) == PMU_VO33_3V60) || ((VOS3V3) == PMU_VO33_3V65))

/*
 * @defgroup Adjust 2.5v voltage definition
 */
#define PMU_VO25_2V18           ((uint32_t)0x00000000)          /* Adjust voltage to 2.18v */
#define PMU_VO25_2V22           ((uint32_t)0x00000001)          /* Adjust voltage to 2.22v */
#define PMU_VO25_2V26           ((uint32_t)0x00000002)          /* Adjust voltage to 2.26v */
#define PMU_VO25_2V30           ((uint32_t)0x00000003)          /* Adjust voltage to 2.30v */
#define PMU_VO25_2V34           ((uint32_t)0x00000004)          /* Adjust voltage to 2.34v */
#define PMU_VO25_2V38           ((uint32_t)0x00000005)          /* Adjust voltage to 2.38v */
#define PMU_VO25_2V42           ((uint32_t)0x00000006)          /* Adjust voltage to 2.42v */
#define PMU_VO25_2V46           ((uint32_t)0x00000007)          /* Adjust voltage to 2.46v */
#define PMU_VO25_2V50           ((uint32_t)0x00000008)          /* Adjust voltage to 2.50v(default) */
#define PMU_VO25_2V54           ((uint32_t)0x00000009)          /* Adjust voltage to 2.54v */
#define PMU_VO25_2V58           ((uint32_t)0x0000000A)          /* Adjust voltage to 2.58v */
#define PMU_VO25_2V62           ((uint32_t)0x0000000B)          /* Adjust voltage to 2.62v */
#define PMU_VO25_2V66           ((uint32_t)0x0000000C)          /* Adjust voltage to 2.66v */
#define PMU_VO25_2V72           ((uint32_t)0x0000000D)          /* Adjust voltage to 2.72v */
#define PMU_VO25_2V74           ((uint32_t)0x0000000E)          /* Adjust voltage to 2.74v */
#define PMU_VO25_2V78           ((uint32_t)0x0000000F)          /* Adjust voltage to 2.78v */
#define IS_PMU_VOS2V5(VOS2V5) (((VOS2V5) == PMU_VO25_2V18) || ((VOS2V5) == PMU_VO25_2V22) || \
                               ((VOS2V5) == PMU_VO25_2V26) || ((VOS2V5) == PMU_VO25_2V30) || \
                               ((VOS2V5) == PMU_VO25_2V34) || ((VOS2V5) == PMU_VO25_2V38) || \
                               ((VOS2V5) == PMU_VO25_2V42) || ((VOS2V5) == PMU_VO25_2V46) || \
                               ((VOS2V5) == PMU_VO25_2V50) || ((VOS2V5) == PMU_VO25_2V54) || \
                               ((VOS2V5) == PMU_VO25_2V58) || ((VOS2V5) == PMU_VO25_2V62) || \
                               ((VOS2V5) == PMU_VO25_2V66) || ((VOS2V5) == PMU_VO25_2V72) || \
                               ((VOS2V5) == PMU_VO25_2V74) || ((VOS2V5) == PMU_VO25_2V78))

/*
 * @defgroup Adjust 1.2v voltage definition
 */
#define PMU_VO12_1V04           ((uint32_t)0x00000000)          /* Adjust voltage to 1.04v */
#define PMU_VO12_1V06           ((uint32_t)0x00000001)          /* Adjust voltage to 1.06v */
#define PMU_VO12_1V08           ((uint32_t)0x00000002)          /* Adjust voltage to 1.08v */
#define PMU_VO12_1V10           ((uint32_t)0x00000003)          /* Adjust voltage to 1.10v */
#define PMU_VO12_1V12           ((uint32_t)0x00000004)          /* Adjust voltage to 1.12v */
#define PMU_VO12_1V14           ((uint32_t)0x00000005)          /* Adjust voltage to 1.14v */
#define PMU_VO12_1V16           ((uint32_t)0x00000006)          /* Adjust voltage to 1.16v */
#define PMU_VO12_1V18           ((uint32_t)0x00000007)          /* Adjust voltage to 1.18v */
#define PMU_VO12_1V20           ((uint32_t)0x00000008)          /* Adjust voltage to 1.20v(default) */
#define PMU_VO12_1V22           ((uint32_t)0x00000009)          /* Adjust voltage to 1.22v */
#define PMU_VO12_1V24           ((uint32_t)0x0000000A)          /* Adjust voltage to 1.24v */
#define PMU_VO12_1V26           ((uint32_t)0x0000000B)          /* Adjust voltage to 1.26v */
#define PMU_VO12_1V28           ((uint32_t)0x0000000C)          /* Adjust voltage to 1.28v */
#define PMU_VO12_1V30           ((uint32_t)0x0000000D)          /* Adjust voltage to 1.30v */
#define PMU_VO12_1V32           ((uint32_t)0x0000000E)          /* Adjust voltage to 1.32v */
#define PMU_VO12_1V34           ((uint32_t)0x0000000F)          /* Adjust voltage to 1.34v */
#define IS_PMU_VOS1V2(VOS1V2) (((VOS1V2) == PMU_VO12_1V04) || ((VOS1V2) == PMU_VO12_1V06) || \
                               ((VOS1V2) == PMU_VO12_1V08) || ((VOS1V2) == PMU_VO12_1V10) || \
                               ((VOS1V2) == PMU_VO12_1V12) || ((VOS1V2) == PMU_VO12_1V14) || \
                               ((VOS1V2) == PMU_VO12_1V16) || ((VOS1V2) == PMU_VO12_1V18) || \
                               ((VOS1V2) == PMU_VO12_1V20) || ((VOS1V2) == PMU_VO12_1V22) || \
                               ((VOS1V2) == PMU_VO12_1V24) || ((VOS1V2) == PMU_VO12_1V26) || \
                               ((VOS1V2) == PMU_VO12_1V28) || ((VOS1V2) == PMU_VO12_1V30) || \
                               ((VOS1V2) == PMU_VO12_1V32) || ((VOS1V2) == PMU_VO12_1V34))

/*
 * @defgroup Adjust Reference 1.2v voltage definition
 */
#define PMU_VREF12_1V04         ((uint32_t)0x00000000)          /* Adjust refer voltage to 1.04v */
#define PMU_VREF12_1V06         ((uint32_t)0x00000001)          /* Adjust refer voltage to 1.06v */
#define PMU_VREF12_1V08         ((uint32_t)0x00000002)          /* Adjust refer voltage to 1.08v */
#define PMU_VREF12_1V10         ((uint32_t)0x00000003)          /* Adjust refer voltage to 1.10v */
#define PMU_VREF12_1V12         ((uint32_t)0x00000004)          /* Adjust refer voltage to 1.12v */
#define PMU_VREF12_1V14         ((uint32_t)0x00000005)          /* Adjust refer voltage to 1.14v */
#define PMU_VREF12_1V16         ((uint32_t)0x00000006)          /* Adjust refer voltage to 1.16v */
#define PMU_VREF12_1V18         ((uint32_t)0x00000007)          /* Adjust refer voltage to 1.18v */
#define PMU_VREF12_1V20         ((uint32_t)0x00000008)          /* Adjust refer voltage to 1.20v(default) */
#define PMU_VREF12_1V22         ((uint32_t)0x00000009)          /* Adjust refer voltage to 1.22v */
#define PMU_VREF12_1V24         ((uint32_t)0x0000000A)          /* Adjust refer voltage to 1.24v */
#define PMU_VREF12_1V26         ((uint32_t)0x0000000B)          /* Adjust refer voltage to 1.26v */
#define PMU_VREF12_1V28         ((uint32_t)0x0000000C)          /* Adjust refer voltage to 1.28v */
#define PMU_VREF12_1V30         ((uint32_t)0x0000000D)          /* Adjust refer voltage to 1.30v */
#define PMU_VREF12_1V32         ((uint32_t)0x0000000E)          /* Adjust refer voltage to 1.32v */
#define PMU_VREF12_1V34         ((uint32_t)0x0000000F)          /* Adjust refer voltage to 1.34v */
#define IS_PMU_VREFS1V2(VREFS1V2) (((VREFS1V2) == PMU_VREF12_1V04) || ((VREFS1V2) == PMU_VREF12_1V06) || \
                                   ((VREFS1V2) == PMU_VREF12_1V08) || ((VREFS1V2) == PMU_VREF12_1V10) || \
                                   ((VREFS1V2) == PMU_VREF12_1V12) || ((VREFS1V2) == PMU_VREF12_1V14) || \
                                   ((VREFS1V2) == PMU_VREF12_1V16) || ((VREFS1V2) == PMU_VREF12_1V18) || \
                                   ((VREFS1V2) == PMU_VREF12_1V20) || ((VREFS1V2) == PMU_VREF12_1V22) || \
                                   ((VREFS1V2) == PMU_VREF12_1V24) || ((VREFS1V2) == PMU_VREF12_1V26) || \
                                   ((VREFS1V2) == PMU_VREF12_1V28) || ((VREFS1V2) == PMU_VREF12_1V30) || \
                                   ((VREFS1V2) == PMU_VREF12_1V32) || ((VREFS1V2) == PMU_VREF12_1V34))

/*
 * @defgroup High Voltage Detect Threshold Scaling definition
 */
#define PMU_HVDTS_2V4           ((uint32_t)0x00000000)          /* Adjust the detection threshold voltage to 2.4V */
#define PMU_HVDTS_2V5           ((uint32_t)0x00000001)          /* Adjust the detection threshold voltage to 2.5V */
#define PMU_HVDTS_2V6           ((uint32_t)0x00000002)          /* Adjust the detection threshold voltage to 2.6V */
#define PMU_HVDTS_2V7           ((uint32_t)0x00000003)          /* Adjust the detection threshold voltage to 2.7V */
#define PMU_HVDTS_2V8           ((uint32_t)0x00000004)          /* Adjust the detection threshold voltage to 2.8V */
#define PMU_HVDTS_2V9           ((uint32_t)0x00000005)          /* Adjust the detection threshold voltage to 2.9V */
#define PMU_HVDTS_3V0           ((uint32_t)0x00000006)          /* Adjust the detection threshold voltage to 3.0V */
#define PMU_HVDTS_3V1           ((uint32_t)0x00000007)          /* Adjust the detection threshold voltage to 3.1V */
#define PMU_HVDTS_3V2           ((uint32_t)0x00000008)          /* Adjust the detection threshold voltage to 3.2V */
#define PMU_HVDTS_3V3           ((uint32_t)0x00000009)          /* Adjust the detection threshold voltage to 3.3V */
#define PMU_HVDTS_3V4           ((uint32_t)0x0000000A)          /* Adjust the detection threshold voltage to 3.4V */
#define PMU_HVDTS_3V5           ((uint32_t)0x0000000B)          /* Adjust the detection threshold voltage to 3.5V */
#define PMU_HVDTS_3V6           ((uint32_t)0x0000000C)          /* Adjust the detection threshold voltage to 3.6V */
#define PMU_HVDTS_3V7           ((uint32_t)0x0000000D)          /* Adjust the detection threshold voltage to 3.7V */
#define PMU_HVDTS_3V8           ((uint32_t)0x0000000E)          /* Adjust the detection threshold voltage to 3.8V */
#define PMU_HVDTS_3V9           ((uint32_t)0x0000000F)          /* Adjust the detection threshold voltage to 3.9V */
#define PMU_HVDTS_4V0           ((uint32_t)0x00000010)          /* Adjust the detection threshold voltage to 4.0V */
#define PMU_HVDTS_4V1           ((uint32_t)0x00000011)          /* Adjust the detection threshold voltage to 4.1V */
#define PMU_HVDTS_4V2           ((uint32_t)0x00000012)          /* Adjust the detection threshold voltage to 4.2V */
#define PMU_HVDTS_4V3           ((uint32_t)0x00000013)          /* Adjust the detection threshold voltage to 4.3V */
#define PMU_HVDTS_4V4           ((uint32_t)0x00000014)          /* Adjust the detection threshold voltage to 4.4V */
#define PMU_HVDTS_4V5           ((uint32_t)0x00000015)          /* Adjust the detection threshold voltage to 4.5V */
#define PMU_HVDTS_4V6           ((uint32_t)0x00000016)          /* Adjust the detection threshold voltage to 4.6V */
#define PMU_HVDTS_4V7           ((uint32_t)0x00000017)          /* Adjust the detection threshold voltage to 4.7V */
#define PMU_HVDTS_4V8           ((uint32_t)0x00000018)          /* Adjust the detection threshold voltage to 4.8V */
#define PMU_HVDTS_4V9           ((uint32_t)0x00000019)          /* Adjust the detection threshold voltage to 4.9V */
#define PMU_HVDTS_5V0           ((uint32_t)0x0000001A)          /* Adjust the detection threshold voltage to 5.0V */
#define PMU_HVDTS_5V1           ((uint32_t)0x0000001B)          /* Adjust the detection threshold voltage to 5.1V */
#define PMU_HVDTS_5V2           ((uint32_t)0x0000001C)          /* Adjust the detection threshold voltage to 5.2V */
#define PMU_HVDTS_5V3           ((uint32_t)0x0000001D)          /* Adjust the detection threshold voltage to 5.3V */
#define PMU_HVDTS_5V4           ((uint32_t)0x0000001E)          /* Adjust the detection threshold voltage to 5.4V */
#define PMU_HVDTS_5V5           ((uint32_t)0x0000001F)          /* Adjust the detection threshold voltage to 5.5V(default) */
#define IS_PMU_HVDTS(HVDTS) (((HVDTS) == PMU_HVDTS_2V4) || ((HVDTS) == PMU_HVDTS_2V5) || \
                             ((HVDTS) == PMU_HVDTS_2V6) || ((HVDTS) == PMU_HVDTS_2V7) || \
                             ((HVDTS) == PMU_HVDTS_2V8) || ((HVDTS) == PMU_HVDTS_2V9) || \
                             ((HVDTS) == PMU_HVDTS_3V0) || ((HVDTS) == PMU_HVDTS_3V1) || \
                             ((HVDTS) == PMU_HVDTS_3V2) || ((HVDTS) == PMU_HVDTS_3V3) || \
                             ((HVDTS) == PMU_HVDTS_3V4) || ((HVDTS) == PMU_HVDTS_3V5) || \
                             ((HVDTS) == PMU_HVDTS_3V6) || ((HVDTS) == PMU_HVDTS_3V7) || \
                             ((HVDTS) == PMU_HVDTS_3V8) || ((HVDTS) == PMU_HVDTS_3V9) || \
                             ((HVDTS) == PMU_HVDTS_4V0) || ((HVDTS) == PMU_HVDTS_4V1) || \
                             ((HVDTS) == PMU_HVDTS_4V2) || ((HVDTS) == PMU_HVDTS_4V3) || \
                             ((HVDTS) == PMU_HVDTS_4V4) || ((HVDTS) == PMU_HVDTS_4V5) || \
                             ((HVDTS) == PMU_HVDTS_4V6) || ((HVDTS) == PMU_HVDTS_4V7) || \
                             ((HVDTS) == PMU_HVDTS_4V8) || ((HVDTS) == PMU_HVDTS_4V9) || \
                             ((HVDTS) == PMU_HVDTS_5V0) || ((HVDTS) == PMU_HVDTS_5V1) || \
                             ((HVDTS) == PMU_HVDTS_5V2) || ((HVDTS) == PMU_HVDTS_5V3) || \
                             ((HVDTS) == PMU_HVDTS_5V4) || ((HVDTS) == PMU_HVDTS_5V5))

/*
 * @defgroup Low Voltage Detect Threshold Scaling definition
 */
#define PMU_LVDTS_2V4           ((uint32_t)0x00000000)          /* Adjust the detection threshold voltage to 2.4V */
#define PMU_LVDTS_2V5           ((uint32_t)0x00000001)          /* Adjust the detection threshold voltage to 2.5V */
#define PMU_LVDTS_2V6           ((uint32_t)0x00000002)          /* Adjust the detection threshold voltage to 2.6V */
#define PMU_LVDTS_2V7           ((uint32_t)0x00000003)          /* Adjust the detection threshold voltage to 2.7V */
#define PMU_LVDTS_2V8           ((uint32_t)0x00000004)          /* Adjust the detection threshold voltage to 2.8V */
#define PMU_LVDTS_2V9           ((uint32_t)0x00000005)          /* Adjust the detection threshold voltage to 2.9V(default) */
#define PMU_LVDTS_3V0           ((uint32_t)0x00000006)          /* Adjust the detection threshold voltage to 3.0V */
#define PMU_LVDTS_3V1           ((uint32_t)0x00000007)          /* Adjust the detection threshold voltage to 3.1V */
#define PMU_LVDTS_3V2           ((uint32_t)0x00000008)          /* Adjust the detection threshold voltage to 3.2V */
#define PMU_LVDTS_3V3           ((uint32_t)0x00000009)          /* Adjust the detection threshold voltage to 3.3V */
#define PMU_LVDTS_3V4           ((uint32_t)0x0000000A)          /* Adjust the detection threshold voltage to 3.4V */
#define PMU_LVDTS_3V5           ((uint32_t)0x0000000B)          /* Adjust the detection threshold voltage to 3.5V */
#define PMU_LVDTS_3V6           ((uint32_t)0x0000000C)          /* Adjust the detection threshold voltage to 3.6V */
#define PMU_LVDTS_3V7           ((uint32_t)0x0000000D)          /* Adjust the detection threshold voltage to 3.7V */
#define PMU_LVDTS_3V8           ((uint32_t)0x0000000E)          /* Adjust the detection threshold voltage to 3.8V */
#define PMU_LVDTS_3V9           ((uint32_t)0x0000000F)          /* Adjust the detection threshold voltage to 3.9V */
#define PMU_LVDTS_4V0           ((uint32_t)0x00000010)          /* Adjust the detection threshold voltage to 4.0V */
#define PMU_LVDTS_4V1           ((uint32_t)0x00000011)          /* Adjust the detection threshold voltage to 4.1V */
#define PMU_LVDTS_4V2           ((uint32_t)0x00000012)          /* Adjust the detection threshold voltage to 4.2V */
#define PMU_LVDTS_4V3           ((uint32_t)0x00000013)          /* Adjust the detection threshold voltage to 4.3V */
#define PMU_LVDTS_4V4           ((uint32_t)0x00000014)          /* Adjust the detection threshold voltage to 4.4V */
#define PMU_LVDTS_4V5           ((uint32_t)0x00000015)          /* Adjust the detection threshold voltage to 4.5V */
#define PMU_LVDTS_4V6           ((uint32_t)0x00000016)          /* Adjust the detection threshold voltage to 4.6V */
#define PMU_LVDTS_4V7           ((uint32_t)0x00000017)          /* Adjust the detection threshold voltage to 4.7V */
#define PMU_LVDTS_4V8           ((uint32_t)0x00000018)          /* Adjust the detection threshold voltage to 4.8V */
#define PMU_LVDTS_4V9           ((uint32_t)0x00000019)          /* Adjust the detection threshold voltage to 4.9V */
#define PMU_LVDTS_5V0           ((uint32_t)0x0000001A)          /* Adjust the detection threshold voltage to 5.0V */
#define PMU_LVDTS_5V1           ((uint32_t)0x0000001B)          /* Adjust the detection threshold voltage to 5.1V */
#define PMU_LVDTS_5V2           ((uint32_t)0x0000001C)          /* Adjust the detection threshold voltage to 5.2V */
#define PMU_LVDTS_5V3           ((uint32_t)0x0000001D)          /* Adjust the detection threshold voltage to 5.3V */
#define PMU_LVDTS_5V4           ((uint32_t)0x0000001E)          /* Adjust the detection threshold voltage to 5.4V */
#define PMU_LVDTS_5V5           ((uint32_t)0x0000001F)          /* Adjust the detection threshold voltage to 5.5V */
#define IS_PMU_LVDTS(LVDTS) (((LVDTS) == PMU_LVDTS_2V4) || ((LVDTS) == PMU_LVDTS_2V5) || \
                             ((LVDTS) == PMU_LVDTS_2V6) || ((LVDTS) == PMU_LVDTS_2V7) || \
                             ((LVDTS) == PMU_LVDTS_2V8) || ((LVDTS) == PMU_LVDTS_2V9) || \
                             ((LVDTS) == PMU_LVDTS_3V0) || ((LVDTS) == PMU_LVDTS_3V1) || \
                             ((LVDTS) == PMU_LVDTS_3V2) || ((LVDTS) == PMU_LVDTS_3V3) || \
                             ((LVDTS) == PMU_LVDTS_3V4) || ((LVDTS) == PMU_LVDTS_3V5) || \
                             ((LVDTS) == PMU_LVDTS_3V6) || ((LVDTS) == PMU_LVDTS_3V7) || \
                             ((LVDTS) == PMU_LVDTS_3V8) || ((LVDTS) == PMU_LVDTS_3V9) || \
                             ((LVDTS) == PMU_LVDTS_4V0) || ((LVDTS) == PMU_LVDTS_4V1) || \
                             ((LVDTS) == PMU_LVDTS_4V2) || ((LVDTS) == PMU_LVDTS_4V3) || \
                             ((LVDTS) == PMU_LVDTS_4V4) || ((LVDTS) == PMU_LVDTS_4V5) || \
                             ((LVDTS) == PMU_LVDTS_4V6) || ((LVDTS) == PMU_LVDTS_4V7) || \
                             ((LVDTS) == PMU_LVDTS_4V8) || ((LVDTS) == PMU_LVDTS_4V9) || \
                             ((LVDTS) == PMU_LVDTS_5V0) || ((LVDTS) == PMU_LVDTS_5V1) || \
                             ((LVDTS) == PMU_LVDTS_5V2) || ((LVDTS) == PMU_LVDTS_5V3) || \
                             ((LVDTS) == PMU_LVDTS_5V4) || ((LVDTS) == PMU_LVDTS_5V5))

#define IS_PMU_RC32KFS(RC32KFS) ((RC32KFS) <= 0x3F)

/*
 * @defgroup PMU Flags Mask
 */
#define PMU_FLAG_MASK                   ((uint32_t)0x0000001F)              /* PMU flags mask */
#define PMU_SR_MASK                     ((uint32_t)0x00000060)              /* PMU status register mask */
#define PMU_SR_POS                      ((uint32_t)0x00000005)              /* PMU status register position */

/*
 * @defgroup PMU Flags Definition
 *        Elements values convention: 000000000XXYYYYYb
 *           - YYYYY  : Interrupt source position in the XX register (5bits)
 *           - XX  : Interrupt source register (2bits)
 *                 - 01: LDOSR register
 *                 - 10: WKFR register
 */
#define PMU_FLAG_3V3LDORDY              ((uint32_t)0x00000021)              /* 3.3V LDO voltage ready flag */
#define PMU_FLAG_2V5LDORDY              ((uint32_t)0x00000022)              /* 2.5V LDO voltage ready flag */
#define PMU_FLAG_1V2LDORDY              ((uint32_t)0x00000023)              /* 1.2V LDO voltage ready flag */
#define PMU_FLAG_1V2BLDORDY             ((uint32_t)0x00000024)              /* 1.2V backup LDO voltage ready flag */
#define PMU_FLAG_IWDGWK                 ((uint32_t)0x00000041)              /* IWDG wake-up flag */
#define PMU_FLAG_RTCWK                  ((uint32_t)0x00000043)              /* RTC wake-up flag */
#define PMU_FLAG_PH0WK                  ((uint32_t)0x00000044)              /* PH0 wake-up flag */
#define PMU_FLAG_PH1WK                  ((uint32_t)0x00000045)              /* PH1 wake-up flag */
#define PMU_FLAG_PH2WK                  ((uint32_t)0x00000046)              /* PH2 wake-up flag */
#define PMU_FLAG_PH3WK                  ((uint32_t)0x00000047)              /* PH3 wake-up flag */
#define PMU_FLAG_PH4WK                  ((uint32_t)0x00000048)              /* PH4 wake-up flag */
#define PMU_FLAG_PH5WK                  ((uint32_t)0x00000049)              /* PH5 wake-up flag */
#define PMU_FLAG_PH6WK                  ((uint32_t)0x0000004A)              /* PH6 wake-up flag */
#define PMU_FLAG_PH7WK                  ((uint32_t)0x0000004B)              /* PH7 wake-up flag */
#define PMU_FLAG_PH8WK                  ((uint32_t)0x0000004C)              /* PH8 wake-up flag */
#define PMU_FLAG_PH9WK                  ((uint32_t)0x0000004D)              /* PH9 wake-up flag */
#define PMU_FLAG_FOCUR                  ((uint32_t)0x0000004E)              /* FOCU reset flag */
#define IS_PMU_FLAG(FLAG) (((FLAG) == PMU_FLAG_3V3LDORDY) || ((FLAG) == PMU_FLAG_2V5LDORDY)  || \
                           ((FLAG) == PMU_FLAG_1V2LDORDY) || ((FLAG) == PMU_FLAG_1V2BLDORDY) || \
                           ((FLAG) == PMU_FLAG_IWDGWK)    || ((FLAG) == PMU_FLAG_RTCWK)      || \
                           ((FLAG) == PMU_FLAG_PH0WK)     || ((FLAG) == PMU_FLAG_PH1WK)      || \
                           ((FLAG) == PMU_FLAG_PH2WK)     || ((FLAG) == PMU_FLAG_PH3WK)      || \
                           ((FLAG) == PMU_FLAG_PH4WK)     || ((FLAG) == PMU_FLAG_PH5WK)      || \
                           ((FLAG) == PMU_FLAG_PH6WK)     || ((FLAG) == PMU_FLAG_PH7WK)      || \
                           ((FLAG) == PMU_FLAG_PH8WK)     || ((FLAG) == PMU_FLAG_PH9WK)      || \
                           ((FLAG) == PMU_FLAG_FOCUR))

/*
 * @defgroup PMU Clear Flags
 */
#define PMU_CLEAR_IWDGWKF               ((uint32_t)0x00000001)              /* IWDG wake-up flag clear */
#define PMU_CLEAR_RTCWKF                ((uint32_t)0x00000008)              /* RTC wake-up flag clear */
#define PMU_CLEAR_PH0WKF                ((uint32_t)0x00000010)              /* PH0 wake-up flag clear */
#define PMU_CLEAR_PH1WKF                ((uint32_t)0x00000020)              /* PH1 wake-up flag clear */
#define PMU_CLEAR_PH2WKF                ((uint32_t)0x00000040)              /* PH2 wake-up flag clear */
#define PMU_CLEAR_PH3WKF                ((uint32_t)0x00000080)              /* PH3 wake-up flag clear */
#define PMU_CLEAR_PH4WKF                ((uint32_t)0x00000100)              /* PH4 wake-up flag clear */
#define PMU_CLEAR_PH5WKF                ((uint32_t)0x00000200)              /* PH5 wake-up flag clear */
#define PMU_CLEAR_PH6WKF                ((uint32_t)0x00000400)              /* PH6 wake-up flag clear */
#define PMU_CLEAR_PH7WKF                ((uint32_t)0x00000800)              /* PH7 wake-up flag clear */
#define PMU_CLEAR_PH8WKF                ((uint32_t)0x00001000)              /* PH8 wake-up flag clear */
#define PMU_CLEAR_PH9WKF                ((uint32_t)0x00002000)              /* PH9 wake-up flag clear */
#define PMU_CLEAR_FOCURF                ((uint32_t)0x00004000)              /* FOCU reset flag clear */
#define IS_PMU_CLEAR(CLEAR) (((CLEAR) == PMU_CLEAR_IWDGWKF) || ((CLEAR) == PMU_CLEAR_RTCWKF) || \
                             ((CLEAR) == PMU_CLEAR_PH0WKF)  || ((CLEAR) == PMU_CLEAR_PH1WKF) || \
                             ((CLEAR) == PMU_CLEAR_PH2WKF)  || ((CLEAR) == PMU_CLEAR_PH3WKF) || \
                             ((CLEAR) == PMU_CLEAR_PH4WKF)  || ((CLEAR) == PMU_CLEAR_PH5WKF) || \
                             ((CLEAR) == PMU_CLEAR_PH6WKF)  || ((CLEAR) == PMU_CLEAR_PH7WKF) || \
                             ((CLEAR) == PMU_CLEAR_PH8WKF)  || ((CLEAR) == PMU_CLEAR_PH9WKF) || \
                             ((CLEAR) == PMU_CLEAR_FOCURF))

/*
 * @brief Function declaration
 */
void PMU_PowerModeConfig(PMUPowerMode_TypeDef PowerMode);
PMUPowerMode_TypeDef PMU_GetPowerModeStatus(void);
void PMU_WakeUpSourceCmd(PMUWKSource_TypeDef WakeUpSource, EnState NewState);
void PMU_BLDO1v2VOLSca(uint32_t VoltageValue);
void PMU_LDO1v2VOLSca(uint32_t VoltageValue);
void PMU_Refer1v2VOLSca(uint32_t VoltageValue);
void PMU_Refer1v2Cmd(EnState NewState);
void PMU_LDO1v2Cmd(EnState NewState);
void PMU_LDO2v5VOLSca(uint32_t VoltageValue);
void PMU_LDO2v5Cmd(EnState NewState);
void PMU_LDO3v3VOLSca(uint32_t VoltageValue);
void PMU_LDO3v3BypassCmd(EnState NewState);
void PMU_LDO3v3Cmd(EnState NewState);
void PMU_LowVolResetCmd(EnState NewState);
void PMU_HighVolDetectCmd(EnState NewState);
void PMU_HighVolDetectThresholdSca(uint32_t VoltageValue);
void PMU_LowVolDetectCmd(EnState NewState);
void PMU_LowVolDetectThresholdSca(uint32_t VoltageValue);
void PMU_RC16MCmd(EnState NewState);
void PMU_RC32KFrequencySca(uint32_t ClockFrequency);
FlagStatus PMU_GetFlagStatus(uint32_t PMU_FLAG);
void PMU_ClearFlag(uint32_t PMU_FLAG);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
