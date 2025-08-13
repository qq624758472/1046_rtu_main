/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	  as32x601_mpu.h
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			      2024/08/01
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/13     1.0     build this module
 * Description:     This file contains all the functions prototypes for the MPU configuration.
 */

#ifndef AS32X601_MPU_H
#define AS32X601_MPU_H

#include "as32x601_mpu_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @defgroup  Use by parameter examine
 */

#define IS_MPU_ALL_TypeDef(MPU)  (((MPU)==(void*)MPU0_IBUS) || \
                              ((MPU)==(void*)MPU1_DBUS) || \
                              ((MPU)==(void*)MPU2_PBUS) || \
                              ((MPU)==(void*)MPU3_DMA0) || \
                              ((MPU)==(void*)MPU4_DMA1))

#define IS_MPU_LIST1_TypeDef(MPU) \
                              (((MPU)==(void*)MPU1_DBUS) || \
                              ((MPU)==(void*)MPU2_PBUS) || \
                              ((MPU)==(void*)MPU3_DMA0) || \
                              ((MPU)==(void*)MPU4_DMA1))

#define IS_MPU_ALL_PERIPH(MPUy_Channelx) (((MPUy_Channelx) == MPU0_Channel0)  || \
                                          ((MPUy_Channelx) == MPU0_Channel1)  || \
                                          ((MPUy_Channelx) == MPU0_Channel2)  || \
                                          ((MPUy_Channelx) == MPU0_Channel3)  || \
                                          ((MPUy_Channelx) == MPU0_Channel4)  || \
                                          ((MPUy_Channelx) == MPU0_Channel5)  || \
                                          ((MPUy_Channelx) == MPU0_Channel6)  || \
                                          ((MPUy_Channelx) == MPU0_Channel7)  || \
                                          ((MPUy_Channelx) == MPU0_Channel8)  || \
                                          ((MPUy_Channelx) == MPU0_Channel9)  || \
                                          ((MPUy_Channelx) == MPU0_Channel10) || \
                                          ((MPUy_Channelx) == MPU0_Channel11) || \
                                          ((MPUy_Channelx) == MPU0_Channel12) || \
                                          ((MPUy_Channelx) == MPU0_Channel13) || \
                                          ((MPUy_Channelx) == MPU0_Channel14) || \
                                          ((MPUy_Channelx) == MPU0_Channel15) || \
                                          ((MPUy_Channelx) == MPU1_Channel0)  || \
                                          ((MPUy_Channelx) == MPU1_Channel1)  || \
                                          ((MPUy_Channelx) == MPU1_Channel2)  || \
                                          ((MPUy_Channelx) == MPU1_Channel3)  || \
                                          ((MPUy_Channelx) == MPU1_Channel4)  || \
                                          ((MPUy_Channelx) == MPU1_Channel5)  || \
                                          ((MPUy_Channelx) == MPU1_Channel6)  || \
                                          ((MPUy_Channelx) == MPU1_Channel7)  || \
                                          ((MPUy_Channelx) == MPU1_Channel8)  || \
                                          ((MPUy_Channelx) == MPU1_Channel9)  || \
                                          ((MPUy_Channelx) == MPU1_Channel10) || \
                                          ((MPUy_Channelx) == MPU1_Channel11) || \
                                          ((MPUy_Channelx) == MPU1_Channel12) || \
                                          ((MPUy_Channelx) == MPU1_Channel13) || \
                                          ((MPUy_Channelx) == MPU1_Channel14) || \
                                          ((MPUy_Channelx) == MPU1_Channel15) || \
                                          ((MPUy_Channelx) == MPU2_Channel0)  || \
                                          ((MPUy_Channelx) == MPU2_Channel1)  || \
                                          ((MPUy_Channelx) == MPU2_Channel2)  || \
                                          ((MPUy_Channelx) == MPU2_Channel3)  || \
                                          ((MPUy_Channelx) == MPU2_Channel4)  || \
                                          ((MPUy_Channelx) == MPU2_Channel5)  || \
                                          ((MPUy_Channelx) == MPU2_Channel6)  || \
                                          ((MPUy_Channelx) == MPU2_Channel7)  || \
                                          ((MPUy_Channelx) == MPU2_Channel8)  || \
                                          ((MPUy_Channelx) == MPU2_Channel9)  || \
                                          ((MPUy_Channelx) == MPU2_Channel10) || \
                                          ((MPUy_Channelx) == MPU2_Channel11) || \
                                          ((MPUy_Channelx) == MPU2_Channel12) || \
                                          ((MPUy_Channelx) == MPU2_Channel13) || \
                                          ((MPUy_Channelx) == MPU2_Channel14) || \
                                          ((MPUy_Channelx) == MPU2_Channel15) || \
                                          ((MPUy_Channelx) == MPU3_Channel0)  || \
                                          ((MPUy_Channelx) == MPU3_Channel1)  || \
                                          ((MPUy_Channelx) == MPU3_Channel2)  || \
                                          ((MPUy_Channelx) == MPU3_Channel3)  || \
                                          ((MPUy_Channelx) == MPU3_Channel4)  || \
                                          ((MPUy_Channelx) == MPU3_Channel5)  || \
                                          ((MPUy_Channelx) == MPU3_Channel6)  || \
                                          ((MPUy_Channelx) == MPU3_Channel7)  || \
                                          ((MPUy_Channelx) == MPU4_Channel0)  || \
                                          ((MPUy_Channelx) == MPU4_Channel1)  || \
                                          ((MPUy_Channelx) == MPU4_Channel2)  || \
                                          ((MPUy_Channelx) == MPU4_Channel3)  || \
                                          ((MPUy_Channelx) == MPU4_Channel4)  || \
                                          ((MPUy_Channelx) == MPU4_Channel5)  || \
                                          ((MPUy_Channelx) == MPU4_Channel6)  || \
                                          ((MPUy_Channelx) == MPU4_Channel7))

