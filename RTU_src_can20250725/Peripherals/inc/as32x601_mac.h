/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	  as32x601_mac.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			      2024/08/19
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/19     1.0     build this module
 * Description:     This file contains all the functions prototypes for the MAC configuration.
 */

#ifndef AS32X601_MAC_H
#define AS32X601_MAC_H

#include "as32x601_mac_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @defgroup  MAC Init structure definition
 */
typedef struct{
    uint32_t MAC_AutoPollInterval;                  /* Transmit auto poll interval */
    uint32_t MAC_DescriptorByteEndianMode;          /* Descriptor byte sort mode */ 
    uint32_t MAC_ProgrammablePulseLength;           /* Programmable pulse length */
    uint32_t MAC_DataEndianMode;                    /* Data endian mode */
    uint32_t MAC_DescriptorSkipLength;              /* Descriptor skip length */
    uint32_t MAC_BusArbitrationScheme;              /* Bus Arbitration scheme */

    uint32_t MAC_ReceiveAll;                        /* Receives all incoming frames */
    uint32_t MAC_TransmitThresholdMode;             /* Transmit Threshold Mode*/
    uint32_t MAC_StoreandForward;                   /* Store and forward */
    uint32_t MAC_ThresholdControlBits;              /* Threshold Control Bits*/
    uint32_t MAC_TransmitMode;                      /* Transmit Mode */
    uint32_t MAC_PassAllMulticast;                  /* Pass All Multicast */
    uint32_t MAC_PromiscuousMode;                   /* Promiscuous Mode */
    uint32_t MAC_PassBadFrame;                      /* Pass Bad Frame */


    uint32_t MAC_CycleSize;                         /* Transmitting and receiving Period Indicates the period */
    uint32_t MAC_TransmitTimer;                     /* Transmit Timer */
    uint32_t MAC_TransmitPacketNumber;              /* Transmit Packet Number */
    uint32_t MAC_ReceiveTimer;                      /* Receive Timer */
    uint32_t MAC_ReceivePacketNumber;               /* Receive Pack packet number */
    uint32_t MAC_ContinuousMode;                    /* Timer Continuous mode */
    uint32_t MAC_TimerValue;                        /* Timer value */

}MAC_InitTypeDef;

/*
 * @defgroup  MAC Transmit descriptor structure
 */
typedef struct
{
    uint32_t         descriptor_0;
    uint32_t         descriptor_1;
    const uint8_t*   buffer_1;
    uint32_t         buffer_2;
} mac_tx_descriptor_t;

/*
 * @defgroup  MAC Receive descriptor structure
 */
typedef struct
{
    uint32_t     descriptor_0;
    uint32_t     descriptor_1;
    uint8_t*     buffer_1;
    uint32_t     buffer_2;
} mac_rx_descriptor_t;

/*
 * @defgroup  Use by parameter examine
 */
#define IS_VALID_MAC_DESCRIPTOR_SKIP_LENGTH(value)  (((value)<=0x1FFU)&&((value)>=0U))
#define IS_VALID_MAC_TIMER_VALUE(value)             (((value)<=0xFFFFU)&&((value)>=0U))

/*
 * @defgroup  MAC Transmit auto poll interval
 */
#define MAC_AutoPollInterval_Disable                (uint32_t)0x00000000     /* TAB disabled */
#define MAC_AutoPollInterval_1                      (uint32_t)0x00000001     /* 819us @10Mbps / 81.9us @100Mbps */
#define MAC_AutoPollInterval_2                      (uint32_t)0x00000002     /* 2450us @10Mbps / 24.5us @100Mbps */
#define MAC_AutoPollInterval_3                      (uint32_t)0x00000003     /* 5730us @10Mbps / 57.3us @100Mbps */
#define MAC_AutoPollInterval_4                      (uint32_t)0x00000004     /* 51.2us @10Mbps / 5.12us @100Mbps */
#define MAC_AutoPollInterval_5                      (uint32_t)0x00000005     /* 102.4us @10Mbps / 10.24us @100Mbps */
#define MAC_AutoPollInterval_6                      (uint32_t)0x00000006     /* 153.6us @10Mbps / 15.36us @100Mbps */
#define MAC_AutoPollInterval_7                      (uint32_t)0x00000007     /* 358.4us @10Mbps / 35.84us @100Mbps */

