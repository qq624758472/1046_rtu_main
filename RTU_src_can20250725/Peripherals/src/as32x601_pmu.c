/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_pmu.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2024/07/16
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/07/16     1.0     build this module
 * Description:     This file provides firmware functions to manage the functionalities of the PMU peripheral.
 */

#include "as32x601_pmu.h"

/*
 * Function:        PMU_PowerModeConfig
 * Description:     Set the power mode to be switched.
 * Param:           PowerMode: Power mode setting value.
 *                   This parameter can be one of the following values:
 *                    PMU_PowerMode_DeepSleep: Deep sleep mode.
 *                    PMU_PowerMode_Sleep: Sleep mode.
 * Return:          None.
 */
void PMU_PowerModeConfig(PMUPowerMode_TypeDef PowerMode)
{
    /* Check the parameters */
    assert_param(IS_PMU_POWERMODE(PowerMode));

    /* Select power mode */
    PMU->PMCR = (uint32_t)PowerMode;
}

/*
 * Function:        PMU_GetPowerModeStatus
 * Description:     Get the current working power mode.
 * Param:           None.
 * Return:          Current power mode.
 *                   This parameter can be one of the following values:
 *                    PMU_PowerMode_INIT: Start initial mode.
 *                    PMU_PowerMode_DeepSleep: Deep sleep mode.
 *                    PMU_PowerMode_Sleep: Sleep mode.
 *                    PMU_PowerMode_Normal: Normal mode.
 */
PMUPowerMode_TypeDef PMU_GetPowerModeStatus(void)
{
    /* Return to power mode */
    return (PMUPowerMode_TypeDef)(PMU->PMCR);
}

/*
 * Function:        PMU_WakeUpSourceCmd
 * Description:     Enables or disables the sleep wake up source channel.
 * Param:           WakeUpSource: Wake up source channel value.
 *                   This parameter can be one of the following values:
 *                    PMU_WKSource_IWDG: The wake-up source is IWDG.
 *                    PMU_WKSource_RTC: The wake-up source is RTC.
 *                    PMU_WKSource_PH0: The wake-up source is PH0.
 *                    PMU_WKSource_PH1: The wake-up source is PH1.
 *                    PMU_WKSource_PH2: The wake-up source is PH2.
 *                    PMU_WKSource_PH3: The wake-up source is PH3.
 *                    PMU_WKSource_PH4: The wake-up source is PH4.
 *                    PMU_WKSource_PH5: The wake-up source is PH5.
 *                    PMU_WKSource_PH6: The wake-up source is PH6.
 *                    PMU_WKSource_PH7: The wake-up source is PH7.
 *                    PMU_WKSource_PH8: The wake-up source is PH8.
 *                    PMU_WKSource_PH9: The wake-up source is PH9.
 *                  NewState: new state of the USART LIN mode.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_WakeUpSourceCmd(PMUWKSource_TypeDef WakeUpSource, EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_PMU_WKSOURCE(WakeUpSource));
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the selected wake-up source by setting the wake-up source bit in the WKEN register */
        PMU->WKEN |= ((uint32_t)WakeUpSource);
    }
    else
    {
        /* Disable the selected wake-up source by setting the wake-up source bit in the WKEN register */
        PMU->WKEN &= ~((uint32_t)WakeUpSource);
    }
}

