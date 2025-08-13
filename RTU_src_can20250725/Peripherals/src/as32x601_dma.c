                    /*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_dma.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			2024/07/23
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/07/23     1.0     build this module
 * Description:         This file provides firmware functions to manage the functionalities of the DMA peripheral.
 */

#include "as32x601_dma.h"


/* DMA registers Masks */
#define CHCTL_CLEAR_Mask           ((uint32_t)0xFFFFF800)

/* DMA flag Masks*/
#define DMA_MASK_ERR               ((uint32_t)0x10000000)
#define DMA_MASK_FTF               ((uint32_t)0x20000000)
#define DMA_MASK_HTF               ((uint32_t)0x40000000)
#define DMA_MASK_WDG               ((uint32_t)0x80000000)

/*
 * Function:        DMA_DeInit
 * Description:     Deinitializes the DMAy Channelx registers to their default reset
 *                  values.
 * Param:           DMAy_Channelx: where y can be 0 or 1 to select the DMA and
*                   x can be 0 to 15 for DMA1 and 0 to 15 for DMA2 to select the DMA Channel.
 * Return:          None.
 */
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    
    int8_t Channelx;
    DMA_TypeDef * DMAy;
  
    if(DMAy_Channelx<DMA1_Channel0)
    {
        DMAy=DMA0;
    }
    else
    {
        DMAy=DMA1;
    }
    /*Get the dma channel*/
    Channelx=(int8_t)(((uint32_t)((uint32_t)DMAy_Channelx-(uint32_t)DMAy))>>4);
    
    /* Disable the selected DMAy Channelx */
    DMAy->CHEN &= (uint32_t)(~(1UL << Channelx));

    /* Disable the interrput DMAy Channelx */
    DMAy->ERR_INT_MASK |=(1UL<<Channelx);
    DMAy->HTF_INT_MASK |=(1UL<<Channelx);
    DMAy->FTF_INT_MASK |=(1UL<<Channelx);
    DMAy->WDG_INT_MASK |=DMA_WDG_INT_MASK_MASK;

    /* Reset interrupt pending bits for DMAy Channelx */
    DMAy->ERR_INT_RAW |=(1UL<<Channelx);
    DMAy->HTF_INT_RAW |=(1UL<<Channelx);
    DMAy->FTF_INT_RAW |=(1UL<<Channelx);
    DMAy->WDG_INT_RAW |=DMA_WDG_INT_RAW_RAW;

  /* Reset DMAy Channelx configuration register */
    DMAy_Channelx->CHCTL  = 0;
    
    /* Reset DMAy Channelx number of data register */
    DMAy_Channelx->CHCNT = 0;
    
    /* Reset DMAy Channelx peripheral address register */
    DMAy_Channelx->CHPADDR  = 0;
    
    /* Reset DMAy Channelx memory address register */
    DMAy_Channelx->CHMADDR = 0;
}

/*
 * Function:        DMA_Init
 * Description:     Initializes the DMAy Channelx according to the specified arameters in the DMA_InitStruct.
 * Param:           DMAy_Channelx:  where y can be 0 or 1 to select the DMA and
 *                  x can be 0 to 15 for DMA1 and 0 to 15 for DMA2 to select the DMA Channel.
 *                  DMA_InitStruct: pointer to a DMA_InitTypeDef structure that contains
 *                  the configuration information for the specified DMA Channel. 
 * Return:          None.
 */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    assert_param(IS_DMA_DIR(DMA_InitStruct->DMA_DIR));
    assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
    assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
    assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));   
    assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
    assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
    assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
    assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
    assert_param(IS_DMA_M2M_STATE(DMA_InitStruct->DMA_M2M));

    /*--------------------------- DMAy Channelx CHCTL Configuration -----------------*/
    /* Get the DMAy_Channelx CHCTL value */
    tmpreg = DMAy_Channelx->CHCTL;
    /* Clear M2M, PRIO, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
    tmpreg &= CHCTL_CLEAR_Mask;
    /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
    /* Set DIR bit according to DMA_DIR value */
    /* Set CIRC bit according to DMA_Mode value */
    /* Set PINC bit according to DMA_PeripheralInc value */
    /* Set MINC bit according to DMA_MemoryInc value */
    /* Set PSIZE bits according to DMA_PeripheralDataSize value */
    /* Set MSIZE bits according to DMA_MemoryDataSize value */
    /* Set PRIO bits according to DMA_Priority value */
    /* Set the M2M bit according to DMA_M2M value */
    tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
    DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
    DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
    DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;

    /* Write to DMAy Channelx CHCTL */
    DMAy_Channelx->CHCTL = tmpreg;

    /* Write to DMAy Channelx CHCNT */
    DMAy_Channelx->CHCNT = DMA_InitStruct->DMA_BufferSize;

    /*--------------------------- DMAy Channelx CHPADDR Configuration ----------------*/
    /* Write to DMAy Channelx CHPADDR */
    DMAy_Channelx->CHPADDR = DMA_InitStruct->DMA_PeripheralBaseAddr;

    /*--------------------------- DMAy Channelx CHMADDR Configuration ----------------*/
    /* Write to DMAy Channelx CHMADDR */
    DMAy_Channelx->CHMADDR = DMA_InitStruct->DMA_MemoryBaseAddr;
}


