                    /*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C): Xiamen Guoke Anxin Technology Co., LTD
 * FileName     : as32x601_dma.h
 * Author       : ANSILIC APPLICATION GROUP
 * Version      : V1.0
 * Date         : 2024/07/23
 * History      : 
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/07/23     1.0     build this module
 * Description:     This file contains all the functions prototypes for the DMA firmware library.
 */

#ifndef AS32X601_DMA_H
#define AS32X601_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "as32x601_dma_regs.h"


/*
 * @brief  DMA Init structure definition
*/
typedef struct
{
  uint32_t DMA_PeripheralBaseAddr; /* Specifies the peripheral base address for DMAy Channelx. */

  uint32_t DMA_MemoryBaseAddr;     /* Specifies the memory base address for DMAy Channelx. */

  uint32_t DMA_DIR;                /* Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction */

  uint32_t DMA_BufferSize;         /* Specifies the buffer size, in data unit, of the specified Channel. 
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction. */

  uint32_t DMA_PeripheralInc;      /* Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */

  uint32_t DMA_MemoryInc;          /* Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode */

  uint32_t DMA_PeripheralDataSize; /* Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_peripheral_data_size */

  uint32_t DMA_MemoryDataSize;     /* Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_memory_data_size */

  uint32_t DMA_Mode;               /* Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_circular_normal_mode.
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */

  uint32_t DMA_Priority;           /* Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level */

  uint32_t DMA_M2M;                /* Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                        This parameter can be a value of @ref DMA_memory_to_memory */
}DMA_InitTypeDef;

/*
 * @brief  Use by parameter examine
*/

#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA0_Channel1)  || \
                                   ((PERIPH) == DMA0_Channel2)  || \
                                   ((PERIPH) == DMA0_Channel3)  || \
                                   ((PERIPH) == DMA0_Channel4)  || \
                                   ((PERIPH) == DMA0_Channel5)  || \
                                   ((PERIPH) == DMA0_Channel6)  || \
                                   ((PERIPH) == DMA0_Channel7)  || \
                                   ((PERIPH) == DMA0_Channel8)  || \
                                   ((PERIPH) == DMA0_Channel9)  || \
                                   ((PERIPH) == DMA0_Channel10) || \
                                   ((PERIPH) == DMA0_Channel11) || \
                                   ((PERIPH) == DMA0_Channel12) || \
                                   ((PERIPH) == DMA0_Channel13) || \
                                   ((PERIPH) == DMA0_Channel14) || \
                                   ((PERIPH) == DMA0_Channel15) || \
                                   ((PERIPH) == DMA1_Channel1)  || \
                                   ((PERIPH) == DMA1_Channel2)  || \
                                   ((PERIPH) == DMA1_Channel3)  || \
                                   ((PERIPH) == DMA1_Channel4)  || \
                                   ((PERIPH) == DMA1_Channel5)  || \
                                   ((PERIPH) == DMA1_Channel6)  || \
                                   ((PERIPH) == DMA1_Channel7)  || \
                                   ((PERIPH) == DMA1_Channel8)  || \
                                   ((PERIPH) == DMA1_Channel9)  || \
                                   ((PERIPH) == DMA1_Channel10) || \
                                   ((PERIPH) == DMA1_Channel11) || \
                                   ((PERIPH) == DMA1_Channel12) || \
                                   ((PERIPH) == DMA1_Channel13) || \
                                   ((PERIPH) == DMA1_Channel14) || \
                                   ((PERIPH) == DMA1_Channel15))

#define IS_DMA_TypeDef(DMA)  (((DMA)==DMA0) || ((DMA)==DMA1))

#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0) && ((COUNTER) <= 0xffff))

/*
 * @defgroup  DMA memory to memory 
*/
#define DMA_M2M_Enable                     ((uint32_t)0x00000001)
#define DMA_M2M_Disable                    ((uint32_t)0x00000000)
#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Enable) || ((STATE) == DMA_M2M_Disable))

/*
 * @defgroup  DMA data transfer definition
*/
#define DMA_DIR_PeripheralDST              ((uint32_t)0x00000002)
#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)
#define IS_DMA_DIR(DIR)                    (((DIR) == DMA_DIR_PeripheralDST) || \
                                            ((DIR) == DMA_DIR_PeripheralSRC))