/*
 * Function:        PMU_BLDO1v2VOLSca
 * Description:     Set 1.2V backup LDO voltage scaling.
 * Param:           VoltageValue: 1.2V backup LDO electric compression discharge value.
 *                   This parameter can be one of the following values:
 *                    PMU_VO12_1V04: Adjust voltage to 1.04v.
 *                    PMU_VO12_1V06: Adjust voltage to 1.06v.
 *                    PMU_VO12_1V08: Adjust voltage to 1.08v.
 *                    PMU_VO12_1V10: Adjust voltage to 1.10v.
 *                    PMU_VO12_1V12: Adjust voltage to 1.12v.
 *                    PMU_VO12_1V14: Adjust voltage to 1.14v.
 *                    PMU_VO12_1V16: Adjust voltage to 1.16v.
 *                    PMU_VO12_1V18: Adjust voltage to 1.18v.
 *                    PMU_VO12_1V20: Adjust voltage to 1.20v(default).
 *                    PMU_VO12_1V22: Adjust voltage to 1.22v.
 *                    PMU_VO12_1V24: Adjust voltage to 1.24v.
 *                    PMU_VO12_1V26: Adjust voltage to 1.26v.
 *                    PMU_VO12_1V28: Adjust voltage to 1.28v.
 *                    PMU_VO12_1V30: Adjust voltage to 1.30v.
 *                    PMU_VO12_1V32: Adjust voltage to 1.32v.
 *                    PMU_VO12_1V34: Adjust voltage to 1.34v.
 * Return:          None.
 */
void PMU_BLDO1v2VOLSca(uint32_t VoltageValue)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PMU_VOS1V2(VoltageValue));

    tmpreg = PMU->LDOCR;

    /* Select 1.2V backup LDO voltage scaling */
    tmpreg &= ~((uint32_t)PMU_LDOCR_1V2BLDOVOS);
    tmpreg |= ((uint32_t)VoltageValue << PMU_LDOCR_1V2BLDOVOS_Pos);

    /* Write to PMU LDOCR */
    PMU->LDOCR = tmpreg;
}

/*
 * Function:        PMU_LDO1v2VOLSca
 * Description:     Set 1.2V LDO voltage scaling.
 * Param:           VoltageValue: 1.2V LDO electric compression discharge value.
 *                   This parameter can be one of the following values:
 *                    PMU_VO12_1V04: Adjust voltage to 1.04v.
 *                    PMU_VO12_1V06: Adjust voltage to 1.06v.
 *                    PMU_VO12_1V08: Adjust voltage to 1.08v.
 *                    PMU_VO12_1V10: Adjust voltage to 1.10v.
 *                    PMU_VO12_1V12: Adjust voltage to 1.12v.
 *                    PMU_VO12_1V14: Adjust voltage to 1.14v.
 *                    PMU_VO12_1V16: Adjust voltage to 1.16v.
 *                    PMU_VO12_1V18: Adjust voltage to 1.18v.
 *                    PMU_VO12_1V20: Adjust voltage to 1.20v(default).
 *                    PMU_VO12_1V22: Adjust voltage to 1.22v.
 *                    PMU_VO12_1V24: Adjust voltage to 1.24v.
 *                    PMU_VO12_1V26: Adjust voltage to 1.26v.
 *                    PMU_VO12_1V28: Adjust voltage to 1.28v.
 *                    PMU_VO12_1V30: Adjust voltage to 1.30v.
 *                    PMU_VO12_1V32: Adjust voltage to 1.32v.
 *                    PMU_VO12_1V34: Adjust voltage to 1.34v.
 * Return:          None.
 */
void PMU_LDO1v2VOLSca(uint32_t VoltageValue)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PMU_VOS1V2(VoltageValue));

    tmpreg = PMU->LDOCR;

    /* Select 1.2V LDO voltage scaling */
    tmpreg &= ~((uint32_t)PMU_LDOCR_1V2LDOVOS);
    tmpreg |= ((uint32_t)VoltageValue << PMU_LDOCR_1V2LDOVOS_Pos);

    /* Write to PMU LDOCR */
    PMU->LDOCR = tmpreg;
}

