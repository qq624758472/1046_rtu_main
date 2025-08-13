/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_dma_regs.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:			2024/7/23
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/7/23     1.0     build this module
 * Description:     This file contains all the register correlation defines for the DMA firmware library.
 */

#ifndef AS32X601_DMA_REG_H
#define AS32X601_DMA_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "as32x601.h"
#include "as32x601_addrmap.h"

/*
* @brief General Purpose DMA channel registers structure
*/

typedef struct
{
    __IO uint32_t CHCTL;                            /* DMA_CHCTL              DMA channel x configuration register */
    __IO uint32_t CHCNT;                            /* DMA_CHNT               DMA channel x number of data register */
    __IO uint32_t CHPADDR;                          /* DMA_CHPADDR            DMA channel x peripheral address register */
    __IO uint32_t CHMADDR;                          /* DMA_CHMADDR            DMA channel x memory address register */
} DMA_Channel_TypeDef;


/*
* @brief General Purpose DMA registers structure
*/

    typedef struct
{
    __IO uint32_t CHEN;                              /* DMA_CHEN               DMA channel enable register,                         Address offset: 0x00 */
    uint32_t RESERVED[64];                           /* Reserved               Makes up the space between 0x04 and 0x104 */
    __IO uint32_t PTCH0;                             /* DMA_PTCH0              DMA peripheral interface register0,                  Address offset: 0x104 */
    __IO uint32_t PTCH1;                             /* DMA_PTCH1              DMA peripheral interface register1,                  Address offset: 0x108 */
    __IO uint32_t CCR;                               /* DMA_CCR                DMA control and status register,                     Address offset: 0x10C */
    __IO uint32_t ERR_INT_RAW;                       /* DMA_ERR_INT_RAW        DMA error interrupt raw status register,             Address offset: 0x110 */
    __IO uint32_t ERR_INT_FORCE;                     /* DMA_ERR_INT_FORCE      DMA error interrupt force register,                  Address offset: 0x114 */
    __IO uint32_t ERR_INT_MASK;                      /* DMA_ERR_INT_MASK       DMA error interrupt mask register,                   Address offset: 0x118 */
    __IO uint32_t ERR_INT_STATUS;                    /* DMA_ERR_INT_STATUS     DMA error interrupt status register,                 Address offset: 0x11C */
    __IO uint32_t FTF_INT_RAW;                       /* DMA_FTF_INT_RAW        DMA full transfer interrupt raw status register,     Address offset: 0x70 */
    __IO uint32_t FTF_INT_FORCE;                     /* DMA_FTF_INT_FORCE      DMA full transfer interrupt force register,          Address offset: 0x74 */
    __IO uint32_t FTF_INT_MASK;                      /* DMA_FTF_INT_MASK       DMA full transfer interrupt mask register,           Address offset: 0x78 */
    __IO uint32_t FTF_INT_STATUS;                    /* DMA_FTF_INT_STATUS     DMA full transfer interrupt status register,         Address offset: 0x7C */
    __IO uint32_t HTF_INT_RAW;                       /* DMA_HTF_INT_RAW        DMA half transfer interrupt raw status register,     Address offset: 0x130 */
    __IO uint32_t HTF_INT_FORCE;                     /* DMA_HTF_INT_FORCE      DMA half transfer interrupt force register,          Address offset: 0x134 */
    __IO uint32_t HTF_INT_MASK;                      /* DMA_HTF_INT_MASK       DMA half transfer interrupt mask register,           Address offset: 0x138 */
    __IO uint32_t HTF_INT_STATUS;                    /* DMA_HTF_INT_STATUS     DMA half transfer interrupt status register,         Address offset: 0x13C */
    __IO uint32_t WDG_INT_RAW;                       /* DMA_WDG_INT_RAW        DMA watchdog interrupt raw status register,          Address offset: 0x140 */
    __IO uint32_t WDG_INT_FORCE;                     /* DMA_WDG_INT_FORCE      DMA watchdog interrupt force register,               Address offset: 0x144 */
    __IO uint32_t WDG_INT_MASK;                      /* DMA_WDG_INT_MASK       DMA watchdog interrupt mask register,                Address offset: 0x148 */
    __IO uint32_t WDG_INT_STATUS;                    /* DMA_WDG_INT_STATUS     DMA watchdog interrupt status register,              Address offset: 0x14C */
} DMA_TypeDef;

/*
 * @addtogroup I2C Peripheral declaration
*/

#define DMA0           ((DMA_TypeDef *) (DMA0_CFG_BASE))
#define DMA0_Channel0  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x04))
#define DMA0_Channel1  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x14))
#define DMA0_Channel2  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x24))
#define DMA0_Channel3  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x34))
#define DMA0_Channel4  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x44))
#define DMA0_Channel5  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x54))
#define DMA0_Channel6  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x64))
#define DMA0_Channel7  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x74))
#define DMA0_Channel8  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0X84))
#define DMA0_Channel9  ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0x94))
#define DMA0_Channel10 ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0xa4))
#define DMA0_Channel11 ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0xb4))
#define DMA0_Channel12 ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0xc4))
#define DMA0_Channel13 ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0xd4))
#define DMA0_Channel14 ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0xe4))
#define DMA0_Channel15 ((DMA_Channel_TypeDef *)(DMA0_CFG_BASE+0xf4))

#define DMA1           ((DMA_TypeDef *)(DMA1_CFG_BASE))
#define DMA1_Channel0  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x04))
#define DMA1_Channel1  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x14))
#define DMA1_Channel2  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x24))
#define DMA1_Channel3  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x34))
#define DMA1_Channel4  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x44))
#define DMA1_Channel5  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x54))
#define DMA1_Channel6  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x64))
#define DMA1_Channel7  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x74))
#define DMA1_Channel8  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0X84))
#define DMA1_Channel9  ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0x94))
#define DMA1_Channel10 ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0xa4))
#define DMA1_Channel11 ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0xb4))
#define DMA1_Channel12 ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0xc4))
#define DMA1_Channel13 ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0xd4))
#define DMA1_Channel14 ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0xe4))
#define DMA1_Channel15 ((DMA_Channel_TypeDef *)(DMA1_CFG_BASE+0xf4))

/******************  Bits definition for DMA_CHEN register  *****************/
#define DMA_CHEN_EN0_DPos           (0U)
#define DMA_CHEN_EN0_Pos            DMA_CHEN_EN0_DPos
#define DMA_CHEN_EN0_Msk            (0x01UL << DMA_CHEN_EN0_Pos)                    /* 0x00000001 */
#define DMA_CHEN_EN0                DMA_CHEN_EN0_Msk                                /* DMA channel 0 enable */

#define DMA_CHEN_EN1_DPos           (1U)
#define DMA_CHEN_EN1_Pos            DMA_CHEN_EN1_DPos
#define DMA_CHEN_EN1_Msk            (0x01UL << DMA_CHEN_EN1_Pos)                    /* 0x00000002 */
#define DMA_CHEN_EN1                DMA_CHEN_EN1_Msk                                /* DMA channel 1 enable */

#define DMA_CHEN_EN2_DPos           (2U)
#define DMA_CHEN_EN2_Pos            DMA_CHEN_EN2_DPos
#define DMA_CHEN_EN2_Msk            (0x01UL << DMA_CHEN_EN2_Pos)                    /* 0x00000004 */
#define DMA_CHEN_EN2                DMA_CHEN_EN2_Msk                                /* DMA channel 2 enable */

#define DMA_CHEN_EN3_DPos           (3U)
#define DMA_CHEN_EN3_Pos            DMA_CHEN_EN3_DPos
#define DMA_CHEN_EN3_Msk            (0x01UL << DMA_CHEN_EN3_Pos)                    /* 0x00000008 */
#define DMA_CHEN_EN3                DMA_CHEN_EN3_Msk                                /* DMA channel 3 enable */

#define DMA_CHEN_EN4_DPos           (4U)
#define DMA_CHEN_EN4_Pos            DMA_CHEN_EN4_DPos
#define DMA_CHEN_EN4_Msk            (0x01UL << DMA_CHEN_EN4_Pos)                    /* 0x00000010 */
#define DMA_CHEN_EN4                DMA_CHEN_EN4_Msk                                /* DMA channel 4 enable */

#define DMA_CHEN_EN5_DPos           (5U)
#define DMA_CHEN_EN5_Pos            DMA_CHEN_EN5_DPos
#define DMA_CHEN_EN5_Msk            (0x01UL << DMA_CHEN_EN5_Pos)                    /* 0x00000020 */
#define DMA_CHEN_EN5                DMA_CHEN_EN5_Msk                                /* DMA channel 5 enable */

#define DMA_CHEN_EN6_DPos           (6U)
#define DMA_CHEN_EN6_Pos            DMA_CHEN_EN6_DPos
#define DMA_CHEN_EN6_Msk            (0x01UL << DMA_CHEN_EN6_Pos)                    /* 0x00000040 */
#define DMA_CHEN_EN6                DMA_CHEN_EN6_Msk                                /* DMA channel 6 enable */

#define DMA_CHEN_EN7_DPos           (7U)
#define DMA_CHEN_EN7_Pos            DMA_CHEN_EN7_DPos
#define DMA_CHEN_EN7_Msk            (0x01UL << DMA_CHEN_EN7_Pos)                    /* 0x00000080 */
#define DMA_CHEN_EN7                DMA_CHEN_EN7_Msk                                /* DMA channel 7 enable */

#define DMA_CHEN_EN8_DPos           (8U)
#define DMA_CHEN_EN8_Pos            DMA_CHEN_EN8_DPos
#define DMA_CHEN_EN8_Msk            (0x01UL << DMA_CHEN_EN8_Pos)                    /* 0x00000100 */
#define DMA_CHEN_EN8                DMA_CHEN_EN8_Msk                                /* DMA channel 8 enable */

#define DMA_CHEN_EN9_DPos           (9U)
#define DMA_CHEN_EN9_Pos            DMA_CHEN_EN9_DPos
#define DMA_CHEN_EN9_Msk            (0x01UL << DMA_CHEN_EN9_Pos)                    /* 0x00000200 */
#define DMA_CHEN_EN9                DMA_CHEN_EN9_Msk                                /* DMA channel 9 enable */

#define DMA_CHEN_EN10_DPos          (10U)
#define DMA_CHEN_EN10_Pos           DMA_CHEN_EN10_DPos
#define DMA_CHEN_EN10_Msk           (0x01UL << DMA_CHEN_EN10_Pos)                   /* 0x00000400 */
#define DMA_CHEN_EN10               DMA_CHEN_EN10_Msk                               /* DMA channel 10 enable */

#define DMA_CHEN_EN11_DPos          (11U)
#define DMA_CHEN_EN11_Pos           DMA_CHEN_EN11_DPos
#define DMA_CHEN_EN11_Msk           (0x01UL << DMA_CHEN_EN11_DPos)                   /* 0x00000800 */
#define DMA_CHEN_EN11               DMA_CHEN_EN11_Msk                                /* DMA channel 11 enable */

#define DMA_CHEN_EN12_DPos          (12U)
#define DMA_CHEN_EN12_Pos           DMA_CHEN_EN12_DPos
#define DMA_CHEN_EN12_Msk           (0x01UL << DMA_CHEN_EN12_Pos)                    /* 0x00001000 */
#define DMA_CHEN_EN12               DMA_CHEN_EN12_Msk                                /* DMA channel 7 enable */

#define DMA_CHEN_EN13_DPos          (13U)
#define DMA_CHEN_EN13_Pos           DMA_CHEN_EN13_DPos
#define DMA_CHEN_EN13_Msk           (0x01UL << DMA_CHEN_EN13_Pos)                    /* 0x00002000 */
#define DMA_CHEN_EN13               DMA_CHEN_EN13_Msk                                /* DMA channel 13 enable */

#define DMA_CHEN_EN14_DPos          (14U)
#define DMA_CHEN_EN14_Pos           DMA_CHEN_EN14_DPos
#define DMA_CHEN_EN14_Msk           (0x01UL << DMA_CHEN_EN14_Pos)                    /* 0x00004000 */
#define DMA_CHEN_EN14               DMA_CHEN_EN14_Msk                                /* DMA channel 14 enable */

#define DMA_CHEN_EN15_DPos          (15U)
#define DMA_CHEN_EN15_Pos           DMA_CHEN_EN15_DPos
#define DMA_CHEN_EN15_Msk           (0x01UL << DMA_CHEN_EN15_Pos)                    /* 0x00008000 */
#define DMA_CHEN_EN15               DMA_CHEN_EN15_Msk                                /* DMA channel 15 enable */

/******************  Bits definition for DMA_CH0CTL register  *****************/
#define DMA_CH0CTL_M2M_DPos          (0U)
#define DMA_CH0CTL_M2M_Pos           DMA_CH0CTL_M2M_DPos
#define DMA_CH0CTL_M2M_Msk           (0x01UL << DMA_CH0CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH0CTL_M2M               DMA_CH0CTL_M2M_Msk                              /* DMA channel 0 memory-to-memory transfer mode */

#define DMA_CH0CTL_DIR_DPos          (1U)
#define DMA_CH0CTL_DIR_Pos           DMA_CH0CTL_DIR_DPos
#define DMA_CH0CTL_DIR_Msk           (0x01UL << DMA_CH0CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH0CTL_DIR               DMA_CH0CTL_DIR_Msk                                /* DMA channel 0 data transfer direction */

#define DMA_CH0CTL_CMEN_DPos         (2U)
#define DMA_CH0CTL_CIRC_Pos          DMA_CH0CTL_CMEN_DPos
#define DMA_CH0CTL_CIRC_Msk          (0x01UL << DMA_CH0CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH0CTL_CIRC              DMA_CH0CTL_CIRC_Msk                                /* DMA channel 0 circular mode */

#define DMA_CH0CTL_PNAGA_DPos        (3U)
#define DMA_CH0CTL_PINC_Pos          DMA_CH0CTL_PNAGA_DPos
#define DMA_CH0CTL_PINC_Msk          (0x01UL << DMA_CH0CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH0CTL_PINC              DMA_CH0CTL_PINC_Msk                                /* DMA channel 0 peripheral address increment */

#define DMA_CH0CTL_MNAGA_DPos        (4U)
#define DMA_CH0CTL_MINC_Pos          DMA_CH0CTL_MINC_DPos
#define DMA_CH0CTL_MINC_Msk          (0x01UL << DMA_CH0CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH0CTL_MINC              DMA_CH0CTL_MINC_Msk                                /* DMA channel 0 memory address increment */

#define DMA_CH0CTL_PWIDTH_DPos       (5U)
#define DMA_CH0CTL_PSIZE_Pos         DMA_CH0CTL_PWIDTH_DPos
#define DMA_CH0CTL_PSIZE_Msk         (0x03UL << DMA_CH0CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH0CTL_PSIZE             DMA_CH0CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 0 peripheral data width) */
#define DMA_CH0CTL_PSIZE_0           (0x01UL << DMA_CH0CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH0CTL_PSIZE_1           (0x02UL << DMA_CH0CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH0CTL_MWIDTH_DPos       (7U)
#define DMA_CH0CTL_MSIZE_Pos         DMA_CH0CTL_MWIDTH_DPos
#define DMA_CH0CTL_MSIZE_Msk         (0x03UL << DMA_CH0CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH0CTL_MSIZE             DMA_CH0CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 0 memory data width) */
#define DMA_CH0CTL_MSIZE_0           (0x01UL << DMA_CH0CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH0CTL_MSIZE_1           (0x02UL << DMA_CH0CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH0CTL_PRIO_DPos          (9U)
#define DMA_CH0CTL_PRIO_Pos           DMA_CH0CTL_PRIO_DPos
#define DMA_CH0CTL_PRIO_Msk           (0x03UL << DMA_CH0CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH0CTL_PRIO               DMA_CH0CTL_PRIO_Msk                                /* PRIO reg[1:0] bits( DMA channel 0 priority level) */
#define DMA_CH0CTL_PRIO_0             (0x01UL << DMA_CH0CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH0CTL_PRIO_1             (0x02UL << DMA_CH0CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH0CNT register  *****************/
#define DMA_CH0CNT_CNT_DPos          (0U)
#define DMA_CH0CNT_CNT_Pos           DMA_CH0CNT_CNT_DPos
#define DMA_CH0CNT_CNT_Msk           (0x01UL << DMA_CH0CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH0CNT_CNT               DMA_CH0CNT_CNT_Msk                                  /* DMA channel 0 number of data to transfer */

/******************  Bits definition for DMA_CH0PADDR register  *****************/
#define DMA_CH0PADDR_PADDR_DPos      (0U)
#define DMA_CH0PADDR_PADDR_Pos       DMA_CH0PADDR_PADDR_DPos
#define DMA_CH0PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH0PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH0PADDR_PADDR           DMA_CH0PADDR_PADDR_Msk                              /* DMA channel 0 peripheral address */

/******************  Bits definition for DMA_CH0MADDR register  *****************/
#define DMA_CH0MADDR_MADDR_DPos      (0U)
#define DMA_CH0MADDR_MADDR_Pos       DMA_CH0MADDR_MADDR_DPos
#define DMA_CH0MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH0MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH0MADDR_MADDR           DMA_CH0MADDR_MADDR_Msk                                     /* DMA channel 0 memory address */

/******************  Bits definition for DMA_CH1CTL register  *****************/
#define DMA_CH1CTL_M2M_DPos          (0U)
#define DMA_CH1CTL_M2M_Pos           DMA_CH1CTL_M2M_DPos
#define DMA_CH1CTL_M2M_Msk           (0x01UL << DMA_CH1CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH1CTL_M2M               DMA_CH1CTL_M2M_Msk                              /* DMA channel 1 memory-to-memory transfer mode */

#define DMA_CH1CTL_DIR_DPos          (1U)
#define DMA_CH1CTL_DIR_Pos           DMA_CH1CTL_DIR_DPos
#define DMA_CH1CTL_DIR_Msk           (0x01UL << DMA_CH1CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH1CTL_DIR               DMA_CH1CTL_DIR_Msk                                /* DMA channel 1 data transfer direction */

#define DMA_CH1CTL_CMEN_DPos         (2U)
#define DMA_CH1CTL_CIRC_Pos          DMA_CH1CTL_CMEN_DPos
#define DMA_CH1CTL_CIRC_Msk          (0x01UL << DMA_CH1CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH1CTL_CIRC              DMA_CH1CTL_CIRC_Msk                                /* DMA channel 1 circular mode */

#define DMA_CH1CTL_PNAGA_DPos        (3U)
#define DMA_CH1CTL_PINC_Pos          DMA_CH1CTL_PNAGA_DPos
#define DMA_CH1CTL_PINC_Msk          (0x01UL << DMA_CH1CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH1CTL_PINC              DMA_CH1CTL_PINC_Msk                                /* DMA channel 1 peripheral address increment */

#define DMA_CH1CTL_MNAGA_DPos        (4U)
#define DMA_CH1CTL_MINC_Pos          DMA_CH1CTL_MINC_DPos
#define DMA_CH1CTL_MINC_Msk          (0x01UL << DMA_CH1CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH1CTL_MINC              DMA_CH1CTL_MINC_Msk                                /* DMA channel 1 memory address increment */

#define DMA_CH1CTL_PWIDTH_DPos       (5U)
#define DMA_CH1CTL_PSIZE_Pos         DMA_CH1CTL_PWIDTH_DPos
#define DMA_CH1CTL_PSIZE_Msk         (0x03UL << DMA_CH1CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH1CTL_PSIZE             DMA_CH1CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 1 peripheral data width) */
#define DMA_CH1CTL_PSIZE_0           (0x01UL << DMA_CH1CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH1CTL_PSIZE_1           (0x02UL << DMA_CH1CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH1CTL_MWIDTH_DPos       (7U)
#define DMA_CH1CTL_MSIZE_Pos         DMA_CH1CTL_MWIDTH_DPos
#define DMA_CH1CTL_MSIZE_Msk         (0x03UL << DMA_CH1CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH1CTL_MSIZE             DMA_CH1CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 1 memory data width) */
#define DMA_CH1CTL_MSIZE_0           (0x01UL << DMA_CH1CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH1CTL_MSIZE_1           (0x02UL << DMA_CH1CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH1CTL_PRIO_DPos          (9U)
#define DMA_CH1CTL_PRIO_Pos           DMA_CH1CTL_PRIO_DPos
#define DMA_CH1CTL_PRIO_Msk           (0x03UL << DMA_CH1CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH1CTL_PRIO               DMA_CH1CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 1 priority level) */
#define DMA_CH1CTL_PRIO_0             (0x01UL << DMA_CH1CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH1CTL_PRIO_1             (0x02UL << DMA_CH1CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH1CNT register  *****************/
#define DMA_CH1CNT_CNT_DPos          (0U)
#define DMA_CH1CNT_CNT_Pos           DMA_CH1CNT_CNT_DPos
#define DMA_CH1CNT_CNT_Msk           (0x01UL << DMA_CH1CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH1CNT_CNT               DMA_CH1CNT_CNT_Msk                                  /* DMA channel 1 number of data to transfer */

/******************  Bits definition for DMA_CH1PADDR register  *****************/
#define DMA_CH1PADDR_PADDR_DPos      (0U)
#define DMA_CH1PADDR_PADDR_Pos       DMA_CH1PADDR_PADDR_DPos
#define DMA_CH1PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH1PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH1PADDR_PADDR           DMA_CH1PADDR_PADDR_Msk                              /* DMA channel 1 peripheral address */

/******************  Bits definition for DMA_CH1MADDR register  *****************/
#define DMA_CH1MADDR_MADDR_DPos      (0U)
#define DMA_CH1MADDR_MADDR_Pos       DMA_CH1MADDR_MADDR_DPos
#define DMA_CH1MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH1MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH1MADDR_MADDR           DMA_CH1MADDR_MADDR_Msk                                     /* DMA channel 1 memory address */

/******************  Bits definition for DMA_CH2CTL register  *****************/
#define DMA_CH2CTL_M2M_DPos          (0U)
#define DMA_CH2CTL_M2M_Pos           DMA_CH2CTL_M2M_DPos
#define DMA_CH2CTL_M2M_Msk           (0x01UL << DMA_CH2CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH2CTL_M2M               DMA_CH2CTL_M2M_Msk                              /* DMA channel 2 memory-to-memory transfer mode */

#define DMA_CH2CTL_DIR_DPos          (1U)
#define DMA_CH2CTL_DIR_Pos           DMA_CH2CTL_DIR_DPos
#define DMA_CH2CTL_DIR_Msk           (0x01UL << DMA_CH2CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH2CTL_DIR               DMA_CH2CTL_DIR_Msk                                /* DMA channel 2 data transfer direction */

#define DMA_CH2CTL_CMEN_DPos         (2U)
#define DMA_CH2CTL_CIRC_Pos          DMA_CH2CTL_CMEN_DPos
#define DMA_CH2CTL_CIRC_Msk          (0x01UL << DMA_CH2CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH2CTL_CIRC              DMA_CH2CTL_CIRC_Msk                                /* DMA channel 2 circular mode */

#define DMA_CH2CTL_PNAGA_DPos        (3U)
#define DMA_CH2CTL_PINC_Pos          DMA_CH2CTL_PNAGA_DPos
#define DMA_CH2CTL_PINC_Msk          (0x01UL << DMA_CH2CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH2CTL_PINC              DMA_CH2CTL_PINC_Msk                                /* DMA channel 2 peripheral address increment */

