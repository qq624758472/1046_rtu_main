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
 * Date:            2024/08/01
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/01     1.0     build this module
 * Description:     This file contains all the register correlation defines for the PLIC firmware library.
 */
#ifndef AS32X601_WWDG_REG_H
#define AS32X601_WWDG_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_addrmap.h"
#include "as32x601.h"

/*
 * @brief WWDG registers structure
 */
typedef struct 
{
    __IO uint32_t PSC;
    __I  uint32_t DSTA;
}WWDG_TypeDef;

typedef struct 
{
    __IO uint32_t CFG;
    __IO uint32_t DIV;
    __IO uint32_t TO;
    __IO uint32_t CNT;
    __IO uint32_t CLR;
    __IO uint32_t WD;
}WWDG_Channel_TypeDef;




/*
 * @addtogroup WWDG peripheral declaration
 */
#define WWDG0  ((WWDG_TypeDef *)(WWDG0_BASE))
#define WWDG1  ((WWDG_TypeDef *)(WWDG1_BASE))
#define WWDG0_Channel0 ((WWDG_Channel_TypeDef *)(WWDG0_BASE+0x08U))
#define WWDG0_Channel1 ((WWDG_Channel_TypeDef *)(WWDG0_BASE+0x20U))
#define WWDG0_Channel2 ((WWDG_Channel_TypeDef *)(WWDG0_BASE+0x38U))
#define WWDG0_Channel3 ((WWDG_Channel_TypeDef *)(WWDG0_BASE+0x50U))

#define WWDG1_Channel0 ((WWDG_Channel_TypeDef *)(WWDG1_BASE+0x08U))
#define WWDG1_Channel1 ((WWDG_Channel_TypeDef *)(WWDG1_BASE+0x20U))
#define WWDG1_Channel2 ((WWDG_Channel_TypeDef *)(WWDG1_BASE+0x38U))
#define WWDG1_Channel3 ((WWDG_Channel_TypeDef *)(WWDG1_BASE+0x50U))


/******************  Bit definition for WWDG_PSC register  *******************/
#define WWDG_PSC_EN_DPos       (0U)
#define WWDG_PSC_EN_Pos        WWDG_PSC_EN_DPos
#define WWDG_PSC_EN_Msk        (0x1UL << WWDG_PSC_EN_Pos)                /* 0x00000001 */
#define WWDG_PSC_EN            WWDG_PSC_EN_Msk                           /* Enable Independent watchdog prescaler. */

#define WWDG_PSC_LOCK_DPos      (1U)
#define WWDG_PSC_LOCK_Pos       WWDG_PSC_LOCK_DPos
#define WWDG_PSC_LOCK_Msk       (0x1UL << WWDG_PSC_LOCK_Pos)              /* 0x00000002 */
#define WWDG_PSC_LOCK           WWDG_PSC_LOCK_Msk                         /*Independent watchdog prescaler lock. */

#define WWDG_PSC_PSCNUM_DPos    (3U)
#define WWDG_PSC_PSCNUM_Pos     WWDG_PSC_PSCNUM_DPos
#define WWDG_PSC_PSCNUM_Msk     (0xffUL << WWDG_PSC_PSCNUM_Pos)            /* 0x00003fc */
#define WWDG_PSC_PSCNUM         WWDG_PSC_PSCNUM_Msk                        /*Independent watchdog prescaler number. */

/******************  Bit definition for WWDG_DSTA register  *******************/
#define WWDG_DSTA_BK0_DPos       (0U)
#define WWDG_DSTA_BK0_Pos        WWDG_DSTA_BK0_DPos
#define WWDG_DSTA_BK0_Msk        (0x1UL << WWDG_DSTA_BK0_Pos)                /* 0x00000001 */
#define WWDG_DSTA_BK0            WWDG_DSTA_BK0_Msk                           /* The WWDG Channel0 Bark flag . */

#define WWDG_DSTA_BK1_DPos       (0U)
#define WWDG_DSTA_BK1_Pos        WWDG_DSTA_BK1_DPos
#define WWDG_DSTA_BK1_Msk        (0x1UL << WWDG_DSTA_BK1_Pos)                /* 0x00000002 */
#define WWDG_DSTA_BK1            WWDG_DSTA_BK1_Msk                           /* The WWDG Channel1 Bark flag . */

#define WWDG_DSTA_BK2_DPos       (0U)
#define WWDG_DSTA_BK2_Pos        WWDG_DSTA_BK2_DPos
#define WWDG_DSTA_BK2_Msk        (0x1UL << WWDG_DSTA_BK2_Pos)                /* 0x00000004 */
#define WWDG_DSTA_BK2            WWDG_DSTA_BK2_Msk                           /* The WWDG Channel2 Bark flag . */

