/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_mpu_regs.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:            2024/08/01
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/01     1.0     build this module
 * Description:     This file contains all the register correlation defines for the MPU firmware library.
 */
#ifndef AS32X601_MPU_REG_H
#define AS32X601_MPU_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_addrmap.h"
#include "as32x601.h"

/*
 * @brief MPU I-Port registers structure
 */
typedef struct 
{
    __IO uint32_t PTEN;
    __IO uint32_t RPTEN;
    __IO uint32_t RPTS;
}MPU_IPort_TypeDef;

/*
 * @brief MPU / D-Port / P-Port registers structure
 */
typedef struct 
{
    __IO uint32_t PTEN;
    __IO uint32_t WPTEN;
    __IO uint32_t RPTEN;
    __IO uint32_t WPTS;
    __IO uint32_t RPTS;
}MPU_DPort_TypeDef;

/*
 * @brief MPU P-Port registers structure
 */
typedef MPU_DPort_TypeDef MPU_PPort_TypeDef;

/*
 * @brief MPU DMA-Port registers structure
 */
typedef MPU_DPort_TypeDef MPU_DMAPort_TypeDef;


/*
 * @brief MPU  Channel registers structure
 */
typedef struct 
{
    __IO uint32_t SADDR;
    __IO uint32_t EADDR;
}MPU_Channel_TypeDef;

/*
 * @addtogroup MPU peripheral declaration
 */
#define MPU0_IBUS     ((MPU_IPort_TypeDef *)(MPU0_IBUS_BASE))
#define MPU1_DBUS     ((MPU_DPort_TypeDef *)(MPU1_DBUS_BASE))
#define MPU2_PBUS     ((MPU_PPort_TypeDef *)(MPU2_PBUS_BASE))
#define MPU3_DMA0     ((MPU_DMAPort_TypeDef *)(MPU3_DMA0_BASE))
#define MPU4_DMA1     ((MPU_DMAPort_TypeDef *)(MPU4_DMA1_BASE))

/*
 * @addtogroup MPU I-Port Channel
 */
#define MPU0_Channel0  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x0CU))
#define MPU0_Channel1  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x14U))
#define MPU0_Channel2  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x1CU))
#define MPU0_Channel3  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x24U))
#define MPU0_Channel4  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x2CU))
#define MPU0_Channel5  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x34U))
#define MPU0_Channel6  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x3CU))
#define MPU0_Channel7  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x44U))
#define MPU0_Channel8  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x4CU))
#define MPU0_Channel9  ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x54U))
#define MPU0_Channel10 ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x5CU))
#define MPU0_Channel11 ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x64U))
#define MPU0_Channel12 ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x6CU))
#define MPU0_Channel13 ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x74U))
#define MPU0_Channel14 ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x7CU))
#define MPU0_Channel15 ((MPU_Channel_TypeDef *)(MPU0_IBUS_BASE+0x84U))

/*
 * @addtogroup MPU I-Port Channel
 */
#define MPU1_Channel0  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x0CU))
#define MPU1_Channel1  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x14U))
#define MPU1_Channel2  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x1CU))
#define MPU1_Channel3  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x24U))
#define MPU1_Channel4  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x2CU))
#define MPU1_Channel5  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x34U))
#define MPU1_Channel6  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x3CU))
#define MPU1_Channel7  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x44U))
#define MPU1_Channel8  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x4CU))
#define MPU1_Channel9  ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x54U))
#define MPU1_Channel10 ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x5CU))
#define MPU1_Channel11 ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x64U))
#define MPU1_Channel12 ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x6CU))
#define MPU1_Channel13 ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x74U))
#define MPU1_Channel14 ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x7CU))
#define MPU1_Channel15 ((MPU_Channel_TypeDef *)(MPU1_DBUS_BASE+0x84U))

/*
 * @addtogroup MPU D-Port Channel
 */
#define MPU2_Channel0  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x14U))
#define MPU2_Channel1  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x1CU))
#define MPU2_Channel2  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x24U))
#define MPU2_Channel3  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x2CU))
#define MPU2_Channel4  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x34U))
#define MPU2_Channel5  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x3CU))
#define MPU2_Channel6  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x44U))
#define MPU2_Channel7  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x4CU))
#define MPU2_Channel8  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x54U))
#define MPU2_Channel9  ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x5CU))
#define MPU2_Channel10 ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x64U))
#define MPU2_Channel11 ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x6CU))
#define MPU2_Channel12 ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x74U))
#define MPU2_Channel13 ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x7CU))
#define MPU2_Channel14 ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x84U))
#define MPU2_Channel15 ((MPU_Channel_TypeDef *)(MPU2_PBUS_BASE+0x8CU))

/*
 * @addtogroup MPU DMA0-Port Channel
 */
#define MPU3_Channel0  ((MPU_Channel_TypeDef *)(MPU3_DMA0_BASE+0x14U))
#define MPU3_Channel1  ((MPU_Channel_TypeDef *)(MPU3_DMA0_BASE+0x1CU))
#define MPU3_Channel2  ((MPU_Channel_TypeDef *)(MPU3_DMA0_BASE+0x24U))
#define MPU3_Channel3  ((MPU_Channel_TypeDef *)(MPU3_DMA0_BASE+0x2CU))
#define MPU3_Channel4  ((MPU_Channel_TypeDef *)(MPU3_DMA0_BASE+0x34U))
#define MPU3_Channel5  ((MPU_Channel_TypeDef *)(MPU3_DMA0_BASE+0x3CU))
#define MPU3_Channel6  ((MPU_Channel_TypeDef *)(MPU3_DMA0_BASE+0x44U))
#define MPU3_Channel7  ((MPU_Channel_TypeDef *)(MPU3_DMA0_BASE+0x4CU))

/*
 * @addtogroup MPU DMA1-Port Channel
 */
#define MPU4_Channel0  ((MPU_Channel_TypeDef *)(MPU4_DMA1_BASE+0x14U))
#define MPU4_Channel1  ((MPU_Channel_TypeDef *)(MPU4_DMA1_BASE+0x1CU))
#define MPU4_Channel2  ((MPU_Channel_TypeDef *)(MPU4_DMA1_BASE+0x24U))
#define MPU4_Channel3  ((MPU_Channel_TypeDef *)(MPU4_DMA1_BASE+0x2CU))
#define MPU4_Channel4  ((MPU_Channel_TypeDef *)(MPU4_DMA1_BASE+0x34U))
#define MPU4_Channel5  ((MPU_Channel_TypeDef *)(MPU4_DMA1_BASE+0x3CU))
#define MPU4_Channel6  ((MPU_Channel_TypeDef *)(MPU4_DMA1_BASE+0x44U))
#define MPU4_Channel7  ((MPU_Channel_TypeDef *)(MPU4_DMA1_BASE+0x4CU))

