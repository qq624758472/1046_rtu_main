/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_rtc_regs.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:            2024/09/09
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/09/09     1.0     build this module
 * Description:     This file contains all the register correlation defines for the RTC firmware library.
 */

#ifndef AS32X601_RTC_REG_H
#define AS32X601_RTC_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601.h"
#include "as32x601_addrmap.h"

/*
 * @brief CRC registers structure
 */
typedef struct
{
    __IO uint32_t TR;           /* RRTC_TIME    RTC time register,              Address offset: 0x00 */
    __IO uint32_t DR;           /* RRTC_DATE    RTC date register,              Address offset: 0x04 */
    __IO uint32_t ALRMTR;       /* RRTC_TALRM   RTC alarm time register,        Address offset: 0x08 */
    __IO uint32_t ALRMDR;       /* RRTC_DALRM   RTC alarm date register,        Address offset: 0x0C */
    __IO uint32_t CR;           /* RRTC_CTRL    RTC control register,           Address offset: 0x10 */
    __IO uint32_t WUCR;         /* RRTC_WKPC    RTC wake-up control register,   Address offset: 0x14 */
} RTC_TypeDef;

/*
 * @brief RTC peripheral declaration
 */
#define RTC     ((RTC_TypeDef *)RTC_BASE)

/******************  Bits definition for RTC_TR register  *****************/
#define RTC_TR_TOS_DPos             (0U)
#define RTC_TR_TOS_Pos              RTC_TR_TOS_DPos
#define RTC_TR_TOS_Msk              (0xFUL << RTC_TR_TOS_Pos)                   /* 0x0000000F */
#define RTC_TR_TOS                  RTC_TR_TOS_Msk                              /* TOS[3:0] bits (tenth of a second) */

#define RTC_TR_S_DPos               (4U)
#define RTC_TR_SU_Pos               RTC_TR_S_DPos
#define RTC_TR_SU_Msk               (0xFUL << RTC_TR_SU_Pos)                    /* 0x000000F0 */
#define RTC_TR_SU                   RTC_TR_SU_Msk                               /* SU[3:0] bits (Second units) */

#define RTC_TR_TS_DPos              (8U)
#define RTC_TR_ST_Pos               RTC_TR_TS_DPos
#define RTC_TR_ST_Msk               (0x7UL << RTC_TR_ST_Pos)                    /* 0x00000700 */
#define RTC_TR_ST                   RTC_TR_ST_Msk                               /* ST[2:0] bits (Second tens) */

#define RTC_TR_M_DPos               (11U)
#define RTC_TR_MNU_Pos              RTC_TR_M_DPos
#define RTC_TR_MNU_Msk              (0xFUL << RTC_TR_MNU_Pos)                   /* 0x00007800 */
#define RTC_TR_MNU                  RTC_TR_MNU_Msk                              /* MNU[3:0] bits (Minute units) */

#define RTC_TR_TM_DPos              (15U)
#define RTC_TR_MNT_Pos              RTC_TR_TM_DPos
#define RTC_TR_MNT_Msk              (0x7UL << RTC_TR_MNT_Pos)                   /* 0x00038000 */
#define RTC_TR_MNT                  RTC_TR_MNT_Msk                              /* MNT[2:0] bits (Minute tens) */

#define RTC_TR_H_DPos               (18U)
#define RTC_TR_HU_Pos               RTC_TR_H_DPos
#define RTC_TR_HU_Msk               (0xFUL << RTC_TR_HU_Pos)                    /* 0x003C0000 */
#define RTC_TR_HU                   RTC_TR_HU_Msk                               /* HU[3:0] bits (Hour units) */

#define RTC_TR_TH_DPos              (22U)
#define RTC_TR_HT_Pos               RTC_TR_TH_DPos
#define RTC_TR_HT_Msk               (0x3UL << RTC_TR_HT_Pos)                    /* 0x00C00000 */
#define RTC_TR_HT                   RTC_TR_HT_Msk                               /* HT[1:0] bits (Hour tens) */

