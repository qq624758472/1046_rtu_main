/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_timer.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:			2023/08/08
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2023/08/08     1.0     build this module
 * Description:     This file provides firmware functions to manage the functionalities of the TIMER peripheral.
 */

#include <stdlib.h>
#include "as32x601_timer.h"



/* ---------------------- TIM registers bit mask ------------------------ */
#define SMCR_ETR_MASK      ((uint32_t)0x000000FF) 
#define CCMR_OFFSET        ((uint32_t)0x00000018)
#define CCER_CCE_SET       ((uint32_t)0x00000001)  
#define	CCER_CCNE_SET      ((uint32_t)0x00000004) 
#define CCMR_OC135M_MASK    ((uint32_t)0xFFF1FF8F)
#define CCMR_OC246M_MASK    ((uint32_t)0xF1FF8FFF) 

/* Private function prototypes -----------------------------------------------*/
static void TI1_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);
static void TI2_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);
static void TI3_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);
static void TI4_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);
static void TI5_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);
static void TI6_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);

/*
 * Function:        TIM_DeInit
 * Description:     DeInitializes the TIM base peripheral.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * Return:          None.
 */
void TIM_DeInit(TIM_TypeDef *TIMx)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Disable the TIM Counter */
	TIMx->CR1 &= ~((uint32_t)TIM_CR1_CEN);
}
/*
 * Function:        TIM_BaseSetConfig
 * Description:     Time base configuration.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *                  TIM_TimeBaseInitStructure: TIM base configuration structure.
 * Return:          None.
 */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStructure)
{
	uint32_t tmpreg = 0;
    /* Check the parameters */
  	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
  	assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStructure->TIM_CounterMode));
 	assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStructure->TIM_ClockDivision));

	tmpreg = TIMx->CR1;

	/* Select the Counter Mode */
	tmpreg &= ~((uint32_t)(TIM_CR1_DIR | TIM_CR1_CMS));
	tmpreg |= ((uint32_t)TIM_TimeBaseInitStructure->TIM_CounterMode);

	/* Set the clock division */
	tmpreg &= ~((uint32_t)TIM_CR1_CKD);
	tmpreg |= ((uint32_t)TIM_TimeBaseInitStructure->TIM_ClockDivision);

	TIMx->CR1 = tmpreg;

	/* Set the Autoreload value */
	TIMx->ARR = ((uint32_t)TIM_TimeBaseInitStructure->TIM_Period);
	/* Set the Prescaler value */
	TIMx->PSC = ((uint32_t)TIM_TimeBaseInitStructure->TIM_Prescaler);
	if(TIMx==TIM0 || TIMx==TIM1 || TIMx==TIM2 || TIMx==TIM5)
	{
		/* Set the Repetition Counter value */
		TIMx->RCR = ((uint32_t)TIM_TimeBaseInitStructure->TIM_RepetitionCounter);
	}
	
	/* Generate an update event to reload the Prescaler
		and the repetition counter (only for advanced timer) value immediately */
	TIMx->EGR = ((uint32_t)TIM_EGR_UG);
}

/*
 * Function:        TIM_TimeBaseStructInit
 * Description:     Fills each Structure member with its default value.
 * Param:           TIM_TimeBaseInitStructure: pointer to a TIM_BaseInitTypeDef structure which will be initialized.
 * Return:          None.
 */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStructure)
{
	/* Set the default configuration */
	TIM_TimeBaseInitStructure->TIM_Period = 0xFFFFFFFF;
	TIM_TimeBaseInitStructure->TIM_Prescaler = 0x0000;
	TIM_TimeBaseInitStructure->TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure->TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure->TIM_RepetitionCounter = 0x0000;
}

/*
 * Function:        TIM_PrescalerConfig
 * Description:     Configures the TIMx Prescaler.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Prescaler: specifies the Prescaler Register value.
 *                  TIM_PSCReloadMode: specifies the TIM Prescaler Reload mode
 *         	    	This parameter can be one of the following values:
 *            	    TIM_PSCReloadMode_Update: The Prescaler is loaded at the update event.
 *                  TIM_PSCReloadMode_Immediate: The Prescaler is loaded immediatly.
 * Return:          None.
 */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint32_t Prescaler, uint32_t TIM_PSCReloadMode)
{
	/* Check the parameters */
  	assert_param(IS_TIM_ALL_PERIPH(TIMx));
  	assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));

	/* Set the Prescaler value */
	if(IS_TIM_GEN_PERIPH(TIMx))
	{
		assert_param(Prescaler<=0xFFFF);	
		TIMx->PSC&= ~(uint32_t)0xFFFF;	
	}
	else
	{
		TIMx->PSC&= ~(uint32_t)0xFFFFFFFF;	
	}
	TIMx->PSC |= Prescaler;
  	/* Set or reset the UG Bit */
  	TIMx->EGR = TIM_PSCReloadMode;
}

/*
 * Function:        TIM_CounterModeConfig
 * Description:     Specifies the TIMx Counter Mode to be used.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_CounterMode: specifies the Counter Mode to be used
 *          		This parameter can be one of the following values:
 *					TIM_CounterMode_Up: TIM Up Counting Mode
 *            	    TIM_CounterMode_Down: TIM Down Counting Mode
 *            	    TIM_CounterMode_CenterAligned1: TIM Center Aligned Mode1
 *            	    TIM_CounterMode_CenterAligned2: TIM Center Aligned Mode2
 *            		TIM_CounterMode_CenterAligned3: TIM Center Aligned Mode3
 * Return:          None.
 */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint32_t TIM_CounterMode)
{
	uint32_t tmpreg= 0;
	/* Check the parameters */
  	assert_param(IS_TIM_ALL_PERIPH(TIMx));
  	assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));

	tmpreg = TIMx->CR1;

	/* Reset the CMS and DIR Bits */
  	tmpreg &= (uint32_t)~(TIM_CR1_DIR | TIM_CR1_CMS);
  	/* Set the Counter Mode */
 	tmpreg |= TIM_CounterMode;
  	/* Write to TIMx CR1 register */
 	TIMx->CR1 = tmpreg;
}

/*
 * Function:        TIM_CounterModeConfig
 * Description:     Sets the TIMx Counter Register value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Counter: specifies the Counter register new value.
 * Return:          None.
 */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter)
{
	/* Check the parameters */
   	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Set the Counter Register value */	
	if(IS_TIM_GEN_PERIPH(TIMx))
	{
		assert_param(Counter<=0xFFFF);
		TIMx->CNT&= ~(uint32_t)0xFFFF;	
	}
	else
	{
		TIMx->CNT&= ~(uint32_t)0xFFFFFFFF;	
	}
	TIMx->CNT |= Counter;
}

/*
 * Function:        TIM_SetAutoreload
 * Description:     Sets the TIMx Autoreload Register value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Autoreload: specifies the Autoreload register new value.
 * Return:          None.
 */
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload)
{
	/* Check the parameters */
  	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	if(IS_TIM_GEN_PERIPH(TIMx))
	{
		assert_param(Autoreload<=0xFFFF);
		TIMx->ARR&= ~(uint32_t)0xFFFF;	
	}
	else
	{
		TIMx->ARR&= ~(uint32_t)0xFFFFFFFF;	
	}
  	/* Set the Autoreload Register value */
  	TIMx->ARR |= Autoreload;
}

/*
 * Function:        TIM_GetCounter
 * Description:     Gets the TIMx Counter value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * Return:          Counter Register value.
 */
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx)
{
	/* Check the parameters */
 	 assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Get the Counter Register value */
  	return TIMx->CNT;	 
}

/*
 * Function:        TIM_GetCounter
 * Description:     Gets the TIMx Prescaler value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * Return:          Prescaler Register value.
 */
uint32_t TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
	/* Check the parameters */
 	 assert_param(IS_TIM_ALL_PERIPH(TIMx));
	
	/* Get the Counter Register value */
  	return TIMx->PSC;	 
}

/*
 * Function:        TIM_UpdateDisableConfig
 * Description:     Enables or Disables the TIMx Update event.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *                	NewState: new state of the TIMx UDIS bit
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  	/* Check the parameters */
  	assert_param(IS_TIM_ALL_PERIPH(TIMx));
  	assert_param(IS_FunctionalState_STATE(NewState));

  	if (NewState != DISABLE)
  	{
    	/* Set the Update Disable Bit */
    	TIMx->CR1 |= TIM_CR1_UDIS;
  	}
	else
	{
		/* Reset the Update Disable Bit */
		TIMx->CR1 &= (uint32_t)~TIM_CR1_UDIS;
	}
}

/*
 * Function:        TIM_UpdateRequestConfig
 * Description:     Configures the TIMx Update Request Interrupt source.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *                	TIM_UpdateSource: specifies the Update source.
 *     		         This parameter can be one of the following values:
 * 					  TIM_UpdateSource_Global: Source of update is the counter
 *                    overflow/underflow or the setting of UG bit, or an update
 *                    generation through the slave mode controller.
 *                    TIM_UpdateSource_Regular: Source of update is counter overflow/underflow.
 * Return:          None.
 */
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint32_t TIM_UpdateSource)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));

	if (TIM_UpdateSource != TIM_UpdateSource_Global)
	{
		/* Set the URS Bit */
		TIMx->CR1 |= TIM_CR1_URS;
	}
	else
	{
		/* Reset the URS Bit */
		TIMx->CR1 &= (uint32_t)~TIM_CR1_URS;
	}
}

/*
 * Function:        TIM_ARRPreloadConfig
 * Description:     Enables or disables TIMx peripheral Preload register on ARR.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *                	NewState: new state of the TIMx peripheral Preload register
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	/* Check the parameters */
  	assert_param(IS_TIM_ALL_PERIPH(TIMx));
  	assert_param(IS_FunctionalState_STATE(NewState));

		if (NewState != DISABLE)
	{
		/* Set the ARR Preload Bit */
		TIMx->CR1 |= TIM_CR1_ARPE;
	}
	else
	{
		/* Reset the ARR Preload Bit */
		TIMx->CR1 &= (uint32_t)~TIM_CR1_ARPE;
	}
}

/*
 * Function:        TIM_SelectOnePulseMode
 * Description:     Selects the TIMx's One Pulse Mode.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *                	TIM_OPMode: specifies the OPM Mode to be used.
 *          		This parameter can be one of the following values:
 *            		TIM_OPMode_Single
 * 	            	TIM_OPMode_Repetitive
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint32_t TIM_OPMode)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OPM_MODE(TIM_OPMode));
	
	/* Reset the OPM Bit */
	TIMx->CR1 &= (uint32_t)~TIM_CR1_OPM;
	/* Configure the OPM Mode */
	TIMx->CR1 |= TIM_OPMode;
}

/*
 * Function:        TIM_SetClockDivision
 * Description:     Sets the TIMx Clock Division value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *                	This parameter can be one of the following value:
 *				    TIM_CKD_DIV1: TDTS = Tck_tim
 *				    TIM_CKD_DIV2: TDTS = 2*Tck_tim
 *				    TIM_CKD_DIV4: TDTS = 4*Tck_tim
 * Return:          None.
 */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint32_t TIM_CKD)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_CKD_DIV(TIM_CKD));

	/* Reset the CKD Bits */
	TIMx->CR1 &= (uint32_t)(~TIM_CR1_CKD);

	/* Set the CKD value */
	TIMx->CR1 |= TIM_CKD;
}

/*
 * Function:        TIM_Cmd
 * Description:     Enables or disables the specified TIM peripheral.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *                	NewState: new state of the TIMx peripheral.
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the TIM Counter */
    TIMx->CR1 |= TIM_CR1_CEN;
  }
  else
  {
    /* Disable the TIM Counter */
    TIMx->CR1 &= (uint32_t)~TIM_CR1_CEN;
  }
}

