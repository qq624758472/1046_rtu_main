/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DIANJI__H
#define __DIANJI__H

/* Includes ------------------------------------------------------------------*/
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_usart.h"
#include "as32x601_spi.h"
#include "as32x601_plic.h"
#include "canfd_xieyi.h"

// 电机数据包接收相关定义
#define MOTOR_PACKET_MAX_LEN    128    // 电机数据包最大长度
#define MOTOR_PACKET_MIN_LEN    59     // 电机数据包最小长度(包头2+ID1+长度2+类型1+命令码1+请求ID1+数据50+校验1)
#define MOTOR_PACKET_HEADER1    0xEB   // 包头第1字节
#define MOTOR_PACKET_HEADER2    0x90   // 包头第2字节
#define MOTOR_PACKET_DATA_LEN   0x35   // 数据长度字(2字节)
#define MOTOR_PACKET_DATA_TYPE  0x05   // 数据类型字
#define MOTOR_PACKET_CMD_CODE   0xB0   // 命令码字
#define MOTOR_PACKET_TELEMETRY_LEN 50  // 遥测数据长度(D0~D49)

// 电机数据包接收状态
typedef enum {
    MOTOR_RX_IDLE = 0,        // 空闲状态，等待包头
    MOTOR_RX_HEADER,          // 接收包头状态
    MOTOR_RX_ID,              // 接收ID字状态
    MOTOR_RX_LENGTH,          // 接收数据长度第一个字节状态
    MOTOR_RX_LENGTH2,         // 接收数据长度第二个字节状态
    MOTOR_RX_TYPE,            // 接收数据类型状态
    MOTOR_RX_CMD,             // 接收命令码状态
    MOTOR_RX_REQ_ID,          // 接收请求ID状态
    MOTOR_RX_DATA,            // 接收遥测数据状态
    MOTOR_RX_CHECKSUM,        // 接收校验和状态
    MOTOR_RX_COMPLETE         // 数据包接收完成
} MotorRxState;

// 电机数据包接收结构体
typedef struct {
    uint8_t buffer[MOTOR_PACKET_MAX_LEN];  // 接收缓冲区
    uint16_t length;                       // 当前接收长度
    uint16_t expected_length;              // 期望接收长度
    MotorRxState state;                    // 当前接收状态
    uint8_t is_complete;                   // 数据包是否完整
    uint8_t checksum;                      // 计算得到的校验和
} MotorPacketRx;

// 协议包头结构体定义（按1字节对齐）
#pragma pack(push, 1)
typedef struct {
    uint16_t header;         // 包头 (2BYTE)，固定为0xEB90（0xEB 0x90）
    uint8_t id;              // ID字 (1BYTE)
    uint16_t data_length;    // 数据长度字 (2BYTE)，示例中为0x0007
    uint8_t data_type;       // 数据类型字 (1BYTE)，示例中为0x05
    uint8_t cmd_code;        // 命令码字 (1BYTE)，示例中为0x44
    uint8_t req_id;          // 请求ID (1BYTE)
    uint8_t *data;         // 数据 (4BYTE)，对应B1~B4
} ProtocolPacket;
#pragma pack(pop)

// 结构体大小验证：2+1+2+1+1+1+4+1 = 13字节


/* Exported define -----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
//将指令重新打包后转发到串口
extern uint8_t dj_uart_cmd_analyze(uint8_t *data, uint8_t len);


/**
 * @brief 电机遥测的回复,进行组包后，通过canfd返回
 *
 * @param data  电机的遥测数据，完整数据没减去头和校验和
 * @param dataLen
 * @return uint8_t
 */
extern uint8_t dj_uart_cmd_yc_return(uint8_t *data, uint8_t dataLen);

// 电机数据包接收相关函数
extern void motor_packet_rx_init(MotorPacketRx *rx);
extern uint8_t motor_packet_rx_byte(MotorPacketRx *rx, uint8_t byte);
extern uint8_t motor_packet_validate(MotorPacketRx *rx);
extern void motor_packet_process(MotorPacketRx *rx);


// 电机数据包接收中断处理函数
extern void motor_uart_rx_handler(USART_TypeDef *uart, MotorPacketRx *rx);

// 电机数据包接收结构体实例声明
extern MotorPacketRx motor_rx_usart0;
extern MotorPacketRx motor_rx_usart1;

// 声明外部frame结构体，用于直接更新电机数据
extern canfdDJ_all frame;



#endif

/*****END OF FILE*****/
