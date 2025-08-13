 /*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	as32x601_mac_regs.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version :        V1.0
 * Date:            2024/08/19
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/19     1.0     build this module
 * Description:     This file contains all the register correlation defines for the MAC firmware library.
 */
#ifndef AS32X601_MAC_REG_H
#define AS32X601_MAC_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_addrmap.h"
#include "as32x601.h"

/*
 * @brief EMAC registers structure
 */
typedef struct 
{
    __IO uint32_t BUS_MODE;               /* BUS_MODE        BUS MODE register,                                         Address offset: 0x00 */
    __IO uint32_t RESERVED0;              /* Reserved,                                                                  Address offset: 0x04 */
    __IO uint32_t TX_POLL;                /* TX_POLL         Transmit Poll Demand register,                             Address offset: 0x08 */
    __IO uint32_t RESERVED1;              /* Reserved,                                                                  Address offset: 0x0C */
    __IO uint32_t RX_POLL;                /* RX_POLL         Receive Poll Demand register,                              Address offset: 0x10 */
    __IO uint32_t RESERVED2;              /* Reserved,                                                                  Address offset: 0x14 */
    __IO uint32_t RDES_BASE_ADDR;         /* RDES_BASE_ADDR  Receive Descriptor List Address register,                  Address offset: 0x18 */
    __IO uint32_t RESERVED3;              /* Reserved,                                                                  Address offset: 0x1C */
    __IO uint32_t TDES_BASE_ADDR;         /* TDES_BASE_ADDR  Transmit Descriptor List Address register,                 Address offset: 0x20 */
    __IO uint32_t RESERVED4;              /* Reserved,                                                                  Address offset: 0x24 */
    __IO uint32_t STATUS;                 /* STATUS          Status register,                                           Address offset: 0x28 */
    __IO uint32_t RESERVED5;              /* Reserved,                                                                  Address offset: 0x2C */
    __IO uint32_t OPT_MODE;               /* OPT_MODE        Operation Mode register,                                   Address offset: 0x30 */
    __IO uint32_t RESERVED6;              /* Reserved,                                                                  Address offset: 0x34 */
    __IO uint32_t INT_ENABLE;             /* INT_ENABLE      Interrupt Enable register,                                 Address offset: 0x38 */
    __IO uint32_t RESERVED7;              /* Reserved,                                                                  Address offset: 0x3C */
    __IO uint32_t FRAME_CNT;              /* FRAME_CNT       Frame and Counter Overflow register,                       Address offset: 0x40 */
    __IO uint32_t RESERVED8;              /* Reserved,                                                                  Address offset: 0x44 */
    __IO uint32_t MDIO_CTRL0;             /* MDIO_CTRL0      MDIO Control register 0,                                   Address offset: 0x48 */
    __IO uint32_t RESERVED9;              /* Reserved,                                                                  Address offset: 0x4C */
    __IO uint32_t MDIO_CTRL1;             /* MDIO_CTRL1      MDIO Control register 1,                                   Address offset: 0x50 */
    __IO uint32_t RESERVED10;             /* Reserved,                                                                  Address offset: 0x54 */
    __IO uint32_t TIMER_CTRL;             /* TIMER_CTRL      General Timer and Interrupt Suppression Control register,  Address offset: 0x58 */
} MAC_TypeDef;

/*
 * @addtogroup MAC Peripheral declaration
 */
#define MAC	((MAC_TypeDef*)MAC_BASE)




/*
 * @addtogroup EMAC peripheral declaration
 */

/******************  Bit definition for MAC_BUS_MODE register  *******************/
#define MAC_BUS_MODE_SWR_DPos       (0U)
#define MAC_BUS_MODE_SWR_Pos        MAC_BUS_MODE_SWR_DPos
#define MAC_BUS_MODE_SWR_Msk        (0x1UL << MAC_BUS_MODE_SWR_Pos)                /* 0x00000001 */
#define MAC_BUS_MODE_SWR            MAC_BUS_MODE_SWR_Msk                           /* Software Reset. */

#define MAC_BUS_MODE_BAR_DPos       (1U)
#define MAC_BUS_MODE_BAR_Pos        MAC_BUS_MODE_BAR_DPos
#define MAC_BUS_MODE_BAR_Msk        (0x1UL << MAC_BUS_MODE_BAR_Pos)                /* 0x00000002 */
#define MAC_BUS_MODE_BAR            MAC_BUS_MODE_BAR_Msk                           /* BUS Arbitration. */

#define MAC_BUS_MODE_DSL_DPos       (2U)
#define MAC_BUS_MODE_DSL_Pos        MAC_BUS_MODE_DSL_DPos
#define MAC_BUS_MODE_DSL_Msk        (0x1FUL << MAC_BUS_MODE_DSL_Pos)               /* 0x0000007c */
#define MAC_BUS_MODE_DSL            MAC_BUS_MODE_DSL_Msk                           /*DSL[4:0] bits (Descriptor Skip Lenngth) */
#define MAC_BUS_MODE_DSL_0          (0x1UL << MAC_BUS_MODE_DSL_Pos)                /* 0x00000004 */
#define MAC_BUS_MODE_DSL_1          (0x2UL << MAC_BUS_MODE_DSL_Pos)                /* 0x00000008 */
#define MAC_BUS_MODE_DSL_2          (0x4UL << MAC_BUS_MODE_DSL_Pos)                /* 0x00000010 */
#define MAC_BUS_MODE_DSL_3          (0x8UL << MAC_BUS_MODE_DSL_Pos)                /* 0x00000020 */
#define MAC_BUS_MODE_DSL_4          (0x10UL << MAC_BUS_MODE_DSL_Pos)               /* 0x00000040 */

