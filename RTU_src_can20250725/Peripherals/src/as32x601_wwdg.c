/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_wwdg.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2024/08/01
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/01     1.0     build this module
 * Description:         This file provides firmware functions to manage the functionalities of the WWDG module.
 */

#include "as32x601_wwdg.h"

/* CLR register bit mask*/
#define CLR_KEY_RESET    ((uint32_t)(0x2f3e5d8a))

/*
 * Function:        WWDG_SetPrescaler
 * Description:     Sets WWDG Prescaler value.
 * Param:           WWDGy: where y can be 0 or 1 to select the WWDG .
 *                  WWDG_Prescaler: specifies the WWDG Prescaler value.
 * Return:          None.       
 */
void WWDG_SetPrescaler(WWDG_TypeDef* WWDGy,uint8_t WWDG_Prescaler)
{
    /* Check the parameters */
    assert_param(IS_WWDG_TypeDef(WWDGy));
    assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));

    /* Disable Prescaler */
    WWDGy->PSC &= (uint32_t)(~WWDG_PSC_EN);

    /* Set Prescaler value.*/
    WWDGy->PSC &=(uint32_t)(~WWDG_PSC_PSCNUM);
    WWDGy->PSC |=(uint32_t)(WWDG_Prescaler<<WWDG_PSC_PSCNUM_Pos);

    /* Enable Prescaler */
    WWDGy->PSC |= (uint32_t)WWDG_PSC_EN;
}

/*
 * Function:        WWDG_GetBKStatus
 * Description:     Checks whether the specified WWDGy Channelx Bark is set or not.
 * Param:           WWDGy: where y can be 0 or 1 to select the WWDG.
 *                  BK_Flag: WWDG Bark flag.
 *                  This parameter can be any combination of the following values:
 *                  WWDG_FLAG_BK0
 *                  WWDG_FLAG_BK1
 *                  WWDG_FLAG_BK2
 *                  WWDG_FLAG_BK3              
 * Return:          The new state of WWDGy_FLAG (SET or RESET).
 */

FlagStatus WWDG_GetBKStatus(WWDG_TypeDef* WWDGy,uint32_t BK_Flag)
{
    /* Check the parameters */
    assert_param(IS_WWDG_TypeDef(WWDGy));
    assert_param(IS_WWDG_BRAK_FLAG(BK_Flag));
    if ((WWDGy->DSTA & BK_Flag)!= (uint32_t)RESET)
    {
      /* The specified WWDG Channelx Bark is set */
      return SET;
    }
    else
    {
      /* The specified WWDG Channelx Bark is reset */
      return RESET;
    }
}	


/*
 * Function:        WWDG_SetDivider
 * Description:     Sets WWDG Divider value.
 * Param:           WWDGy_Channelx: where y can be 0 or 1 to select the WWDG and
 *                  x can be 0 to 3 for WWDG1 and 0 to 3 for WWDG1 to select the WWDG Channel.
 *                  WWDG_Divider: specifies the WWDG Divider value.   
 * Return:          None.       
 */
void WWDG_SetDivider(WWDG_Channel_TypeDef* WWDGy_Channelx ,uint8_t WWDG_Divider)
{
    /* Check the parameters */
    assert_param(IS_WWDG_ALL_PERIPH(WWDGy_Channelx));
    assert_param(IS_WWDG_DIVIDER(WWDG_Divider));

    WWDGy_Channelx->DIV = WWDG_Divider;
}

/*
 * Function:        WWDG_SetTimeout
 * Description:     WWDGy_Channelx: where y can be 0 or 1 to select the WWDG and
 *                  x can be 0 to 3 for WWDG1 and 0 to 3 for WWDG1 to select the WWDG Channel.
 *                  Sets WWDG timeout value.
 * Param:           BVAL: specifies the WWDG timeout value.
 * Return:          None.
 */
void WWDG_SetTimeout(WWDG_Channel_TypeDef* WWDGy_Channelx,uint16_t BVAL)
{
  /* Check the parameters */
    assert_param(IS_WWDG_ALL_PERIPH(WWDGy_Channelx));
    assert_param(IS_WWDG_TOValue(BVAL));
    WWDGy_Channelx->TO = BVAL;
}

/*
 * Function:        WWDG_GetCounter
 * Description:     Read the WWDG counter value
 * Param:           WWDGy_Channelx: where y can be 0 or 1 to select the WWDG and
 *                  x can be 0 to 3 for WWDG1 and 0 to 3 for WWDG1 to select the WWDG Channel.
 * Return:          The WWDG counter value.  
 */
uint16_t WWDG_GetCounter(WWDG_Channel_TypeDef* WWDGy_Channelx)
{
    /* Check the parameters */
    assert_param(IS_WWDG_ALL_PERIPH(WWDGy_Channelx));
    return (uint16_t)(WWDGy_Channelx->CNT & WWDG_CNT_CNTNUM);
}

/*
 * Function:        WWDG_ResetCounter
 * Description:     Reset the WWDG counter.
 * Param:           WWDGy_Channelx: where y can be 0 or 1 to select the WWDG and
 *                  x can be 0 to 3 for WWDG1 and 0 to 3 for WWDG1 to select the WWDG Channel.
 * Return:          None.
 */
void WWDG_ResetCounter(WWDG_Channel_TypeDef* WWDGy_Channelx)
{
    /* Check the parameters */
    assert_param(IS_WWDG_ALL_PERIPH(WWDGy_Channelx));
    WWDGy_Channelx->CLR = CLR_KEY_RESET;
}