/******************  Bit definition for MPU_PTEN register  *******************/
#define MPU_PTEN_EN0_DPos       (0U)
#define MPU_PTEN_EN0_Pos        MPU_PTEN_EN0_DPos
#define MPU_PTEN_EN0_Msk        (0x1UL << MPU_PTEN_EN0_Pos)                /* 0x00000001 */
#define MPU_PTEN_EN0            MPU_PTEN_EN0_Msk                           /* Enable MPU Channel 0. */

#define MPU_PTEN_EN1_DPos       (1U)
#define MPU_PTEN_EN1_Pos        MPU_PTEN_EN1_DPos
#define MPU_PTEN_EN1_Msk        (0x1UL << MPU_PTEN_EN1_Pos)                /* 0x00000002 */
#define MPU_PTEN_EN1            MPU_PTEN_EN1_Msk                           /* Enable MPU Channel 1. */

#define MPU_PTEN_EN2_DPos       (2U)
#define MPU_PTEN_EN2_Pos        MPU_PTEN_EN2_DPos
#define MPU_PTEN_EN2_Msk        (0x1UL << MPU_PTEN_EN2_Pos)                /* 0x00000004 */
#define MPU_PTEN_EN2            MPU_PTEN_EN2_Msk                           /* Enable MPU Channel 2. */

#define MPU_PTEN_EN3_DPos       (3U)
#define MPU_PTEN_EN3_Pos        MPU_PTEN_EN3_DPos
#define MPU_PTEN_EN3_Msk        (0x1UL << MPU_PTEN_EN3_Pos)                /* 0x00000008 */
#define MPU_PTEN_EN3            MPU_PTEN_EN3_Msk                           /* Enable MPU Channel 3. */

#define MPU_PTEN_EN4_DPos       (4U)
#define MPU_PTEN_EN4_Pos        MPU_PTEN_EN4_DPos
#define MPU_PTEN_EN4_Msk        (0x1UL << MPU_PTEN_EN4_Pos)                /* 0x00000010 */
#define MPU_PTEN_EN4            MPU_PTEN_EN4_Msk                           /* Enable MPU Channel 4. */

#define MPU_PTEN_EN5_DPos       (5U)
#define MPU_PTEN_EN5_Pos        MPU_PTEN_EN5_DPos
#define MPU_PTEN_EN5_Msk        (0x1UL << MPU_PTEN_EN5_Pos)                /* 0x00000020 */
#define MPU_PTEN_EN5            MPU_PTEN_EN5_Msk                           /* Enable MPU Channel 5. */

#define MPU_PTEN_EN6_DPos       (6U)
#define MPU_PTEN_EN6_Pos        MPU_PTEN_EN6_DPos
#define MPU_PTEN_EN6_Msk        (0x1UL << MPU_PTEN_EN6_Pos)                /* 0x00000040 */
#define MPU_PTEN_EN6            MPU_PTEN_EN6_Msk                           /* Enable MPU Channel 6. */

#define MPU_PTEN_EN7_DPos       (7U)
#define MPU_PTEN_EN7_Pos        MPU_PTEN_EN7_DPos
#define MPU_PTEN_EN7_Msk        (0x1UL << MPU_PTEN_EN7_Pos)                /* 0x00000080 */
#define MPU_PTEN_EN7            MPU_PTEN_EN7_Msk                           /* Enable MPU Channel 7. */

#define MPU_PTEN_EN8_DPos       (8U)
#define MPU_PTEN_EN8_Pos        MPU_PTEN_EN8_DPos
#define MPU_PTEN_EN8_Msk        (0x1UL << MPU_PTEN_EN8_Pos)                /* 0x00000100 */
#define MPU_PTEN_EN8            MPU_PTEN_EN8_Msk                           /* Enable MPU Channel 8. */

#define MPU_PTEN_EN9_DPos       (9U)
#define MPU_PTEN_EN9_Pos        MPU_PTEN_EN9_DPos
#define MPU_PTEN_EN9_Msk        (0x1UL << MPU_PTEN_EN9_Pos)                /* 0x00000200 */
#define MPU_PTEN_EN9            MPU_PTEN_EN9_Msk                           /* Enable MPU Channel 9. */

#define MPU_PTEN_EN10_DPos      (10U)
#define MPU_PTEN_EN10_Pos       MPU_PTEN_EN10_DPos
#define MPU_PTEN_EN10_Msk       (0x1UL << MPU_PTEN_EN10_Pos)               /* 0x00000400 */
#define MPU_PTEN_EN10           MPU_PTEN_EN10_Msk                          /* Enable MPU Channel 10. */

#define MPU_PTEN_EN11_DPos      (11U)
#define MPU_PTEN_EN11_Pos       MPU_PTEN_EN11_DPos
#define MPU_PTEN_EN11_Msk       (0x1UL << MPU_PTEN_EN11_Pos)               /* 0x00000800 */
#define MPU_PTEN_EN11           MPU_PTEN_EN11_Msk                          /* Enable MPU Channel 11. */

#define MPU_PTEN_EN12_DPos      (12U)
#define MPU_PTEN_EN12_Pos       MPU_PTEN_EN12_DPos
#define MPU_PTEN_EN12_Msk       (0x1UL << MPU_PTEN_EN12_Pos)               /* 0x00001000 */
#define MPU_PTEN_EN12           MPU_PTEN_EN12_Msk                          /* Enable MPU Channel 12. */

#define MPU_PTEN_EN13_DPos      (13U)
#define MPU_PTEN_EN13_Pos       MPU_PTEN_EN13_DPos
#define MPU_PTEN_EN13_Msk       (0x1UL << MPU_PTEN_EN13_Pos)               /* 0x00002000 */
#define MPU_PTEN_EN13           MPU_PTEN_EN13_Msk                          /* Enable MPU Channel 13. */

#define MPU_PTEN_EN14_DPos      (14U)
#define MPU_PTEN_EN14_Pos       MPU_PTEN_EN14_DPos
#define MPU_PTEN_EN14_Msk       (0x1UL << MPU_PTEN_EN14_Pos)               /* 0x00004000 */
#define MPU_PTEN_EN14           MPU_PTEN_EN14_Msk                          /* Enable MPU Channel 14. */

#define MPU_PTEN_EN15_DPos      (15U)
#define MPU_PTEN_EN15_Pos       MPU_PTEN_EN15_DPos
#define MPU_PTEN_EN15_Msk       (0x1UL << MPU_PTEN_EN15_Pos)               /* 0x00008000 */
#define MPU_PTEN_EN15           MPU_PTEN_EN15_Msk                          /* Enable MPU Channel 15. */