#define MAC_BUS_MODE_BLE_DPos       (7U)
#define MAC_BUS_MODE_BLE_Pos        MAC_BUS_MODE_BLE_DPos
#define MAC_BUS_MODE_BLE_Msk        (0x1UL << MAC_BUS_MODE_BLE_Pos)                /* 0x00000080 */
#define MAC_BUS_MODE_BLE            MAC_BUS_MODE_BLE_Msk                           /* Big-Endian and Little-Endian Select. */

#define MAC_BUS_MODE_PBL_DPos       (8U)
#define MAC_BUS_MODE_PBL_Pos        MAC_BUS_MODE_PBL_DPos
#define MAC_BUS_MODE_PBL_Msk        (0x3FUL << MAC_BUS_MODE_PBL_Pos)               /* 0x00003F00 */
#define MAC_BUS_MODE_PBL            MAC_BUS_MODE_PBL_Msk                           /*PBL[5:0] bits (Programmable Burst Length) */
#define MAC_BUS_MODE_PBL_0          (0x1UL << MAC_BUS_MODE_PBL_Pos)                /* 0x00000100 */
#define MAC_BUS_MODE_PBL_1          (0x2UL << MAC_BUS_MODE_PBL_Pos)                /* 0x00000200 */
#define MAC_BUS_MODE_PBL_2          (0x4UL << MAC_BUS_MODE_PBL_Pos)                /* 0x00000400 */
#define MAC_BUS_MODE_PBL_3          (0x8UL << MAC_BUS_MODE_PBL_Pos)                /* 0x00000800 */
#define MAC_BUS_MODE_PBL_4          (0x10UL << MAC_BUS_MODE_PBL_Pos)               /* 0x00001000 */
#define MAC_BUS_MODE_PBL_5          (0x20UL << MAC_BUS_MODE_PBL_Pos)               /* 0x00002000 */

#define MAC_BUS_MODE_TAP_DPos       (17U)
#define MAC_BUS_MODE_TAP_Pos        MAC_BUS_MODE_TAP_DPos
#define MAC_BUS_MODE_TAP_Msk        (0x07UL << MAC_BUS_MODE_TAP_Pos)               /* 0x000E0000 */
#define MAC_BUS_MODE_TAP            MAC_BUS_MODE_TAP_Msk                           /*TAP[2:0] bits (Transmit Automatic Polling) */
#define MAC_BUS_MODE_TAP_0          (0x1UL << MAC_BUS_MODE_TAP_Pos)                /* 0x00020000 */
#define MAC_BUS_MODE_TAP_1          (0x2UL << MAC_BUS_MODE_TAP_Pos)                /* 0x00040000 */
#define MAC_BUS_MODE_TAP_2          (0x3UL << MAC_BUS_MODE_TAP_Pos)                /* 0x00080000 */

#define MAC_BUS_MODE_DBO_DPos       (20U)
#define MAC_BUS_MODE_DBO_Pos        MAC_BUS_MODE_DBO_DPos
#define MAC_BUS_MODE_DBO_Msk        (0x1UL << MAC_BUS_MODE_DBO_Pos)                /* 0x00100000 */
#define MAC_BUS_MODE_DBO            MAC_BUS_MODE_DBO_Msk                           /* Descriptor Byte Order. */

/******************  Bit definition for MAC_TX_MODE register  *******************/
#define MAC_TX_POLL_RPD_DPos        (0U)
#define MAC_TX_POLL_RPD_Pos         MAC_TX_POLL_RPD_DPos
#define MAC_TX_POLL_RPD_Msk         (0xFFFFFFFFUL << MAC_TX_POLL_RPD_Pos)          /* 0xFFFFFFFF */
#define MAC_TX_POLL_RPD             MAC_TX_POLL_RPD_Msk                            /* Send Poll Descriptor. */

/******************  Bit definition for MAC_RX_MODE register  *******************/
#define MAC_RX_POLL_RPD_DPos        (0U)
#define MAC_RX_POLL_RPD_Pos         MAC_RX_POLL_RPD_DPos
#define MAC_RX_POLL_RPD_Msk         (0xFFFFFFFFUL << MAC_RX_POLL_RPD_Pos)          /* 0xFFFFFFFF */
#define MAC_RX_POLL_RPD             MAC_RX_POLL_RPD_Msk                            /* Receive Poll Descriptor. */

/******************  Bit definition for MAC_RDES_BASE_ADDR register  *******************/
#define MAC_RDES_BASE_ADDR_RLAD_DPos       (0U)
#define MAC_RDES_BASE_ADDR_RLAD_Pos        MAC_RDES_BASE_ADDR_RLAD_DPos
#define MAC_RDES_BASE_ADDR_RLAD_Msk        (0xFFFFFFFFUL << MAC_RDES_BASE_ADDR_RLAD_Pos)   /* 0xFFFFFFFF */
#define MAC_RDES_BASE_ADDR_RLAD            MAC_RDES_BASE_ADDR_RLAD_Msk                     /* Receive List Address Start. */