/*
 * @defgroup  DMA circular or normal mode
*/
#define DMA_Mode_Circular                  ((uint32_t)0x00000004)
#define DMA_Mode_Normal                    ((uint32_t)0x00000000)
#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Circular) || ((MODE) == DMA_Mode_Normal))

/*
 * @defgroup  DMA peripheral incremented mode
*/
#define DMA_PeripheralInc_Enable           ((uint32_t)0x00000008)
#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)
#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Enable) || \
                                            ((STATE) == DMA_PeripheralInc_Disable))


/*
 * @defgroup  DMA memory incremented mode
*/
#define DMA_MemoryInc_Enable               ((uint32_t)0x00000010)
#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)
#define IS_DMA_MEMORY_INC_STATE(STATE)     (((STATE) == DMA_MemoryInc_Enable) || \
                                           ((STATE) == DMA_MemoryInc_Disable))

/*
 * @defgroup  DMA peripheral data size
*/
#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord    ((uint32_t)0x00000020)
#define DMA_PeripheralDataSize_Word        ((uint32_t)0x00000040)
#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE)  (((SIZE) == DMA_PeripheralDataSize_Byte) || \
                                            ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
                                            ((SIZE) == DMA_PeripheralDataSize_Word))

/*
 * @defgroup  DMA memory data size
*/
#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord        ((uint32_t)0x00000080)
#define DMA_MemoryDataSize_Word            ((uint32_t)0x00000100)
#define IS_DMA_MEMORY_DATA_SIZE(SIZE)      (((SIZE) == DMA_MemoryDataSize_Byte) || \
                                            ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                            ((SIZE) == DMA_MemoryDataSize_Word))

/*
 * @defgroup  DMA priority level
*/
#define DMA_Priority_VeryHigh              ((uint32_t)0x00000600)
#define DMA_Priority_High                  ((uint32_t)0x00000400)
#define DMA_Priority_Medium                ((uint32_t)0x00000200)
#define DMA_Priority_Low                   ((uint32_t)0x00000000)
#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
                                   ((PRIORITY) == DMA_Priority_High) || \
                                   ((PRIORITY) == DMA_Priority_Medium) || \
                                   ((PRIORITY) == DMA_Priority_Low))

/*
* @defgroup  DMA Buffer size
*/
#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))

/*
* @defgroup  DMAy flags definition
*/
#define  DMA_FLAG_ERR0              ((uint32_t)0x10000001)
#define  DMA_FLAG_ERR1              ((uint32_t)0x10000002)
#define  DMA_FLAG_ERR2              ((uint32_t)0x10000004)
#define  DMA_FLAG_ERR3              ((uint32_t)0x10000008)
#define  DMA_FLAG_ERR4              ((uint32_t)0x10000010)
#define  DMA_FLAG_ERR5              ((uint32_t)0x10000020)
#define  DMA_FLAG_ERR6              ((uint32_t)0x10000040)
#define  DMA_FLAG_ERR7              ((uint32_t)0x10000080)
#define  DMA_FLAG_ERR8              ((uint32_t)0x10000100)
#define  DMA_FLAG_ERR9              ((uint32_t)0x10000200)
#define  DMA_FLAG_ERR10             ((uint32_t)0x10000400)
#define  DMA_FLAG_ERR11             ((uint32_t)0x10000800)
#define  DMA_FLAG_ERR12             ((uint32_t)0x10001000)
#define  DMA_FLAG_ERR13             ((uint32_t)0x10002000)
#define  DMA_FLAG_ERR14             ((uint32_t)0x10004000)
#define  DMA_FLAG_ERR15             ((uint32_t)0x10008000)

