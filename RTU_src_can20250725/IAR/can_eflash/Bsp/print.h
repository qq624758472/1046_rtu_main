/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PRINT_H
#define PRINT_H

/* Includes ------------------------------------------------------------------*/
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_usart.h"
#include "as32x601_spi.h"
#include "as32x601_plic.h"
#include "as32x601_usart_regs.h"
/* Exported define -----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void User_app1_uart5_Init(uint32_t BaudRate);
extern void User_app2_uart3_Init(uint32_t BaudRate);
extern void User_app3_uart1_Init(uint32_t BaudRate);
extern void User_app4_uart0_Init(uint32_t BaudRate);
extern void User_appTS_uart6_Init(uint32_t BaudRate);


/**
 * @brief 向指定USART外设发送十六进制数据，并打印发送的内容
 * @param uart: 目标USART外设（如USART0、USART1等宏定义）
 * @param data: 待发送的数据缓冲区
 * @param len: 待发送数据的长度
 * @return 0: 成功
 */
extern uint8_t uart_send_hex_datas(USART_TypeDef *uart, uint8_t *data, uint32_t len);

// 星间模块配置相关声明
extern volatile uint8_t xingjian_config_ok_flag;  // 星间模块配置成功标志位
extern volatile uint8_t xingjian_mode_config_ok_flag;  // 星间模块工作模式配置成功标志位

#endif

/*****END OF FILE*****/