#define IS_MPU_LIST1_PERIPH(MPUy_Channelx) \
                                          (((MPUy_Channelx) == MPU1_Channel0)  || \
                                          ((MPUy_Channelx) == MPU1_Channel1)  || \
                                          ((MPUy_Channelx) == MPU1_Channel2)  || \
                                          ((MPUy_Channelx) == MPU1_Channel3)  || \
                                          ((MPUy_Channelx) == MPU1_Channel4)  || \
                                          ((MPUy_Channelx) == MPU1_Channel5)  || \
                                          ((MPUy_Channelx) == MPU1_Channel6)  || \
                                          ((MPUy_Channelx) == MPU1_Channel7)  || \
                                          ((MPUy_Channelx) == MPU1_Channel8)  || \
                                          ((MPUy_Channelx) == MPU1_Channel9)  || \
                                          ((MPUy_Channelx) == MPU1_Channel10) || \
                                          ((MPUy_Channelx) == MPU1_Channel11) || \
                                          ((MPUy_Channelx) == MPU1_Channel12) || \
                                          ((MPUy_Channelx) == MPU1_Channel13) || \
                                          ((MPUy_Channelx) == MPU1_Channel14) || \
                                          ((MPUy_Channelx) == MPU1_Channel15) || \
                                          ((MPUy_Channelx) == MPU2_Channel0)  || \
                                          ((MPUy_Channelx) == MPU2_Channel1)  || \
                                          ((MPUy_Channelx) == MPU2_Channel2)  || \
                                          ((MPUy_Channelx) == MPU2_Channel3)  || \
                                          ((MPUy_Channelx) == MPU2_Channel4)  || \
                                          ((MPUy_Channelx) == MPU2_Channel5)  || \
                                          ((MPUy_Channelx) == MPU2_Channel6)  || \
                                          ((MPUy_Channelx) == MPU2_Channel7)  || \
                                          ((MPUy_Channelx) == MPU2_Channel8)  || \
                                          ((MPUy_Channelx) == MPU2_Channel9)  || \
                                          ((MPUy_Channelx) == MPU2_Channel10) || \
                                          ((MPUy_Channelx) == MPU2_Channel11) || \
                                          ((MPUy_Channelx) == MPU2_Channel12) || \
                                          ((MPUy_Channelx) == MPU2_Channel13) || \
                                          ((MPUy_Channelx) == MPU2_Channel14) || \
                                          ((MPUy_Channelx) == MPU2_Channel15) || \
                                          ((MPUy_Channelx) == MPU3_Channel0)  || \
                                          ((MPUy_Channelx) == MPU3_Channel1)  || \
                                          ((MPUy_Channelx) == MPU3_Channel2)  || \
                                          ((MPUy_Channelx) == MPU3_Channel3)  || \
                                          ((MPUy_Channelx) == MPU3_Channel4)  || \
                                          ((MPUy_Channelx) == MPU3_Channel5)  || \
                                          ((MPUy_Channelx) == MPU3_Channel6)  || \
                                          ((MPUy_Channelx) == MPU3_Channel7)  || \
                                          ((MPUy_Channelx) == MPU4_Channel0)  || \
                                          ((MPUy_Channelx) == MPU4_Channel1)  || \
                                          ((MPUy_Channelx) == MPU4_Channel2)  || \
                                          ((MPUy_Channelx) == MPU4_Channel3)  || \
                                          ((MPUy_Channelx) == MPU4_Channel4)  || \
                                          ((MPUy_Channelx) == MPU4_Channel5)  || \
                                          ((MPUy_Channelx) == MPU4_Channel6)  || \
                                          ((MPUy_Channelx) == MPU4_Channel7))