#define  DMA_FLAG_FTF0              ((uint32_t)0x20000001)
#define  DMA_FLAG_FTF1              ((uint32_t)0x20000002)
#define  DMA_FLAG_FTF2              ((uint32_t)0x20000004)
#define  DMA_FLAG_FTF3              ((uint32_t)0x20000008)
#define  DMA_FLAG_FTF4              ((uint32_t)0x20000010)
#define  DMA_FLAG_FTF5              ((uint32_t)0x20000020)
#define  DMA_FLAG_FTF6              ((uint32_t)0x20000040)
#define  DMA_FLAG_FTF7              ((uint32_t)0x20000080)
#define  DMA_FLAG_FTF8              ((uint32_t)0x20000100)
#define  DMA_FLAG_FTF9              ((uint32_t)0x20000200)
#define  DMA_FLAG_FTF10             ((uint32_t)0x20000400)
#define  DMA_FLAG_FTF11             ((uint32_t)0x20000800)
#define  DMA_FLAG_FTF12             ((uint32_t)0x20001000)
#define  DMA_FLAG_FTF13             ((uint32_t)0x20002000)
#define  DMA_FLAG_FTF14             ((uint32_t)0x20004000)
#define  DMA_FLAG_FTF15             ((uint32_t)0x20008000)

#define  DMA_FLAG_HTF0              ((uint32_t)0x40000001)
#define  DMA_FLAG_HTF1              ((uint32_t)0x40000002)
#define  DMA_FLAG_HTF2              ((uint32_t)0x40000004)
#define  DMA_FLAG_HTF3              ((uint32_t)0x40000008)
#define  DMA_FLAG_HTF4              ((uint32_t)0x40000010)
#define  DMA_FLAG_HTF5              ((uint32_t)0x40000020)
#define  DMA_FLAG_HTF6              ((uint32_t)0x40000040)
#define  DMA_FLAG_HTF7              ((uint32_t)0x40000080)
#define  DMA_FLAG_HTF8              ((uint32_t)0x40000100)
#define  DMA_FLAG_HTF9              ((uint32_t)0x40000200)
#define  DMA_FLAG_HTF10             ((uint32_t)0x40000400)
#define  DMA_FLAG_HTF11             ((uint32_t)0x40000800)
#define  DMA_FLAG_HTF12             ((uint32_t)0x40001000)
#define  DMA_FLAG_HTF13             ((uint32_t)0x40002000)
#define  DMA_FLAG_HTF14             ((uint32_t)0x40004000)
#define  DMA_FLAG_HTF15             ((uint32_t)0x40008000)

#define  DMA_FLAG_WDG               ((uint32_t)0x80000001)               

#define IS_DMA_CLEAR_FLAG(FLAG) (((((FLAG) & 0xEFFF0000) == 0x00) || (((FLAG) & 0xDFFF0000) == 0x00) ||(((FLAG) & 0xBFFF0000) == 0x00)||(((FLAG) & 0x7FFF0000) == 0x00) ) && ((FLAG) != 0x00)) 
#define IS_DMA_FLAG(FLAG) (((FLAG) ==DMA_FLAG_ERR0)   || ((FLAG) ==DMA_FLAG_ERR1)  \
                           ((FLAG) ==DMA_FLAG_ERR2)   || ((FLAG) ==DMA_FLAG_ERR3)  \
                           ((FLAG) ==DMA_FLAG_ERR4)   || ((FLAG) ==DMA_FLAG_ERR5)  \
                           ((FLAG) ==DMA_FLAG_ERR6)   || ((FLAG) ==DMA_FLAG_ERR7)  \
                           ((FLAG) ==DMA_FLAG_ERR8)   || ((FLAG) ==DMA_FLAG_ERR9)  \
                           ((FLAG) ==DMA_FLAG_ERR10)  || ((FLAG) ==DMA_FLAG_ERR11) \
                           ((FLAG) ==DMA_FLAG_ERR12)  || ((FLAG) ==DMA_FLAG_ERR13)\
                           ((FLAG) ==DMA_FLAG_ERR14)  || ((FLAG) ==DMA_FLAG_ERR15) \
                           ((FLAG) ==DMA_FLAG_FTF0)   || ((FLAG) ==DMA_FLAG_FTF1)  \
                           ((FLAG) ==DMA_FLAG_FTF2)   || ((FLAG) ==DMA_FLAG_FTF3)  \
                           ((FLAG) ==DMA_FLAG_FTF4)   || ((FLAG) ==DMA_FLAG_FTF5)  \
                           ((FLAG) ==DMA_FLAG_FTF6)   || ((FLAG) ==DMA_FLAG_FTF7)  \
                           ((FLAG) ==DMA_FLAG_FTF8)   || ((FLAG) ==DMA_FLAG_FTF9)  \
                           ((FLAG) ==DMA_FLAG_FTF10)  || ((FLAG) ==DMA_FLAG_FTF11) \
                           ((FLAG) ==DMA_FLAG_FTF12)  || ((FLAG) ==DMA_FLAG_FTF13) \
                           ((FLAG) ==DMA_FLAG_FTF14)  || ((FLAG) ==DMA_FLAG_FTF15) \
                           ((FLAG) ==DMA_FLAG_HTF0)   || ((FLAG) ==DMA_FLAG_HTF1)  \
                           ((FLAG) ==DMA_FLAG_HTF2)   || ((FLAG) ==DMA_FLAG_HTF3)  \
                           ((FLAG) ==DMA_FLAG_HTF4)   || ((FLAG) ==DMA_FLAG_HTF5)  \
                           ((FLAG) ==DMA_FLAG_HTF6)   || ((FLAG) ==DMA_FLAG_HTF7)  \
                           ((FLAG) ==DMA_FLAG_HTF8)   || ((FLAG) ==DMA_FLAG_HTF9)  \
                           ((FLAG) ==DMA_FLAG_HTF10)  || ((FLAG) ==DMA_FLAG_HTF11) \
                           ((FLAG) ==DMA_FLAG_HTF12)  || ((FLAG) ==DMA_FLAG_HTF13)\
                           ((FLAG) ==DMA_FLAG_HTF14)  || ((FLAG) ==DMA_FLAG_HTF15)||((FLAG) ==DMA_FLAG_WDG))

