/*
 * @Description: 
 * @Version: 2.0
 * @Autor: ruog__
 * @Date: 2025-07-17 13:49:15
 * @LastEditors: ruog__
 * @LastEditTime: 2025-05-02 12:23:02
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LED_H
#define LED_H

/* Includes ------------------------------------------------------------------*/
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"

/* Exported define -----------------------------------------------------------*/

#define LED1_ON()       GPIO_WriteBits(GPIOG, GPIO_Pin_15, GPIO_OCtrl_Vol)
#define LED1_OFF()      GPIO_WriteBits(GPIOG, GPIO_Pin_15, GPIO_OCtrl_Voh)
#define LED1_TOGGLE()   GPIO_ToggleBits(GPIOG, GPIO_Pin_15)
#define LED2_ON()       GPIO_WriteBits(GPIOG, GPIO_Pin_14, GPIO_OCtrl_Vol)
#define LED2_OFF()      GPIO_WriteBits(GPIOG, GPIO_Pin_14, GPIO_OCtrl_Voh)
#define LED2_TOGGLE()   GPIO_ToggleBits(GPIOG, GPIO_Pin_14)
#define LED3_ON()       GPIO_WriteBits(GPIOG, GPIO_Pin_10, GPIO_OCtrl_Vol)
#define LED3_OFF()      GPIO_WriteBits(GPIOG, GPIO_Pin_10, GPIO_OCtrl_Voh)
#define LED3_TOGGLE()   GPIO_ToggleBits(GPIOG, GPIO_Pin_10)

/* Exported functions ------------------------------------------------------- */

extern void User_LED_Ctrl(uint8_t state);
extern void User_GPIO_Init();
extern void iic_enable_open();
//打开所有功能的使能信号
extern void User_all_enable();

/**
 * @brief 控制对外8路gpio的高电平还是低电平
 *
 * @chan 8路中的哪一路，
 *
 * @ctr  0:1
 *
 */
extern uint8_t out_gpio_ctr(uint8_t chan, uint8_t ctr);

// PG8
// PC6
/**
 * @brief 控制大电流配电使能
 *
 * @chan 8路中的哪一路，
 *
 * @ctr  0:1
 *
 */
uint8_t large_electric_gpio_ctr(uint8_t chan, uint8_t ctr);


/**
 * @brief 控制16路小电流配电使能
 *
 * @param chan 16路中的哪一路 (0-15)
 * @param ctr  控制值: 0=关闭, 1=打开
 *
 * @return 0=成功, -1=参数错误
 */
uint8_t small_electric_gpio_ctr(uint8_t chan, uint8_t ctr);


/**
 * @brief 控制电源输出使能
 *
 * @chan 2路中的哪一路，
 *
 * @ctr  0:1
 *
 */
uint8_t power_gpio_ctr(uint8_t chan, uint8_t ctr);

#endif

/*****END OF FILE*****/