/******************  Bit definition for MAC_TDES_BASE_ADDR register  *******************/
#define MAC_TDES_BASE_ADDR_RLAD_DPos       (0U)
#define MAC_TDES_BASE_ADDR_RLAD_Pos        MAC_TDES_BASE_ADDR_RLAD_DPos
#define MAC_TDES_BASE_ADDR_RLAD_Msk        (0xFFFFFFFFUL << MAC_TDES_BASE_ADDR_RLAD_Pos)   /* 0xFFFFFFFF */
#define MAC_TDES_BASE_ADDR_RLAD            MAC_TDES_BASE_ADDR_RLAD_Msk                     /* Transmit List Address Start. */

/******************  Bit definition for MAC_RX_MODE register  *******************/
#define MAC_STATUS_TI_DPos          (0U)
#define MAC_STATUS_TI_Pos           MAC_STATUS_TI_DPos
#define MAC_STATUS_TI_Msk           (0x1UL << MAC_STATUS_TI_Pos)                /* 0x00000001 */
#define MAC_STATUS_TI               MAC_STATUS_TI_Msk                           /* Transmit Interrupt. */

#define MAC_STATUS_TPS_DPos         (1U)
#define MAC_STATUS_TPS_Pos          MAC_STATUS_TPS_DPos
#define MAC_STATUS_TPS_Msk          (0x1UL << MAC_STATUS_TPS_Pos)               /* 0x00000002 */
#define MAC_STATUS_TPS              MAC_STATUS_TPS_Msk                          /* Transmit Process Stopped. */

#define MAC_STATUS_TU_DPos          (2U)
#define MAC_STATUS_TU_Pos           MAC_STATUS_TU_DPos
#define MAC_STATUS_TU_Msk           (0x1UL << MAC_STATUS_TU_Pos)                /* 0x00000004 */
#define MAC_STATUS_TU               MAC_STATUS_TU_Msk                           /* Transmit Buffer Unavailable. */

#define MAC_STATUS_UNF_DPos         (5U)
#define MAC_STATUS_UNF_Pos          MAC_STATUS_UNF_DPos
#define MAC_STATUS_UNF_Msk          (0x1UL << MAC_STATUS_UNF_Pos)               /* 0x00000020 */
#define MAC_STATUS_UNF              MAC_STATUS_UNF_Msk                          /* Transmit Underflow. */

#define MAC_STATUS_RI_DPos          (6U)
#define MAC_STATUS_RI_Pos           MAC_STATUS_RI_DPos
#define MAC_STATUS_RI_Msk           (0x1UL << MAC_STATUS_RI_Pos)                /* 0x00000040 */
#define MAC_STATUS_RI               MAC_STATUS_RI_Msk                           /* Receive Interrupt. */

#define MAC_STATUS_RU_DPos          (7U)
#define MAC_STATUS_RU_Pos           MAC_STATUS_RU_DPos
#define MAC_STATUS_RU_Msk           (0x1UL << MAC_STATUS_RU_Pos)                /* 0x00000080 */
#define MAC_STATUS_RU               MAC_STATUS_RU_Msk                           /* Receive Buffer Unavailable. */

#define MAC_STATUS_RPS_DPos         (8U)
#define MAC_STATUS_RPS_Pos          MAC_STATUS_RPS_DPos
#define MAC_STATUS_RPS_Msk          (0x1UL << MAC_STATUS_RPS_Pos)               /* 0x00000100 */
#define MAC_STATUS_RPS              MAC_STATUS_RPS_Msk                          /* Receive Process Stopped. */

#define MAC_STATUS_ETI_DPos         (10U)
#define MAC_STATUS_ETI_Pos          MAC_STATUS_ETI_DPos
#define MAC_STATUS_ETI_Msk          (0x1UL << MAC_STATUS_ETI_Pos)               /* 0x00000400 */
#define MAC_STATUS_ETI              MAC_STATUS_ETI_Msk                          /* Early Transmit Interrupt. */

#define MAC_STATUS_GTE_DPos         (11U)
#define MAC_STATUS_GTE_Pos          MAC_STATUS_GTE_DPos
#define MAC_STATUS_GTE_Msk          (0x1UL << MAC_STATUS_GTE_Pos)               /* 0x00000800 */
#define MAC_STATUS_GTE              MAC_STATUS_GTE_Msk                          /* General Timer Expiry. */

#define MAC_STATUS_ERI_DPos         (14U)
#define MAC_STATUS_ERI_Pos          MAC_STATUS_ERI_DPos
#define MAC_STATUS_ERI_Msk          (0x1UL << MAC_STATUS_ERI_Pos)               /* 0x00004000 */
#define MAC_STATUS_ERI              MAC_STATUS_ERI_Msk                          /* Early Receive Interrupt. */

#define MAC_STATUS_AIS_DPos         (15U)
#define MAC_STATUS_AIS_Pos          MAC_STATUS_AIS_DPos
#define MAC_STATUS_AIS_Msk          (0x1UL << MAC_STATUS_AIS_Pos)               /* 0x00008000 */
#define MAC_STATUS_AIS              MAC_STATUS_AIS_Msk                          /* Abnormal Interrupt Summary. */

#define MAC_STATUS_NIS_DPos         (16U)
#define MAC_STATUS_NIS_Pos          MAC_STATUS_NIS_DPos
#define MAC_STATUS_NIS_Msk          (0x1UL << MAC_STATUS_NIS_Pos)               /* 0x00010000 */
#define MAC_STATUS_NIS              MAC_STATUS_NIS_Msk                          /* Normal Interrupt Summary. */