#define WWDG_DSTA_BK3_DPos       (0U)
#define WWDG_DSTA_BK3_Pos        WWDG_DSTA_BK3_DPos
#define WWDG_DSTA_BK3_Msk        (0x1UL << WWDG_DSTA_BK3_Pos)                /* 0x00000008 */
#define WWDG_DSTA_BK3            WWDG_DSTA_BK3_Msk                           /* The WWDG Channel3 Bark flag . */

/******************  Bit definition for WWDG_CFG register  *******************/
#define WWDG_CFG_EN_DPos         (0U)
#define WWDG_CFG_EN_Pos          WWDG_CFG_EN_DPos
#define WWDG_CFG_EN_Msk          (0x1UL << WWDG_CFG_EN_Pos)                  /* 0x00000001 */
#define WWDG_CFG_EN              WWDG_CFG_EN_Msk                             /* Enable Independent watchdog configuration. */
  
#define WWDG_CFG_LOCK_DPos       (1U)
#define WWDG_CFG_LOCK_Pos        WWDG_CFG_LOCK_DPos
#define WWDG_CFG_LOCK_Msk        (0x1UL << WWDG_CFG_LOCK_Pos)                /* 0x00000002 */
#define WWDG_CFG_LOCK            WWDG_CFG_LOCK_Msk                           /*Independent watchdog prescaler lock. */

/******************  Bit definition for WWDG_DIV register  *******************/
#define WWDG_DIV_DIVNUM_DPos    (0U)
#define WWDG_DIV_DIVNUM_Pos     WWDG_DIV_DIVNUM_DPos
#define WWDG_DIV_DIVNUM_Msk     (0xffffUL << WWDG_DIV_DIVNUM_Pos)            /* 0x0000ffff */
#define WWDG_DIV_DIVNUM         WWDG_DIV_DIVNUM_Msk                          /*Independent watchdog divider number. */

/******************  Bit definition for WWDG_TO register  *******************/
#define WWDG_TO_BVAL_DPos       (0U)
#define WWDG_TO_BVAL_Pos        WWDG_TO_BVAL_DPos
#define WWDG_TO_BVAL_Msk        (0xffffUL << WWDG_TO_BVAL_Pos)            /* 0x0000ffff */
#define WWDG_TO_BVAL            WWDG_TO_BVAL_Msk                          /*Independent watchdog configure timeout period. */

/******************  Bit definition for WWDG_CNT register  *******************/
#define WWDG_CNT_CNTNUM_DPos    (0U)
#define WWDG_CNT_CNTNUM_Pos     WWDG_CNT_CNTNUM_DPos
#define WWDG_CNT_CNTNUM_Msk     (0xffffUL << WWDG_CNT_CNTNUM_Pos)            /* 0x0000ffff */
#define WWDG_CNT_CNTNUM         WWDG_CNT_CNTNUM_Msk                          /*Independent watchdog counter number. */

/******************  Bit definition for WWDG_CLR register  *******************/
#define WWDG_CLR_CLEARPASS_DPos      (0U)
#define WWDG_CLR_KEY_Pos             WWDG_CLR_CLEARPASS_DPos
#define WWDG_CLR_KEY_Msk             (0xffffffffUL << WWDG_CLR_KEY_Pos)        /* 0xffffffff */
#define WWDG_CLR_KEY                 WWDG_CLR_KEY_Msk                          /*Independent watchdog refreshes the key. */

/******************  Bit definition for WWDG_WD register  *******************/
#define WWDG_WD_WDEN_DPos    (0U)
#define WWDG_WD_WDEN_Pos     WWDG_WD_WDEN_DPos
#define WWDG_WD_WDEN_Msk     (1UL << WWDG_WD_WDEN_Pos)                        /* 0x00000001 */
#define WWDG_WD_WDEN         WWDG_WD_WDEN_Msk                                 /*Enable WWDG Window Counter. */

#define WWDG_WD_WDCNT_DPos    (1U)
#define WWDG_WD_WDCNT_Pos     WWDG_WD_WDCNT_DPos
#define WWDG_WD_WDCNT_Msk     (0xffffUL << WWDG_WD_WDCNT_Pos)                      /* 0x00000001 */
#define WWDG_WD_WDCNT         WWDG_WD_WDCNT_Msk                               /* WWDG Window Counter Value. */


#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