#define RTC_TR_DOW_DPos             (24U)
#define RTC_TR_WDU_Pos              RTC_TR_DOW_DPos
#define RTC_TR_WDU_Msk              (0x7UL << RTC_TR_WDU_Pos)                   /* 0x07000000 */
#define RTC_TR_WDU                  RTC_TR_WDU_Msk                              /* WDU[2:0] bits (Week day units) */


/******************  Bits definition for RTC_DR register  *****************/
#define RTC_DR_D_DPos               (0U)
#define RTC_DR_DU_Pos               RTC_DR_D_DPos
#define RTC_DR_DU_Msk               (0xFUL << RTC_DR_DU_Pos)                    /* 0x0000000F */
#define RTC_DR_DU                   RTC_DR_DU_Msk                               /* DU[3:0] bits (Date units) */

#define RTC_DR_TD_DPos              (4U)
#define RTC_DR_DT_Pos               RTC_DR_TD_DPos
#define RTC_DR_DT_Msk               (0x3UL << RTC_DR_DT_Pos)                    /* 0x00000030 */
#define RTC_DR_DT                   RTC_DR_DT_Msk                               /* DT[1:0] bits (Date tens) */

#define RTC_DR_M_DPos               (6U)
#define RTC_DR_MU_Pos               RTC_DR_M_DPos
#define RTC_DR_MU_Msk               (0xFUL << RTC_DR_MU_Pos)                    /* 0x000003C0 */
#define RTC_DR_MU                   RTC_DR_MU_Msk                               /* MU[3:0] bits (Month units) */

#define RTC_DR_TM_DPos              (10U)
#define RTC_DR_MT_Pos               RTC_DR_TM_DPos
#define RTC_DR_MT_Msk               (0x1UL << RTC_DR_MT_Pos)                    /* 0x00000400 */
#define RTC_DR_MT                   RTC_DR_MT_Msk                               /* Month tens */

#define RTC_DR_Y_DPos               (11U)
#define RTC_DR_YU_Pos               RTC_DR_Y_DPos
#define RTC_DR_YU_Msk               (0xFUL << RTC_DR_YU_Pos)                    /* 0x00007800 */
#define RTC_DR_YU                   RTC_DR_YU_Msk                               /* YU[3:0] bits (Year units) */

#define RTC_DR_TY_DPos              (15U)
#define RTC_DR_YT_Pos               RTC_DR_TY_DPos
#define RTC_DR_YT_Msk               (0xFUL << RTC_DR_YT_Pos)                    /* 0x00078000 */
#define RTC_DR_YT                   RTC_DR_YT_Msk                               /* YT[3:0] bits (Year tens) */

#define RTC_DR_C_DPos               (19U)
#define RTC_DR_CU_Pos               RTC_DR_C_DPos
#define RTC_DR_CU_Msk               (0xFUL << RTC_DR_CU_Pos)                    /* 0x00780000 */
#define RTC_DR_CU                   RTC_DR_CU_Msk                               /* CU[3:0] bits (Century units) */

#define RTC_DR_TC_DPos              (23U)
#define RTC_DR_CT_Pos               RTC_DR_TC_DPos
#define RTC_DR_CT_Msk               (0xFUL << RTC_DR_CT_Pos)                    /* 0x07800000 */
#define RTC_DR_CT                   RTC_DR_CT_Msk                               /* CT[3:0] bits (Century tens) */

/******************  Bits definition for RTC_ALRMTR register  *****************/
#define RTC_ALRMTR_TOS_DPos         (0U)
#define RTC_ALRMTR_TOS_Pos          RTC_ALRMTR_TOS_DPos
#define RTC_ALRMTR_TOS_Msk          (0xFUL << RTC_ALRMTR_TOS_Pos)               /* 0x0000000F */
#define RTC_ALRMTR_TOS              RTC_ALRMTR_TOS_Msk                          /* TOS[3:0] bits (tenth of a second) */

#define RTC_ALRMTR_S_DPos           (4U)
#define RTC_ALRMTR_SU_Pos           RTC_ALRMTR_S_DPos
#define RTC_ALRMTR_SU_Msk           (0xFUL << RTC_ALRMTR_SU_Pos)                /* 0x000000F0 */
#define RTC_ALRMTR_SU               RTC_ALRMTR_SU_Msk                           /* SU[3:0] bits (Second units) */