#define MAC_STATUS_RS_DPos          (17U)
#define MAC_STATUS_RS_Pos           MAC_STATUS_RS_DPos
#define MAC_STATUS_RS_Msk           (0x7UL << MAC_STATUS_RS_Pos)                /* 0x000E0000 */
#define MAC_STATUS_RS               MAC_STATUS_RS_Msk                           /* RS[2:0] bits (Receive Process State) */
#define MAC_STATUS_RS_0             (0x1UL << MAC_STATUS_RS_Pos)                /* 0x00020000 */
#define MAC_STATUS_RS_1             (0x2UL << MAC_STATUS_RS_Pos)                /* 0x00040000 */
#define MAC_STATUS_RS_2             (0x4UL << MAC_STATUS_RS_Pos)                /* 0x00080000 */

#define MAC_STATUS_TS_DPos          (20U)
#define MAC_STATUS_TS_Pos           MAC_STATUS_TS_DPos
#define MAC_STATUS_TS_Msk           (0x7UL << MAC_STATUS_TS_Pos)                /* 0x00700000 */
#define MAC_STATUS_TS               MAC_STATUS_TS_Msk                           /* TS[2:0] bits (Transmit Process State) */
#define MAC_STATUS_TS_0             (0x1UL << MAC_STATUS_TS_Pos)                /* 0x00100000 */
#define MAC_STATUS_TS_1             (0x2UL << MAC_STATUS_TS_Pos)                /* 0x00200000 */
#define MAC_STATUS_TS_2             (0x4UL << MAC_STATUS_TS_Pos)                /* 0x00400000 */

/******************  Bit definition for MAC_OPT_MODE register  *******************/
#define MAC_OPT_MODE_HP_DPos       (0U)
#define MAC_OPT_MODE_HP_Pos        MAC_OPT_MODE_HP_DPos
#define MAC_OPT_MODE_HP_Msk        (0x1UL << MAC_OPT_MODE_HP_Pos)             /* 0x00000001 */
#define MAC_OPT_MODE_HP            MAC_OPT_MODE_HP_Msk                        /* Hash/Perfect Filter Mode (Read Only). */

#define MAC_OPT_MODE_SR_DPos       (1U)
#define MAC_OPT_MODE_SR_Pos        MAC_OPT_MODE_SR_DPos
#define MAC_OPT_MODE_SR_Msk        (0x1UL << MAC_OPT_MODE_SR_Pos)             /* 0x00000002 */
#define MAC_OPT_MODE_SR            MAC_OPT_MODE_SR_Msk                        /* Start/Stop Receive Command. */

#define MAC_OPT_MODE_HO_DPos       (2U)
#define MAC_OPT_MODE_HO_Pos        MAC_OPT_MODE_HO_DPos
#define MAC_OPT_MODE_HO_Msk        (0x1UL << MAC_OPT_MODE_HO_Pos)             /* 0x00000004 */
#define MAC_OPT_MODE_HO            MAC_OPT_MODE_HO_Msk                        /* Hash Only Filter Mode (Read Only). */

#define MAC_OPT_MODE_PB_DPos       (3U)
#define MAC_OPT_MODE_PB_Pos        MAC_OPT_MODE_PB_DPos
#define MAC_OPT_MODE_PB_Msk        (0x1UL << MAC_OPT_MODE_PB_Pos)             /* 0x00000008 */
#define MAC_OPT_MODE_PB            MAC_OPT_MODE_PB_Msk                        /* Pass Bad Frames. */

#define MAC_OPT_MODE_IF_DPos       (4U)
#define MAC_OPT_MODE_IF_Pos        MAC_OPT_MODE_IF_DPos
#define MAC_OPT_MODE_IF_Msk        (0x1UL << MAC_OPT_MODE_IF_Pos)             /* 0x00000010 */
#define MAC_OPT_MODE_IF            MAC_OPT_MODE_IF_Msk                        /* Inverse Filtering (Read Only). */

#define MAC_OPT_MODE_PR_DPos       (6U)
#define MAC_OPT_MODE_PR_Pos        MAC_OPT_MODE_PR_DPos
#define MAC_OPT_MODE_PR_Msk        (0x1UL << MAC_OPT_MODE_PR_Pos)             /* 0x00000040 */
#define MAC_OPT_MODE_PR            MAC_OPT_MODE_PR_Msk                        /* Promiscuous Mode. */

#define MAC_OPT_MODE_PM_DPos       (7U)
#define MAC_OPT_MODE_PM_Pos        MAC_OPT_MODE_PM_DPos
#define MAC_OPT_MODE_PM_Msk        (0x1UL << MAC_OPT_MODE_PM_Pos)             /* 0x00000080 */
#define MAC_OPT_MODE_PM            MAC_OPT_MODE_PM_Msk                        /* Pass All Multicast. */

#define MAC_OPT_MODE_FD_DPos       (9U)
#define MAC_OPT_MODE_FD_Pos        MAC_OPT_MODE_FD_DPos
#define MAC_OPT_MODE_FD_Msk        (0x1UL << MAC_OPT_MODE_FD_Pos)             /* 0x00000200 */
#define MAC_OPT_MODE_FD            MAC_OPT_MODE_FD_Msk                        /* Full Duplex Mode. */

#define MAC_OPT_MODE_ST_DPos       (13U)
#define MAC_OPT_MODE_ST_Pos        MAC_OPT_MODE_ST_DPos
#define MAC_OPT_MODE_ST_Msk        (0x1UL << MAC_OPT_MODE_ST_Pos)             /* 0x00002000 */
#define MAC_OPT_MODE_ST            MAC_OPT_MODE_ST_Msk                        /* Start/Stop Transmission Command. */