/******************  Bit definition for MPU_WPTEN register  *******************/
#define MPU_WPTEN_EN0_DPos       (0U)
#define MPU_WPTEN_EN0_Pos        MPU_WPTEN_EN0_DPos
#define MPU_WPTEN_EN0_Msk        (0x1UL << MPU_WPTEN_EN0_Pos)                /* 0x00000001 */
#define MPU_WPTEN_EN0            MPU_WPTEN_EN0_Msk                           /* Write Protection Enable signal 0. */

#define MPU_WPTEN_EN1_DPos       (1U)
#define MPU_WPTEN_EN1_Pos        MPU_WPTEN_EN1_DPos
#define MPU_WPTEN_EN1_Msk        (0x1UL << MPU_WPTEN_EN1_Pos)                /* 0x00000002 */
#define MPU_WPTEN_EN1            MPU_WPTEN_EN1_Msk                           /* Write Protection Enable signal 1. */

#define MPU_WPTEN_EN2_DPos       (2U)
#define MPU_WPTEN_EN2_Pos        MPU_WPTEN_EN2_DPos
#define MPU_WPTEN_EN2_Msk        (0x1UL << MPU_WPTEN_EN2_Pos)                /* 0x00000004 */
#define MPU_WPTEN_EN2            MPU_WPTEN_EN2_Msk                           /* Write Protection Enable signal 2. */

#define MPU_WPTEN_EN3_DPos       (3U)
#define MPU_WPTEN_EN3_Pos        MPU_WPTEN_EN3_DPos
#define MPU_WPTEN_EN3_Msk        (0x1UL << MPU_WPTEN_EN3_Pos)                /* 0x00000008 */
#define MPU_WPTEN_EN3            MPU_WPTEN_EN3_Msk                           /* Write Protection Enable signal 3. */

#define MPU_WPTEN_EN4_DPos       (4U)
#define MPU_WPTEN_EN4_Pos        MPU_WPTEN_EN4_DPos
#define MPU_WPTEN_EN4_Msk        (0x1UL << MPU_WPTEN_EN4_Pos)                /* 0x00000010 */
#define MPU_WPTEN_EN4            MPU_WPTEN_EN4_Msk                           /* Write Protection Enable signal 4. */

#define MPU_WPTEN_EN5_DPos       (5U)
#define MPU_WPTEN_EN5_Pos        MPU_WPTEN_EN5_DPos
#define MPU_WPTEN_EN5_Msk        (0x1UL << MPU_WPTEN_EN5_Pos)                /* 0x00000020 */
#define MPU_WPTEN_EN5            MPU_WPTEN_EN5_Msk                           /* Write Protection Enable signal 5. */

#define MPU_WPTEN_EN6_DPos       (6U)
#define MPU_WPTEN_EN6_Pos        MPU_WPTEN_EN6_DPos
#define MPU_WPTEN_EN6_Msk        (0x1UL << MPU_WPTEN_EN6_Pos)                /* 0x00000040 */
#define MPU_WPTEN_EN6            MPU_WPTEN_EN6_Msk                           /* Write Protection Enable signal 6. */

#define MPU_WPTEN_EN7_DPos       (7U)
#define MPU_WPTEN_EN7_Pos        MPU_WPTEN_EN7_DPos
#define MPU_WPTEN_EN7_Msk        (0x1UL << MPU_WPTEN_EN7_Pos)                /* 0x00000080 */
#define MPU_WPTEN_EN7            MPU_WPTEN_EN7_Msk                           /* Write Protection Enable signal 7. */

#define MPU_WPTEN_EN8_DPos       (8U)
#define MPU_WPTEN_EN8_Pos        MPU_WPTEN_EN8_DPos
#define MPU_WPTEN_EN8_Msk        (0x1UL << MPU_WPTEN_EN8_Pos)                /* 0x00000100 */
#define MPU_WPTEN_EN8            MPU_WPTEN_EN8_Msk                           /* Write Protection Enable signal 8. */

#define MPU_WPTEN_EN9_DPos       (9U)
#define MPU_WPTEN_EN9_Pos        MPU_WPTEN_EN9_DPos
#define MPU_WPTEN_EN9_Msk        (0x1UL << MPU_WPTEN_EN9_Pos)                /* 0x00000200 */
#define MPU_WPTEN_EN9            MPU_WPTEN_EN9_Msk                           /* Write Protection Enable signal 9. */

#define MPU_WPTEN_EN10_DPos      (10U)
#define MPU_WPTEN_EN10_Pos       MPU_WPTEN_EN10_DPos
#define MPU_WPTEN_EN10_Msk       (0x1UL << MPU_WPTEN_EN10_Pos)               /* 0x00000400 */
#define MPU_WPTEN_EN10           MPU_WPTEN_EN10_Msk                          /* Write Protection Enable signal 10. */

#define MPU_WPTEN_EN11_DPos      (11U)
#define MPU_WPTEN_EN11_Pos       MPU_WPTEN_EN11_DPos
#define MPU_WPTEN_EN11_Msk       (0x1UL << MPU_WPTEN_EN11_Pos)               /* 0x00000800 */
#define MPU_WPTEN_EN11           MPU_WPTEN_EN11_Msk                          /* Write Protection Enable signal 11. */

#define MPU_WPTEN_EN12_DPos      (12U)
#define MPU_WPTEN_EN12_Pos       MPU_WPTEN_EN12_DPos
#define MPU_WPTEN_EN12_Msk       (0x1UL << MPU_WPTEN_EN12_Pos)               /* 0x00001000 */
#define MPU_WPTEN_EN12           MPU_WPTEN_EN12_Msk                          /* Write Protection Enable signal 12. */

#define MPU_WPTEN_EN13_DPos      (13U)
#define MPU_WPTEN_EN13_Pos       MPU_WPTEN_EN13_DPos
#define MPU_WPTEN_EN13_Msk       (0x1UL << MPU_WPTEN_EN13_Pos)               /* 0x00002000 */
#define MPU_WPTEN_EN13           MPU_WPTEN_EN13_Msk                          /* Write Protection Enable signal 13. */

#define MPU_WPTEN_EN14_DPos      (14U)
#define MPU_WPTEN_EN14_Pos       MPU_WPTEN_EN14_DPos
#define MPU_WPTEN_EN14_Msk       (0x1UL << MPU_WPTEN_EN14_Pos)               /* 0x00004000 */
#define MPU_WPTEN_EN14           MPU_WPTEN_EN14_Msk                          /* Write Protection Enable signal 14. */