#define DMA_CH2CTL_MNAGA_DPos        (4U)
#define DMA_CH2CTL_MINC_Pos          DMA_CH2CTL_MINC_DPos
#define DMA_CH2CTL_MINC_Msk          (0x01UL << DMA_CH2CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH2CTL_MINC              DMA_CH2CTL_MINC_Msk                                /* DMA channel 2 memory address increment */

#define DMA_CH2CTL_PWIDTH_DPos       (5U)
#define DMA_CH2CTL_PSIZE_Pos         DMA_CH2CTL_PWIDTH_DPos
#define DMA_CH2CTL_PSIZE_Msk         (0x03UL << DMA_CH2CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH2CTL_PSIZE             DMA_CH2CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 2 peripheral data width) */
#define DMA_CH2CTL_PSIZE_0           (0x01UL << DMA_CH2CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH2CTL_PSIZE_1           (0x02UL << DMA_CH2CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH2CTL_MWIDTH_DPos       (7U)
#define DMA_CH2CTL_MSIZE_Pos         DMA_CH2CTL_MWIDTH_DPos
#define DMA_CH2CTL_MSIZE_Msk         (0x03UL << DMA_CH2CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH2CTL_MSIZE             DMA_CH2CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 2 memory data width) */
#define DMA_CH2CTL_MSIZE_0           (0x01UL << DMA_CH2CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH2CTL_MSIZE_1           (0x02UL << DMA_CH2CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH2CTL_PRIO_DPos          (9U)
#define DMA_CH2CTL_PRIO_Pos           DMA_CH2CTL_PRIO_DPos
#define DMA_CH2CTL_PRIO_Msk           (0x03UL << DMA_CH2CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH2CTL_PRIO               DMA_CH2CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 2 priority level) */
#define DMA_CH2CTL_PRIO_0             (0x01UL << DMA_CH2CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH2CTL_PRIO_1             (0x02UL << DMA_CH2CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH2CNT register  *****************/
#define DMA_CH2CNT_CNT_DPos          (0U)
#define DMA_CH2CNT_CNT_Pos           DMA_CH2CNT_CNT_DPos
#define DMA_CH2CNT_CNT_Msk           (0x01UL << DMA_CH2CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH2CNT_CNT               DMA_CH2CNT_CNT_Msk                                  /* DMA channel 2 number of data to transfer */

/******************  Bits definition for DMA_CH2PADDR register  *****************/
#define DMA_CH2PADDR_PADDR_DPos      (0U)
#define DMA_CH2PADDR_PADDR_Pos       DMA_CH2PADDR_PADDR_DPos
#define DMA_CH2PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH2PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH2PADDR_PADDR           DMA_CH2PADDR_PADDR_Msk                              /* DMA channel 2 peripheral address */

/******************  Bits definition for DMA_CH2MADDR register  *****************/
#define DMA_CH2MADDR_MADDR_DPos      (0U)
#define DMA_CH2MADDR_MADDR_Pos       DMA_CH2MADDR_MADDR_DPos
#define DMA_CH2MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH2MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH2MADDR_MADDR           DMA_CH2MADDR_MADDR_Msk                                     /* DMA channel 2 memory address */

/******************  Bits definition for DMA_CH3CTL register  *****************/
#define DMA_CH3CTL_M2M_DPos          (0U)
#define DMA_CH3CTL_M2M_Pos           DMA_CH3CTL_M2M_DPos
#define DMA_CH3CTL_M2M_Msk           (0x01UL << DMA_CH3CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH3CTL_M2M               DMA_CH3CTL_M2M_Msk                              /* DMA channel 3 memory-to-memory transfer mode */

#define DMA_CH3CTL_DIR_DPos          (1U)
#define DMA_CH3CTL_DIR_Pos           DMA_CH3CTL_DIR_DPos
#define DMA_CH3CTL_DIR_Msk           (0x01UL << DMA_CH3CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH3CTL_DIR               DMA_CH3CTL_DIR_Msk                                /* DMA channel 3 data transfer direction */

#define DMA_CH3CTL_CMEN_DPos         (2U)
#define DMA_CH3CTL_CIRC_Pos          DMA_CH3CTL_CMEN_DPos
#define DMA_CH3CTL_CIRC_Msk          (0x01UL << DMA_CH3CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH3CTL_CIRC              DMA_CH3CTL_CIRC_Msk                                /* DMA channel 3 circular mode */

#define DMA_CH3CTL_PNAGA_DPos        (3U)
#define DMA_CH3CTL_PINC_Pos          DMA_CH3CTL_PNAGA_DPos
#define DMA_CH3CTL_PINC_Msk          (0x01UL << DMA_CH3CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH3CTL_PINC              DMA_CH3CTL_PINC_Msk                                /* DMA channel 3 peripheral address increment */

#define DMA_CH3CTL_MNAGA_DPos        (4U)
#define DMA_CH3CTL_MINC_Pos          DMA_CH3CTL_MINC_DPos
#define DMA_CH3CTL_MINC_Msk          (0x01UL << DMA_CH3CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH3CTL_MINC              DMA_CH3CTL_MINC_Msk                                /* DMA channel 3 memory address increment */

#define DMA_CH3CTL_PWIDTH_DPos       (5U)
#define DMA_CH3CTL_PSIZE_Pos         DMA_CH3CTL_PWIDTH_DPos
#define DMA_CH3CTL_PSIZE_Msk         (0x03UL << DMA_CH3CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH3CTL_PSIZE             DMA_CH3CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 3 peripheral data width) */
#define DMA_CH3CTL_PSIZE_0           (0x01UL << DMA_CH3CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH3CTL_PSIZE_1           (0x02UL << DMA_CH3CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH3CTL_MWIDTH_DPos       (7U)
#define DMA_CH3CTL_MSIZE_Pos         DMA_CH3CTL_MWIDTH_DPos
#define DMA_CH3CTL_MSIZE_Msk         (0x03UL << DMA_CH3CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH3CTL_MSIZE             DMA_CH3CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 3 memory data width) */
#define DMA_CH3CTL_MSIZE_0           (0x01UL << DMA_CH3CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH3CTL_MSIZE_1           (0x02UL << DMA_CH3CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH3CTL_PRIO_DPos          (9U)
#define DMA_CH3CTL_PRIO_Pos           DMA_CH3CTL_PRIO_DPos
#define DMA_CH3CTL_PRIO_Msk           (0x03UL << DMA_CH3CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH3CTL_PRIO               DMA_CH3CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 3 priority level) */
#define DMA_CH3CTL_PRIO_0             (0x01UL << DMA_CH3CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH3CTL_PRIO_1             (0x02UL << DMA_CH3CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH3CNT register  *****************/
#define DMA_CH3CNT_CNT_DPos          (0U)
#define DMA_CH3CNT_CNT_Pos           DMA_CH3CNT_CNT_DPos
#define DMA_CH3CNT_CNT_Msk           (0x01UL << DMA_CH3CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH3CNT_CNT               DMA_CH3CNT_CNT_Msk                                  /* DMA channel 3 number of data to transfer */

/******************  Bits definition for DMA_CH3PADDR register  *****************/
#define DMA_CH3PADDR_PADDR_DPos      (0U)
#define DMA_CH3PADDR_PADDR_Pos       DMA_CH3PADDR_PADDR_DPos
#define DMA_CH3PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH3PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH3PADDR_PADDR           DMA_CH3PADDR_PADDR_Msk                              /* DMA channel 3 peripheral address */

/******************  Bits definition for DMA_CH3MADDR register  *****************/
#define DMA_CH3MADDR_MADDR_DPos      (0U)
#define DMA_CH3MADDR_MADDR_Pos       DMA_CH3MADDR_MADDR_DPos
#define DMA_CH3MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH3MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH3MADDR_MADDR           DMA_CH3MADDR_MADDR_Msk                                     /* DMA channel 3 memory address */


/******************  Bits definition for DMA_CH4CTL register  *****************/
#define DMA_CH4CTL_M2M_DPos          (0U)
#define DMA_CH4CTL_M2M_Pos           DMA_CH4CTL_M2M_DPos
#define DMA_CH4CTL_M2M_Msk           (0x01UL << DMA_CH4CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH4CTL_M2M               DMA_CH4CTL_M2M_Msk                              /* DMA channel 4 memory-to-memory transfer mode */

#define DMA_CH4CTL_DIR_DPos          (1U)
#define DMA_CH4CTL_DIR_Pos           DMA_CH4CTL_DIR_DPos
#define DMA_CH4CTL_DIR_Msk           (0x01UL << DMA_CH4CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH4CTL_DIR               DMA_CH4CTL_DIR_Msk                                /* DMA channel 4 data transfer direction */

#define DMA_CH4CTL_CMEN_DPos         (2U)
#define DMA_CH4CTL_CIRC_Pos          DMA_CH4CTL_CMEN_DPos
#define DMA_CH4CTL_CIRC_Msk          (0x01UL << DMA_CH4CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH4CTL_CIRC              DMA_CH4CTL_CIRC_Msk                                /* DMA channel 4 circular mode */

#define DMA_CH4CTL_PNAGA_DPos        (3U)
#define DMA_CH4CTL_PINC_Pos          DMA_CH4CTL_PNAGA_DPos
#define DMA_CH4CTL_PINC_Msk          (0x01UL << DMA_CH4CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH4CTL_PINC              DMA_CH4CTL_PINC_Msk                                /* DMA channel 4 peripheral address increment */

#define DMA_CH4CTL_MNAGA_DPos        (4U)
#define DMA_CH4CTL_MINC_Pos          DMA_CH4CTL_MINC_DPos
#define DMA_CH4CTL_MINC_Msk          (0x01UL << DMA_CH4CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH4CTL_MINC              DMA_CH4CTL_MINC_Msk                                /* DMA channel 4 memory address increment */

#define DMA_CH4CTL_PWIDTH_DPos       (5U)
#define DMA_CH4CTL_PSIZE_Pos         DMA_CH4CTL_PWIDTH_DPos
#define DMA_CH4CTL_PSIZE_Msk         (0x03UL << DMA_CH4CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH4CTL_PSIZE             DMA_CH4CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 4 peripheral data width) */
#define DMA_CH4CTL_PSIZE_0           (0x01UL << DMA_CH4CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH4CTL_PSIZE_1           (0x02UL << DMA_CH4CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH4CTL_MWIDTH_DPos       (7U)
#define DMA_CH4CTL_MSIZE_Pos         DMA_CH4CTL_MWIDTH_DPos
#define DMA_CH4CTL_MSIZE_Msk         (0x03UL << DMA_CH4CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH4CTL_MSIZE             DMA_CH4CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 4 memory data width) */
#define DMA_CH4CTL_MSIZE_0           (0x01UL << DMA_CH4CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH4CTL_MSIZE_1           (0x02UL << DMA_CH4CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH4CTL_PRIO_DPos          (9U)
#define DMA_CH4CTL_PRIO_Pos           DMA_CH4CTL_PRIO_DPos
#define DMA_CH4CTL_PRIO_Msk           (0x03UL << DMA_CH4CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH4CTL_PRIO               DMA_CH4CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 4 priority level) */
#define DMA_CH4CTL_PRIO_0             (0x01UL << DMA_CH4CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH4CTL_PRIO_1             (0x02UL << DMA_CH4CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH4CNT register  *****************/
#define DMA_CH4CNT_CNT_DPos          (0U)
#define DMA_CH4CNT_CNT_Pos           DMA_CH4CNT_CNT_DPos
#define DMA_CH4CNT_CNT_Msk           (0x01UL << DMA_CH4CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH4CNT_CNT               DMA_CH4CNT_CNT_Msk                                  /* DMA channel 4 number of data to transfer */

/******************  Bits definition for DMA_CH4PADDR register  *****************/
#define DMA_CH4PADDR_PADDR_DPos      (0U)
#define DMA_CH4PADDR_PADDR_Pos       DMA_CH4PADDR_PADDR_DPos
#define DMA_CH4PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH4PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH4PADDR_PADDR           DMA_CH4PADDR_PADDR_Msk                              /* DMA channel 4 peripheral address */

/******************  Bits definition for DMA_CH4MADDR register  *****************/
#define DMA_CH4MADDR_MADDR_DPos      (0U)
#define DMA_CH4MADDR_MADDR_Pos       DMA_CH4MADDR_MADDR_DPos
#define DMA_CH4MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH4MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH4MADDR_MADDR           DMA_CH4MADDR_MADDR_Msk                                     /* DMA channel 4 memory address */



/******************  Bits definition for DMA_CH5CTL register  *****************/
#define DMA_CH5CTL_M2M_DPos          (0U)
#define DMA_CH5CTL_M2M_Pos           DMA_CH5CTL_M2M_DPos
#define DMA_CH5CTL_M2M_Msk           (0x01UL << DMA_CH5CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH5CTL_M2M               DMA_CH5CTL_M2M_Msk                              /* DMA channel 5 memory-to-memory transfer mode */

#define DMA_CH5CTL_DIR_DPos          (1U)
#define DMA_CH5CTL_DIR_Pos           DMA_CH5CTL_DIR_DPos
#define DMA_CH5CTL_DIR_Msk           (0x01UL << DMA_CH5CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH5CTL_DIR               DMA_CH5CTL_DIR_Msk                                /* DMA channel 5 data transfer direction */

#define DMA_CH5CTL_CMEN_DPos         (2U)
#define DMA_CH5CTL_CIRC_Pos          DMA_CH5CTL_CMEN_DPos
#define DMA_CH5CTL_CIRC_Msk          (0x01UL << DMA_CH5CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH5CTL_CIRC              DMA_CH5CTL_CIRC_Msk                                /* DMA channel 5 circular mode */

#define DMA_CH5CTL_PNAGA_DPos        (3U)
#define DMA_CH5CTL_PINC_Pos          DMA_CH5CTL_PNAGA_DPos
#define DMA_CH5CTL_PINC_Msk          (0x01UL << DMA_CH5CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH5CTL_PINC              DMA_CH5CTL_PINC_Msk                                /* DMA channel 5 peripheral address increment */

#define DMA_CH5CTL_MNAGA_DPos        (4U)
#define DMA_CH5CTL_MINC_Pos          DMA_CH5CTL_MINC_DPos
#define DMA_CH5CTL_MINC_Msk          (0x01UL << DMA_CH5CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH5CTL_MINC              DMA_CH5CTL_MINC_Msk                                /* DMA channel 5 memory address increment */

#define DMA_CH5CTL_PWIDTH_DPos       (5U)
#define DMA_CH5CTL_PSIZE_Pos         DMA_CH5CTL_PWIDTH_DPos
#define DMA_CH5CTL_PSIZE_Msk         (0x03UL << DMA_CH5CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH5CTL_PSIZE             DMA_CH5CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 5 peripheral data width) */
#define DMA_CH5CTL_PSIZE_0           (0x01UL << DMA_CH5CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH5CTL_PSIZE_1           (0x02UL << DMA_CH5CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH5CTL_MWIDTH_DPos       (7U)
#define DMA_CH5CTL_MSIZE_Pos         DMA_CH5CTL_MWIDTH_DPos
#define DMA_CH5CTL_MSIZE_Msk         (0x03UL << DMA_CH5CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH5CTL_MSIZE             DMA_CH5CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 5 memory data width) */
#define DMA_CH5CTL_MSIZE_0           (0x01UL << DMA_CH5CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH5CTL_MSIZE_1           (0x02UL << DMA_CH5CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH5CTL_PRIO_DPos          (9U)
#define DMA_CH5CTL_PRIO_Pos           DMA_CH5CTL_PRIO_DPos
#define DMA_CH5CTL_PRIO_Msk           (0x03UL << DMA_CH5CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH5CTL_PRIO               DMA_CH5CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 5 priority level) */
#define DMA_CH5CTL_PRIO_0             (0x01UL << DMA_CH5CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH5CTL_PRIO_1             (0x02UL << DMA_CH5CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH5CNT register  *****************/
#define DMA_CH5CNT_CNT_DPos          (0U)
#define DMA_CH5CNT_CNT_Pos           DMA_CH5CNT_CNT_DPos
#define DMA_CH5CNT_CNT_Msk           (0x01UL << DMA_CH5CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH5CNT_CNT               DMA_CH5CNT_CNT_Msk                                  /* DMA channel 5 number of data to transfer */

/******************  Bits definition for DMA_CH5PADDR register  *****************/
#define DMA_CH5PADDR_PADDR_DPos      (0U)
#define DMA_CH5PADDR_PADDR_Pos       DMA_CH5PADDR_PADDR_DPos
#define DMA_CH5PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH5PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH5PADDR_PADDR           DMA_CH5PADDR_PADDR_Msk                              /* DMA channel 5 peripheral address */

/******************  Bits definition for DMA_CH5MADDR register  *****************/
#define DMA_CH5MADDR_MADDR_DPos      (0U)
#define DMA_CH5MADDR_MADDR_Pos       DMA_CH5MADDR_MADDR_DPos
#define DMA_CH5MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH5MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH5MADDR_MADDR           DMA_CH5MADDR_MADDR_Msk                                     /* DMA channel 5 memory address */


/******************  Bits definition for DMA_CH6CTL register  *****************/
#define DMA_CH6CTL_M2M_DPos          (0U)
#define DMA_CH6CTL_M2M_Pos           DMA_CH6CTL_M2M_DPos
#define DMA_CH6CTL_M2M_Msk           (0x01UL << DMA_CH6CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH6CTL_M2M               DMA_CH6CTL_M2M_Msk                              /* DMA channel 6 memory-to-memory transfer mode */

#define DMA_CH6CTL_DIR_DPos          (1U)
#define DMA_CH6CTL_DIR_Pos           DMA_CH6CTL_DIR_DPos
#define DMA_CH6CTL_DIR_Msk           (0x01UL << DMA_CH6CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH6CTL_DIR               DMA_CH6CTL_DIR_Msk                                /* DMA channel 6 data transfer direction */

#define DMA_CH6CTL_CMEN_DPos         (2U)
#define DMA_CH6CTL_CIRC_Pos          DMA_CH6CTL_CMEN_DPos
#define DMA_CH6CTL_CIRC_Msk          (0x01UL << DMA_CH6CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH6CTL_CIRC              DMA_CH6CTL_CIRC_Msk                                /* DMA channel 6 circular mode */

#define DMA_CH6CTL_PNAGA_DPos        (3U)
#define DMA_CH6CTL_PINC_Pos          DMA_CH6CTL_PNAGA_DPos
#define DMA_CH6CTL_PINC_Msk          (0x01UL << DMA_CH6CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH6CTL_PINC              DMA_CH6CTL_PINC_Msk                                /* DMA channel 6 peripheral address increment */

#define DMA_CH6CTL_MNAGA_DPos        (4U)
#define DMA_CH6CTL_MINC_Pos          DMA_CH6CTL_MINC_DPos
#define DMA_CH6CTL_MINC_Msk          (0x01UL << DMA_CH6CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH6CTL_MINC              DMA_CH6CTL_MINC_Msk                                /* DMA channel 6 memory address increment */

#define DMA_CH6CTL_PWIDTH_DPos       (5U)
#define DMA_CH6CTL_PSIZE_Pos         DMA_CH6CTL_PWIDTH_DPos
#define DMA_CH6CTL_PSIZE_Msk         (0x03UL << DMA_CH6CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH6CTL_PSIZE             DMA_CH6CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 6 peripheral data width) */
#define DMA_CH6CTL_PSIZE_0           (0x01UL << DMA_CH6CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH6CTL_PSIZE_1           (0x02UL << DMA_CH6CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH6CTL_MWIDTH_DPos       (7U)
#define DMA_CH6CTL_MSIZE_Pos         DMA_CH6CTL_MWIDTH_DPos
#define DMA_CH6CTL_MSIZE_Msk         (0x03UL << DMA_CH6CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH6CTL_MSIZE             DMA_CH6CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 6 memory data width) */
#define DMA_CH6CTL_MSIZE_0           (0x01UL << DMA_CH6CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH6CTL_MSIZE_1           (0x02UL << DMA_CH6CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH6CTL_PRIO_DPos          (9U)
#define DMA_CH6CTL_PRIO_Pos           DMA_CH6CTL_PRIO_DPos
#define DMA_CH6CTL_PRIO_Msk           (0x03UL << DMA_CH6CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH6CTL_PRIO               DMA_CH6CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 6 priority level) */
#define DMA_CH6CTL_PRIO_0             (0x01UL << DMA_CH6CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH6CTL_PRIO_1             (0x02UL << DMA_CH6CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH6CNT register  *****************/
#define DMA_CH6CNT_CNT_DPos          (0U)
#define DMA_CH6CNT_CNT_Pos           DMA_CH6CNT_CNT_DPos
#define DMA_CH6CNT_CNT_Msk           (0x01UL << DMA_CH6CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH6CNT_CNT               DMA_CH6CNT_CNT_Msk                                  /* DMA channel 6 number of data to transfer */

/******************  Bits definition for DMA_CH6PADDR register  *****************/
#define DMA_CH6PADDR_PADDR_DPos      (0U)
#define DMA_CH6PADDR_PADDR_Pos       DMA_CH6PADDR_PADDR_DPos
#define DMA_CH6PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH6PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH6PADDR_PADDR           DMA_CH6PADDR_PADDR_Msk                              /* DMA channel 6 peripheral address */

/******************  Bits definition for DMA_CH6MADDR register  *****************/
#define DMA_CH6MADDR_MADDR_DPos      (0U)
#define DMA_CH6MADDR_MADDR_Pos       DMA_CH6MADDR_MADDR_DPos
#define DMA_CH6MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH6MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH6MADDR_MADDR           DMA_CH6MADDR_MADDR_Msk                                     /* DMA channel 6 memory address */



/******************  Bits definition for DMA_CH7CTL register  *****************/
#define DMA_CH7CTL_M2M_DPos          (0U)
#define DMA_CH7CTL_M2M_Pos           DMA_CH7CTL_M2M_DPos
#define DMA_CH7CTL_M2M_Msk           (0x01UL << DMA_CH7CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH7CTL_M2M               DMA_CH7CTL_M2M_Msk                              /* DMA channel 7 memory-to-memory transfer mode */

#define DMA_CH7CTL_DIR_DPos          (1U)
#define DMA_CH7CTL_DIR_Pos           DMA_CH7CTL_DIR_DPos
#define DMA_CH7CTL_DIR_Msk           (0x01UL << DMA_CH7CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH7CTL_DIR               DMA_CH7CTL_DIR_Msk                                /* DMA channel 7 data transfer direction */

#define DMA_CH7CTL_CMEN_DPos         (2U)
#define DMA_CH7CTL_CIRC_Pos          DMA_CH7CTL_CMEN_DPos
#define DMA_CH7CTL_CIRC_Msk          (0x01UL << DMA_CH7CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH7CTL_CIRC              DMA_CH7CTL_CIRC_Msk                                /* DMA channel 7 circular mode */

#define DMA_CH7CTL_PNAGA_DPos        (3U)
#define DMA_CH7CTL_PINC_Pos          DMA_CH7CTL_PNAGA_DPos
#define DMA_CH7CTL_PINC_Msk          (0x01UL << DMA_CH7CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH7CTL_PINC              DMA_CH7CTL_PINC_Msk                                /* DMA channel 7 peripheral address increment */

#define DMA_CH7CTL_MNAGA_DPos        (4U)
#define DMA_CH7CTL_MINC_Pos          DMA_CH7CTL_MINC_DPos
#define DMA_CH7CTL_MINC_Msk          (0x01UL << DMA_CH7CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH7CTL_MINC              DMA_CH7CTL_MINC_Msk                                /* DMA channel 7 memory address increment */