#define MAC_OPT_MODE_TR_DPos       (15U)
#define MAC_OPT_MODE_TR_Pos        MAC_OPT_MODE_TR_DPos
#define MAC_OPT_MODE_TR_Msk        (0x1UL << MAC_OPT_MODE_TR_Pos)             /* 0x00008000 */
#define MAC_OPT_MODE_TR            MAC_OPT_MODE_TR_Msk                        /* Threshold Control Bit. */

#define MAC_OPT_MODE_SF_DPos       (21U)
#define MAC_OPT_MODE_SF_Pos        MAC_OPT_MODE_SF_DPos
#define MAC_OPT_MODE_SF_Msk        (0x1UL << MAC_OPT_MODE_SF_Pos)             /* 0x00200000 */
#define MAC_OPT_MODE_SF            MAC_OPT_MODE_SF_Msk                        /* Store and Forward. */

#define MAC_OPT_MODE_TTM_DPos      (22U)
#define MAC_OPT_MODE_TTM_Pos       MAC_OPT_MODE_TTM_DPos
#define MAC_OPT_MODE_TTM_Msk       (0x1UL << MAC_OPT_MODE_TTM_Pos)            /* 0x00400000 */
#define MAC_OPT_MODE_TTM           MAC_OPT_MODE_TTM_Msk                       /* Transmit Threshold Mode. */

#define MAC_OPT_MODE_RA_DPos       (30U)
#define MAC_OPT_MODE_RA_Pos        MAC_OPT_MODE_RA_DPos
#define MAC_OPT_MODE_RA_Msk        (0x1UL << MAC_OPT_MODE_RA_Pos)             /* 0x40000000 */
#define MAC_OPT_MODE_RA            MAC_OPT_MODE_RA_Msk                        /* Receive All. */

/******************  Bit definition for MAC_INT_ENABLE register  *******************/
#define MAC_INT_ENABLE_TIE_DPos       (0U)
#define MAC_INT_ENABLE_TIE_Pos        MAC_INT_ENABLE_TIE_DPos
#define MAC_INT_ENABLE_TIE_Msk        (0x1UL << MAC_INT_ENABLE_TIE_Pos)             /* 0x00000001 */
#define MAC_INT_ENABLE_TIE            MAC_INT_ENABLE_TIE_Msk                        /* Transmit Interrupt Enable. */

#define MAC_INT_ENABLE_TSE_DPos       (1U)
#define MAC_INT_ENABLE_TSE_Pos        MAC_INT_ENABLE_TSE_DPos
#define MAC_INT_ENABLE_TSE_Msk        (0x1UL << MAC_INT_ENABLE_TSE_Pos)             /* 0x00000002 */
#define MAC_INT_ENABLE_TSE            MAC_INT_ENABLE_TSE_Msk                        /* Transmit Stop Interrupt Enable. */

#define MAC_INT_ENABLE_TUE_DPos       (2U)
#define MAC_INT_ENABLE_TUE_Pos        MAC_INT_ENABLE_TUE_DPos
#define MAC_INT_ENABLE_TUE_Msk        (0x1UL << MAC_INT_ENABLE_TUE_Pos)             /* 0x00000004 */
#define MAC_INT_ENABLE_TUE            MAC_INT_ENABLE_TUE_Msk                        /* Transmit Buffer Unavailable Interrupt Enable. */

#define MAC_INT_ENABLE_UNE_DPos       (5U)
#define MAC_INT_ENABLE_UNE_Pos        MAC_INT_ENABLE_UNE_DPos
#define MAC_INT_ENABLE_UNE_Msk        (0x1UL << MAC_INT_ENABLE_UNE_Pos)             /* 0x00000020 */
#define MAC_INT_ENABLE_UNE            MAC_INT_ENABLE_UNE_Msk                        /* Transmit Underflow Interrupt Enable. */

#define MAC_INT_ENABLE_RIE_DPos       (6U)
#define MAC_INT_ENABLE_RIE_Pos        MAC_INT_ENABLE_RIE_DPos
#define MAC_INT_ENABLE_RIE_Msk        (0x1UL << MAC_INT_ENABLE_RIE_Pos)             /* 0x00000040 */
#define MAC_INT_ENABLE_RIE            MAC_INT_ENABLE_RIE_Msk                        /* Receive Interrupt Enable. */

#define MAC_INT_ENABLE_RUE_DPos       (7U)
#define MAC_INT_ENABLE_RUE_Pos        MAC_INT_ENABLE_RUE_DPos
#define MAC_INT_ENABLE_RUE_Msk        (0x1UL << MAC_INT_ENABLE_RUE_Pos)             /* 0x00000080 */
#define MAC_INT_ENABLE_RUE            MAC_INT_ENABLE_RUE_Msk                        /* Receive Buffer Unavailable Interrupt Enable. */

#define MAC_INT_ENABLE_RSE_DPos       (8U)
#define MAC_INT_ENABLE_RSE_Pos        MAC_INT_ENABLE_RSE_DPos
#define MAC_INT_ENABLE_RSE_Msk        (0x1UL << MAC_INT_ENABLE_RSE_Pos)             /* 0x00000100 */
#define MAC_INT_ENABLE_RSE            MAC_INT_ENABLE_RSE_Msk                        /* Receive Stop Interrupt Enable. */