#define MPU_WPTEN_EN15_DPos      (15U)
#define MPU_WPTEN_EN15_Pos       MPU_WPTEN_EN15_DPos
#define MPU_WPTEN_EN15_Msk       (0x1UL << MPU_WPTEN_EN15_Pos)               /* 0x00008000 */
#define MPU_WPTEN_EN15           MPU_WPTEN_EN15_Msk                          /* Write Protection Enable signal 15. */

/******************  Bit definition for MPU_RPTEN register  *******************/
#define MPU_RPTEN_EN0_DPos       (0U)
#define MPU_RPTEN_EN0_Pos        MPU_RPTEN_EN0_DPos
#define MPU_RPTEN_EN0_Msk        (0x1UL << MPU_RPTEN_EN0_Pos)                /* 0x00000001 */
#define MPU_RPTEN_EN0            MPU_RPTEN_EN0_Msk                           /* Read Protection Enable signal 0. */

#define MPU_RPTEN_EN1_DPos       (1U)
#define MPU_RPTEN_EN1_Pos        MPU_RPTEN_EN1_DPos
#define MPU_RPTEN_EN1_Msk        (0x1UL << MPU_RPTEN_EN1_Pos)                /* 0x00000002 */
#define MPU_RPTEN_EN1            MPU_RPTEN_EN1_Msk                           /* Read Protection Enable signal 1. */

#define MPU_RPTEN_EN2_DPos       (2U)
#define MPU_RPTEN_EN2_Pos        MPU_RPTEN_EN2_DPos
#define MPU_RPTEN_EN2_Msk        (0x1UL << MPU_RPTEN_EN2_Pos)                /* 0x00000004 */
#define MPU_RPTEN_EN2            MPU_RPTEN_EN2_Msk                           /* Read Protection Enable signal 2. */

#define MPU_RPTEN_EN3_DPos       (3U)
#define MPU_RPTEN_EN3_Pos        MPU_RPTEN_EN3_DPos
#define MPU_RPTEN_EN3_Msk        (0x1UL << MPU_RPTEN_EN3_Pos)                /* 0x00000008 */
#define MPU_RPTEN_EN3            MPU_RPTEN_EN3_Msk                           /* Read Protection Enable signal 3. */

#define MPU_RPTEN_EN4_DPos       (4U)
#define MPU_RPTEN_EN4_Pos        MPU_RPTEN_EN4_DPos
#define MPU_RPTEN_EN4_Msk        (0x1UL << MPU_RPTEN_EN4_Pos)                /* 0x00000010 */
#define MPU_RPTEN_EN4            MPU_RPTEN_EN4_Msk                           /* Read Protection Enable signal 4. */

#define MPU_RPTEN_EN5_DPos       (5U)
#define MPU_RPTEN_EN5_Pos        MPU_RPTEN_EN5_DPos
#define MPU_RPTEN_EN5_Msk        (0x1UL << MPU_RPTEN_EN5_Pos)                /* 0x00000020 */
#define MPU_RPTEN_EN5            MPU_RPTEN_EN5_Msk                           /* Read Protection Enable signal 5. */

#define MPU_RPTEN_EN6_DPos       (6U)
#define MPU_RPTEN_EN6_Pos        MPU_RPTEN_EN6_DPos
#define MPU_RPTEN_EN6_Msk        (0x1UL << MPU_RPTEN_EN6_Pos)                /* 0x00000040 */
#define MPU_RPTEN_EN6            MPU_RPTEN_EN6_Msk                           /* Read Protection Enable signal 6. */

#define MPU_RPTEN_EN7_DPos       (7U)
#define MPU_RPTEN_EN7_Pos        MPU_RPTEN_EN7_DPos
#define MPU_RPTEN_EN7_Msk        (0x1UL << MPU_RPTEN_EN7_Pos)                /* 0x00000080 */
#define MPU_RPTEN_EN7            MPU_RPTEN_EN7_Msk                           /* Read Protection Enable signal 7. */

#define MPU_RPTEN_EN8_DPos       (8U)
#define MPU_RPTEN_EN8_Pos        MPU_RPTEN_EN8_DPos
#define MPU_RPTEN_EN8_Msk        (0x1UL << MPU_RPTEN_EN8_Pos)                /* 0x00000100 */
#define MPU_RPTEN_EN8            MPU_RPTEN_EN8_Msk                           /* Read Protection Enable signal 8. */

#define MPU_RPTEN_EN9_DPos       (9U)
#define MPU_RPTEN_EN9_Pos        MPU_RPTEN_EN9_DPos
#define MPU_RPTEN_EN9_Msk        (0x1UL << MPU_RPTEN_EN9_Pos)                /* 0x00000200 */
#define MPU_RPTEN_EN9            MPU_RPTEN_EN9_Msk                           /* Read Protection Enable signal 9. */

#define MPU_RPTEN_EN10_DPos      (10U)
#define MPU_RPTEN_EN10_Pos       MPU_RPTEN_EN10_DPos
#define MPU_RPTEN_EN10_Msk       (0x1UL << MPU_RPTEN_EN10_Pos)               /* 0x00000400 */
#define MPU_RPTEN_EN10           MPU_RPTEN_EN10_Msk                          /* Read Protection Enable signal 10. */

#define MPU_RPTEN_EN11_DPos      (11U)
#define MPU_RPTEN_EN11_Pos       MPU_RPTEN_EN11_DPos
#define MPU_RPTEN_EN11_Msk       (0x1UL << MPU_RPTEN_EN11_Pos)               /* 0x00000800 */
#define MPU_RPTEN_EN11           MPU_RPTEN_EN11_Msk                          /* Read Protection Enable signal 11. */

#define MPU_RPTEN_EN12_DPos      (12U)
#define MPU_RPTEN_EN12_Pos       MPU_RPTEN_EN12_DPos
#define MPU_RPTEN_EN12_Msk       (0x1UL << MPU_RPTEN_EN12_Pos)               /* 0x00001000 */
#define MPU_RPTEN_EN12           MPU_RPTEN_EN12_Msk                          /* Read Protection Enable signal 12. */

#define MPU_RPTEN_EN13_DPos      (13U)
#define MPU_RPTEN_EN13_Pos       MPU_RPTEN_EN13_DPos
#define MPU_RPTEN_EN13_Msk       (0x1UL << MPU_RPTEN_EN13_Pos)               /* 0x00002000 */
#define MPU_RPTEN_EN13           MPU_RPTEN_EN13_Msk                          /* Read Protection Enable signal 13. */

#define MPU_RPTEN_EN14_DPos      (14U)
#define MPU_RPTEN_EN14_Pos       MPU_RPTEN_EN14_DPos
#define MPU_RPTEN_EN14_Msk       (0x1UL << MPU_RPTEN_EN14_Pos)               /* 0x00004000 */
#define MPU_RPTEN_EN14           MPU_RPTEN_EN14_Msk                          /* Read Protection Enable signal 14. */