/*
 * Function:        WWDG_ENCmd
 * Description:     Enables WWDG.
 * Param:           WWDGy_Channelx: where y can be 0 or 1 to select the WWDG and
 *                  x can be 0 to 3 for WWDG1 and 0 to 3 for WWDG1 to select the WWDG Channel.
 *				          WWDG_EN: WWDG ENABLE.This parameter can be:
						        W_PSC_EN,  W_CFG_EN,   W_WD_EN.
 *                  NewState: new state of the WWDG. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.        
 */
void WWDG_ENCmd(WWDG_Channel_TypeDef* WWDGy_Channelx,uint32_t WWDG_EN,FunctionalState NewState)
{
    uint32_t * enreg_address;
    uint32_t tmreg=0;
	  WWDG_TypeDef * WWDGy; 
   
    /* Check the parameters */
    assert_param(IS_WWDG_ALL_PERIPH(WWDGy_Channelx));
    assert_param(IS_WWDG_CONFIG_EN(WWDG_EN));
    assert_param(IS_FunctionalState_STATE(NewState));
    
    /* Check the WWDGy is WWDG0 or WWDG1*/
      if(WWDGy_Channelx<WWDG1_Channel0)
    {
        WWDGy=WWDG0;
    }
    else
    {
        WWDGy=WWDG1;
    }
    
    /* Check if WWDG_EN is PSC_EN,CFG_EN or WD_EN*/
    if(WWDG_EN==W_PSC_EN)
    {
      /*Get the value of the Predivider register and its configure */
      enreg_address=(uint32_t *)&WWDGy->PSC;
      tmreg=WWDG_PSC_EN;
    }
    else if(WWDG_EN==W_CFG_EN)
    {
      /*Get the value of the Configuration register and its configure */
      enreg_address=(uint32_t *)&WWDGy_Channelx->CFG;
      tmreg=WWDG_CFG_EN;
    }
    else
    {
      if(WWDG_EN==W_WD_EN)
      {
        /*Get the value of the Window Counter register and its configure */
        enreg_address=(uint32_t *)&WWDGy_Channelx->WD;
        tmreg=WWDG_WD_WDEN;		  
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
 * Function:        WWDG_LockCmd
 * Description:     Enables WWDG Lock.
 * Param:           WWDGy_Channelx: where y can be 0 or 1 to select the WWDG and
 *                  x can be 0 to 3 for WWDG1 and 0 to 3 for WWDG1 to select the WWDG Channel.
 *				          WWDG_LOCK: WWDG Lock Configuration.This parameter can be:
 *					        W_PSC_LOCK,W_CFG_LOCK
 *                  NewState: new state of the WWDG. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.        
 */
void WWDG_LockCmd(WWDG_Channel_TypeDef* WWDGy_Channelx,uint32_t WWDG_LOCK,FunctionalState NewState)
{
	/*Enable register address*/
    uint32_t * enreg_address;
    uint32_t tmreg=0;
	  WWDG_TypeDef *WWDGy; 
   
    /* Check the parameters */
    assert_param(IS_WWDG_ALL_PERIPH(WWDGy_Channelx));
    assert_param(IS_WWDG_CONFIG_LOCK(WWDG_LOCK));
    assert_param(IS_FunctionalState_STATE(NewState));
    
    /* Check the WWDGy is WWDG0 or WWDG1*/
      if(WWDGy_Channelx<WWDG1_Channel0)
    {
          WWDGy=WWDG0;
    }
    else
    {
          WWDGy=WWDG1;
    }
    
    /* Check if WWDG_LOCK is PSC_LOCK or CFG_LOCK*/
    if(WWDG_LOCK==W_PSC_LOCK)
    {
      /*Get the value of the Predivider register and its configure */
      enreg_address=(uint32_t *)&WWDGy->PSC;
      tmreg=WWDG_PSC_LOCK;
    }
    else 
    {
      if(WWDG_LOCK==W_CFG_LOCK)
      {
          /*Get the value of the Configuration register and its configure */
        enreg_address=(uint32_t *)&WWDGy_Channelx->CFG;
        tmreg=WWDG_CFG_LOCK;
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

/*
 * Function:        WWDG_SetWDCNT
 * Description:     WWDGy_Channelx: where y can be 0 or 1 to select the WWDG and
 *                  x can be 0 to 3 for WWDG1 and 0 to 3 for WWDG1 to select the WWDG Channel.
 *                  Sets WWDG Window Counter value.
 * Param:           BVAL: specifies the WWDG Window Counter value.
 * Return:          None.
 */
void WWDG_SetWDCNT(WWDG_Channel_TypeDef* WWDGy_Channelx,uint16_t WindowCount)
{
  /* Check the parameters */
    assert_param(IS_WWDG_ALL_PERIPH(WWDGy_Channelx));
    assert_param(IS_WWDG_WDCNTValue(WindowCount));

    /* Disable Window Counter */
    WWDGy_Channelx->WD &= (uint32_t)(~WWDG_WD_WDEN);

    /* Set the Window counter value */
    WWDGy_Channelx->WD &= (uint32_t)(~WWDG_WD_WDCNT);
    WWDGy_Channelx->WD |= (uint32_t)(WindowCount<<WWDG_WD_WDCNT_Pos);
    
    /* Enable Window Counter*/
    WWDGy_Channelx->WD |= (uint32_t)(WWDG_WD_WDEN);
}


/*****END OF FILE*****/