#define MAC_INT_ENABLE_ETE_DPos       (10U)
#define MAC_INT_ENABLE_ETE_Pos        MAC_INT_ENABLE_ETE_DPos
#define MAC_INT_ENABLE_ETE_Msk        (0x1UL << MAC_INT_ENABLE_ETE_Pos)             /* 0x00000400 */
#define MAC_INT_ENABLE_ETE            MAC_INT_ENABLE_ETE_Msk                        /* Early Transmit Interrupt Enable. */

#define MAC_INT_ENABLE_GTE_DPos       (11U)
#define MAC_INT_ENABLE_GTE_Pos        MAC_INT_ENABLE_GTE_DPos
#define MAC_INT_ENABLE_GTE_Msk        (0x1UL << MAC_INT_ENABLE_GTE_Pos)             /* 0x00000800 */
#define MAC_INT_ENABLE_GTE            MAC_INT_ENABLE_GTE_Msk                        /* General Timer Expiry Interrupt Enable. */

#define MAC_INT_ENABLE_ERE_DPos       (14U)
#define MAC_INT_ENABLE_ERE_Pos        MAC_INT_ENABLE_ERE_DPos
#define MAC_INT_ENABLE_ERE_Msk        (0x1UL << MAC_INT_ENABLE_ERE_Pos)             /* 0x00004000 */
#define MAC_INT_ENABLE_ERE            MAC_INT_ENABLE_ERE_Msk                        /* Early Receive Interrupt Enable. */

#define MAC_INT_ENABLE_AIE_DPos       (15U)
#define MAC_INT_ENABLE_AIE_Pos        MAC_INT_ENABLE_AIE_DPos
#define MAC_INT_ENABLE_AIE_Msk        (0x1UL << MAC_INT_ENABLE_AIE_Pos)             /* 0x00008000 */
#define MAC_INT_ENABLE_AIE            MAC_INT_ENABLE_AIE_Msk                        /* Abnormal Interrupt Enable. */

#define MAC_INT_ENABLE_NIE_DPos       (16U)
#define MAC_INT_ENABLE_NIE_Pos        MAC_INT_ENABLE_NIE_DPos
#define MAC_INT_ENABLE_NIE_Msk        (0x1UL << MAC_INT_ENABLE_NIE_Pos)             /* 0x00010000 */
#define MAC_INT_ENABLE_NIE            MAC_INT_ENABLE_NIE_Msk                        /* Normal Interrupt Summary Enable. */

/******************  Bit definition for MAC_FRAME_CNT register  *******************/
#define MAC_FRAME_CNT_MFC_DPos        (0U)
#define MAC_FRAME_CNT_MFC_Pos         MAC_FRAME_CNT_MFC_DPos
#define MAC_FRAME_CNT_MFC_Msk         (0xFFFFUL << MAC_FRAME_CNT_MFC_Pos)        /* 0x0000FFFF */
#define MAC_FRAME_CNT_MFC             MAC_FRAME_CNT_MFC_Msk                       /* Missed Frame Counter (Read Only). */

#define MAC_FRAME_CNT_MFO_DPos        (16U)
#define MAC_FRAME_CNT_MFO_Pos         MAC_FRAME_CNT_MFO_DPos
#define MAC_FRAME_CNT_MFO_Msk         (0x1UL << MAC_FRAME_CNT_MFO_Pos)           /* 0x00010000 */
#define MAC_FRAME_CNT_MFO             MAC_FRAME_CNT_MFO_Msk                       /* Missed Frame Overflow (Read Only). */

#define MAC_FRAME_CNT_FOC_DPos        (17U)
#define MAC_FRAME_CNT_FOC_Pos         MAC_FRAME_CNT_FOC_DPos
#define MAC_FRAME_CNT_FOC_Msk         (0x7FFUL << MAC_FRAME_CNT_FOC_Pos)         /* 0x00FFFE00 */
#define MAC_FRAME_CNT_FOC             MAC_FRAME_CNT_FOC_Msk                       /* FIFO Overflow Counter (Read Only). */

#define MAC_FRAME_CNT_OCO_DPos        (28U)
#define MAC_FRAME_CNT_OCO_Pos         MAC_FRAME_CNT_OCO_DPos
#define MAC_FRAME_CNT_OCO_Msk         (0x1UL << MAC_FRAME_CNT_OCO_Pos)           /* 0x10000000 */
#define MAC_FRAME_CNT_OCO             MAC_FRAME_CNT_OCO_Msk                       /* Overflow Counter Overflow (Read Only). */

/******************  Bit definition for MAC_MDIO_CTRL0 register  *******************/
#define MAC_MDIO_CTRL0_MDC_DIV_DPos    (0U)
#define MAC_MDIO_CTRL0_MDC_DIV_Pos     MAC_MDIO_CTRL0_MDC_DIV_DPos
#define MAC_MDIO_CTRL0_MDC_DIV_Msk     (0xFFFFUL << MAC_MDIO_CTRL0_MDC_DIV_Pos)    /* 0x0000FFFF */
#define MAC_MDIO_CTRL0_MDC_DIV         MAC_MDIO_CTRL0_MDC_DIV_Msk                  /* MDC Divider (Read/Write). */

#define MAC_MDIO_CTRL0_MDCE_DPos       (16U)
#define MAC_MDIO_CTRL0_MDCE_Pos        MAC_MDIO_CTRL0_MDCE_DPos
#define MAC_MDIO_CTRL0_MDCE_Msk        (0x1UL << MAC_MDIO_CTRL0_MDCE_Pos)          /* 0x00010000 */
#define MAC_MDIO_CTRL0_MDCE            MAC_MDIO_CTRL0_MDCE_Msk                    /* MDIO Enable (Read/Write). */

