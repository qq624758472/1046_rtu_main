/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):    Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	 as32x601_cmu.h
 * Author:           ANSILIC APPLICATION GROUP
 * Version:          V1.0
 * Date:             2024/08/20
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/20     1.0     build this module
 * Description:     This file contains all the functions prototypes for the CMU firmware library.
 */

#ifndef AS32X601_CMU_H
#define AS32X601_CMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_cmu_regs.h"

/*
 * @brief  Use by parameter examine.
 */
#define IS_CMU_ALL_PERIPH(PERIPH) (((PERIPH) == CMU_FIRC) || ((PERIPH) == CMU_PLLQ) || \
                                   ((PERIPH) == CMU_PLLR) || ((PERIPH) == CMU_OSC))

/*
 * @defgroup CMU Flags
 */
#define CMU_FLAG_WORK                   ((uint32_t)0x00000010)              /* Working condition */
#define CMU_FLAG_CHCDONE                ((uint32_t)0x00000008)              /* Status detection */
#define CMU_FLAG_LOSSCLK                ((uint32_t)0x00000004)              /* Clock loss status */
#define CMU_FLAG_FHH                    ((uint32_t)0x00000002)              /* State where the frequency is greater than the high-frequency reference threshold */
#define CMU_FLAG_FLL                    ((uint32_t)0x00000001)              /* Frequency below the low frequency reference threshold state */

#define IS_CMU_FLAG(FLAG) (((FLAG) == CMU_FLAG_WORK)    || ((FLAG) == CMU_FLAG_CHCDONE) || \
                           ((FLAG) == CMU_FLAG_LOSSCLK) || ((FLAG) == CMU_FLAG_FHH)     || \
                           ((FLAG) == CMU_FLAG_FLL))

/*
 * @defgroup CMU Clear Flags
 */
#define CMU_CLEAR_FLL                   ((uint32_t)0x00000001)              /* Frequency below the low frequency reference threshold state clear */
#define CMU_CLEAR_FHH                   ((uint32_t)0x00000002)              /* State where the frequency is greater than the high-frequency reference threshold clear */
#define IS_CMU_CLEAR(CLEAR) (((CLEAR) == CMU_CLEAR_FLL) || ((CLEAR) == CMU_CLEAR_FHH))

/*
 * @brief Function declaration
 */
void CMU_Cmd(CMU_TypeDef *CMUx, FunctionalState NewState);
void CMU_SetWinLen(CMU_TypeDef *CMUx, uint32_t WindowLength);
void CMU_SetReferenceThreshold(CMU_TypeDef *CMUx, uint32_t HighThreshold, uint32_t LowThreshold);
FlagStatus CMU_GetFlagStatus(CMU_TypeDef *CMUx, uint32_t CMU_FLAG);
void CMU_ClearFlag(CMU_TypeDef *CMUx, uint32_t CMU_FLAG);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
