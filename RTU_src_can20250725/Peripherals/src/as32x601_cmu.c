/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_cmu.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2024/08/20
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/20     1.0     build this module
 * Description:     This file provides firmware functions to manage the functionalities of the CMU peripheral.
 */

#include "as32x601_cmu.h"

/*
 * Function:        CMU_Cmd
 * Description:     Enables or disables the clock monitoring.
 * Param:           CMUx: where x can be (_FIRC,_PLLQ,_PLLR,_OSC) to select the CMU peripheral.
 *                  NewState: new state of the CMUx peripheral.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void CMU_Cmd(CMU_TypeDef *CMUx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));
    assert_param(IS_CMU_ALL_PERIPH(CMUx));

    if (NewState != DISABLE) 
    {
        CMUx->CR |= ((uint32_t)CMU_CR_MODE);
    } 
    else
    {
        CMUx->CR &= ~((uint32_t)CMU_CR_MODE);
    }
}

/*
 * Function:        CMU_SetWinLen
 * Description:     Set the reference Count Window Length.
 * Param:           CMUx: where x can be (_FIRC,_PLLQ,_PLLR,_OSC) to select the CMU peripheral.
 *                  WindowLength: Count Window Length.
 * Return:          None.
 */
void CMU_SetWinLen(CMU_TypeDef *CMUx, uint32_t WindowLength)
{
    /* Check the parameters */
    assert_param(IS_CMU_ALL_PERIPH(CMUx));
    assert_param(WindowLength <= 0xFFFFFF);

    CMUx->CCR = WindowLength;
}

/*
 * Function:        CMU_SetReferenceThreshold
 * Description:     Set the reference threshold.
 * Param:           CMUx: where x can be (_FIRC,_PLLQ,_PLLR,_OSC) to select the CMU peripheral.
 *                  HighThreshold: High frequency reference threshold.
 *                  LowThreshold: Low frequency reference threshold.
 * Return:          None.
 */
void CMU_SetReferenceThreshold(CMU_TypeDef *CMUx, uint32_t HighThreshold, uint32_t LowThreshold)
{
    /* Check the parameters */
    assert_param(IS_CMU_ALL_PERIPH(CMUx));
    assert_param(HighThreshold <= 0xFFFFFF);
    assert_param(LowThreshold <= 0xFFFFFF);

    CMUx->HTCR = HighThreshold;
    CMUx->LTCR = LowThreshold;
}

/*
 * Function:        CMU_GetFlagStatus
 * Description:     Check whether the specified CMU state has occurred or not.
 * param:           CMUx: where x can be (_FIRC,_PLLQ,_PLLR,_OSC) to select the CMU peripheral.
 *                  CMU_FLAG: Specifies the CMU flag to check.
 *                   This parameter can be one of the following values:
 *                    CMU_FLAG_WORK: Working condition.
 *                    CMU_FLAG_CHCDONE: Status detection.
 *                    CMU_FLAG_LOSSCLK: Clock loss status.
 *                    CMU_FLAG_FHH: State where the frequency is greater than the high-frequency reference threshold.
 *                    CMU_FLAG_FLL: Frequency below the low frequency reference threshold state.
 * Return:          CMU status.
 *                   This parameter can be one of the following values:
 *                    SET or RESET.
 */
FlagStatus CMU_GetFlagStatus(CMU_TypeDef *CMUx, uint32_t CMU_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	assert_param(IS_CMU_ALL_PERIPH(CMUx));
	assert_param(IS_CMU_FLAG(CMU_FLAG));

	if ((CMUx->SR & CMU_FLAG) != RESET) 
    {
        bitstatus = SET;
    } 
    else 
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/*
 * Function:        CMU_ClearFlag
 * Description:     Clear the status pending bits of the specified CMU.
 * Param:           CMUx: where x can be (_FIRC,_PLLQ,_PLLR,_OSC) to select the CMU peripheral.
 *                  CMU_FLAG: CMU clear flags.
 *                   This parameter can be one of the following values:
 *                    CMU_CLEAR_FHH: State where the frequency is greater than the high-frequency reference threshold clear.
 *                    CMU_CLEAR_FLL: Frequency below the low frequency reference threshold state clear.
 * Return:          None
 */
void CMU_ClearFlag(CMU_TypeDef *CMUx, uint32_t CMU_FLAG)
{
	/* Check the parameters */
	assert_param(IS_CMU_ALL_PERIPH(CMUx));
	assert_param(IS_CMU_CLEAR(CMU_FLAG));

	CMUx->SR = ((uint32_t)CMU_FLAG);
}

/*****END OF FILE*****/
