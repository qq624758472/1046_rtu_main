/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_dac.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:			2024/9/2
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/9/2      1.0     build this module
 * Description:     This file contains all the functions prototypes for the ADC firmware library.
 */
#ifndef AS32X601_DAC_H
#define AS32X601_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_dac_regs.h"

/*
 * @brief  Use by parameter examine.
 */
#define IS_DAC_ALL_PERIPH(PERIPH) (((PERIPH) == DAC0) || \
                                   ((PERIPH) == DAC1))

/*
 * @brief DAC Init Structure definition
 */
typedef struct
{
    FunctionalState DAC_Enable;                                         /* Enable/disable DAC function */
    uint32_t        DAC_Mode;                                           /* DAC mode selection */
    uint32_t        DAC_VrefMode;                                       /* DAC reference voltage selection */
    uint32_t        DAC_ClockDivider;                                   /* DAC clock divide ratio */
} DAC_InitTypeDef;

/*
 * @brief DAC Comparator Structure definition
 */
typedef struct
{
    FunctionalState CMP_Enable;                                          /* Enable/disable comparator function */
    uint32_t        CMP_Mode;                                            /* Comparator mode selection */
    uint32_t        CMP_Hysteresis;                                      /* Comparator hysteresis selection */
}DAC_CMPTypedef;

/*
 * @brief DAC Enable selection
 */
#define DAC_ENABLE                                  ((uint32_t)0x00000001)          /* DAC enable */
#define DAC_DISABLE                                 ((uint32_t)0x00000000)          /* DAC disable */
#define IS_DAC_EN(EN)                       (((EN) == DAC_ENABLE) || ((EN) == DAC_DISABLE))

/*
 * @brief DAC Mode selection
 */
#define DAC_MD_BUFFER_OUT                           ((uint32_t)0x00000000)          /* DAC output buffer mode */
#define DAC_MD_BYPASS_OUT                           ((uint32_t)0x00000001)          /* DAC bypass output mode */
#define IS_DAC_MD(MD)                      (((MD) == DAC_MD_BUFFER_OUT) || ((MD) == DAC_MD_BYPASS_OUT))

/*
 * @brief DAC Reference Voltage selection
 */
#define DAC_VREF_MD_VREFP                           ((uint32_t)0x00000000)          /* DAC reference VREFP selection */
#define DAC_VREF_MD_AVD                             ((uint32_t)0x00000001)          /* DAC reference AVD selection */
#define IS_DAC_VREF_MD(MD)                 (((MD) == DAC_VREF_MD_VREFP) || ((MD) == DAC_VREF_MD_AVD))

/*
 * @brief DAC Clock Frequency Division Coefficient Selection
 */
#define IS_DAC_CLK_DIV(CLKDIV)  ((CLKDIV>=0x00)&&(CLKDIV<=0xff))

/*
 * @brief DAC Comparator Enable selection
 */
#define DAC_CMP_ENABLE                              ((uint32_t)0x00000001)          /* DAC comparator enable */
#define DAC_CMP_DISABLE                             ((uint32_t)0x00000000)          /* DAC comparator disable */
#define IS_DAC_CMP_EN(EN)                  (((EN) == DAC_CMP_ENABLE) || ((EN) == DAC_CMP_DISABLE))

/*
 * @brief DAC Comparator Mode selection
 */
#define DAC_CMP_MD_DAC0                             ((uint32_t)0x00000000)          /* DAC comparator mode selection for DAC0 */
#define DAC_CMP_MD_CMP_P                            ((uint32_t)0x00000001)          /* DAC comparator mode selection for CMP_P */
#define IS_DAC_CMP_MD(MD)                 (((MD) == DAC_CMP_MD_DAC0) || ((MD) == DAC_CMP_MD_CMP_P))

/*
 * @brief DAC Comparator Hysteresis Voltage Selection Signal. Unit: mV
 */
#define DAC_CMP_HYS_0                               ((uint32_t)0x00000000)          /* DAC comparator hysteresis voltage selection 0mV */
#define DAC_CMP_HYS_3MV3                            ((uint32_t)0x00000001)          /* DAC comparator hysteresis voltage selection 3.3mV */
#define DAC_CMP_HYS_16MV5                           ((uint32_t)0x00000002)          /* DAC comparator hysteresis voltage selection 16.5mV */
#define DAC_CMP_HYS_33                              ((uint32_t)0x00000003)          /* DAC comparator hysteresis voltage selection 33mV */
#define DAC_CMP_HYS_66                              ((uint32_t)0x00000004)          /* DAC comparator hysteresis voltage selection 66mV */
#define DAC_CMP_HYS_165                             ((uint32_t)0x00000005)          /* DAC comparator hysteresis voltage selection 165mV */
#define DAC_CMP_HYS_330                             ((uint32_t)0x00000006)          /* DAC comparator hysteresis voltage selection 330mV */
#define IS_DAC_CMP_HYS(HYS)               (((HYS) == DAC_CMP_HYS_0) || \
                                           ((HYS) == DAC_CMP_HYS_3MV3) || \
                                           ((HYS) == DAC_CMP_HYS_16MV5) || \
                                           ((HYS) ==DAC_CMP_HYS_33) || \
                                           ((HYS) == DAC_CMP_HYS_66) || \
                                           ((HYS) == DAC_CMP_HYS_165) || \
                                           ((HYS) == DAC_CMP_HYS_330))

/*
 * @brief Function declaration
 */
void DAC_StructInit(DAC_InitTypeDef * const DAC_InitStruct);
void DAC_Init(DAC_TypeDef *DACx, const DAC_InitTypeDef * const DAC_InitStruct);
void DAC_Cmd(DAC_TypeDef *DACx, FunctionalState NewState);
void DAC_SetValue(DAC_TypeDef *DACx, uint16_t DAC_Value);
void DAC_CMP_StructInit(DAC_CMPTypedef * const DAC_CMPStruct);
void DAC_CMP_Init(DAC_TypeDef *DACx, const DAC_CMPTypedef * const DAC_CMPStruct);
void DAC_CMP_Cmd(DAC_TypeDef *DACx, FunctionalState NewState);
uint8_t DAC_CMP_GetResult(DAC_TypeDef *DACx);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
