/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_dac_reg.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:			2024/9/2
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/9/2       1.0     build this module
 * Description:     This file contains all the register correlation defines for the DAC firmware library.
 */

#ifndef AS32X601_DAC_REGS_H
#define AS32X601_DAC_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601.h"
#include "as32x601_addrmap.h"

/*
 * @brief General Purpose I/O registers structure
 */
typedef struct
{
	__IO uint8_t CTRL;					/* DAC Control Register,							Address offset: 0x00 */
	uint8_t RESERVED0[3];				/* DAC Reserved,									Address offset: 0x01 - 0x03 */
	__IO uint8_t DOUT;					/* DAC Data Register,								Address offset: 0x04 */
	uint8_t RESERVED1[3];				/* DAC Reserved,									Address offset: 0x05 - 0x07 */
	__IO uint8_t CLK_DIV;				/* DAC Clock Division Register,						Address offset: 0x08 */
	uint8_t RESERVED2[3];				/* DAC Reserved,									Address offset: 0x09 - 0x0B */
	__IO uint8_t CMP_CTRL;				/* DAC Comparator Control Register,					Address offset: 0x0C */
	uint8_t RESERVED3[3];				/* DAC Reserved,									Address offset: 0x0D - 0x0F */
} DAC_TypeDef;

/*
 * @addtogroup DAC Peripheral declaration
 */
#define DAC0			((DAC_TypeDef*)DAC_CMP0_BASE)
#define DAC1			((DAC_TypeDef*)DAC_CMP1_BASE)

/******************  Bit definition for DAC_CTRL register  *******************/
#define DAC_CTRL_DAC_EN_DPos      	(0U)
#define DAC_CTRL_EN_Pos       	  	DAC_CTRL_DAC_EN_DPos
#define DAC_CTRL_EN_Msk       		(0x1UL << DAC_CTRL_EN_Pos)                	/* 0x00000001 */
#define DAC_CTRL_EN          		DAC_CTRL_EN_Msk                        		/* DAC enable */

#define DAC_CTRL_DAC_MD_DPos      	(1UL)
#define DAC_CTRL_MD_Pos       	  	DAC_CTRL_DAC_MD_DPos
#define DAC_CTRL_MD_Msk       		(0x1UL << DAC_CTRL_MD_Pos)					/* 0x00000002 */
#define DAC_CTRL_MD          		DAC_CTRL_MD_Msk								/* DAC mode */

#define DAC_CTRL_VREF_MD_DPos      	(2UL)
#define DAC_CTRL_VREF_MD_Pos      	DAC_CTRL_VREF_MD_DPos
#define DAC_CTRL_VREF_MD_Msk       (0x1UL << DAC_CTRL_VREF_MD_Pos)				/* 0x00000004 */
#define DAC_CTRL_VREF_MD           DAC_CTRL_VREF_MD_Msk							/* DAC VREF mode */

#define DAC_CTRL_RESETN_DPos      	(3UL)
#define DAC_CTRL_RESETN_Pos      	DAC_CTRL_RESETN_DPos
#define DAC_CTRL_RESETN_Msk       	(0x1UL << DAC_CTRL_RESETN_Pos)				/* 0x00000008 */
#define DAC_CTRL_RESETN           	DAC_CTRL_RESETN_Msk							/* DAC reset */

/******************  Bit definition for DAC_DOUT register  *******************/
#define DAC_DOUT_DOUT_DPos    		(0U)
#define DAC_DOUT_DOUT_Pos       	DAC_DOUT_DOUT_DPos
#define DAC_DOUT_DOUT_Msk       	(0xFFUL << DAC_DOUT_DOUT_Pos)				/* 0x000000FF */
#define DAC_DOUT_DOUT           	DAC_DOUT_DOUT_Msk
#define DAC_DOUT_DOUT_0				(0x1UL << DAC_DOUT_DOUT_Pos)				/* 0x00000001 */
#define DAC_DOUT_DOUT_1				(0x2UL << DAC_DOUT_DOUT_Pos)				/* 0x00000002 */
#define DAC_DOUT_DOUT_2				(0x4UL << DAC_DOUT_DOUT_Pos)				/* 0x00000004 */
#define DAC_DOUT_DOUT_3				(0x8UL << DAC_DOUT_DOUT_Pos)				/* 0x00000008 */
#define DAC_DOUT_DOUT_4				(0x10UL << DAC_DOUT_DOUT_Pos)				/* 0x00000010 */
#define DAC_DOUT_DOUT_5				(0x20UL << DAC_DOUT_DOUT_Pos)				/* 0x00000020 */
#define DAC_DOUT_DOUT_6				(0x40UL << DAC_DOUT_DOUT_Pos)				/* 0x00000040 */
#define DAC_DOUT_DOUT_7				(0x80UL << DAC_DOUT_DOUT_Pos)				/* 0x00000080 */