/*
 * @defgroup  DMAy interrupts definition
 */
#define DMA_ERR_IT                          ((uint32_t)0x10000000)
#define DMA_FTF_IT                          ((uint32_t)0x20000000)
#define DMA_HTF_IT                          ((uint32_t)0x40000000)
#define DMA_WDG_IT                          ((uint32_t)0x80000000)
#define IS_DMA_CONFIG_IT(IT) (((IT)== DMA_ERR_IT)||((IT)== DMA_FTF_IT)||((IT)== DMA_HTF_IT)||((IT)== DMA_WDG_IT))

#define  DMA_IT_ERR0              ((uint32_t)0x10000001)
#define  DMA_IT_ERR1              ((uint32_t)0x10000002)
#define  DMA_IT_ERR2              ((uint32_t)0x10000004)
#define  DMA_IT_ERR3              ((uint32_t)0x10000008)
#define  DMA_IT_ERR4              ((uint32_t)0x10000010)
#define  DMA_IT_ERR5              ((uint32_t)0x10000020)
#define  DMA_IT_ERR6              ((uint32_t)0x10000040)
#define  DMA_IT_ERR7              ((uint32_t)0x10000080)
#define  DMA_IT_ERR8              ((uint32_t)0x10000100)
#define  DMA_IT_ERR9              ((uint32_t)0x10000200)
#define  DMA_IT_ERR10             ((uint32_t)0x10000400)
#define  DMA_IT_ERR11             ((uint32_t)0x10000800)
#define  DMA_IT_ERR12             ((uint32_t)0x10001000)
#define  DMA_IT_ERR13             ((uint32_t)0x10002000)
#define  DMA_IT_ERR14             ((uint32_t)0x10004000)
#define  DMA_IT_ERR15             ((uint32_t)0x10008000)

#define  DMA_IT_FTF0              ((uint32_t)0x20000001)
#define  DMA_IT_FTF1              ((uint32_t)0x20000002)
#define  DMA_IT_FTF2              ((uint32_t)0x20000004)
#define  DMA_IT_FTF3              ((uint32_t)0x20000008)
#define  DMA_IT_FTF4              ((uint32_t)0x20000010)
#define  DMA_IT_FTF5              ((uint32_t)0x20000020)
#define  DMA_IT_FTF6              ((uint32_t)0x20000040)
#define  DMA_IT_FTF7              ((uint32_t)0x20000080)
#define  DMA_IT_FTF8              ((uint32_t)0x20000100)
#define  DMA_IT_FTF9              ((uint32_t)0x20000200)
#define  DMA_IT_FTF10             ((uint32_t)0x20000400)
#define  DMA_IT_FTF11             ((uint32_t)0x20000800)
#define  DMA_IT_FTF12             ((uint32_t)0x20001000)
#define  DMA_IT_FTF13             ((uint32_t)0x20002000)
#define  DMA_IT_FTF14             ((uint32_t)0x20004000)
#define  DMA_IT_FTF15             ((uint32_t)0x20008000)