/*
 * Function:        TIM_OC1Init
 * Description:     Initializes the TIMx Channel1 according to the specified parameters in
 *         			the TIM_OCInitStruct.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *          		TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that contains
 * 					the configuration information for the specified TIM peripheral.
 * Return:          None.
 */
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
	assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

	/* Disable the Channel 1: Reset the CC1E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC1E;
	
	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;
	/* Get the TIMx CR2 register value */
	tmpcr2 =  TIMx->CR2;
	
	/* Get the TIMx CCMR1 register value */
	tmpccmrx = TIMx->CCMR1;
		
	/* Reset the Output Compare Mode Bits */
	tmpccmrx &= (uint32_t)~TIM_CCMR1_OC1M;
	tmpccmrx &= (uint32_t)~TIM_CCMR1_CC1S;
	/* Select the Output Compare Mode */
	tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
	
	/* Reset the Output Polarity level */
	tmpccer &= (uint32_t)~TIM_CCER_CC1P;
	/* Set the Output Compare Polarity */
	tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;
	
	/* Set the Output State */
	tmpccer |= TIM_OCInitStruct->TIM_OutputState;
		
	if((TIMx == TIM0) || (TIMx == TIM1)||(TIMx == TIM2) || (TIMx == TIM5))
	{
		assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
		assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
		assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
		assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
		
		/* Reset the Output N Polarity level */
		tmpccer &= (uint32_t)~TIM_CCER_CC1NP;
		/* Set the Output N Polarity */
		tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;
		/* Reset the Output N State */
		tmpccer &= (uint32_t)~TIM_CCER_CC1NE;
		
		/* Set the Output N State */
		tmpccer |= TIM_OCInitStruct->TIM_OutputNState;
		/* Reset the Output Compare and Output Compare N IDLE State */
		tmpcr2 &= (uint32_t)~TIM_CR2_OIS1;
		tmpcr2 &= (uint32_t)~TIM_CR2_OIS1N;
		/* Set the Output Idle state */
		tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
		/* Set the Output N Idle state */
		tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
	}
	/* Write to TIMx CR2 */
	TIMx->CR2 = tmpcr2;
	
	/* Write to TIMx CCMR1 */
	TIMx->CCMR1 = tmpccmrx;
	
	/* Set the Capture Compare Register value */
	TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;
	
	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC2Init
 * Description:     Initializes the TIMx Channel2 according to the specified parameters in
 *         			the TIM_OCInitStruct.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *          		TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that contains
 * 					the configuration information for the specified TIM peripheral.
 * Return:          None.
 */
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
	assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
	
	/* Disable the Channel 2: Reset the CC2E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC2E;
	
	/* Get the TIMx CCER register value */  
	tmpccer = TIMx->CCER;
	/* Get the TIMx CR2 register value */
	tmpcr2 =  TIMx->CR2;
	
	/* Get the TIMx CCMR1 register value */
	tmpccmrx = TIMx->CCMR1;
		
	/* Reset the Output Compare mode and Capture/Compare selection Bits */
	tmpccmrx &= (uint32_t)~TIM_CCMR1_OC2M;
	tmpccmrx &= (uint32_t)~TIM_CCMR1_CC2S;
  
	/* Select the Output Compare Mode */
	tmpccmrx |= (uint32_t)(TIM_OCInitStruct->TIM_OCMode << 8);
	
	/* Reset the Output Polarity level */
	tmpccer &= (uint32_t)~TIM_CCER_CC2P;
	/* Set the Output Compare Polarity */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);
	
	/* Set the Output State */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 4);
		
	if((TIMx == TIM0) || (TIMx == TIM1)||(TIMx == TIM2) || (TIMx == TIM5))
	{
		assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
		assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
		assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
		assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
		
		/* Reset the Output N Polarity level */
		tmpccer &= (uint32_t)~TIM_CCER_CC2NP;
		/* Set the Output N Polarity */
		tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCNPolarity << 4);
		/* Reset the Output N State */
		tmpccer &= (uint32_t)~TIM_CCER_CC2NE;
		
		/* Set the Output N State */
		tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputNState << 4);
		/* Reset the Output Compare and Output Compare N IDLE State */
		tmpcr2 &= (uint32_t)~TIM_CR2_OIS2;
		tmpcr2 &= (uint32_t)~TIM_CR2_OIS2N;
		/* Set the Output Idle state */
		tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 2);
		/* Set the Output N Idle state */
		tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
	}
	/* Write to TIMx CR2 */
	TIMx->CR2 = tmpcr2;
	
	/* Write to TIMx CCMR1 */
	TIMx->CCMR1 = tmpccmrx;
	
	/* Set the Capture Compare Register value */
	TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
	
	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC3Init
 * Description:     Initializes the TIMx Channel3 according to the specified parameters in
 *         			the TIM_OCInitStruct.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *          		TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that contains
 * 					the configuration information for the specified TIM peripheral.
 * Return:          None.
 */
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
	
	/* Check the parameters */
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
	assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

	/* Disable the Channel 3: Reset the CC3E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC3E;
	
	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;
	/* Get the TIMx CR2 register value */
	tmpcr2 =  TIMx->CR2;
	
	/* Get the TIMx CCMR2 register value */
	tmpccmrx = TIMx->CCMR2;
		
	/* Reset the Output Compare mode and Capture/Compare selection Bits */
	tmpccmrx &= (uint32_t)~TIM_CCMR2_OC3M;
	tmpccmrx &= (uint32_t)~TIM_CCMR2_CC3S;  
	/* Select the Output Compare Mode */
	tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
	
	/* Reset the Output Polarity level */
	tmpccer &= (uint32_t)~TIM_CCER_CC3P;
	/* Set the Output Compare Polarity */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 8);
	
	/* Set the Output State */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 8);
		
	if((TIMx == TIM0) || (TIMx == TIM1)||(TIMx == TIM2) || (TIMx == TIM5))
	{
		assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
		assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
		assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
		assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
		
		/* Reset the Output N Polarity level */
		tmpccer &= (uint32_t)~TIM_CCER_CC3NP;
		/* Set the Output N Polarity */
		tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCNPolarity << 8);
		/* Reset the Output N State */
		tmpccer &= (uint32_t)~TIM_CCER_CC3NE;
		
		/* Set the Output N State */
		tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputNState << 8);
		/* Reset the Output Compare and Output Compare N IDLE State */
		tmpcr2 &= (uint32_t)~TIM_CR2_OIS3;
		tmpcr2 &= (uint32_t)~TIM_CR2_OIS3N;
		/* Set the Output Idle state */
		tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 4);
		/* Set the Output N Idle state */
		tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
	}
	/* Write to TIMx CR2 */
	TIMx->CR2 = tmpcr2;
	
	/* Write to TIMx CCMR2 */
	TIMx->CCMR2 = tmpccmrx;
	
	/* Set the Capture Compare Register value */
	TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
	
	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC4Init
 * Description:     Initializes the TIMx Channel4 according to the specified parameters in
 *         			the TIM_OCInitStruct.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *          		TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that contains
 * 					the configuration information for the specified TIM peripheral.
 * Return:          None.
 */
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
	assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   

	/* Disable the Channel 4: Reset the CC4E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC4E;
	
	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;
	/* Get the TIMx CR2 register value */
	tmpcr2 =  TIMx->CR2;
	
	/* Get the TIMx CCMR2 register value */
	tmpccmrx = TIMx->CCMR2;
		
	/* Reset the Output Compare mode and Capture/Compare selection Bits */
	tmpccmrx &= (uint32_t)~TIM_CCMR2_OC4M;
	tmpccmrx &= (uint32_t)~TIM_CCMR2_CC4S;
	
	/* Select the Output Compare Mode */
	tmpccmrx |= (uint32_t)(TIM_OCInitStruct->TIM_OCMode << 8);
	
	/* Reset the Output Polarity level */
	tmpccer &= (uint32_t)~TIM_CCER_CC4P;
	/* Set the Output Compare Polarity */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);
	
	/* Set the Output State */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 12);
	
	if((TIMx == TIM0) || (TIMx == TIM1)||(TIMx == TIM2) || (TIMx == TIM5))
	{

		assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
		assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
		assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
		assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
		
		/* Reset the Output N Polarity level */
		tmpccer &= (uint32_t)~TIM_CCER_CC4NP;
		/* Set the Output N Polarity */
		tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCNPolarity << 12);
		/* Reset the Output N State */
		tmpccer &= (uint32_t)~TIM_CCER_CC4NE;
		/* Set the Output N State */
		tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputNState << 12);

		/* Reset the Output Compare and Output Compare N IDLE State */
		tmpcr2 &= (uint32_t)~TIM_CR2_OIS4;
		tmpcr2 &= (uint32_t)~TIM_CR2_OIS4N;
		/* Set the Output Idle state */
		tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
		/* Set the Output N Idle state */
		tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCNIdleState << 6);

	}
	/* Write to TIMx CR2 */
	TIMx->CR2 = tmpcr2;
	
	/* Write to TIMx CCMR2 */  
	TIMx->CCMR2 = tmpccmrx;
		
	/* Set the Capture Compare Register value */
	TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
	
	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC5Init
 * Description:     Initializes the TIMx Channel5 according to the specified parameters in
 *         			the TIM_OCInitStruct.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 *          		TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that contains
 * 					the configuration information for the specified TIM peripheral.
 * Return:          None.
 */
void TIM_OC5Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx)); 
	assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
	assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));  
	assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
	assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
	assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
	assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState)); 

	/* Disable the Channel 5: Reset the CC5E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC5E;
	
	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;
	/* Get the TIMx CR2 register value */
	tmpcr2 =  TIMx->CR2;
	
	/* Get the TIMx CCMR3 register value */
	tmpccmrx = TIMx->CCMR3;
		
	/* Reset the Output Compare mode and Capture/Compare selection Bits */
	tmpccmrx &= (uint32_t)~TIM_CCMR3_OC5M;
	tmpccmrx &= (uint32_t)~TIM_CCMR3_CC5S;
	
	/* Select the Output Compare Mode */
	tmpccmrx |= (uint32_t)TIM_OCInitStruct->TIM_OCMode;
	
	/* Reset the Output Polarity level */
	tmpccer &= (uint32_t)~TIM_CCER_CC5P;
	/* Set the Output Compare Polarity */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 16);
	
	/* Set the Output State */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 16);
			
	/* Reset the Output N Polarity level */
	tmpccer &= (uint32_t)~TIM_CCER_CC5NP;
	/* Set the Output N Polarity */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCNPolarity << 16);
	/* Reset the Output N State */
	tmpccer &= (uint32_t)~TIM_CCER_CC5NE;
	/* Set the Output N State */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputNState << 16);

	/* Reset the Output Compare and Output Compare N IDLE State */
	tmpcr2 &= (uint32_t)~TIM_CR2_OIS5;
	tmpcr2 &= (uint32_t)~TIM_CR2_OIS5N;
	/* Set the Output Idle state */
	tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 8);
	/* Set the Output N Idle state */
	tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCNIdleState << 8);

	/* Write to TIMx CR2 */
	TIMx->CR2 = tmpcr2;
	
	/* Write to TIMx CCMR3 */  
	TIMx->CCMR3 = tmpccmrx;
		
	/* Set the Capture Compare Register value */
	TIMx->CCR5 = TIM_OCInitStruct->TIM_Pulse;
	
	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC6Init
 * Description:     Initializes the TIMx Channel6 according to the specified parameters in
 *         			the TIM_OCInitStruct.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 *          		TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that contains
 * 					the configuration information for the specified TIM peripheral.
 * Return:          None.
 */
void TIM_OC6Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx)); 
	assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
	assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));  
	assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
	assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
	assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
	assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState)); 

	/* Disable the Channel 6: Reset the CC6E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC6E;
	
	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;
	/* Get the TIMx CR2 register value */
	tmpcr2 =  TIMx->CR2;
	
	/* Get the TIMx CCMR3 register value */
	tmpccmrx = TIMx->CCMR3;
		
	/* Reset the Output Compare mode and Capture/Compare selection Bits */
	tmpccmrx &= (uint32_t)~TIM_CCMR3_OC6M;
	tmpccmrx &= (uint32_t)~TIM_CCMR3_CC6S;
	
	/* Select the Output Compare Mode */
	tmpccmrx |= (uint32_t)(TIM_OCInitStruct->TIM_OCMode << 8);
	
	/* Reset the Output Polarity level */
	tmpccer &= (uint32_t)~TIM_CCER_CC6P;
	/* Set the Output Compare Polarity */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 20);
	
	/* Set the Output State */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 20);
			
	/* Reset the Output N Polarity level */
	tmpccer &= (uint32_t)~TIM_CCER_CC6NP;
	/* Set the Output N Polarity */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCNPolarity << 20);
	/* Reset the Output N State */
	tmpccer &= (uint32_t)~TIM_CCER_CC6NE;
	/* Set the Output N State */
	tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputNState << 20);

	/* Reset the Output Compare and Output Compare N IDLE State */
	tmpcr2 &= (uint32_t)~TIM_CR2_OIS6;
	tmpcr2 &= (uint32_t)~TIM_CR2_OIS6N;
	/* Set the Output Idle state */
	tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 10);
	/* Set the Output N Idle state */
	tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCNIdleState << 10);

	/* Write to TIMx CR2 */
	TIMx->CR2 = tmpcr2;
	
	/* Write to TIMx CCMR3 */  
	TIMx->CCMR3 = tmpccmrx;
		
	/* Set the Capture Compare Register value */
	TIMx->CCR6 = TIM_OCInitStruct->TIM_Pulse;
	
	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OCStructInit
 * Description:     Fills each TIM_OCInitStruct member with its default value.
 * Param:           TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure which will
 *      		   	be initialized.
 * Return:          None.
 */
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	/* Set the default configuration */
	TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStruct->TIM_Pulse = 0x00000000;
	TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/*
 * Function:        TIM_SelectOCxM
 * Description:     This function disables the selected channel before changing the Output
 * 					Compare Mode. If needed, user has to enable this channel using
 * 					TIM_CCxCmd() and TIM_CCxNCmd() functions.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				TIM_Channel: specifies the TIM Channel
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_Channel_1: TIM_Channel_1
 * 					  TIM_Channel_2: TIM_Channel_2
 *                    TIM_Channel_3: TIM_Channel_3
 *                    TIM_Channel_4: TIM_Channel_4
 * 					  TIM_Channel_5: TIM_Channel_5
 *                    TIM_Channel_6: TIM_Channel_6
 *                  TIM_OCMode: specifies the TIM Output Compare Mode.
 *                   This parameter can be one of the following values:
 *                    TIM_OCMode_Timing
 *                    TIM_OCMode_Active
 *                    TIM_OCMode_Toggle
 *                    TIM_OCMode_PWM1
 *                    TIM_OCMode_PWM2
 *                    TIM_ForcedAction_Active
 *                    TIM_ForcedAction_InActive
 * Return:          None.
 */
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_OCMode)
{
	uint32_t tmp = 0;
	uint32_t tmp1 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_CHANNEL(TIM_Channel));
	assert_param(IS_TIM_OCM(TIM_OCMode));
	/*If the channels is 5 or 6, then check if the timer is an advanced timer*/
	if((TIM_Channel == TIM_Channel_6) ||(TIM_Channel == TIM_Channel_5))
	{
		assert_param(IS_TIM_ADV_PERIPH(TIMx));
	}

	tmp = (uint32_t) TIMx;
	tmp += CCMR_OFFSET;

	tmp1 = CCER_CCE_SET << (uint32_t)TIM_Channel;

	/* Disable the Channel: Reset the CCxE Bit */
	TIMx->CCER &= (uint32_t) ~tmp1;

	if((TIM_Channel == TIM_Channel_1) ||(TIM_Channel == TIM_Channel_3)||(TIM_Channel == TIM_Channel_5))
	{
		tmp += (uint32_t)((uint32_t)(TIM_Channel>>2)*2);

		/* Reset the OCxM bits in the CCMRx register */
		*(__IO uint32_t *) tmp &= CCMR_OC135M_MASK;
	
		/* Configure the OCxM bits in the CCMRx register */
		*(__IO uint32_t *) tmp |= TIM_OCMode;
	}
	else
	{
		tmp += (uint32_t)(((uint32_t)(TIM_Channel>>2)-1)*2);

		/* Reset the OCxM bits in the CCMRx register */
		*(__IO uint32_t *) tmp &= CCMR_OC246M_MASK;
		
		/* Configure the OCxM bits in the CCMRx register */
		*(__IO uint32_t *) tmp |= (uint32_t)(TIM_OCMode << 8);
	}
}

