/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_iwdg_regs.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:            2024/07/31
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/07/31     1.0     build this module
 * Description:     This file contains all the register correlation defines for the PLIC firmware library.
 */
#ifndef AS32X601_IWDG_REG_H
#define AS32X601_IWDG_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_addrmap.h"
#include "as32x601.h"

/*
 * @brief IWDG registers structure
 */
typedef struct 
{
    __IO uint32_t PSC;
    __IO uint32_t CFG;
    __IO uint32_t DIV;
    __IO uint32_t TO;
    __I  uint32_t CNT;
    __IO uint32_t CLR;
}IWDG_TypeDef;

/*
 * @addtogroup IWDG peripheral declaration
 */
#define IWDG  ((IWDG_TypeDef *)(IWDG_BASE))

/******************  Bit definition for IWDG_PSC register  *******************/
#define IWDG_PSC_EN_DPos       (0U)
#define IWDG_PSC_EN_Pos        IWDG_PSC_EN_DPos
#define IWDG_PSC_EN_Msk        (0x1UL << IWDG_PSC_EN_Pos)                /* 0x00000001 */
#define IWDG_PSC_EN            IWDG_PSC_EN_Msk                           /* Enable Independent watchdog prescaler. */

#define IWDG_PSC_LOCK_DPos      (1U)
#define IWDG_PSC_LOCK_Pos       IWDG_PSC_LOCK_DPos
#define IWDG_PSC_LOCK_Msk       (0x1UL << IWDG_PSC_LOCK_Pos)              /* 0x00000002 */
#define IWDG_PSC_LOCK           IWDG_PSC_LOCK_Msk                         /*Independent watchdog prescaler lock. */

#define IWDG_PSC_PSCNUM_DPos    (3U)
#define IWDG_PSC_PSCNUM_Pos     IWDG_PSC_PSCNUM_DPos
#define IWDG_PSC_PSCNUM_Msk     (0xffUL << IWDG_PSC_PSCNUM_Pos)            /* 0x00003fc */
#define IWDG_PSC_PSCNUM         IWDG_PSC_PSCNUM_Msk                        /*Independent watchdog prescaler number. */

/******************  Bit definition for IWDG_CFG register  *******************/
#define IWDG_CFG_EN_DPos       (0U)
#define IWDG_CFG_EN_Pos        IWDG_CFG_EN_DPos
#define IWDG_CFG_EN_Msk        (0x1UL << IWDG_CFG_EN_Pos)                  /* 0x00000001 */
#define IWDG_CFG_EN            IWDG_CFG_EN_Msk                             /* Enable Independent watchdog configuration. */

#define IWDG_CFG_LOCK_DPos     (1U)
#define IWDG_CFG_LOCK_Pos      IWDG_CFG_LOCK_DPos
#define IWDG_CFG_LOCK_Msk      (0x1UL << IWDG_CFG_LOCK_Pos)                /* 0x00000002 */
#define IWDG_CFG_LOCK          IWDG_CFG_LOCK_Msk                           /*Independent watchdog prescaler lock. */

/******************  Bit definition for IWDG_DIV register  *******************/
#define IWDG_DIV_DIVNUM_DPos    (0U)
#define IWDG_DIV_DIVNUM_Pos     IWDG_DIV_DIVNUM_DPos
#define IWDG_DIV_DIVNUM_Msk     (0xffffUL << IWDG_DIV_DIVNUM_Pos)            /* 0x0000ffff */
#define IWDG_DIV_DIVNUM         IWDG_DIV_DIVNUM_Msk                          /*Independent watchdog divider number. */

/******************  Bit definition for IWDG_TO register  *******************/
#define IWDG_TO_BVAL_DPos       (0U)
#define IWDG_TO_BVAL_Pos        IWDG_TO_BVAL_DPos
#define IWDG_TO_BVAL_Msk        (0xffffUL << IWDG_TO_BVAL_Pos)            /* 0x0000ffff */
#define IWDG_TO_BVAL            IWDG_TO_BVAL_Msk                          /*Independent watchdog configure timeout period. */

/******************  Bit definition for IWDG_CNT register  *******************/
#define IWDG_CNT_CNTNUM_DPos    (0U)
#define IWDG_CNT_CNTNUM_Pos     IWDG_CNT_CNTNUM_DPos
#define IWDG_CNT_CNTNUM_Msk     (0xffffUL << IWDG_CNT_CNTNUM_Pos)            /* 0x0000ffff */
#define IWDG_CNT_CNTNUM         IWDG_CNT_CNTNUM_Msk                          /*Independent watchdog counter number. */

/******************  Bit definition for IWDG_CLR register  *******************/
#define IWDG_CLR_CLEARPASS_DPos      (0U)
#define IWDG_CLR_KEY_Pos             IWDG_CLR_CLEARPASS_DPos
#define IWDG_CLR_KEY_Msk             (0xffffffffUL << IWDG_CLR_KEY_Pos)        /* 0xffffffff */
#define IWDG_CLR_KEY                 IWDG_CLR_KEY_Msk                          /*Independent watchdog refreshes the key. */


#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