/*
 * Function:        DMA_StructInit
 * Description:     Fills each DMA_InitStruct member with its default value.
 * Param:           DMA_InitStruct: pointer to a DMA_InitTypeDef structure which will
 *                  be initialized.
 * Return:          None.
 */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
  /*-------------- Reset DMA init structure parameters values ------------------*/
    /* Initialize the DMA_PeripheralBaseAddr member */
    DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
    /* Initialize the DMA_MemoryBaseAddr member */
    DMA_InitStruct->DMA_MemoryBaseAddr = 0;
    /* Initialize the DMA_DIR member */
    DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralSRC;
    /* Initialize the DMA_BufferSize member */
    DMA_InitStruct->DMA_BufferSize = 0;
    /* Initialize the DMA_PeripheralInc member */
    DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /* Initialize the DMA_MemoryInc member */
    DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;
    /* Initialize the DMA_PeripheralDataSize member */
    DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /* Initialize the DMA_MemoryDataSize member */
    DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    /* Initialize the DMA_Mode member */
    DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
    /* Initialize the DMA_Priority member */
    DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
    /* Initialize the DMA_M2M member */
    DMA_InitStruct->DMA_M2M = DMA_M2M_Disable;
}

/*
 * Function:        DMA_Cmd
 * Description:     Enables or disables the specified DMAy Channelx..
 * Param:           DMAy_Channelx: where y can be 0 or 1 to select the DMA and
 *                  x can be 0 to 15 for DMA1 and 0 to 15 for DMA2 to select the DMA Channel.
 *                  NewState: new state of the DMAy Channelx. This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx,FunctionalState NewState)
{
  /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    assert_param(IS_FunctionalState_STATE(NewState));

    int8_t Channelx;
    DMA_TypeDef * DMAy;
  
    if(DMAy_Channelx<DMA1_Channel0)
    {
        DMAy=DMA0;
    }
    else
    {
        DMAy=DMA1;
    }
    /*Get the dma channel*/
    Channelx=(int8_t)(((uint32_t)((uint32_t)DMAy_Channelx-(uint32_t)DMAy))>>4);

      if (NewState != DISABLE)
    {
      /* Enable the selected DMAy Channelx */
      DMAy->CHEN |= (uint32_t)(1UL << Channelx);
    }
    else
    {
      /* Disable the selected DMAy Channelx */
      DMAy->CHEN &= (uint32_t)(~(1UL << Channelx));
    }
}

/*
 * Function:        DMA_DcoreConfig
 * Description:     Dual-core lock step is enable or disable.
 * Param:           DMAy: where y can be 0 or 1 to select the DMA .
 *                  NewState: new state of the DMAy Channelx. This parameter can be: ENABLE or DISABLE.
 *              
 * Return:          None.
 */
void DMA_DcoreCmd( DMA_TypeDef * DMAy,FunctionalState NewState)
{
  /* Check the parameters */
    assert_param(IS_DMA_TypeDef(DMAy));
    assert_param(IS_FunctionalState_STATE(NewState));

      if (NewState != DISABLE)
    {
      /* Enable dual-core lock step DMAy Channelx */
      DMAy->CCR |= DMA_CCR_DEN;
    }
    else
    {
      /* Disable dual-core lock step DMAy Channelx */
      DMAy->CCR &= (uint32_t)(~(DMA_CCR_DEN));
    }
}