/*
 * Function:        TIM_ForcedOC1Config
 * Description:     Sets the TIMx Capture Compare1 Register value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Compare1: specifies the Capture Compare1 register new value.
 * Return:          None.
 */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Set the Capture Compare1 Register value */
	if(IS_TIM_GEN_PERIPH(TIMx))
	{
		assert_param(Compare1<=0xFFFF);	
		TIMx->CCR1&= ~(uint32_t)0xFFFF;	
	}
	else
	{
		TIMx->CCR1&= ~(uint32_t)0xFFFFFFFF;	
	}
	TIMx->CCR1 |= Compare1;
}

/*
 * Function:        TIM_ForcedOC2Config
 * Description:     Sets the TIMx Capture Compare2 Register value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Compare1: specifies the Capture Compare2 register new value.
 * Return:          None.
 */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Set the Capture Compare1 Register value */
	if(IS_TIM_GEN_PERIPH(TIMx))
	{
		assert_param(Compare2<=0xFFFF);	
		TIMx->CCR2&= ~(uint32_t)0xFFFF;	
	}
	else
	{
		TIMx->CCR2&= ~(uint32_t)0xFFFFFFFF;	
	}
	TIMx->CCR2 |= Compare2;
}

/*
 * Function:        TIM_ForcedOC3Config
 * Description:     Sets the TIMx Capture Compare3 Register value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Compare1: specifies the Capture Compare1 register new value.
 * Return:          None.
 */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Set the Capture Compare1 Register value */
	if(IS_TIM_GEN_PERIPH(TIMx))
	{
		assert_param(Compare3<=0xFFFF);	
		TIMx->CCR3&= ~(uint32_t)0xFFFF;	
	}
	else
	{
		TIMx->CCR3&= ~(uint32_t)0xFFFFFFFF;	
	}
	TIMx->CCR3 |= Compare3;
}

/*
 * Function:        TIM_ForcedOC4Config
 * Description:     Sets the TIMx Capture Compare4 Register value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Compare4: specifies the Capture Compare4 register new value.
 * Return:          None.
 */
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Set the Capture Compare1 Register value */
	if(IS_TIM_GEN_PERIPH(TIMx))
	{
		assert_param(Compare4<=0xFFFF);	
		TIMx->CCR4&= ~(uint32_t)0xFFFF;	
	}
	else
	{
		TIMx->CCR4&= ~(uint32_t)0xFFFFFFFF;	
	}
	TIMx->CCR4 |= Compare4;
}

/*
 * Function:        TIM_ForcedOC5Config
 * Description:     Sets the TIMx Capture Compare5 Register value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Compare5: specifies the Capture Compare5 register new value.
 * Return:          None.
 */
void TIM_SetCompare5(TIM_TypeDef* TIMx, uint32_t Compare5)
{
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));

	/* Set the Capture Compare5 Register value */
	TIMx->CCR5 = Compare5;
}

/*
 * Function:        TIM_SetCompare6
 * Description:     Sets the TIMx Capture Compare6 Register value.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					Compare6: specifies the Capture Compare6 register new value.
 * Return:          None.
 */
void TIM_SetCompare6(TIM_TypeDef* TIMx, uint32_t Compare6)
{
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));

	/* Set the Capture Compare6 Register value */
	TIMx->CCR6 = Compare6;
}


/*
 * Function:        TIM_ForcedOC1Config
 * Description:     Forces the TIMx output 1 waveform to active or inactive level.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
 *          		This parameter can be one of the following values:
 *           		TIM_ForcedAction_Active: Force active level on OC1REF
 *            		TIM_ForcedAction_InActive: Force inactive level on OC1REF.
 * Return:          None.
 */
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
	uint32_t tmpccmr1 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
	tmpccmr1 = TIMx->CCMR1;

	/* Reset the OC1M Bits */
	tmpccmr1 &= (uint32_t)~TIM_CCMR1_OC1M;

	/* Configure The Forced output Mode */
	tmpccmr1 |= TIM_ForcedAction;

	/* Write to TIMx CCMR1 register */
	TIMx->CCMR1 = tmpccmr1;
}

/*
 * Function:        TIM_ForcedOC2Config
 * Description:     Forces the TIMx output 2 waveform to active or inactive level.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
 *          		This parameter can be one of the following values:
 *           		TIM_ForcedAction_Active: Force active level on OC1REF
 *            		TIM_ForcedAction_InActive: Force inactive level on OC1REF.
 * Return:          None.
 */
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
	uint32_t tmpccmr1 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
	tmpccmr1 = TIMx->CCMR1;

	/* Reset the OC2M Bits */
	tmpccmr1 &= (uint32_t)~TIM_CCMR1_OC2M;

	/* Configure The Forced output Mode */
	tmpccmr1 |= (uint32_t)(TIM_ForcedAction << 8);

	/* Write to TIMx CCMR1 register */
	TIMx->CCMR1 = tmpccmr1;
}

/*
 * Function:        TIM_ForcedOC3Config
 * Description:     Forces the TIMx output 3 waveform to active or inactive level.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
 *          		This parameter can be one of the following values:
 *           		TIM_ForcedAction_Active: Force active level on OC1REF
 *            		TIM_ForcedAction_InActive: Force inactive level on OC1REF.
 * Return:          None.
 */
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
	uint32_t tmpccmr2 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));

	tmpccmr2 = TIMx->CCMR2;

	/* Reset the OC1M Bits */
	tmpccmr2 &= (uint32_t)~TIM_CCMR2_OC3M;

	/* Configure The Forced output Mode */
	tmpccmr2 |= TIM_ForcedAction;

	/* Write to TIMx CCMR2 register */
	TIMx->CCMR2 = tmpccmr2;
}

/*
 * Function:        TIM_ForcedOC4Config
 * Description:     Forces the TIMx output 4 waveform to active or inactive level.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
 *          		This parameter can be one of the following values:
 *           		TIM_ForcedAction_Active: Force active level on OC1REF
 *            		TIM_ForcedAction_InActive: Force inactive level on OC1REF.
 * Return:          None.
 */
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
	uint32_t tmpccmr2 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
	tmpccmr2 = TIMx->CCMR2;

	/* Reset the OC2M Bits */
	tmpccmr2 &= (uint32_t)~TIM_CCMR2_OC4M;

	/* Configure The Forced output Mode */
	tmpccmr2 |= (uint32_t)(TIM_ForcedAction << 8);

	/* Write to TIMx CCMR2 register */
	TIMx->CCMR2 = tmpccmr2;
}

/*
 * Function:        TIM_ForcedOC5Config
 * Description:     Forces the TIMx output 5 waveform to active or inactive level.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
 *          		This parameter can be one of the following values:
 *           		TIM_ForcedAction_Active: Force active level on OC1REF
 *            		TIM_ForcedAction_InActive: Force inactive level on OC1REF.
 * Return:          None.
 */
void TIM_ForcedOC5Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
	uint32_t tmpccmr3 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
	tmpccmr3 = TIMx->CCMR3;

	/* Reset the OC5M Bits */
	tmpccmr3 &= (uint32_t)~TIM_CCMR3_OC5M;

	/* Configure The Forced output Mode */
	tmpccmr3 |= TIM_ForcedAction;

	/* Write to TIMx CCMR3 register */
	TIMx->CCMR3 = tmpccmr3;
}

/*
 * Function:        TIM_ForcedOC6Config
 * Description:     Forces the TIMx output 6 waveform to active or inactive level.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
 *          		This parameter can be one of the following values:
 *           		TIM_ForcedAction_Active: Force active level on OC1REF
 *            		TIM_ForcedAction_InActive: Force inactive level on OC1REF.
 * Return:          None.
 */
void TIM_ForcedOC6Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
	uint32_t tmpccmr3 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
	tmpccmr3 = TIMx->CCMR3;

	/* Reset the OC6M Bits */
	tmpccmr3 &= (uint32_t)~TIM_CCMR3_OC6M;

	/* Configure The Forced output Mode */
	tmpccmr3 |= (uint32_t)(TIM_ForcedAction<< 8);

	/* Write to TIMx CCMR3 register */
	TIMx->CCMR3 = tmpccmr3;
}

/*
 * Function:        TIM_OC1PreloadConfig
 * Description:     Enables or disables the TIMx peripheral Preload register on CCR1.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPreload: new state of the TIMx peripheral Preload register
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
  uint32_t tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC1PE Bit */
  tmpccmr1 &= (uint32_t)(~TIM_CCMR1_OC1PE);

  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= TIM_OCPreload;

  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/*
 * Function:        TIM_OC2PreloadConfig
 * Description:     Enables or disables the TIMx peripheral Preload register on CCR2.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPreload: new state of the TIMx peripheral Preload register
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
	uint32_t tmpccmr1 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

	tmpccmr1 = TIMx->CCMR1;

	/* Reset the OC2PE Bit */
	tmpccmr1 &= (uint32_t)(~TIM_CCMR1_OC2PE);

	/* Enable or Disable the Output Compare Preload feature */
	tmpccmr1 |= (uint32_t)(TIM_OCPreload << 8);

	/* Write to TIMx CCMR1 register */
	TIMx->CCMR1 = tmpccmr1;
}

/*
 * Function:        TIM_OC3PreloadConfig
 * Description:     Enables or disables the TIMx peripheral Preload register on CCR3.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPreload: new state of the TIMx peripheral Preload register
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
	uint32_t tmpccmr2 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_LIST3_PERIPH(TIMx));
	assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

	tmpccmr2 = TIMx->CCMR2;

	/* Reset the OC3PE Bit */
	tmpccmr2 &= (uint32_t)(~TIM_CCMR2_OC3PE);

	/* Enable or Disable the Output Compare Preload feature */
	tmpccmr2 |= TIM_OCPreload;

	/* Write to TIMx CCMR2 register */
	TIMx->CCMR2 = tmpccmr2;
}

/*
 * Function:        TIM_OC4PreloadConfig
 * Description:     Enables or disables the TIMx peripheral Preload register on CCR4.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPreload: new state of the TIMx peripheral Preload register
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
	uint32_t tmpccmr2 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

	tmpccmr2 = TIMx->CCMR2;

	/* Reset the OC4PE Bit */
	tmpccmr2 &= (uint32_t)(~TIM_CCMR2_OC4PE);

	/* Enable or Disable the Output Compare Preload feature */
	tmpccmr2 |= (uint32_t)(TIM_OCPreload << 8);

	/* Write to TIMx CCMR2 register */
	TIMx->CCMR2 = tmpccmr2;
}

/*
 * Function:        TIM_OC5PreloadConfig
 * Description:     Enables or disables the TIMx peripheral Preload register on CCR5.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPreload: new state of the TIMx peripheral Preload register
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC5PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
	uint32_t tmpccmr3 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

	tmpccmr3 = TIMx->CCMR3;

	/* Reset the OC3PE Bit */
	tmpccmr3 &= (uint32_t)(~TIM_CCMR3_OC5PE);

	/* Enable or Disable the Output Compare Preload feature */
	tmpccmr3 |= TIM_OCPreload;

	/* Write to TIMx CCMR3 register */
	TIMx->CCMR3 = tmpccmr3;
}

/*
 * Function:        TIM_OC6PreloadConfig
 * Description:     Enables or disables the TIMx peripheral Preload register on CCR6.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPreload: new state of the TIMx peripheral Preload register
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC6PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
	uint32_t tmpccmr3 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

	tmpccmr3 = TIMx->CCMR3;

	/* Reset the OC3PE Bit */
	tmpccmr3 &= (uint32_t)(~TIM_CCMR3_OC6PE);

	/* Enable or Disable the Output Compare Preload feature */
	tmpccmr3 |= (uint32_t)(TIM_OCPreload<<8);

	/* Write to TIMx CCMR3 register */
	TIMx->CCMR3 = tmpccmr3;
}



