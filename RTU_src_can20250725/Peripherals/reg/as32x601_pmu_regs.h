/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_pmu_reg.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:			2024/08/26
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/26     1.0     build this module
 * Description:     This file contains all the register correlation defines for the PMU firmware library.
 */

#ifndef AS32X601_PMU_REGS_H
#define AS32X601_PMU_REGS_H

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
	__IO uint32_t LDOCR;        /* PMU_PW       PMU LDO configuration register,                 Address offset: 0x00 */
	__I  uint32_t LDOSR;        /* PMU_PS       PMU LDO status register,                        Address offset: 0x04 */
	__IO uint32_t VDCR;         /* PMU_VD       PMU voltage detection configuration register,   Address offset: 0x08 */
	__IO uint32_t OCR;          /* PMU_CA       PMU oscillator configuration register,          Address offset: 0x0C */
	__IO uint32_t PMCR;         /* PMU_MODE     PMU power mode configuration register,          Address offset: 0x10 */
	__IO uint32_t WKFR;         /* PMU_WKP      PMU wake up flag register,                      Address offset: 0x14 */
	__IO uint32_t WKEN;         /* PMU_WKEN     PMU wake up channel enable register,            Address offset: 0x18 */
} PMU_TypeDef;

/*
 * @addtogroup PMU Peripheral declaration
 */
#define PMU	((PMU_TypeDef*)PMU_BASE)

/******************  Bit definition for PMU_LDOCR register  *******************/
#define PMU_LDOCR_EN_3V3_DPos           (0U)
#define PMU_LDOCR_3V3LDOEN_Pos          PMU_LDOCR_EN_3V3_DPos
#define PMU_LDOCR_3V3LDOEN_Msk          (0x1UL << PMU_LDOCR_3V3LDOEN_Pos)       /* 0x00000001 */
#define PMU_LDOCR_3V3LDOEN              PMU_LDOCR_3V3LDOEN_Msk                  /* 3.3V LDO Enable */

#define PMU_LDOCR_BP_3V3_DPos           (1U)
#define PMU_LDOCR_3V3LDOBYP_Pos     	PMU_LDOCR_BP_3V3_DPos
#define PMU_LDOCR_3V3LDOBYP_Msk         (0x1UL << PMU_LDOCR_3V3LDOBYP_Pos)      /* 0x00000002 */
#define PMU_LDOCR_3V3LDOBYP             PMU_LDOCR_3V3LDOBYP_Msk                 /* 3.3V LDO Bypass */

#define PMU_LDOCR_ADJ_3V3_DPos          (2U)
#define PMU_LDOCR_3V3LDOVOS_Pos         PMU_LDOCR_ADJ_3V3_DPos
#define PMU_LDOCR_3V3LDOVOS_Msk         (0xFUL << PMU_LDOCR_3V3LDOVOS_Pos)      /* 0x0000003C */
#define PMU_LDOCR_3V3LDOVOS             PMU_LDOCR_3V3LDOVOS_Msk                 /* 3V3LDOVOS [3:0] (3.3V LDO Voltage Scaling) */
#define PMU_LDOCR_3V3LDOVOS_0           (0x01UL << PMU_LDOCR_3V3LDOVOS_Pos)     /* 0x00000004 */
#define PMU_LDOCR_3V3LDOVOS_1           (0x02UL << PMU_LDOCR_3V3LDOVOS_Pos)     /* 0x00000008 */
#define PMU_LDOCR_3V3LDOVOS_2           (0x04UL << PMU_LDOCR_3V3LDOVOS_Pos)     /* 0x00000010 */
#define PMU_LDOCR_3V3LDOVOS_3           (0x08UL << PMU_LDOCR_3V3LDOVOS_Pos)     /* 0x00000020 */

#define PMU_LDOCR_EN_2V5_DPos           (6U)
#define PMU_LDOCR_2V5LDOEN_Pos          PMU_LDOCR_EN_2V5_DPos
#define PMU_LDOCR_2V5LDOEN_Msk          (0x1UL << PMU_LDOCR_2V5LDOEN_Pos)       /* 0x00000040 */
#define PMU_LDOCR_2V5LDOEN              PMU_LDOCR_2V5LDOEN_Msk                  /* 2.5V LDO Enable */