/*
 * Function:        PMU_Refer1v2VOLSca
 * Description:     Set 1.2V reference voltage source scaling.
 * Param:           VoltageValue: 1.2V reference voltage source scaling value.
 *                   This parameter can be one of the following values:
 *                    PMU_VREF12_1V04: Adjust refer voltage to 1.04v.
 *                    PMU_VREF12_1V06: Adjust refer voltage to 1.06v.
 *                    PMU_VREF12_1V08: Adjust refer voltage to 1.08v.
 *                    PMU_VREF12_1V10: Adjust refer voltage to 1.10v.
 *                    PMU_VREF12_1V12: Adjust refer voltage to 1.12v.
 *                    PMU_VREF12_1V14: Adjust refer voltage to 1.14v.
 *                    PMU_VREF12_1V16: Adjust refer voltage to 1.16v.
 *                    PMU_VREF12_1V18: Adjust refer voltage to 1.18v.
 *                    PMU_VREF12_1V20: Adjust refer voltage to 1.20v(default).
 *                    PMU_VREF12_1V22: Adjust refer voltage to 1.22v.
 *                    PMU_VREF12_1V24: Adjust refer voltage to 1.24v.
 *                    PMU_VREF12_1V26: Adjust refer voltage to 1.26v.
 *                    PMU_VREF12_1V28: Adjust refer voltage to 1.28v.
 *                    PMU_VREF12_1V30: Adjust refer voltage to 1.30v.
 *                    PMU_VREF12_1V32: Adjust refer voltage to 1.32v.
 *                    PMU_VREF12_1V34: Adjust refer voltage to 1.34v.
 * Return:          None.
 */
void PMU_Refer1v2VOLSca(uint32_t VoltageValue)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PMU_VREFS1V2(VoltageValue));

    tmpreg = PMU->LDOCR;

    /* Select 1.2V reference voltage source scaling */
    tmpreg &= ~((uint32_t)PMU_LDOCR_1V2VREFS);
    tmpreg |= ((uint32_t)VoltageValue << PMU_LDOCR_1V2VREFS_Pos);

    /* Write to PMU LDOCR */
    PMU->LDOCR = tmpreg;
}

/*
 * Function:        PMU_Refer1v2Cmd
 * Description:     Enables or disables the 1.2V refer LDO.
 * Param:           NewState: new state of the 1.2V refer LDO.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_Refer1v2Cmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the 1.2V Flash reference voltage source by setting the 1V2VREFEN bit in the LDOCR register */
        PMU->LDOCR |= ((uint32_t)PMU_LDOCR_1V2VREFEN);
    } 
    else
    {
        /* Disable the 1.2V Flash reference voltage source by setting the 1V2VREFEN bit in the LDOCR register */
        PMU->LDOCR &= ~((uint32_t)PMU_LDOCR_1V2VREFEN);
    }
}

/*
 * Function:        PMU_LDO1v2Cmd
 * Description:     Enables or disables the 1.2V LDO.
 * Param:           NewState: new state of the 1.2V LDO.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_LDO1v2Cmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the 1.2V LDO by setting the 1V2LDOEN bit in the LDOCR register */
        PMU->LDOCR |= ((uint32_t)PMU_LDOCR_1V2LDOEN);
    } 
    else
    {
        /* Disable the 1.2V LDO by setting the 1V2LDOEN bit in the LDOCR register */
        PMU->LDOCR &= ~((uint32_t)PMU_LDOCR_1V2LDOEN);
    }
}

/*
 * Function:        PMU_LDO2v5VOLSca
 * Description:     Set 2.5V LDO voltage scaling.
 * Param:           VoltageValue: 2.5V LDO electric compression discharge value.
 *                   This parameter can be one of the following values:
 *                    PMU_VO25_2V18: Adjust voltage to 2.18v.
 *                    PMU_VO25_2V22: Adjust voltage to 2.22v.
 *                    PMU_VO25_2V26: Adjust voltage to 2.26v.
 *                    PMU_VO25_2V30: Adjust voltage to 2.30v.
 *                    PMU_VO25_2V34: Adjust voltage to 2.34v.
 *                    PMU_VO25_2V38: Adjust voltage to 2.38v.
 *                    PMU_VO25_2V42: Adjust voltage to 2.42v.
 *                    PMU_VO25_2V46: Adjust voltage to 2.46v.
 *                    PMU_VO25_2V50: Adjust voltage to 2.50v(default).
 *                    PMU_VO25_2V54: Adjust voltage to 2.54v.
 *                    PMU_VO25_2V58: Adjust voltage to 2.58v.
 *                    PMU_VO25_2V62: Adjust voltage to 2.62v.
 *                    PMU_VO25_2V66: Adjust voltage to 2.66v.
 *                    PMU_VO25_2V72: Adjust voltage to 2.72v.
 *                    PMU_VO25_2V74: Adjust voltage to 2.74v.
 *                    PMU_VO25_2V78: Adjust voltage to 2.78v.
 * Return:          None.
 */