#define  DMA_IT_HTF0              ((uint32_t)0x40000001)
#define  DMA_IT_HTF1              ((uint32_t)0x40000002)
#define  DMA_IT_HTF2              ((uint32_t)0x40000004)
#define  DMA_IT_HTF3              ((uint32_t)0x40000008)
#define  DMA_IT_HTF4              ((uint32_t)0x40000010)
#define  DMA_IT_HTF5              ((uint32_t)0x40000020)
#define  DMA_IT_HTF6              ((uint32_t)0x40000040)
#define  DMA_IT_HTF7              ((uint32_t)0x40000080)
#define  DMA_IT_HTF8              ((uint32_t)0x40000100)
#define  DMA_IT_HTF9              ((uint32_t)0x40000200)
#define  DMA_IT_HTF10             ((uint32_t)0x40000400)
#define  DMA_IT_HTF11             ((uint32_t)0x40000800)
#define  DMA_IT_HTF12             ((uint32_t)0x40001000)
#define  DMA_IT_HTF13             ((uint32_t)0x40002000)
#define  DMA_IT_HTF14             ((uint32_t)0x40004000)
#define  DMA_IT_HTF15             ((uint32_t)0x40008000)

#define  DMA_IT_WDG               ((uint32_t)0x80000001)               

#define IS_DMA_CLEAR_IT(IT) (((((IT) & 0xEFFF0000) == 0x00) || (((IT) & 0xDFFF0000) == 0x00) ||(((IT) & 0xBFFF0000) == 0x00)||(((IT) & 0x7FFF0000) == 0x00) ) && ((IT) != 0x00)) 
#define IS_DMA_IT(IT) (((IT) ==DMA_IT_ERR0)   || ((IT) ==DMA_IT_ERR1)  \
                           ((IT) ==DMA_IT_ERR2)   || ((IT) ==DMA_IT_ERR3)  \
                           ((IT) ==DMA_IT_ERR4)   || ((IT) ==DMA_IT_ERR5)  \
                           ((IT) ==DMA_IT_ERR6)   || ((IT) ==DMA_IT_ERR7)  \
                           ((IT) ==DMA_IT_ERR8)   || ((IT) ==DMA_IT_ERR9)  \
                           ((IT) ==DMA_IT_ERR10)  || ((IT) ==DMA_IT_ERR11) \
                           ((IT) ==DMA_IT_ERR12)  || ((IT) ==DMA_IT_ERR13)\
                           ((IT) ==DMA_IT_ERR14)  || ((IT) ==DMA_IT_ERR15) \
                           ((IT) ==DMA_IT_FTF0)   || ((IT) ==DMA_IT_FTF1)  \
                           ((IT) ==DMA_IT_FTF2)   || ((IT) ==DMA_IT_FTF3)  \
                           ((IT) ==DMA_IT_FTF4)   || ((IT) ==DMA_IT_FTF5)  \
                           ((IT) ==DMA_IT_FTF6)   || ((IT) ==DMA_IT_FTF7)  \
                           ((IT) ==DMA_IT_FTF8)   || ((IT) ==DMA_IT_FTF9)  \
                           ((IT) ==DMA_IT_FTF10)  || ((IT) ==DMA_IT_FTF11) \
                           ((IT) ==DMA_IT_FTF12)  || ((IT) ==DMA_IT_FTF13) \
                           ((IT) ==DMA_IT_FTF14)  || ((IT) ==DMA_IT_FTF15) \
                           ((IT) ==DMA_IT_HTF0)   || ((IT) ==DMA_IT_HTF1)  \
                           ((IT) ==DMA_IT_HTF2)   || ((IT) ==DMA_IT_HTF3)  \
                           ((IT) ==DMA_IT_HTF4)   || ((IT) ==DMA_IT_HTF5)  \
                           ((IT) ==DMA_IT_HTF6)   || ((IT) ==DMA_IT_HTF7)  \
                           ((IT) ==DMA_IT_HTF8)   || ((IT) ==DMA_IT_HTF9)  \
                           ((IT) ==DMA_IT_HTF10)  || ((IT) ==DMA_IT_HTF11) \
                           ((IT) ==DMA_IT_HTF12)  || ((IT) ==DMA_IT_HTF13)\
                           ((IT) ==DMA_IT_HTF14)  || ((IT) ==DMA_IT_HTF15)||((IT) ==DMA_IT_WDG))