/******************  Bit definition for MAC_MDIO_CTRL1 register  *******************/
#define MAC_MDIO_CTRL1_RDATA_DPos       (0U)
#define MAC_MDIO_CTRL1_RDATA_Pos        MAC_MDIO_CTRL1_RDATA_DPos
#define MAC_MDIO_CTRL1_RDATA_Msk        (0xFFFFUL << MAC_MDIO_CTRL1_RDATA_Pos)      /* 0x0000FFFF */
#define MAC_MDIO_CTRL1_RDATA            MAC_MDIO_CTRL1_RDATA_Msk                    /* MDIO Read Data. */

#define MAC_MDIO_CTRL1_TURN_DPos        (16U)
#define MAC_MDIO_CTRL1_TURN_Pos         MAC_MDIO_CTRL1_TURN_DPos
#define MAC_MDIO_CTRL1_TURN_Msk         (0x3UL << MAC_MDIO_CTRL1_TURN_Pos)          /* 0x00030000 */
#define MAC_MDIO_CTRL1_TURN             MAC_MDIO_CTRL1_TURN_Msk                     /* TURN[1:0] bits (MDIO Turnaround Time) */
#define MAC_MDIO_CTRL1_TURN_0           (0x1UL << MAC_MDIO_CTRL1_TURN_Pos)          /* 0x00010000 */
#define MAC_MDIO_CTRL1_TURN_1           (0x2UL << MAC_MDIO_CTRL1_TURN_Pos)          /* 0x00020000 */


#define MAC_MDIO_CTRL1_REG_ADDR_DPos    (18U)
#define MAC_MDIO_CTRL1_REG_ADDR_Pos     MAC_MDIO_CTRL1_REG_ADDR_DPos
#define MAC_MDIO_CTRL1_REG_ADDR_Msk     (0x1FUL << MAC_MDIO_CTRL1_REG_ADDR_Pos)     /* 0x007C0000 */
#define MAC_MDIO_CTRL1_REG_ADDR         MAC_MDIO_CTRL1_REG_ADDR_Msk                 /* PHY Register Address. */

#define MAC_MDIO_CTRL1_PHY_ADDR_DPos    (23U)
#define MAC_MDIO_CTRL1_PHY_ADDR_Pos     MAC_MDIO_CTRL1_PHY_ADDR_DPos
#define MAC_MDIO_CTRL1_PHY_ADDR_Msk     (0x1FUL << MAC_MDIO_CTRL1_PHY_ADDR_Pos)     /* 0x0F800000 */
#define MAC_MDIO_CTRL1_PHY_ADDR         MAC_MDIO_CTRL1_PHY_ADDR_Msk                 /* PHY Address. */

#define MAC_MDIO_CTRL1_RDWR_DPos        (28U)
#define MAC_MDIO_CTRL1_RDWR_Pos         MAC_MDIO_CTRL1_RDWR_DPos
#define MAC_MDIO_CTRL1_RDWR_Msk         (0x3UL << MAC_MDIO_CTRL1_RDWR_Pos)          /* 0x30000000 */
#define MAC_MDIO_CTRL1_RDWR             MAC_MDIO_CTRL1_RDWR_Msk                     /* RDWR[1:0] bits (Read/Write Flag) */
#define MAC_MDIO_CTRL1_RDWR_0           (0x1UL << MAC_MDIO_CTRL1_RDWR_Pos)          /* 0x10000000 */
#define MAC_MDIO_CTRL1_RDWR_1           (0x2UL << MAC_MDIO_CTRL1_RDWR_Pos)          /* 0x20000000 */

#define MAC_MDIO_CTRL1_START0_DPos       (30U)
#define MAC_MDIO_CTRL1_START0_Pos        MAC_MDIO_CTRL1_START0_DPos
#define MAC_MDIO_CTRL1_START0_Msk        (0x1UL << MAC_MDIO_CTRL1_START0_Pos)           /* 0x40000000 */
#define MAC_MDIO_CTRL1_START0            MAC_MDIO_CTRL1_START0_Msk                      /* Start bit 0. */

#define MAC_MDIO_CTRL1_ACK_DPos         (31U)
#define MAC_MDIO_CTRL1_ACK_Pos          MAC_MDIO_CTRL1_ACK_DPos
#define MAC_MDIO_CTRL1_ACK_Msk          (0x1UL << MAC_MDIO_CTRL1_ACK_Pos)           /* 0x80000000 */
#define MAC_MDIO_CTRL1_ACK              MAC_MDIO_CTRL1_ACK_Msk                      /* Acknowledge Signal. */

#define MAC_MDIO_CTRL1_START1_DPos       (31U)
#define MAC_MDIO_CTRL1_START1_Pos        MAC_MDIO_CTRL1_START1_DPos
#define MAC_MDIO_CTRL1_START1_Msk        (0x1UL << MAC_MDIO_CTRL1_START1_Pos)           /* 0x80000000 */
#define MAC_MDIO_CTRL1_START1            MAC_MDIO_CTRL1_START1_Msk                      /* Start bit 1. */