void PMU_LDO2v5VOLSca(uint32_t VoltageValue)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PMU_VOS2V5(VoltageValue));

    tmpreg = PMU->LDOCR;

    /* Select 2.5V LDO voltage scaling */
    tmpreg &= ~((uint32_t)PMU_LDOCR_2V5LDOVOS);
    tmpreg |= ((uint32_t)VoltageValue << PMU_LDOCR_2V5LDOVOS_Pos);

    /* Write to PMU LDOCR */
    PMU->LDOCR = tmpreg;
}

/*
 * Function:        PMU_LDO2v5Cmd
 * Description:     Enables or disables the 2.5V LDO.
 * Param:           NewState: new state of the 2.5V LDO.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_LDO2v5Cmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the 2.5V LDO by setting the 2V5LDOEN bit in the LDOCR register */
        PMU->LDOCR |= ((uint32_t)PMU_LDOCR_2V5LDOEN);
    } 
    else
    {
        /* Disable the 2.5V LDO by setting the 2V5LDOEN bit in the LDOCR register */
        PMU->LDOCR &= ~((uint32_t)PMU_LDOCR_2V5LDOEN);
    }
}

/*
 * Function:        PMU_LDO3v3VOLSca
 * Description:     Set 3.3V LDO voltage scaling.
 * Param:           VoltageValue: 3.3V LDO electric compression discharge value.
 *                   This parameter can be one of the following values:
 *                    PMU_VO33_2V90: Adjust voltage to 2.90v.
 *                    PMU_VO33_2V95: Adjust voltage to 2.95v.
 *                    PMU_VO33_3V00: Adjust voltage to 3.00v.
 *                    PMU_VO33_3V05: Adjust voltage to 3.05v.
 *                    PMU_VO33_3V10: Adjust voltage to 3.10v.
 *                    PMU_VO33_3V15: Adjust voltage to 3.15v.
 *                    PMU_VO33_3V20: Adjust voltage to 3.20v.
 *                    PMU_VO33_3V25: Adjust voltage to 3.25v.
 *                    PMU_VO33_3V30: Adjust voltage to 3.30v(default).
 *                    PMU_VO33_3V35: Adjust voltage to 3.35v.
 *                    PMU_VO33_3V40: Adjust voltage to 3.40v.
 *                    PMU_VO33_3V45: Adjust voltage to 3.45v.
 *                    PMU_VO33_3V50: Adjust voltage to 3.50v.
 *                    PMU_VO33_3V55: Adjust voltage to 3.55v.
 *                    PMU_VO33_3V60: Adjust voltage to 3.60v.
 *                    PMU_VO33_3V65: Adjust voltage to 3.65v.
 * Return:          None.
 */
void PMU_LDO3v3VOLSca(uint32_t VoltageValue)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PMU_VOS3V3(VoltageValue));

    tmpreg = PMU->LDOCR;

    /* Select 3.3V LDO voltage scaling */
    tmpreg &= ~((uint32_t)PMU_LDOCR_3V3LDOVOS);
    tmpreg |= ((uint32_t)VoltageValue << PMU_LDOCR_3V3LDOVOS_Pos);

    /* Write to PMU LDOCR */
    PMU->LDOCR = tmpreg;
}

/*
 * Function:        PMU_LDO3v3BypassCmd
 * Description:     Enables or disables the 3.3V LDO bypass.
 * Param:           NewState: new state of the 3.3V LDO bypass.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_LDO3v3BypassCmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE)
    {
        /* Enable the 3.3V LDO bypass by setting the 3V3LDOBYP bit in the LDOCR register */
        PMU->LDOCR |= ((uint32_t)PMU_LDOCR_3V3LDOBYP);
    } 
    else 
    {
        /* Disable the 3.3V LDO bypass by setting the 3V3LDOBYP bit in the LDOCR register */
        PMU->LDOCR &= ~((uint32_t)PMU_LDOCR_3V3LDOBYP);
    }
}

