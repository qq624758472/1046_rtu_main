/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_dac.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:			2024/9/2
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/9/2      1.0     build this module
 * Description:     This file provides firmware functions to manage the functionalities of the DAC peripheral.
 */

#include "as32x601_dac.h"
#include <stddef.h>

/*
 * Function:        DAC_StructInit
 * Description:     Initialization convert structure.
 * Param:           DAC_InitStruct: convert config structure pointer.
 * Return:          None.
 */
void DAC_StructInit(DAC_InitTypeDef * const DAC_InitStruct)
{
    /* Reset DAC init structure parameters values */
    DAC_InitStruct->DAC_Enable              = DISABLE;  
    DAC_InitStruct->DAC_Mode                = DAC_MD_BUFFER_OUT;
    DAC_InitStruct->DAC_VrefMode            = DAC_VREF_MD_VREFP;
    DAC_InitStruct->DAC_ClockDivider        = 0x1;
}

/*
 * Function:        DAC_Init
 * Description:     Config DAC convert setting.
 * Param:           DACx: where x can be (0) to select the DAC peripheral.
 *                  DAC_InitStruct: convert config that need to config.
 * Return:          None.
 */
void DAC_Init(DAC_TypeDef *DACx, const DAC_InitTypeDef * const DAC_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));
    assert_param(DAC_InitStruct != NULL);
    assert_param(IS_DAC_EN(DAC_InitStruct->DAC_Enable));
    assert_param(IS_DAC_MD(DAC_InitStruct->DAC_Mode));
    assert_param(IS_DAC_VREF_MD(DAC_InitStruct->DAC_VrefMode));
    assert_param(IS_DAC_CLK_DIV(DAC_InitStruct->DAC_ClockDivider));

    /* Enable or disable DAC */
    DACx->CTRL &= ~((uint32_t)DAC_CTRL_EN);
    DACx->CTRL |= (((uint32_t)DAC_InitStruct->DAC_Enable) << DAC_CTRL_EN_Pos);

    /* Set DAC mode */
    DACx->CTRL &= ~((uint32_t)DAC_CTRL_MD);
    DACx->CTRL |= (((uint32_t)DAC_InitStruct->DAC_Enable) << DAC_CTRL_MD_Pos);

    /* Set DAC VREF mode */
    DACx->CTRL &= ~((uint32_t)DAC_CTRL_VREF_MD);
    DACx->CTRL |= (((uint32_t)DAC_InitStruct->DAC_VrefMode) << DAC_CTRL_VREF_MD_Pos);

    /* Set DAC clock divide */
    DACx->CTRL &= ~((uint32_t)DAC_CLK_DIV_NU);
    DACx->CTRL |= (((uint32_t)DAC_InitStruct->DAC_ClockDivider) << DAC_CLK_DIV_NU_Pos);
}

/*
 * Function:        DAC_Cmd
 * Description:     Enable or disable DAC.
 * Param:           DACx: where x can be (0) to select the DAC peripheral.
 *                  NewState: ENABLE or DISABLE.
 * Return:          None.
 */
void DAC_Cmd(DAC_TypeDef *DACx, FunctionalState NewState)
{
    assert_param(IS_DAC_ALL_PERIPH(DACx));

    if (NewState != DISABLE)
    {
        /* Enable the selected DAC */
        DACx->CTRL |= DAC_CTRL_EN;
    }
    else
    {
        /* Disable the selected DAC */
        DACx->CTRL &= ~DAC_CTRL_EN;
    }
}

/*
 * Function:        DAC_SetValue
 * Description:     Set DAC channel data holding register value.
 * Param:           DACx: where x can be (0) to select the DAC peripheral.
 *                  DAC_Value: DAC data.
 * Return:          None.
 */
void DAC_SetValue(DAC_TypeDef *DACx, uint16_t DAC_Value)
{
    assert_param(IS_ADC_ALL_PERIPH(DACx));

    /* Set the selected DAC channel data holding register */
    DACx->DOUT = DAC_Value;
}

/*
 * Function:        DAC_CMP_StructInit
 * Description:     Initialization compare structure.
 * Param:           DAC_CMPStruct: compare config structure pointer.
 * Return:          None.
 */
void DAC_CMP_StructInit(DAC_CMPTypedef * const DAC_CMPStruct)
{
    DAC_CMPStruct->CMP_Enable                      = DISABLE;
    DAC_CMPStruct->CMP_Mode                        = DAC_CMP_MD_DAC0;
    DAC_CMPStruct->CMP_Hysteresis                  = DAC_CMP_HYS_0;
}

/*
 * Function:        DAC_CMP_Init
 * Description:     Config DAC compare setting.
 * Param:           DACx: where x can be (0) to select the DAC peripheral.
 *                  DAC_CMPStruct: compare config that need to config.
 * Return:          None.
 */
void DAC_CMP_Init(DAC_TypeDef *DACx, const DAC_CMPTypedef * const DAC_CMPStruct)
{
    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));
    assert_param(DAC_CMPStruct != NULL);
    assert_param(IS_DAC_CMP_EN(DAC_CMPStruct->CMP_Enable));
    assert_param(IS_DAC_CMP_MD(DAC_CMPStruct->CMP_Mode));
    assert_param(IS_DAC_CMP_HYS(DAC_CMPStruct->CMP_Hysteresis));

    /* Set DAC compare enable */
    DACx->CTRL &= ~((uint32_t)DAC_CMP_CTRL_EN);
    DACx->CTRL |= (((uint32_t)DAC_CMPStruct->CMP_Enable) << DAC_CMP_CTRL_EN_Pos);

    /* Set DAC compare mode */
    DACx->CTRL &= ~((uint32_t)DAC_CMP_CTRL_MD);
    DACx->CTRL |= (((uint32_t)DAC_CMPStruct->CMP_Mode) << DAC_CMP_CTRL_MD_Pos);

    /* Set DAC compare hysteresis */
    DACx->CTRL &= ~((uint32_t)DAC_CMP_CTRL_HYS);
    DACx->CTRL |= (((uint32_t)DAC_CMPStruct->CMP_Hysteresis) << DAC_CMP_CTRL_HYS_Pos);
}

/*
 * Function:        DAC_CMP_Cmd
 * Description:     Enable or disable DAC compare.
 * Param:           DACx: where x can be (0) to select the DAC peripheral.
 *                  NewState: ENABLE or DISABLE.
 * Return:          None.
 */
void DAC_CMP_Cmd(DAC_TypeDef *DACx, FunctionalState NewState)
{
    assert_param(IS_DAC_ALL_PERIPH(DACx));

    if (NewState != DISABLE)
    {
        /* Enable the selected DAC compare */
        DACx->CTRL |= DAC_CMP_CTRL_EN;
    }
    else
    {
        /* Disable the selected DAC compare */
        DACx->CTRL &= ~DAC_CMP_CTRL_EN;
    }
}

/*
 * Function:        DAC_CMP_GetResult
 * Description:     Gets The DAC Comparator Result Value.
 * Param:           DACx: where x can be (0) to select the DAC peripheral.
 * Return:          DAC data.
 */
uint8_t DAC_CMP_GetResult(DAC_TypeDef *DACx)
{
    uint8_t temp = 0;

    /* Check the parameters */
    assert_param(IS_DAC_ALL_PERIPH(DACx));

    /* Get the DAC comparator result value */
    temp = (uint8_t)(DACx->CTRL & DAC_CMP_CTRL_CMPO);

    /* Return the DAC comparator result value */
    return (uint8_t)(temp >> DAC_CMP_CTRL_CMPO_Pos);
}

/*****END OF FILE*****/