#define DMA_CH7CTL_PWIDTH_DPos       (5U)
#define DMA_CH7CTL_PSIZE_Pos         DMA_CH7CTL_PWIDTH_DPos
#define DMA_CH7CTL_PSIZE_Msk         (0x03UL << DMA_CH7CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH7CTL_PSIZE             DMA_CH7CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 7 peripheral data width) */
#define DMA_CH7CTL_PSIZE_0           (0x01UL << DMA_CH7CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH7CTL_PSIZE_1           (0x02UL << DMA_CH7CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH7CTL_MWIDTH_DPos       (7U)
#define DMA_CH7CTL_MSIZE_Pos         DMA_CH7CTL_MWIDTH_DPos
#define DMA_CH7CTL_MSIZE_Msk         (0x03UL << DMA_CH7CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH7CTL_MSIZE             DMA_CH7CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 7 memory data width) */
#define DMA_CH7CTL_MSIZE_0           (0x01UL << DMA_CH7CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH7CTL_MSIZE_1           (0x02UL << DMA_CH7CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH7CTL_PRIO_DPos          (9U)
#define DMA_CH7CTL_PRIO_Pos           DMA_CH7CTL_PRIO_DPos
#define DMA_CH7CTL_PRIO_Msk           (0x03UL << DMA_CH7CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH7CTL_PRIO               DMA_CH7CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 7 priority level) */
#define DMA_CH7CTL_PRIO_0             (0x01UL << DMA_CH7CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH7CTL_PRIO_1             (0x02UL << DMA_CH7CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH7CNT register  *****************/
#define DMA_CH7CNT_CNT_DPos          (0U)
#define DMA_CH7CNT_CNT_Pos           DMA_CH7CNT_CNT_DPos
#define DMA_CH7CNT_CNT_Msk           (0x01UL << DMA_CH7CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH7CNT_CNT               DMA_CH7CNT_CNT_Msk                                  /* DMA channel 7 number of data to transfer */

/******************  Bits definition for DMA_CH7PADDR register  *****************/
#define DMA_CH7PADDR_PADDR_DPos      (0U)
#define DMA_CH7PADDR_PADDR_Pos       DMA_CH7PADDR_PADDR_DPos
#define DMA_CH7PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH7PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH7PADDR_PADDR           DMA_CH7PADDR_PADDR_Msk                              /* DMA channel 7 peripheral address */

/******************  Bits definition for DMA_CH7MADDR register  *****************/
#define DMA_CH7MADDR_MADDR_DPos      (0U)
#define DMA_CH7MADDR_MADDR_Pos       DMA_CH7MADDR_MADDR_DPos
#define DMA_CH7MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH7MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH7MADDR_MADDR           DMA_CH7MADDR_MADDR_Msk                                     /* DMA channel 7 memory address */


/******************  Bits definition for DMA_CH8CTL register  *****************/
#define DMA_CH8CTL_M2M_DPos          (0U)
#define DMA_CH8CTL_M2M_Pos           DMA_CH8CTL_M2M_DPos
#define DMA_CH8CTL_M2M_Msk           (0x01UL << DMA_CH8CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH8CTL_M2M               DMA_CH8CTL_M2M_Msk                              /* DMA channel 8 memory-to-memory transfer mode */

#define DMA_CH8CTL_DIR_DPos          (1U)
#define DMA_CH8CTL_DIR_Pos           DMA_CH8CTL_DIR_DPos
#define DMA_CH8CTL_DIR_Msk           (0x01UL << DMA_CH8CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH8CTL_DIR               DMA_CH8CTL_DIR_Msk                                /* DMA channel 8 data transfer direction */

#define DMA_CH8CTL_CMEN_DPos         (2U)
#define DMA_CH8CTL_CIRC_Pos          DMA_CH8CTL_CMEN_DPos
#define DMA_CH8CTL_CIRC_Msk          (0x01UL << DMA_CH8CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH8CTL_CIRC              DMA_CH8CTL_CIRC_Msk                                /* DMA channel 8 circular mode */

#define DMA_CH8CTL_PNAGA_DPos        (3U)
#define DMA_CH8CTL_PINC_Pos          DMA_CH8CTL_PNAGA_DPos
#define DMA_CH8CTL_PINC_Msk          (0x01UL << DMA_CH8CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH8CTL_PINC              DMA_CH8CTL_PINC_Msk                                /* DMA channel 8 peripheral address increment */

#define DMA_CH8CTL_MNAGA_DPos        (4U)
#define DMA_CH8CTL_MINC_Pos          DMA_CH8CTL_MINC_DPos
#define DMA_CH8CTL_MINC_Msk          (0x01UL << DMA_CH8CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH8CTL_MINC              DMA_CH8CTL_MINC_Msk                                /* DMA channel 8 memory address increment */

#define DMA_CH8CTL_PWIDTH_DPos       (5U)
#define DMA_CH8CTL_PSIZE_Pos         DMA_CH8CTL_PWIDTH_DPos
#define DMA_CH8CTL_PSIZE_Msk         (0x03UL << DMA_CH8CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH8CTL_PSIZE             DMA_CH8CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 8 peripheral data width) */
#define DMA_CH8CTL_PSIZE_0           (0x01UL << DMA_CH8CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH8CTL_PSIZE_1           (0x02UL << DMA_CH8CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH8CTL_MWIDTH_DPos       (7U)
#define DMA_CH8CTL_MSIZE_Pos         DMA_CH8CTL_MWIDTH_DPos
#define DMA_CH8CTL_MSIZE_Msk         (0x03UL << DMA_CH8CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH8CTL_MSIZE             DMA_CH8CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 8 memory data width) */
#define DMA_CH8CTL_MSIZE_0           (0x01UL << DMA_CH8CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH8CTL_MSIZE_1           (0x02UL << DMA_CH8CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH8CTL_PRIO_DPos          (9U)
#define DMA_CH8CTL_PRIO_Pos           DMA_CH8CTL_PRIO_DPos
#define DMA_CH8CTL_PRIO_Msk           (0x03UL << DMA_CH8CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH8CTL_PRIO               DMA_CH8CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 8 priority level) */
#define DMA_CH8CTL_PRIO_0             (0x01UL << DMA_CH8CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH8CTL_PRIO_1             (0x02UL << DMA_CH8CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH8CNT register  *****************/
#define DMA_CH8CNT_CNT_DPos          (0U)
#define DMA_CH8CNT_CNT_Pos           DMA_CH8CNT_CNT_DPos
#define DMA_CH8CNT_CNT_Msk           (0x01UL << DMA_CH8CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH8CNT_CNT               DMA_CH8CNT_CNT_Msk                                  /* DMA channel 8 number of data to transfer */

/******************  Bits definition for DMA_CH8PADDR register  *****************/
#define DMA_CH8PADDR_PADDR_DPos      (0U)
#define DMA_CH8PADDR_PADDR_Pos       DMA_CH8PADDR_PADDR_DPos
#define DMA_CH8PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH8PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH8PADDR_PADDR           DMA_CH8PADDR_PADDR_Msk                              /* DMA channel 8 peripheral address */

/******************  Bits definition for DMA_CH8MADDR register  *****************/
#define DMA_CH8MADDR_MADDR_DPos      (0U)
#define DMA_CH8MADDR_MADDR_Pos       DMA_CH8MADDR_MADDR_DPos
#define DMA_CH8MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH8MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH8MADDR_MADDR           DMA_CH8MADDR_MADDR_Msk                                     /* DMA channel 8 memory address */


/******************  Bits definition for DMA_CH9CTL register  *****************/
#define DMA_CH9CTL_M2M_DPos          (0U)
#define DMA_CH9CTL_M2M_Pos           DMA_CH9CTL_M2M_DPos
#define DMA_CH9CTL_M2M_Msk           (0x01UL << DMA_CH9CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH9CTL_M2M               DMA_CH9CTL_M2M_Msk                              /* DMA channel 9 memory-to-memory transfer mode */

#define DMA_CH9CTL_DIR_DPos          (1U)
#define DMA_CH9CTL_DIR_Pos           DMA_CH9CTL_DIR_DPos
#define DMA_CH9CTL_DIR_Msk           (0x01UL << DMA_CH9CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH9CTL_DIR               DMA_CH9CTL_DIR_Msk                                /* DMA channel 9 data transfer direction */

#define DMA_CH9CTL_CMEN_DPos         (2U)
#define DMA_CH9CTL_CIRC_Pos          DMA_CH9CTL_CMEN_DPos
#define DMA_CH9CTL_CIRC_Msk          (0x01UL << DMA_CH9CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH9CTL_CIRC              DMA_CH9CTL_CIRC_Msk                                /* DMA channel 9 circular mode */

#define DMA_CH9CTL_PNAGA_DPos        (3U)
#define DMA_CH9CTL_PINC_Pos          DMA_CH9CTL_PNAGA_DPos
#define DMA_CH9CTL_PINC_Msk          (0x01UL << DMA_CH9CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH9CTL_PINC              DMA_CH9CTL_PINC_Msk                                /* DMA channel 9 peripheral address increment */

#define DMA_CH9CTL_MNAGA_DPos        (4U)
#define DMA_CH9CTL_MINC_Pos          DMA_CH9CTL_MINC_DPos
#define DMA_CH9CTL_MINC_Msk          (0x01UL << DMA_CH9CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH9CTL_MINC              DMA_CH9CTL_MINC_Msk                                /* DMA channel 9 memory address increment */

#define DMA_CH9CTL_PWIDTH_DPos       (5U)
#define DMA_CH9CTL_PSIZE_Pos         DMA_CH9CTL_PWIDTH_DPos
#define DMA_CH9CTL_PSIZE_Msk         (0x03UL << DMA_CH9CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH9CTL_PSIZE             DMA_CH9CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 9 peripheral data width) */
#define DMA_CH9CTL_PSIZE_0           (0x01UL << DMA_CH9CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH9CTL_PSIZE_1           (0x02UL << DMA_CH9CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH9CTL_MWIDTH_DPos       (7U)
#define DMA_CH9CTL_MSIZE_Pos         DMA_CH9CTL_MWIDTH_DPos
#define DMA_CH9CTL_MSIZE_Msk         (0x03UL << DMA_CH9CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH9CTL_MSIZE             DMA_CH9CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 9 memory data width) */
#define DMA_CH9CTL_MSIZE_0           (0x01UL << DMA_CH9CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH9CTL_MSIZE_1           (0x02UL << DMA_CH9CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH9CTL_PRIO_DPos          (9U)
#define DMA_CH9CTL_PRIO_Pos           DMA_CH9CTL_PRIO_DPos
#define DMA_CH9CTL_PRIO_Msk           (0x03UL << DMA_CH9CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH9CTL_PRIO               DMA_CH9CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 9 priority level)  */
#define DMA_CH9CTL_PRIO_0             (0x01UL << DMA_CH9CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH9CTL_PRIO_1             (0x02UL << DMA_CH9CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH9CNT register  *****************/
#define DMA_CH9CNT_CNT_DPos          (0U)
#define DMA_CH9CNT_CNT_Pos           DMA_CH9CNT_CNT_DPos
#define DMA_CH9CNT_CNT_Msk           (0x01UL << DMA_CH9CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH9CNT_CNT               DMA_CH9CNT_CNT_Msk                                  /* DMA channel 9 number of data to transfer */

/******************  Bits definition for DMA_CH9PADDR register  *****************/
#define DMA_CH9PADDR_PADDR_DPos      (0U)
#define DMA_CH9PADDR_PADDR_Pos       DMA_CH9PADDR_PADDR_DPos
#define DMA_CH9PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH9PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH9PADDR_PADDR           DMA_CH9PADDR_PADDR_Msk                              /* DMA channel 9 peripheral address */

/******************  Bits definition for DMA_CH9MADDR register  *****************/
#define DMA_CH9MADDR_MADDR_DPos      (0U)
#define DMA_CH9MADDR_MADDR_Pos       DMA_CH9MADDR_MADDR_DPos
#define DMA_CH9MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH9MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH9MADDR_MADDR           DMA_CH9MADDR_MADDR_Msk                                     /* DMA channel 9 memory address */



/******************  Bits definition for DMA_CH10CTL register  *****************/
#define DMA_CH10CTL_M2M_DPos          (0U)
#define DMA_CH10CTL_M2M_Pos           DMA_CH10CTL_M2M_DPos
#define DMA_CH10CTL_M2M_Msk           (0x01UL << DMA_CH10CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH10CTL_M2M               DMA_CH10CTL_M2M_Msk                              /* DMA channel 10 memory-to-memory transfer mode */

#define DMA_CH10CTL_DIR_DPos          (1U)
#define DMA_CH10CTL_DIR_Pos           DMA_CH10CTL_DIR_DPos
#define DMA_CH10CTL_DIR_Msk           (0x01UL << DMA_CH10CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH10CTL_DIR               DMA_CH10CTL_DIR_Msk                                /* DMA channel 10 data transfer direction */

#define DMA_CH10CTL_CMEN_DPos         (2U)
#define DMA_CH10CTL_CIRC_Pos          DMA_CH10CTL_CMEN_DPos
#define DMA_CH10CTL_CIRC_Msk          (0x01UL << DMA_CH10CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH10CTL_CIRC              DMA_CH10CTL_CIRC_Msk                                /* DMA channel 10 circular mode */

#define DMA_CH10CTL_PNAGA_DPos        (3U)
#define DMA_CH10CTL_PINC_Pos          DMA_CH10CTL_PNAGA_DPos
#define DMA_CH10CTL_PINC_Msk          (0x01UL << DMA_CH10CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH10CTL_PINC              DMA_CH10CTL_PINC_Msk                                /* DMA channel 10 peripheral address increment */

#define DMA_CH10CTL_MNAGA_DPos        (4U)
#define DMA_CH10CTL_MINC_Pos          DMA_CH10CTL_MINC_DPos
#define DMA_CH10CTL_MINC_Msk          (0x01UL << DMA_CH10CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH10CTL_MINC              DMA_CH10CTL_MINC_Msk                                /* DMA channel 10 memory address increment */

#define DMA_CH10CTL_PWIDTH_DPos       (5U)
#define DMA_CH10CTL_PSIZE_Pos         DMA_CH10CTL_PWIDTH_DPos
#define DMA_CH10CTL_PSIZE_Msk         (0x03UL << DMA_CH10CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH10CTL_PSIZE             DMA_CH10CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 10 peripheral data width) */
#define DMA_CH10CTL_PSIZE_0           (0x01UL << DMA_CH10CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH10CTL_PSIZE_1           (0x02UL << DMA_CH10CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH10CTL_MWIDTH_DPos       (7U)
#define DMA_CH10CTL_MSIZE_Pos         DMA_CH10CTL_MWIDTH_DPos
#define DMA_CH10CTL_MSIZE_Msk         (0x03UL << DMA_CH10CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH10CTL_MSIZE             DMA_CH10CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 10 memory data width) */
#define DMA_CH10CTL_MSIZE_0           (0x01UL << DMA_CH10CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH10CTL_MSIZE_1           (0x02UL << DMA_CH10CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH10CTL_PRIO_DPos          (9U)
#define DMA_CH10CTL_PRIO_Pos           DMA_CH10CTL_PRIO_DPos
#define DMA_CH10CTL_PRIO_Msk           (0x03UL << DMA_CH10CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH10CTL_PRIO               DMA_CH10CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 10 priority level) */
#define DMA_CH10CTL_PRIO_0             (0x01UL << DMA_CH10CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH10CTL_PRIO_1             (0x02UL << DMA_CH10CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH10CNT register  *****************/
#define DMA_CH10CNT_CNT_DPos          (0U)
#define DMA_CH10CNT_CNT_Pos           DMA_CH10CNT_CNT_DPos
#define DMA_CH10CNT_CNT_Msk           (0x01UL << DMA_CH10CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH10CNT_CNT               DMA_CH10CNT_CNT_Msk                                  /* DMA channel 10 number of data to transfer */

/******************  Bits definition for DMA_CH10PADDR register  *****************/
#define DMA_CH10PADDR_PADDR_DPos      (0U)
#define DMA_CH10PADDR_PADDR_Pos       DMA_CH10PADDR_PADDR_DPos
#define DMA_CH10PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH10PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH10PADDR_PADDR           DMA_CH10PADDR_PADDR_Msk                              /* DMA channel 10 peripheral address */

/******************  Bits definition for DMA_CH10MADDR register  *****************/
#define DMA_CH10MADDR_MADDR_DPos      (0U)
#define DMA_CH10MADDR_MADDR_Pos       DMA_CH10MADDR_MADDR_DPos
#define DMA_CH10MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH10MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH10MADDR_MADDR           DMA_CH10MADDR_MADDR_Msk                                     /* DMA channel 10 memory address */


/******************  Bits definition for DMA_CH11CTL register  *****************/
#define DMA_CH11CTL_M2M_DPos          (0U)
#define DMA_CH11CTL_M2M_Pos           DMA_CH11CTL_M2M_DPos
#define DMA_CH11CTL_M2M_Msk           (0x01UL << DMA_CH11CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH11CTL_M2M               DMA_CH11CTL_M2M_Msk                              /* DMA channel 11 memory-to-memory transfer mode */

#define DMA_CH11CTL_DIR_DPos          (1U)
#define DMA_CH11CTL_DIR_Pos           DMA_CH11CTL_DIR_DPos
#define DMA_CH11CTL_DIR_Msk           (0x01UL << DMA_CH11CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH11CTL_DIR               DMA_CH11CTL_DIR_Msk                                /* DMA channel 11 data transfer direction */

#define DMA_CH11CTL_CMEN_DPos         (2U)
#define DMA_CH11CTL_CIRC_Pos          DMA_CH11CTL_CMEN_DPos
#define DMA_CH11CTL_CIRC_Msk          (0x01UL << DMA_CH11CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH11CTL_CIRC              DMA_CH11CTL_CIRC_Msk                                /* DMA channel 11 circular mode */

#define DMA_CH11CTL_PNAGA_DPos        (3U)
#define DMA_CH11CTL_PINC_Pos          DMA_CH11CTL_PNAGA_DPos
#define DMA_CH11CTL_PINC_Msk          (0x01UL << DMA_CH11CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH11CTL_PINC              DMA_CH11CTL_PINC_Msk                                /* DMA channel 11 peripheral address increment */

#define DMA_CH11CTL_MNAGA_DPos        (4U)
#define DMA_CH11CTL_MINC_Pos          DMA_CH11CTL_MINC_DPos
#define DMA_CH11CTL_MINC_Msk          (0x01UL << DMA_CH11CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH11CTL_MINC              DMA_CH11CTL_MINC_Msk                                /* DMA channel 11 memory address increment */

#define DMA_CH11CTL_PWIDTH_DPos       (5U)
#define DMA_CH11CTL_PSIZE_Pos         DMA_CH11CTL_PWIDTH_DPos
#define DMA_CH11CTL_PSIZE_Msk         (0x03UL << DMA_CH11CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH11CTL_PSIZE             DMA_CH11CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 11 peripheral data width) */
#define DMA_CH11CTL_PSIZE_0           (0x01UL << DMA_CH11CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH11CTL_PSIZE_1           (0x02UL << DMA_CH11CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH11CTL_MWIDTH_DPos       (7U)
#define DMA_CH11CTL_MSIZE_Pos         DMA_CH11CTL_MWIDTH_DPos
#define DMA_CH11CTL_MSIZE_Msk         (0x03UL << DMA_CH11CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH11CTL_MSIZE             DMA_CH11CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 11 memory data width) */
#define DMA_CH11CTL_MSIZE_0           (0x01UL << DMA_CH11CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH11CTL_MSIZE_1           (0x02UL << DMA_CH11CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH11CTL_PRIO_DPos          (9U)
#define DMA_CH11CTL_PRIO_Pos           DMA_CH11CTL_PRIO_DPos
#define DMA_CH11CTL_PRIO_Msk           (0x03UL << DMA_CH11CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH11CTL_PRIO               DMA_CH11CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 11 priority level) */
#define DMA_CH11CTL_PRIO_0             (0x01UL << DMA_CH11CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH11CTL_PRIO_1             (0x02UL << DMA_CH11CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH11CNT register  *****************/
#define DMA_CH11CNT_CNT_DPos          (0U)
#define DMA_CH11CNT_CNT_Pos           DMA_CH11CNT_CNT_DPos
#define DMA_CH11CNT_CNT_Msk           (0x01UL << DMA_CH11CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH11CNT_CNT               DMA_CH11CNT_CNT_Msk                                  /* DMA channel 11 number of data to transfer */

/******************  Bits definition for DMA_CH11PADDR register  *****************/
#define DMA_CH11PADDR_PADDR_DPos      (0U)
#define DMA_CH11PADDR_PADDR_Pos       DMA_CH11PADDR_PADDR_DPos
#define DMA_CH11PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH11PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH11PADDR_PADDR           DMA_CH11PADDR_PADDR_Msk                              /* DMA channel 11 peripheral address */

/******************  Bits definition for DMA_CH11MADDR register  *****************/
#define DMA_CH11MADDR_MADDR_DPos      (0U)
#define DMA_CH11MADDR_MADDR_Pos       DMA_CH11MADDR_MADDR_DPos
#define DMA_CH11MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH11MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH11MADDR_MADDR           DMA_CH11MADDR_MADDR_Msk                                     /* DMA channel 11 memory address */



/******************  Bits definition for DMA_CH7CTL register  *****************/
#define DMA_CH7CTL_M2M_DPos          (0U)
#define DMA_CH7CTL_M2M_Pos           DMA_CH7CTL_M2M_DPos
#define DMA_CH7CTL_M2M_Msk           (0x01UL << DMA_CH7CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH7CTL_M2M               DMA_CH7CTL_M2M_Msk                              /* DMA channel 7 memory-to-memory transfer mode */

#define DMA_CH7CTL_DIR_DPos          (1U)
#define DMA_CH7CTL_DIR_Pos           DMA_CH7CTL_DIR_DPos
#define DMA_CH7CTL_DIR_Msk           (0x01UL << DMA_CH7CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH7CTL_DIR               DMA_CH7CTL_DIR_Msk                                /* DMA channel 7 data transfer direction */

#define DMA_CH7CTL_CMEN_DPos         (2U)
#define DMA_CH7CTL_CIRC_Pos          DMA_CH7CTL_CMEN_DPos
#define DMA_CH7CTL_CIRC_Msk          (0x01UL << DMA_CH7CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH7CTL_CIRC              DMA_CH7CTL_CIRC_Msk                                /* DMA channel 7 circular mode */

#define DMA_CH7CTL_PNAGA_DPos        (3U)
#define DMA_CH7CTL_PINC_Pos          DMA_CH7CTL_PNAGA_DPos
#define DMA_CH7CTL_PINC_Msk          (0x01UL << DMA_CH7CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH7CTL_PINC              DMA_CH7CTL_PINC_Msk                                /* DMA channel 7 peripheral address increment */

#define DMA_CH7CTL_MNAGA_DPos        (4U)
#define DMA_CH7CTL_MINC_Pos          DMA_CH7CTL_MINC_DPos
#define DMA_CH7CTL_MINC_Msk          (0x01UL << DMA_CH7CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH7CTL_MINC              DMA_CH7CTL_MINC_Msk                                /* DMA channel 7 memory address increment */