/*
* @defgroup  MPU flags definition
*/
#define  MPU_FLAG_WPTS0              ((uint32_t)0x10000001)
#define  MPU_FLAG_WPTS1              ((uint32_t)0x10000002)
#define  MPU_FLAG_WPTS2              ((uint32_t)0x10000004)
#define  MPU_FLAG_WPTS3              ((uint32_t)0x10000008)
#define  MPU_FLAG_WPTS4              ((uint32_t)0x10000010)
#define  MPU_FLAG_WPTS5              ((uint32_t)0x10000020)
#define  MPU_FLAG_WPTS6              ((uint32_t)0x10000040)
#define  MPU_FLAG_WPTS7              ((uint32_t)0x10000080)
#define  MPU_FLAG_WPTS8              ((uint32_t)0x10000100)
#define  MPU_FLAG_WPTS9              ((uint32_t)0x10000200)
#define  MPU_FLAG_WPTS10             ((uint32_t)0x10000400)
#define  MPU_FLAG_WPTS11             ((uint32_t)0x10000800)
#define  MPU_FLAG_WPTS12             ((uint32_t)0x10001000)
#define  MPU_FLAG_WPTS13             ((uint32_t)0x10002000)
#define  MPU_FLAG_WPTS14             ((uint32_t)0x10004000)
#define  MPU_FLAG_WPTS15             ((uint32_t)0x10008000)

#define  MPU_FLAG_RPTS0              ((uint32_t)0x20000001)
#define  MPU_FLAG_RPTS1              ((uint32_t)0x20000002)
#define  MPU_FLAG_RPTS2              ((uint32_t)0x20000004)
#define  MPU_FLAG_RPTS3              ((uint32_t)0x20000008)
#define  MPU_FLAG_RPTS4              ((uint32_t)0x20000010)
#define  MPU_FLAG_RPTS5              ((uint32_t)0x20000020)
#define  MPU_FLAG_RPTS6              ((uint32_t)0x20000040)
#define  MPU_FLAG_RPTS7              ((uint32_t)0x20000080)
#define  MPU_FLAG_RPTS8              ((uint32_t)0x20000100)
#define  MPU_FLAG_RPTS9              ((uint32_t)0x20000200)
#define  MPU_FLAG_RPTS10             ((uint32_t)0x20000400)
#define  MPU_FLAG_RPTS11             ((uint32_t)0x20000800)
#define  MPU_FLAG_RPTS12             ((uint32_t)0x20001000)
#define  MPU_FLAG_RPTS13             ((uint32_t)0x20002000)
#define  MPU_FLAG_RPTS14             ((uint32_t)0x20004000)
#define  MPU_FLAG_RPTS15             ((uint32_t)0x20008000)