/*
 * Function:        PMU_LDO3v3Cmd
 * Description:     Enables or disables the 3.3V LDO.
 * Param:           NewState: new state of the 3.3V LDO.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_LDO3v3Cmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the 3.3V LDO by setting the 3V3LDOEN bit in the LDOCR register */
        PMU->LDOCR |= ((uint32_t)PMU_LDOCR_3V3LDOEN);
    }
    else
    {
        /* Disable the 3.3V LDO by setting the 3V3LDOEN bit in the LDOCR register */
        PMU->LDOCR &= ~((uint32_t)PMU_LDOCR_3V3LDOEN);
    }
}

/*
 * Function:        PMU_LowVolResetCmd
 * Description:     Enables or disables the low voltage reset.
 * Param:           NewState: new state of the low voltage reset.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_LowVolResetCmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the low voltage reset by setting the LVREN bit in the VDCR register */
        PMU->VDCR |= ((uint32_t)PMU_VDCR_LVREN);
    }
    else
    {
        /* Disable the low voltage reset by setting the LVREN bit in the VDCR register */
        PMU->VDCR &= ~((uint32_t)PMU_VDCR_LVREN);
    }
}

/*
 * Function:        PMU_HighVolDetectCmd
 * Description:     Enables or disables the high voltage detect.
 * Param:           NewState: new state of the high voltage detect.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_HighVolDetectCmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the high voltage detect by setting the HVDEN bit in the VDCR register */
        PMU->VDCR |= ((uint32_t)PMU_VDCR_HVDEN);
    }
    else
    {
        /* Disable the high voltage detect by setting the HVDEN bit in the VDCR register */
        PMU->VDCR &= ~((uint32_t)PMU_VDCR_HVDEN);
    }
}

/*
 * Function:        PMU_HighVolDetectThresholdSca
 * Description:     Set high voltage detect threshold scaling.
 * Param:           VoltageValue: high voltage detect threshold scaling value.
 *                   This parameter can be one of the following values:
 *                    PMU_HVDTS_2V4: Adjust the detection threshold voltage to 2.4V.
 *                    PMU_HVDTS_2V5: Adjust the detection threshold voltage to 2.5V.
 *                    PMU_HVDTS_2V6: Adjust the detection threshold voltage to 2.6V.
 *                    PMU_HVDTS_2V7: Adjust the detection threshold voltage to 2.7V.
 *                    PMU_HVDTS_2V8: Adjust the detection threshold voltage to 2.8V.
 *                    PMU_HVDTS_2V9: Adjust the detection threshold voltage to 2.9V.
 *                    PMU_HVDTS_3V0: Adjust the detection threshold voltage to 3.0V.
 *                    PMU_HVDTS_3V1: Adjust the detection threshold voltage to 3.1V.
 *                    PMU_HVDTS_3V2: Adjust the detection threshold voltage to 3.2V.
 *                    PMU_HVDTS_3V3: Adjust the detection threshold voltage to 3.3V.
 *                    PMU_HVDTS_3V4: Adjust the detection threshold voltage to 3.4V.
 *                    PMU_HVDTS_3V5: Adjust the detection threshold voltage to 3.5V.
 *                    PMU_HVDTS_3V6: Adjust the detection threshold voltage to 3.6V.
 *                    PMU_HVDTS_3V7: Adjust the detection threshold voltage to 3.7V.
 *                    PMU_HVDTS_3V8: Adjust the detection threshold voltage to 3.8V.
 *                    PMU_HVDTS_3V9: Adjust the detection threshold voltage to 3.9V.
 *                    PMU_HVDTS_4V0: Adjust the detection threshold voltage to 4.0V.
 *                    PMU_HVDTS_4V1: Adjust the detection threshold voltage to 4.1V.
 *                    PMU_HVDTS_4V2: Adjust the detection threshold voltage to 4.2V.
 *                    PMU_HVDTS_4V3: Adjust the detection threshold voltage to 4.3V.
 *                    PMU_HVDTS_4V4: Adjust the detection threshold voltage to 4.4V.
 *                    PMU_HVDTS_4V5: Adjust the detection threshold voltage to 4.5V.
 *                    PMU_HVDTS_4V6: Adjust the detection threshold voltage to 4.6V.
 *                    PMU_HVDTS_4V7: Adjust the detection threshold voltage to 4.7V.
 *                    PMU_HVDTS_4V8: Adjust the detection threshold voltage to 4.8V.
 *                    PMU_HVDTS_4V9: Adjust the detection threshold voltage to 4.9V.
 *                    PMU_HVDTS_5V0: Adjust the detection threshold voltage to 5.0V.
 *                    PMU_HVDTS_5V1: Adjust the detection threshold voltage to 5.1V.
 *                    PMU_HVDTS_5V2: Adjust the detection threshold voltage to 5.2V.
 *                    PMU_HVDTS_5V3: Adjust the detection threshold voltage to 5.3V.
 *                    PMU_HVDTS_5V4: Adjust the detection threshold voltage to 5.4V.
 *                    PMU_HVDTS_5V5: Adjust the detection threshold voltage to 5.5V(default).
 * Return:          None.
 */