#define MPU_RPTEN_EN15_DPos      (15U)
#define MPU_RPTEN_EN15_Pos       MPU_RPTEN_EN15_DPos
#define MPU_RPTEN_EN15_Msk       (0x1UL << MPU_RPTEN_EN15_Pos)               /* 0x00008000 */
#define MPU_RPTEN_EN15           MPU_RPTEN_EN15_Msk                          /* Read Protection Enable signal 15. */

/******************  Bit definition for MPU_WPTS register  *******************/
#define MPU_WPTS_STA0_DPos       (0U)
#define MPU_WPTS_STA0_Pos        MPU_WPTS_STA0_DPos
#define MPU_WPTS_STA0_Msk        (0x1UL << MPU_WPTS_STA0_Pos)                /* 0x00000001 */
#define MPU_WPTS_STA0            MPU_WPTS_STA0_Msk                           /* Write Protection Status 0. */

#define MPU_WPTS_STA1_DPos       (1U)
#define MPU_WPTS_STA1_Pos        MPU_WPTS_STA1_DPos
#define MPU_WPTS_STA1_Msk        (0x1UL << MPU_WPTS_STA1_Pos)                /* 0x00000002 */
#define MPU_WPTS_STA1            MPU_WPTS_STA1_Msk                           /* Write Protection Status 1. */

#define MPU_WPTS_STA2_DPos       (2U)
#define MPU_WPTS_STA2_Pos        MPU_WPTS_STA2_DPos
#define MPU_WPTS_STA2_Msk        (0x1UL << MPU_WPTS_STA2_Pos)                /* 0x00000004 */
#define MPU_WPTS_STA2            MPU_WPTS_STA2_Msk                           /* Write Protection Status 2. */

#define MPU_WPTS_STA3_DPos       (3U)
#define MPU_WPTS_STA3_Pos        MPU_WPTS_STA3_DPos
#define MPU_WPTS_STA3_Msk        (0x1UL << MPU_WPTS_STA3_Pos)                /* 0x00000008 */
#define MPU_WPTS_STA3            MPU_WPTS_STA3_Msk                           /* Write Protection Status 3. */

#define MPU_WPTS_STA4_DPos       (4U)
#define MPU_WPTS_STA4_Pos        MPU_WPTS_STA4_DPos
#define MPU_WPTS_STA4_Msk        (0x1UL << MPU_WPTS_STA4_Pos)                /* 0x00000010 */
#define MPU_WPTS_STA4            MPU_WPTS_STA4_Msk                           /* Write Protection Status 4. */

#define MPU_WPTS_STA5_DPos       (5U)
#define MPU_WPTS_STA5_Pos        MPU_WPTS_STA5_DPos
#define MPU_WPTS_STA5_Msk        (0x1UL << MPU_WPTS_STA5_Pos)                /* 0x00000020 */
#define MPU_WPTS_STA5            MPU_WPTS_STA5_Msk                           /* Write Protection Status 5. */

#define MPU_WPTS_STA6_DPos       (6U)
#define MPU_WPTS_STA6_Pos        MPU_WPTS_STA6_DPos
#define MPU_WPTS_STA6_Msk        (0x1UL << MPU_WPTS_STA6_Pos)                /* 0x00000040 */
#define MPU_WPTS_STA6            MPU_WPTS_STA6_Msk                           /* Write Protection Status 6. */

#define MPU_WPTS_STA7_DPos       (7U)
#define MPU_WPTS_STA7_Pos        MPU_WPTS_STA7_DPos
#define MPU_WPTS_STA7_Msk        (0x1UL << MPU_WPTS_STA7_Pos)                /* 0x00000080 */
#define MPU_WPTS_STA7            MPU_WPTS_STA7_Msk                           /* Write Protection Status 7. */

#define MPU_WPTS_STA8_DPos       (8U)
#define MPU_WPTS_STA8_Pos        MPU_WPTS_STA8_DPos
#define MPU_WPTS_STA8_Msk        (0x1UL << MPU_WPTS_STA8_Pos)                /* 0x00000100 */
#define MPU_WPTS_STA8            MPU_WPTS_STA8_Msk                           /* Write Protection Status 8. */

#define MPU_WPTS_STA9_DPos       (9U)
#define MPU_WPTS_STA9_Pos        MPU_WPTS_STA9_DPos
#define MPU_WPTS_STA9_Msk        (0x1UL << MPU_WPTS_STA9_Pos)                /* 0x00000200 */
#define MPU_WPTS_STA9            MPU_WPTS_STA9_Msk                           /* Write Protection Status 9. */

#define MPU_WPTS_STA10_DPos      (10U)
#define MPU_WPTS_STA10_Pos       MPU_WPTS_STA10_DPos
#define MPU_WPTS_STA10_Msk       (0x1UL << MPU_WPTS_STA10_Pos)               /* 0x00000400 */
#define MPU_WPTS_STA10           MPU_WPTS_STA10_Msk                          /* Write Protection Status 10. */

#define MPU_WPTS_STA11_DPos      (11U)
#define MPU_WPTS_STA11_Pos       MPU_WPTS_STA11_DPos
#define MPU_WPTS_STA11_Msk       (0x1UL << MPU_WPTS_STA11_Pos)               /* 0x00000800 */
#define MPU_WPTS_STA11           MPU_WPTS_STA11_Msk                          /* Write Protection Status 11. */

#define MPU_WPTS_STA12_DPos      (12U)
#define MPU_WPTS_STA12_Pos       MPU_WPTS_STA12_DPos
#define MPU_WPTS_STA12_Msk       (0x1UL << MPU_WPTS_STA12_Pos)               /* 0x00001000 */
#define MPU_WPTS_STA12           MPU_WPTS_STA12_Msk                          /* Write Protection Status 12. */

#define MPU_WPTS_STA13_DPos      (13U)
#define MPU_WPTS_STA13_Pos       MPU_WPTS_STA13_DPos
#define MPU_WPTS_STA13_Msk       (0x1UL << MPU_WPTS_STA13_Pos)               /* 0x00002000 */
#define MPU_WPTS_STA13           MPU_WPTS_STA13_Msk                          /* Write Protection Status 13. */

#define MPU_WPTS_STA14_DPos      (14U)
#define MPU_WPTS_STA14_Pos       MPU_WPTS_STA14_DPos
#define MPU_WPTS_STA14_Msk       (0x1UL << MPU_WPTS_STA14_Pos)               /* 0x00004000 */
#define MPU_WPTS_STA14           MPU_WPTS_STA14_Msk                          /* Write Protection Status 14. */