#define DMA_CH7CTL_PWIDTH_DPos       (5U)
#define DMA_CH7CTL_PSIZE_Pos         DMA_CH7CTL_PWIDTH_DPos
#define DMA_CH7CTL_PSIZE_Msk         (0x03UL << DMA_CH7CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH7CTL_PSIZE             DMA_CH7CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 7 peripheral data width) */
#define DMA_CH7CTL_PSIZE_0           (0x01UL << DMA_CH7CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH7CTL_PSIZE_1           (0x02UL << DMA_CH7CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH7CTL_MWIDTH_DPos       (7U)
#define DMA_CH7CTL_MSIZE_Pos         DMA_CH7CTL_MWIDTH_DPos
#define DMA_CH7CTL_MSIZE_Msk         (0x03UL << DMA_CH7CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH7CTL_MSIZE             DMA_CH7CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 7 memory data width) */
#define DMA_CH7CTL_MSIZE_0           (0x01UL << DMA_CH7CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH7CTL_MSIZE_1           (0x02UL << DMA_CH7CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH7CTL_PRIO_DPos          (9U)
#define DMA_CH7CTL_PRIO_Pos           DMA_CH7CTL_PRIO_DPos
#define DMA_CH7CTL_PRIO_Msk           (0x03UL << DMA_CH7CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH7CTL_PRIO               DMA_CH7CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 7 priority level) */
#define DMA_CH7CTL_PRIO_0             (0x01UL << DMA_CH7CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH7CTL_PRIO_1             (0x02UL << DMA_CH7CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH7CNT register  *****************/
#define DMA_CH7CNT_CNT_DPos          (0U)
#define DMA_CH7CNT_CNT_Pos           DMA_CH7CNT_CNT_DPos
#define DMA_CH7CNT_CNT_Msk           (0x01UL << DMA_CH7CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH7CNT_CNT               DMA_CH7CNT_CNT_Msk                                  /* DMA channel 7 number of data to transfer */

/******************  Bits definition for DMA_CH7PADDR register  *****************/
#define DMA_CH7PADDR_PADDR_DPos      (0U)
#define DMA_CH7PADDR_PADDR_Pos       DMA_CH7PADDR_PADDR_DPos
#define DMA_CH7PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH7PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH7PADDR_PADDR           DMA_CH7PADDR_PADDR_Msk                              /* DMA channel 7 peripheral address */

/******************  Bits definition for DMA_CH7MADDR register  *****************/
#define DMA_CH7MADDR_MADDR_DPos      (0U)
#define DMA_CH7MADDR_MADDR_Pos       DMA_CH7MADDR_MADDR_DPos
#define DMA_CH7MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH7MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH7MADDR_MADDR           DMA_CH7MADDR_MADDR_Msk                                     /* DMA channel 7 memory address */


/******************  Bits definition for DMA_CH13CTL register  *****************/
#define DMA_CH13CTL_M2M_DPos          (0U)
#define DMA_CH13CTL_M2M_Pos           DMA_CH13CTL_M2M_DPos
#define DMA_CH13CTL_M2M_Msk           (0x01UL << DMA_CH13CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH13CTL_M2M               DMA_CH13CTL_M2M_Msk                              /* DMA channel 13 memory-to-memory transfer mode */

#define DMA_CH13CTL_DIR_DPos          (1U)
#define DMA_CH13CTL_DIR_Pos           DMA_CH13CTL_DIR_DPos
#define DMA_CH13CTL_DIR_Msk           (0x01UL << DMA_CH13CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH13CTL_DIR               DMA_CH13CTL_DIR_Msk                                /* DMA channel 13 data transfer direction */

#define DMA_CH13CTL_CMEN_DPos         (2U)
#define DMA_CH13CTL_CIRC_Pos          DMA_CH13CTL_CMEN_DPos
#define DMA_CH13CTL_CIRC_Msk          (0x01UL << DMA_CH13CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH13CTL_CIRC              DMA_CH13CTL_CIRC_Msk                                /* DMA channel 13 circular mode */

#define DMA_CH13CTL_PNAGA_DPos        (3U)
#define DMA_CH13CTL_PINC_Pos          DMA_CH13CTL_PNAGA_DPos
#define DMA_CH13CTL_PINC_Msk          (0x01UL << DMA_CH13CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH13CTL_PINC              DMA_CH13CTL_PINC_Msk                                /* DMA channel 13 peripheral address increment */

#define DMA_CH13CTL_MNAGA_DPos        (4U)
#define DMA_CH13CTL_MINC_Pos          DMA_CH13CTL_MINC_DPos
#define DMA_CH13CTL_MINC_Msk          (0x01UL << DMA_CH13CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH13CTL_MINC              DMA_CH13CTL_MINC_Msk                                /* DMA channel 13 memory address increment */

#define DMA_CH13CTL_PWIDTH_DPos       (5U)
#define DMA_CH13CTL_PSIZE_Pos         DMA_CH13CTL_PWIDTH_DPos
#define DMA_CH13CTL_PSIZE_Msk         (0x03UL << DMA_CH13CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH13CTL_PSIZE             DMA_CH13CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 13 peripheral data width) */
#define DMA_CH13CTL_PSIZE_0           (0x01UL << DMA_CH13CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH13CTL_PSIZE_1           (0x02UL << DMA_CH13CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH13CTL_MWIDTH_DPos       (7U)
#define DMA_CH13CTL_MSIZE_Pos         DMA_CH13CTL_MWIDTH_DPos
#define DMA_CH13CTL_MSIZE_Msk         (0x03UL << DMA_CH13CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH13CTL_MSIZE             DMA_CH13CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 13 memory data width) */
#define DMA_CH13CTL_MSIZE_0           (0x01UL << DMA_CH13CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH13CTL_MSIZE_1           (0x02UL << DMA_CH13CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH13CTL_PRIO_DPos          (9U)
#define DMA_CH13CTL_PRIO_Pos           DMA_CH13CTL_PRIO_DPos
#define DMA_CH13CTL_PRIO_Msk           (0x03UL << DMA_CH13CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH13CTL_PRIO               DMA_CH13CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 13 priority level) */
#define DMA_CH13CTL_PRIO_0             (0x01UL << DMA_CH13CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH13CTL_PRIO_1             (0x02UL << DMA_CH13CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH13CNT register  *****************/
#define DMA_CH13CNT_CNT_DPos          (0U)
#define DMA_CH13CNT_CNT_Pos           DMA_CH13CNT_CNT_DPos
#define DMA_CH13CNT_CNT_Msk           (0x01UL << DMA_CH13CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH13CNT_CNT               DMA_CH13CNT_CNT_Msk                                  /* DMA channel 13 number of data to transfer */

/******************  Bits definition for DMA_CH13PADDR register  *****************/
#define DMA_CH13PADDR_PADDR_DPos      (0U)
#define DMA_CH13PADDR_PADDR_Pos       DMA_CH13PADDR_PADDR_DPos
#define DMA_CH13PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH13PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH13PADDR_PADDR           DMA_CH13PADDR_PADDR_Msk                              /* DMA channel 13 peripheral address */

/******************  Bits definition for DMA_CH13MADDR register  *****************/
#define DMA_CH13MADDR_MADDR_DPos      (0U)
#define DMA_CH13MADDR_MADDR_Pos       DMA_CH13MADDR_MADDR_DPos
#define DMA_CH13MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH13MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH13MADDR_MADDR           DMA_CH13MADDR_MADDR_Msk                                     /* DMA channel 13 memory address */



/******************  Bits definition for DMA_CH14CTL register  *****************/
#define DMA_CH14CTL_M2M_DPos          (0U)
#define DMA_CH14CTL_M2M_Pos           DMA_CH14CTL_M2M_DPos
#define DMA_CH14CTL_M2M_Msk           (0x01UL << DMA_CH14CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH14CTL_M2M               DMA_CH14CTL_M2M_Msk                              /* DMA channel 14 memory-to-memory transfer mode */

#define DMA_CH14CTL_DIR_DPos          (1U)
#define DMA_CH14CTL_DIR_Pos           DMA_CH14CTL_DIR_DPos
#define DMA_CH14CTL_DIR_Msk           (0x01UL << DMA_CH14CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH14CTL_DIR               DMA_CH14CTL_DIR_Msk                                /* DMA channel 14 data transfer direction */

#define DMA_CH14CTL_CMEN_DPos         (2U)
#define DMA_CH14CTL_CIRC_Pos          DMA_CH14CTL_CMEN_DPos
#define DMA_CH14CTL_CIRC_Msk          (0x01UL << DMA_CH14CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH14CTL_CIRC              DMA_CH14CTL_CIRC_Msk                                /* DMA channel 14 circular mode */

#define DMA_CH14CTL_PNAGA_DPos        (3U)
#define DMA_CH14CTL_PINC_Pos          DMA_CH14CTL_PNAGA_DPos
#define DMA_CH14CTL_PINC_Msk          (0x01UL << DMA_CH14CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH14CTL_PINC              DMA_CH14CTL_PINC_Msk                                /* DMA channel 14 peripheral address increment */

#define DMA_CH14CTL_MNAGA_DPos        (4U)
#define DMA_CH14CTL_MINC_Pos          DMA_CH14CTL_MINC_DPos
#define DMA_CH14CTL_MINC_Msk          (0x01UL << DMA_CH14CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH14CTL_MINC              DMA_CH14CTL_MINC_Msk                                /* DMA channel 14 memory address increment */

#define DMA_CH14CTL_PWIDTH_DPos       (5U)
#define DMA_CH14CTL_PSIZE_Pos         DMA_CH14CTL_PWIDTH_DPos
#define DMA_CH14CTL_PSIZE_Msk         (0x03UL << DMA_CH14CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH14CTL_PSIZE             DMA_CH14CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 14 peripheral data width) */
#define DMA_CH14CTL_PSIZE_0           (0x01UL << DMA_CH14CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH14CTL_PSIZE_1           (0x02UL << DMA_CH14CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH14CTL_MWIDTH_DPos       (7U)
#define DMA_CH14CTL_MSIZE_Pos         DMA_CH14CTL_MWIDTH_DPos
#define DMA_CH14CTL_MSIZE_Msk         (0x03UL << DMA_CH14CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH14CTL_MSIZE             DMA_CH14CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 14 memory data width) */
#define DMA_CH14CTL_MSIZE_0           (0x01UL << DMA_CH14CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH14CTL_MSIZE_1           (0x02UL << DMA_CH14CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH14CTL_PRIO_DPos          (9U)
#define DMA_CH14CTL_PRIO_Pos           DMA_CH14CTL_PRIO_DPos
#define DMA_CH14CTL_PRIO_Msk           (0x03UL << DMA_CH14CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH14CTL_PRIO               DMA_CH14CTL_PRIO_Msk                                /* PRIO reg[1:0] bits(DMA channel 14 priority level) */
#define DMA_CH14CTL_PRIO_0             (0x01UL << DMA_CH14CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH14CTL_PRIO_1             (0x02UL << DMA_CH14CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH14CNT register  *****************/
#define DMA_CH14CNT_CNT_DPos          (0U)
#define DMA_CH14CNT_CNT_Pos           DMA_CH14CNT_CNT_DPos
#define DMA_CH14CNT_CNT_Msk           (0x01UL << DMA_CH14CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH14CNT_CNT               DMA_CH14CNT_CNT_Msk                                  /* DMA channel 14 number of data to transfer */

/******************  Bits definition for DMA_CH14PADDR register  *****************/
#define DMA_CH14PADDR_PADDR_DPos      (0U)
#define DMA_CH14PADDR_PADDR_Pos       DMA_CH14PADDR_PADDR_DPos
#define DMA_CH14PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH14PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH14PADDR_PADDR           DMA_CH14PADDR_PADDR_Msk                              /* DMA channel 14 peripheral address */

/******************  Bits definition for DMA_CH14MADDR register  *****************/
#define DMA_CH14MADDR_MADDR_DPos      (0U)
#define DMA_CH14MADDR_MADDR_Pos       DMA_CH14MADDR_MADDR_DPos
#define DMA_CH14MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH14MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH14MADDR_MADDR           DMA_CH14MADDR_MADDR_Msk                                     /* DMA channel 14 memory address */


/******************  Bits definition for DMA_CH15CTL register  *****************/
#define DMA_CH15CTL_M2M_DPos          (0U)
#define DMA_CH15CTL_M2M_Pos           DMA_CH15CTL_M2M_DPos
#define DMA_CH15CTL_M2M_Msk           (0x01UL << DMA_CH15CTL_M2M_Pos)                  /* 0x00000001 */
#define DMA_CH15CTL_M2M               DMA_CH15CTL_M2M_Msk                              /* DMA channel 15 memory-to-memory transfer mode */

#define DMA_CH15CTL_DIR_DPos          (1U)
#define DMA_CH15CTL_DIR_Pos           DMA_CH15CTL_DIR_DPos
#define DMA_CH15CTL_DIR_Msk           (0x01UL << DMA_CH15CTL_DIR_Pos)                    /* 0x00000002 */
#define DMA_CH15CTL_DIR               DMA_CH15CTL_DIR_Msk                                /* DMA channel 15 data transfer direction */

#define DMA_CH15CTL_CMEN_DPos         (2U)
#define DMA_CH15CTL_CIRC_Pos          DMA_CH15CTL_CMEN_DPos
#define DMA_CH15CTL_CIRC_Msk          (0x01UL << DMA_CH15CTL_CIRC_Pos)                    /* 0x00000004 */
#define DMA_CH15CTL_CIRC              DMA_CH15CTL_CIRC_Msk                                /* DMA channel 15 circular mode */

#define DMA_CH15CTL_PNAGA_DPos        (3U)
#define DMA_CH15CTL_PINC_Pos          DMA_CH15CTL_PNAGA_DPos
#define DMA_CH15CTL_PINC_Msk          (0x01UL << DMA_CH15CTL_PINC_Pos)                    /* 0x00000008 */
#define DMA_CH15CTL_PINC              DMA_CH15CTL_PINC_Msk                                /* DMA channel 15 peripheral address increment */

#define DMA_CH15CTL_MNAGA_DPos        (4U)
#define DMA_CH15CTL_MINC_Pos          DMA_CH15CTL_MINC_DPos
#define DMA_CH15CTL_MINC_Msk          (0x01UL << DMA_CH15CTL_MINC_Pos)                    /* 0x00000010 */
#define DMA_CH15CTL_MINC              DMA_CH15CTL_MINC_Msk                                /* DMA channel 15 memory address increment */

#define DMA_CH15CTL_PWIDTH_DPos       (5U)
#define DMA_CH15CTL_PSIZE_Pos         DMA_CH15CTL_PWIDTH_DPos
#define DMA_CH15CTL_PSIZE_Msk         (0x03UL << DMA_CH15CTL_PSIZE_Pos)                    /* 0x00000060 */
#define DMA_CH15CTL_PSIZE             DMA_CH15CTL_PSIZE_Msk                                /* PWIDTH reg[1:0] bits( DMA channel 15 peripheral data width) */
#define DMA_CH15CTL_PSIZE_0           (0x01UL << DMA_CH15CTL_PSIZE_Pos)                    /* 0x00000020 */
#define DMA_CH15CTL_PSIZE_1           (0x02UL << DMA_CH15CTL_PSIZE_Pos)                    /* 0x00000040 */ 

#define DMA_CH15CTL_MWIDTH_DPos       (7U)
#define DMA_CH15CTL_MSIZE_Pos         DMA_CH15CTL_MWIDTH_DPos
#define DMA_CH15CTL_MSIZE_Msk         (0x03UL << DMA_CH15CTL_MSIZE_Pos)                    /* 0x00000180 */
#define DMA_CH15CTL_MSIZE             DMA_CH15CTL_MSIZE_Msk                                /* MWIDTH reg[1:0] bits( DMA channel 15 memory data width) */
#define DMA_CH15CTL_MSIZE_0           (0x01UL << DMA_CH15CTL_MSIZE_Pos)                    /* 0x00000080 */
#define DMA_CH15CTL_MSIZE_1           (0x02UL << DMA_CH15CTL_MSIZE_Pos)                    /* 0x00000100 */ 

#define DMA_CH15CTL_PRIO_DPos          (9U)
#define DMA_CH15CTL_PRIO_Pos           DMA_CH15CTL_PRIO_DPos
#define DMA_CH15CTL_PRIO_Msk           (0x03UL << DMA_CH15CTL_PRIO_Pos)                    /* 0x00000C00 */
#define DMA_CH15CTL_PRIO               DMA_CH15CTL_PRIO_Msk                                /*PRIO reg[1:0] bits(DMA channel 15 priority level) */
#define DMA_CH15CTL_PRIO_0             (0x01UL << DMA_CH15CTL_PRIO_Pos)                    /* 0x00000200 */
#define DMA_CH15CTL_PRIO_1             (0x02UL << DMA_CH15CTL_PRIO_Pos)                    /* 0x00000400 */ 

/******************  Bits definition for DMA_CH15CNT register  *****************/
#define DMA_CH15CNT_CNT_DPos          (0U)
#define DMA_CH15CNT_CNT_Pos           DMA_CH15CNT_CNT_DPos
#define DMA_CH15CNT_CNT_Msk           (0x01UL << DMA_CH15CNT_CNT_Pos)                      /* 0x0000ffff */
#define DMA_CH15CNT_CNT               DMA_CH15CNT_CNT_Msk                                  /* DMA channel 15 number of data to transfer */

/******************  Bits definition for DMA_CH15PADDR register  *****************/
#define DMA_CH15PADDR_PADDR_DPos      (0U)
#define DMA_CH15PADDR_PADDR_Pos       DMA_CH15PADDR_PADDR_DPos
#define DMA_CH15PADDR_PADDR_Msk       (0xffffffffUL<< DMA_CH15PADDR_PADDR_Pos)             /* 0xffffffff */
#define DMA_CH15PADDR_PADDR           DMA_CH15PADDR_PADDR_Msk                              /* DMA channel 15 peripheral address */

/******************  Bits definition for DMA_CH15MADDR register  *****************/
#define DMA_CH15MADDR_MADDR_DPos      (0U)
#define DMA_CH15MADDR_MADDR_Pos       DMA_CH15MADDR_MADDR_DPos
#define DMA_CH15MADDR_MADDR_Msk       (0xffffffffUL<< DMA_CH15MADDR_MADDR_Pos)                    /* 0xffffffff */
#define DMA_CH15MADDR_MADDR           DMA_CH15MADDR_MADDR_Msk                                     /* DMA channel 15 memory address */

/******************  Bits definition for DMA_PTCH0 register  *****************/
#define DMA_PTCH0_CH0PT_DPos          (0)
#define DMA_PTCH0_CH0PT_Pos           DMA_PTCH0_CH0PT_DPos
#define DMA_PTCH0_CH0PT_Msk           (0x0fUL<<DMA_PTCH0_CH0PT_Pos)                    /* 0x0000000f */
#define DMA_PTCH0_CH0PT               DMA_PTCH0_CH0PT_Msk                              /* DMA channel 0 peripheral interface */

#define DMA_PTCH0_CH1PT_DPos          (4)
#define DMA_PTCH0_CH1PT_Pos           DMA_PTCH0_CH1PT_DPos
#define DMA_PTCH0_CH1PT_Msk           (0x0fUL<<DMA_PTCH0_CH1PT_Pos)                    /* 0x000000f0 */
#define DMA_PTCH0_CH1PT               DMA_PTCH0_CH1PT_Msk                              /* DMA channel 1 peripheral interface */

#define DMA_PTCH0_CH2PT_DPos          (8)
#define DMA_PTCH0_CH2PT_Pos           DMA_PTCH0_CH2PT_DPos
#define DMA_PTCH0_CH2PT_Msk           (0x0fUL<<DMA_PTCH0_CH2PT_Pos)                    /* 0x00000f00 */
#define DMA_PTCH0_CH2PT               DMA_PTCH0_CH2PT_Msk                              /* DMA channel 2 peripheral interface */

#define DMA_PTCH0_CH3PT_DPos          (7)
#define DMA_PTCH0_CH3PT_Pos           DMA_PTCH0_CH3PT_DPos
#define DMA_PTCH0_CH3PT_Msk           (0x0fUL<<DMA_PTCH0_CH3PT_Pos)                    /* 0x0000f000 */
#define DMA_PTCH0_CH3PT               DMA_PTCH0_CH3PT_Msk                              /* DMA channel 3 peripheral interface */

#define DMA_PTCH0_CH4PT_DPos          (16)
#define DMA_PTCH0_CH4PT_Pos           DMA_PTCH0_CH4PT_DPos
#define DMA_PTCH0_CH4PT_Msk           (0x0fUL<<DMA_PTCH0_CH4PT_Pos)                    /* 0x000f0000 */
#define DMA_PTCH0_CH4PT               DMA_PTCH0_CH4PT_Msk                              /* DMA  channel 4 peripheral interface */

#define DMA_PTCH0_CH5PT_DPos          (20)
#define DMA_PTCH0_CH5PT_Pos           DMA_PTCH0_CH5PT_DPos
#define DMA_PTCH0_CH5PT_Msk           (0x0fUL<<DMA_PTCH0_CH5PT_Pos)                    /* 0x00f00000*/
#define DMA_PTCH0_CH5PT               DMA_PTCH0_CH5PT_Msk                              /* DMA  channel 5 peripheral interface */

#define DMA_PTCH0_CH6PT_DPos          (24)
#define DMA_PTCH0_CH6PT_Pos           DMA_PTCH0_CH6PT_DPos
#define DMA_PTCH0_CH6PT_Msk           (0x0fUL<<DMA_PTCH0_CH6PT_Pos)                    /* 0x0f000000*/
#define DMA_PTCH0_CH6PT               DMA_PTCH0_CH6PT_Msk                              /* DMA  channel 6 peripheral interface */

#define DMA_PTCH0_CH7PT_DPos          (28)
#define DMA_PTCH0_CH7PT_Pos           DMA_PTCH0_CH7PT_DPos
#define DMA_PTCH0_CH7PT_Msk           (0x0fUL<<DMA_PTCH0_CH7PT_Pos)                    /* 0xf0000000*/
#define DMA_PTCH0_CH7PT               DMA_PTCH0_CH7PT_Msk                              /* DMA  channel 7 peripheral interface */

/******************  Bits definition for DMA_PTCH1 register  *****************/
#define DMA_PTCH1_CH8PT_DPos          (0)
#define DMA_PTCH1_CH8PT_Pos           DMA_PTCH1_CH8PT_DPos
#define DMA_PTCH1_CH8PT_Msk           (0x0fUL<<DMA_PTCH1_CH8PT_Pos)                    /* 0x0000000f */
#define DMA_PTCH1_CH8PT               DMA_PTCH1_CH8PT_Msk                              /* DMA  channel 8 peripheral interface */

#define DMA_PTCH1_CH9PT_DPos          (4)
#define DMA_PTCH1_CH9PT_Pos           DMA_PTCH1_CH9PT_DPos
#define DMA_PTCH1_CH9PT_Msk           (0x0fUL<<DMA_PTCH1_CH9PT_Pos)                    /* 0x000000f0 */
#define DMA_PTCH1_CH9PT               DMA_PTCH1_CH9PT_Msk                              /* DMA  channel 9 peripheral interface */

#define DMA_PTCH1_CH10PT_DPos          (8)
#define DMA_PTCH1_CH10PT_Pos           DMA_PTCH1_CH10PT_DPos
#define DMA_PTCH1_CH10PT_Msk           (0x0fUL<<DMA_PTCH1_CH10PT_Pos)                    /* 0x00000f00 */
#define DMA_PTCH1_CH10PT               DMA_PTCH1_CH10PT_Msk                              /* DMA  channel 10 peripheral interface */

#define DMA_PTCH1_CH11PT_DPos          (7)
#define DMA_PTCH1_CH11PT_Pos           DMA_PTCH1_CH11PT_DPos
#define DMA_PTCH1_CH11PT_Msk           (0x0fUL<<DMA_PTCH1_CH11PT_Pos)                    /* 0x0000f000 */
#define DMA_PTCH1_CH11PT               DMA_PTCH1_CH11PT_Msk                              /* DMA  channel 11 peripheral interface */

