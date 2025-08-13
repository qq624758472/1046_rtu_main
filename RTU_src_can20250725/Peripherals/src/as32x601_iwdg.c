/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_iwdg.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2024/07/31
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/07/31     1.0     build this module
 * Description:         This file provides firmware functions to manage the functionalities of the IWDG module.
 */

#include "as32x601_iwdg.h"

/* CLR register bit mask*/
#define CLR_KEY_RESET    ((uint32_t)(0x2f3e5d8a))

/*
 * Function:        IWDG_SetPrescaler
 * Description:     Sets IWDG Prescaler value.
 * Param:           IWDG_Prescaler: specifies the IWDG Prescaler value.   
 * Return:          None.       
 */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
    /* Check the parameters */
    assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));
    
    /* Disable Prescaler */
    IWDG->PSC &= (uint32_t)(~IWDG_PSC_EN);

    /* Write the prescaler value to the PSC register */
    IWDG->PSC &= (uint32_t)(~IWDG_PSC_PSCNUM);
    IWDG->PSC |= (uint32_t)(IWDG_Prescaler<<IWDG_PSC_PSCNUM_Pos);

    /* Enable Prescaler */
    IWDG->PSC |= (uint32_t)(IWDG_PSC_EN);
}

/*
 * Function:        IWDG_SetDivider
 * Description:     Sets IWDG Divider value.
 * Param:           IWDG_Prescaler: specifies the IWDG Divider value.   
 * Return:          None.       
 */
void IWDG_SetDivider(uint8_t IWDG_Divider)
{
    /* Check the parameters */
    assert_param(IS_IWDG_DIVIDER(IWDG_Divider));
    IWDG->DIV = IWDG_Divider;
}

/*
 * Function:        IWDG_SetTimeout
 * Description:     Sets IWDG timeout value.
 * Param:           IWDG_Reload: specifies the IWDG timeout value.
 * Return : None.
 */
void IWDG_SetTimeout(uint16_t BVAL)
{
  /* Check the parameters */
    assert_param(IS_IWDG_TOValue(BVAL));
    IWDG->TO = BVAL;
}

/*
 * Function:        IWDG_GetCounter
 * Description:     Read the IWDG counter value
 * Param:           None.
 * Return:          The IWDG counter value.  
 */
uint16_t IWDG_GetCounter(void)
{
    return (uint16_t)(IWDG->CNT & IWDG_CNT_CNTNUM);
}

/*
 * Function:        IWDG_ResetCounter
 * Description:     Reset the IWDG counter.
 * Param:           None.
 * Return:          None.
 */
void IWDG_ResetCounter(void)
{
    IWDG->CLR = CLR_KEY_RESET;
}

/*
 * Function:        IWDG_ENCmd
 * Description:     Enables IWDG.
 * Param:           IWDG_EN: IWDG ENABLE.This parameter can be:
 *						      I_PSC_EN,  I_CFG_EN.
 *                  NewState: new state of the IWDG. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.        
 */
void IWDG_ENCmd(uint32_t IWDG_EN,FunctionalState NewState)
{
    uint32_t * enreg_address;
    uint32_t tmreg=0;
   
    /* Check the parameters */
    assert_param(IS_IWDG_CONFIG_EN(IWDG_EN));
    assert_param(IS_FunctionalState_STATE(NewState));
    
    /* Check if IWDG_EN is I_PSC_EN,I_CFG_EN or I_WD_EN*/
    if(IWDG_EN==I_PSC_EN)
    {
      /*Get the value of the Predivider register and its configure */
      enreg_address=(uint32_t *)&IWDG->PSC;
      tmreg=IWDG_PSC_EN;
    }
    else
    {
          if(IWDG_EN==I_CFG_EN)
        {
          /*Get the value of the Configuration register and its configure */
          enreg_address=(uint32_t *)&IWDG->CFG;
          tmreg=IWDG_CFG_EN;
        }
    }

    if (NewState != DISABLE)
    {
      /* Enable watchdog */
      *enreg_address |= tmreg;
    }
    else
    {
      /* Disable watchdog */
      *enreg_address &= (uint32_t)(~tmreg);
    }
}

/*
 * Function:        IWDG_LockCmd
 * Description:     Enables IWDG Lock.
 * Param:           IWDG_LOCK: IWDG Lock Configuration.This parameter can be:
 *						      I_PSC_LOCK,I_CFG_LOCK
 *                  NewState: new state of the IWDG. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.        
 */
void IWDG_LockCmd(uint32_t IWDG_LOCK,FunctionalState NewState)
{
    /*Enable register address*/
      uint32_t * enreg_address;
      uint32_t tmreg=0;
    
    /* Check the parameters */
    assert_param(IS_IWDG_CONFIG_LOCK(IWDG_LOCK));
    assert_param(IS_FunctionalState_STATE(NewState));
    

    
    /* Check if IWDG_LOCK is PSC_LOCK or CFG_LOCK*/
    if(IWDG_LOCK==I_PSC_LOCK)
    {
      /*Get the value of the Predivider register and its configure */
      enreg_address=(uint32_t *)&IWDG->PSC;
      tmreg=IWDG_PSC_LOCK;
    }
    else 
    {
      if(IWDG_LOCK==I_CFG_LOCK)
      {
          /*Get the value of the Configuration register and its configure */
        enreg_address=(uint32_t *)&IWDG->CFG;
        tmreg=IWDG_CFG_LOCK;
      }
      
    }
    
    if (NewState != DISABLE)
    {
      /* Enable watchdog */
      *enreg_address |= (uint32_t)tmreg;
    }
    else
    {
      /* Disable watchdog */
      *enreg_address &= (uint32_t)(~tmreg);
    }
}

/*****END OF FILE*****/