/*
 * Function:        TIM_OC1FastConfig
 * Description:     Configures the TIMx Output Compare 2 Fast feature.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCFast: new state of the Output Compare Fast Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
	uint32_t tmpccmr1 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

	/* Get the TIMx CCMR1 register value */
	tmpccmr1 = TIMx->CCMR1;

	/* Reset the OC1FE Bit */
	tmpccmr1 &= (uint32_t)~TIM_CCMR1_OC1FE;

	/* Enable or Disable the Output Compare Fast Bit */
	tmpccmr1 |= TIM_OCFast;

	/* Write to TIMx CCMR1 */
	TIMx->CCMR1 = tmpccmr1;
}

/*
 * Function:        TIM_OC2FastConfig
 * Description:     Configures the TIMx Output Compare 2 Fast feature.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCFast: new state of the Output Compare Fast Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
	uint32_t tmpccmr1 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

	/* Get the TIMx CCMR1 register value */
	tmpccmr1 = TIMx->CCMR1;

	/* Reset the OC2FE Bit */
	tmpccmr1 &= (uint32_t)(~TIM_CCMR1_OC2FE);

	/* Enable or Disable the Output Compare Fast Bit */
	tmpccmr1 |= (uint32_t)(TIM_OCFast << 8);

	/* Write to TIMx CCMR1 */
	TIMx->CCMR1 = tmpccmr1;
}

/*
 * Function:        TIM_OC3FastConfig
 * Description:     Configures the TIMx Output Compare 3 Fast feature.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCFast: new state of the Output Compare Fast Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
	uint32_t tmpccmr2 = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

	/* Get the TIMx CCMR2 register value */
	tmpccmr2 = TIMx->CCMR2;

	/* Reset the OC3FE Bit */
	tmpccmr2 &= (uint32_t)~TIM_CCMR2_OC3FE;

	/* Enable or Disable the Output Compare Fast Bit */
	tmpccmr2 |= TIM_OCFast;

	/* Write to TIMx CCMR2 */
	TIMx->CCMR2 = tmpccmr2;
}

/*
 * Function:        TIM_OC4FastConfig
 * Description:     Configures the TIMx Output Compare 4 Fast feature.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCFast: new state of the Output Compare Fast Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
	uint32_t tmpccmr2 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

	/* Get the TIMx CCMR2 register value */
	tmpccmr2 = TIMx->CCMR2;

	/* Reset the OC4FE Bit */
	tmpccmr2 &= (uint32_t)(~TIM_CCMR2_OC4FE);

	/* Enable or Disable the Output Compare Fast Bit */
	tmpccmr2 |= (uint32_t)(TIM_OCFast << 8);

	/* Write to TIMx CCMR2 */
	TIMx->CCMR2 = tmpccmr2;
}

/*
 * Function:        TIM_OC5FastConfig
 * Description:     Configures the TIMx Output Compare 5 Fast feature.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCFast: new state of the Output Compare Fast Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC5FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
	uint32_t tmpccmr3 = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

	/* Get the TIMx CCMR3 register value */
	tmpccmr3 = TIMx->CCMR3;

	/* Reset the OC5FE Bit */
	tmpccmr3 &= (uint32_t)~TIM_CCMR3_OC5FE;

	/* Enable or Disable the Output Compare Fast Bit */
	tmpccmr3 |= TIM_OCFast;

	/* Write to TIMx CCMR5 */
	TIMx->CCMR3 = tmpccmr3;
}

/*
 * Function:        TIM_OC6FastConfig
 * Description:     Configures the TIMx Output Compare 6 Fast feature.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCFast: new state of the Output Compare Fast Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCFast_Enable: TIM output compare fast enable
 *            		TIM_OCFast_Disable: TIM output compare fast disable
 * Return:          None.
 */
void TIM_OC6FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
	uint32_t tmpccmr3 = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

	/* Get the TIMx CCMR3 register value */
	tmpccmr3 = TIMx->CCMR3;

	/* Reset the OC6FE Bit */
	tmpccmr3 &= (uint32_t)~TIM_CCMR3_OC6FE;

	/* Enable or Disable the Output Compare Fast Bit */
	tmpccmr3 |= (uint32_t)(TIM_OCFast<<8);

	/* Write to TIMx CCMR3 */
	TIMx->CCMR3 = tmpccmr3;
}

/*
 * Function:        TIM_ClearOC1Ref
 * Description:     Clears or safeguards the OCREF1 signal on an external event
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCClear: new state of the Output Compare Clear Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCClear_Enable: TIM Output clear enable
 *            		TIM_OCClear_Disable: TIM Output clear disable
 * Return:          None.
 */
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
	uint32_t tmpccmr1 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

	tmpccmr1 = TIMx->CCMR1;

	/* Reset the OC1CE Bit */
	tmpccmr1 &= (uint32_t)~TIM_CCMR1_OC1CE;

	/* Enable or Disable the Output Compare Clear Bit */
	tmpccmr1 |= TIM_OCClear;

	/* Write to TIMx CCMR1 register */
	TIMx->CCMR1 = tmpccmr1;
}

/*
 * Function:        TIM_ClearOC2Ref
 * Description:     Clears or safeguards the OCREF1 signal on an external event
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCClear: new state of the Output Compare Clear Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCClear_Enable: TIM Output clear enable
 *            		TIM_OCClear_Disable: TIM Output clear disable
 * Return:          None.
 */
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
	uint32_t tmpccmr1 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

	tmpccmr1 = TIMx->CCMR1;

	/* Reset the OC2CE Bit */
	tmpccmr1 &= (uint32_t)~TIM_CCMR1_OC2CE;

	/* Enable or Disable the Output Compare Clear Bit */
	tmpccmr1 |= (uint32_t)(TIM_OCClear << 8);

	/* Write to TIMx CCMR1 register */
	TIMx->CCMR1 = tmpccmr1;
}

/*
 * Function:        TIM_ClearOC3Ref
 * Description:     Clears or safeguards the OCREF1 signal on an external event
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCClear: new state of the Output Compare Clear Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCClear_Enable: TIM Output clear enable
 *            		TIM_OCClear_Disable: TIM Output clear disable
 * Return:          None.
 */
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
	uint32_t tmpccmr2 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

	tmpccmr2 = TIMx->CCMR2;

	/* Reset the OC3CE Bit */
	tmpccmr2 &= (uint32_t)~TIM_CCMR2_OC3CE;

	/* Enable or Disable the Output Compare Clear Bit */
	tmpccmr2 |= TIM_OCClear;

	/* Write to TIMx CCMR2 register */
	TIMx->CCMR2 = tmpccmr2;
}

/*
 * Function:        TIM_ClearOC4Ref
 * Description:     Clears or safeguards the OCREF1 signal on an external event
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCClear: new state of the Output Compare Clear Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCClear_Enable: TIM Output clear enable
 *            		TIM_OCClear_Disable: TIM Output clear disable
 * Return:          None.
 */
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
  uint32_t tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC4CE Bit */
  tmpccmr2 &= (uint32_t)~TIM_CCMR2_OC4CE;

  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= (uint32_t)(TIM_OCClear << 8);

  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/*
 * Function:        TIM_ClearOC5Ref
 * Description:     Clears or safeguards the OCREF1 signal on an external event
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCClear: new state of the Output Compare Clear Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCClear_Enable: TIM Output clear enable
 *            		TIM_OCClear_Disable: TIM Output clear disable
 * Return:          None.
 */
void TIM_ClearOC5Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
	uint32_t tmpccmr3 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

	tmpccmr3 = TIMx->CCMR3;

	/* Reset the OC5CE Bit */
	tmpccmr3 &= (uint32_t)~TIM_CCMR3_OC5CE;

	/* Enable or Disable the Output Compare Clear Bit */
	tmpccmr3 |= TIM_OCClear;

	/* Write to TIMx CCMR3 register */
	TIMx->CCMR3 = tmpccmr3;
}

/*
 * Function:        TIM_ClearOC6Ref
 * Description:     Clears or safeguards the OCREF1 signal on an external event
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCClear: new state of the Output Compare Clear Enable Bit.
 *          		This parameter can be one of the following values:
 *           		TIM_OCClear_Enable: TIM Output clear enable
 *            		TIM_OCClear_Disable: TIM Output clear disable
 * Return:          None.
 */
void TIM_ClearOC6Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
	uint32_t tmpccmr3 = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

	tmpccmr3 = TIMx->CCMR3;

	/* Reset the OC6CE Bit */
	tmpccmr3 &= (uint32_t)~TIM_CCMR3_OC6CE;

	/* Enable or Disable the Output Compare Clear Bit */
	tmpccmr3 |= (uint32_t)(TIM_OCClear<<8);

	/* Write to TIMx CCMR3 register */
	TIMx->CCMR3 = tmpccmr3;
}

/*
 * Function:        TIM_OC1PolarityConfig
 * Description:     Configures the TIMx channel 1 polarity.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
	uint32_t tmpccer = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

	tmpccer = TIMx->CCER;

	/* Set or Reset the CC1P Bit */
	tmpccer &= (uint32_t)(~TIM_CCER_CC1P);
	tmpccer |= TIM_OCPolarity;

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC1NPolarityConfig
 * Description:     Configures the TIMx Channel 1N polarity.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
	uint32_t tmpccer = 0;
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
	
	tmpccer = TIMx->CCER;

	/* Set or Reset the CC1NP Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC1NP;
	tmpccer |= TIM_OCNPolarity;

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC2PolarityConfig
 * Description:     Configures the TIMx channel 2 polarity.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
	uint32_t tmpccer = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

	tmpccer = TIMx->CCER;

	/* Set or Reset the CC2P Bit */
	tmpccer &= (uint32_t)(~TIM_CCER_CC2P);
	tmpccer |= (uint32_t)(TIM_OCPolarity << 4);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC2NPolarityConfig
 * Description:     Configures the TIMx Channel 2N polarity.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
	uint32_t tmpccer = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
	
	tmpccer = TIMx->CCER;

	/* Set or Reset the CC2NP Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC2NP;
	tmpccer |= (uint32_t)(TIM_OCNPolarity << 4);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC3PolarityConfig
 * Description:     Configures the TIMx channel 3 polarity.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
	uint32_t tmpccer = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

	tmpccer = TIMx->CCER;

	/* Set or Reset the CC3P Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC3P;
	tmpccer |= (uint32_t)(TIM_OCPolarity << 8);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC3NPolarityConfig
 * Description:     Configures the TIMx Channel 3N polarity.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
	uint32_t tmpccer = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
		
	tmpccer = TIMx->CCER;

	/* Set or Reset the CC3NP Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC3NP;
	tmpccer |= (uint32_t)(TIM_OCNPolarity << 8);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC4PolarityConfig
 * Description:     Configures the TIMx channel 4 polarity.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
	uint32_t tmpccer = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

	tmpccer = TIMx->CCER;

	/* Set or Reset the CC4P Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC4P;
	tmpccer |= (uint32_t)(TIM_OCPolarity << 12);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC4NPolarityConfig
 * Description:     Configures the TIMx Channel 4N polarity.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC4NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
	uint32_t tmpccer = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
		
	tmpccer = TIMx->CCER;

	/* Set or Reset the CC4NP Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC4NP;
	tmpccer |= (uint32_t)(TIM_OCNPolarity << 12);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC5PolarityConfig
 * Description:     Configures the TIMx channel 5 polarity.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC5PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
	uint32_t tmpccer = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

	tmpccer = TIMx->CCER;

	/* Set or Reset the CC5P Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC5P;
	tmpccer |= (uint32_t)(TIM_OCPolarity << 16);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC5NPolarityConfig
 * Description:     Configures the TIMx Channel 5N polarity.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC5NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
	uint32_t tmpccer = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
		
	tmpccer = TIMx->CCER;

	/* Set or Reset the CC5NP Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC5NP;
	tmpccer |= (uint32_t)(TIM_OCNPolarity << 16);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC6PolarityConfig
 * Description:     Configures the TIMx channel 6 polarity.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC6PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
	uint32_t tmpccer = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

	tmpccer = TIMx->CCER;

	/* Set or Reset the CC6P Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC6P;
	tmpccer |= (uint32_t)(TIM_OCPolarity <<20);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_OC6NPolarityConfig
 * Description:     Configures the TIMx Channel 6N polarity.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_OCPolarity: specifies the OC1 Polarity
 *          		This parameter can be one of the following values:
 *           		TIM_OCPolarity_High: Output Compare active high
 *            		TIM_OCPolarity_Low: Output Compare active low
 * Return:          None.
 */
