/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_mpu.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2024/08/01
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/13     1.0     build this module
 * Description:         This file provides firmware functions to manage the functionalities of the MPU module.
 */

#include "as32x601_mpu.h"

/* MPU flag Masks*/
#define MPU_MASK_WPTS               ((uint32_t)0x10000000)
#define MPU_MASK_RPTS               ((uint32_t)0x20000000)

/* Private function prototypes */
static uint32_t GetChannelx(MPU_Channel_TypeDef * MPUy_Channelx);

/*
 * Function:        WWDG_SetPrescaler
 * Description:     The address protection range is specified.
 * Param:           MPUy_Channelx: where y can be 0 to 4 to select the MPU and
 *                  x can be 0 to 15 to select the MPU Channel.
 *                  SADDR: Start of address
 *                  EADDR: End of address
 * Return:          None.       
 */
void MPU_SetAddressRange(MPU_Channel_TypeDef * MPUy_Channelx,uint32_t SADDR,uint32_t EADDR)
{
    /* Check the parameters */
    assert_param(IS_MPU_ALL_PERIPH(MPUy_Channelx));
    assert_param(SADDR < EADDR);

    /* Set start of address*/
    MPUy_Channelx->SADDR = SADDR;
    /* Set end of address*/
    MPUy_Channelx->EADDR = EADDR;
}

/*
 * Function:        MPUCmd
 * Description:     Enables or Disable MPU Channel.
 * Param:           MPUy_Channelx: where y can be 0 to 4 to select the MPU and
 *                  x can be 0 to 15 to select the MPU Channel.
 *                  NewState: new state of the MPU. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.       
 */
void MPU_Cmd(MPU_Channel_TypeDef * MPUy_Channelx,FunctionalState NewState)
{
    uint32_t Channelx;
    uint32_t *enreg_address;
    /* Check the parameters */
    assert_param(IS_MPU_ALL_PERIPH(MPUy_Channelx));
    assert_param(IS_FunctionalState_STATE(NewState));

    if((MPUy_Channelx>=MPU0_Channel0)&&(MPUy_Channelx<MPU1_Channel0))
    {
        /* Get the address of MPU_PTEN Register */
        enreg_address=(uint32_t *)&(MPU0_IBUS->PTEN);
    }
    else if ((MPUy_Channelx>=MPU1_Channel0)&&(MPUy_Channelx<MPU2_Channel0))
    {
        /* Get the address of MPU_PTEN Register */
        enreg_address=(uint32_t *)&(MPU1_DBUS->PTEN);
    }
    else if ((MPUy_Channelx>=MPU2_Channel0)&&(MPUy_Channelx<MPU3_Channel0))
    {
        /* Get the address of MPU_PTEN Register */
        enreg_address=(uint32_t *)&(MPU2_PBUS->PTEN);
    }
     else if ((MPUy_Channelx>=MPU3_Channel0)&&(MPUy_Channelx<MPU4_Channel0))
    {
        /* Get the address of MPU_PTEN Register */
        enreg_address=(uint32_t *)&(MPU3_DMA0->PTEN);
    }
    else
    {
        /* Get the address of MPU_PTEN Register */
        enreg_address=(uint32_t *)&(MPU4_DMA1->PTEN);
    }

    /* Get the channel of MPU*/
    Channelx=GetChannelx(MPUy_Channelx);

    /* Set or Reset the MPU Channel */
    if (NewState != DISABLE)
    {
        /* Enable MPU Channel*/
        *enreg_address |= (uint32_t)(1U<<Channelx);
    }
    else
    {
        /* Disable MPU Channel */
        *enreg_address &= (uint32_t)(~(1U<<Channelx));
    }
}

/*
 * Function:        MPU_WriteProtectCmd
 * Description:     Enables or Disable MPU Write Protect.
 * Param:           MPUy_Channelx: where y can be 1 to 4 to select the MPU and
 *                  x can be 0 to 15 to select the MPU Channel.
 *                  NewState: new state of the MPU. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.       
 */
void MPU_WriteProtectCmd(MPU_Channel_TypeDef * MPUy_Channelx,FunctionalState NewState)
{
    uint32_t Channelx;
    uint32_t *enreg_address;
    /* Check the parameters */
    assert_param(IS_MPU_LIST1_PERIPH(MPUy_Channelx));
    assert_param(IS_FunctionalState_STATE(NewState));

    if ((MPUy_Channelx>=MPU1_Channel0)&&(MPUy_Channelx<MPU2_Channel0))
    {
        /* Get the address of MPU_WPTEN Register */
        enreg_address=(uint32_t *)&(MPU1_DBUS->WPTEN);
    }
    else if ((MPUy_Channelx>=MPU2_Channel0)&&(MPUy_Channelx<MPU3_Channel0))
    {
        /* Get the address of MPU_WPTEN Register */
        enreg_address=(uint32_t *)&(MPU2_PBUS->WPTEN);
    }
     else if ((MPUy_Channelx>=MPU3_Channel0)&&(MPUy_Channelx<MPU4_Channel0))
    {
        /* Get the address of MPU_WPTEN Register */
        enreg_address=(uint32_t *)&(MPU3_DMA0->WPTEN);
    }
    else
    {
        /* Get the address of MPU_WPTEN Register */
        enreg_address=(uint32_t *)&(MPU4_DMA1->WPTEN);
    }

    /* Get the channel of MPU*/
    Channelx=GetChannelx(MPUy_Channelx);

    /* Set or Reset the MPU Channel */
    if (NewState != DISABLE)
    {
        /* Enable MPU Write Protect*/
        *enreg_address |= (uint32_t)(1U<<Channelx);
    }
    else
    {
        /* Disable MPU Write Protect */
        *enreg_address &= (uint32_t)(~(1U<<Channelx));
    }
}