#define MPU_WPTS_STA15_DPos      (15U)
#define MPU_WPTS_STA15_Pos       MPU_WPTS_STA15_DPos
#define MPU_WPTS_STA15_Msk       (0x1UL << MPU_WPTS_STA15_Pos)               /* 0x00008000 */
#define MPU_WPTS_STA15           MPU_WPTS_STA15_Msk                          /* Write Protection Status 15. */

/******************  Bit definition for MPU_RPTS register  *******************/
#define MPU_RPTS_STA0_DPos       (0U)
#define MPU_RPTS_STA0_Pos        MPU_RPTS_STA0_DPos
#define MPU_RPTS_STA0_Msk        (0x1UL << MPU_RPTS_STA0_Pos)                /* 0x00000001 */
#define MPU_RPTS_STA0            MPU_RPTS_STA0_Msk                           /* Read Protection Status 0. */

#define MPU_RPTS_STA1_DPos       (1U)
#define MPU_RPTS_STA1_Pos        MPU_RPTS_STA1_DPos
#define MPU_RPTS_STA1_Msk        (0x1UL << MPU_RPTS_STA1_Pos)                /* 0x00000002 */
#define MPU_RPTS_STA1            MPU_RPTS_STA1_Msk                           /* Read Protection Status 1. */

#define MPU_RPTS_STA2_DPos       (2U)
#define MPU_RPTS_STA2_Pos        MPU_RPTS_STA2_DPos
#define MPU_RPTS_STA2_Msk        (0x1UL << MPU_RPTS_STA2_Pos)                /* 0x00000004 */
#define MPU_RPTS_STA2            MPU_RPTS_STA2_Msk                           /* Read Protection Status 2. */

#define MPU_RPTS_STA3_DPos       (3U)
#define MPU_RPTS_STA3_Pos        MPU_RPTS_STA3_DPos
#define MPU_RPTS_STA3_Msk        (0x1UL << MPU_RPTS_STA3_Pos)                /* 0x00000008 */
#define MPU_RPTS_STA3            MPU_RPTS_STA3_Msk                           /* Read Protection Status 3. */

#define MPU_RPTS_STA4_DPos       (4U)
#define MPU_RPTS_STA4_Pos        MPU_RPTS_STA4_DPos
#define MPU_RPTS_STA4_Msk        (0x1UL << MPU_RPTS_STA4_Pos)                /* 0x00000010 */
#define MPU_RPTS_STA4            MPU_RPTS_STA4_Msk                           /* Read Protection Status 4. */

#define MPU_RPTS_STA5_DPos       (5U)
#define MPU_RPTS_STA5_Pos        MPU_RPTS_STA5_DPos
#define MPU_RPTS_STA5_Msk        (0x1UL << MPU_RPTS_STA5_Pos)                /* 0x00000020 */
#define MPU_RPTS_STA5            MPU_RPTS_STA5_Msk                           /* Read Protection Status 5. */

#define MPU_RPTS_STA6_DPos       (6U)
#define MPU_RPTS_STA6_Pos        MPU_RPTS_STA6_DPos
#define MPU_RPTS_STA6_Msk        (0x1UL << MPU_RPTS_STA6_Pos)                /* 0x00000040 */
#define MPU_RPTS_STA6            MPU_RPTS_STA6_Msk                           /* Read Protection Status 6. */

#define MPU_RPTS_STA7_DPos       (7U)
#define MPU_RPTS_STA7_Pos        MPU_RPTS_STA7_DPos
#define MPU_RPTS_STA7_Msk        (0x1UL << MPU_RPTS_STA7_Pos)                /* 0x00000080 */
#define MPU_RPTS_STA7            MPU_RPTS_STA7_Msk                           /* Read Protection Status 7. */

#define MPU_RPTS_STA8_DPos       (8U)
#define MPU_RPTS_STA8_Pos        MPU_RPTS_STA8_DPos
#define MPU_RPTS_STA8_Msk        (0x1UL << MPU_RPTS_STA8_Pos)                /* 0x00000100 */
#define MPU_RPTS_STA8            MPU_RPTS_STA8_Msk                           /* Read Protection Status 8. */

#define MPU_RPTS_STA9_DPos       (9U)
#define MPU_RPTS_STA9_Pos        MPU_RPTS_STA9_DPos
#define MPU_RPTS_STA9_Msk        (0x1UL << MPU_RPTS_STA9_Pos)                /* 0x00000200 */
#define MPU_RPTS_STA9            MPU_RPTS_STA9_Msk                           /* Read Protection Status 9. */

#define MPU_RPTS_STA10_DPos      (10U)
#define MPU_RPTS_STA10_Pos       MPU_RPTS_STA10_DPos
#define MPU_RPTS_STA10_Msk       (0x1UL << MPU_RPTS_STA10_Pos)               /* 0x00000400 */
#define MPU_RPTS_STA10           MPU_RPTS_STA10_Msk                          /* Read Protection Status 10. */

#define MPU_RPTS_STA11_DPos      (11U)
#define MPU_RPTS_STA11_Pos       MPU_RPTS_STA11_DPos
#define MPU_RPTS_STA11_Msk       (0x1UL << MPU_RPTS_STA11_Pos)               /* 0x00000800 */
#define MPU_RPTS_STA11           MPU_RPTS_STA11_Msk                          /* Read Protection Status 11. */

#define MPU_RPTS_STA12_DPos      (12U)
#define MPU_RPTS_STA12_Pos       MPU_RPTS_STA12_DPos
#define MPU_RPTS_STA12_Msk       (0x1UL << MPU_RPTS_STA12_Pos)               /* 0x00001000 */
#define MPU_RPTS_STA12           MPU_RPTS_STA12_Msk                          /* Read Protection Status 12. */

#define MPU_RPTS_STA13_DPos      (13U)
#define MPU_RPTS_STA13_Pos       MPU_RPTS_STA13_DPos
#define MPU_RPTS_STA13_Msk       (0x1UL << MPU_RPTS_STA13_Pos)               /* 0x00002000 */
#define MPU_RPTS_STA13           MPU_RPTS_STA13_Msk                          /* Read Protection Status 13. */

#define MPU_RPTS_STA14_DPos      (14U)
#define MPU_RPTS_STA14_Pos       MPU_RPTS_STA14_DPos
#define MPU_RPTS_STA14_Msk       (0x1UL << MPU_RPTS_STA14_Pos)               /* 0x00004000 */
#define MPU_RPTS_STA14           MPU_RPTS_STA14_Msk                          /* Read Protection Status 14. */