void TIM_OC6NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
	uint32_t tmpccer = 0;
	
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
		
	tmpccer = TIMx->CCER;

	/* Set or Reset the CC6NP Bit */
	tmpccer &= (uint32_t)~TIM_CCER_CC6NP;
	tmpccer |= (uint32_t)(TIM_OCNPolarity << 20);

	/* Write to TIMx CCER register */
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TIM_CCxCmd
 * Description:     Enables or disables the TIM Capture Compare Channel x.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				TIM_Channel: specifies the TIM Channel
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_Channel_1: TIM_Channel_1
 * 					  TIM_Channel_2: TIM_Channel_2
 *                    TIM_Channel_3: TIM_Channel_3
 *                    TIM_Channel_4: TIM_Channel_4
 * 					  TIM_Channel_5: TIM_Channel_5
 *                    TIM_Channel_6: TIM_Channel_6
 *                   TIM_CCx: specifies the TIM Channel CCxE bit new state.
 *                    This parameter can be: TIM_CCx_Enable or TIM_CCx_Disable. 
 * Return:          None.
 */
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_CCx)
{
	uint32_t tmp = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	assert_param(IS_TIM_CHANNEL(TIM_Channel));
	assert_param(IS_TIM_CCX(TIM_CCx));
	/*If the channels is 5 or 6, then check if the timer is an advanced timer*/
	if((TIM_Channel == TIM_Channel_6) ||(TIM_Channel == TIM_Channel_5))
	{
		assert_param(IS_TIM_ADV_PERIPH(TIMx));
	}

	tmp = CCER_CCE_SET << TIM_Channel;

	/* Reset the CCxE Bit */
	TIMx->CCER &= (uint32_t)~ tmp;

	/* Set or reset the CCxE Bit */ 
	TIMx->CCER |=  (uint32_t)(TIM_CCx << TIM_Channel);
}

/*
 * Function:        TIM_CCxNCmd
 * Description:     Enables or disables the TIM Capture Compare Channel xN.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				TIM_Channel: specifies the TIM Channel
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_Channel_1: TIM_Channel_1
 * 					  TIM_Channel_2: TIM_Channel_2
 *                    TIM_Channel_3: TIM_Channel_3
 *                    TIM_Channel_4: TIM_Channel_4
 * 					  TIM_Channel_5: TIM_Channel_5
 *                    TIM_Channel_6: TIM_Channel_6
 *                   TIM_CCxN: specifies the TIM Channel CCxNE bit new state.
 *                    This parameter can be: TIM_CCxN_Enable or TIM_CCxN_Disable. 
 * Return:          None.
 */
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_CCxN)
{
	uint32_t tmp = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_TIM_CHANNEL(TIM_Channel));
	assert_param(IS_TIM_CCXN(TIM_CCxN));

	tmp = CCER_CCNE_SET << TIM_Channel;

	/* Reset the CCxNE Bit */
	TIMx->CCER &= (uint32_t) ~tmp;

	/* Set or reset the CCxNE Bit */ 
	TIMx->CCER |=  (uint32_t)(TIM_CCxN << TIM_Channel);
}

/*
 * Function:        TIM_CCxNCmd
 * Description:     Enables or disables the TIM Capture Compare Channel xN.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				TIM_Channel: specifies the TIM Channel
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_Channel_1: TIM_Channel_1
 * 					  TIM_Channel_2: TIM_Channel_2
 *                    TIM_Channel_3: TIM_Channel_3
 *                    TIM_Channel_4: TIM_Channel_4
 * 					  TIM_Channel_5: TIM_Channel_5
 *                    TIM_Channel_6: TIM_Channel_6
 *                   TIM_CCxN: specifies the TIM Channel CCxNE bit new state.
 *                    This parameter can be: TIM_CCxN_Enable or TIM_CCxN_Disable. 
 * Return:          None.
 */
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));
	assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
	assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
	assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));
	
		if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
	{
		/* TI1 Configuration */
		TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
				TIM_ICInitStruct->TIM_ICSelection,
				TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
	}
	else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
	{
		/* TI2 Configuration */
		assert_param(IS_TIM_ALL_PERIPH(TIMx));
		TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
				TIM_ICInitStruct->TIM_ICSelection,
				TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
	}
	else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
	{
		/* TI3 Configuration */
		assert_param(IS_TIM_ALL_PERIPH(TIMx));
		TI3_Config(TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
				TIM_ICInitStruct->TIM_ICSelection,
				TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
	}
	else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_4)
	{
		/* TI4 Configuration */
		assert_param(IS_TIM_ALL_PERIPH(TIMx));
		TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
				TIM_ICInitStruct->TIM_ICSelection,
				TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
	}
	else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_5)
	{
		/* TI5 Configuration */
		assert_param(IS_TIM_ADV_PERIPH(TIMx));
		TI5_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
				TIM_ICInitStruct->TIM_ICSelection,
				TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC5Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
	}
	else
	{
		/* TI6 Configuration */
		assert_param(IS_TIM_ADV_PERIPH(TIMx));
		TI6_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
				TIM_ICInitStruct->TIM_ICSelection,
				TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC6Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
	}
}

/*
 * Function:        TIM_ICStructInit
 * Description:     Fills each TIM_ICInitStruct member with its default value.
 * Param:           TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure which will
 *         			be initialized.
 * Return:          None.
 */
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* Set the default configuration */
  TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
  TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

/*
 * Function:        TIM_PWMIConfig
 * Description:     Configures the TIM peripheral according to the specified parameters
 * 					in the TIM_ICInitStruct to measure an external PWM signal.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure that contains
 * 					the configuration information for the specified TIM peripheral.
 * Return:          None.
 */
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
	uint32_t icoppositepolarity = TIM_ICPolarity_Rising;
	uint32_t icoppositeselection = TIM_ICSelection_DirectTI;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Select the Opposite Input Polarity */
	if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
	{
		icoppositepolarity = TIM_ICPolarity_Falling;
	}
	else
	{
		icoppositepolarity = TIM_ICPolarity_Rising;
	}
	/* Select the Opposite Input */
	if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
	{
		icoppositeselection = TIM_ICSelection_IndirectTI;
	}
	else
	{
		icoppositeselection = TIM_ICSelection_DirectTI;
	}
	if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
	{
		/* TI1 Configuration */
		TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
				TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
		/* TI2 Configuration */
		TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
	}
	else
	{ 
		/* TI2 Configuration */
		TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
				TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
		/* TI1 Configuration */
		TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
		/* Set the Input Capture Prescaler value */
		TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
	}
}

/*
 * Function:        TIM_GetCapture1
 * Description:    	Gets the TIMx Input Capture 1 value.
 * 					in the TIM_ICInitStruct to measure an external PWM signal.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * Return:          None.
 */
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  /* Get the Capture 1 Register value */
  return TIMx->CCR1;
}

/*
 * Function:        TIM_GetCapture2
 * Description:    	Gets the TIMx Input Capture 2 value.
 * 					in the TIM_ICInitStruct to measure an external PWM signal.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * Return:          None.
 */
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  /* Get the Capture 2 Register value */
  return TIMx->CCR2;
}

/*
 * Function:        TIM_GetCapture3
 * Description:    	Gets the TIMx Input Capture 3 value.
 * 					in the TIM_ICInitStruct to measure an external PWM signal.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * Return:          None.
 */
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  /* Get the Capture 3 Register value */
  return TIMx->CCR3;
}

/*
 * Function:        TIM_GetCapture4
 * Description:    	Gets the TIMx Input Capture 4 value.
 * 					in the TIM_ICInitStruct to measure an external PWM signal.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * Return:          None.
 */
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  /* Get the Capture 4 Register value */
  return TIMx->CCR4;
}

/*
 * Function:        TIM_GetCapture5
 * Description:    	Gets the TIMx Input Capture 5 value.
 * 					in the TIM_ICInitStruct to measure an external PWM signal.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * Return:          None.
 */
uint32_t TIM_GetCapture5(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ADV_PERIPH(TIMx));

  /* Get the Capture 5 Register value */
  return TIMx->CCR5;
}

/*
 * Function:        TIM_GetCapture6
 * Description:    	Gets the TIMx Input Capture 6 value.
 * 					in the TIM_ICInitStruct to measure an external PWM signal.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * Return:          None.
 */
uint32_t TIM_GetCapture6(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ADV_PERIPH(TIMx));

  /* Get the Capture 6 Register value */
  return TIMx->CCR6;
}

/*
 * Function:        TIM_SetIC1Prescaler
 * Description:     Sets the TIMx Input Capture 1 prescaler.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ICPSC: specifies the Input Capture1 prescaler new value.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPSC_DIV1: no prescaler
 * 					  TIM_ICPSC_DIV2: capture is done once every 2 events
 *                    TIM_ICPSC_DIV4: capture is done once every 4 events
 * 					  TIM_ICPSC_DIV8: capture is done once every 8 events
 * Return:          None.
 */
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC1PSC Bits */
  TIMx->CCMR1 &= (uint32_t)~TIM_CCMR1_IC1PSC;

  /* Set the IC1PSC value */
  TIMx->CCMR1 |= TIM_ICPSC;
}

/*
 * Function:        TIM_SetIC2Prescaler
 * Description:     Sets the TIMx Input Capture 2 prescaler.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ICPSC: specifies the Input Capture2 prescaler new value.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPSC_DIV1: no prescaler
 * 					  TIM_ICPSC_DIV2: capture is done once every 2 events
 *                    TIM_ICPSC_DIV4: capture is done once every 4 events
 * 					  TIM_ICPSC_DIV8: capture is done once every 8 events
 * Return:          None.
 */
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

	/* Reset the IC2PSC Bits */
	TIMx->CCMR1 &= (uint32_t)~TIM_CCMR1_IC2PSC;

	/* Set the IC2PSC value */
	TIMx->CCMR1 |= (uint32_t)(TIM_ICPSC << 8);
}
/*
 * Function:        TIM_SetIC3Prescaler
 * Description:     Sets the TIMx Input Capture 3 prescaler.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ICPSC: specifies the Input Capture3 prescaler new value.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPSC_DIV1: no prescaler
 * 					  TIM_ICPSC_DIV2: capture is done once every 2 events
 *                    TIM_ICPSC_DIV4: capture is done once every 4 events
 * 					  TIM_ICPSC_DIV8: capture is done once every 8 events
 * Return:          None.
 */
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC3PSC Bits */
  TIMx->CCMR2 &= (uint32_t)~TIM_CCMR2_IC3PSC;

  /* Set the IC3PSC value */
  TIMx->CCMR2 |= TIM_ICPSC;
}

/*
 * Function:        TIM_SetIC4Prescaler
 * Description:     Sets the TIMx Input Capture 4 prescaler.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ICPSC: specifies the Input Capture3 prescaler new value.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPSC_DIV1: no prescaler
 * 					  TIM_ICPSC_DIV2: capture is done once every 2 events
 *                    TIM_ICPSC_DIV4: capture is done once every 4 events
 * 					  TIM_ICPSC_DIV8: capture is done once every 8 events
 * Return:          None.
 */
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{  
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC4PSC Bits */
  TIMx->CCMR2 &= (uint32_t)~TIM_CCMR2_IC4PSC;

  /* Set the IC4PSC value */
  TIMx->CCMR2 |= (uint32_t)(TIM_ICPSC << 8);
}

/*
 * Function:        TIM_SetIC5Prescaler
 * Description:     Sets the TIMx Input Capture 5 prescaler.
 * Param:           TIMx: where x can be 0 ,1 ,2 or 5 to select the TIM peripheral.
 * 					TIM_ICPSC: specifies the Input Capture5 prescaler new value.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPSC_DIV1: no prescaler
 * 					  TIM_ICPSC_DIV2: capture is done once every 2 events
 *                    TIM_ICPSC_DIV4: capture is done once every 4 events
 * 					  TIM_ICPSC_DIV8: capture is done once every 8 events
 * Return:          None.
 */
void TIM_SetIC5Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{  
  /* Check the parameters */
  assert_param(IS_TIM_ADV_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC4PSC Bits */
  TIMx->CCMR3 &= (uint32_t)~TIM_CCMR3_IC5PSC;

  /* Set the IC4PSC value */
  TIMx->CCMR3 |= TIM_ICPSC;
}

/*
 * Function:        TIM_SetIC6Prescaler
 * Description:     Sets the TIMx Input Capture 6 prescaler.
 * Param:           TIMx: where x can be 0 ,1 ,2 or 5 to select the TIM peripheral.
 * 					TIM_ICPSC: specifies the Input Capture3 prescaler new value.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPSC_DIV1: no prescaler
 * 					  TIM_ICPSC_DIV2: capture is done once every 2 events
 *                    TIM_ICPSC_DIV4: capture is done once every 4 events
 * 					  TIM_ICPSC_DIV8: capture is done once every 8 events
 * Return:          None.
 */
void TIM_SetIC6Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{  
  /* Check the parameters */
  assert_param(IS_TIM_ADV_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC4PSC Bits */
  TIMx->CCMR3 &= (uint32_t)~TIM_CCMR3_IC6PSC;

  /* Set the IC4PSC value */
   TIMx->CCMR3 |= (uint32_t)(TIM_ICPSC << 8);
}

/*
 * Function:        TIM_BDTRConfig
 * Description:     Configures the Break feature, dead time, Lock level, OSSI/OSSR State
 *         			and the AOE(automatic output enable).
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 * 					TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure that
 *      		   	contains the BDTR Register configuration  information for the TIM peripheral.
 * Return:          None.
 */
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_ADV_PERIPH(TIMx));
  assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
  assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
  assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
  assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
  assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
  assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));

  /* Set the Lock level, the Break enable Bit and the Polarity, the OSSR State,
     the OSSI State, the dead time value and the Automatic Output Enable Bit */
  TIMx->BDTR = (uint32_t)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
             TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
             TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
             TIM_BDTRInitStruct->TIM_AutomaticOutput;
}