/*
 * Function:        MPU_ReadProtectCmd
 * Description:     Enables or Disable MPU Read Protect.
 * Param:           MPUy_Channelx: where y can be 1 to 4 to select the MPU and
 *                  x can be 0 to 15 to select the MPU Channel.
 *                  NewState: new state of the MPU. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.       
 */
void MPU_ReadProtectCmd(MPU_Channel_TypeDef * MPUy_Channelx,FunctionalState NewState)
{
    uint32_t Channelx;
    uint32_t *enreg_address;
    /* Check the parameters */
    assert_param(IS_MPU_ALL_PERIPH(MPUy_Channelx));
    assert_param(IS_FunctionalState_STATE(NewState));

    if ((MPUy_Channelx>=MPU0_Channel0)&&(MPUy_Channelx<MPU1_Channel0))
    {
        /* Get the address of MPU_RPTEN Register */
        enreg_address=(uint32_t *)&(MPU0_IBUS->RPTEN);
    }
    else if ((MPUy_Channelx>=MPU1_Channel0)&&(MPUy_Channelx<MPU2_Channel0))
    {
        /* Get the address of MPU_RPTEN Register */
        enreg_address=(uint32_t *)&(MPU1_DBUS->RPTEN);
    }
    else if ((MPUy_Channelx>=MPU2_Channel0)&&(MPUy_Channelx<MPU3_Channel0))
    {
        /* Get the address of MPU_RPTEN Register */
        enreg_address=(uint32_t *)&(MPU2_PBUS->RPTEN);
    }
     else if ((MPUy_Channelx>=MPU3_Channel0)&&(MPUy_Channelx<MPU4_Channel0))
    {
        /* Get the address of MPU_RPTEN Register */
        enreg_address=(uint32_t *)&(MPU3_DMA0->RPTEN);
    }
    else
    {
        /* Get the address of MPU_RPTEN Register */
        enreg_address=(uint32_t *)&(MPU4_DMA1->RPTEN);
    }

    /* Get the channel of MPU*/
    Channelx=GetChannelx(MPUy_Channelx);

    /* Set or Reset the MPU Channel */
    if (NewState != DISABLE)
    {
        /* Enable MPU Read Protect*/
        *enreg_address |= (uint32_t)(1U<<Channelx);
    }
    else
    {
        /* Disable MPU Read Protect */
        *enreg_address &= (uint32_t)(~(1U<<Channelx));
    }
}

/*
 * Function:        MPU_GetFlagStatus
 * Description:     Checks whether the specified MPUy Channelx flag is set or not.
 * Param:           MPUy: where y can be 0 to 4 to select the MPU .
 *                  MPU_FLAG_RPTSx: Channelx read protect flag
 *                  MPU_FLAG_WPTSx: Channelx write protect flag
 * Returns:         The new state of MPU_FLAG (SET or RESET).
 */
FlagStatus MPU_GetFlagStatus(void * MPUy,uint32_t MPU_FLAG)
{

    FlagStatus bitstatus = RESET;
    uint32_t* ptsreg_adress = 0;
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_MPU_ALL_TypeDef(MPUy));
    assert_param(IS_MPU_FLAG(MPU_FLAG));

    if((MPU_IPort_TypeDef *)MPUy == MPU0_IBUS)
    {
        /* Get the address of MPU_WPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU0_IBUS->RPTS);
    }
    else if((MPU_DPort_TypeDef *)MPUy == MPU1_DBUS)
    {
        /* Get the address of MPU_RPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU1_DBUS->RPTS);
    }
    else if((MPU_DPort_TypeDef *)MPUy == MPU2_PBUS)
    {
        /* Get the address of MPU_RPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU2_PBUS->RPTS);
    }
    else if((MPU_DPort_TypeDef *)MPUy == MPU3_DMA0)
    {
        assert_param(IS_MPU_DMA_FLAG(MPU_FLAG));
        /* Get the address of MPU_RPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU3_DMA0->RPTS);
    }
    else
    {
        assert_param(IS_MPU_DMA_FLAG(MPU_FLAG));
        /* Get the address of MPU_RPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU4_DMA1->RPTS);
    }

    /* Check if MPU_FLAG is MPU_FLAG_RPTSx or MPU_FLAG_WPTSx */
    if ((MPU_FLAG & MPU_MASK_WPTS ) ==MPU_MASK_WPTS)
    {
        assert_param(IS_MPU_LIST1_TypeDef(MPUy));
        /* Get the value of MPU_WPTS Register */
        tmpreg = *(ptsreg_adress-1);
    }

    if ((MPU_FLAG & MPU_MASK_RPTS ) ==MPU_MASK_RPTS)
    {
        /* Get the value of MPU_RPTS Register */
        tmpreg = *ptsreg_adress;
    }

    /* Check the status of the specified MPUy flag */
    if ((tmpreg & MPU_FLAG) != (uint32_t)RESET)
    {
        /* MPU FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* MPU FLAG is reset */
        bitstatus = RESET;
    }
    
    /* Return the MPU_FLAG status */
    return  bitstatus;
}