void PMU_HighVolDetectThresholdSca(uint32_t VoltageValue)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PMU_HVDTS(VoltageValue));

    tmpreg = PMU->VDCR;

    /* Select high voltage detect threshold scaling */
    tmpreg &= ~((uint32_t)PMU_VDCR_HVDTS);
    tmpreg |= ((uint32_t)VoltageValue << PMU_VDCR_HVDTS_Pos);

    /* Write to PMU VDCR */
    PMU->VDCR = tmpreg;
}

/*
 * Function:        PMU_LowVolDetectCmd
 * Description:     Enables or disables the low voltage detect.
 * Param:           NewState: new state of the low voltage detect.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_LowVolDetectCmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the low voltage detect by setting the LVDEN bit in the VDCR register */
        PMU->VDCR |= ((uint32_t)PMU_VDCR_LVDEN);
    }
    else
    {
        /* Disable the low voltage detect by setting the LVDEN bit in the VDCR register */
        PMU->VDCR &= ~((uint32_t)PMU_VDCR_LVDEN);
    }
}

/*
 * Function:        PMU_LowVolDetectThresholdSca
 * Description:     Set low voltage detect threshold scaling.
 * Param:           VoltageValue: low voltage detect threshold scaling value.
 *                   This parameter can be one of the following values:
 *                    PMU_LVDTS_2V4: Adjust the detection threshold voltage to 2.4V.
 *                    PMU_LVDTS_2V5: Adjust the detection threshold voltage to 2.5V.
 *                    PMU_LVDTS_2V6: Adjust the detection threshold voltage to 2.6V.
 *                    PMU_LVDTS_2V7: Adjust the detection threshold voltage to 2.7V.
 *                    PMU_LVDTS_2V8: Adjust the detection threshold voltage to 2.8V.
 *                    PMU_LVDTS_2V9: Adjust the detection threshold voltage to 2.9V(default).
 *                    PMU_LVDTS_3V0: Adjust the detection threshold voltage to 3.0V.
 *                    PMU_LVDTS_3V1: Adjust the detection threshold voltage to 3.1V.
 *                    PMU_LVDTS_3V2: Adjust the detection threshold voltage to 3.2V.
 *                    PMU_LVDTS_3V3: Adjust the detection threshold voltage to 3.3V.
 *                    PMU_LVDTS_3V4: Adjust the detection threshold voltage to 3.4V.
 *                    PMU_LVDTS_3V5: Adjust the detection threshold voltage to 3.5V.
 *                    PMU_LVDTS_3V6: Adjust the detection threshold voltage to 3.6V.
 *                    PMU_LVDTS_3V7: Adjust the detection threshold voltage to 3.7V.
 *                    PMU_LVDTS_3V8: Adjust the detection threshold voltage to 3.8V.
 *                    PMU_LVDTS_3V9: Adjust the detection threshold voltage to 3.9V.
 *                    PMU_LVDTS_4V0: Adjust the detection threshold voltage to 4.0V.
 *                    PMU_LVDTS_4V1: Adjust the detection threshold voltage to 4.1V.
 *                    PMU_LVDTS_4V2: Adjust the detection threshold voltage to 4.2V.
 *                    PMU_LVDTS_4V3: Adjust the detection threshold voltage to 4.3V.
 *                    PMU_LVDTS_4V4: Adjust the detection threshold voltage to 4.4V.
 *                    PMU_LVDTS_4V5: Adjust the detection threshold voltage to 4.5V.
 *                    PMU_LVDTS_4V6: Adjust the detection threshold voltage to 4.6V.
 *                    PMU_LVDTS_4V7: Adjust the detection threshold voltage to 4.7V.
 *                    PMU_LVDTS_4V8: Adjust the detection threshold voltage to 4.8V.
 *                    PMU_LVDTS_4V9: Adjust the detection threshold voltage to 4.9V.
 *                    PMU_LVDTS_5V0: Adjust the detection threshold voltage to 5.0V.
 *                    PMU_LVDTS_5V1: Adjust the detection threshold voltage to 5.1V.
 *                    PMU_LVDTS_5V2: Adjust the detection threshold voltage to 5.2V.
 *                    PMU_LVDTS_5V3: Adjust the detection threshold voltage to 5.3V.
 *                    PMU_LVDTS_5V4: Adjust the detection threshold voltage to 5.4V.
 *                    PMU_LVDTS_5V5: Adjust the detection threshold voltage to 5.5V.
 * Return:          None.
 */
