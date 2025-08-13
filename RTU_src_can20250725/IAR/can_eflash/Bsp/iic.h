/*
 * @Description: 
 * @Version: 2.0
 * @Autor: ruog__
 * @Date: 2025-05-02 12:10:11
 * @LastEditors: ruog__
 * @LastEditTime: 2025-05-02 12:20:40
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IIC_H
#define IIC_H

/* Includes ------------------------------------------------------------------*/
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_usart.h"
#include "as32x601_i2c.h"
#include "as32x601_plic.h"


// DS2482 寄存器地址
#define DS2482_I2C0_ADDR  0x30   // 根据 A0/A1 引脚设置
#define DS2482_I2C1_ADDR  0x38   // 根据 A0/A1 引脚设置
#define DS2482_I2C2_ADDR  0x3C   // 根据 A0/A1 引脚设置
#define STATUS_REG       0xF0
#define CONFIG_REG       0xE1
#define I2C_TIMEOUT       1000  // 超时时间(ms)

// 1-Wire 命令
#define OW_RESET         0xB4
#define OW_WRITE_BYTE    0x5A //手册写的0xA5
#define OW_READ_BYTE     0x96

// DS18B20 命令
#define CONVERT_T        0x44   // 温度转换
#define READ_SCRATCHPAD  0xBE   // 读暂存器


/* Exported define -----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void User_I2C_Init();
extern void iic_enable_open();

//板卡要用的，上边的是实例
extern void User_APP1_I2C3_Init();
extern void User_APP0_I2C2_Init();
// 读取 DS18B20 温度
extern uint8_t read_ds18b20_temperature(float *temp);

extern uint8_t ads7828_read_channel(I2C_TypeDef *hi2c, uint8_t channel, uint16_t *adc_value, uint8_t ADS7828_ADDR);
#endif

/*****END OF FILE*****/