#define IS_MPU_FLAG(FLAG) \
    (((FLAG) == MPU_FLAG_WPTS0)  || ((FLAG) == MPU_FLAG_WPTS1)  || \
     ((FLAG) == MPU_FLAG_WPTS2)  || ((FLAG) == MPU_FLAG_WPTS3)  || \
     ((FLAG) == MPU_FLAG_WPTS4)  || ((FLAG) == MPU_FLAG_WPTS5)  || \
     ((FLAG) == MPU_FLAG_WPTS6)  || ((FLAG) == MPU_FLAG_WPTS7)  || \
     ((FLAG) == MPU_FLAG_WPTS8)  || ((FLAG) == MPU_FLAG_WPTS9)  || \
     ((FLAG) == MPU_FLAG_WPTS10) || ((FLAG) == MPU_FLAG_WPTS11) || \
     ((FLAG) == MPU_FLAG_WPTS12) || ((FLAG) == MPU_FLAG_WPTS13) || \
     ((FLAG) == MPU_FLAG_WPTS14) || ((FLAG) == MPU_FLAG_WPTS15) || \
     ((FLAG) == MPU_FLAG_RPTS0)  || ((FLAG) == MPU_FLAG_RPTS1)  || \
     ((FLAG) == MPU_FLAG_RPTS2)  || ((FLAG) == MPU_FLAG_RPTS3)  || \
     ((FLAG) == MPU_FLAG_RPTS4)  || ((FLAG) == MPU_FLAG_RPTS5)  || \
     ((FLAG) == MPU_FLAG_RPTS6)  || ((FLAG) == MPU_FLAG_RPTS7)  || \
     ((FLAG) == MPU_FLAG_RPTS8)  || ((FLAG) == MPU_FLAG_RPTS9)  || \
     ((FLAG) == MPU_FLAG_RPTS10) || ((FLAG) == MPU_FLAG_RPTS11) || \
     ((FLAG) == MPU_FLAG_RPTS12) || ((FLAG) == MPU_FLAG_RPTS13) || \
     ((FLAG) == MPU_FLAG_RPTS14) || ((FLAG) == MPU_FLAG_RPTS15))

#define IS_MPU_DMA_FLAG(FLAG) \
    (((FLAG) == MPU_FLAG_WPTS0)  || ((FLAG) == MPU_FLAG_WPTS1)  || \
     ((FLAG) == MPU_FLAG_WPTS2)  || ((FLAG) == MPU_FLAG_WPTS3)  || \
     ((FLAG) == MPU_FLAG_WPTS4)  || ((FLAG) == MPU_FLAG_WPTS5)  || \
     ((FLAG) == MPU_FLAG_WPTS6)  || ((FLAG) == MPU_FLAG_WPTS7)  || \
     ((FLAG) == MPU_FLAG_RPTS0)  || ((FLAG) == MPU_FLAG_RPTS1)  || \
     ((FLAG) == MPU_FLAG_RPTS2)  || ((FLAG) == MPU_FLAG_RPTS3)  || \
     ((FLAG) == MPU_FLAG_RPTS4)  || ((FLAG) == MPU_FLAG_RPTS5)  || \
     ((FLAG) == MPU_FLAG_RPTS6)  || ((FLAG) == MPU_FLAG_RPTS7))


/*
 * @brief Function declaration
 */
void MPU_SetAddressRange(MPU_Channel_TypeDef * MPUy_Channelx,uint32_t SADDR,uint32_t EADDR);
void MPU_Cmd(MPU_Channel_TypeDef * MPUy_Channelx,FunctionalState NewState);
void MPU_WriteProtectCmd(MPU_Channel_TypeDef * MPUy_Channelx,FunctionalState NewState);
void MPU_ReadProtectCmd(MPU_Channel_TypeDef * MPUy_Channelx,FunctionalState NewState);
FlagStatus MPU_GetFlagStatus(void * MPUy,uint32_t MPU_FLAG);
void MPU_ClearFlag(void * MPUy,uint32_t MPU_FLAG);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/