#define DMA_PTCH1_CH7PT_DPos          (16)
#define DMA_PTCH1_CH7PT_Pos           DMA_PTCH1_CH7PT_DPos
#define DMA_PTCH1_CH7PT_Msk           (0x0fUL<<DMA_PTCH1_CH7PT_Pos)                    /* 0x000f0000 */
#define DMA_PTCH1_CH7PT               DMA_PTCH1_CH7PT_Msk                              /* DMA  channel 7 peripheral interface */

#define DMA_PTCH1_CH13PT_DPos          (20)
#define DMA_PTCH1_CH13PT_Pos           DMA_PTCH1_CH13PT_DPos
#define DMA_PTCH1_CH13PT_Msk           (0x0fUL<<DMA_PTCH1_CH13PT_Pos)                    /* 0x00f00000 */
#define DMA_PTCH1_CH13PT               DMA_PTCH1_CH13PT_Msk                              /* DMA  channel 13 peripheral interface */


#define DMA_PTCH1_CH14PT_DPos          (24)
#define DMA_PTCH1_CH14PT_Pos           DMA_PTCH1_CH14PT_DPos
#define DMA_PTCH1_CH14PT_Msk           (0x0fUL<<DMA_PTCH1_CH14PT_Pos)                    /* 0x0f000000 */
#define DMA_PTCH1_CH14PT               DMA_PTCH1_CH14PT_Msk                              /* DMA  channel 14 peripheral interface */


#define DMA_PTCH1_CH15PT_DPos          (28)
#define DMA_PTCH1_CH15PT_Pos           DMA_PTCH1_CH15PT_DPos
#define DMA_PTCH1_CH15PT_Msk           (0x0fUL<<DMA_PTCH1_CH15PT_Pos)                    /* 0xf0000000 */
#define DMA_PTCH1_CH15PT               DMA_PTCH1_CH15PT_Msk                              /* DMA  channel 15 peripheral interface */

/******************  Bits definition for DMA_CCR register  *****************/

#define DMA_CCR_DEN_DPos                 (0)
#define DMA_CCR_DEN_Pos                  DMA_CCR_DEN_DPos
#define DMA_CCR_DEN_Msk                  (0x01UL<<DMA_CCR_DEN_Pos)                             /* 0x00000001 */
#define DMA_CCR_DEN                      DMA_CCR_DEN_Msk                                       /* Dual-core lock step enabled */

#define DMA_CCR_DRDY_DPos                 (1)
#define DMA_CCR_DRDY_Pos                  DMA_CCR_DRDY_DPos
#define DMA_CCR_DRDY_Msk                  (0x01UL<<DMA_CCR_DRDY_Pos)                            /* 0x00000002 */
#define DMA_CCR_DRDY                      DMA_CCR_DRDY_Msk                                      /* Dual-core lock step ready status*/

#define DMA_CCR_DERR_DPos                 (2)
#define DMA_CCR_DERR_Pos                  DMA_CCR_DERR_DPos
#define DMA_CCR_DERR_Msk                  (0x01UL<<DMA_CCR_DERR_Pos)                            /* 0x00000004 */
#define DMA_CCR_DERR                      DMA_CCR_DERR_Msk                                      /* Dual-core lock step error status*/

#define DMA_CCR_WDEN_DPos                 (3)
#define DMA_CCR_WDEN_Pos                  DMA_CCR_WDEN_DPos
#define DMA_CCR_WDEN_Msk                  (0x01UL<<DMA_CCR_WDEN_Pos)                             /* 0x00000008 */
#define DMA_CCR_WDEN                      DMA_CCR_WDEN_Msk                                       /* Watch dog enable*/

#define DMA_CCR_WDCNT_DPos                (4)
#define DMA_CCR_WDCNT_Pos                 DMA_CCR_WDCNT_DPos
#define DMA_CCR_WDCNT_Msk                 (0xffffUL<<DMA_CCR_WDCNT_Pos)                           /* 0x00000 */
#define DMA_CCR_WDCNT                     DMA_CCR_WDCNT_Msk                                       /* Watchdog threshold*/


/******************  Bits definition for DMA_ERR_INT_RAW register  *****************/
#define DMA_ERR_INT_RAW_ERR_RAW0_DPos   (0)
#define DMA_ERR_INT_RAW_RAW0_Pos        DMA_ERR_INT_RAW_ERR_RAW0_DPos
#define DMA_ERR_INT_RAW_RAW0_Msk        (0x06UL<<DMA_ERR_INT_RAW_RAW0_Pos)                    /* 0x00000001 */
#define DMA_ERR_INT_RAW_RAW0            DMA_ERR_INT_RAW_RAW0_Msk                              /* DMA channel 0 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW1_DPos   (1)
#define DMA_ERR_INT_RAW_RAW1_Pos        DMA_ERR_INT_RAW_ERR_RAW1_DPos
#define DMA_ERR_INT_RAW_RAW1_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW1_Pos)                    /* 0x00000002 */
#define DMA_ERR_INT_RAW_RAW1            DMA_ERR_INT_RAW_RAW1_Msk                              /* DMA channel 1 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW2_DPos   (2)
#define DMA_ERR_INT_RAW_RAW2_Pos        DMA_ERR_INT_RAW_ERR_RAW2_DPos
#define DMA_ERR_INT_RAW_RAW2_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW2_Pos)                    /* 0x00000004 */
#define DMA_ERR_INT_RAW_RAW2            DMA_ERR_INT_RAW_RAW2_Msk                              /* DMA channel 2 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW3_DPos   (3)
#define DMA_ERR_INT_RAW_RAW3_Pos        DMA_ERR_INT_RAW_ERR_RAW3_DPos
#define DMA_ERR_INT_RAW_RAW3_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW3_Pos)                    /* 0x00000008 */
#define DMA_ERR_INT_RAW_RAW3            DMA_ERR_INT_RAW_RAW3_Msk                              /* DMA channel 3 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW4_DPos   (4)
#define DMA_ERR_INT_RAW_RAW4_Pos        DMA_ERR_INT_RAW_ERR_RAW4_DPos
#define DMA_ERR_INT_RAW_RAW4_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW4_Pos)                    /* 0x00000010 */
#define DMA_ERR_INT_RAW_RAW4            DMA_ERR_INT_RAW_RAW4_Msk                              /* DMA channel 4 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW5_DPos   (5)
#define DMA_ERR_INT_RAW_RAW5_Pos        DMA_ERR_INT_RAW_ERR_RAW5_DPos
#define DMA_ERR_INT_RAW_RAW5_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW5_Pos)                    /* 0x00000020 */
#define DMA_ERR_INT_RAW_RAW5            DMA_ERR_INT_RAW_RAW5_Msk                              /* DMA channel 5 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW6_DPos   (6)
#define DMA_ERR_INT_RAW_RAW6_Pos        DMA_ERR_INT_RAW_ERR_RAW6_DPos
#define DMA_ERR_INT_RAW_RAW6_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW6_Pos)                    /* 0x00000040 */
#define DMA_ERR_INT_RAW_RAW6            DMA_ERR_INT_RAW_RAW6_Msk                              /* DMA channel 6 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW7_DPos   (7)
#define DMA_ERR_INT_RAW_RAW7_Pos        DMA_ERR_INT_RAW_ERR_RAW7_DPos
#define DMA_ERR_INT_RAW_RAW7_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW7_Pos)                     /* 0x00000080 */
#define DMA_ERR_INT_RAW_RAW7            DMA_ERR_INT_RAW_RAW7_Msk                               /* DMA channel 7 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW8_DPos   (8)
#define DMA_ERR_INT_RAW_RAW8_Pos        DMA_ERR_INT_RAW_ERR_RAW8_DPos
#define DMA_ERR_INT_RAW_RAW8_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW8_Pos)                    /* 0x00000100 */
#define DMA_ERR_INT_RAW_RAW8            DMA_ERR_INT_RAW_RAW8_Msk                              /* DMA channel 8 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW9_DPos   (9)
#define DMA_ERR_INT_RAW_RAW9_Pos        DMA_ERR_INT_RAW_ERR_RAW9_DPos
#define DMA_ERR_INT_RAW_RAW9_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW9_Pos)                    /* 0x00000200 */
#define DMA_ERR_INT_RAW_RAW9            DMA_ERR_INT_RAW_RAW9_Msk                              /* DMA channel 9 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW10_DPos  (10)
#define DMA_ERR_INT_RAW_RAW10_Pos       DMA_ERR_INT_RAW_ERR_RAW10_DPos
#define DMA_ERR_INT_RAW_RAW10_Msk       (0x01UL<<DMA_ERR_INT_RAW_RAW10_Pos)                    /* 0x00000400 */
#define DMA_ERR_INT_RAW_RAW10           DMA_ERR_INT_RAW_RAW10_Msk                              /* DMA channel 10 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW11_DPos  (11)
#define DMA_ERR_INT_RAW_RAW11_Pos       DMA_ERR_INT_RAW_ERR_RAW11_DPos
#define DMA_ERR_INT_RAW_RAW11_Msk       (0x01UL<<DMA_ERR_INT_RAW_RAW11_Pos)                    /* 0x00000800 */
#define DMA_ERR_INT_RAW_RAW11           DMA_ERR_INT_RAW_RAW11_Msk                              /* DMA channel 11 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW12_DPos   (12)
#define DMA_ERR_INT_RAW_RAW12_Pos        DMA_ERR_INT_RAW_ERR_RAW12_DPos
#define DMA_ERR_INT_RAW_RAW12_Msk        (0x01UL<<DMA_ERR_INT_RAW_RAW12_Pos)                    /* 0x00001000 */
#define DMA_ERR_INT_RAW_RAW12            DMA_ERR_INT_RAW_RAW12_Msk                              /* DMA channel 12 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW13_DPos  (13)
#define DMA_ERR_INT_RAW_RAW13_Pos       DMA_ERR_INT_RAW_ERR_RAW13_DPos
#define DMA_ERR_INT_RAW_RAW13_Msk       (0x01UL<<DMA_ERR_INT_RAW_RAW13_Pos)                    /* 0x00002000 */
#define DMA_ERR_INT_RAW_RAW13           DMA_ERR_INT_RAW_RAW13_Msk                              /* DMA channel 13 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW14_DPos  (14)
#define DMA_ERR_INT_RAW_RAW14_Pos       DMA_ERR_INT_RAW_ERR_RAW14_DPos
#define DMA_ERR_INT_RAW_RAW14_Msk       (0x01UL<<DMA_ERR_INT_RAW_RAW14_Pos)                    /* 0x00004000 */
#define DMA_ERR_INT_RAW_RAW14           DMA_ERR_INT_RAW_RAW14_Msk                              /* DMA channel 14 error interrupt raw status */

#define DMA_ERR_INT_RAW_ERR_RAW15_DPos  (15)
#define DMA_ERR_INT_RAW_RAW15_Pos       DMA_ERR_INT_RAW_ERR_RAW15_DPos
#define DMA_ERR_INT_RAW_RAW15_Msk       (0x01UL<<DMA_ERR_INT_RAW_RAW15_Pos)                    /* 0x00008000 */
#define DMA_ERR_INT_RAW_RAW15           DMA_ERR_INT_RAW_RAW15_Msk                              /* DMA channel 15 error interrupt raw status */


/******************  Bits definition for DMA_ERR_INT_FORCE register  *****************/
#define DMA_ERR_INT_FORCE_FORCE0_DPos   (0)
#define DMA_ERR_INT_FORCE_FORCE0_Pos    DMA_ERR_INT_FORCE_FORCE0_DPos
#define DMA_ERR_INT_FORCE_FORCE0_Msk    (0x06UL<<DMA_ERR_INT_FORCE_FORCE0_Pos)                    /* 0x00000001 */
#define DMA_ERR_INT_FORCE_FORCE0         DMA_ERR_INT_FORCE_FORCE0_Msk                              /* DMA channel 0 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE1_DPos   (1)
#define DMA_ERR_INT_FORCE_FORCE1_Pos    DMA_ERR_INT_FORCE_FORCE1_DPos
#define DMA_ERR_INT_FORCE_FORCE1_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE1_Pos)                    /* 0x00000002 */
#define DMA_ERR_INT_FORCE_FORCE1        DMA_ERR_INT_FORCE_FORCE1_Msk                              /* DMA channel 1 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE2_DPos   (2)
#define DMA_ERR_INT_FORCE_FORCE2_Pos    DMA_ERR_INT_FORCE_FORCE2_DPos
#define DMA_ERR_INT_FORCE_FORCE2_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE2_Pos)                    /* 0x00000004 */
#define DMA_ERR_INT_FORCE_FORCE2        DMA_ERR_INT_FORCE_FORCE2_Msk                              /* DMA channel 2 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE6_DPos   (6)
#define DMA_ERR_INT_FORCE_FORCE6_Pos    DMA_ERR_INT_FORCE_FORCE6_DPos
#define DMA_ERR_INT_FORCE_FORCE6_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE6_Pos)                    /* 0x00000008 */
#define DMA_ERR_INT_FORCE_FORCE6        DMA_ERR_INT_FORCE_FORCE6_Msk                              /* DMA channel 6 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE4_DPos   (4)
#define DMA_ERR_INT_FORCE_FORCE4_Pos    DMA_ERR_INT_FORCE_FORCE4_DPos
#define DMA_ERR_INT_FORCE_FORCE4_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE4_Pos)                    /* 0x00000010 */
#define DMA_ERR_INT_FORCE_FORCE4        DMA_ERR_INT_FORCE_FORCE4_Msk                              /* DMA channel 4 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE5_DPos   (5)
#define DMA_ERR_INT_FORCE_FORCE5_Pos    DMA_ERR_INT_FORCE_FORCE5_DPos
#define DMA_ERR_INT_FORCE_FORCE5_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE5_Pos)                    /* 0x00000020 */
#define DMA_ERR_INT_FORCE_FORCE5        DMA_ERR_INT_FORCE_FORCE5_Msk                              /* DMA channel 5 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE6_DPos   (6)
#define DMA_ERR_INT_FORCE_FORCE6_Pos    DMA_ERR_INT_FORCE_FORCE6_DPos
#define DMA_ERR_INT_FORCE_FORCE6_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE6_Pos)                    /* 0x00000040 */
#define DMA_ERR_INT_FORCE_FORCE6        DMA_ERR_INT_FORCE_FORCE6_Msk                              /* DMA channel 6 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE7_DPos   (7)
#define DMA_ERR_INT_FORCE_FORCE7_Pos    DMA_ERR_INT_FORCE_FORCE7_DPos
#define DMA_ERR_INT_FORCE_FORCE7_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE7_Pos)                     /* 0x00000080 */
#define DMA_ERR_INT_FORCE_FORCE7        DMA_ERR_INT_FORCE_FORCE7_Msk                               /* DMA channel 7 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE8_DPos   (8)
#define DMA_ERR_INT_FORCE_FORCE8_Pos    DMA_ERR_INT_FORCE_FORCE8_DPos
#define DMA_ERR_INT_FORCE_FORCE8_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE8_Pos)                    /* 0x00000100 */
#define DMA_ERR_INT_FORCE_FORCE8        DMA_ERR_INT_FORCE_FORCE8_Msk                              /* DMA channel 8 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE9_DPos   (9)
#define DMA_ERR_INT_FORCE_FORCE9_Pos    DMA_ERR_INT_FORCE_FORCE9_DPos
#define DMA_ERR_INT_FORCE_FORCE9_Msk    (0x01UL<<DMA_ERR_INT_FORCE_FORCE9_Pos)                    /* 0x00000200 */
#define DMA_ERR_INT_FORCE_FORCE9        DMA_ERR_INT_FORCE_FORCE9_Msk                              /* DMA channel 9 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE10_DPos  (10)
#define DMA_ERR_INT_FORCE_FORCE10_Pos   DMA_ERR_INT_FORCE_FORCE10_DPos
#define DMA_ERR_INT_FORCE_FORCE10_Msk   (0x01UL<<DMA_ERR_INT_FORCE_FORCE10_Pos)                    /* 0x00000400 */
#define DMA_ERR_INT_FORCE_FORCE10       DMA_ERR_INT_FORCE_FORCE10_Msk                              /* DMA channel 10 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE11_DPos  (11)
#define DMA_ERR_INT_FORCE_FORCE11_Pos   DMA_ERR_INT_FORCE_FORCE11_DPos
#define DMA_ERR_INT_FORCE_FORCE11_Msk   (0x01UL<<DMA_ERR_INT_FORCE_FORCE11_Pos)                    /* 0x00000800 */
#define DMA_ERR_INT_FORCE_FORCE11       DMA_ERR_INT_FORCE_FORCE11_Msk                              /* DMA channel 11 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE12_DPos  (12)
#define DMA_ERR_INT_FORCE_FORCE12_Pos   DMA_ERR_INT_FORCE_FORCE12_DPos
#define DMA_ERR_INT_FORCE_FORCE12_Msk   (0x01UL<<DMA_ERR_INT_FORCE_FORCE12_Pos)                    /* 0x00001000 */
#define DMA_ERR_INT_FORCE_FORCE12       DMA_ERR_INT_FORCE_FORCE12_Msk                              /* DMA channel 12 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE13_DPos  (13)
#define DMA_ERR_INT_FORCE_FORCE13_Pos   DMA_ERR_INT_FORCE_FORCE13_DPos
#define DMA_ERR_INT_FORCE_FORCE13_Msk   (0x01UL<<DMA_ERR_INT_FORCE_FORCE13_Pos)                    /* 0x00002000 */
#define DMA_ERR_INT_FORCE_FORCE13       DMA_ERR_INT_FORCE_FORCE13_Msk                              /* DMA channel 13 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE14_DPos  (14)
#define DMA_ERR_INT_FORCE_FORCE14_Pos   DMA_ERR_INT_FORCE_FORCE14_DPos
#define DMA_ERR_INT_FORCE_FORCE14_Msk   (0x01UL<<DMA_ERR_INT_FORCE_FORCE14_Pos)                    /* 0x00004000 */
#define DMA_ERR_INT_FORCE_FORCE14       DMA_ERR_INT_FORCE_FORCE14_Msk                              /* DMA channel 14 error interrupt force */

#define DMA_ERR_INT_FORCE_FORCE15_DPos  (15)
#define DMA_ERR_INT_FORCE_FORCE15_Pos   DMA_ERR_INT_FORCE_FORCE15_DPos
#define DMA_ERR_INT_FORCE_FORCE15_Msk   (0x01UL<<DMA_ERR_INT_FORCE_FORCE15_Pos)                    /* 0x00008000 */
#define DMA_ERR_INT_FORCE_FORCE15       DMA_ERR_INT_FORCE_FORCE15_Msk                              /* DMA channel 15 error interrupt force */

/******************  Bits definition for DMA_ERR_INT_MASK register  *****************/
#define DMA_ERR_INT_MASK_MASK0_DPos   (0)
#define DMA_ERR_INT_MASK_MASK0_Pos    DMA_ERR_INT_MASK_MASK0_DPos
#define DMA_ERR_INT_MASK_MASK0_Msk    (0x06UL<<DMA_ERR_INT_MASK_MASK0_Pos)                    /* 0x00000001 */
#define DMA_ERR_INT_MASK_MASK0         DMA_ERR_INT_MASK_MASK0_Msk                              /* DMA channel 0 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK1_DPos   (1)
#define DMA_ERR_INT_MASK_MASK1_Pos    DMA_ERR_INT_MASK_MASK1_DPos
#define DMA_ERR_INT_MASK_MASK1_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK1_Pos)                    /* 0x00000002 */
#define DMA_ERR_INT_MASK_MASK1        DMA_ERR_INT_MASK_MASK1_Msk                              /* DMA channel 1 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK2_DPos   (2)
#define DMA_ERR_INT_MASK_MASK2_Pos    DMA_ERR_INT_MASK_MASK2_DPos
#define DMA_ERR_INT_MASK_MASK2_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK2_Pos)                    /* 0x00000004 */
#define DMA_ERR_INT_MASK_MASK2        DMA_ERR_INT_MASK_MASK2_Msk                              /* DMA channel 2 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK6_DPos   (6)
#define DMA_ERR_INT_MASK_MASK6_Pos    DMA_ERR_INT_MASK_MASK6_DPos
#define DMA_ERR_INT_MASK_MASK6_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK6_Pos)                    /* 0x00000008 */
#define DMA_ERR_INT_MASK_MASK6        DMA_ERR_INT_MASK_MASK6_Msk                              /* DMA channel 6 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK4_DPos   (4)
#define DMA_ERR_INT_MASK_MASK4_Pos    DMA_ERR_INT_MASK_MASK4_DPos
#define DMA_ERR_INT_MASK_MASK4_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK4_Pos)                    /* 0x00000010 */
#define DMA_ERR_INT_MASK_MASK4        DMA_ERR_INT_MASK_MASK4_Msk                              /* DMA channel 4 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK5_DPos   (5)
#define DMA_ERR_INT_MASK_MASK5_Pos    DMA_ERR_INT_MASK_MASK5_DPos
#define DMA_ERR_INT_MASK_MASK5_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK5_Pos)                    /* 0x00000020 */
#define DMA_ERR_INT_MASK_MASK5        DMA_ERR_INT_MASK_MASK5_Msk                              /* DMA channel 5 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK6_DPos   (6)
#define DMA_ERR_INT_MASK_MASK6_Pos    DMA_ERR_INT_MASK_MASK6_DPos
#define DMA_ERR_INT_MASK_MASK6_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK6_Pos)                    /* 0x00000040 */
#define DMA_ERR_INT_MASK_MASK6        DMA_ERR_INT_MASK_MASK6_Msk                              /* DMA channel 6 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK7_DPos   (7)
#define DMA_ERR_INT_MASK_MASK7_Pos    DMA_ERR_INT_MASK_MASK7_DPos
#define DMA_ERR_INT_MASK_MASK7_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK7_Pos)                     /* 0x00000080 */
#define DMA_ERR_INT_MASK_MASK7        DMA_ERR_INT_MASK_MASK7_Msk                               /* DMA channel 7 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK8_DPos   (8)
#define DMA_ERR_INT_MASK_MASK8_Pos    DMA_ERR_INT_MASK_MASK8_DPos
#define DMA_ERR_INT_MASK_MASK8_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK8_Pos)                    /* 0x00000100 */
#define DMA_ERR_INT_MASK_MASK8        DMA_ERR_INT_MASK_MASK8_Msk                              /* DMA channel 8 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK9_DPos   (9)
#define DMA_ERR_INT_MASK_MASK9_Pos    DMA_ERR_INT_MASK_MASK9_DPos
#define DMA_ERR_INT_MASK_MASK9_Msk    (0x01UL<<DMA_ERR_INT_MASK_MASK9_Pos)                    /* 0x00000200 */
#define DMA_ERR_INT_MASK_MASK9        DMA_ERR_INT_MASK_MASK9_Msk                              /* DMA channel 9 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK10_DPos  (10)
#define DMA_ERR_INT_MASK_MASK10_Pos   DMA_ERR_INT_MASK_MASK10_DPos
#define DMA_ERR_INT_MASK_MASK10_Msk   (0x01UL<<DMA_ERR_INT_MASK_MASK10_Pos)                    /* 0x00000400 */
#define DMA_ERR_INT_MASK_MASK10       DMA_ERR_INT_MASK_MASK10_Msk                              /* DMA channel 10 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK11_DPos  (11)
#define DMA_ERR_INT_MASK_MASK11_Pos   DMA_ERR_INT_MASK_MASK11_DPos
#define DMA_ERR_INT_MASK_MASK11_Msk   (0x01UL<<DMA_ERR_INT_MASK_MASK11_Pos)                    /* 0x00000800 */
#define DMA_ERR_INT_MASK_MASK11       DMA_ERR_INT_MASK_MASK11_Msk                              /* DMA channel 11 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK12_DPos  (12)
#define DMA_ERR_INT_MASK_MASK12_Pos   DMA_ERR_INT_MASK_MASK12_DPos
#define DMA_ERR_INT_MASK_MASK12_Msk   (0x01UL<<DMA_ERR_INT_MASK_MASK12_Pos)                    /* 0x00001000 */
#define DMA_ERR_INT_MASK_MASK12       DMA_ERR_INT_MASK_MASK12_Msk                              /* DMA channel 12 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK13_DPos  (13)
#define DMA_ERR_INT_MASK_MASK13_Pos   DMA_ERR_INT_MASK_MASK13_DPos
#define DMA_ERR_INT_MASK_MASK13_Msk   (0x01UL<<DMA_ERR_INT_MASK_MASK13_Pos)                    /* 0x00002000 */
#define DMA_ERR_INT_MASK_MASK13       DMA_ERR_INT_MASK_MASK13_Msk                              /* DMA channel 13 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK14_DPos  (14)
#define DMA_ERR_INT_MASK_MASK14_Pos   DMA_ERR_INT_MASK_MASK14_DPos
#define DMA_ERR_INT_MASK_MASK14_Msk   (0x01UL<<DMA_ERR_INT_MASK_MASK14_Pos)                    /* 0x00004000 */
#define DMA_ERR_INT_MASK_MASK14       DMA_ERR_INT_MASK_MASK14_Msk                              /* DMA channel 14 error interrupt mask */