#define MPU_RPTS_STA15_DPos      (15U)
#define MPU_RPTS_STA15_Pos       MPU_RPTS_STA15_DPos
#define MPU_RPTS_STA15_Msk       (0x1UL << MPU_RPTS_STA15_Pos)               /* 0x00008000 */
#define MPU_RPTS_STA15           MPU_RPTS_STA15_Msk                          /* Read Protection Status 15. */

/******************  Bit definition for MPU_SADDR0 register  *******************/
#define MPU_SADDR0_ADDR_DPos      (0)
#define MPU_SADDR0_ADDR_Pos       MPU_SADDR0_ADDR_DPos
#define MPU_SADDR0_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR0_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR0_ADDR           MPU_SADDR0_ADDR_Msk                          /* Start address 0. */

/******************  Bit definition for MPU_EADDR0 register  *******************/
#define MPU_EADDR0_ADDR_DPos      (0)
#define MPU_EADDR0_ADDR_Pos       MPU_EADDR0_ADDR_DPos
#define MPU_EADDR0_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR0_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR0_ADDR           MPU_EADDR0_ADDR_Msk                          /* End address 0. */


/******************  Bit definition for MPU_SADDR1 register  *******************/
#define MPU_SADDR1_ADDR_DPos      (0)
#define MPU_SADDR1_ADDR_Pos       MPU_SADDR1_ADDR_DPos
#define MPU_SADDR1_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR1_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR1_ADDR           MPU_SADDR1_ADDR_Msk                          /* Start address 1. */

/******************  Bit definition for MPU_EADDR1 register  *******************/
#define MPU_EADDR1_ADDR_DPos      (0)
#define MPU_EADDR1_ADDR_Pos       MPU_EADDR1_ADDR_DPos
#define MPU_EADDR1_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR1_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR1_ADDR           MPU_EADDR1_ADDR_Msk                          /* End address 1. */

/******************  Bit definition for MPU_SADDR2 register  *******************/
#define MPU_SADDR2_ADDR_DPos      (0)
#define MPU_SADDR2_ADDR_Pos       MPU_SADDR2_ADDR_DPos
#define MPU_SADDR2_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR2_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR2_ADDR           MPU_SADDR2_ADDR_Msk                          /* Start address 2. */

/******************  Bit definition for MPU_EADDR2 register  *******************/
#define MPU_EADDR2_ADDR_DPos      (0)
#define MPU_EADDR2_ADDR_Pos       MPU_EADDR2_ADDR_DPos
#define MPU_EADDR2_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR2_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR2_ADDR           MPU_EADDR2_ADDR_Msk                          /* End address 2. */


/******************  Bit definition for MPU_SADDR3 register  *******************/
#define MPU_SADDR3_ADDR_DPos      (0)
#define MPU_SADDR3_ADDR_Pos       MPU_SADDR3_ADDR_DPos
#define MPU_SADDR3_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR3_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR3_ADDR           MPU_SADDR3_ADDR_Msk                          /* Start address 3. */

/******************  Bit definition for MPU_EADDR3 register  *******************/
#define MPU_EADDR3_ADDR_DPos      (0)
#define MPU_EADDR3_ADDR_Pos       MPU_EADDR3_ADDR_DPos
#define MPU_EADDR3_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR3_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR3_ADDR           MPU_EADDR3_ADDR_Msk                          /* End address 3. */


/******************  Bit definition for MPU_SADDR4 register  *******************/
#define MPU_SADDR4_ADDR_DPos      (0)
#define MPU_SADDR4_ADDR_Pos       MPU_SADDR4_ADDR_DPos
#define MPU_SADDR4_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR4_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR4_ADDR           MPU_SADDR4_ADDR_Msk                          /* Start address 4. */

/******************  Bit definition for MPU_EADDR4 register  *******************/
#define MPU_EADDR4_ADDR_DPos      (0)
#define MPU_EADDR4_ADDR_Pos       MPU_EADDR4_ADDR_DPos
#define MPU_EADDR4_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR4_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR4_ADDR           MPU_EADDR4_ADDR_Msk                          /* End address 4. */


/******************  Bit definition for MPU_SADDR5 register  *******************/
#define MPU_SADDR5_ADDR_DPos      (0)
#define MPU_SADDR5_ADDR_Pos       MPU_SADDR5_ADDR_DPos
#define MPU_SADDR5_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR5_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR5_ADDR           MPU_SADDR5_ADDR_Msk                          /* Start address 5. */

/******************  Bit definition for MPU_EADDR5 register  *******************/
#define MPU_EADDR5_ADDR_DPos      (0)
#define MPU_EADDR5_ADDR_Pos       MPU_EADDR5_ADDR_DPos
#define MPU_EADDR5_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR5_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR5_ADDR           MPU_EADDR5_ADDR_Msk                          /* End address 5. */


/******************  Bit definition for MPU_SADDR6 register  *******************/
#define MPU_SADDR6_ADDR_DPos      (0)
#define MPU_SADDR6_ADDR_Pos       MPU_SADDR6_ADDR_DPos
#define MPU_SADDR6_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR6_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR6_ADDR           MPU_SADDR6_ADDR_Msk                          /* Start address 6. */

/******************  Bit definition for MPU_EADDR6 register  *******************/
#define MPU_EADDR6_ADDR_DPos      (0)
#define MPU_EADDR6_ADDR_Pos       MPU_EADDR6_ADDR_DPos
#define MPU_EADDR6_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR6_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR6_ADDR           MPU_EADDR6_ADDR_Msk                          /* End address 6. */


/******************  Bit definition for MPU_SADDR7 register  *******************/
#define MPU_SADDR7_ADDR_DPos      (0)
#define MPU_SADDR7_ADDR_Pos       MPU_SADDR7_ADDR_DPos
#define MPU_SADDR7_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR7_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR7_ADDR           MPU_SADDR7_ADDR_Msk                          /* Start address 7. */

/******************  Bit definition for MPU_EADDR7 register  *******************/
#define MPU_EADDR7_ADDR_DPos      (0)
#define MPU_EADDR7_ADDR_Pos       MPU_EADDR7_ADDR_DPos
#define MPU_EADDR7_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR7_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR7_ADDR           MPU_EADDR7_ADDR_Msk                          /* End address 7. */


/******************  Bit definition for MPU_SADDR8 register  *******************/
#define MPU_SADDR8_ADDR_DPos      (0)
#define MPU_SADDR8_ADDR_Pos       MPU_SADDR8_ADDR_DPos
#define MPU_SADDR8_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR8_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR8_ADDR           MPU_SADDR8_ADDR_Msk                          /* Start address 8. */