#define IS_VALID_MAC_AutoPollInterval(value)    (((value) == MAC_AutoPollInterval_DISABLE) || \
                                                 ((value) == MAC_AutoPollInterval_1) || \
                                                 ((value) == MAC_AutoPollInterval_2) || \
                                                 ((value) == MAC_AutoPollInterval_3) || \
                                                 ((value) == MAC_AutoPollInterval_4) || \
                                                 ((value) == MAC_AutoPollInterval_5) || \
                                                 ((value) == MAC_AutoPollInterval_6) || \
                                                 ((value) == MAC_AutoPollInterval_7))

/*
 * @defgroup  MAC Descriptor byte sort mode
 */
#define MAC_DescriptorEndianMode_Big                ((uint32_t)0x00000001)
#define MAC_DescriptorEndianMode_Little             ((uint32_t)0x00000000)

#define IS_VALID_MAC_DESCRIPTOR_BYTE_ENDIAN(value) (((value) == MAC_DescriptorEndianMode_Big) || \
                                                  ((value) == MAC_DescriptorEndianMode_Little))
                    

/*
 * @defgroup  MAC Programmable pulse length
 */
#define MAC_ProgrammablePulseLength_0               ((uint32_t)0x00000000)
#define MAC_ProgrammablePulseLength_1               ((uint32_t)0x00000001)
#define MAC_ProgrammablePulseLength_2               ((uint32_t)0x00000002)
#define MAC_ProgrammablePulseLength_4               ((uint32_t)0x00000004)
#define MAC_ProgrammablePulseLength_8               ((uint32_t)0x00000008)
#define MAC_ProgrammablePulseLength_16              ((uint32_t)0x00000010)
#define MAC_ProgrammablePulseLength_32              ((uint32_t)0x00000020)

#define IS_VALID_MAC_PROGRAMMABLE_PULSE_LENGTH(value) (((value) == MAC_ProgrammablePulseLength_0) || \
                                                      ((value) == MAC_ProgrammablePulseLength_1) || \
                                                      ((value) == MAC_ProgrammablePulseLength_2) || \
                                                      ((value) == MAC_ProgrammablePulseLength_4) || \
                                                      ((value) == MAC_ProgrammablePulseLength_8) || \
                                                      ((value) == MAC_ProgrammablePulseLength_16) || \
                                                      ((value) == MAC_ProgrammablePulseLength_32))

/*
 * @defgroup  MAC Data endian mode
 */
#define MAC_DataEndianMode_Big                      ((uint32_t)0x00000001)
#define MAC_DataEndianMode_Little                   ((uint32_t)0x00000000) 

#define IS_VALID_MAC_DATA_ENDIAN(value)          (((value) == MAC_DataEndianMode_Big) || \
                                                 ((value) == MAC_DataEndianMode_Little))

/*
 * @defgroup MAC Bus Arbitration scheme
 */
#define MAC_BuArbitrations_EqualPriority            ((uint32_t)0x00000001)
#define MAC_BusArbitration_Intelligent              ((uint32_t)0x00000000)

#define IS_VALID_MAC_BUS_ARBITRATION_SCHEME(value)   (((value) == MAC_BuArbitrations_EqualPriority) || \
                                                  ((value) == MAC_BusArbitration_Intelligent))

/*
 * @defgroup MAC Enable or Disable Receives all incoming frames
 */
#define MAC_ReceiveAll_Enable                       ((uint32_t)0x00000001)
#define MAC_ReceiveAll_Disable                      ((uint32_t)0x00000000)