/*
 * Function:        TIM_BDTRStructInit
 * Description:     Fills each TIM_BDTRInitStruct member with its default value..
 * Param:           TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure which
 *         			be initialized.
 * Return:          None.
 */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct)
{
  /* Set the default configuration */
  TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/*
 * Function:        TIM_CtrlPWMOutputs
 * Description:     Enables or disables the TIM peripheral Main Outputs.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 *                	NewState: new state of the TIM peripheral Main Outputs.
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_FunctionalState_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable the TIM Main Output */
		TIMx->BDTR |= TIM_BDTR_MOE;
	}
	else
	{
		/* Disable the TIM Main Output */
		TIMx->BDTR &= (uint32_t)~TIM_BDTR_MOE;
	}  
}

/*
 * Function:        TIM_SelectCOM
 * Description:     Selects the TIM peripheral Commutation event.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 *                	NewState: new state of the Commutation event.
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_FunctionalState_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Set the COM Bit */
		TIMx->CR2 |= TIM_CR2_CCUS;
	}
	else
	{
		/* Reset the COM Bit */
		TIMx->CR2 &= (uint32_t)~TIM_CR2_CCUS;
	}
}

/*
 * Function:        TIM_CCPreloadControl
 * Description:     Sets or Resets the TIM peripheral Capture Compare Preload Control bit.
 * Param:           TIMx: where x can be 0,1,2 or 5 to select the TIM peripheral.
 *                	NewState: new state of the Capture Compare Preload Control bit
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState)
{ 
	/* Check the parameters */
	assert_param(IS_TIM_ADV_PERIPH(TIMx));
	assert_param(IS_FunctionalState_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Set the CCPC Bit */
		TIMx->CR2 |= TIM_CR2_CCPC;
	}
	else
	{
		/* Reset the CCPC Bit */
		TIMx->CR2 &= (uint32_t)~TIM_CR2_CCPC;
	}
}

/*
 * Function:        TIM_ITConfig
 * Description:     Enables or disables the specified TIM interrupts.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_IT: specifies the TIM interrupts sources to be enabled or disabled.
 * 					 This parameter can be any combination of the following values:
 * 					  TIM_IT_Update: TIM update Interrupt source
 * 					  TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
 * 					  TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
 * 					  TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
 * 					  TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
 * 					  TIM_IT_CC5: TIM Capture Compare 5 Interrupt source	
 * 					  TIM_IT_CC6: TIM Capture Compare 6 Interrupt source
 * 					  TIM_IT_COM: TIM Commutation Interrupt source
 * 					  TIM_IT_Trigger: TIM Trigger Interrupt source
 * 					  TIM_IT_Break: TIM Break Interrupt source
 *                	NewState: new state of the TIM interrupts.
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_ITConfig(TIM_TypeDef* TIMx, uint32_t TIM_IT, FunctionalState NewState)
{  
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_IT(TIM_IT));
	assert_param(IS_FunctionalState_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* Enable the Interrupt sources */
		TIMx->DIER |= TIM_IT;
	}
	else
	{
		/* Disable the Interrupt sources */
		TIMx->DIER &= (uint32_t)~TIM_IT;
	}
}

/*
 * Function:        TIM_CCPreloadControl
 * Description:     Configures the TIMx event to be generate by software.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_EventSource: specifies the TIM interrupts sources to be enabled or disabled.
 * 					 This parameter can be any combination of the following values:
 * 					  TIM_EventSource_Update: TIM update Interrupt source
 * 					  TIM_EventSource_CC1: TIM Capture Compare 1 Interrupt source
 * 					  TIM_EventSource_CC2: TIM Capture Compare 2 Interrupt source
 * 					  TIM_EventSource_CC3: TIM Capture Compare 3 Interrupt source
 * 					  TIM_EventSource_CC4: TIM Capture Compare 4 Interrupt source
 * 					  TIM_EventSource_CC5: TIM Capture Compare 5 Interrupt source	
 * 					  TIM_EventSource_CC6: TIM Capture Compare 6 Interrupt source
 * 					  TIM_EventSource_COM: TIM Commutation Interrupt source
 * 					  TIM_EventSource_Trigger: TIM Trigger Interrupt source
 * 					  TIM_EventSource_Break: TIM Break Interrupt source
 * Return:          None.
 */
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint32_t TIM_EventSource)
{ 
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource));
	
	/* Set the event sources */
	TIMx->EGR = TIM_EventSource;
}

/*
 * Function:        TIM_GetFlagStatus
 * Description:     Checks whether the specified TIM flag is set or not.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_FLAG: specifies the TIM interrupts sources to be enabled or disabled.
 * 					 This parameter can be any combination of the following values:
 * 					  TIM_FLAG_Update: TIM update Flag
 * 					  TIM_FLAG_CC1: TIM Capture Compare 1 Flag
 * 					  TIM_FLAG_CC2: TIM Capture Compare 2 Flag
 * 					  TIM_FLAG_CC3: TIM Capture Compare 3 Flag
 * 					  TIM_FLAG_CC4: TIM Capture Compare 4 Flag
 * 					  TIM_FLAG_CC5: TIM Capture Compare 5 Flag
 * 					  TIM_FLAG_CC6: TIM Capture Compare 6 Flag
 * 					  TIM_FLAG_COM: TIM Commutation Flag
 * 					  TIM_FLAG_Trigger: TIM Trigger Flag
 * 					  TIM_FLAG_Break: TIM Break Flag
 * 					  TIM_FLAG_CC1OF: TIM Capture Compare 1 over capture Flag
 * 					  TIM_FLAG_CC2OF: TIM Capture Compare 2 over capture Flag
 *                    TIM_FLAG_CC3OF: TIM Capture Compare 3 over capture Flag
 *                    TIM_FLAG_CC4OF: TIM Capture Compare 4 over capture Flag
 *					  TIM_FLAG_CC5OF: TIM Capture Compare 5 over capture Flag
 * 					  TIM_FLAG_CC6OF: TIM Capture Compare 6 over capture Flag
 * Return:          The new state of TIM_FLAG (SET or RESET).
 */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint32_t TIM_FLAG)
{ 
	ITStatus bitstatus = RESET;  
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_GET_FLAG(TIM_FLAG));

	
	if ((TIMx->SR & TIM_FLAG) != (uint32_t)RESET)
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
 * Function:        TIM_ClearFlag
 * Description:     Clears the TIMx's pending flags.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_FLAG: specifies the TIM interrupts sources to be enabled or disabled.
 * 					 This parameter can be any combination of the following values:
 * 					  TIM_FLAG_Update: TIM update Flag
 * 					  TIM_FLAG_CC1: TIM Capture Compare 1 Flag
 * 					  TIM_FLAG_CC2: TIM Capture Compare 2 Flag
 * 					  TIM_FLAG_CC3: TIM Capture Compare 3 Flag
 * 					  TIM_FLAG_CC4: TIM Capture Compare 4 Flag
 * 					  TIM_FLAG_CC5: TIM Capture Compare 5 Flag
 * 					  TIM_FLAG_CC6: TIM Capture Compare 6 Flag
 * 					  TIM_FLAG_COM: TIM Commutation Flag
 * 					  TIM_FLAG_Trigger: TIM Trigger Flag
 * 					  TIM_FLAG_Break: TIM Break Flag
 * 					  TIM_FLAG_CC1OF: TIM Capture Compare 1 over capture Flag
 * 					  TIM_FLAG_CC2OF: TIM Capture Compare 2 over capture Flag
 *                    TIM_FLAG_CC3OF: TIM Capture Compare 3 over capture Flag
 *                    TIM_FLAG_CC4OF: TIM Capture Compare 4 over capture Flag
 *					  TIM_FLAG_CC5OF: TIM Capture Compare 5 over capture Flag
 * 					  TIM_FLAG_CC6OF: TIM Capture Compare 6 over capture Flag
 * Return:          None.
 */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint32_t TIM_FLAG)
{  
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	
	/* Clear the flags */
	TIMx->SR = (uint32_t)~TIM_FLAG;
}

/*
 * Function:        TIM_GetITStatus
 * Description:     Checks whether the TIM interrupt has occurred or not.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_IT: specifies the TIM interrupts sources to be enabled or disabled.
 * 					 This parameter can be any combination of the following values:
 * 					  TIM_IT_Update: TIM update Interrupt source
 * 					  TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
 * 					  TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
 * 					  TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
 * 					  TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
 * 					  TIM_IT_CC5: TIM Capture Compare 5 Interrupt source	
 * 					  TIM_IT_CC6: TIM Capture Compare 6 Interrupt source
 * 					  TIM_IT_COM: TIM Commutation Interrupt source
 * 					  TIM_IT_Trigger: TIM Trigger Interrupt source
 * 					  TIM_IT_Break: TIM Break Interrupt source
 * Return:          The new state of the TIM_IT(SET or RESET).
 */
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint32_t TIM_IT)
{
	ITStatus bitstatus = RESET;  
	uint32_t itstatus = 0x0, itenable = 0x0;
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_GET_IT(TIM_IT));
	
	itstatus = TIMx->SR & TIM_IT;
	
	itenable = TIMx->DIER & TIM_IT;
	if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
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
 * Function:        TIM_ClearITPendingBit
 * Description:     Clears the TIMx's interrupt pending bits.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_IT: specifies the TIM interrupts sources to be enabled or disabled.
 * 					 This parameter can be any combination of the following values:
 * 					  TIM_IT_Update: TIM update Interrupt source
 * 					  TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
 * 					  TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
 * 					  TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
 * 					  TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
 * 					  TIM_IT_CC5: TIM Capture Compare 5 Interrupt source	
 * 					  TIM_IT_CC6: TIM Capture Compare 6 Interrupt source
 * 					  TIM_IT_COM: TIM Commutation Interrupt source
 * 					  TIM_IT_Trigger: TIM Trigger Interrupt source
 * 					  TIM_IT_Break: TIM Break Interrupt source
 * Return:          None.
 */
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint32_t TIM_IT)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Clear the IT pending Bit */
	TIMx->SR = (uint32_t)~TIM_IT;
}

/*
 * Function:        TIM_DMAConfig
 * Description:     Configures the TIMx's DMA interface.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_DMABase: DMA Base address.
 * 					 This parameter can be one of the following values:
 * 					  TIM_DMABase_CR1                  
 * 					  TIM_DMABase_CR2                  
 * 					  TIM_DMABase_SMCR                 
 * 					  TIM_DMABase_DIER                 
 * 					  TIM_DMABase_SR                   
 * 					  TIM_DMABase_EGR                  
 * 					  TIM_DMABase_CCMR1                
 * 					  TIM_DMABase_CCMR2                
 * 					  TIM_DMABase_CCMR3                
 * 					  TIM_DMABase_CCER                 
 * 					  TIM_DMABase_CNT                  
 * 					  TIM_DMABase_PSC                  
 * 					  TIM_DMABase_ARR                  
 * 					  TIM_DMABase_RCR                  
 * 					  TIM_DMABase_CCR1                 
 * 					  TIM_DMABase_CCR2                 
 * 					  TIM_DMABase_CCR3                 
 * 					  TIM_DMABase_CCR4                 
 * 					  TIM_DMABase_CCR5                 
 * 					  TIM_DMABase_CCR6                 
 * 					  TIM_DMABase_BDTR                 
 * 					  TIM_DMABase_DCR                  
 * 					  TIM_DMABase_DMAR                 
 * 					  TIM_DMABase_AF1                  
 * 					TIM_DMABurstLength: DMA Burst length. This parameter can be one value
 * 					between: TIM_DMABurstLength_1Transfer and TIM_DMABurstLength_18Transfers.
 * Return:          None.
 */
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint32_t TIM_DMABase, uint32_t TIM_DMABurstLength)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_DMA_BASE(TIM_DMABase)); 
	assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));

	/* Set the DMA Base and the DMA Burst Length */
	TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
	}

/*
 * Function:        TIM_DMACmd
 * Description:     Enables or disables the TIMx's DMA Requests.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_DMASource: specifies the DMA Request sources.
 * 					 This parameter can be any combination of the following values:
 *  				  TIM_DMA_Update: TIM update Interrupt source
 *					  TIM_DMA_CC1: TIM Capture Compare 1 DMA source
 *					  TIM_DMA_CC2: TIM Capture Compare 2 DMA source
 *					  TIM_DMA_CC3: TIM Capture Compare 3 DMA source
 *					  TIM_DMA_CC4: TIM Capture Compare 4 DMA source
 *                    TIM_DMA_CC5: TIM Capture Compare 5 DMA source
 *                    TIM_DMA_CC6: TIM Capture Compare 6 DMA source
 *  				  NewState: new state of the DMA Request sources.
 * 					  This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_DMACmd(TIM_TypeDef* TIMx, uint32_t TIM_DMASource, FunctionalState NewState)
{ 
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
	assert_param(IS_FunctionalState_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* Enable the DMA sources */
		TIMx->DIER |= TIM_DMASource; 
	}
	else
	{
		/* Disable the DMA sources */
		TIMx->DIER &= (uint32_t)~TIM_DMASource;
	}
}

/*
 * Function:        TIM_SelectCCDMA
 * Description:     Selects the TIMx peripheral Capture Compare DMA source.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				NewState: new state of the DMA Request sources.
 * 					  This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_FunctionalState_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Set the CCDS Bit */
		TIMx->CR2 |= TIM_CR2_CCDS;
	}
	else
	{
		/* Reset the CCDS Bit */
		TIMx->CR2 &= (uint32_t)~TIM_CR2_CCDS;
	}
}

/*
 * Function:        TIM_InternalClockConfig
 * Description:     Configures the TIMx internal Clock
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * Return:          None.
 */
