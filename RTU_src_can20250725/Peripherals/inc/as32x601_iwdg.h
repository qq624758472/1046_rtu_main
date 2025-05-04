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
 * Date:			      2024/07/31
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/07/31     1.0     build this module
 * Description:     This file contains all the functions prototypes for the iwdg configuration.
 */

#ifndef AS32X601_IWDG_H
#define AS32X601_IWDG_H

#include "as32x601_iwdg_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @defgroup  Use by parameter examine
 */

#define IS_IWDG_PRESCALER(PRESCALER)  ((PRESCALER>=0x02)&&(PRESCALER<=0xff))

#define IS_IWDG_DIVIDER(DIVIDER)  ((DIVIDER>=0x0002)&&(DIVIDER<=0xffff))

#define IS_IWDG_TOValue(BVAL)  ((BVAL>=0x00)&&(BVAL<=0xffff))

/*
 * @defgroup  WWDG Enable definition
 */
#define I_PSC_EN                          ((uint32_t)0x10000000)
#define I_CFG_EN                          ((uint32_t)0x20000000)
#define IS_IWDG_CONFIG_EN(EN) (((EN)== I_PSC_EN)||((EN)== I_CFG_EN))	

/*
 * @defgroup  IWDG Lock definition
 */
#define I_PSC_LOCK                        ((uint32_t)0x80000000)
#define I_CFG_LOCK                        ((uint32_t)0xa0000000)
#define IS_IWDG_CONFIG_LOCK(LOCK) (((LOCK)== I_PSC_LOCK)||((LOCK)== I_PSC_LOCK))	

/*
 * @brief Function declaration
 */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetDivider(uint8_t IWDG_Divider);
void IWDG_SetTimeout(uint16_t BVAL);
uint16_t IWDG_GetCounter(void);
void IWDG_ResetCounter(void);
void IWDG_ENCmd(uint32_t IWDG_EN,FunctionalState NewState);
void IWDG_LockCmd(uint32_t IWDG_LOCK,FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/