#define IS_VALID_MAC_RECEIVE_ALL(value)            (((value) == MAC_ReceiveAll_Enable) || \
                                                  ((value) == MAC_ReceiveAll_Disable))

/*
 * @defgroup MAC Transmit Threshold Mode
 */
#define MAC_FIFOThreshold_100M                      ((uint32_t)0x00000001)
#define MAC_FIFOThreshold_10M                       ((uint32_t)0x00000000)

#define IS_VALID_MAC_FIFO_THRESHOLD_MODE(value)     (((value) == MAC_FIFOThreshold_100M) || \
                                                  ((value) == MAC_FIFOThreshold_10M))

/*
 * @defgroup MAC Enable or Disable Store and forward Mode
 */
#define MAC_StoreandForward_Enable                  ((uint32_t)0x00000001)
#define MAC_StoreandForward_Disable                 ((uint32_t)0x00000000)

#define IS_VALID_MAC_STORE_AND_FORWARD(value)       (((value) == MAC_StoreandForward_Enable) || \
                                                  ((value) == MAC_StoreandForward_Disable))

/*
 * @defgroup MAC Threshold Control Bits
 */
#define MAC_ThresholdControlBits_Enable             ((uint32_t)0x00000001)
#define MAC_ThresholdControlBits_Disable            ((uint32_t)0x00000000)

#define IS_VALID_MAC_THRESHOLD_CONTROL_BITS(value)  (((value) == MAC_ThresholdControlBits_Enable) || \
                                                  ((value) == MAC_ThresholdControlBits_Disable))

/*
 * @defgroup MAC Transmit Mode
 */
#define MAC_TransmitMode_HalfDuplex                 ((uint32_t)0x00000000)
#define MAC_TransmitMode_FullDuplex                 ((uint32_t)0x00000001)

#define IS_VALID_MAC_TRANSMIT_MODE(value)             (((value) == MAC_Mode_HalfDuplex) || \
                                                      ((value) == MAC_Mode_FullDuplex))

/*
 * @defgroup MAC Pass All Multicast
 */
#define MAC_PassAllMulticasts_Disable               ((uint32_t)0x00000000)
#define MAC_PassAllMulticasts_Enable                ((uint32_t)0x00000001)

#define IS_VALID_MAC_PASSALL_MULTICASTS(value)       (((value) == MAC_PassAllMulticasts_Disable) || \
                                                     ((value) == MAC_PassAllMulticasts_Enable))

/*
 * @defgroup MAC Promiscuous Mode
 */
#define MAC_PromiscuousMode_Disable                 ((uint32_t)0x00000000)
#define MAC_PromiscuousMode_Enable                  ((uint32_t)0x00000001)

#define IS_VALID_MAC_PROMISCUOUS_MODE(value)         (((value) == MAC_PromiscuousMode_Disable) || \
                                                     ((value) == MAC_PromiscuousMode_Enable))

/*
 * @defgroup MAC Pass Bad Frame
 */
#define MAC_PassBadFrame_Disable                    ((uint32_t)0x00000000)
#define MAC_PassBadFrame_Enable                     ((uint32_t)0x00000001)

#define IS_VALID_MAC_PASS_BAD_FRAME(value)            (((value) == MAC_PassBadFrame_Disable) || \
                                                     ((value) == MAC_PassBadFrame_Enable))

/*
 * @defgroup MAC Timer Work Mode
 */
#define MAC_TimerWorkMode_OneShot                   ((uint32_t)0x00000000)
#define MAC_TimerWorkMode_Continuous                ((uint32_t)0x00000001)

#define IS_VALID_MAC_TIMERWORK_MODE(value)           (((value) == MAC_TimerWorkMode_OneShot) || \
                                                     ((value) == MAC_TimerWorkMode_Continuous))