/*
 * Function:        MPU_ClearFlag
 * Description:     Clear MPUy Channelx flag.
 * Param:           MPUy: where y can be 0 to 4 to select the MPU .
 *                  MPU_FLAG_RPTSx: Channelx read protect flag
 *                  MPU_FLAG_WPTSx: Channelx write protect flag
 * Returns:         None.
 */
void MPU_ClearFlag(void * MPUy,uint32_t MPU_FLAG)
{

    uint32_t* ptsreg_adress = 0;

    /* Check the parameters */
    assert_param(IS_MPU_ALL_TypeDef(MPUy));
    assert_param(IS_MPU_FLAG(MPU_FLAG));

    if((MPU_IPort_TypeDef *)MPUy == MPU0_IBUS)
    {
        /* Get the address of MPU_WPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU0_IBUS->RPTS);
    }
    else if((MPU_DPort_TypeDef *)MPUy == MPU1_DBUS)
    {
        /* Get the address of MPU_RPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU1_DBUS->RPTS);
    }
    else if((MPU_DPort_TypeDef *)MPUy == MPU2_PBUS)
    {
        /* Get the address of MPU_RPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU2_PBUS->RPTS);
    }
    else if((MPU_DPort_TypeDef *)MPUy == MPU3_DMA0)
    {
        assert_param(IS_MPU_DMA_FLAG(MPU_FLAG));
        /* Get the address of MPU_RPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU3_DMA0->RPTS);
    }
    else
    {
        assert_param(IS_MPU_DMA_FLAG(MPU_FLAG));
        /* Get the address of MPU_RPTS Register */
        ptsreg_adress = (uint32_t *)&(MPU4_DMA1->RPTS);
    }

    /* Check if MPU_FLAG is MPU_FLAG_RPTSx or MPU_FLAG_WPTSx */
    if ((MPU_FLAG & MPU_MASK_WPTS ) ==MPU_MASK_WPTS)
    {
        assert_param(IS_MPU_LIST1_TypeDef(MPUy));
        /* Clear MPU_WPTS Register */
        *(ptsreg_adress-1)|= (uint32_t)(0xFFFFU&MPU_FLAG);
    }

    if ((MPU_FLAG & MPU_MASK_RPTS ) ==MPU_MASK_RPTS)
    {
        /* Clear MPU_RPTS Register */
        *ptsreg_adress |= (uint32_t)(0xFFFFU&MPU_FLAG);
    }

}


/*
 * Function:        GetChannelx
 * Description:     Returns the curren MPUy Channelx.
 * Param:           MPUy_Channelx: where y can be 1 to 4 to select the MPU and
 *                  x can be 0 to 15 to select the MPU Channel.
 * Return:          The value of Channelx.
 */
static uint32_t GetChannelx(MPU_Channel_TypeDef * MPUy_Channelx)
{
    uint32_t Channelx;
    /* Check the parameters */
    assert_param(IS_MPU_ALL_PERIPH(MPUy_Channelx));

    if((MPUy_Channelx>=MPU0_Channel0)&&(MPUy_Channelx<MPU1_Channel0))
    {
        /* Get the channel of MPU0*/
        Channelx=(uint32_t)((uint32_t)((uint32_t)MPUy_Channelx - (uint32_t)MPU0_Channel0)>>3);
    }
    else if ((MPUy_Channelx>=MPU1_Channel0)&&(MPUy_Channelx<MPU2_Channel0))
    {
        /* Get the channel of MPU1*/
        Channelx=(uint32_t)((uint32_t)((uint32_t)MPUy_Channelx - (uint32_t)MPU1_Channel0)>>3);
    }
    else if ((MPUy_Channelx>=MPU2_Channel0)&&(MPUy_Channelx<MPU3_Channel0))
    {
        /* Get the channel of MPU2*/
        Channelx=(uint32_t)((uint32_t)((uint32_t)MPUy_Channelx - (uint32_t)MPU2_Channel0)>>3);
    }
     else if ((MPUy_Channelx>=MPU3_Channel0)&&(MPUy_Channelx<MPU4_Channel0))
    {
        /* Get the channel of MPU3*/
        Channelx=(uint32_t)((uint32_t)((uint32_t)MPUy_Channelx - (uint32_t)MPU3_Channel0)>>3);
    }
    else
    {
        /* Get the channel of MPU4*/
        Channelx=(uint32_t)((uint32_t)((uint32_t)MPUy_Channelx - (uint32_t)MPU4_Channel0)>>3);
    }

    return Channelx;
}



/*****END OF FILE*****/