#define PMU_LDOCR_ADJ_2V5_DPos          (7U)
#define PMU_LDOCR_2V5LDOVOS_Pos         PMU_LDOCR_ADJ_2V5_DPos
#define PMU_LDOCR_2V5LDOVOS_Msk         (0xFUL << PMU_LDOCR_2V5LDOVOS_Pos)      /* 0x00000780 */
#define PMU_LDOCR_2V5LDOVOS             PMU_LDOCR_2V5LDOVOS_Msk                 /* 2V5LDOVOS [3:0] (2.5V LDO Voltage Scaling) */
#define PMU_LDOCR_2V5LDOVOS_0           (0x01UL << PMU_LDOCR_2V5LDOVOS_Pos)     /* 0x00000080 */
#define PMU_LDOCR_2V5LDOVOS_1           (0x02UL << PMU_LDOCR_2V5LDOVOS_Pos)     /* 0x00000100 */
#define PMU_LDOCR_2V5LDOVOS_2           (0x04UL << PMU_LDOCR_2V5LDOVOS_Pos)     /* 0x00000200 */
#define PMU_LDOCR_2V5LDOVOS_3           (0x08UL << PMU_LDOCR_2V5LDOVOS_Pos)     /* 0x00000400 */

#define PMU_LDOCR_EN_1V2A_DPos          (11U)
#define PMU_LDOCR_1V2LDOEN_Pos          PMU_LDOCR_EN_1V2A_DPos
#define PMU_LDOCR_1V2LDOEN_Msk          (0x1UL << PMU_LDOCR_1V2LDOEN_Pos)       /* 0x00000800 */
#define PMU_LDOCR_1V2LDOEN              PMU_LDOCR_1V2LDOEN_Msk                  /* 1.2V LDO Enable */

#define PMU_LDOCR_EN_VREF_DPos          (12U)
#define PMU_LDOCR_1V2VREFEN_Pos         PMU_LDOCR_EN_VREF_DPos
#define PMU_LDOCR_1V2VREFEN_Msk         (0x1UL << PMU_LDOCR_1V2VREFEN_Pos)      /* 0x00001000 */
#define PMU_LDOCR_1V2VREFEN             PMU_LDOCR_1V2VREFEN_Msk                 /* 1.2V Flash Reference Voltage Source Enable */

#define PMU_LDOCR_ADJ_VREF_DPos         (13U)
#define PMU_LDOCR_1V2VREFS_Pos          PMU_LDOCR_ADJ_VREF_DPos
#define PMU_LDOCR_1V2VREFS_Msk          (0xFUL << PMU_LDOCR_1V2VREFS_Pos)       /* 0x0001E000 */
#define PMU_LDOCR_1V2VREFS              PMU_LDOCR_1V2VREFS_Msk                  /* 1V2VREFS [3:0] (1.2V Reference Voltage Source Scaling) */
#define PMU_LDOCR_1V2VREFS_0            (0x01UL << PMU_LDOCR_1V2VREFS_Pos)      /* 0x00002000 */
#define PMU_LDOCR_1V2VREFS_1            (0x02UL << PMU_LDOCR_1V2VREFS_Pos)      /* 0x00004000 */
#define PMU_LDOCR_1V2VREFS_2            (0x04UL << PMU_LDOCR_1V2VREFS_Pos)      /* 0x00008000 */
#define PMU_LDOCR_1V2VREFS_3            (0x08UL << PMU_LDOCR_1V2VREFS_Pos)      /* 0x00010000 */