/******************  Bit definition for MAC_TIMER_CTRL register  *******************/
#define MAC_TIMER_CTRL_TIM_DPos         (0U)
#define MAC_TIMER_CTRL_TIM_Pos          MAC_TIMER_CTRL_TIM_DPos
#define MAC_TIMER_CTRL_TIM_Msk          (0xFFFFUL << MAC_TIMER_CTRL_TIM_Pos)         /* 0x0000FFFF */
#define MAC_TIMER_CTRL_TIM              MAC_TIMER_CTRL_TIM_Msk                       /* TIM[15:0] bits (Timer Value) */

#define MAC_TIMER_CTRL_CON_DPos         (16U)
#define MAC_TIMER_CTRL_CON_Pos          MAC_TIMER_CTRL_CON_DPos
#define MAC_TIMER_CTRL_CON_Msk          (0x1UL << MAC_TIMER_CTRL_CON_Pos)            /* 0x00010000 */
#define MAC_TIMER_CTRL_CON              MAC_TIMER_CTRL_CON_Msk                       /* Continuous Mode. */

#define MAC_TIMER_CTRL_NRP_DPos         (17U)
#define MAC_TIMER_CTRL_NRP_Pos          MAC_TIMER_CTRL_NRP_DPos
#define MAC_TIMER_CTRL_NRP_Msk          (0x7UL << MAC_TIMER_CTRL_NRP_Pos)            /* 0x000E0000 */
#define MAC_TIMER_CTRL_NRP              MAC_TIMER_CTRL_NRP_Msk                       /* NRP[2:0] bits (Number of Received Packets) */
#define MAC_TIMER_CTRL_NRP_0            (0x1UL << MAC_TIMER_CTRL_NRP_Pos)            /* 0x00020000 */
#define MAC_TIMER_CTRL_NRP_1            (0x2UL << MAC_TIMER_CTRL_NRP_Pos)            /* 0x00040000 */
#define MAC_TIMER_CTRL_NRP_2            (0x4UL << MAC_TIMER_CTRL_NRP_Pos)            /* 0x00080000 */

#define MAC_TIMER_CTRL_RT_DPos          (20U)
#define MAC_TIMER_CTRL_RT_Pos           MAC_TIMER_CTRL_RT_DPos
#define MAC_TIMER_CTRL_RT_Msk           (0xFUL << MAC_TIMER_CTRL_RT_Pos)             /* 0x00F00000 */
#define MAC_TIMER_CTRL_RT               MAC_TIMER_CTRL_RT_Msk                        /* RT[3:0] bits (Receive Timer) */
#define MAC_TIMER_CTRL_RT_0             (0x1UL << MAC_TIMER_CTRL_RT_Pos)             /* 0x00100000 */
#define MAC_TIMER_CTRL_RT_1             (0x2UL << MAC_TIMER_CTRL_RT_Pos)             /* 0x00200000 */
#define MAC_TIMER_CTRL_RT_2             (0x4UL << MAC_TIMER_CTRL_RT_Pos)             /* 0x00400000 */
#define MAC_TIMER_CTRL_RT_3             (0x8UL << MAC_TIMER_CTRL_RT_Pos)             /* 0x00800000 */

#define MAC_TIMER_CTRL_NTP_DPos         (24U)
#define MAC_TIMER_CTRL_NTP_Pos          MAC_TIMER_CTRL_NTP_DPos
#define MAC_TIMER_CTRL_NTP_Msk          (0x7UL << MAC_TIMER_CTRL_NTP_Pos)            /* 0x07000000 */
#define MAC_TIMER_CTRL_NTP              MAC_TIMER_CTRL_NTP_Msk                       /* NTP[2:0] bits (Number of Transmitted Packets) */
#define MAC_TIMER_CTRL_NTP_0            (0x1UL << MAC_TIMER_CTRL_NTP_Pos)            /* 0x01000000 */
#define MAC_TIMER_CTRL_NTP_1            (0x2UL << MAC_TIMER_CTRL_NTP_Pos)            /* 0x02000000 */
#define MAC_TIMER_CTRL_NTP_2            (0x4UL << MAC_TIMER_CTRL_NTP_Pos)            /* 0x04000000 */

#define MAC_TIMER_CTRL_TT_DPos          (27U)
#define MAC_TIMER_CTRL_TT_Pos           MAC_TIMER_CTRL_TT_DPos
#define MAC_TIMER_CTRL_TT_Msk           (0xFUL << MAC_TIMER_CTRL_TT_Pos)             /* 0x78000000 */
#define MAC_TIMER_CTRL_TT               MAC_TIMER_CTRL_TT_Msk                        /* TT[3:0] bits (Transmit Timer) */
#define MAC_TIMER_CTRL_TT_0             (0x1UL << MAC_TIMER_CTRL_TT_Pos)             /* 0x08000000 */
#define MAC_TIMER_CTRL_TT_1             (0x2UL << MAC_TIMER_CTRL_TT_Pos)             /* 0x10000000 */
#define MAC_TIMER_CTRL_TT_2             (0x4UL << MAC_TIMER_CTRL_TT_Pos)             /* 0x20000000 */
#define MAC_TIMER_CTRL_TT_3             (0x8UL << MAC_TIMER_CTRL_TT_Pos)             /* 0x40000000 */

#define MAC_TIMER_CTRL_CS_DPos          (31U)
#define MAC_TIMER_CTRL_CS_Pos           MAC_TIMER_CTRL_CS_DPos
#define MAC_TIMER_CTRL_CS_Msk           (0x1UL << MAC_TIMER_CTRL_CS_Pos)             /* 0x80000000 */
#define MAC_TIMER_CTRL_CS               MAC_TIMER_CTRL_CS_Msk                        /* Cycle Size. */

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/