/*
 * @defgroup  DMAy Channelx Peripheral Interface number
 */
 
#define TIM0_IF  	  ((uint32_t)0x00) 
#define ADC0_IF  	  ((uint32_t)0x01)
#define ADC1_IF  	  ((uint32_t)0x02)
#define SPI0_IF  	  ((uint32_t)0x03)
#define SPI1_IF  	  ((uint32_t)0x04)
#define SPI2_IF  	  ((uint32_t)0x05)
#define USART0_IF   ((uint32_t)0x08)		
#define USART1_IF   ((uint32_t)0x09)
#define USART2_IF   ((uint32_t)0x0a)
#define USART3_IF   ((uint32_t)0x0b)
#define TIM2_IF     ((uint32_t)0x0c) 
#define TIM3_IF     ((uint32_t)0x0d) 
#define TIM4_IF     ((uint32_t)0x0e)

#define TIM1_IF  	  ((uint32_t)0x00) 
#define ADC2_IF	    ((uint32_t)0x01)
#define SPI3_IF    	((uint32_t)0x02)
#define SPI4_IF    	((uint32_t)0x03)
#define SPI5_IF    	((uint32_t)0x04)
#define USART4_IF  	((uint32_t)0x07)
#define USART5_IF   ((uint32_t)0x08)		
#define USART6_IF   ((uint32_t)0x09)
#define USART7_IF   ((uint32_t)0x0a)
#define TIM5_IF     ((uint32_t)0x0b)
#define TIM6_IF   	((uint32_t)0x0c) 
#define TIM7_IF   	((uint32_t)0x0d)

#define IS_PeriphInterface_Number(IF_Number) \
                                (((IF_Number) == ADC0_IF) || \
                                ((IF_Number) == ADC1_IF) || \
                                ((IF_Number) == SPI0_IF) || \
                                ((IF_Number) == SPI1_IF) || \
                                ((IF_Number) == SPI2_IF) || \
                                ((IF_Number) == USART0_IF) || \
                                ((IF_Number) == USART1_IF) || \
                                ((IF_Number) == USART2_IF) || \
                                ((IF_Number) == USART3_IF) || \
                                ((IF_Number) == TIM2_IF) || \
                                ((IF_Number) == TIM3_IF) || \
                                ((IF_Number) == TIM4_IF) || \
                                \
                                ((IF_Number) == TIM1_IF) || \
                                ((IF_Number) == ADC2_IF) || \
                                ((IF_Number) == SPI3_IF) || \
                                ((IF_Number) == SPI4_IF) || \
                                ((IF_Number) == SPI5_IF) || \
                                ((IF_Number) == USART4_IF) || \
                                ((IF_Number) == USART5_IF) || \
                                ((IF_Number) == USART6_IF) || \
                                ((IF_Number) == USART7_IF) || \
                                ((IF_Number) == TIM5_IF) || \
                                ((IF_Number) == TIM6_IF) || \
                                ((IF_Number) == TIM7_IF))

/*
 * @brief Function declaration
 */
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx,FunctionalState NewState);
void DMA_WDGConfig( DMA_TypeDef * DMAy,uint16_t Counter,FunctionalState NewState);
void DMA_DcoreCmd( DMA_TypeDef * DMAy,FunctionalState NewState);
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT,FunctionalState NewState);
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber); 
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);
FlagStatus DMA_GetFlagStatus(DMA_TypeDef* DMAy,uint32_t DMA_FLAG);
void DMA_ClearFlag(DMA_TypeDef* DMAy,uint32_t DMA_FLAG);
ITStatus DMA_GetITStatus(DMA_TypeDef* DMAy,uint32_t DMAy_IT);
void DMA_ClearITPendingBit(DMA_TypeDef* DMAy,uint32_t DMAy_IT);
void DMA_PeriphIF(DMA_Channel_TypeDef* DMAy_Channelx,uint32_t IF_Number);

#ifdef __cplusplus
}
#endif

#endif

/*****END OF FILE*****/