#define RTC_ALRMTR_TS_DPos          (8U)
#define RTC_ALRMTR_ST_Pos           RTC_ALRMTR_TS_DPos
#define RTC_ALRMTR_ST_Msk           (0x7UL << RTC_ALRMTR_ST_Pos)                /* 0x00000700 */
#define RTC_ALRMTR_ST               RTC_ALRMTR_ST_Msk                           /* ST[2:0] bits (Second tens) */

#define RTC_ALRMTR_M_DPos           (11U)
#define RTC_ALRMTR_MNU_Pos          RTC_ALRMTR_M_DPos
#define RTC_ALRMTR_MNU_Msk          (0xFUL << RTC_ALRMTR_MNU_Pos)               /* 0x00007800 */
#define RTC_ALRMTR_MNU              RTC_ALRMTR_MNU_Msk                          /* MNU[3:0] bits (Minute units) */

#define RTC_ALRMTR_TM_DPos          (15U)
#define RTC_ALRMTR_MNT_Pos          RTC_ALRMTR_TM_DPos
#define RTC_ALRMTR_MNT_Msk          (0x7UL << RTC_ALRMTR_MNT_Pos)               /* 0x00038000 */
#define RTC_ALRMTR_MNT              RTC_ALRMTR_MNT_Msk                          /* MNT[2:0] bits (Minute tens) */

#define RTC_ALRMTR_H_DPos           (18U)
#define RTC_ALRMTR_HU_Pos           RTC_ALRMTR_H_DPos
#define RTC_ALRMTR_HU_Msk           (0xFUL << RTC_ALRMTR_HU_Pos)                /* 0x003C0000 */
#define RTC_ALRMTR_HU               RTC_ALRMTR_HU_Msk                           /* HU[3:0] bits (Hour units) */

#define RTC_ALRMTR_TH_DPos          (22U)
#define RTC_ALRMTR_HT_Pos           RTC_ALRMTR_TH_DPos
#define RTC_ALRMTR_HT_Msk           (0x3UL << RTC_ALRMTR_HT_Pos)                /* 0x00C00000 */
#define RTC_ALRMTR_HT               RTC_ALRMTR_HT_Msk                           /* HT[1:0] bits (Hour tens) */

#define RTC_ALRMTR_DOW_DPos         (24U)
#define RTC_ALRMTR_WDU_Pos          RTC_ALRMTR_DOW_DPos
#define RTC_ALRMTR_WDU_Msk          (0x7UL << RTC_ALRMTR_WDU_Pos)               /* 0x07000000 */
#define RTC_ALRMTR_WDU              RTC_ALRMTR_WDU_Msk                          /* WDU[2:0] bits (Week day units) */

#define RTC_ALRMTR_CTOS_DPos        (27U)
#define RTC_ALRMTR_TOSCE_Pos        RTC_ALRMTR_CTOS_DPos
#define RTC_ALRMTR_TOSCE_Msk        (0x1UL << RTC_ALRMTR_TOSCE_Pos)             /* 0x08000000 */
#define RTC_ALRMTR_TOSCE            RTC_ALRMTR_TOSCE_Msk                        /* One tenth of a second comparison enable */

#define RTC_ALRMTR_CS_DPos          (28U)
#define RTC_ALRMTR_SCE_Pos          RTC_ALRMTR_CS_DPos
#define RTC_ALRMTR_SCE_Msk          (0x1UL << RTC_ALRMTR_SCE_Pos)               /* 0x10000000 */
#define RTC_ALRMTR_SCE              RTC_ALRMTR_SCE_Msk                          /* Second comparison enable */

#define RTC_ALRMTR_CM_DPos          (29U)
#define RTC_ALRMTR_MCE_Pos          RTC_ALRMTR_CM_DPos
#define RTC_ALRMTR_MCE_Msk          (0x1UL << RTC_ALRMTR_MCE_Pos)               /* 0x20000000 */
#define RTC_ALRMTR_MCE              RTC_ALRMTR_MCE_Msk                          /* Minute comparison enable */