/*
 * Function:        DMA_WDGConfig
 * Description:     Config DMA watch dog.
 * Param:           DMAy: where y can be 0 or 1 to select the DMA .
 *                  Counter:specifies the watchdog counter value.
 *                  This parameter must be a number between 0x00 and 0xFFFF.
 *                  NewState: new state of the DMAy Channelx. This parameter can be: ENABLE or DISABLE. 
 * Return:          None.
 */
void DMA_WDGConfig( DMA_TypeDef * DMAy,uint16_t Counter,FunctionalState NewState)
{
  /* Check the parameters */
    assert_param(IS_DMA_TypeDef(DMAy));
    assert_param(IS_WWDG_COUNTER(Counter));
    assert_param(IS_FunctionalState_STATE(NewState));

    DMAy->CCR |=(Counter<<DMA_CCR_WDCNT_Pos);

      if (NewState != DISABLE)
    {
      /* Enable watch dog DMAy Channelx */
      DMAy->CCR |= DMA_CCR_WDEN;
    }
    else
    {
      /* Disable watch dog DMAy Channelx */
      DMAy->CCR &= (uint32_t)(~(DMA_CCR_WDEN));
    }
}


/*
 * Function:        DMA_ITConfig
 * Description:     Enables or disables the specified DMAy Channelx..
 * Param:           DMAy_Channelx: where y can be 0 or 1 to select the DMA and
 *                  x can be 0 to 15 for DMA1 and 0 to 15 for DMA2 to select the DMA Channel.
 *                  DMA_IT: specifies the DMA interrupts sources to be enabled
 *                  or disabled. 
 *                  This parameter can be any combination of the following values:
 *                  DMA_FTF_IT:  Transfer complete interrupt mask
 *                  DMA_HTF_IT:  Half transfer interrupt mask
 *                  DMA_ERR_IT:  Transfer error interrupt mask
 *                  DMA_WDG_IT:  watch dog interrupt mask
 *                  NewState : new state of the DMAy Channelx. This parameter can be: ENABLE or DISABLE.
 * Return:      None.
 */
 void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT,FunctionalState NewState)
{

    int8_t Channelx;
    DMA_TypeDef * DMAy;
    
  /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    assert_param(IS_DMA_CONFIG_IT(DMA_IT));
    assert_param(IS_FunctionalState_STATE(NewState));

    if(DMAy_Channelx<DMA1_Channel0)
    {
        DMAy=DMA0;
    }
    else
    {
        DMAy=DMA1;
    }
    /*Get the dma channel number*/
    Channelx=(int8_t)(((uint32_t)((uint32_t)DMAy_Channelx-(uint32_t)DMAy))>>4);

      /* Check if the interrput is in ERR_INT,FTF_INT,HTF_INT or WDG_INT */
    if(DMA_IT==DMA_ERR_IT)
    {
      if (NewState != DISABLE)
      {
        /* Enable the error interrput DMAy Channelx */
        DMAy->ERR_INT_MASK &= (uint32_t)(~(1UL << Channelx));
      }
      else
      {
        /* Disable the error interrput  DMAy Channelx */
        DMAy->ERR_INT_MASK |= (uint32_t)(1UL << Channelx);
      }
    }
    else if(DMA_IT==DMA_HTF_IT)
    {
      if (NewState != DISABLE)
      {
        /* Enable the halt transfer interrput DMAy Channelx */
        DMAy->HTF_INT_MASK &= (uint32_t)(~(1UL << Channelx));
      }
      else
      {
        /* Disable the halt transfer interrput  DMAy Channelx */
        DMAy->HTF_INT_MASK |= (uint32_t)(1UL << Channelx);
      }
    }
    else if(DMA_IT==DMA_FTF_IT)
    {
      if (NewState != DISABLE)
      {
        /* Enable the transfer complete interrput DMAy Channelx */
        DMAy->FTF_INT_MASK &= (uint32_t)(~(1UL << Channelx));
      }
      else
      {
        /* Disable the transfer complete interrput  DMAy Channelx */
        DMAy->FTF_INT_MASK |= (uint32_t)(1UL << Channelx);
      }
    }
    else
    {
      if(DMA_IT==DMA_WDG_IT)
      {
          if (NewState != DISABLE)
        {
          /* Enable the watch dog interrput DMAy Channelx */
          DMAy->WDG_INT_MASK &= (uint32_t)(~(DMA_WDG_INT_MASK_MASK));
        }
        else
        {
          /* Disable the watch dog interrput  DMAy Channelx */
          DMAy->WDG_INT_MASK |=DMA_WDG_INT_MASK_MASK;
        }
      }
    
    }
}

