/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_crc_regs.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:            2024/09/06
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/09/06     1.0     build this module
 * Description:     This file contains all the register correlation defines for the CRC firmware library.
 */

#ifndef AS32X601_CRC_REG_H
#define AS32X601_CRC_REG_H

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
    __IO uint32_t DR;           /* CRC_DR       CRC data register,                      Address offset: 0x00 */
    __IO uint32_t IDR;          /* CRC_IDR      CRC independent data register,          Address offset: 0x04 */
    __IO uint32_t CR;           /* CRC_CR       CRC control register,                   Address offset: 0x08 */
    __IO uint32_t INIT;         /* CRC_INIT     CRC initial vector register,            Address offset: 0x0C */
    __O  uint32_t POLY;         /* CRC_POLY     CRC generates polynomial registers,     Address offset: 0x10 */
    __O  uint32_t XOR;          /* CRC_XOR      CRC XOR polynomial register,            Address offset: 0x14 */
} CRC_TypeDef;

/*
 * @brief CRC peripheral declaration
 */
#define CRC     ((CRC_TypeDef *)CRC_BASE)

/******************  Bits definition for CRC_DR register  *****************/
#define CRC_DR_DATA_DPos            (0U)
#define CRC_DR_DATA_Pos             CRC_DR_DATA_DPos
#define CRC_DR_DATA_Msk             (0xFFFFFFFFUL << CRC_DR_DATA_Pos)           /* 0xFFFFFFFF */
#define CRC_DR_DATA                 CRC_DR_DATA_Msk                             /* DATA[31:0] bits (CRC calculated result bit) */

/******************  Bits definition for CRC_IDR register  *****************/
#define CRC_IDR_IDATA_DPos          (0U)
#define CRC_IDR_IDATA_Pos           CRC_IDR_IDATA_DPos
#define CRC_IDR_IDATA_Msk           (0xFFUL << CRC_IDR_IDATA_Pos)               /* 0x000000FF */
#define CRC_IDR_IDATA               CRC_IDR_IDATA_Msk                           /* IDATA[7:0] bits (Universal 8-bit data register bit) */

/******************  Bits definition for CRC_CR register  *****************/
#define CRC_CR_RESET_DPos           (0U)
#define CRC_CR_RESET_Pos            CRC_CR_RESET_DPos
#define CRC_CR_RESET_Msk            (0x1UL << CRC_CR_RESET_Pos)                 /* 0x00000001 */
#define CRC_CR_RESET                CRC_CR_RESET_Msk                            /* Reset CRC */

#define CRC_CR_POLYSIZE_DPos        (3U)
#define CRC_CR_POLYSIZE_Pos         CRC_CR_POLYSIZE_DPos
#define CRC_CR_POLYSIZE_Msk         (0x3UL << CRC_CR_POLYSIZE_Pos)              /* 0x00000018 */
#define CRC_CR_POLYSIZE             CRC_CR_POLYSIZE_Msk                         /* POLYSIZE[1:0] bits (Polynomial size) */
#define CRC_CR_POLYSIZE_0           (0x01UL << CRC_CR_POLYSIZE_Pos)             /* 0x00000008 */
#define CRC_CR_POLYSIZE_1           (0x02UL << CRC_CR_POLYSIZE_Pos)             /* 0x00000010 */

#define CRC_CR_REV_IN_DPos          (5U)
#define CRC_CR_REVIN_Pos            CRC_CR_REV_IN_DPos
#define CRC_CR_REVIN_Msk            (0x3UL << CRC_CR_REVIN_Pos)                 /* 0x00000060 */
#define CRC_CR_REVIN                CRC_CR_REVIN_Msk                            /* REVIN[1:0] bits (Reverse input data) */
#define CRC_CR_REVIN_0              (0x01UL << CRC_CR_REVIN_Pos)                /* 0x00000020 */
#define CRC_CR_REVIN_1              (0x02UL << CRC_CR_REVIN_Pos)                /* 0x00000040 */

#define CRC_CR_REV_OUT_DPos         (7U)
#define CRC_CR_REVOUT_Pos           CRC_CR_REV_OUT_DPos
#define CRC_CR_REVOUT_Msk           (0x1UL << CRC_CR_REVOUT_Pos)                /* 0x00000080 */
#define CRC_CR_REVOUT               CRC_CR_REVOUT_Msk                           /* Reverse output data */

#define CRC_CR_XOR_OUT_DPos         (8U)
#define CRC_CR_XOROUT_Pos           CRC_CR_XOR_OUT_DPos
#define CRC_CR_XOROUT_Msk           (0x1UL << CRC_CR_XOROUT_Pos)                /* 0x00000100 */
#define CRC_CR_XOROUT               CRC_CR_XOROUT_Msk                           /* Output data XOR */

#define CRC_CR_SIZE_DPos            (16U)
#define CRC_CR_SIZE_Pos             CRC_CR_SIZE_DPos
#define CRC_CR_SIZE_Msk             (0x3UL << CRC_CR_SIZE_Pos)                  /* 0x00030000 */
#define CRC_CR_SIZE                 CRC_CR_SIZE_Msk                             /* SIZE[1:0] bits (Calculate the size of the data) */
#define CRC_CR_SIZE_0               (0x01UL << CRC_CR_SIZE_Pos)                 /* 0x00010000 */
#define CRC_CR_SIZE_1               (0x02UL << CRC_CR_SIZE_Pos)                 /* 0x00020000 */

/******************  Bits definition for CRC_INIT register  *****************/
#define CRC_INIT_INIT_DPos          (0U)
#define CRC_INIT_INIT_Pos           CRC_INIT_INIT_DPos
#define CRC_INIT_INIT_Msk           (0xFFFFFFFFUL << CRC_INIT_INIT_Pos)         /* 0xFFFFFFFF */
#define CRC_INIT_INIT               CRC_INIT_INIT_Msk                           /* INIT[31:0] bits (Initial vector register) */

/******************  Bits definition for CRC_POLY register  *****************/
#define CRC_POLY_POLY_DPos          (0U)
#define CRC_POLY_POLY_Pos           CRC_POLY_POLY_DPos
#define CRC_POLY_POLY_Msk           (0xFFFFFFFFUL << CRC_POLY_POLY_Pos)         /* 0xFFFFFFFF */
#define CRC_POLY_POLY               CRC_POLY_POLY_Msk                           /* POLY[31:0] bits (Generating polynomial register) */

/******************  Bits definition for CRC_XOR register  *****************/
#define CRC_XOR_XOR_DPos            (0U)
#define CRC_XOR_XOR_Pos             CRC_XOR_XOR_DPos
#define CRC_XOR_XOR_Msk             (0xFFFFFFFFUL << CRC_XOR_XOR_Pos)           /* 0xFFFFFFFF */
#define CRC_XOR_XOR                 CRC_XOR_XOR_Msk                             /* XOR[31:0] bits (XOR register) */


#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