#define RTC_ALRMTR_CH_DPos          (30U)
#define RTC_ALRMTR_HCE_Pos          RTC_ALRMTR_CH_DPos
#define RTC_ALRMTR_HCE_Msk          (0x1UL << RTC_ALRMTR_HCE_Pos)               /* 0x40000000 */
#define RTC_ALRMTR_HCE              RTC_ALRMTR_HCE_Msk                          /* Hour comparison enable */

#define RTC_ALRMTR_CDOW_DPos        (31U)
#define RTC_ALRMTR_WDCE_Pos         RTC_ALRMTR_CDOW_DPos
#define RTC_ALRMTR_WDCE_Msk         (0x1UL << RTC_ALRMTR_WDCE_Pos)              /* 0x80000000 */
#define RTC_ALRMTR_WDCE             RTC_ALRMTR_WDCE_Msk                         /* Week day comparison enable */

/******************  Bits definition for RTC_ALRMDR register  *****************/
#define RTC_ALRMDR_D_DPos           (0U)
#define RTC_ALRMDR_DU_Pos           RTC_ALRMDR_D_DPos
#define RTC_ALRMDR_DU_Msk           (0xFUL << RTC_ALRMDR_DU_Pos)                /* 0x0000000F */
#define RTC_ALRMDR_DU               RTC_ALRMDR_DU_Msk                           /* DU[3:0] bits (Date units) */

#define RTC_ALRMDR_TD_DPos          (4U)
#define RTC_ALRMDR_DT_Pos           RTC_ALRMDR_TD_DPos
#define RTC_ALRMDR_DT_Msk           (0x3UL << RTC_ALRMDR_DT_Pos)                /* 0x00000030 */
#define RTC_ALRMDR_DT               RTC_ALRMDR_DT_Msk                           /* DT[1:0] bits (Date tens) */

#define RTC_ALRMDR_M_DPos           (6U)
#define RTC_ALRMDR_MU_Pos           RTC_ALRMDR_M_DPos
#define RTC_ALRMDR_MU_Msk           (0xFUL << RTC_ALRMDR_MU_Pos)                /* 0x000003C0 */
#define RTC_ALRMDR_MU               RTC_ALRMDR_MU_Msk                           /* MU[3:0] bits (Month units) */

#define RTC_ALRMDR_TM_DPos          (10U)
#define RTC_ALRMDR_MT_Pos           RTC_ALRMDR_TM_DPos
#define RTC_ALRMDR_MT_Msk           (0x1UL << RTC_ALRMDR_MT_Pos)                /* 0x00000400 */
#define RTC_ALRMDR_MT               RTC_ALRMDR_MT_Msk                           /* Month tens */

#define RTC_ALRMDR_Y_DPos           (11U)
#define RTC_ALRMDR_YU_Pos           RTC_ALRMDR_Y_DPos
#define RTC_ALRMDR_YU_Msk           (0xFUL << RTC_ALRMDR_YU_Pos)                /* 0x00007800 */
#define RTC_ALRMDR_YU               RTC_ALRMDR_YU_Msk                           /* YU[3:0] bits (Year units) */

#define RTC_ALRMDR_TY_DPos          (15U)
#define RTC_ALRMDR_YT_Pos           RTC_ALRMDR_TY_DPos
#define RTC_ALRMDR_YT_Msk           (0xFUL << RTC_ALRMDR_YT_Pos)                /* 0x00078000 */
#define RTC_ALRMDR_YT               RTC_ALRMDR_YT_Msk                           /* YT[3:0] bits (Year tens) */

#define RTC_ALRMDR_C_DPos           (19U)
#define RTC_ALRMDR_CU_Pos           RTC_ALRMDR_C_DPos
#define RTC_ALRMDR_CU_Msk           (0xFUL << RTC_ALRMDR_CU_Pos)                /* 0x00780000 */
#define RTC_ALRMDR_CU               RTC_ALRMDR_CU_Msk                           /* CU[3:0] bits (Century units) */

#define RTC_ALRMDR_TC_DPos          (23U)
#define RTC_ALRMDR_CT_Pos           RTC_ALRMDR_TC_DPos
#define RTC_ALRMDR_CT_Msk           (0xFUL << RTC_ALRMDR_CT_Pos)                /* 0x07800000 */
#define RTC_ALRMDR_CT               RTC_ALRMDR_CT_Msk                           /* CT[3:0] bits (Century tens) */