#define DMA_ERR_INT_MASK_MASK15_DPos  (15)
#define DMA_ERR_INT_MASK_MASK15_Pos   DMA_ERR_INT_MASK_MASK15_DPos
#define DMA_ERR_INT_MASK_MASK15_Msk   (0x01UL<<DMA_ERR_INT_MASK_MASK15_Pos)                    /* 0x00008000 */
#define DMA_ERR_INT_MASK_MASK15       DMA_ERR_INT_MASK_MASK15_Msk                              /* DMA channel 15 error interrupt mask */

/******************  Bits definition for DMA_ERR_INT_STATUS register  *****************/
#define DMA_ERR_INT_STATUS_STATUS0_DPos   (0)
#define DMA_ERR_INT_STATUS_STAT0_Pos      DMA_ERR_INT_STATUS_STATUS0_DPos
#define DMA_ERR_INT_STATUS_STAT0_Msk      (0x06UL<<DMA_ERR_INT_STATUS_STAT0_Pos)                    /* 0x00000001 */
#define DMA_ERR_INT_STATUS_STAT0          DMA_ERR_INT_STATUS_STAT0_Msk                              /* DMA channel 0 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS1_DPos   (1)
#define DMA_ERR_INT_STATUS_STAT1_Pos      DMA_ERR_INT_STATUS_STATUS1_DPos
#define DMA_ERR_INT_STATUS_STAT1_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT1_Pos)                    /* 0x00000002 */
#define DMA_ERR_INT_STATUS_STAT1          DMA_ERR_INT_STATUS_STAT1_Msk                              /* DMA channel 1 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS2_DPos   (2)
#define DMA_ERR_INT_STATUS_STAT2_Pos      DMA_ERR_INT_STATUS_STATUS2_DPos
#define DMA_ERR_INT_STATUS_STAT2_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT2_Pos)                    /* 0x00000004 */
#define DMA_ERR_INT_STATUS_STAT2          DMA_ERR_INT_STATUS_STAT2_Msk                              /* DMA channel 2 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS6_DPos   (6)
#define DMA_ERR_INT_STATUS_STAT6_Pos      DMA_ERR_INT_STATUS_STATUS6_DPos
#define DMA_ERR_INT_STATUS_STAT6_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT6_Pos)                    /* 0x00000008 */
#define DMA_ERR_INT_STATUS_STAT6          DMA_ERR_INT_STATUS_STAT6_Msk                              /* DMA channel 6 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS4_DPos   (4)
#define DMA_ERR_INT_STATUS_STAT4_Pos      DMA_ERR_INT_STATUS_STATUS4_DPos
#define DMA_ERR_INT_STATUS_STAT4_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT4_Pos)                    /* 0x00000010 */
#define DMA_ERR_INT_STATUS_STAT4          DMA_ERR_INT_STATUS_STAT4_Msk                              /* DMA channel 4 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS5_DPos   (5)
#define DMA_ERR_INT_STATUS_STAT5_Pos      DMA_ERR_INT_STATUS_STATUS5_DPos
#define DMA_ERR_INT_STATUS_STAT5_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT5_Pos)                    /* 0x00000020 */
#define DMA_ERR_INT_STATUS_STAT5          DMA_ERR_INT_STATUS_STAT5_Msk                              /* DMA channel 5 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS6_DPos   (6)
#define DMA_ERR_INT_STATUS_STAT6_Pos      DMA_ERR_INT_STATUS_STATUS6_DPos
#define DMA_ERR_INT_STATUS_STAT6_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT6_Pos)                    /* 0x00000040 */
#define DMA_ERR_INT_STATUS_STAT6          DMA_ERR_INT_STATUS_STAT6_Msk                              /* DMA channel 6 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS7_DPos   (7)
#define DMA_ERR_INT_STATUS_STAT7_Pos      DMA_ERR_INT_STATUS_STATUS7_DPos
#define DMA_ERR_INT_STATUS_STAT7_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT7_Pos)                     /* 0x00000080 */
#define DMA_ERR_INT_STATUS_STAT7          DMA_ERR_INT_STATUS_STAT7_Msk                               /* DMA channel 7 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS8_DPos   (8)
#define DMA_ERR_INT_STATUS_STAT8_Pos      DMA_ERR_INT_STATUS_STATUS8_DPos
#define DMA_ERR_INT_STATUS_STAT8_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT8_Pos)                    /* 0x00000100 */
#define DMA_ERR_INT_STATUS_STAT8          DMA_ERR_INT_STATUS_STAT8_Msk                              /* DMA channel 8 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS9_DPos   (9)
#define DMA_ERR_INT_STATUS_STAT9_Pos      DMA_ERR_INT_STATUS_STATUS9_DPos
#define DMA_ERR_INT_STATUS_STAT9_Msk      (0x01UL<<DMA_ERR_INT_STATUS_STAT9_Pos)                    /* 0x00000200 */
#define DMA_ERR_INT_STATUS_STAT9          DMA_ERR_INT_STATUS_STAT9_Msk                              /* DMA channel 9 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS10_DPos  (10)
#define DMA_ERR_INT_STATUS_STAT10_Pos     DMA_ERR_INT_STATUS_STATUS10_DPos
#define DMA_ERR_INT_STATUS_STAT10_Msk     (0x01UL<<DMA_ERR_INT_STATUS_STAT10_Pos)                    /* 0x00000400 */
#define DMA_ERR_INT_STATUS_STAT10         DMA_ERR_INT_STATUS_STAT10_Msk                              /* DMA channel 10 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS11_DPos  (11)
#define DMA_ERR_INT_STATUS_STAT11_Pos     DMA_ERR_INT_STATUS_STATUS11_DPos
#define DMA_ERR_INT_STATUS_STAT11_Msk     (0x01UL<<DMA_ERR_INT_STATUS_STAT11_Pos)                    /* 0x00000800 */
#define DMA_ERR_INT_STATUS_STAT11         DMA_ERR_INT_STATUS_STAT11_Msk                              /* DMA channel 11 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS12_DPos  (12)
#define DMA_ERR_INT_STATUS_STAT12_Pos     DMA_ERR_INT_STATUS_STATUS12_DPos
#define DMA_ERR_INT_STATUS_STAT12_Msk     (0x01UL<<DMA_ERR_INT_STATUS_STAT12_Pos)                    /* 0x00001000 */
#define DMA_ERR_INT_STATUS_STAT12         DMA_ERR_INT_STATUS_STAT12_Msk                              /* DMA channel 12 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS13_DPos  (13)
#define DMA_ERR_INT_STATUS_STAT13_Pos     DMA_ERR_INT_STATUS_STATUS13_DPos
#define DMA_ERR_INT_STATUS_STAT13_Msk     (0x01UL<<DMA_ERR_INT_STATUS_STAT13_Pos)                    /* 0x00002000 */
#define DMA_ERR_INT_STATUS_STAT13         DMA_ERR_INT_STATUS_STAT13_Msk                              /* DMA channel 13 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS14_DPos  (14)
#define DMA_ERR_INT_STATUS_STAT14_Pos     DMA_ERR_INT_STATUS_STATUS14_DPos
#define DMA_ERR_INT_STATUS_STAT14_Msk     (0x01UL<<DMA_ERR_INT_STATUS_STAT14_Pos)                    /* 0x00004000 */
#define DMA_ERR_INT_STATUS_STAT14         DMA_ERR_INT_STATUS_STAT14_Msk                              /* DMA channel 14 error interrupt status */

#define DMA_ERR_INT_STATUS_STATUS15_DPos  (15)
#define DMA_ERR_INT_STATUS_STAT15_Pos     DMA_ERR_INT_STATUS_STATUS15_DPos
#define DMA_ERR_INT_STATUS_STAT15_Msk     (0x01UL<<DMA_ERR_INT_STATUS_STAT15_Pos)                    /* 0x00008000 */
#define DMA_ERR_INT_STATUS_STAT15         DMA_ERR_INT_STATUS_STAT15_Msk                              /* DMA channel 15 error interrupt status */



/******************  Bits definition for DMA_FTF_INT_RAW register  *****************/
#define DMA_FTF_INT_RAW_FTF_RAW0_DPos   (0)
#define DMA_FTF_INT_RAW_RAW0_Pos        DMA_FTF_INT_RAW_FTF_RAW0_DPos
#define DMA_FTF_INT_RAW_RAW0_Msk        (0x06UL<<DMA_FTF_INT_RAW_RAW0_Pos)                    /* 0x00000001 */
#define DMA_FTF_INT_RAW_RAW0            DMA_FTF_INT_RAW_RAW0_Msk                              /* DMA channel 0 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW1_DPos   (1)
#define DMA_FTF_INT_RAW_RAW1_Pos        DMA_FTF_INT_RAW_FTF_RAW1_DPos
#define DMA_FTF_INT_RAW_RAW1_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW1_Pos)                    /* 0x00000002 */
#define DMA_FTF_INT_RAW_RAW1            DMA_FTF_INT_RAW_RAW1_Msk                              /* DMA channel 1 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW2_DPos   (2)
#define DMA_FTF_INT_RAW_RAW2_Pos        DMA_FTF_INT_RAW_FTF_RAW2_DPos
#define DMA_FTF_INT_RAW_RAW2_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW2_Pos)                    /* 0x00000004 */
#define DMA_FTF_INT_RAW_RAW2            DMA_FTF_INT_RAW_RAW2_Msk                              /* DMA channel 2 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW3_DPos   (3)
#define DMA_FTF_INT_RAW_RAW3_Pos        DMA_FTF_INT_RAW_FTF_RAW3_DPos
#define DMA_FTF_INT_RAW_RAW3_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW3_Pos)                    /* 0x00000008 */
#define DMA_FTF_INT_RAW_RAW3            DMA_FTF_INT_RAW_RAW3_Msk                              /* DMA channel 6 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW4_DPos   (4)
#define DMA_FTF_INT_RAW_RAW4_Pos        DMA_FTF_INT_RAW_FTF_RAW4_DPos
#define DMA_FTF_INT_RAW_RAW4_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW4_Pos)                    /* 0x00000010 */
#define DMA_FTF_INT_RAW_RAW4            DMA_FTF_INT_RAW_RAW4_Msk                              /* DMA channel 4 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW5_DPos   (5)
#define DMA_FTF_INT_RAW_RAW5_Pos        DMA_FTF_INT_RAW_FTF_RAW5_DPos
#define DMA_FTF_INT_RAW_RAW5_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW5_Pos)                    /* 0x00000020 */
#define DMA_FTF_INT_RAW_RAW5            DMA_FTF_INT_RAW_RAW5_Msk                              /* DMA channel 5 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW6_DPos   (6)
#define DMA_FTF_INT_RAW_RAW6_Pos        DMA_FTF_INT_RAW_FTF_RAW6_DPos
#define DMA_FTF_INT_RAW_RAW6_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW6_Pos)                    /* 0x00000040 */
#define DMA_FTF_INT_RAW_RAW6            DMA_FTF_INT_RAW_RAW6_Msk                              /* DMA channel 6 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW7_DPos   (7)
#define DMA_FTF_INT_RAW_RAW7_Pos        DMA_FTF_INT_RAW_FTF_RAW7_DPos
#define DMA_FTF_INT_RAW_RAW7_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW7_Pos)                     /* 0x00000080 */
#define DMA_FTF_INT_RAW_RAW7            DMA_FTF_INT_RAW_RAW7_Msk                               /* DMA channel 7 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW8_DPos   (8)
#define DMA_FTF_INT_RAW_RAW8_Pos        DMA_FTF_INT_RAW_FTF_RAW8_DPos
#define DMA_FTF_INT_RAW_RAW8_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW8_Pos)                    /* 0x00000100 */
#define DMA_FTF_INT_RAW_RAW8            DMA_FTF_INT_RAW_RAW8_Msk                              /* DMA channel 8 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW9_DPos   (9)
#define DMA_FTF_INT_RAW_RAW9_Pos        DMA_FTF_INT_RAW_FTF_RAW9_DPos
#define DMA_FTF_INT_RAW_RAW9_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW9_Pos)                    /* 0x00000200 */
#define DMA_FTF_INT_RAW_RAW9            DMA_FTF_INT_RAW_RAW9_Msk                              /* DMA channel 9 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW10_DPos  (10)
#define DMA_FTF_INT_RAW_RAW10_Pos       DMA_FTF_INT_RAW_FTF_RAW10_DPos
#define DMA_FTF_INT_RAW_RAW10_Msk       (0x01UL<<DMA_FTF_INT_RAW_RAW10_Pos)                    /* 0x00000400 */
#define DMA_FTF_INT_RAW_RAW10           DMA_FTF_INT_RAW_RAW10_Msk                              /* DMA channel 10 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW11_DPos  (11)
#define DMA_FTF_INT_RAW_RAW11_Pos       DMA_FTF_INT_RAW_FTF_RAW11_DPos
#define DMA_FTF_INT_RAW_RAW11_Msk       (0x01UL<<DMA_FTF_INT_RAW_RAW11_Pos)                    /* 0x00000800 */
#define DMA_FTF_INT_RAW_RAW11           DMA_FTF_INT_RAW_RAW11_Msk                              /* DMA channel 11 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW12_DPos   (12)
#define DMA_FTF_INT_RAW_RAW12_Pos        DMA_FTF_INT_RAW_FTF_RAW12_DPos
#define DMA_FTF_INT_RAW_RAW12_Msk        (0x01UL<<DMA_FTF_INT_RAW_RAW12_Pos)                    /* 0x00001000 */
#define DMA_FTF_INT_RAW_RAW12            DMA_FTF_INT_RAW_RAW12_Msk                              /* DMA channel 12 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW13_DPos  (13)
#define DMA_FTF_INT_RAW_RAW13_Pos       DMA_FTF_INT_RAW_FTF_RAW13_DPos
#define DMA_FTF_INT_RAW_RAW13_Msk       (0x01UL<<DMA_FTF_INT_RAW_RAW13_Pos)                    /* 0x00002000 */
#define DMA_FTF_INT_RAW_RAW13           DMA_FTF_INT_RAW_RAW13_Msk                              /* DMA channel 13 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW14_DPos  (14)
#define DMA_FTF_INT_RAW_RAW14_Pos       DMA_FTF_INT_RAW_FTF_RAW14_DPos
#define DMA_FTF_INT_RAW_RAW14_Msk       (0x01UL<<DMA_FTF_INT_RAW_RAW14_Pos)                    /* 0x00004000 */
#define DMA_FTF_INT_RAW_RAW14           DMA_FTF_INT_RAW_RAW14_Msk                              /* DMA channel 14 tranfer commplete interrupt raw status */

#define DMA_FTF_INT_RAW_FTF_RAW15_DPos  (15)
#define DMA_FTF_INT_RAW_RAW15_Pos       DMA_FTF_INT_RAW_FTF_RAW15_DPos
#define DMA_FTF_INT_RAW_RAW15_Msk       (0x01UL<<DMA_FTF_INT_RAW_RAW15_Pos)                    /* 0x00008000 */
#define DMA_FTF_INT_RAW_RAW15           DMA_FTF_INT_RAW_RAW15_Msk                              /* DMA channel 15 tranfer commplete interrupt raw status */


/******************  Bits definition for DMA_FTF_INT_FORCE register  *****************/
#define DMA_FTF_INT_FORCE_FORCE0_DPos   (0)
#define DMA_FTF_INT_FORCE_FORCE0_Pos    DMA_FTF_INT_FORCE_FORCE0_DPos
#define DMA_FTF_INT_FORCE_FORCE0_Msk    (0x06UL<<DMA_FTF_INT_FORCE_FORCE0_Pos)                    /* 0x00000001 */
#define DMA_FTF_INT_FORCE_FORCE0         DMA_FTF_INT_FORCE_FORCE0_Msk                              /* DMA channel 0 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE1_DPos   (1)
#define DMA_FTF_INT_FORCE_FORCE1_Pos    DMA_FTF_INT_FORCE_FORCE1_DPos
#define DMA_FTF_INT_FORCE_FORCE1_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE1_Pos)                    /* 0x00000002 */
#define DMA_FTF_INT_FORCE_FORCE1        DMA_FTF_INT_FORCE_FORCE1_Msk                              /* DMA channel 1 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE2_DPos   (2)
#define DMA_FTF_INT_FORCE_FORCE2_Pos    DMA_FTF_INT_FORCE_FORCE2_DPos
#define DMA_FTF_INT_FORCE_FORCE2_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE2_Pos)                    /* 0x00000004 */
#define DMA_FTF_INT_FORCE_FORCE2        DMA_FTF_INT_FORCE_FORCE2_Msk                              /* DMA channel 2 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE6_DPos   (6)
#define DMA_FTF_INT_FORCE_FORCE6_Pos    DMA_FTF_INT_FORCE_FORCE6_DPos
#define DMA_FTF_INT_FORCE_FORCE6_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE6_Pos)                    /* 0x00000008 */
#define DMA_FTF_INT_FORCE_FORCE6        DMA_FTF_INT_FORCE_FORCE6_Msk                              /* DMA channel 6 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE4_DPos   (4)
#define DMA_FTF_INT_FORCE_FORCE4_Pos    DMA_FTF_INT_FORCE_FORCE4_DPos
#define DMA_FTF_INT_FORCE_FORCE4_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE4_Pos)                    /* 0x00000010 */
#define DMA_FTF_INT_FORCE_FORCE4        DMA_FTF_INT_FORCE_FORCE4_Msk                              /* DMA channel 4 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE5_DPos   (5)
#define DMA_FTF_INT_FORCE_FORCE5_Pos    DMA_FTF_INT_FORCE_FORCE5_DPos
#define DMA_FTF_INT_FORCE_FORCE5_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE5_Pos)                    /* 0x00000020 */
#define DMA_FTF_INT_FORCE_FORCE5        DMA_FTF_INT_FORCE_FORCE5_Msk                              /* DMA channel 5 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE6_DPos   (6)
#define DMA_FTF_INT_FORCE_FORCE6_Pos    DMA_FTF_INT_FORCE_FORCE6_DPos
#define DMA_FTF_INT_FORCE_FORCE6_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE6_Pos)                    /* 0x00000040 */
#define DMA_FTF_INT_FORCE_FORCE6        DMA_FTF_INT_FORCE_FORCE6_Msk                              /* DMA channel 6 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE7_DPos   (7)
#define DMA_FTF_INT_FORCE_FORCE7_Pos    DMA_FTF_INT_FORCE_FORCE7_DPos
#define DMA_FTF_INT_FORCE_FORCE7_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE7_Pos)                     /* 0x00000080 */
#define DMA_FTF_INT_FORCE_FORCE7        DMA_FTF_INT_FORCE_FORCE7_Msk                               /* DMA channel 7 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE8_DPos   (8)
#define DMA_FTF_INT_FORCE_FORCE8_Pos    DMA_FTF_INT_FORCE_FORCE8_DPos
#define DMA_FTF_INT_FORCE_FORCE8_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE8_Pos)                    /* 0x00000100 */
#define DMA_FTF_INT_FORCE_FORCE8        DMA_FTF_INT_FORCE_FORCE8_Msk                              /* DMA channel 8 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE9_DPos   (9)
#define DMA_FTF_INT_FORCE_FORCE9_Pos    DMA_FTF_INT_FORCE_FORCE9_DPos
#define DMA_FTF_INT_FORCE_FORCE9_Msk    (0x01UL<<DMA_FTF_INT_FORCE_FORCE9_Pos)                    /* 0x00000200 */
#define DMA_FTF_INT_FORCE_FORCE9        DMA_FTF_INT_FORCE_FORCE9_Msk                              /* DMA channel 9 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE10_DPos  (10)
#define DMA_FTF_INT_FORCE_FORCE10_Pos   DMA_FTF_INT_FORCE_FORCE10_DPos
#define DMA_FTF_INT_FORCE_FORCE10_Msk   (0x01UL<<DMA_FTF_INT_FORCE_FORCE10_Pos)                    /* 0x00000400 */
#define DMA_FTF_INT_FORCE_FORCE10       DMA_FTF_INT_FORCE_FORCE10_Msk                              /* DMA channel 10 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE11_DPos  (11)
#define DMA_FTF_INT_FORCE_FORCE11_Pos   DMA_FTF_INT_FORCE_FORCE11_DPos
#define DMA_FTF_INT_FORCE_FORCE11_Msk   (0x01UL<<DMA_FTF_INT_FORCE_FORCE11_Pos)                    /* 0x00000800 */
#define DMA_FTF_INT_FORCE_FORCE11       DMA_FTF_INT_FORCE_FORCE11_Msk                              /* DMA channel 11 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE12_DPos  (12)
#define DMA_FTF_INT_FORCE_FORCE12_Pos   DMA_FTF_INT_FORCE_FORCE12_DPos
#define DMA_FTF_INT_FORCE_FORCE12_Msk   (0x01UL<<DMA_FTF_INT_FORCE_FORCE12_Pos)                    /* 0x00001000 */
#define DMA_FTF_INT_FORCE_FORCE12       DMA_FTF_INT_FORCE_FORCE12_Msk                              /* DMA channel 12 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE13_DPos  (13)
#define DMA_FTF_INT_FORCE_FORCE13_Pos   DMA_FTF_INT_FORCE_FORCE13_DPos
#define DMA_FTF_INT_FORCE_FORCE13_Msk   (0x01UL<<DMA_FTF_INT_FORCE_FORCE13_Pos)                    /* 0x00002000 */
#define DMA_FTF_INT_FORCE_FORCE13       DMA_FTF_INT_FORCE_FORCE13_Msk                              /* DMA channel 13 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE14_DPos  (14)
#define DMA_FTF_INT_FORCE_FORCE14_Pos   DMA_FTF_INT_FORCE_FORCE14_DPos
#define DMA_FTF_INT_FORCE_FORCE14_Msk   (0x01UL<<DMA_FTF_INT_FORCE_FORCE14_Pos)                    /* 0x00004000 */
#define DMA_FTF_INT_FORCE_FORCE14       DMA_FTF_INT_FORCE_FORCE14_Msk                              /* DMA channel 14 tranfer commplete interrupt force */