/*
 * Function:        DMA_SetCurrDataCounter
 * Description:     Sets the number of data units in the current DMAy Channelx transfer.
 * Param:           DMAy_Channelx: where y can be 0 or 1 to select the DMA and
 *                  x can be 0 to 15 for DMA0 and 0 to 15 for DMA1 to select the DMA Channel.
 *                  DataNumber: The number of data units in the current DMAy Channelx transfer. 
 * Return:          None.
 */
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

  /*--------------------------- DMAy Channelx CHCNT Configuration ---------------*/
    /* Write to DMAy Channelx CHCNT */
    DMAy_Channelx->CHCNT = DataNumber;
}

/*
 * Function:        DMA_GetCurrDataCounter
 * Description:     Returns the number of remaining data units in the curren DMAy Channelx transfer.
 * Param:           DMAy_Channelx: where y can be 0 or 1 to select the DMA and
 *                  x can be 0 to 15 for DMA0 and 0 to 15 for DMA1 to select the DMA Channel.
 * Return:          The number of remaining data units in the current DMAy Channelx transfer.
 */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* Return the number of remaining data units for DMAy Channelx */
    return ((uint16_t)(DMAy_Channelx->CHCNT));
}

/*
 * Function:        DMA_GetFlagStatus
 * Description:     Checks whether the specified DMAy Channelx flag is set or not.
 * Param:           DMAy: where y can be 0 or 1 to select the DMA .
 *                  DMA_FLAG_ERRx: Channelx error flag
 *                  DMA_FLAG_FTFx: Channelx tranfer commplete flag
 *                  DMA_FLAG_HTFx: Channelx tranfer commplete flag
 *                  DMA_FLAG_WDG:  watch dog interrput flag.
 *                  whwere x can 0 t0 15 to select thw DMA Channel.
 * Returns:         The new state of DMAy_FLAG (SET or RESET).
 */
 FlagStatus DMA_GetFlagStatus(DMA_TypeDef* DMAy,uint32_t DMA_FLAG)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_DMA_FLAG(DMA_FLAG));
    assert_param(IS_DMA_TypeDef(DMAy));
  
    /* Check if the flag is in ERR_INT_RAW,FTF_INT_RAW,HTF_INT_RAW or WDG_INT_RAW */
    if((DMA_FLAG&DMA_MASK_ERR)==DMA_MASK_ERR)
    {
      /* Get DMAy ERR_INT_RAW register value */
      tmpreg=DMAy->ERR_INT_RAW;
    }
    else if((DMA_FLAG&DMA_MASK_FTF)==DMA_MASK_FTF)
    {
      /* Get DMAy FTF_INT_RAW register value*/
      tmpreg=DMAy->FTF_INT_RAW;
    }
    else if((DMA_FLAG&DMA_MASK_HTF)==DMA_MASK_HTF)
    {
      /* Get DMAy HTF_INT_RAW register value*/
      tmpreg=DMAy->HTF_INT_RAW;
    }
    else
    {
      if((DMA_FLAG&DMA_MASK_WDG)==DMA_MASK_WDG)
      {
      /* Get DMAy WDG_INT_RAW register value */
        tmpreg = DMAy->WDG_INT_RAW;
      }
    }

    /* Check the status of the specified DMAy flag */
    if ((tmpreg & DMA_FLAG) != (uint32_t)RESET)
    {
      /* DMAy_FLAG is set */
      bitstatus = SET;
    }
    else
    {
      /* DMA FLAG is reset */
      bitstatus = RESET;
    }
    
    /* Return the DMAy_FLAG status */
    return  bitstatus;
}