void PMU_LowVolDetectThresholdSca(uint32_t VoltageValue)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PMU_LVDTS(VoltageValue));

    tmpreg = PMU->VDCR;

    /* Select low voltage detect threshold scaling */
    tmpreg &= ~((uint32_t)PMU_VDCR_LVDTS);
    tmpreg |= ((uint32_t)VoltageValue << PMU_VDCR_LVDTS_Pos);

    /* Write to PMU VDCR */
    PMU->VDCR = tmpreg;
}

/*
 * Function:        PMU_RC16MCmd
 * Description:     Enables or disables the internal RC 16MHz clock.
 * Param:           NewState: new state of the low voltage detect.
 *                   This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void PMU_RC16MCmd(EnState NewState)
{
    /* Check the parameters */
    assert_param(IS_EnState_STATE(NewState));

    if (NewState != (uint32_t)DISABLE) 
    {
        /* Enable the internal RC 16MHz clock by setting the IRC16MEN bit in the OCR register */
        PMU->OCR |= ((uint32_t)PMU_OCR_IRC16MEN);
    }
    else
    {
        /* Disable the internal RC 16MHz clock by setting the IRC16MEN bit in the OCR register */
        PMU->OCR &= ~((uint32_t)PMU_OCR_IRC16MEN);
    }
}

/*
 * Function:        PMU_RC32KFrequencySca
 * Description:     Set RC 32KHz clock frequency scaling.
 * Param:           ClockFrequency: RC 32KHz clock frequency scaling value.
 * Note:            The clock adjustment parameter can be one of the following values:
 *                   000000:22.282KHz.
 *                   000001:22.609KHz.
 *                   … …
 *                   100000:32.768KHz(default).
 *                   … …
 *                   111111:42.926KHz.
 * Return:          None.
 */
void PMU_RC32KFrequencySca(uint32_t ClockFrequency)
{
    uint32_t tmpreg = 0x00;

    /* Check the parameters */
    assert_param(IS_PMU_RC32KFS(ClockFrequency));

    tmpreg = PMU->OCR;
    tmpreg &= ~((uint32_t)PMU_OCR_RC32KFS);
    tmpreg |= ((uint32_t)ClockFrequency << PMU_OCR_RC32KFS_Pos);
    PMU->OCR = tmpreg;
}