/*
 * @defgroup MAC receiving and transmitting process.
 */
#define MAC_PROCESS_RECEIVE                         ((uint32_t)0x000E0000)
#define MAC_PROCESS_TRANSMIT                        ((uint32_t)0x00700000)

#define IS_MAC_PROCESS(value)                       (((value) == MAC_PROCESS_RECEIVE) || \
                                                     ((value) == MAC_PROCESS_TRANSMIT))

#define MAC_IT_NIE                                  ((uint32_t)0x00010000)
#define MAC_IT_AIE                                  ((uint32_t)0x00008000)
#define MAC_IT_ERE                                  ((uint32_t)0x00004000)
#define MAC_IT_GTE                                  ((uint32_t)0x00000800)
#define MAC_IT_ETE                                  ((uint32_t)0x00000400)
#define MAC_IT_RSE                                  ((uint32_t)0x00000100)
#define MAC_IT_RUE                                  ((uint32_t)0x00000080)
#define MAC_IT_RIE                                  ((uint32_t)0x00000040)
#define MAC_IT_UNE                                  ((uint32_t)0x00000020)
#define MAC_IT_TUE                                  ((uint32_t)0x00000004)
#define MAC_IT_TSE                                  ((uint32_t)0x00000002)
#define MAC_IT_TIE                                  ((uint32_t)0x00000001)
#define IS_MAC_IT(value)                            (((value) == MAC_IT_NIE) || \
                                                     ((value) == MAC_IT_AIE) || \
                                                     ((value) == MAC_IT_ERE) || \
                                                     ((value) == MAC_IT_GTE) || \
                                                     ((value) == MAC_IT_ETE) || \
                                                     ((value) == MAC_IT_RSE) || \
                                                     ((value) == MAC_IT_RUE) || \
                                                     ((value) == MAC_IT_RIE) || \
                                                     ((value) == MAC_IT_UNE) || \
                                                     ((value) == MAC_IT_TUE) || \
                                                     ((value) == MAC_IT_TSE) || \
                                                     ((value) == MAC_IT_TIE))

#define MAC_Flag_NIS                                ((uint32_t)0x00010000)
#define MAC_Flag_AIS                                ((uint32_t)0x00008000)
#define MAC_Flag_ERI                                ((uint32_t)0x00004000)
#define MAC_Flag_GTE                                ((uint32_t)0x00000800)
#define MAC_Flag_ETI                                ((uint32_t)0x00000400)
#define MAC_Flag_RPS                                ((uint32_t)0x00000100)
#define MAC_Flag_RU                                 ((uint32_t)0x00000080)
#define MAC_Flag_RI                                 ((uint32_t)0x00000040)
#define MAC_Flag_UNF                                ((uint32_t)0x00000020)
#define MAC_Flag_TU                                 ((uint32_t)0x00000004)
#define MAC_Flag_TPS                                ((uint32_t)0x00000002)
#define MAC_Flag_TI                                 ((uint32_t)0x00000001)
#define IS_MAC_FLAG(value)                         (((value) == MAC_Flag_NIS) || \
                                                    ((value) == MAC_Flag_AIS) || \
                                                    ((value) == MAC_Flag_ERI) || \
                                                    ((value) == MAC_Flag_GTE) || \
                                                    ((value) == MAC_Flag_ETI) || \
                                                    ((value) == MAC_Flag_RPS) || \
                                                    ((value) == MAC_Flag_RU)  || \
                                                    ((value) == MAC_Flag_RI)  || \
                                                    ((value) == MAC_Flag_UNF) || \
                                                    ((value) == MAC_Flag_TU)  || \
                                                    ((value) == MAC_Flag_TPS) || \
                                                    ((value) == MAC_Flag_TI))