#define PMU_LDOCR_ADJ_1V2A_DPos         (17U)
#define PMU_LDOCR_1V2LDOVOS_Pos         PMU_LDOCR_ADJ_1V2A_DPos
#define PMU_LDOCR_1V2LDOVOS_Msk         (0xFUL << PMU_LDOCR_1V2LDOVOS_Pos)      /* 0x001E0000 */
#define PMU_LDOCR_1V2LDOVOS             PMU_LDOCR_1V2LDOVOS_Msk                 /* 1V2LDOVOS [3:0] (1.2V LDO Voltage Scaling) */
#define PMU_LDOCR_1V2LDOVOS_0           (0x01UL << PMU_LDOCR_1V2LDOVOS_Pos)     /* 0x00020000 */
#define PMU_LDOCR_1V2LDOVOS_1           (0x02UL << PMU_LDOCR_1V2LDOVOS_Pos)     /* 0x00040000 */
#define PMU_LDOCR_1V2LDOVOS_2           (0x04UL << PMU_LDOCR_1V2LDOVOS_Pos)     /* 0x00080000 */
#define PMU_LDOCR_1V2LDOVOS_3           (0x08UL << PMU_LDOCR_1V2LDOVOS_Pos)     /* 0x00100000 */

#define PMU_LDOCR_ADJ_1V2B_DPos         (21U)
#define PMU_LDOCR_1V2BLDOVOS_Pos        PMU_LDOCR_ADJ_1V2B_DPos
#define PMU_LDOCR_1V2BLDOVOS_Msk        (0xFUL << PMU_LDOCR_1V2BLDOVOS_Pos)     /* 0x01E00000 */
#define PMU_LDOCR_1V2BLDOVOS            PMU_LDOCR_1V2BLDOVOS_Msk                /* 1V2BLDOVOS [3:0] (1.2V Backup LDO Voltage Scaling) */
#define PMU_LDOCR_1V2BLDOVOS_0          (0x01UL << PMU_LDOCR_1V2BLDOVOS_Pos)    /* 0x00200000 */
#define PMU_LDOCR_1V2BLDOVOS_1          (0x02UL << PMU_LDOCR_1V2BLDOVOS_Pos)    /* 0x00400000 */
#define PMU_LDOCR_1V2BLDOVOS_2          (0x04UL << PMU_LDOCR_1V2BLDOVOS_Pos)    /* 0x00800000 */
#define PMU_LDOCR_1V2BLDOVOS_3          (0x08UL << PMU_LDOCR_1V2BLDOVOS_Pos)    /* 0x01000000 */


/******************  Bit definition for PMU_LDOSR register  *******************/
#define PMU_LDOSR_RDY_3V3_DPos          (0U)
#define PMU_LDOSR_3V3LDORDY_Pos         PMU_LDOSR_RDY_3V3_DPos
#define PMU_LDOSR_3V3LDORDY_Msk         (0x1UL << PMU_LDOSR_3V3LDORDY_Pos)      /* 0x00000001 */
#define PMU_LDOSR_3V3LDORDY             PMU_LDOSR_3V3LDORDY_Msk                 /* 3.3V LDO Voltage Ready Flag */

#define PMU_LDOSR_RDY_2V5_DPos          (1U)
#define PMU_LDOSR_2V5LDORDY_Pos         PMU_LDOSR_RDY_2V5_DPos
#define PMU_LDOSR_2V5LDORDY_Msk         (0x1UL << PMU_LDOSR_2V5LDORDY_Pos)      /* 0x00000002 */
#define PMU_LDOSR_2V5LDORDY             PMU_LDOSR_2V5LDORDY_Msk                 /* 2.5V LDO Voltage Ready Flag */

#define PMU_LDOSR_RDY_1V2A_DPos         (2U)
#define PMU_LDOSR_1V2LDORDY_Pos         PMU_LDOSR_RDY_1V2A_DPos
#define PMU_LDOSR_1V2LDORDY_Msk         (0x1UL << PMU_LDOSR_1V2LDORDY_Pos)      /* 0x00000004 */
#define PMU_LDOSR_1V2LDORDY             PMU_LDOSR_1V2LDORDY_Msk                 /* 1.2V LDO Voltage Ready Flag */

#define PMU_LDOSR_RDY_1V2B_DPos         (3U)
#define PMU_LDOSR_1V2BLDORDY_Pos        PMU_LDOSR_RDY_1V2B_DPos
#define PMU_LDOSR_1V2BLDORDY_Msk        (0x1UL << PMU_LDOSR_1V2BLDORDY_Pos)     /* 0x00000008 */
#define PMU_LDOSR_1V2BLDORDY            PMU_LDOSR_1V2BLDORDY_Msk                /* 1.2V Backup LDO Voltage Ready Flag */


