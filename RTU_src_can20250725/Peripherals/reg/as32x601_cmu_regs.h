/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_cmu_regs.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:            2024/08/20
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/20     1.0     build this module
 * Description:     This file contains all the register correlation defines for the CMU firmware library.
 */

#ifndef AS32X601_CMU_REG_H
#define AS32X601_CMU_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601.h"
#include "as32x601_addrmap.h"

/*
 * @brief CMU registers structure
 */
typedef struct
{
    __IO uint32_t CR;           /* CMU_cmuCR        Control register,                           Address offset: 0x00 */
    __IO uint32_t CCR;          /* CMU_cmuRCCR      Counter configuration register,             Address offset: 0x04 */
    __IO uint32_t HTCR;         /* CMU_cmuHTCR      High threshold configuration register,      Address offset: 0x08 */
    __IO uint32_t LTCR;         /* CMU_cmuLTCR      Low threshold configuration register,       Address offset: 0x0C */
    __IO uint32_t SR;           /* CMU_cmuSR        Status register,                            Address offset: 0x10 */
} CMU_TypeDef;

/*
 * @brief CMU peripheral declaration
 */
#define CMU_FIRC    ((CMU_TypeDef *)CMU0_BASE)
#define CMU_PLLQ    ((CMU_TypeDef *)CMU1_BASE)
#define CMU_PLLR    ((CMU_TypeDef *)CMU2_BASE)
#define CMU_OSC     ((CMU_TypeDef *)CMU3_BASE)

/******************  Bits definition for CMU_CR register  *****************/
#define CMU_CR_MODE_DPos            (0U)
#define CMU_CR_MODE_Pos             CMU_CR_MODE_DPos
#define CMU_CR_MODE_Msk             (0x7UL << CMU_CR_MODE_Pos)                  /* 0x00000007 */
#define CMU_CR_MODE                 CMU_CR_MODE_Msk                             /* MODE[2:0] bits (Clock monitoring enabled) */

/******************  Bits definition for CMU_CCR register  *****************/
#define CMU_CCR_WINLEN_DPos         (0U)
#define CMU_CCR_WINLEN_Pos          CMU_CCR_WINLEN_DPos
#define CMU_CCR_WINLEN_Msk          (0xFFFFFFUL << CMU_CCR_WINLEN_Pos)          /* 0x00FFFFFF */
#define CMU_CCR_WINLEN              CMU_CCR_WINLEN_Msk                          /* WINLEN[23:0] bits (Reference Count Window Length) */

/******************  Bits definition for CMU_HTCR register  *****************/
#define CMU_HTCR_HFREF_DPos         (0U)
#define CMU_HTCR_HFREF_Pos          CMU_HTCR_HFREF_DPos
#define CMU_HTCR_HFREF_Msk          (0xFFFFFFUL << CMU_HTCR_HFREF_Pos)          /* 0x00FFFFFF */
#define CMU_HTCR_HFREF              CMU_HTCR_HFREF_Msk                          /* HFREF[23:0] bits (High frequency reference threshold) */

/******************  Bits definition for CMU_LTCR register  *****************/
#define CMU_LTCR_LFREF_DPos         (0U)
#define CMU_LTCR_LFREF_Pos          CMU_LTCR_LFREF_DPos
#define CMU_LTCR_LFREF_Msk          (0xFFFFFFUL << CMU_LTCR_LFREF_Pos)          /* 0x00FFFFFF */
#define CMU_LTCR_LFREF              CMU_LTCR_LFREF_Msk                          /* LFREF[23:0] bits (Low frequency reference threshold) */

/******************  Bits definition for CMU_SR register  *****************/
#define CMU_SR_FLL_DPos             (0U)
#define CMU_SR_FLL_Pos              CMU_SR_FLL_DPos
#define CMU_SR_FLL_Msk              (0x1UL << CMU_SR_FLL_Pos)                   /* 0x00000001 */
#define CMU_SR_FLL                  CMU_SR_FLL_Msk                              /* Frequency below the low frequency reference threshold state */

#define CMU_SR_FHH_DPos             (1U)
#define CMU_SR_FHH_Pos              CMU_SR_FHH_DPos
#define CMU_SR_FHH_Msk              (0x1UL << CMU_SR_FHH_Pos)                   /* 0x00000002 */
#define CMU_SR_FHH                  CMU_SR_FHH_Msk                              /* State where the frequency is greater than the high-frequency reference threshold */

#define CMU_SR_LOSSCLK_DPos         (2U)
#define CMU_SR_LOSSCLK_Pos          CMU_SR_LOSSCLK_DPos
#define CMU_SR_LOSSCLK_Msk          (0x1UL << CMU_SR_LOSSCLK_Pos)               /* 0x00000004 */
#define CMU_SR_LOSSCLK              CMU_SR_LOSSCLK_Msk                          /* Clock loss status */

#define CMU_SR_CHCDONE_DPos         (3U)
#define CMU_SR_CHCDONE_Pos          CMU_SR_CHCDONE_DPos
#define CMU_SR_CHCDONE_Msk          (0x1UL << CMU_SR_CHCDONE_Pos)               /* 0x00000008 */
#define CMU_SR_CHCDONE              CMU_SR_CHCDONE_Msk                          /* Status Detection */

#define CMU_SR_WORK_DPos            (4U)
#define CMU_SR_WORK_Pos             CMU_SR_WORK_DPos
#define CMU_SR_WORK_Msk             (0x1UL << CMU_SR_WORK_Pos)                  /* 0x00000010 */
#define CMU_SR_WORK                 CMU_SR_WORK_Msk                             /* Working condition */

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