#define RTC_ALRMDR_CD_DPos          (27U)
#define RTC_ALRMDR_DCE_Pos          RTC_ALRMDR_CD_DPos
#define RTC_ALRMDR_DCE_Msk          (0x1UL << RTC_ALRMDR_DCE_Pos)               /* 0x08000000 */
#define RTC_ALRMDR_DCE              RTC_ALRMDR_DCE_Msk                          /* Date comparison enable */

#define RTC_ALRMDR_CM_DPos          (28U)
#define RTC_ALRMDR_MCE_Pos          RTC_ALRMDR_CM_DPos
#define RTC_ALRMDR_MCE_Msk          (0x1UL << RTC_ALRMDR_MCE_Pos)               /* 0x10000000 */
#define RTC_ALRMDR_MCE              RTC_ALRMDR_MCE_Msk                          /* Month comparison enable */

#define RTC_ALRMDR_CY_DPos          (29U)
#define RTC_ALRMDR_YCE_Pos          RTC_ALRMDR_CY_DPos
#define RTC_ALRMDR_YCE_Msk          (0x1UL << RTC_ALRMDR_YCE_Pos)               /* 0x20000000 */
#define RTC_ALRMDR_YCE              RTC_ALRMDR_YCE_Msk                          /* Year comparison enable */

#define RTC_ALRMDR_CC_DPos          (30U)
#define RTC_ALRMDR_CCE_Pos          RTC_ALRMDR_CC_DPos
#define RTC_ALRMDR_CCE_Msk          (0x1UL << RTC_ALRMDR_CCE_Pos)               /* 0x40000000 */
#define RTC_ALRMDR_CCE              RTC_ALRMDR_CCE_Msk                          /* Century comparison enable */

/******************  Bits definition for RTC_CR register  *****************/
#define RTC_CR_DIV_DPos             (0U)
#define RTC_CR_DIV_Pos              RTC_CR_DIV_DPos
#define RTC_CR_DIV_Msk              (0x7FFFFFFUL << RTC_CR_DIV_Pos)             /* 0x07FFFFFF */
#define RTC_CR_DIV                  RTC_CR_DIV_Msk                              /* RTC clock divider */

#define RTC_CR_BTOS_DPos            (27U)
#define RTC_CR_TOSB_Pos             RTC_CR_BTOS_DPos
#define RTC_CR_TOSB_Msk             (0x1UL << RTC_CR_TOSB_Pos)                  /* 0x08000000 */
#define RTC_CR_TOSB                 RTC_CR_TOSB_Msk                             /* One tenth of a second blocking position */

#define RTC_CR_INTE_DPos            (29U)
#define RTC_CR_IE_Pos               RTC_CR_INTE_DPos
#define RTC_CR_IE_Msk               (0x1UL << RTC_CR_IE_Pos)                    /* 0x20000000 */
#define RTC_CR_IE                   RTC_CR_IE_Msk                               /* Interrupt enable position */

#define RTC_CR_ALRM_DPos            (30U)
#define RTC_CR_ALRMT_Pos            RTC_CR_ALRM_DPos
#define RTC_CR_ALRMT_Msk            (0x1UL << RTC_CR_ALRMT_Pos)                 /* 0x40000000 */
#define RTC_CR_ALRMT                RTC_CR_ALRMT_Msk                            /* Alarm trigger position */

#define RTC_CR_EN_DPos              (31U)
#define RTC_CR_EN_Pos               RTC_CR_EN_DPos
#define RTC_CR_EN_Msk               (0x1UL << RTC_CR_EN_Pos)                    /* 0x80000000 */
#define RTC_CR_EN                   RTC_CR_EN_Msk                               /* RTC enable position */

/******************  Bits definition for RTC_WUCR register  *****************/
#define RTC_WUCR_WKPE_DPos          (0U)
#define RTC_WUCR_WUTE_Pos           RTC_WUCR_WKPE_DPos
#define RTC_WUCR_WUTE_Msk           (0x1UL << RTC_WUCR_WUTE_Pos)                /* 0x00000001 */
#define RTC_WUCR_WUTE               RTC_WUCR_WUTE_Msk                           /* Wakeup timer enable */


#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