/******************  Bit definition for PMU_VDCR register  *******************/
#define PMU_VDCR_EN_LVR_DPos            (0U)
#define PMU_VDCR_LVREN_Pos              PMU_VDCR_EN_LVR_DPos
#define PMU_VDCR_LVREN_Msk              (0x1UL << PMU_VDCR_LVREN_Pos)           /* 0x00000001 */
#define PMU_VDCR_LVREN                  PMU_VDCR_LVREN_Msk                      /* Low Voltage Reset Enable */

#define PMU_VDCR_EN_HVD_DPos            (1U)
#define PMU_VDCR_HVDEN_Pos              PMU_VDCR_EN_HVD_DPos
#define PMU_VDCR_HVDEN_Msk              (0x1UL << PMU_VDCR_HVDEN_Pos)           /* 0x00000002 */
#define PMU_VDCR_HVDEN                  PMU_VDCR_HVDEN_Msk                      /* High Voltage Detect Enable */

#define PMU_VDCR_ADJ_HVD_DPos           (2U)
#define PMU_VDCR_HVDTS_Pos              PMU_VDCR_ADJ_HVD_DPos
#define PMU_VDCR_HVDTS_Msk              (0x1FUL << PMU_VDCR_HVDTS_Pos)          /* 0x0000007C */
#define PMU_VDCR_HVDTS                  PMU_VDCR_HVDTS_Msk                      /* HVDTS [4:0] (High Voltage Detect Threshold Scaling) */
#define PMU_VDCR_HVDTS_0                (0x01UL << PMU_VDCR_HVDTS_Pos)          /* 0x00000004 */
#define PMU_VDCR_HVDTS_1                (0x02UL << PMU_VDCR_HVDTS_Pos)          /* 0x00000008 */
#define PMU_VDCR_HVDTS_2                (0x04UL << PMU_VDCR_HVDTS_Pos)          /* 0x00000010 */
#define PMU_VDCR_HVDTS_3                (0x08UL << PMU_VDCR_HVDTS_Pos)          /* 0x00000020 */
#define PMU_VDCR_HVDTS_4                (0x10UL << PMU_VDCR_HVDTS_Pos)          /* 0x00000040 */

#define PMU_VDCR_EN_LVD_DPos            (7U)
#define PMU_VDCR_LVDEN_Pos              PMU_VDCR_EN_LVD_DPos
#define PMU_VDCR_LVDEN_Msk              (0x1UL << PMU_VDCR_LVDEN_Pos)           /* 0x00000080 */
#define PMU_VDCR_LVDEN                  PMU_VDCR_LVDEN_Msk                      /* Low Voltage Detect Enable */

#define PMU_VDCR_ADJ_LVD_DPos           (8U)
#define PMU_VDCR_LVDTS_Pos              PMU_VDCR_ADJ_LVD_DPos
#define PMU_VDCR_LVDTS_Msk              (0x1FUL << PMU_VDCR_LVDTS_Pos)          /* 0x00001F00 */
#define PMU_VDCR_LVDTS                  PMU_VDCR_LVDTS_Msk                      /* LVDTS [4:0] (Low Voltage Detect Threshold Scaling) */
#define PMU_VDCR_LVDTS_0                (0x01UL << PMU_VDCR_LVDTS_Pos)          /* 0x00000100 */
#define PMU_VDCR_LVDTS_1                (0x02UL << PMU_VDCR_LVDTS_Pos)          /* 0x00000200 */
#define PMU_VDCR_LVDTS_2                (0x04UL << PMU_VDCR_LVDTS_Pos)          /* 0x00000400 */
#define PMU_VDCR_LVDTS_3                (0x08UL << PMU_VDCR_LVDTS_Pos)          /* 0x00000800 */
#define PMU_VDCR_LVDTS_4                (0x10UL << PMU_VDCR_LVDTS_Pos)          /* 0x00001000 */


