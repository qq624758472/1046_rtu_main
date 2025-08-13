/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):    Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	 as32x601_crc.h
 * Author:           ANSILIC APPLICATION GROUP
 * Version:          V1.0
 * Date:             2024/09/09
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/09/09     1.0     build this module
 * Description:     This file contains all the functions prototypes for the CRC firmware library.
 */

#ifndef AS32X601_CRC_H
#define AS32X601_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_crc_regs.h"

/*
 * @brief CRC calculates data size enumeration
 */
typedef enum 
{
    CRC_Size_8b  = 0x00,    /* Calculate data size of 8-bit */
    CRC_Size_16b = 0x01,    /* Calculate data size of 16-bit */
    CRC_Size_32b = 0x02     /* Calculate data size of 32-bit */
} CRCSize_TypeDef;
#define IS_CRC_SIZE(SIZE) (((SIZE) == CRC_Size_8b) || ((SIZE) == CRC_Size_16b) || \
                           ((SIZE) == CRC_Size_32b))

/*
 * @brief CRC reverse input data enumeration
 */
typedef enum 
{
    CRC_IReverse_NOT  = 0x00,   /* Does not affect the bit order */
    CRC_IReverse_BYTE = 0x01,   /* Perform bit reversal by byte */
    CRC_IReverse_HALF = 0x02,   /* Perform bit reversal by half character */
    CRC_IReverse_WORD = 0x03    /* Perform bit reversal by word */
} CRCIReverse_TypeDef;
#define IS_CRC_IREVERSE(IREVERSE) (((IREVERSE) == CRC_IReverse_NOT)  || ((IREVERSE) == CRC_IReverse_BYTE) || \
                                   ((IREVERSE) == CRC_IReverse_HALF) || ((IREVERSE) == CRC_IReverse_WORD))

/*
 * @brief CRC polynomial size enumeration
 */
typedef enum 
{
    CRC_POLYSIZE_32b = 0x00,    /* 32-bit polynomial */
    CRC_POLYSIZE_16b = 0x01,    /* 16-bit polynomial */
    CRC_POLYSIZE_8b  = 0x02,    /* 8-bit polynomial */
    CRC_POLYSIZE_7b  = 0x03     /* 7-bit polynomial */
} CRCPOLYSIZE_TypeDef;
#define IS_CRC_POLYSIZE(POLYSIZE) (((POLYSIZE) == CRC_POLYSIZE_32b) || ((POLYSIZE) == CRC_POLYSIZE_16b) || \
                                   ((POLYSIZE) == CRC_POLYSIZE_8b)  || ((POLYSIZE) == CRC_POLYSIZE_7b))

/*
 * @brief CRC init structure definition
 */
typedef struct
{
    CRCSize_TypeDef CRC_Size;           /* Specifies the size of the calculated data. */
    uint32_t CRC_OXOR;                  /* Specifies the XOR of CRC calculation result.*/
    uint32_t CRC_OReverse;              /* Specifies CRC inversion output data. */
    CRCIReverse_TypeDef CRC_IReverse;   /* Specifies CRC inversion input data. */
    CRCPOLYSIZE_TypeDef CRC_PolySize;   /* Specifies the size of the polynomial. */
    uint32_t CRC_INIT;                  /* Specifies the initial value of the CRC calculation. */
    uint32_t CRC_Poly;                  /* Specifies the polynomial. */
    uint32_t CRC_XOR;                   /* Specifies the XOR value of the CRC calculation result. */
} CRC_InitTypeDef;

/*
 * @defgroup CRC Output XOR Enable
 */
#define CRC_OXOR_Disable                ((uint32_t)0x00000000)              /* Output non XOR */
#define CRC_OXOR_Enable                 ((uint32_t)0x00000001)              /* Output XOR */
#define IS_CRC_OXOR(OXOR) (((OXOR) == CRC_OXOR_Disable) || ((OXOR) == CRC_OXOR_Enable))

/*
 * @defgroup CRC Reverse Output Data
 */
#define CRC_OREVERSE_Not                ((uint32_t)0x00000000)              /* Output data is not reversed */
#define CRC_OREVERSE_Bit                ((uint32_t)0x00000001)              /* Output data bit inversion */
#define IS_CRC_OREVERSE(OREVERSE) (((OREVERSE) == CRC_OREVERSE_Not) || ((OREVERSE) == CRC_OREVERSE_Bit))

/*
 * @defgroup CRC Polynomial
 */
#define CRC_POLY_7MMC                   ((uint32_t)0x00000009)              /* Polynomial CRC-7/MMC */
#define CRC_POLY_8                      ((uint32_t)0x00000007)              /* Polynomial CRC-8 */
#define CRC_POLY_8MAXIM                 ((uint32_t)0x00000031)              /* Polynomial CRC-8/MAXIM */
#define CRC_POLY_16IBM                  ((uint32_t)0x00008005)              /* Polynomial CRC-16/IBM */
#define CRC_POLY_16XMODEM               ((uint32_t)0x00001021)              /* Polynomial CRC-16/XMODEM */
#define CRC_POLY_16DNP                  ((uint32_t)0x00003D65)              /* Polynomial CRC-16/DNP */
#define CRC_POLY_32                     ((uint32_t)0x04C11DB7)              /* Polynomial CRC-32 */
#define CRC_POLY_32C                    ((uint32_t)0x1EDC6F41)              /* Polynomial CRC-32/C */
#define IS_CRC_POLY(POLY) ((POLY) <= 0xFFFFFFFF)

#define IS_CRC_DATA(DATA) ((DATA) <= 0xFFFFFFFF)
#define IS_CRC_INIT(INIT) ((INIT) <= 0xFFFFFFFF)
#define IS_CRC_XOR(XOR) ((XOR) <= 0xFFFFFFFF)

/*
 * @brief Function declaration
 */
void CRC_Reset(void);
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct);
void CRC_Init(CRC_InitTypeDef *CRC_InitStruct);
uint32_t CRC_CalcCRC(uint32_t Data);
uint32_t CRC_CalcWordBlockCRC(uint32_t *pBuffer, uint32_t BufferLength);
uint32_t CRC_CalcHalfBlockCRC(uint16_t *pBuffer, uint32_t BufferLength);
uint32_t CRC_CalcByteBlockCRC(uint8_t *pBuffer, uint32_t BufferLength);
void CRC_SetIDRegister(uint8_t IDValue);
uint8_t CRC_GetIDRegister(void);
uint32_t CRC_GetCRC(void);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