#define DMA_FTF_INT_FORCE_FORCE15_DPos  (15)
#define DMA_FTF_INT_FORCE_FORCE15_Pos   DMA_FTF_INT_FORCE_FORCE15_DPos
#define DMA_FTF_INT_FORCE_FORCE15_Msk   (0x01UL<<DMA_FTF_INT_FORCE_FORCE15_Pos)                    /* 0x00008000 */
#define DMA_FTF_INT_FORCE_FORCE15       DMA_FTF_INT_FORCE_FORCE15_Msk                              /* DMA channel 15 tranfer commplete interrupt force */

/******************  Bits definition for DMA_FTF_INT_MASK register  *****************/
#define DMA_FTF_INT_MASK_MASK0_DPos   (0)
#define DMA_FTF_INT_MASK_MASK0_Pos    DMA_FTF_INT_MASK_MASK0_DPos
#define DMA_FTF_INT_MASK_MASK0_Msk    (0x06UL<<DMA_FTF_INT_MASK_MASK0_Pos)                    /* 0x00000001 */
#define DMA_FTF_INT_MASK_MASK0         DMA_FTF_INT_MASK_MASK0_Msk                              /* DMA channel 0 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK1_DPos   (1)
#define DMA_FTF_INT_MASK_MASK1_Pos    DMA_FTF_INT_MASK_MASK1_DPos
#define DMA_FTF_INT_MASK_MASK1_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK1_Pos)                    /* 0x00000002 */
#define DMA_FTF_INT_MASK_MASK1        DMA_FTF_INT_MASK_MASK1_Msk                              /* DMA channel 1 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK2_DPos   (2)
#define DMA_FTF_INT_MASK_MASK2_Pos    DMA_FTF_INT_MASK_MASK2_DPos
#define DMA_FTF_INT_MASK_MASK2_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK2_Pos)                    /* 0x00000004 */
#define DMA_FTF_INT_MASK_MASK2        DMA_FTF_INT_MASK_MASK2_Msk                              /* DMA channel 2 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK3_DPos   (3)
#define DMA_FTF_INT_MASK_MASK3_Pos    DMA_FTF_INT_MASK_MASK3_DPos
#define DMA_FTF_INT_MASK_MASK3_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK3_Pos)                    /* 0x00000008 */
#define DMA_FTF_INT_MASK_MASK3        DMA_FTF_INT_MASK_MASK3_Msk                              /* DMA channel 3 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK4_DPos   (4)
#define DMA_FTF_INT_MASK_MASK4_Pos    DMA_FTF_INT_MASK_MASK4_DPos
#define DMA_FTF_INT_MASK_MASK4_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK4_Pos)                    /* 0x00000010 */
#define DMA_FTF_INT_MASK_MASK4        DMA_FTF_INT_MASK_MASK4_Msk                              /* DMA channel 4 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK5_DPos   (5)
#define DMA_FTF_INT_MASK_MASK5_Pos    DMA_FTF_INT_MASK_MASK5_DPos
#define DMA_FTF_INT_MASK_MASK5_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK5_Pos)                    /* 0x00000020 */
#define DMA_FTF_INT_MASK_MASK5        DMA_FTF_INT_MASK_MASK5_Msk                              /* DMA channel 5 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK6_DPos   (6)
#define DMA_FTF_INT_MASK_MASK6_Pos    DMA_FTF_INT_MASK_MASK6_DPos
#define DMA_FTF_INT_MASK_MASK6_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK6_Pos)                    /* 0x00000040 */
#define DMA_FTF_INT_MASK_MASK6        DMA_FTF_INT_MASK_MASK6_Msk                              /* DMA channel 6 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK7_DPos   (7)
#define DMA_FTF_INT_MASK_MASK7_Pos    DMA_FTF_INT_MASK_MASK7_DPos
#define DMA_FTF_INT_MASK_MASK7_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK7_Pos)                     /* 0x00000080 */
#define DMA_FTF_INT_MASK_MASK7        DMA_FTF_INT_MASK_MASK7_Msk                               /* DMA channel 7 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK8_DPos   (8)
#define DMA_FTF_INT_MASK_MASK8_Pos    DMA_FTF_INT_MASK_MASK8_DPos
#define DMA_FTF_INT_MASK_MASK8_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK8_Pos)                    /* 0x00000100 */
#define DMA_FTF_INT_MASK_MASK8        DMA_FTF_INT_MASK_MASK8_Msk                              /* DMA channel 8 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK9_DPos   (9)
#define DMA_FTF_INT_MASK_MASK9_Pos    DMA_FTF_INT_MASK_MASK9_DPos
#define DMA_FTF_INT_MASK_MASK9_Msk    (0x01UL<<DMA_FTF_INT_MASK_MASK9_Pos)                    /* 0x00000200 */
#define DMA_FTF_INT_MASK_MASK9        DMA_FTF_INT_MASK_MASK9_Msk                              /* DMA channel 9 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK10_DPos  (10)
#define DMA_FTF_INT_MASK_MASK10_Pos   DMA_FTF_INT_MASK_MASK10_DPos
#define DMA_FTF_INT_MASK_MASK10_Msk   (0x01UL<<DMA_FTF_INT_MASK_MASK10_Pos)                    /* 0x00000400 */
#define DMA_FTF_INT_MASK_MASK10       DMA_FTF_INT_MASK_MASK10_Msk                              /* DMA channel 10 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK11_DPos  (11)
#define DMA_FTF_INT_MASK_MASK11_Pos   DMA_FTF_INT_MASK_MASK11_DPos
#define DMA_FTF_INT_MASK_MASK11_Msk   (0x01UL<<DMA_FTF_INT_MASK_MASK11_Pos)                    /* 0x00000800 */
#define DMA_FTF_INT_MASK_MASK11       DMA_FTF_INT_MASK_MASK11_Msk                              /* DMA channel 11 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK12_DPos  (12)
#define DMA_FTF_INT_MASK_MASK12_Pos   DMA_FTF_INT_MASK_MASK12_DPos
#define DMA_FTF_INT_MASK_MASK12_Msk   (0x01UL<<DMA_FTF_INT_MASK_MASK12_Pos)                    /* 0x00001000 */
#define DMA_FTF_INT_MASK_MASK12       DMA_FTF_INT_MASK_MASK12_Msk                              /* DMA channel 12 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK13_DPos  (13)
#define DMA_FTF_INT_MASK_MASK13_Pos   DMA_FTF_INT_MASK_MASK13_DPos
#define DMA_FTF_INT_MASK_MASK13_Msk   (0x01UL<<DMA_FTF_INT_MASK_MASK13_Pos)                    /* 0x00002000 */
#define DMA_FTF_INT_MASK_MASK13       DMA_FTF_INT_MASK_MASK13_Msk                              /* DMA channel 13 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK14_DPos  (14)
#define DMA_FTF_INT_MASK_MASK14_Pos   DMA_FTF_INT_MASK_MASK14_DPos
#define DMA_FTF_INT_MASK_MASK14_Msk   (0x01UL<<DMA_FTF_INT_MASK_MASK14_Pos)                    /* 0x00004000 */
#define DMA_FTF_INT_MASK_MASK14       DMA_FTF_INT_MASK_MASK14_Msk                              /* DMA channel 14 tranfer commplete interrupt mask */

#define DMA_FTF_INT_MASK_MASK15_DPos  (15)
#define DMA_FTF_INT_MASK_MASK15_Pos   DMA_FTF_INT_MASK_MASK15_DPos
#define DMA_FTF_INT_MASK_MASK15_Msk   (0x01UL<<DMA_FTF_INT_MASK_MASK15_Pos)                    /* 0x00008000 */
#define DMA_FTF_INT_MASK_MASK15       DMA_FTF_INT_MASK_MASK15_Msk                              /* DMA channel 15 tranfer commplete interrupt mask */

/******************  Bits definition for DMA_FTF_INT_STATUS register  *****************/
#define DMA_FTF_INT_STATUS_STATUS0_DPos   (0)
#define DMA_FTF_INT_STATUS_STAT0_Pos      DMA_FTF_INT_STATUS_STATUS0_DPos
#define DMA_FTF_INT_STATUS_STAT0_Msk      (0x06UL<<DMA_FTF_INT_STATUS_STAT0_Pos)                    /* 0x00000001 */
#define DMA_FTF_INT_STATUS_STAT0          DMA_FTF_INT_STATUS_STAT0_Msk                              /* DMA channel 0 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS1_DPos   (1)
#define DMA_FTF_INT_STATUS_STAT1_Pos      DMA_FTF_INT_STATUS_STATUS1_DPos
#define DMA_FTF_INT_STATUS_STAT1_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT1_Pos)                    /* 0x00000002 */
#define DMA_FTF_INT_STATUS_STAT1          DMA_FTF_INT_STATUS_STAT1_Msk                              /* DMA channel 1 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS2_DPos   (2)
#define DMA_FTF_INT_STATUS_STAT2_Pos      DMA_FTF_INT_STATUS_STATUS2_DPos
#define DMA_FTF_INT_STATUS_STAT2_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT2_Pos)                    /* 0x00000004 */
#define DMA_FTF_INT_STATUS_STAT2          DMA_FTF_INT_STATUS_STAT2_Msk                              /* DMA channel 2 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS6_DPos   (6)
#define DMA_FTF_INT_STATUS_STAT6_Pos      DMA_FTF_INT_STATUS_STATUS6_DPos
#define DMA_FTF_INT_STATUS_STAT6_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT6_Pos)                    /* 0x00000008 */
#define DMA_FTF_INT_STATUS_STAT6          DMA_FTF_INT_STATUS_STAT6_Msk                              /* DMA channel 6 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS4_DPos   (4)
#define DMA_FTF_INT_STATUS_STAT4_Pos      DMA_FTF_INT_STATUS_STATUS4_DPos
#define DMA_FTF_INT_STATUS_STAT4_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT4_Pos)                    /* 0x00000010 */
#define DMA_FTF_INT_STATUS_STAT4          DMA_FTF_INT_STATUS_STAT4_Msk                              /* DMA channel 4 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS5_DPos   (5)
#define DMA_FTF_INT_STATUS_STAT5_Pos      DMA_FTF_INT_STATUS_STATUS5_DPos
#define DMA_FTF_INT_STATUS_STAT5_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT5_Pos)                    /* 0x00000020 */
#define DMA_FTF_INT_STATUS_STAT5          DMA_FTF_INT_STATUS_STAT5_Msk                              /* DMA channel 5 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS6_DPos   (6)
#define DMA_FTF_INT_STATUS_STAT6_Pos      DMA_FTF_INT_STATUS_STATUS6_DPos
#define DMA_FTF_INT_STATUS_STAT6_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT6_Pos)                    /* 0x00000040 */
#define DMA_FTF_INT_STATUS_STAT6          DMA_FTF_INT_STATUS_STAT6_Msk                              /* DMA channel 6 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS7_DPos   (7)
#define DMA_FTF_INT_STATUS_STAT7_Pos      DMA_FTF_INT_STATUS_STATUS7_DPos
#define DMA_FTF_INT_STATUS_STAT7_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT7_Pos)                     /* 0x00000080 */
#define DMA_FTF_INT_STATUS_STAT7          DMA_FTF_INT_STATUS_STAT7_Msk                               /* DMA channel 7 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS8_DPos   (8)
#define DMA_FTF_INT_STATUS_STAT8_Pos      DMA_FTF_INT_STATUS_STATUS8_DPos
#define DMA_FTF_INT_STATUS_STAT8_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT8_Pos)                    /* 0x00000100 */
#define DMA_FTF_INT_STATUS_STAT8          DMA_FTF_INT_STATUS_STAT8_Msk                              /* DMA channel 8 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS9_DPos   (9)
#define DMA_FTF_INT_STATUS_STAT9_Pos      DMA_FTF_INT_STATUS_STATUS9_DPos
#define DMA_FTF_INT_STATUS_STAT9_Msk      (0x01UL<<DMA_FTF_INT_STATUS_STAT9_Pos)                    /* 0x00000200 */
#define DMA_FTF_INT_STATUS_STAT9          DMA_FTF_INT_STATUS_STAT9_Msk                              /* DMA channel 9 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS10_DPos  (10)
#define DMA_FTF_INT_STATUS_STAT10_Pos     DMA_FTF_INT_STATUS_STATUS10_DPos
#define DMA_FTF_INT_STATUS_STAT10_Msk     (0x01UL<<DMA_FTF_INT_STATUS_STAT10_Pos)                    /* 0x00000400 */
#define DMA_FTF_INT_STATUS_STAT10         DMA_FTF_INT_STATUS_STAT10_Msk                              /* DMA channel 10 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS11_DPos  (11)
#define DMA_FTF_INT_STATUS_STAT11_Pos     DMA_FTF_INT_STATUS_STATUS11_DPos
#define DMA_FTF_INT_STATUS_STAT11_Msk     (0x01UL<<DMA_FTF_INT_STATUS_STAT11_Pos)                    /* 0x00000800 */
#define DMA_FTF_INT_STATUS_STAT11         DMA_FTF_INT_STATUS_STAT11_Msk                              /* DMA channel 11 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS12_DPos  (12)
#define DMA_FTF_INT_STATUS_STAT12_Pos     DMA_FTF_INT_STATUS_STATUS12_DPos
#define DMA_FTF_INT_STATUS_STAT12_Msk     (0x01UL<<DMA_FTF_INT_STATUS_STAT12_Pos)                    /* 0x00001000 */
#define DMA_FTF_INT_STATUS_STAT12         DMA_FTF_INT_STATUS_STAT12_Msk                              /* DMA channel 12 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS13_DPos  (13)
#define DMA_FTF_INT_STATUS_STAT13_Pos     DMA_FTF_INT_STATUS_STATUS13_DPos
#define DMA_FTF_INT_STATUS_STAT13_Msk     (0x01UL<<DMA_FTF_INT_STATUS_STAT13_Pos)                    /* 0x00002000 */
#define DMA_FTF_INT_STATUS_STAT13         DMA_FTF_INT_STATUS_STAT13_Msk                              /* DMA channel 13 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS14_DPos  (14)
#define DMA_FTF_INT_STATUS_STAT14_Pos     DMA_FTF_INT_STATUS_STATUS14_DPos
#define DMA_FTF_INT_STATUS_STAT14_Msk     (0x01UL<<DMA_FTF_INT_STATUS_STAT14_Pos)                    /* 0x00004000 */
#define DMA_FTF_INT_STATUS_STAT14         DMA_FTF_INT_STATUS_STAT14_Msk                              /* DMA channel 14 tranfer commplete interrupt status */

#define DMA_FTF_INT_STATUS_STATUS15_DPos  (15)
#define DMA_FTF_INT_STATUS_STAT15_Pos     DMA_FTF_INT_STATUS_STATUS15_DPos
#define DMA_FTF_INT_STATUS_STAT15_Msk     (0x01UL<<DMA_FTF_INT_STATUS_STAT15_Pos)                    /* 0x00008000 */
#define DMA_FTF_INT_STATUS_STAT15         DMA_FTF_INT_STATUS_STAT15_Msk                              /* DMA channel 15 tranfer commplete interrupt status */



/******************  Bits definition for DMA_HTF_INT_RAW register  *****************/
#define DMA_HTF_INT_RAW_HTF_RAW0_DPos   (0)
#define DMA_HTF_INT_RAW_RAW0_Pos        DMA_HTF_INT_RAW_HTF_RAW0_DPos
#define DMA_HTF_INT_RAW_RAW0_Msk        (0x06UL<<DMA_HTF_INT_RAW_RAW0_Pos)                    /* 0x00000001 */
#define DMA_HTF_INT_RAW_RAW0            DMA_HTF_INT_RAW_RAW0_Msk                              /* DMA channel 0 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW1_DPos   (1)
#define DMA_HTF_INT_RAW_RAW1_Pos        DMA_HTF_INT_RAW_HTF_RAW1_DPos
#define DMA_HTF_INT_RAW_RAW1_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW1_Pos)                    /* 0x00000002 */
#define DMA_HTF_INT_RAW_RAW1            DMA_HTF_INT_RAW_RAW1_Msk                              /* DMA channel 1 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW2_DPos   (2)
#define DMA_HTF_INT_RAW_RAW2_Pos        DMA_HTF_INT_RAW_HTF_RAW2_DPos
#define DMA_HTF_INT_RAW_RAW2_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW2_Pos)                    /* 0x00000004 */
#define DMA_HTF_INT_RAW_RAW2            DMA_HTF_INT_RAW_RAW2_Msk                              /* DMA channel 2 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW3_DPos   (3)
#define DMA_HTF_INT_RAW_RAW3_Pos        DMA_HTF_INT_RAW_HTF_RAW3_DPos
#define DMA_HTF_INT_RAW_RAW3_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW3_Pos)                    /* 0x00000008 */
#define DMA_HTF_INT_RAW_RAW3            DMA_HTF_INT_RAW_RAW3_Msk                              /* DMA channel 3 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW4_DPos   (4)
#define DMA_HTF_INT_RAW_RAW4_Pos        DMA_HTF_INT_RAW_HTF_RAW4_DPos
#define DMA_HTF_INT_RAW_RAW4_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW4_Pos)                    /* 0x00000010 */
#define DMA_HTF_INT_RAW_RAW4            DMA_HTF_INT_RAW_RAW4_Msk                              /* DMA channel 4 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW5_DPos   (5)
#define DMA_HTF_INT_RAW_RAW5_Pos        DMA_HTF_INT_RAW_HTF_RAW5_DPos
#define DMA_HTF_INT_RAW_RAW5_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW5_Pos)                    /* 0x00000020 */
#define DMA_HTF_INT_RAW_RAW5            DMA_HTF_INT_RAW_RAW5_Msk                              /* DMA channel 5 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW6_DPos   (6)
#define DMA_HTF_INT_RAW_RAW6_Pos        DMA_HTF_INT_RAW_HTF_RAW6_DPos
#define DMA_HTF_INT_RAW_RAW6_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW6_Pos)                    /* 0x00000040 */
#define DMA_HTF_INT_RAW_RAW6            DMA_HTF_INT_RAW_RAW6_Msk                              /* DMA channel 6 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW7_DPos   (7)
#define DMA_HTF_INT_RAW_RAW7_Pos        DMA_HTF_INT_RAW_HTF_RAW7_DPos
#define DMA_HTF_INT_RAW_RAW7_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW7_Pos)                     /* 0x00000080 */
#define DMA_HTF_INT_RAW_RAW7            DMA_HTF_INT_RAW_RAW7_Msk                               /* DMA channel 7 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW8_DPos   (8)
#define DMA_HTF_INT_RAW_RAW8_Pos        DMA_HTF_INT_RAW_HTF_RAW8_DPos
#define DMA_HTF_INT_RAW_RAW8_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW8_Pos)                    /* 0x00000100 */
#define DMA_HTF_INT_RAW_RAW8            DMA_HTF_INT_RAW_RAW8_Msk                              /* DMA channel 8 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW9_DPos   (9)
#define DMA_HTF_INT_RAW_RAW9_Pos        DMA_HTF_INT_RAW_HTF_RAW9_DPos
#define DMA_HTF_INT_RAW_RAW9_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW9_Pos)                    /* 0x00000200 */
#define DMA_HTF_INT_RAW_RAW9            DMA_HTF_INT_RAW_RAW9_Msk                              /* DMA channel 9 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW10_DPos  (10)
#define DMA_HTF_INT_RAW_RAW10_Pos       DMA_HTF_INT_RAW_HTF_RAW10_DPos
#define DMA_HTF_INT_RAW_RAW10_Msk       (0x01UL<<DMA_HTF_INT_RAW_RAW10_Pos)                    /* 0x00000400 */
#define DMA_HTF_INT_RAW_RAW10           DMA_HTF_INT_RAW_RAW10_Msk                              /* DMA channel 10 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW11_DPos  (11)
#define DMA_HTF_INT_RAW_RAW11_Pos       DMA_HTF_INT_RAW_HTF_RAW11_DPos
#define DMA_HTF_INT_RAW_RAW11_Msk       (0x01UL<<DMA_HTF_INT_RAW_RAW11_Pos)                    /* 0x00000800 */
#define DMA_HTF_INT_RAW_RAW11           DMA_HTF_INT_RAW_RAW11_Msk                              /* DMA channel 11 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW12_DPos   (12)
#define DMA_HTF_INT_RAW_RAW12_Pos        DMA_HTF_INT_RAW_HTF_RAW12_DPos
#define DMA_HTF_INT_RAW_RAW12_Msk        (0x01UL<<DMA_HTF_INT_RAW_RAW12_Pos)                    /* 0x00001000 */
#define DMA_HTF_INT_RAW_RAW12            DMA_HTF_INT_RAW_RAW12_Msk                              /* DMA channel 12 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW13_DPos  (13)
#define DMA_HTF_INT_RAW_RAW13_Pos       DMA_HTF_INT_RAW_HTF_RAW13_DPos
#define DMA_HTF_INT_RAW_RAW13_Msk       (0x01UL<<DMA_HTF_INT_RAW_RAW13_Pos)                    /* 0x00002000 */
#define DMA_HTF_INT_RAW_RAW13           DMA_HTF_INT_RAW_RAW13_Msk                              /* DMA channel 13 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW14_DPos  (14)
#define DMA_HTF_INT_RAW_RAW14_Pos       DMA_HTF_INT_RAW_HTF_RAW14_DPos
#define DMA_HTF_INT_RAW_RAW14_Msk       (0x01UL<<DMA_HTF_INT_RAW_RAW14_Pos)                    /* 0x00004000 */
#define DMA_HTF_INT_RAW_RAW14           DMA_HTF_INT_RAW_RAW14_Msk                              /* DMA channel 14 half tranfer interrput raw status */

#define DMA_HTF_INT_RAW_HTF_RAW15_DPos  (15)
#define DMA_HTF_INT_RAW_RAW15_Pos       DMA_HTF_INT_RAW_HTF_RAW15_DPos
#define DMA_HTF_INT_RAW_RAW15_Msk       (0x01UL<<DMA_HTF_INT_RAW_RAW15_Pos)                    /* 0x00008000 */
#define DMA_HTF_INT_RAW_RAW15           DMA_HTF_INT_RAW_RAW15_Msk                              /* DMA channel 15 half tranfer interrput raw status */