void TIM_InternalClockConfig(TIM_TypeDef* TIMx)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Disable slave mode to clock the prescaler directly with the internal clock */
	TIMx->SMCR &=  (uint32_t)~TIM_SMCR_SMS;
}

/*
 * Function:        TIM_ITRxExternalClockConfig
 * Description:     Configures the TIMx Internal Trigger as External Clock
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_InputTriggerSource: Trigger source.
 * 					 This parameter can be one of the following values:
 *           		  TIM_TS_ITR0: Internal Trigger 0
 *           		  TIM_TS_ITR1: Internal Trigger 1
 *           		  TIM_TS_ITR2: Internal Trigger 2
 *           		  TIM_TS_ITR3: Internal Trigger 3			
 * Return:          None.
 */
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint32_t TIM_InputTriggerSource)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));

	/* Select the Internal Trigger */
	TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);

	/* Select the External clock mode1 */
	TIMx->SMCR |= TIM_SlaveMode_External1;
}

/*
 * Function:        TIM_TIxExternalClockConfig
 * Description:     Configures the TIMx Trigger as External Clock
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_TIxExternalCLKSource: Trigger source.
 * 					 This parameter can be one of the following values:
 *            		 TIM_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
 *            		 TIM_TIxExternalCLK1Source_TI1: Filtered Timer Input 1
 *            		 TIM_TIxExternalCLK1Source_TI2: Filtered Timer Input 2
 * 					TIM_ICPolarity: specifies the TIx Polarity.
 * 					 This parameter can be one of the following values:
 * 					  TIM_ICPolarity_Rising
 *					  TIM_ICPolarity_Falling
 *                  ICFilter: specifies the filter value.
 * 					 This parameter must be a value between 0x0 and 0xF.
 * Return:          None.
 */
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint32_t TIM_TIxExternalCLKSource,
                                uint32_t TIM_ICPolarity, uint32_t ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
  assert_param(IS_TIM_IC_FILTER(ICFilter));

  /* Configure the Timer Input Clock Source */
  if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  /* Select the Trigger source */
  TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
  /* Select the External clock mode1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/*
 * Function:        TIM_ETRClockMode1Config
 * Description:     Configures the External clock Mode1
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ExtTRGPrescaler: The external Trigger Prescaler.
 *          		 This parameter can be one of the following values:
  *            		  TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *            		  TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            		  TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *             	  TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  *  				TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          		 This parameter can be one of the following values:
  *            		  TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
  *            		  TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  *  				ExtTRGFilter: External Trigger Filter.
  *          		 This parameter must be a value between 0x00 and 0x0F
 * Return:          None.
 */
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler,
                            uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
	uint32_t tmpsmcr = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
	assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
	assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
	/* Configure the ETR Clock source */
	TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
	
	/* Get the TIMx SMCR register value */
	tmpsmcr = TIMx->SMCR;

	/* Reset the SMS Bits */
	tmpsmcr &= (uint32_t)~TIM_SMCR_SMS;

	/* Select the External clock mode1 */
	tmpsmcr |= TIM_SlaveMode_External1;

	/* Select the Trigger selection : ETRF */
	tmpsmcr &= (uint32_t)~TIM_SMCR_TS;
	tmpsmcr |= TIM_TS_ETRF;

	/* Write to TIMx SMCR */
	TIMx->SMCR = tmpsmcr;
}

/*
 * Function:        TIM_ETRClockMode2Config
 * Description:     Configures the External clock Mode2
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ExtTRGPrescaler: The external Trigger Prescaler.
 *          		 This parameter can be one of the following values:
  *            		  TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *            		  TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            		  TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *             	  TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  *  				TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          		 This parameter can be one of the following values:
  *            		  TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
  *            		  TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  *  				ExtTRGFilter: External Trigger Filter.
  *          		 This parameter must be a value between 0x00 and 0x0F
 * Return:          None.
 */
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler, 
                             uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
	assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
	assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

	/* Configure the ETR Clock source */
	TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);

	/* Enable the External clock mode2 */
	TIMx->SMCR |= TIM_SMCR_ECE;
}

/*
 * Function:        TIM_SelectInputTrigger
 * Description:     Selects the Input Trigger source
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_InputTriggerSource: Trigger source.
 * 					 This parameter can be one of the following values:
 *           		  TIM_TS_ITR0: Internal Trigger 0
 *           		  TIM_TS_ITR1: Internal Trigger 1
 *           		  TIM_TS_ITR2: Internal Trigger 2
 *           		  TIM_TS_ITR3: Internal Trigger 3
 * 					  TIM_TS_TI1F_ED: TI1 Edge Detector
 * 					  TIM_TS_TI1FP1: Filtered Timer Input 1
 * 					  TIM_TS_TI2FP2: Filtered Timer Input 2
 * 					  TIM_TS_ETRF: External Trigger input			
 * Return:          None.
 */
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint32_t TIM_InputTriggerSource)
{
	uint32_t tmpsmcr = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));

	/* Get the TIMx SMCR register value */
	tmpsmcr = TIMx->SMCR;

	/* Reset the TS Bits */
	tmpsmcr &= (uint32_t)~TIM_SMCR_TS;

	/* Set the Input Trigger source */
	tmpsmcr |= TIM_InputTriggerSource;

	/* Write to TIMx SMCR */
	TIMx->SMCR = tmpsmcr;
}

/*
 * Function:        TIM_SelectOutputTrigger
 * Description:     Selects the TIMx Trigger Output Mode.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_TRGOSource: specifies the Trigger Output source.
 * 					 This parameter can be the following values:
 *            		  TIM_TRGOSource_Reset:  The UG bit in the TIM_EGR register is used as the trigger output(TRGO)
 *            		  TIM_TRGOSource_Enable: The Counter Enable CEN is used as the trigger output(TRGO)
 *            		  TIM_TRGOSource_Update: The update event is selected as the trigger output(TRGO)
 *            		  TIM_TRGOSource_OC1: The trigger output sends a positive pulse when the CC1IF flag
 *            		                      is to be set, as soon as a capture or compare match occurs(TRGO)
 *            		  TIM_TRGOSource_OC1Ref: OC1REF signal is used as the trigger output(TRGO)
 *            		  TIM_TRGOSource_OC2Ref: OC2REF signal is used as the trigger output(TRGO)
 *            		  TIM_TRGOSource_OC3Ref: OC3REF signal is used as the trigger output(TRGO)
 *            		  TIM_TRGOSource_OC4Ref: OC4REF signal is used as the trigger output(TRGO)
 *					  TIM_TRGO2Source_Reset: The UG bit in the TIM_EGR register is used as the trigger output(TRGO2)                    
 *					  TIM_TRGO2Source_Enable: The Counter Enable CEN is used as the trigger output(TRGO2)                   
 *					  TIM_TRGO2Source_Update: The update event is selected as the trigger output(TRGO2)                     
 *					  TIM_TRGO2Source_OC1: The trigger output sends a positive pulse when the CC1IF flag
 *            		                       is to be set, as soon as a capture or compare match occurs(TRGO2)                       
 *					  TIM_TRGO2Source_OC1Ref: OC1REF signal is used as the trigger output(TRGO2)                    
 *					  TIM_TRGO2Source_OC2Ref: OC2REF signal is used as the trigger output(TRGO2)                  
 *					  TIM_TRGO2Source_OC3Ref: OC3REF signal is used as the trigger output(TRGO2)                   
 *					  TIM_TRGO2Source_OC4Ref: OC4REF signal is used as the trigger output(TRGO2)                   
 *					  TIM_TRGO2Source_OC5Ref: OC5REF signal is used as the trigger output(TRGO2)                     
 *					  TIM_TRGO2Source_OC6Ref: OC6REF signal is used as the trigger output(TRGO2)                     
 *					  TIM_TRGO2Source_OC4Ref_BothEdge: When OC4REF signal is rising or falling,
 														it is used as the trigger output(TRGO2)           
 *					  TIM_TRGO2Source_OC6Ref_BothEdge: When OC6REF signal is rising or falling,
 														it is used as the trigger output(TRGO2)          
 *					  TIM_TRGO2Source_OC46Ref_Rising: When OC4REF signal or OC6REF signal is rising ,
 													  it is used as the trigger output(TRGO2)            
 *					  TIM_TRGO2Source_OC4_Rising_OR_OC6_Falling:When OC4REF signal is rising or  OC6REF signal is falling ,
 																it is used as the trigger output(TRGO2)
 *					  TIM_TRGO2Source_OC5_Rising_OR_OC6_Rising:When OC5REF signal or OC6REF signal is rising ,
 													  		   it is used as the trigger output(TRGO2)        
 *					  TIM_TRGO2Source_OC5_Rising_OR_OC6_Falling:When OC5REF signal is rising or  OC6REF signal is falling ,
 																it is used as the trigger output(TRGO2)
 *                    		
 * Return:          None.
 */
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint32_t TIM_TRGOSource)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));

	/* Reset the MMS Bits */
	TIMx->CR2 &= (uint32_t)~TIM_CR2_MMS;
	/* Reset the MMS2 Bits */
	TIMx->CR2 &= (uint32_t)~TIM_CR2_MMS2;

	/* Select the TRGO source */
	TIMx->CR2 |=  TIM_TRGOSource;
}


/*
 * Function:        TIM_SelectSlaveMode
 * Description:     Selects the TIMx Slave Mode.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_SlaveMode: specifies the Timer Slave Mode.
 *            		 TIM_SlaveMode_Reset: Rising edge of the selected trigger signal(TRGI) reinitialize 
 *            		                      the counter and triggers an update of the registers
 *            		 TIM_SlaveMode_Gated:     The counter clock is enabled when the trigger signal (TRGI) is high
 *            		 TIM_SlaveMode_Trigger:   The counter starts at a rising edge of the trigger TRGI
 *            		 TIM_SlaveMode_External1: Rising edges of the selected trigger (TRGI) clock the counter	
 * Return:          None.
 */
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint32_t TIM_SlaveMode)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));

	/* Reset the SMS Bits */
	TIMx->SMCR &= (uint32_t)~TIM_SMCR_SMS;

	/* Select the Slave Mode */
	TIMx->SMCR |= TIM_SlaveMode;
}

/*
 * Function:        TIM_ETRConfig
 * Description:     Configures the TIMx External Trigger (ETR).
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_ExtTRGPrescaler: The external Trigger Prescaler.
 *          		 This parameter can be one of the following values:
  *            		  TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *            		  TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            		  TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *             	  TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  *  				TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          		 This parameter can be one of the following values:
  *            		  TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
  *            		  TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  *  				ExtTRGFilter: External Trigger Filter.
  *          		 This parameter must be a value between 0x00 and 0x0F
 * Return:          None.
 */
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler,
                   uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
	uint32_t tmpsmcr = 0;

	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
	assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
	assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

	tmpsmcr = TIMx->SMCR;

	/* Reset the ETR Bits */
	tmpsmcr &= SMCR_ETR_MASK;

	/* Set the Prescaler, the Filter value and the Polarity */
	tmpsmcr |= (uint32_t)(TIM_ExtTRGPrescaler | (uint32_t)(TIM_ExtTRGPolarity | (uint32_t)(ExtTRGFilter << (uint32_t)8)));

	/* Write to TIMx SMCR */
	TIMx->SMCR = tmpsmcr;
}

/*
 * Function:        TIM_SelectInputTrigger
 * Description:     Selects External Trigger input source
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_InputETRSource: Trigger source.
 * 					 This parameter can be one of the following values:
 *           		  TIM_TS_ETR0: External Trigger 0
 *           		  TIM_TS_ETR1: External Trigger 1		
 * Return:          None.
 */
void TIM_SelectInputETR(TIM_TypeDef* TIMx,uint32_t TIM_InputETRSource)
{
		uint32_t tmpaf1 = 0;

		/* Check the parameters */
		assert_param(IS_TIM_ADV_PERIPH(TIMx)); 
		assert_param(IS_TIM_EXTERNAL_TRIGGER_SELECTION(TIM_InputETRSource));

		/* Get the TIMx SMCR register value */
		tmpaf1 = TIMx->AF1;

		/* Reset the TS Bits */
		tmpaf1 &= (uint32_t)~TIM_AF1_ETRSEL;

		/* Set the External Trigger source */
		tmpaf1 |= TIM_InputETRSource;

		/* Write to TIMx AF1 */
		TIMx->AF1 = tmpaf1;
}