/******************  Bit definition for MPU_EADDR8 register  *******************/
#define MPU_EADDR8_ADDR_DPos      (0)
#define MPU_EADDR8_ADDR_Pos       MPU_EADDR8_ADDR_DPos
#define MPU_EADDR8_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR8_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR8_ADDR           MPU_EADDR8_ADDR_Msk                          /* End address 8. */


/******************  Bit definition for MPU_SADDR9 register  *******************/
#define MPU_SADDR9_ADDR_DPos      (0)
#define MPU_SADDR9_ADDR_Pos       MPU_SADDR9_ADDR_DPos
#define MPU_SADDR9_ADDR_Msk       (0xFFFFFFFFUL << MPU_SADDR9_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_SADDR9_ADDR           MPU_SADDR9_ADDR_Msk                          /* Start address 9. */

/******************  Bit definition for MPU_EADDR9 register  *******************/
#define MPU_EADDR9_ADDR_DPos      (0)
#define MPU_EADDR9_ADDR_Pos       MPU_EADDR9_ADDR_DPos
#define MPU_EADDR9_ADDR_Msk       (0xFFFFFFFFUL << MPU_EADDR9_ADDR_Pos)        /* 0xFFFFFFFF */
#define MPU_EADDR9_ADDR           MPU_EADDR9_ADDR_Msk                          /* End address 9. */


/******************  Bit definition for MPU_SADDR10 register  *******************/
#define MPU_SADDR10_ADDR_DPos     (0)
#define MPU_SADDR10_ADDR_Pos      MPU_SADDR10_ADDR_DPos
#define MPU_SADDR10_ADDR_Msk      (0xFFFFFFFFUL << MPU_SADDR10_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_SADDR10_ADDR          MPU_SADDR10_ADDR_Msk                         /* Start address 10. */

/******************  Bit definition for MPU_EADDR10 register  *******************/
#define MPU_EADDR10_ADDR_DPos     (0)
#define MPU_EADDR10_ADDR_Pos      MPU_EADDR10_ADDR_DPos
#define MPU_EADDR10_ADDR_Msk      (0xFFFFFFFFUL << MPU_EADDR10_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_EADDR10_ADDR          MPU_EADDR10_ADDR_Msk                         /* End address 10. */


/******************  Bit definition for MPU_SADDR11 register  *******************/
#define MPU_SADDR11_ADDR_DPos     (0)
#define MPU_SADDR11_ADDR_Pos      MPU_SADDR11_ADDR_DPos
#define MPU_SADDR11_ADDR_Msk      (0xFFFFFFFFUL << MPU_SADDR11_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_SADDR11_ADDR          MPU_SADDR11_ADDR_Msk                         /* Start address 11. */

/******************  Bit definition for MPU_EADDR11 register  *******************/
#define MPU_EADDR11_ADDR_DPos     (0)
#define MPU_EADDR11_ADDR_Pos      MPU_EADDR11_ADDR_DPos
#define MPU_EADDR11_ADDR_Msk      (0xFFFFFFFFUL << MPU_EADDR11_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_EADDR11_ADDR          MPU_EADDR11_ADDR_Msk                         /* End address 11. */


/******************  Bit definition for MPU_SADDR12 register  *******************/
#define MPU_SADDR12_ADDR_DPos     (0)
#define MPU_SADDR12_ADDR_Pos      MPU_SADDR12_ADDR_DPos
#define MPU_SADDR12_ADDR_Msk      (0xFFFFFFFFUL << MPU_SADDR12_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_SADDR12_ADDR          MPU_SADDR12_ADDR_Msk                         /* Start address 12. */

/******************  Bit definition for MPU_EADDR12 register  *******************/
#define MPU_EADDR12_ADDR_DPos     (0)
#define MPU_EADDR12_ADDR_Pos      MPU_EADDR12_ADDR_DPos
#define MPU_EADDR12_ADDR_Msk      (0xFFFFFFFFUL << MPU_EADDR12_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_EADDR12_ADDR          MPU_EADDR12_ADDR_Msk                         /* End address 12. */


/******************  Bit definition for MPU_SADDR13 register  *******************/
#define MPU_SADDR13_ADDR_DPos     (0)
#define MPU_SADDR13_ADDR_Pos      MPU_SADDR13_ADDR_DPos
#define MPU_SADDR13_ADDR_Msk      (0xFFFFFFFFUL << MPU_SADDR13_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_SADDR13_ADDR          MPU_SADDR13_ADDR_Msk                         /* Start address 13. */

/******************  Bit definition for MPU_EADDR13 register  *******************/
#define MPU_EADDR13_ADDR_DPos     (0)
#define MPU_EADDR13_ADDR_Pos      MPU_EADDR13_ADDR_DPos
#define MPU_EADDR13_ADDR_Msk      (0xFFFFFFFFUL << MPU_EADDR13_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_EADDR13_ADDR          MPU_EADDR13_ADDR_Msk                         /* End address 13. */


/******************  Bit definition for MPU_SADDR14 register  *******************/
#define MPU_SADDR14_ADDR_DPos     (0)
#define MPU_SADDR14_ADDR_Pos      MPU_SADDR14_ADDR_DPos
#define MPU_SADDR14_ADDR_Msk      (0xFFFFFFFFUL << MPU_SADDR14_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_SADDR14_ADDR          MPU_SADDR14_ADDR_Msk                         /* Start address 14. */

/******************  Bit definition for MPU_EADDR14 register  *******************/
#define MPU_EADDR14_ADDR_DPos     (0)
#define MPU_EADDR14_ADDR_Pos      MPU_EADDR14_ADDR_DPos
#define MPU_EADDR14_ADDR_Msk      (0xFFFFFFFFUL << MPU_EADDR14_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_EADDR14_ADDR          MPU_EADDR14_ADDR_Msk                         /* End address 14. */


/******************  Bit definition for MPU_SADDR15 register  *******************/
#define MPU_SADDR15_ADDR_DPos     (0)
#define MPU_SADDR15_ADDR_Pos      MPU_SADDR15_ADDR_DPos
#define MPU_SADDR15_ADDR_Msk      (0xFFFFFFFFUL << MPU_SADDR15_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_SADDR15_ADDR          MPU_SADDR15_ADDR_Msk                         /* Start address 15. */

/******************  Bit definition for MPU_EADDR15 register  *******************/
#define MPU_EADDR15_ADDR_DPos     (0)
#define MPU_EADDR15_ADDR_Pos      MPU_EADDR15_ADDR_DPos
#define MPU_EADDR15_ADDR_Msk      (0xFFFFFFFFUL << MPU_EADDR15_ADDR_Pos)       /* 0xFFFFFFFF */
#define MPU_EADDR15_ADDR          MPU_EADDR15_ADDR_Msk                         /* End address 15. */



#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