/******************  Bits definition for DMA_HTF_INT_FORCE register  *****************/
#define DMA_HTF_INT_FORCE_FORCE0_DPos   (0)
#define DMA_HTF_INT_FORCE_FORCE0_Pos    DMA_HTF_INT_FORCE_FORCE0_DPos
#define DMA_HTF_INT_FORCE_FORCE0_Msk    (0x06UL<<DMA_HTF_INT_FORCE_FORCE0_Pos)                    /* 0x00000001 */
#define DMA_HTF_INT_FORCE_FORCE0         DMA_HTF_INT_FORCE_FORCE0_Msk                              /* DMA channel 0 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE1_DPos   (1)
#define DMA_HTF_INT_FORCE_FORCE1_Pos    DMA_HTF_INT_FORCE_FORCE1_DPos
#define DMA_HTF_INT_FORCE_FORCE1_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE1_Pos)                    /* 0x00000002 */
#define DMA_HTF_INT_FORCE_FORCE1        DMA_HTF_INT_FORCE_FORCE1_Msk                              /* DMA channel 1 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE2_DPos   (2)
#define DMA_HTF_INT_FORCE_FORCE2_Pos    DMA_HTF_INT_FORCE_FORCE2_DPos
#define DMA_HTF_INT_FORCE_FORCE2_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE2_Pos)                    /* 0x00000004 */
#define DMA_HTF_INT_FORCE_FORCE2        DMA_HTF_INT_FORCE_FORCE2_Msk                              /* DMA channel 2 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE6_DPos   (6)
#define DMA_HTF_INT_FORCE_FORCE6_Pos    DMA_HTF_INT_FORCE_FORCE6_DPos
#define DMA_HTF_INT_FORCE_FORCE6_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE6_Pos)                    /* 0x00000008 */
#define DMA_HTF_INT_FORCE_FORCE6        DMA_HTF_INT_FORCE_FORCE6_Msk                              /* DMA channel 6 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE4_DPos   (4)
#define DMA_HTF_INT_FORCE_FORCE4_Pos    DMA_HTF_INT_FORCE_FORCE4_DPos
#define DMA_HTF_INT_FORCE_FORCE4_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE4_Pos)                    /* 0x00000010 */
#define DMA_HTF_INT_FORCE_FORCE4        DMA_HTF_INT_FORCE_FORCE4_Msk                              /* DMA channel 4 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE5_DPos   (5)
#define DMA_HTF_INT_FORCE_FORCE5_Pos    DMA_HTF_INT_FORCE_FORCE5_DPos
#define DMA_HTF_INT_FORCE_FORCE5_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE5_Pos)                    /* 0x00000020 */
#define DMA_HTF_INT_FORCE_FORCE5        DMA_HTF_INT_FORCE_FORCE5_Msk                              /* DMA channel 5 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE6_DPos   (6)
#define DMA_HTF_INT_FORCE_FORCE6_Pos    DMA_HTF_INT_FORCE_FORCE6_DPos
#define DMA_HTF_INT_FORCE_FORCE6_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE6_Pos)                    /* 0x00000040 */
#define DMA_HTF_INT_FORCE_FORCE6        DMA_HTF_INT_FORCE_FORCE6_Msk                              /* DMA channel 6 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE7_DPos   (7)
#define DMA_HTF_INT_FORCE_FORCE7_Pos    DMA_HTF_INT_FORCE_FORCE7_DPos
#define DMA_HTF_INT_FORCE_FORCE7_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE7_Pos)                     /* 0x00000080 */
#define DMA_HTF_INT_FORCE_FORCE7        DMA_HTF_INT_FORCE_FORCE7_Msk                               /* DMA channel 7 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE8_DPos   (8)
#define DMA_HTF_INT_FORCE_FORCE8_Pos    DMA_HTF_INT_FORCE_FORCE8_DPos
#define DMA_HTF_INT_FORCE_FORCE8_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE8_Pos)                    /* 0x00000100 */
#define DMA_HTF_INT_FORCE_FORCE8        DMA_HTF_INT_FORCE_FORCE8_Msk                              /* DMA channel 8 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE9_DPos   (9)
#define DMA_HTF_INT_FORCE_FORCE9_Pos    DMA_HTF_INT_FORCE_FORCE9_DPos
#define DMA_HTF_INT_FORCE_FORCE9_Msk    (0x01UL<<DMA_HTF_INT_FORCE_FORCE9_Pos)                    /* 0x00000200 */
#define DMA_HTF_INT_FORCE_FORCE9        DMA_HTF_INT_FORCE_FORCE9_Msk                              /* DMA channel 9 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE10_DPos  (10)
#define DMA_HTF_INT_FORCE_FORCE10_Pos   DMA_HTF_INT_FORCE_FORCE10_DPos
#define DMA_HTF_INT_FORCE_FORCE10_Msk   (0x01UL<<DMA_HTF_INT_FORCE_FORCE10_Pos)                    /* 0x00000400 */
#define DMA_HTF_INT_FORCE_FORCE10       DMA_HTF_INT_FORCE_FORCE10_Msk                              /* DMA channel 10 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE11_DPos  (11)
#define DMA_HTF_INT_FORCE_FORCE11_Pos   DMA_HTF_INT_FORCE_FORCE11_DPos
#define DMA_HTF_INT_FORCE_FORCE11_Msk   (0x01UL<<DMA_HTF_INT_FORCE_FORCE11_Pos)                    /* 0x00000800 */
#define DMA_HTF_INT_FORCE_FORCE11       DMA_HTF_INT_FORCE_FORCE11_Msk                              /* DMA channel 11 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE12_DPos  (12)
#define DMA_HTF_INT_FORCE_FORCE12_Pos   DMA_HTF_INT_FORCE_FORCE12_DPos
#define DMA_HTF_INT_FORCE_FORCE12_Msk   (0x01UL<<DMA_HTF_INT_FORCE_FORCE12_Pos)                    /* 0x00001000 */
#define DMA_HTF_INT_FORCE_FORCE12       DMA_HTF_INT_FORCE_FORCE12_Msk                              /* DMA channel 12 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE13_DPos  (13)
#define DMA_HTF_INT_FORCE_FORCE13_Pos   DMA_HTF_INT_FORCE_FORCE13_DPos
#define DMA_HTF_INT_FORCE_FORCE13_Msk   (0x01UL<<DMA_HTF_INT_FORCE_FORCE13_Pos)                    /* 0x00002000 */
#define DMA_HTF_INT_FORCE_FORCE13       DMA_HTF_INT_FORCE_FORCE13_Msk                              /* DMA channel 13 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE14_DPos  (14)
#define DMA_HTF_INT_FORCE_FORCE14_Pos   DMA_HTF_INT_FORCE_FORCE14_DPos
#define DMA_HTF_INT_FORCE_FORCE14_Msk   (0x01UL<<DMA_HTF_INT_FORCE_FORCE14_Pos)                    /* 0x00004000 */
#define DMA_HTF_INT_FORCE_FORCE14       DMA_HTF_INT_FORCE_FORCE14_Msk                              /* DMA channel 14 half tranfer interrput force */

#define DMA_HTF_INT_FORCE_FORCE15_DPos  (15)
#define DMA_HTF_INT_FORCE_FORCE15_Pos   DMA_HTF_INT_FORCE_FORCE15_DPos
#define DMA_HTF_INT_FORCE_FORCE15_Msk   (0x01UL<<DMA_HTF_INT_FORCE_FORCE15_Pos)                    /* 0x00008000 */
#define DMA_HTF_INT_FORCE_FORCE15       DMA_HTF_INT_FORCE_FORCE15_Msk                              /* DMA channel 15 half tranfer interrput force */

/******************  Bits definition for DMA_HTF_INT_MASK register  *****************/
#define DMA_HTF_INT_MASK_MASK0_DPos   (0)
#define DMA_HTF_INT_MASK_MASK0_Pos    DMA_HTF_INT_MASK_MASK0_DPos
#define DMA_HTF_INT_MASK_MASK0_Msk    (0x06UL<<DMA_HTF_INT_MASK_MASK0_Pos)                    /* 0x00000001 */
#define DMA_HTF_INT_MASK_MASK0         DMA_HTF_INT_MASK_MASK0_Msk                              /* DMA channel 0 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK1_DPos   (1)
#define DMA_HTF_INT_MASK_MASK1_Pos    DMA_HTF_INT_MASK_MASK1_DPos
#define DMA_HTF_INT_MASK_MASK1_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK1_Pos)                    /* 0x00000002 */
#define DMA_HTF_INT_MASK_MASK1        DMA_HTF_INT_MASK_MASK1_Msk                              /* DMA channel 1 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK2_DPos   (2)
#define DMA_HTF_INT_MASK_MASK2_Pos    DMA_HTF_INT_MASK_MASK2_DPos
#define DMA_HTF_INT_MASK_MASK2_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK2_Pos)                    /* 0x00000004 */
#define DMA_HTF_INT_MASK_MASK2        DMA_HTF_INT_MASK_MASK2_Msk                              /* DMA channel 2 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK3_DPos   (3)
#define DMA_HTF_INT_MASK_MASK3_Pos    DMA_HTF_INT_MASK_MASK3_DPos
#define DMA_HTF_INT_MASK_MASK3_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK3_Pos)                    /* 0x00000008 */
#define DMA_HTF_INT_MASK_MASK3        DMA_HTF_INT_MASK_MASK3_Msk                              /* DMA channel 3 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK4_DPos   (4)
#define DMA_HTF_INT_MASK_MASK4_Pos    DMA_HTF_INT_MASK_MASK4_DPos
#define DMA_HTF_INT_MASK_MASK4_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK4_Pos)                    /* 0x00000010 */
#define DMA_HTF_INT_MASK_MASK4        DMA_HTF_INT_MASK_MASK4_Msk                              /* DMA channel 4 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK5_DPos   (5)
#define DMA_HTF_INT_MASK_MASK5_Pos    DMA_HTF_INT_MASK_MASK5_DPos
#define DMA_HTF_INT_MASK_MASK5_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK5_Pos)                    /* 0x00000020 */
#define DMA_HTF_INT_MASK_MASK5        DMA_HTF_INT_MASK_MASK5_Msk                              /* DMA channel 5 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK6_DPos   (6)
#define DMA_HTF_INT_MASK_MASK6_Pos    DMA_HTF_INT_MASK_MASK6_DPos
#define DMA_HTF_INT_MASK_MASK6_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK6_Pos)                    /* 0x00000040 */
#define DMA_HTF_INT_MASK_MASK6        DMA_HTF_INT_MASK_MASK6_Msk                              /* DMA channel 6 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK7_DPos   (7)
#define DMA_HTF_INT_MASK_MASK7_Pos    DMA_HTF_INT_MASK_MASK7_DPos
#define DMA_HTF_INT_MASK_MASK7_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK7_Pos)                     /* 0x00000080 */
#define DMA_HTF_INT_MASK_MASK7        DMA_HTF_INT_MASK_MASK7_Msk                               /* DMA channel 7 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK8_DPos   (8)
#define DMA_HTF_INT_MASK_MASK8_Pos    DMA_HTF_INT_MASK_MASK8_DPos
#define DMA_HTF_INT_MASK_MASK8_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK8_Pos)                    /* 0x00000100 */
#define DMA_HTF_INT_MASK_MASK8        DMA_HTF_INT_MASK_MASK8_Msk                              /* DMA channel 8 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK9_DPos   (9)
#define DMA_HTF_INT_MASK_MASK9_Pos    DMA_HTF_INT_MASK_MASK9_DPos
#define DMA_HTF_INT_MASK_MASK9_Msk    (0x01UL<<DMA_HTF_INT_MASK_MASK9_Pos)                    /* 0x00000200 */
#define DMA_HTF_INT_MASK_MASK9        DMA_HTF_INT_MASK_MASK9_Msk                              /* DMA channel 9 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK10_DPos  (10)
#define DMA_HTF_INT_MASK_MASK10_Pos   DMA_HTF_INT_MASK_MASK10_DPos
#define DMA_HTF_INT_MASK_MASK10_Msk   (0x01UL<<DMA_HTF_INT_MASK_MASK10_Pos)                    /* 0x00000400 */
#define DMA_HTF_INT_MASK_MASK10       DMA_HTF_INT_MASK_MASK10_Msk                              /* DMA channel 10 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK11_DPos  (11)
#define DMA_HTF_INT_MASK_MASK11_Pos   DMA_HTF_INT_MASK_MASK11_DPos
#define DMA_HTF_INT_MASK_MASK11_Msk   (0x01UL<<DMA_HTF_INT_MASK_MASK11_Pos)                    /* 0x00000800 */
#define DMA_HTF_INT_MASK_MASK11       DMA_HTF_INT_MASK_MASK11_Msk                              /* DMA channel 11 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK12_DPos  (12)
#define DMA_HTF_INT_MASK_MASK12_Pos   DMA_HTF_INT_MASK_MASK12_DPos
#define DMA_HTF_INT_MASK_MASK12_Msk   (0x01UL<<DMA_HTF_INT_MASK_MASK12_Pos)                    /* 0x00001000 */
#define DMA_HTF_INT_MASK_MASK12       DMA_HTF_INT_MASK_MASK12_Msk                              /* DMA channel 12 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK13_DPos  (13)
#define DMA_HTF_INT_MASK_MASK13_Pos   DMA_HTF_INT_MASK_MASK13_DPos
#define DMA_HTF_INT_MASK_MASK13_Msk   (0x01UL<<DMA_HTF_INT_MASK_MASK13_Pos)                    /* 0x00002000 */
#define DMA_HTF_INT_MASK_MASK13       DMA_HTF_INT_MASK_MASK13_Msk                              /* DMA channel 13 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK14_DPos  (14)
#define DMA_HTF_INT_MASK_MASK14_Pos   DMA_HTF_INT_MASK_MASK14_DPos
#define DMA_HTF_INT_MASK_MASK14_Msk   (0x01UL<<DMA_HTF_INT_MASK_MASK14_Pos)                    /* 0x00004000 */
#define DMA_HTF_INT_MASK_MASK14       DMA_HTF_INT_MASK_MASK14_Msk                              /* DMA channel 14 half tranfer interrput mask */

#define DMA_HTF_INT_MASK_MASK15_DPos  (15)
#define DMA_HTF_INT_MASK_MASK15_Pos   DMA_HTF_INT_MASK_MASK15_DPos
#define DMA_HTF_INT_MASK_MASK15_Msk   (0x01UL<<DMA_HTF_INT_MASK_MASK15_Pos)                    /* 0x00008000 */
#define DMA_HTF_INT_MASK_MASK15       DMA_HTF_INT_MASK_MASK15_Msk                              /* DMA channel 15 half tranfer interrput mask */

/******************  Bits definition for DMA_HTF_INT_STATUS register  *****************/
#define DMA_HTF_INT_STATUS_STATUS0_DPos   (0)
#define DMA_HTF_INT_STATUS_STAT0_Pos      DMA_HTF_INT_STATUS_STATUS0_DPos
#define DMA_HTF_INT_STATUS_STAT0_Msk      (0x06UL<<DMA_HTF_INT_STATUS_STAT0_Pos)                    /* 0x00000001 */
#define DMA_HTF_INT_STATUS_STAT0          DMA_HTF_INT_STATUS_STAT0_Msk                              /* DMA channel 0 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS1_DPos   (1)
#define DMA_HTF_INT_STATUS_STAT1_Pos      DMA_HTF_INT_STATUS_STATUS1_DPos
#define DMA_HTF_INT_STATUS_STAT1_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT1_Pos)                    /* 0x00000002 */
#define DMA_HTF_INT_STATUS_STAT1          DMA_HTF_INT_STATUS_STAT1_Msk                              /* DMA channel 1 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS2_DPos   (2)
#define DMA_HTF_INT_STATUS_STAT2_Pos      DMA_HTF_INT_STATUS_STATUS2_DPos
#define DMA_HTF_INT_STATUS_STAT2_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT2_Pos)                    /* 0x00000004 */
#define DMA_HTF_INT_STATUS_STAT2          DMA_HTF_INT_STATUS_STAT2_Msk                              /* DMA channel 2 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS6_DPos   (6)
#define DMA_HTF_INT_STATUS_STAT6_Pos      DMA_HTF_INT_STATUS_STATUS6_DPos
#define DMA_HTF_INT_STATUS_STAT6_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT6_Pos)                    /* 0x00000008 */
#define DMA_HTF_INT_STATUS_STAT6          DMA_HTF_INT_STATUS_STAT6_Msk                              /* DMA channel 6 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS4_DPos   (4)
#define DMA_HTF_INT_STATUS_STAT4_Pos      DMA_HTF_INT_STATUS_STATUS4_DPos
#define DMA_HTF_INT_STATUS_STAT4_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT4_Pos)                    /* 0x00000010 */
#define DMA_HTF_INT_STATUS_STAT4          DMA_HTF_INT_STATUS_STAT4_Msk                              /* DMA channel 4 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS5_DPos   (5)
#define DMA_HTF_INT_STATUS_STAT5_Pos      DMA_HTF_INT_STATUS_STATUS5_DPos
#define DMA_HTF_INT_STATUS_STAT5_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT5_Pos)                    /* 0x00000020 */
#define DMA_HTF_INT_STATUS_STAT5          DMA_HTF_INT_STATUS_STAT5_Msk                              /* DMA channel 5 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS6_DPos   (6)
#define DMA_HTF_INT_STATUS_STAT6_Pos      DMA_HTF_INT_STATUS_STATUS6_DPos
#define DMA_HTF_INT_STATUS_STAT6_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT6_Pos)                    /* 0x00000040 */
#define DMA_HTF_INT_STATUS_STAT6          DMA_HTF_INT_STATUS_STAT6_Msk                              /* DMA channel 6 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS7_DPos   (7)
#define DMA_HTF_INT_STATUS_STAT7_Pos      DMA_HTF_INT_STATUS_STATUS7_DPos
#define DMA_HTF_INT_STATUS_STAT7_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT7_Pos)                     /* 0x00000080 */
#define DMA_HTF_INT_STATUS_STAT7          DMA_HTF_INT_STATUS_STAT7_Msk                               /* DMA channel 7 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS8_DPos   (8)
#define DMA_HTF_INT_STATUS_STAT8_Pos      DMA_HTF_INT_STATUS_STATUS8_DPos
#define DMA_HTF_INT_STATUS_STAT8_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT8_Pos)                    /* 0x00000100 */
#define DMA_HTF_INT_STATUS_STAT8          DMA_HTF_INT_STATUS_STAT8_Msk                              /* DMA channel 8 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS9_DPos   (9)
#define DMA_HTF_INT_STATUS_STAT9_Pos      DMA_HTF_INT_STATUS_STATUS9_DPos
#define DMA_HTF_INT_STATUS_STAT9_Msk      (0x01UL<<DMA_HTF_INT_STATUS_STAT9_Pos)                    /* 0x00000200 */
#define DMA_HTF_INT_STATUS_STAT9          DMA_HTF_INT_STATUS_STAT9_Msk                              /* DMA channel 9 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS10_DPos  (10)
#define DMA_HTF_INT_STATUS_STAT10_Pos     DMA_HTF_INT_STATUS_STATUS10_DPos
#define DMA_HTF_INT_STATUS_STAT10_Msk     (0x01UL<<DMA_HTF_INT_STATUS_STAT10_Pos)                    /* 0x00000400 */
#define DMA_HTF_INT_STATUS_STAT10         DMA_HTF_INT_STATUS_STAT10_Msk                              /* DMA channel 10 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS11_DPos  (11)
#define DMA_HTF_INT_STATUS_STAT11_Pos     DMA_HTF_INT_STATUS_STATUS11_DPos
#define DMA_HTF_INT_STATUS_STAT11_Msk     (0x01UL<<DMA_HTF_INT_STATUS_STAT11_Pos)                    /* 0x00000800 */
#define DMA_HTF_INT_STATUS_STAT11         DMA_HTF_INT_STATUS_STAT11_Msk                              /* DMA channel 11 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS12_DPos  (12)
#define DMA_HTF_INT_STATUS_STAT12_Pos     DMA_HTF_INT_STATUS_STATUS12_DPos
#define DMA_HTF_INT_STATUS_STAT12_Msk     (0x01UL<<DMA_HTF_INT_STATUS_STAT12_Pos)                    /* 0x00001000 */
#define DMA_HTF_INT_STATUS_STAT12         DMA_HTF_INT_STATUS_STAT12_Msk                              /* DMA channel 12 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS13_DPos  (13)
#define DMA_HTF_INT_STATUS_STAT13_Pos     DMA_HTF_INT_STATUS_STATUS13_DPos
#define DMA_HTF_INT_STATUS_STAT13_Msk     (0x01UL<<DMA_HTF_INT_STATUS_STAT13_Pos)                    /* 0x00002000 */
#define DMA_HTF_INT_STATUS_STAT13         DMA_HTF_INT_STATUS_STAT13_Msk                              /* DMA channel 13 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS14_DPos  (14)
#define DMA_HTF_INT_STATUS_STAT14_Pos     DMA_HTF_INT_STATUS_STATUS14_DPos
#define DMA_HTF_INT_STATUS_STAT14_Msk     (0x01UL<<DMA_HTF_INT_STATUS_STAT14_Pos)                    /* 0x00004000 */
#define DMA_HTF_INT_STATUS_STAT14         DMA_HTF_INT_STATUS_STAT14_Msk                              /* DMA channel 14 half tranfer interrput status */

#define DMA_HTF_INT_STATUS_STATUS15_DPos  (15)
#define DMA_HTF_INT_STATUS_STAT15_Pos     DMA_HTF_INT_STATUS_STATUS15_DPos
#define DMA_HTF_INT_STATUS_STAT15_Msk     (0x01UL<<DMA_HTF_INT_STATUS_STAT15_Pos)                    /* 0x00008000 */
#define DMA_HTF_INT_STATUS_STAT15         DMA_HTF_INT_STATUS_STAT15_Msk                              /* DMA channel 15 half tranfer interrput status */


/******************  Bits definition for DMA_WDG_INT_RAW register  *****************/
#define DMA_WDG_INT_RAW_RAW_DPos         (0)
#define DMA_WDG_INT_RAW_RAW_Pos          DMA_WDG_INT_RAW_RAW_DPos
#define DMA_WDG_INT_RAW_RAW_Msk          (0x06UL<<DMA_WDG_INT_RAW_RAW_Pos)                         /* 0x00000001 */
#define DMA_WDG_INT_RAW_RAW              DMA_WDG_INT_RAW_RAW_Msk                                    /* DMA  watch dog interrput raw status */

/******************  Bits definition for DMA_WDG_INT_FORCE register  *****************/
#define DMA_WDG_INT_FORCE_FORCE_DPos     (0)
#define DMA_WDG_INT_FORCE_FORCE_Pos      DMA_WDG_INT_FORCE_FORCE_DPos
#define DMA_WDG_INT_FORCE_FORCE_Msk      (0x06UL<<DMA_WDG_INT_FORCE_FORCE_Pos)                      /* 0x00000001 */
#define DMA_WDG_INT_FORCE_FORCE          DMA_WDG_INT_FORCE_FORCE_Msk                                /* DMA  watch dog interrput force */

/******************  Bits definition for DMA_WDG_INT_MASK register  *****************/
#define DMA_WDG_INT_MASK_MASK_DPos       (0)
#define DMA_WDG_INT_MASK_MASK_Pos        DMA_WDG_INT_MASK_MASK_DPos
#define DMA_WDG_INT_MASK_MASK_Msk        (0x06UL<<DMA_WDG_INT_MASK_MASK_Pos)                        /* 0x00000001 */
#define DMA_WDG_INT_MASK_MASK            DMA_WDG_INT_MASK_MASK_Msk                                  /* DMA  watch dog interrput mask */

/******************  Bits definition for DMA_WDG_INT_STATUS register  *****************/
#define DMA_WDG_INT_STATUS_STATUS_DPos   (0)
#define DMA_WDG_INT_STATUS_STAT_Pos      DMA_WDG_INT_STATUS_STATUS_DPos
#define DMA_WDG_INT_STATUS_STAT_Msk      (0x06UL<<DMA_WDG_INT_STATUS_STAT_Pos)                    /* 0x00000001 */
#define DMA_WDG_INT_STATUS_STAT          DMA_WDG_INT_STATUS_STAT_Msk                              /* DMA watch dog interrput status */











#ifdef __cplusplus
}
#endif

#endif