#define MAC_IT_NIS                                ((uint32_t)0x00010000)
#define MAC_IT_AIS                                ((uint32_t)0x00008000)
#define MAC_IT_ERI                                ((uint32_t)0x00004000)
#define MAC_IT_GTE                                ((uint32_t)0x00000800)
#define MAC_IT_ETI                                ((uint32_t)0x00000400)
#define MAC_IT_RPS                                ((uint32_t)0x00000100)
#define MAC_IT_RU                                 ((uint32_t)0x00000080)
#define MAC_IT_RI                                 ((uint32_t)0x00000040)
#define MAC_IT_UNF                                ((uint32_t)0x00000020)
#define MAC_IT_TU                                 ((uint32_t)0x00000004)
#define MAC_IT_TPS                                ((uint32_t)0x00000002)
#define MAC_IT_TI                                 ((uint32_t)0x00000001)
#define IS_MAC_ClearIT(value)                          (((value) == MAC_IT_NIS) || \
                                                    ((value) == MAC_IT_AIS) || \
                                                    ((value) == MAC_IT_ERI) || \
                                                    ((value) == MAC_IT_GTE) || \
                                                    ((value) == MAC_IT_ETI) || \
                                                    ((value) == MAC_IT_RPS) || \
                                                    ((value) == MAC_IT_RU)  || \
                                                    ((value) == MAC_IT_RI)  || \
                                                    ((value) == MAC_IT_UNF) || \
                                                    ((value) == MAC_IT_TU)  || \
                                                    ((value) == MAC_IT_TPS) || \
                                                    ((value) == MAC_IT_TI))

/*
 * @defgroup Ownership bit.
 */
#define TDES0_OWN     ((uint32_t)0x80000000U)

/*
 * @defgroup error summary.
 */
#define TDES0_ES     ((uint32_t)(1U << 15U))

/*
 * @defgroup Lost carrier.
 */
#define TDES0_LO     ((uint32_t)(1U << 11U))

/*
 * @defgroup No carrier.
 */
#define TDES0_NC     ((uint32_t)(1U << 10U))

/*
 * @defgroup Delayed conflict.
 */
#define TDES0_LC     ((uint32_t)(1U << 9U))

/*
 * @defgroup Excessive collision.
 */
#define TDES0_EC     ((uint32_t)(1U << 8U))

/*
 * @defgroup Update collision count.
 */
#define TDES0_CC_MASK       0xFU
#define TDES0_CC_OFFSET     3U

/*
 * @defgroup Underflow error.
 */
#define TDES0_UF     ((uint32_t)(1U << 1U))

/*
 * @defgroup Delayed.
 */
#define TDES0_DE      ((uint32_t)(1U))

/*
 * @defgroup Interrupt on completion.
 */
#define TDES1_IC      ((uint32_t)(1U << 31U))

/*
 * @defgroup Last descriptor.
 */
#define TDES1_LS      ((uint32_t)(1U << 30U))

/*
 * @defgroup First descriptor
 */
#define TDES1_FS      ((uint32_t)(1U << 29U))

/*
 * @defgroup Filter type
 */
#define TDES1_FT1     ((uint32_t)(1U << 28U))

/*
 * @defgroup Setup packet
 */
#define TDES1_SET     ((uint32_t)(1U << 27U))

/*
 * @defgroup Add CRC disable
 */
#define TDES1_AC      ((uint32_t)(1U << 26U))

/*
 * @defgroup Transmit end of ring
 */
#define TDES1_TER     ((uint32_t)(1U << 25U))

/*
 * @defgroup Second address link.
 */
#define TDES1_TCH     ((uint32_t)(1U << 24U))

/*
 * @defgroup Disable fill.
 */
#define TDES1_DPD     ((uint32_t)(1U << 23U))

/*
 * @defgroup Filter type.
 */
#define TDES1_FT0     ((uint32_t)(1U << 22U))



/*
 * @defgroup Ownership bit
 */
#define RDES0_OWN   ((uint32_t)0x80000000U)

/*
 * @defgroup Filtering Fail
 */
