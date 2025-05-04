/*
 * @Description: 
 * @Version: 2.0
 * @Autor: ruog__
 * @Date: 2025-07-23 16:26:18
 * @LastEditors: ruog__
 * @LastEditTime: 2025-05-03 06:19:32
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __XINGJIAN__H
#define __XINGJIAN__H

/* Includes ------------------------------------------------------------------*/
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_usart.h"
#include "as32x601_spi.h"
#include "as32x601_plic.h"

/* Exported define -----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
// 定义AT指令类型枚举（按参数数量分类）
typedef enum {
    // 无参数指令
    AT_CMD_NONE_IAP,               // 对应AT+IAP：进入IAP升级模式（谨慎使用，详情参考8.3节串口升级固件注意事项）
    AT_CMD_NONE_RESET,             // 对应AT+RESET：设备重启指令
    AT_CMD_NONE_DEFAULT,           // 对应AT+DEFAULT：配置参数恢复默认值并重启设备
    AT_CMD_NONE_HELP_QUERY,        // 对应AT+HELP=?：查询AT指令表，返回所有支持的指令及说明
    AT_CMD_NONE_DEVTYPE_QUERY,     // 对应AT+DEVTYPE=?：查询模块型号，返回示例：DEVTYPE=E22-400T30D/D
    AT_CMD_NONE_FWCODE_QUERY,      // 对应AT+FWCODE=?：查询固件编码，返回示例：FWCODE=7432-0-10
    AT_CMD_NONE_UART_QUERY,        // 对应AT+UART=?：查询当前波特率和校验位配置，返回示例：AT+UART=3,0
    AT_CMD_NONE_RATE_QUERY,        // 对应AT+RATE=?：查询当前空中速率配置，返回示例：AT+RATE=7
    AT_CMD_NONE_PACKET_QUERY,      // 对应AT+PACKET=?：查询当前封包长度配置，返回示例：AT+PACKET=0
    AT_CMD_NONE_WOR_QUERY,         // 对应AT+WOR=?：查询当前WOR角色配置，返回示例：AT+WOR=0
    AT_CMD_NONE_POWER_QUERY,       // 对应AT+POWER=?：查询当前发送功率配置，返回示例：AT+POWER=0
    AT_CMD_NONE_TRANS_QUERY,       // 对应AT+TRANS=?：查询当前发送模式配置，返回示例：AT+TRANS=1
    AT_CMD_NONE_ROUTER_QUERY,      // 对应AT+ROUTER=?：查询当前中继模式配置，返回示例：AT+ROUTER=1
    AT_CMD_NONE_LBT_QUERY,         // 对应AT+LBT=?：查询LBT功能开关状态，返回示例：AT+LBT=1
    AT_CMD_NONE_ERSSI_QUERY,       // 对应AT+ERSSI=?：查询环境噪声RSSI开关状态，返回示例：AT+ERSSI=1
    AT_CMD_NONE_DRSSI_QUERY,       // 对应AT+DRSSI=?：查询接收数据RSSI开关状态，返回示例：AT+DRSSI=1
    AT_CMD_NONE_ADDR_QUERY,        // 对应AT+ADDR=?：查询当前模块地址，返回示例：AT+ADDR=1234
    AT_CMD_NONE_CHANNEL_QUERY,     // 对应AT+CHANNEL=?：查询当前工作信道，返回示例：AT+CHANNEL=23
    AT_CMD_NONE_NETID_QUERY,       // 对应AT+NETID=?：查询当前网络ID，返回示例：AT+NETID=2
    AT_CMD_NONE_KEY_QUERY,         // 对应AT+KEY=?：查询模块密钥（安全考虑，返回ERR）
    AT_CMD_NONE_DELAY_QUERY,       // 对应AT+DELAY=?：查询WOR延迟休眠时间，返回示例：AT+DELAY=1000
    AT_CMD_NONE_SWITCH_QUERY,      // 对应AT+SWITCH=?：查询软件切换模式开关状态，返回示例：AT+SWITCH=0
    AT_CMD_NONE_MODE_QUERY,        // 对应AT+MODE=?：查询当前工作模式，返回示例：AT+MODE=0

    // 单参数指令
    AT_CMD_1PARAM_RATE,            // 对应AT+RATE=param：设定空中速率，param为速率编码（400MHz/230MHz频段各有定义）
    AT_CMD_1PARAM_PACKET,          // 对应AT+PACKET=param：设定封包长度，param为长度编码（0-240字节，1-128字节等）
    AT_CMD_1PARAM_WOR,             // 对应AT+WOR=param：设定WOR角色，param为角色类型（0-接收，1-发送）
    AT_CMD_1PARAM_POWER,           // 对应AT+POWER=param：设定发送功率，param为功率等级（0-30dBm等）
    AT_CMD_1PARAM_TRANS,           // 对应AT+TRANS=param：设定发送模式，param为模式类型（0-透明模式，1-定点模式）
    AT_CMD_1PARAM_ROUTER,          // 对应AT+ROUTER=param：设定中继模式，param为开关状态（0-关闭，1-开启）
    AT_CMD_1PARAM_LBT,             // 对应AT+LBT=param：设定LBT功能开关，param为开关状态（0-关闭，1-开启）
    AT_CMD_1PARAM_ERSSI,           // 对应AT+ERSSI=param：设定环境噪声RSSI开关，param为开关状态（0-关闭，1-开启）
    AT_CMD_1PARAM_DRSSI,           // 对应AT+DRSSI=param：设定接收数据RSSI开关，param为开关状态（0-关闭，1-开启）
    AT_CMD_1PARAM_ADDR,            // 对应AT+ADDR=param：设定模块地址，param为地址值（0~65535，十进制）
    AT_CMD_1PARAM_CHANNEL,         // 对应AT+CHANNEL=param：设定工作信道，param为信道号（0~83，十进制）
    AT_CMD_1PARAM_NETID,           // 对应AT+NETID=param：设定网络ID，param为网络标识（0~255，十进制）
    AT_CMD_1PARAM_KEY,             // 对应AT+KEY=param：设定模块密钥，param为密钥值（0~65535，十进制）
    AT_CMD_1PARAM_DELAY,           // 对应AT+DELAY=param：设定WOR延迟休眠时间，param为时间值（0~65535ms）
    AT_CMD_1PARAM_SWITCH,          // 对应AT+SWITCH=param：设定软件切换模式开关，param为开关状态（0-关闭，1-开启）
    AT_CMD_1PARAM_MODE,            // 对应AT+MODE=param：切换工作模式，param为模式类型（0-透传，1-WOR，2-配置）

    // 双参数指令
    AT_CMD_2PARAM_UART             // 对应AT+UART=param1,param2：设定波特率和校验位，param1为波特率编码，param2为校验位编码
} AtCommandType;

typedef enum
{
    AT_CMD_GET_UART_QUERY=6,    // 对应AT+UART=?：查询当前波特率和校验位配置，返回示例：AT+UART=3,0
    AT_CMD_GET_RATE_QUERY,    // 对应AT+RATE=?：查询当前空中速率配置，返回示例：AT+RATE=7
    AT_CMD_GET_PACKET_QUERY,  // 对应AT+PACKET=?：查询当前封包长度配置，返回示例：AT+PACKET=0
    AT_CMD_GET_WOR_QUERY,     // 对应AT+WOR=?：查询当前WOR角色配置，返回示例：AT+WOR=0
    AT_CMD_GET_POWER_QUERY,   // 对应AT+POWER=?：查询当前发送功率配置，返回示例：AT+POWER=0
    AT_CMD_GET_TRANS_QUERY,   // 对应AT+TRANS=?：查询当前发送模式配置，返回示例：AT+TRANS=1
    AT_CMD_GET_ROUTER_QUERY,  // 对应AT+ROUTER=?：查询当前中继模式配置，返回示例：AT+ROUTER=1
    AT_CMD_GET_LBT_QUERY,     // 对应AT+LBT=?：查询LBT功能开关状态，返回示例：AT+LBT=1
    AT_CMD_GET_ERSSI_QUERY,   // 对应AT+ERSSI=?：查询环境噪声RSSI开关状态，返回示例：AT+ERSSI=1
    AT_CMD_GET_DRSSI_QUERY,   // 对应AT+DRSSI=?：查询接收数据RSSI开关状态，返回示例：AT+DRSSI=1
    AT_CMD_GET_ADDR_QUERY,    // 对应AT+ADDR=?：查询当前模块地址，返回示例：AT+ADDR=1234
    AT_CMD_GET_CHANNEL_QUERY, // 对应AT+CHANNEL=?：查询当前工作信道，返回示例：AT+CHANNEL=23
    AT_CMD_GET_NETID_QUERY,   // 对应AT+NETID=?：查询当前网络ID，返回示例：AT+NETID=2
    AT_CMD_GET_KEY_QUERY,     // 对应AT+KEY=?：查询模块密钥（安全考虑，返回ERR）
    AT_CMD_GET_DELAY_QUERY,   // 对应AT+DELAY=?：查询WOR延迟休眠时间，返回示例：AT+DELAY=1000
    AT_CMD_GET_SWITCH_QUERY,  // 对应AT+SWITCH=?：查询软件切换模式开关状态，返回示例：AT+SWITCH=0
    AT_CMD_GET_MODE_QUERY,    // 对应AT+MODE=?：查询当前工作模式，返回示例：AT+MODE=0
} ATCommandCHAXUN;             // 查询指令

//星间模块控制指令
extern uint8_t at_send_cmd(AtCommandType cmd, int param1, int param2);

//透传文件数据转发接口
extern int8_t forward_transparent_file_data(const uint8_t *file_data, uint16_t data_len);

// 透传文件任务缓存结构体
typedef struct {
    uint8_t used;                // 是否正在缓存
    uint8_t task_seq;            // 任务序号
    uint16_t total_len;          // 总数据长度
    uint16_t received_len;       // 已接收长度
    uint8_t data_type;           // 数据类型
    uint8_t data_encoding;       // 数据编码
    uint8_t buffer[1024];        // 数据缓存
} TransparentFileTask;

/**
 * @brief 配置星间模块的工作模式, 两M1和M0 引脚进行拉低或者拉高来配置
 *         RTU连接了2个星间模块，所以是4个GPIO口。分别是PB11
 * @param mode
 * @param xingjianNum   星间模块的编号
 * @return int
 */
// 模式（0-3） M1 M0 模式介绍 备注
// 0 传输模式 0 0 串口打开， 无线打开， 透明传输 支持特殊指令空中配置
// 1 WOR 模式 0 1 可以定义为 WOR 发送方和 WOR 接收方 支持空中唤醒
// 2 配置模式 1 0 用户可通过串口对寄存器进行访问， 从而控制模块工作状态
// 3 深度休眠 1 1 模块进入休眠
extern int xingjian_change_config_mode(uint8_t xingjianNum, uint8_t mode);


/**
 * @brief 星间模块复位
 *
 * @return int
 */
extern int xingjian_reset(uint8_t xingjianNum);

// 星间模块透传数据协议解析与CANFD分帧发送函数声明
extern void xj_transparent_data_parse_and_send(void);
// 星间模块响应数据处理函数声明
extern void xingjian_response_process(void);

// 星间模块AT指令响应相关变量声明
extern uint8_t xingjian_response_buffer[32];
extern uint8_t xingjian_response_ptr;
extern volatile uint8_t xingjian_config_ok_flag;
extern volatile uint8_t xingjian_mode_config_ok_flag;

#endif

/*****END OF FILE*****/