/*
 * Function:        DMA_ClearFlag
 * Description:     Checks whether the specified DMAy Channelx flag is set or not.
 * Param:           DMAy: where y can be 0 or 1 to select the DMA .
 *                  DMA_FLAG_ERRx: Channelx error flag
 *                  DMA_FLAG_FTFx: Channelx tranfer commplete flag
 *                  DMA_FLAG_HTFx: Channelx tranfer commplete flag
 *                  DMA_FLAG_WDG:  watch dog interrput flag.
 *                  whwere x can 0 t0 15 to select thw DMA Channel.
 * Returns:         None.
 */
void DMA_ClearFlag(DMA_TypeDef* DMAy,uint32_t DMA_FLAG)
{
    /* Check the parameters */
    assert_param(IS_DMA_CLEAR_FLAG(DMA_FLAG));
    assert_param(IS_DMA_TypeDef(DMAy));
  
    /* Check if the flag is in ERR_INT_RAW,FTF_INT_RAW,HTF_INT_RAW or WDG_INT_RAW */
    if((DMA_FLAG&DMA_MASK_ERR)==DMA_MASK_ERR)
    {
      /* Clear DMA ERR_INT_RAW register value */
      DMAy->ERR_INT_RAW |= DMA_FLAG;
    }
    else if((DMA_FLAG&DMA_MASK_FTF)==DMA_MASK_FTF)
    {
      /* Clear DMA FTF_INT_RAW register value*/
      DMAy->FTF_INT_RAW |= DMA_FLAG;
    }
    else if((DMA_FLAG&DMA_MASK_HTF)==DMA_MASK_HTF)
    {
      /* Clear DMA HTF_INT_RAW register value*/
      DMAy->HTF_INT_RAW|= DMA_FLAG;
    }
    else
    {
      if((DMA_FLAG&DMA_MASK_WDG)==DMA_MASK_WDG)
      {
      /* Clear DMA WDG_INT_RAW register value */
        DMAy->WDG_INT_RAW|= DMA_FLAG;
      }
    }
}


/*
 * Function:        DMA_GetITStatus
 * Description:     Checks whether the specified DMAy Channelx interrupt is set or not.
 * Param:           DMAy: where y can be 0 or 1 to select the DMA .
 *                  DMA_IT_ERRx: Channelx error interrupt
 *                  DMA_IT_FTFx: Channelx tranfer commplete interrupt
 *                  DMA_IT_HTFx: Channelx tranfer commplete interrupt
 *                  DMA_IT_WDG:  watch dog interrput interrupt.
 *                  whwere x can 0 t0 15 to select thw DMA Channel.
 * Returns:         The new state of DMAy_IT (SET or RESET).
 */
 ITStatus DMA_GetITStatus(DMA_TypeDef* DMAy,uint32_t DMAy_IT)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_DMAy_IT(DMAy_IT));
    assert_param(IS_DMA_TypeDef(DMAy));
  
    /* Check if the flag is in ERR_INT_STATUS,FTF_INT_STATUS,HTF_INT_STATUS or WDG_INT_STATUS */
    if((DMAy_IT&DMA_MASK_ERR)==DMA_MASK_ERR)
    {
      /* Get DMAy ERR_INT_STATUS register value */
      tmpreg=DMAy->ERR_INT_STATUS;
    }
    else if((DMAy_IT&DMA_MASK_FTF)==DMA_MASK_FTF)
    {
      /* Get DMAy FTF_INT_STATUS register value*/
      tmpreg=DMAy->FTF_INT_STATUS;
    }
    else if((DMAy_IT&DMA_MASK_HTF)==DMA_MASK_HTF)
    {
      /* Get DMAy HTF_INT_STATUS register value*/
      tmpreg=DMAy->HTF_INT_STATUS;
    }
    else
    {
      if((DMAy_IT&DMA_MASK_WDG)==DMA_MASK_WDG)
      {
      /* Get DMAy WDG_INT_STATUS register value */
        tmpreg = DMAy->WDG_INT_STATUS;
      }
    }

    /* Check the status of the specified DMAy flag */
    if ((tmpreg & DMAy_IT) != (uint32_t)RESET)
    {
      /* DMAy_IT is set */
      bitstatus = SET;
    }
    else
    {
      /* DMAy_IT is reset */
      bitstatus = RESET;
    }
    
    /* Return the DMAy_IT status */
    return  bitstatus;
}