/******************  Bit definition for PMU_OCR register  *******************/
#define PMU_OCR_EN_RC16_DPos            (0U)
#define PMU_OCR_IRC16MEN_Pos            PMU_OCR_EN_RC16_DPos
#define PMU_OCR_IRC16MEN_Msk            (0x1UL << PMU_OCR_IRC16MEN_Pos)         /* 0x00000001 */
#define PMU_OCR_IRC16MEN                PMU_OCR_IRC16MEN_Msk                    /* Internal RC 16MHz Clock Enable */

#define PMU_OCR_ADJ_32K_DPos            (1U)
#define PMU_OCR_RC32KFS_Pos             PMU_OCR_ADJ_32K_DPos
#define PMU_OCR_RC32KFS_Msk             (0x3FUL << PMU_OCR_RC32KFS_Pos)         /* 0x0000007E */
#define PMU_OCR_RC32KFS                 PMU_OCR_RC32KFS_Msk                     /* RC32KFS [5:0] (RC 32KHz Clock Frequency Scaling) */
#define PMU_OCR_RC32KFS_0               (0x01UL << PMU_OCR_RC32KFS_Pos)         /* 0x00000002 */
#define PMU_OCR_RC32KFS_1               (0x02UL << PMU_OCR_RC32KFS_Pos)         /* 0x00000004 */
#define PMU_OCR_RC32KFS_2               (0x04UL << PMU_OCR_RC32KFS_Pos)         /* 0x00000008 */
#define PMU_OCR_RC32KFS_3               (0x08UL << PMU_OCR_RC32KFS_Pos)         /* 0x00000010 */
#define PMU_OCR_RC32KFS_4               (0x10UL << PMU_OCR_RC32KFS_Pos)         /* 0x00000020 */
#define PMU_OCR_RC32KFS_5               (0x20UL << PMU_OCR_RC32KFS_Pos)         /* 0x00000040 */


/******************  Bit definition for PMU_PMCR register  *******************/
#define PMU_PMCR_MD_CFG_DPos            (0U)
#define PMU_PMCR_POWMC_Pos              PMU_PMCR_MD_CFG_DPos
#define PMU_PMCR_POWMC_Msk              (0x3UL << PMU_PMCR_POWMC_Pos)           /* 0x00000003 */
#define PMU_PMCR_POWMC                  PMU_PMCR_POWMC_Msk                      /* POWMC [1:0] (Power Mode Config) */
#define PMU_PMCR_POWMC_0                (0x01UL << PMU_PMCR_POWMC_Pos)          /* 0x00000001 */
#define PMU_PMCR_POWMC_1                (0x02UL << PMU_PMCR_POWMC_Pos)          /* 0x00000002 */


/******************  Bit definition for PMU_WKFR register  *******************/
#define PMU_WKFR_WKSIG_DPos             (0U)
#define PMU_WKFR_WKCC_Pos               PMU_WKFR_WKSIG_DPos
#define PMU_WKFR_WKCC_Msk               (0x3FFFUL << PMU_WKFR_WKCC_Pos)         /* 0x00003FFF */
#define PMU_WKFR_WKCC                   PMU_WKFR_WKCC_Msk                       /* WKCC [13:0] (Wake Up Channel Config) */
#define PMU_WKFR_WKCC_0                 (0x0001UL << PMU_WKFR_WKCC_Pos)         /* 0x00000001 */
#define PMU_WKFR_WKCC_1                 (0x0002UL << PMU_WKFR_WKCC_Pos)         /* 0x00000002 */
#define PMU_WKFR_WKCC_2                 (0x0004UL << PMU_WKFR_WKCC_Pos)         /* 0x00000004 */
#define PMU_WKFR_WKCC_3                 (0x0008UL << PMU_WKFR_WKCC_Pos)         /* 0x00000008 */
#define PMU_WKFR_WKCC_4                 (0x0010UL << PMU_WKFR_WKCC_Pos)         /* 0x00000010 */
#define PMU_WKFR_WKCC_5                 (0x0020UL << PMU_WKFR_WKCC_Pos)         /* 0x00000020 */
#define PMU_WKFR_WKCC_6                 (0x0040UL << PMU_WKFR_WKCC_Pos)         /* 0x00000040 */
#define PMU_WKFR_WKCC_7                 (0x0080UL << PMU_WKFR_WKCC_Pos)         /* 0x00000080 */
#define PMU_WKFR_WKCC_8                 (0x0100UL << PMU_WKFR_WKCC_Pos)         /* 0x00000100 */
#define PMU_WKFR_WKCC_9                 (0x0200UL << PMU_WKFR_WKCC_Pos)         /* 0x00000200 */
#define PMU_WKFR_WKCC_10                (0x0400UL << PMU_WKFR_WKCC_Pos)         /* 0x00000400 */
#define PMU_WKFR_WKCC_11                (0x0800UL << PMU_WKFR_WKCC_Pos)         /* 0x00000800 */
#define PMU_WKFR_WKCC_12                (0x1000UL << PMU_WKFR_WKCC_Pos)         /* 0x00001000 */
#define PMU_WKFR_WKCC_13                (0x2000UL << PMU_WKFR_WKCC_Pos)         /* 0x00002000 */

