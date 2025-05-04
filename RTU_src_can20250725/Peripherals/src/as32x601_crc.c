/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_crc.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2024/09/09
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/09/09     1.0     build this module
 * Description:     This file provides firmware functions to manage the functionalities of the CRC peripheral.
 */

#include "as32x601_crc.h"

/*
 * Function:        CRC_Reset
 * Description:     Reset CRC.
 * Param:           None.
 * Return:          None.
 */
void CRC_Reset(void)
{
    /* Reset CRC */
    CRC->CR = CRC_CR_RESET;
}

/*
 * Function:        CRC_StructInit
 * Description:     Fills each CRC_InitStruct member with its default value.
 * Param:           CRC_InitStruct: pointer to a CRC_InitTypeDef structure that contains
 *                  the configuration information for the specified.
 * Return:          None.
 */
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct)
{
    /* CRC_InitStruct members default value */
    CRC_InitStruct->CRC_Size = CRC_Size_32b;
    CRC_InitStruct->CRC_OXOR = CRC_OXOR_Disable;
    CRC_InitStruct->CRC_OReverse = CRC_OREVERSE_Not;
    CRC_InitStruct->CRC_IReverse = CRC_IReverse_NOT;
    CRC_InitStruct->CRC_PolySize = CRC_POLYSIZE_32b;
    CRC_InitStruct->CRC_INIT = 0x00000000;
    CRC_InitStruct->CRC_Poly = CRC_POLY_32;
    CRC_InitStruct->CRC_XOR = 0x00000000;
}

/*
 * Function:        CRC_Init
 * Description:     Initialize the CRC according to the specified.
 *					parameters in the CRC_InitTypeDef and initialize the associated handle.
 * Param:           CRC_InitStruct: pointer to a CRC_InitTypeDef structure that contains
 *                  the configuration information for the specified CRC peripheral.
 * Return:          None.
 */
void CRC_Init(CRC_InitTypeDef *CRC_InitStruct)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_CRC_SIZE(CRC_InitStruct->CRC_Size));
    assert_param(IS_CRC_OXOR(CRC_InitStruct->CRC_OXOR));
    assert_param(IS_CRC_OREVERSE(CRC_InitStruct->CRC_OReverse));
    assert_param(IS_CRC_IREVERSE(CRC_InitStruct->CRC_IReverse));
    assert_param(IS_CRC_POLYSIZE(CRC_InitStruct->CRC_PolySize));
    assert_param(IS_CRC_INIT(CRC_InitStruct->CRC_INIT));
    assert_param(IS_CRC_POLY(CRC_InitStruct->CRC_Poly));
    assert_param(IS_CRC_XOR(CRC_InitStruct->CRC_XOR));

    tmpreg = CRC->CR;

    /* Set the size of CRC calculation data */
    tmpreg &= ~((uint32_t)CRC_CR_SIZE);
    tmpreg |= (CRC_InitStruct->CRC_Size << CRC_CR_SIZE_Pos);

    /* Set CRC calculation result XOR */
    tmpreg &= ~((uint32_t)CRC_CR_XOROUT);
    tmpreg |= (CRC_InitStruct->CRC_OXOR << CRC_CR_XOROUT_Pos);

    /* Set CRC reverse output data */
    tmpreg &= ~((uint32_t)CRC_CR_REVOUT);
    tmpreg |= (CRC_InitStruct->CRC_OReverse << CRC_CR_REVOUT_Pos);

    /* Set CRC reverse input data */
    tmpreg &= ~((uint32_t)CRC_CR_REVIN);
    tmpreg |= (CRC_InitStruct->CRC_IReverse << CRC_CR_REVIN_Pos);

    /* Set CRC polynomial size */
    tmpreg &= ~((uint32_t)CRC_CR_POLYSIZE);
    tmpreg |= (CRC_InitStruct->CRC_PolySize << CRC_CR_POLYSIZE_Pos);

    /* Write to CRC CR */
    CRC->CR = (uint32_t)tmpreg;

    /* Set CRC initial vector */
    CRC->INIT = (uint32_t)CRC_InitStruct->CRC_INIT;

    /* Set CRC polynomial */
    CRC->POLY = (uint32_t)CRC_InitStruct->CRC_Poly;

    /* Set CRC XOR polynomial */
    CRC->XOR = (uint32_t)CRC_InitStruct->CRC_XOR;
}

/*
 * Function:        CRC_CalcCRC
 * Description:     Computes the 32-bit CRC of a given data word.
 * Param:           Data: data word to compute its CRC.
 * Return:          32-bit CRC.
 */
uint32_t CRC_CalcCRC(uint32_t Data)
{
    /* Write the data to the CRC Data register */
    CRC->DR = Data;

    /* Return the CRC value */
    return CRC->DR;
}

/*
 * Function:        CRC_CalcWordBlockCRC
 * Description:     Computes the 32-bit CRC of a given buffer of data word(32-bit).
 * Param:           pBuffer: pointer to the buffer containing the data to be computed.
 *                  BufferLength: length of the buffer to be computed.
 * Return:          32-bit CRC.
 */
uint32_t CRC_CalcWordBlockCRC(uint32_t *pBuffer, uint32_t BufferLength)
{
    uint32_t index = 0;

    for(index = 0; index < BufferLength; index++)
    {
        CRC->DR = pBuffer[index];
    }

    return (CRC->DR);
}

/*
 * Function:        CRC_CalcHalfBlockCRC
 * Description:     Computes the 16-bit CRC of a given buffer of data halfword(16-bit).
 * Param:           pBuffer: pointer to the buffer containing the data to be computed.
 *                  BufferLength: length of the buffer to be computed.
 * Return:          32-bit CRC.
 */
uint32_t CRC_CalcHalfBlockCRC(uint16_t *pBuffer, uint32_t BufferLength)
{
    uint32_t index = 0;

    for(index = 0; index < BufferLength; index++)
    {
        CRC->DR = pBuffer[index];
    }

    return (CRC->DR);
}

/*
 * Function:        CRC_CalcByteBlockCRC
 * Description:     Computes the 8-bit CRC of a given buffer of data byte(8-bit).
 * Param:           pBuffer: pointer to the buffer containing the data to be computed.
 *                  BufferLength: length of the buffer to be computed.
 * Return:          32-bit CRC.
 */
uint32_t CRC_CalcByteBlockCRC(uint8_t *pBuffer, uint32_t BufferLength)
{
    uint32_t index = 0;

    for(index = 0; index < BufferLength; index++)
    {
        CRC->DR = pBuffer[index];
    }

    return (CRC->DR);
}

/*
 * Function:        CRC_SetIDRegister
 * Description:     Stores a 8-bit data in the Independent Data(ID) register.
 * Param:           IDValue: 8-bit value to be stored in the ID register.
 * Return:          None.
 */
void CRC_SetIDRegister(uint8_t IDValue)
{
    CRC->IDR = IDValue;
}

/*
 * Function:        CRC_GetIDRegister
 * Description:     Returns the 8-bit data stored in the Independent Data(ID) register.
 * Param:           None.
 * Return:          8-bit value of the ID register.
 */
uint8_t CRC_GetIDRegister(void)
{
    return (CRC->IDR);
} 

/*
 * Function:        CRC_GetCRC
 * Description:     Returns the current CRC value.
 * Param:           None.
 * Return:          32-bit CRC.
 */
uint32_t CRC_GetCRC(void)
{
    return (CRC->DR);
}

/*****END OF FILE*****/