/*
 * Function:        DMA_ClearITPendingBit
 * Description:     Checks whether the specified DMAy Channelx interrupt is set or not.
 * Param:           DMAy: where y can be 0 or 1 to select the DMA .
 *                  DMA_ERR_ITx: Channelx error interrupt
 *                  DMA_FTF_ITx: Channelx tranfer commplete interrupt
 *                  DMA_HTF_ITx: Channelx tranfer commplete interrupt
 *                  DMA_WDG_IT:  watch dog interrput.
 *                  whwere x can 0 t0 15 to select thw DMA Channel.
 * Returns:         None.
 */
void DMA_ClearITPendingBit(DMA_TypeDef* DMAy,uint32_t DMAy_IT)
{
    /* Check the parameters */
    assert_param(IS_DMA_CLEAR_IT(DMAy_IT));
    assert_param(IS_DMA_TypeDef(DMAy));
  
    /* Check if the flag is in ERR_INT_STATUS,FTF_INT_STATUS,HTF_INT_STATUS or WDG_INT_STATUS */
    if((DMAy_IT&DMA_MASK_ERR)==DMA_MASK_ERR)
    {
      /* Clear DMA ERR_INT_STATUS register value */
      DMAy->ERR_INT_RAW |= DMAy_IT;
    }
    else if((DMAy_IT&DMA_MASK_FTF)==DMA_MASK_FTF)
    {
      /* Clear DMA FTF_INT_STATUS register value*/
      DMAy->FTF_INT_RAW |= DMAy_IT;
    }
    else if((DMAy_IT&DMA_MASK_HTF)==DMA_MASK_HTF)
    {
      /* Clear DMA HTF_INT_STATUS register value*/
      DMAy->HTF_INT_RAW |= DMAy_IT;
    }
    else
    {
      if((DMAy_IT&DMA_MASK_WDG)==DMA_MASK_WDG)
      {
      /* Clear DMA WDG_INT_STATUS register value */
        DMAy->WDG_INT_RAW|= DMAy_IT;
      }
    }
}

/*
 * Function:        DMA_PeriphIF
 * Description:     Config the number of Peripheral Interface in DMAy Channelx..
 * Param:           DMAy_Channelx: where y can be 0 or 1 to select the DMA and
 *                  x can be 0 to 15 for DMA1 and 0 to 15 for DMA2 to select the DMA Channel.
 *                  IF_Number: DMAy Channelx Peripheral Interface number.
 *                  This parameter can be any combination of the following values *:
 *			            TIM0_IF            TIM1_IF 
 *                  ADC0_IF            ADC2_IF
 *                  ADC1_IF            SPI3_IF
 *                  SPI0_IF            SPI4_IF
 *                  SPI1_IF            SPI5_IF
 *                  SPI2_IF            USART4_IF
 *                  USART0_IF          USART5_IF
 *                  USART1_IF          USART6_IF
 *                  USART2_IF          USART7_IF
 *                  USART3_IF          TIM5_IF
 *                  TIM2_IF            TIM6_IF
 *                  TIM3_IF            TIM7_IF
 *                  TIM4_IF        
 *                                                                              
 *              
 * Return:          None.
 */
void DMA_PeriphIF(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t IF_Number)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    assert_param(IS_PeriphInterface_Number(IF_Number));

    int8_t Channelx;
    DMA_TypeDef * DMAy;
  
    if(DMAy_Channelx<DMA1_Channel0)
    {
        DMAy=DMA0;
    }
    else
    {
        DMAy=DMA1;
    }
    /*Get the dma channel*/
    Channelx=(int8_t)(((uint32_t)((uint32_t)DMAy_Channelx-(uint32_t)DMAy))>>4);
    
    if(Channelx<8)
    {
    DMAy->PTCH0|=(IF_Number<<(Channelx*4));  
    }
    else
    {
    DMAy->PTCH1|=(IF_Number<<((Channelx-8)*4)); 
    }
  }

/*****END OF FILE*****/

