#define PMU_WKFR_FOCUS_DPos             (14U)
#define PMU_WKFR_FOCURF_Pos             PMU_WKFR_FOCUS_DPos
#define PMU_WKFR_FOCURF_Msk             (0x1UL << PMU_WKFR_FOCURF_Pos)          /* 0x00004000 */
#define PMU_WKFR_FOCURF                 PMU_WKFR_FOCURF_Msk                     /* FOCU Reset Flag */


/******************  Bit definition for PMU_WKEN register  *******************/
#define PMU_WKEN_WKEN_DPos              (0U)
#define PMU_WKEN_WKEN_Pos               PMU_WKEN_WKEN_DPos
#define PMU_WKEN_WKEN_Msk               (0x3FFFUL << PMU_WKEN_WKEN_Pos)         /* 0x00003FFF */
#define PMU_WKEN_WKEN                   PMU_WKEN_WKEN_Msk                       /* WKEN [13:0] (Wake Up Channel Enable) */
#define PMU_WKEN_WKEN_0                 (0x0001UL << PMU_WKEN_WKEN_Pos)         /* 0x00000001 */
#define PMU_WKEN_WKEN_1                 (0x0002UL << PMU_WKEN_WKEN_Pos)         /* 0x00000002 */
#define PMU_WKEN_WKEN_2                 (0x0004UL << PMU_WKEN_WKEN_Pos)         /* 0x00000004 */
#define PMU_WKEN_WKEN_3                 (0x0008UL << PMU_WKEN_WKEN_Pos)         /* 0x00000008 */
#define PMU_WKEN_WKEN_4                 (0x0010UL << PMU_WKEN_WKEN_Pos)         /* 0x00000010 */
#define PMU_WKEN_WKEN_5                 (0x0020UL << PMU_WKEN_WKEN_Pos)         /* 0x00000020 */
#define PMU_WKEN_WKEN_6                 (0x0040UL << PMU_WKEN_WKEN_Pos)         /* 0x00000040 */
#define PMU_WKEN_WKEN_7                 (0x0080UL << PMU_WKEN_WKEN_Pos)         /* 0x00000080 */
#define PMU_WKEN_WKEN_8                 (0x0100UL << PMU_WKEN_WKEN_Pos)         /* 0x00000100 */
#define PMU_WKEN_WKEN_9                 (0x0200UL << PMU_WKEN_WKEN_Pos)         /* 0x00000200 */
#define PMU_WKEN_WKEN_10                (0x0400UL << PMU_WKEN_WKEN_Pos)         /* 0x00000400 */
#define PMU_WKEN_WKEN_11                (0x0800UL << PMU_WKEN_WKEN_Pos)         /* 0x00000800 */
#define PMU_WKEN_WKEN_12                (0x1000UL << PMU_WKEN_WKEN_Pos)         /* 0x00001000 */
#define PMU_WKEN_WKEN_13                (0x2000UL << PMU_WKEN_WKEN_Pos)         /* 0x00002000 */


#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