#define RDES0_FF    ((uint32_t)0x40000000U)


/*
 * @defgroup Frame Length
 */
#define RDES0_FL_MASK       ((uint32_t)0x00003FFFU)
#define RDES0_FL_OFFSET     16U


/*
 * @defgroup Error Summary
 */
#define RDES0_ES    ((uint32_t)0x00008000U)

/*
 * @defgroup Descriptor Error
 */
#define RDES0_DE    ((uint32_t)0x00004000U)

/*
 * @defgroup Runt Frame
 */
#define RDES0_RF    ((uint32_t)0x00000800U)

/*
 * @defgroup Multicast Frame
 */
#define RDES0_MF    ((uint32_t)0x00000400U)

/*
 * @defgroup First Descriptor
 */
#define RDES0_FS    ((uint32_t)0x00000200U)

/*
 * @defgroup Last Descriptor
 */
#define RDES0_LS    ((uint32_t)0x00000100U)

/*
 * @defgroup Frame Too Long
 */
#define RDES0_TL    ((uint32_t)0x00000080U)

/*
 * @defgroup Collision Seen
 */
#define RDES0_CS    ((uint32_t)0x00000040U)

/*
 * @defgroup Frame Type
 */
#define RDES0_FT    ((uint32_t)0x00000020U)

/*
 * @defgroup MII Error Report
 */
#define RDES0_RE    ((uint32_t)0x00000008U)

/*
 * @defgroup Dribbling Bit
 */
#define RDES0_DB    ((uint32_t)0x00000004U)

/*
 * @defgroup CRC Error
 */
#define RDES0_CE    ((uint32_t)0x00000002U)

/*
 * @defgroup Valid Frame Length
 */
#define RDES0_ZERO  ((uint32_t)0x00000001U)

/*
 * @defgroup Receive End of Ring
 */
#define RDES1_RER   ((uint32_t)0x02000000U)

/*
 * @defgroup Second Address Chained
 */
#define RDES1_RCH   ((uint32_t)0x01000000U)

/*
 * @defgroup Buffer2 Size
 */
#define RDES1_RBS2_MASK         0x7FFU
#define RDES1_RBS2_OFFSET       11U

/*
 * @defgroup Buffer1 Size
 */
#define RDES1_RBS1_MASK         0x7FFU
#define RDES1_RBS1_OFFSET       0U


/*
 * @brief Function declaration
 */
void MAC_DeInit(void);
void MAC_StructInit(MAC_InitTypeDef * MAC_InitStruct);
void MAC_Init(MAC_InitTypeDef * MAC_InitStruct);
void MAC_SoftwareReset(void);
void MAC_ReceiveDescriptorAddress(uint32_t Addr);
void MAC_TransmitDescriptorAddress(uint32_t Addr);
void MAC_ReceiveCmd(FunctionalState NewState);
void MAC_TransmitCmd(FunctionalState NewState);
uint8_t MAC_GetProcessStatus(uint32_t Process);
void MAC_ITConfig(uint32_t MAC_IT, FunctionalState NewState);
FlagStatus MAC_GetFlagStatus(uint32_t MAC_FLAG);
void MAC_MDIOClockCmd(FunctionalState NewState);
void MAC_SetPrescaler(uint16_t MAC_Prescaler);
ErrorStatus MAC_MDIOWriteData(uint32_t PHY_ADDR,uint32_t REG_ADDR,uint32_t Data,uint32_t timeout);
int MAC_MDIOReadData(uint8_t PHY_ADDR, uint8_t REG_ADDR,uint32_t timeout);
ErrorStatus MAC_TransmitPack(uint32_t Frame_length,mac_tx_descriptor_t * P_tx_desc);
ErrorStatus MAC_ReceivePack( uint8_t* rx_buffer, uint32_t *len,mac_rx_descriptor_t * P_rx_desc);
void MAC_ClearITStatus(uint32_t MAC_IT);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/