/******************  Bit definition for DAC_CLK_DIV register  *******************/
#define DAC_CLK_DIV_CLK_DIV_NU_DPos (0U)
#define DAC_CLK_DIV_NU_Pos     		DAC_CLK_DIV_CLK_DIV_NU_DPos
#define DAC_CLK_DIV_NU_Msk 			(0xFFUL << DAC_CLK_DIV_NU_Pos)
#define DAC_CLK_DIV_NU          	DAC_CLK_DIV_NU_Msk
#define DAC_CLK_DIV_NU_0			(0x1UL << DAC_CLK_DIV_NU_Pos)				/* 0x00000001 */
#define DAC_CLK_DIV_NU_1			(0x2UL << DAC_CLK_DIV_NU_Pos)				/* 0x00000002 */
#define DAC_CLK_DIV_NU_2			(0x4UL << DAC_CLK_DIV_NU_Pos)				/* 0x00000004 */
#define DAC_CLK_DIV_NU_3			(0x8UL << DAC_CLK_DIV_NU_Pos)				/* 0x00000008 */
#define DAC_CLK_DIV_NU_4			(0x10UL << DAC_CLK_DIV_NU_Pos)				/* 0x00000010 */
#define DAC_CLK_DIV_NU_5			(0x20UL << DAC_CLK_DIV_NU_Pos)				/* 0x00000020 */
#define DAC_CLK_DIV_NU_6			(0x40UL << DAC_CLK_DIV_NU_Pos)				/* 0x00000040 */
#define DAC_CLK_DIV_NU_7			(0x80UL << DAC_CLK_DIV_NU_Pos)				/* 0x00000080 */

/******************  Bit definition for DAC_CMP_CTRL register  *******************/
#define DAC_CMP_CTRL_CMP_EN_DPos    (0U)
#define DAC_CMP_CTRL_EN_Pos     	DAC_CMP_CTRL_CMP_EN_DPos
#define DAC_CMP_CTRL_EN_Msk       	(0x1UL << DAC_CMP_CTRL_EN_Pos)				/* 0x00000001 */
#define DAC_CMP_CTRL_EN          	DAC_CMP_CTRL_EN_Msk							/* DAC comparator enable */

#define DAC_CMP_CTRL_CMP_MD_DPos    (1UL)
#define DAC_CMP_CTRL_MD_Pos     	DAC_CMP_CTRL_CMP_MD_DPos
#define DAC_CMP_CTRL_MD_Msk       	(0x1UL << DAC_CMP_CTRL_MD_Pos)				/* 0x00000002 */
#define DAC_CMP_CTRL_MD          	DAC_CMP_CTRL_MD_Msk							/* DAC comparator mode */

#define DAC_CMP_CTRL_CMP_HYS_DPos   (2UL)
#define DAC_CMP_CTRL_HYS_Pos     	DAC_CMP_CTRL_CMP_HYS_DPos
#define DAC_CMP_CTRL_HYS_Msk       	(0x7UL << DAC_CMP_CTRL_HYS_Pos)				/* 0x0000001C */
#define DAC_CMP_CTRL_HYS          	DAC_CMP_CTRL_HYS_Msk						/* DAC comparator hysteresis */
#define DAC_CMP_CTRL_HYS_0			(0x1UL << DAC_CMP_CTRL_HYS_Pos)				/* 0x00000004 */
#define DAC_CMP_CTRL_HYS_1			(0x2UL << DAC_CMP_CTRL_HYS_Pos)				/* 0x00000008 */
#define DAC_CMP_CTRL_HYS_2			(0x4UL << DAC_CMP_CTRL_HYS_Pos)				/* 0x00000010 */

#define DAC_CMP_CTRL_CMPO_DPos      (5UL)
#define DAC_CMP_CTRL_CMPO_Pos      	DAC_CMP_CTRL_CMPO_DPos
#define DAC_CMP_CTRL_CMPO_Msk       (0x1UL << DAC_CMP_CTRL_CMPO_Pos)
#define DAC_CMP_CTRL_CMPO           DAC_CMP_CTRL_CMPO_Msk
  
#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
