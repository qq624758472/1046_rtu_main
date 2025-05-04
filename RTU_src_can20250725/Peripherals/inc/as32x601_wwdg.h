/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	  as32x601_iwag.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			      2024/08/01
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/01     1.0     build this module
 * Description:     This file contains all the functions prototypes for the wwdg configuration.
 */

#ifndef AS32X601_WWDG_H
#define AS32X601_WWDG_H

#include "as32x601_wwdg_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @defgroup  Use by parameter examine
 */

#define IS_WWDG_ALL_PERIPH(PERIPH) (((PERIPH) == WWDG0_Channel0)  || \
                                    ((PERIPH) == WWDG0_Channel1)  || \
                                    ((PERIPH) == WWDG0_Channel2)  || \
                                    ((PERIPH) == WWDG0_Channel3)  || \
                                    ((PERIPH) == WWDG1_Channel0)  || \
                                    ((PERIPH) == WWDG1_Channel1)  || \
                                    ((PERIPH) == WWDG1_Channel2)  || \
                                    ((PERIPH) == WWDG1_Channel3) 


#define IS_WWDG_TypeDef(WWDG)  (((WWDG)==WWDG0) || ((WWDG)==WWDG1))

#define IS_WWDG_PRESCALER(PRESCALER)  ((PRESCALER>=0x02)&&(PRESCALER<=0xff))

#define IS_WWDG_DIVIDER(DIVIDER)  ((DIVIDER>=0x0002)&&(DIVIDER<=0xffff))

#define IS_WWDG_TOValue(BVAL)  ((BVAL>=0x00)&&(BVAL<=0xffff))

#define IS_WWDG_WDCNTValue(COUNT)  ((COUNT>=0x00)&&(COUNT<=0xffff))

/*
 * @defgroup  WWDG Bark flag definition
 */
#define WWDG_FLAG_BK0                          ((uint32_t)0x00000001)
#define WWDG_FLAG_BK1                          ((uint32_t)0x00000002)
#define WWDG_FLAG_BK2                          ((uint32_t)0x00000004)
#define WWDG_FLAG_BK3                          ((uint32_t)0x00000008)
#define IS_WWDG_BRAK_FLAG(FLAG) (((FLAG)== WWDG_FLAG_BK0)||((FLAG)== WWDG_FLAG_BK1)||((FLAG)== WWDG_FLAG_BK2)||((FLAG)== WWDG_FLAG_BK3))

/*
 * @defgroup  WWDG Enable definition
 */
#define W_PSC_EN                          ((uint32_t)0x10000000)
#define W_CFG_EN                          ((uint32_t)0x20000000)
#define W_WD_EN                           ((uint32_t)0x40000000)
#define IS_WWDG_CONFIG_EN(EN) (((EN)== W_PSC_EN)||((EN)== W_CFG_EN)||((EN)== W_WD_EN))	

/*
 * @defgroup  WWDG Enable definition
 */
#define W_PSC_LOCK                        ((uint32_t)0x80000000)
#define W_CFG_LOCK                        ((uint32_t)0xa0000000)
#define IS_WWDG_CONFIG_LOCK(LOCK) (((LOCK)== W_PSC_LOCK)||((LOCK)== W_CFG_LOCK))	

/*
 * @brief Function declaration
 */
void WWDG_SetPrescaler(WWDG_TypeDef* WWDGy,uint8_t WWDG_Prescaler);
FlagStatus WWDG_GetBKStatus(WWDG_TypeDef* WWDGy,uint32_t BK_Flag);
void WWDG_SetDivider(WWDG_Channel_TypeDef* WWDGy_Channelx ,uint8_t WWDG_Divider);
void WWDG_SetTimeout(WWDG_Channel_TypeDef* WWDGy_Channelx,uint16_t BVAL);
uint16_t WWDG_GetCounter(WWDG_Channel_TypeDef* WWDGy_Channelx);
void WWDG_ResetCounter(WWDG_Channel_TypeDef* WWDGy_Channelx);
void WWDG_ENCmd(WWDG_Channel_TypeDef* WWDGy_Channelx,uint32_t WWDG_EN,FunctionalState NewState);
void WWDG_LockCmd(WWDG_Channel_TypeDef* WWDGy_Channelx,uint32_t WWDG_LOCK,FunctionalState NewState);
void WWDG_SetWDCNT(WWDG_Channel_TypeDef* WWDGy_Channelx,uint16_t WindowCount);




#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/