/*
 * Function:        PMU_GetFlagStatus
 * Description:     Check whether the specified PMUstatus has occurred or not.
 * param:           PMU_FLAG: Specifies the PMU flag to check.
 *                   This parameter can be one of the following values:
 *                    PMU_FLAG_3V3LDORDY: 3.3V LDO voltage ready flag.
 *                    PMU_FLAG_2V5LDORDY: 2.5V LDO voltage ready flag.
 *                    PMU_FLAG_1V2LDORDY: 1.2V LDO voltage ready flag.
 *                    PMU_FLAG_1V2BLDORDY: 1.2V backup LDO voltage ready flag.
 *                    PMU_FLAG_IWDGWK: IWDG wake-up flag.
 *                    PMU_FLAG_RTCWK: RTC wake-up flag.
 *                    PMU_FLAG_PH0WK: PH0 wake-up flag.
 *                    PMU_FLAG_PH1WK: PH1 wake-up flag.
 *                    PMU_FLAG_PH2WK: PH2 wake-up flag.
 *                    PMU_FLAG_PH3WK: PH3 wake-up flag.
 *                    PMU_FLAG_PH4WK: PH4 wake-up flag.
 *                    PMU_FLAG_PH5WK: PH5 wake-up flag.
 *                    PMU_FLAG_PH6WK: PH6 wake-up flag.
 *                    PMU_FLAG_PH7WK: PH7 wake-up flag.
 *                    PMU_FLAG_PH8WK: PH8 wake-up flag.
 *                    PMU_FLAG_PH9WK: PH9 wake-up flag.
 *                    PMU_FLAG_FOCUR: FOCU reset flag.
 * Return:          PMU status.
 *                   This parameter can be one of the following values:
 *                    SET or RESET.
 */
FlagStatus PMU_GetFlagStatus(uint32_t PMU_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_PMU_FLAG(PMU_FLAG));

    if(((PMU_FLAG & PMU_SR_MASK) >> PMU_SR_POS) == 1U)
    {
        if ((PMU->LDOSR & ((uint32_t)(1U << (PMU_FLAG & PMU_FLAG_MASK)))) != RESET) 
        {
            bitstatus = SET;
        } 
        else 
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if ((PMU->WKFR & ((uint32_t)(1U << (PMU_FLAG & PMU_FLAG_MASK)))) != RESET) 
        {
            bitstatus = SET;
        } 
        else 
        {
            bitstatus = RESET;
        }
    }

    return bitstatus;
}

/*
 * Function:        PMU_ClearFlag
 * Description:     Clear the status pending bits of the specified PMU.
 * Param:           CMU_FLAG: CMU clear flags.
 *                   This parameter can be one of the following values:
 *                    PMU_CLEAR_IWDGWKF: IWDG wake-up flag clear.
 *                    PMU_CLEAR_RTCWKF: RTC wake-up flag clear.
 *                    PMU_CLEAR_PH0WKF: PH0 wake-up flag clear.
 *                    PMU_CLEAR_PH1WKF: PH1 wake-up flag clear.
 *                    PMU_CLEAR_PH2WKF: PH2 wake-up flag clear.
 *                    PMU_CLEAR_PH3WKF: PH3 wake-up flag clear.
 *                    PMU_CLEAR_PH4WKF: PH4 wake-up flag clear.
 *                    PMU_CLEAR_PH5WKF: PH5 wake-up flag clear.
 *                    PMU_CLEAR_PH6WKF: PH6 wake-up flag clear.
 *                    PMU_CLEAR_PH7WKF: PH7 wake-up flag clear.
 *                    PMU_CLEAR_PH8WKF: PH8 wake-up flag clear.
 *                    PMU_CLEAR_PH9WKF: PH9 wake-up flag clear.
 *                    PMU_CLEAR_FOCURF: FOCU reset flag clear.
 * Return:          None
 */
void PMU_ClearFlag(uint32_t PMU_FLAG)
{
    /* Check the parameters */
    assert_param(IS_PMU_CLEAR(PMU_FLAG));

    PMU->WKFR = PMU_FLAG;
}

/*****END OF FILE*****/