/*
 * Function:        TIM_EncoderInterfaceConfig
 * Description:     Configures the TIMx Encoder Interface.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 * 					TIM_EncoderMode: specifies the TIMx Encoder Mode.
 *          		 This parameter can be one of the following values:
 *            		 TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
 *            		 TIM_EncoderMode_TI2: Counter counts on TI2FP2 edge depending on TI1FP1 level.
 *            		 TIM_EncoderMode_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
 *  				TIM_IC1Polarity: specifies the IC1 Polarity
 *          		 This parameter can be one of the following values:
 *          		  TIM_ICPolarity_Falling: IC Falling edge.
 *          		  TIM_ICPolarity_Rising: IC Rising edge.
 * 					TIM_IC2Polarity: specifies the IC2 Polarity
 *                   This parameter can be one of the following values:
 *                    TIM_ICPolarity_Falling: IC Falling edge.
 *                    TIM_ICPolarity_Rising: IC Rising edge.
 * Return:          None.
 */
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint32_t TIM_EncoderMode,
                                uint32_t TIM_IC1Polarity, uint32_t TIM_IC2Polarity)
{
	uint32_t tmpsmcr = 0;
	uint32_t tmpccmr1 = 0;
	uint32_t tmpccer = 0;
		
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
	assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
	assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));

	/* Get the TIMx SMCR register value */
	tmpsmcr = TIMx->SMCR;

	/* Get the TIMx CCMR1 register value */
	tmpccmr1 = TIMx->CCMR1;

	/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;

	/* Set the encoder Mode */
	tmpsmcr &= (uint32_t)~TIM_SMCR_SMS;
	tmpsmcr |= TIM_EncoderMode;

	/* Select the Capture Compare 1 and the Capture Compare 2 as input */
	tmpccmr1 &= ((uint32_t)~TIM_CCMR1_CC1S) & ((uint32_t)~TIM_CCMR1_CC2S);
	tmpccmr1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;

	/* Set the TI1 and the TI2 Polarities */
	tmpccer &= ((uint32_t)~TIM_CCER_CC1P) & ((uint32_t)~TIM_CCER_CC2P);
	tmpccer |= (uint32_t)(TIM_IC1Polarity | (uint32_t)(TIM_IC2Polarity << (uint32_t)4));

	/* Write to TIMx SMCR */
	TIMx->SMCR = tmpsmcr;

	/* Write to TIMx CCMR1 */
	TIMx->CCMR1 = tmpccmr1;

	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}
/*
 * Function:        TIM_SelectHallSensor
 * Description:     Enables or disables the TIMx's Hall sensor interface.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *                	NewState: new state of the TIMx Hall sensor interface.
 *     		        This parameter can be: ENABLE or DISABLE.
 * Return:          None.
 */
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));
	assert_param(IS_FunctionalState_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Set the TI1S Bit */
		TIMx->CR2 |= TIM_CR2_TI1S;
	}
	else
	{
		/* Reset the TI1S Bit */
		TIMx->CR2 &= (uint32_t)~TIM_CR2_TI1S;
	}
}


/*
 * Function:        TI1_Config
 * Description:     Configure the TI1 as Input.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				 TIM_ICPolarity : The Input Polarity.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPolarity_Rising
 * 					  TIM_ICPolarity_Falling
 *                    TIM_ICPolarity_BothEdge
 *                  TIM_ICSelection: specifies the input to be used.
 *                    This parameter can be one of the following values:
 * 					  TIM_ICSelection_DirectTI: TIM Input 1 is selected to be connected to IC1.
 *                    TIM_ICSelection_IndirectTI: TIM Input 1 is selected to be connected to IC2.
 *                    TIM_ICSelection_TRC: TIM Input 1 is selected to be connected to TRC.
 * 					TIM_ICFilter: Specifies the Input Capture Filter.
 * 					 This parameter must be a value between 0x00 and 0x0F.
 * Return:          None.
 */
static void TI1_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
	uint32_t tmpccmr1 = 0, tmpccer = 0;

	/* Disable the Channel 1: Reset the CC1E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC1E;
	tmpccmr1 = TIMx->CCMR1;
	tmpccer = TIMx->CCER;

	/* Select the Input and set the filter */
	tmpccmr1 &= ((uint32_t)~TIM_CCMR1_CC1S) & ((uint32_t)~TIM_CCMR1_IC1F);
	tmpccmr1 |= (uint32_t)(TIM_ICSelection | (uint32_t)(TIM_ICFilter << (uint32_t)4));

	/* Select the Polarity and set the CC1E Bit */
	tmpccer &= (uint32_t)~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
	tmpccer |= (uint32_t)(TIM_ICPolarity | (uint32_t)TIM_CCER_CC1E);

	/* Write to TIMx CCMR1 and CCER registers */
	TIMx->CCMR1 = tmpccmr1;
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TI2_Config
 * Description:     Configure the TI2 as Input.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				 TIM_ICPolarity : The Input Polarity.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPolarity_Rising
 * 					  TIM_ICPolarity_Falling
 *                    TIM_ICPolarity_BothEdge
 *					TIM_ICSelection: specifies the input to be used.
 *                    This parameter can be one of the following values:
 * 					  TIM_ICSelection_DirectTI: TIM Input 2 is selected to be connected to IC2.
 *                    TIM_ICSelection_IndirectTI: TIM Input 2 is selected to be connected to IC1.
 *                    TIM_ICSelection_TRC: TIM Input 2 is selected to be connected to TRC.
 * 					TIM_ICFilter: Specifies the Input Capture Filter.
 * 					 This parameter must be a value between 0x00 and 0x0F.
 * Return:          None.
 */
static void TI2_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
	uint32_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;

	/* Disable the Channel 2: Reset the CC2E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC2E;
	tmpccmr1 = TIMx->CCMR1;
	tmpccer = TIMx->CCER;
	tmp = (uint32_t)(TIM_ICPolarity << 4);

	/* Select the Input and set the filter */
	tmpccmr1 &= ((uint32_t)~TIM_CCMR1_CC2S) & ((uint32_t)~TIM_CCMR1_IC2F);
	tmpccmr1 |= (uint32_t)(TIM_ICFilter << 12);
	tmpccmr1 |= (uint32_t)(TIM_ICSelection << 8);

	/* Select the Polarity and set the CC2E Bit */
	tmpccer &= (uint32_t)~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
	tmpccer |=  (uint32_t)(tmp | (uint32_t)TIM_CCER_CC2E);

	/* Write to TIMx CCMR1 and CCER registers */
	TIMx->CCMR1 = tmpccmr1 ;
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TI3_Config
 * Description:     Configure the TI3 as Input.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				TIM_ICPolarity : The Input Polarity.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPolarity_Rising
 * 					  TIM_ICPolarity_Falling
 *                    TIM_ICPolarity_BothEdge
 *					TIM_ICSelection: specifies the input to be used.
 *                    This parameter can be one of the following values:
 * 					  TIM_ICSelection_DirectTI: TIM Input 3 is selected to be connected to IC3.
 *                    TIM_ICSelection_IndirectTI: TIM Input 3 is selected to be connected to IC4.
 *                    TIM_ICSelection_TRC: TIM Input 3 is selected to be connected to TRC.
 * 					TIM_ICFilter: Specifies the Input Capture Filter.
 * 					 This parameter must be a value between 0x00 and 0x0F.
 * Return:          None.
 */
static void TI3_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
	uint32_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

	/* Disable the Channel 3: Reset the CC3E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC3E;
	tmpccmr2 = TIMx->CCMR2;
	tmpccer = TIMx->CCER;
	tmp = (uint32_t)(TIM_ICPolarity << 8);

	/* Select the Input and set the filter */
	tmpccmr2 &= ((uint32_t)~TIM_CCMR2_CC3S) & ((uint32_t)~TIM_CCMR2_IC3F);
	tmpccmr2 |= (uint32_t)(TIM_ICSelection | (uint32_t)(TIM_ICFilter << (uint32_t)4));

	/* Select the Polarity and set the CC3E Bit */
	tmpccer &= (uint32_t)~(TIM_CCER_CC3P | TIM_CCER_CC3NP);
	tmpccer |= (uint32_t)(tmp | (uint32_t)TIM_CCER_CC3E);

	/* Write to TIMx CCMR2 and CCER registers */
	TIMx->CCMR2 = tmpccmr2;
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TI4_Config
 * Description:     Configure the TI4 as Input.
 * Param:           TIMx: where x can be 0 to 7 to select the TIM peripheral.
 *  				TIM_ICPolarity : The Input Polarity.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPolarity_Rising
 * 					  TIM_ICPolarity_Falling
 *                    TIM_ICPolarity_BothEdge
 *					TIM_ICSelection: specifies the input to be used.
 *                    This parameter can be one of the following values:
 * 					  TIM_ICSelection_DirectTI: TIM Input 4 is selected to be connected to IC4.
 *                    TIM_ICSelection_IndirectTI: TIM Input 4 is selected to be connected to IC3.
 *                    TIM_ICSelection_TRC: TIM Input 4 is selected to be connected to TRC.
 * 					TIM_ICFilter: Specifies the Input Capture Filter.
 * 					 This parameter must be a value between 0x00 and 0x0F.
 * Return:          None.
 */
static void TI4_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
	uint32_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

	/* Disable the Channel 4: Reset the CC4E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC4E;
	tmpccmr2 = TIMx->CCMR2;
	tmpccer = TIMx->CCER;
	tmp = (uint32_t)(TIM_ICPolarity << 12);

	/* Select the Input and set the filter */
	tmpccmr2 &= ((uint32_t)~TIM_CCMR2_CC4S) & ((uint32_t)~TIM_CCMR2_IC4F);
	tmpccmr2 |= (uint32_t)(TIM_ICSelection << 8);
	tmpccmr2 |= (uint32_t)(TIM_ICFilter << 12);

	/* Select the Polarity and set the CC4E Bit */
	tmpccer &= (uint32_t)~(TIM_CCER_CC4P | TIM_CCER_CC4NP);
	tmpccer |= (uint32_t)(tmp | (uint32_t)TIM_CCER_CC4E);

	/* Write to TIMx CCMR2 and CCER registers */
	TIMx->CCMR2 = tmpccmr2;
	TIMx->CCER = tmpccer ;
}

/*
 * Function:        TI5_Config
 * Description:     Configure the TI5 as Input.
 * Param:           TIMx: where x can be 0 ,1 ,2 or 5 to select the TIM peripheral.
 *  				TIM_ICPolarity : The Input Polarity.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPolarity_Rising
 * 					  TIM_ICPolarity_Falling
 *                    TIM_ICPolarity_BothEdge
 *					TIM_ICSelection: specifies the input to be used.
 *                    This parameter can be one of the following values:
 * 					  TIM_ICSelection_DirectTI: TIM Input 5 is selected to be connected to IC5.
 *                    TIM_ICSelection_IndirectTI: TIM Input 5 is selected to be connected to IC6.
 *                    TIM_ICSelection_TRC: TIM Input 5 is selected to be connected to TRC.
 * 					TIM_ICFilter: Specifies the Input Capture Filter.
 * 					 This parameter must be a value between 0x00 and 0x0F.
 * Return:          None.
 */
static void TI5_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
	uint32_t tmpccmr3 = 0, tmpccer = 0, tmp = 0;

	/* Disable the Channel 5: Reset the CC5E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC5E;
	tmpccmr3 = TIMx->CCMR3;
	tmpccer = TIMx->CCER;
	tmp = (uint32_t)(TIM_ICPolarity << 16);

	/* Select the Input and set the filter */
	tmpccmr3 &= ((uint32_t)~TIM_CCMR3_CC5S) & ((uint32_t)~TIM_CCMR3_IC5F);
	tmpccmr3 |= (uint32_t)(TIM_ICSelection | (uint32_t)(TIM_ICFilter << (uint32_t)4));

	/* Select the Polarity and set the CC5E Bit */
	tmpccer &= (uint32_t)~(TIM_CCER_CC5P | TIM_CCER_CC5NP);
	tmpccer |= (uint32_t)(tmp | (uint32_t)TIM_CCER_CC5E);

	/* Write to TIMx CCMR3 and CCER registers */
	TIMx->CCMR3 = tmpccmr3;
	TIMx->CCER = tmpccer;
}

/*
 * Function:        TI6_Config
 * Description:     Configure the TI6 as Input.
 * Param:           TIMx: where x can be 0 ,1 ,2 or 5 to select the TIM peripheral.
 *  				TIM_ICPolarity : The Input Polarity.
 *      		   	 This parameter can be one of the following values:
 * 					  TIM_ICPolarity_Rising
 * 					  TIM_ICPolarity_Falling
 *                    TIM_ICPolarity_BothEdge
 *					TIM_ICSelection: specifies the input to be used.
 *                    This parameter can be one of the following values:
 * 					  TIM_ICSelection_DirectTI: TIM Input 6 is selected to be connected to IC6.
 *                    TIM_ICSelection_IndirectTI: TIM Input 6 is selected to be connected to IC5.
 *                    TIM_ICSelection_TRC: TIM Input 6 is selected to be connected to TRC.
 * 					TIM_ICFilter: Specifies the Input Capture Filter.
 * 					 This parameter must be a value between 0x00 and 0x0F.
 * Return:          None.
 */
static void TI6_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
	uint32_t tmpccmr3 = 0, tmpccer = 0, tmp = 0;

	/* Disable the Channel 6: Reset the CC6E Bit */
	TIMx->CCER &= (uint32_t)~TIM_CCER_CC6E;
	tmpccmr3 = TIMx->CCMR3;
	tmpccer = TIMx->CCER;
	tmp = (uint32_t)(TIM_ICPolarity << 20);

	/* Select the Input and set the filter */
	tmpccmr3 &= ((uint32_t)~TIM_CCMR3_CC6S) & ((uint32_t)~TIM_CCMR3_IC6F);
	tmpccmr3 |= (uint32_t)(TIM_ICSelection << 8);
	tmpccmr3 |= (uint32_t)(TIM_ICFilter << 12);

	/* Select the Polarity and set the CC6E Bit */
	tmpccer &= (uint32_t)~(TIM_CCER_CC6P | TIM_CCER_CC6NP);
	tmpccer |= (uint32_t)(tmp | (uint32_t)TIM_CCER_CC6E);

	/* Write to TIMx CCMR3 and CCER registers */
	TIMx->CCMR3 = tmpccmr3;
	TIMx->CCER = tmpccer;
}
/*****END OF FILE*****/
