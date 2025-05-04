#include "uart_dianji.h"
#include "canfd_xieyi.h"
#include "myprintf.h"
#include <string.h>
#include <stdlib.h>

// 包头定义
#define PACKET_HEADER_1 0xEB
#define PACKET_HEADER_2 0x90

// 固定字段定义（可根据实际需求修改）
#define DEFAULT_ID 0x01        // ID字默认值
#define DEFAULT_DATA_TYPE 0x05 // 数据类型字默认值
#define DEFAULT_CMD_CODE 0x44  // 命令码字默认值
#define DEFAULT_REQ_ID 0x00    // 请求ID默认值

// 全局变量：电机数据包接收结构体
MotorPacketRx motor_rx_usart0;
MotorPacketRx motor_rx_usart1;

// 发送遥测数据，这里直接传所有数据和总长度，这个函数进行分包发送
uint8_t canfd_send_all_data0(uint8_t *data, uint16_t data_length);
/**
 * @brief 向指定USART外设发送十六进制数据，并打印发送的内容
 * @param uart: 目标USART外设（如USART0、USART1等宏定义）
 * @param data: 待发送的数据缓冲区
 * @param len: 待发送数据的长度
 * @return 0: 成功
 */
uint8_t uart_send_hex_datas(USART_TypeDef *uart, uint8_t *data, uint32_t len);

/**
 * @brief 初始化电机数据包接收结构体
 * @param rx: 电机数据包接收结构体指针
 */
void motor_packet_rx_init(MotorPacketRx *rx)
{
    if (rx == NULL)
        return;

    memset(rx->buffer, 0, MOTOR_PACKET_MAX_LEN);
    rx->length = 0;
    rx->expected_length = 0;
    rx->state = MOTOR_RX_IDLE;
    rx->is_complete = 0;
    rx->checksum = 0;
}

/**
 * @brief 接收单个字节并处理状态机
 * @param rx: 电机数据包接收结构体指针
 * @param byte: 接收到的字节
 * @return 0: 继续接收, 1: 数据包接收完成, 2: 接收错误
 */
uint8_t motor_packet_rx_byte(MotorPacketRx *rx, uint8_t byte)
{
    if (rx == NULL)
        return 2;

    switch (rx->state)
    {
    case MOTOR_RX_IDLE:
        // 等待包头第一个字节
        if (byte == MOTOR_PACKET_HEADER1)
        {
            rx->buffer[0] = byte;
            rx->length = 1;
            rx->checksum = byte;
            rx->state = MOTOR_RX_HEADER;
        }
        break;

    case MOTOR_RX_HEADER:
        // 等待包头第二个字节
        if (byte == MOTOR_PACKET_HEADER2)
        {
            rx->buffer[1] = byte;
            rx->length = 2;
            rx->checksum += byte;
            rx->state = MOTOR_RX_ID;
        }
        else
        {
            // 包头错误，重新开始
            motor_packet_rx_init(rx);
            if (byte == MOTOR_PACKET_HEADER1)
            {
                rx->buffer[0] = byte;
                rx->length = 1;
                rx->checksum = byte;
                rx->state = MOTOR_RX_HEADER;
            }
        }
        break;

    case MOTOR_RX_ID:
        // 接收ID字
        rx->buffer[2] = byte;
        rx->length = 3;
        rx->checksum += byte;
        rx->state = MOTOR_RX_LENGTH;
        break;

    case MOTOR_RX_LENGTH:
        // 接收数据长度第一个字节
        rx->buffer[3] = byte;
        rx->length = 4;
        rx->checksum += byte;
        rx->state = MOTOR_RX_LENGTH2;
        break;

    case MOTOR_RX_LENGTH2:
        // 接收数据长度第二个字节
        rx->buffer[4] = byte;
        rx->length = 5;
        rx->checksum += byte;
        // 验证数据长度是否为0x35
        if (rx->buffer[3] == 0x00 && byte == MOTOR_PACKET_DATA_LEN)
        {
            rx->state = MOTOR_RX_TYPE;
        }
        else
        {
            // 数据长度错误，重新开始
            motor_packet_rx_init(rx);
            if (byte == MOTOR_PACKET_HEADER1)
            {
                rx->buffer[0] = byte;
                rx->length = 1;
                rx->checksum = byte;
                rx->state = MOTOR_RX_HEADER;
            }
        }
        break;

    case MOTOR_RX_TYPE:
        // 接收数据类型
        rx->buffer[5] = byte;
        rx->length = 6;
        rx->checksum += byte;
        // 验证数据类型是否为0x05
        if (byte == MOTOR_PACKET_DATA_TYPE)
        {
            rx->state = MOTOR_RX_CMD;
        }
        else
        {
            // 数据类型错误，重新开始
            motor_packet_rx_init(rx);
            if (byte == MOTOR_PACKET_HEADER1)
            {
                rx->buffer[0] = byte;
                rx->length = 1;
                rx->checksum = byte;
                rx->state = MOTOR_RX_HEADER;
            }
        }
        break;

    case MOTOR_RX_CMD:
        // 接收命令码
        rx->buffer[6] = byte;
        rx->length = 7;
        rx->checksum += byte;
        // 验证命令码是否为0xB0
        if (byte == MOTOR_PACKET_CMD_CODE)
        {
            rx->state = MOTOR_RX_REQ_ID;
        }
        else
        {
            // 命令码错误，重新开始
            motor_packet_rx_init(rx);
            if (byte == MOTOR_PACKET_HEADER1)
            {
                rx->buffer[0] = byte;
                rx->length = 1;
                rx->checksum = byte;
                rx->state = MOTOR_RX_HEADER;
            }
        }
        break;

    case MOTOR_RX_REQ_ID:
        // 接收请求ID
        rx->buffer[7] = byte;
        rx->length = 8;
        rx->checksum += byte;
        rx->state = MOTOR_RX_DATA;
        break;

    case MOTOR_RX_DATA:
        // 接收遥测数据部分
        if (rx->length < MOTOR_PACKET_MAX_LEN - 1)
        {
            rx->buffer[rx->length] = byte;
            rx->length++;
            rx->checksum += byte;

            // 检查是否接收到完整的遥测数据(50字节)
            if (rx->length >= 8 + MOTOR_PACKET_TELEMETRY_LEN)
            {
                rx->state = MOTOR_RX_CHECKSUM;
            }
        }
        else
        {
            // 缓冲区溢出，重新开始
            motor_packet_rx_init(rx);
        }
        break;

    case MOTOR_RX_CHECKSUM:
        // 接收校验和
        rx->buffer[rx->length] = byte;
        rx->length++;

        // 验证校验和
        if (rx->checksum == byte)
        {
            rx->is_complete = 1;
            rx->state = MOTOR_RX_COMPLETE;
            return 1; // 数据包接收完成
        }
        else
        {
            // 校验和错误，重新开始
            motor_packet_rx_init(rx);
            return 2; // 接收错误
        }
        break;

    case MOTOR_RX_COMPLETE:
        // 数据包已完成，等待下一个包头
        if (byte == MOTOR_PACKET_HEADER1)
        {
            motor_packet_rx_init(rx);
            rx->buffer[0] = byte;
            rx->length = 1;
            rx->checksum = byte;
            rx->state = MOTOR_RX_HEADER;
        }
        break;
    }

    return 0; // 继续接收
}

/**
 * @brief 验证电机数据包的完整性
 * @param rx: 电机数据包接收结构体指针
 * @return 0: 验证通过, 非0: 验证失败
 */
uint8_t motor_packet_validate(MotorPacketRx *rx)
{
    if (rx == NULL || !rx->is_complete)
        return 1;

    // 检查数据包长度
    if (rx->length != MOTOR_PACKET_MIN_LEN)
        return 2;

    // 检查包头
    if (rx->buffer[0] != MOTOR_PACKET_HEADER1 || rx->buffer[1] != MOTOR_PACKET_HEADER2)
        return 3;

    // 检查数据长度字段
    if (rx->buffer[3] != 0x00 || rx->buffer[4] != MOTOR_PACKET_DATA_LEN)
        return 4;

    // 检查数据类型
    if (rx->buffer[5] != MOTOR_PACKET_DATA_TYPE)
        return 5;

    // 检查命令码
    if (rx->buffer[6] != MOTOR_PACKET_CMD_CODE)
        return 6;

    // 校验和已在接收时验证过，这里再次确认
    uint8_t calc_checksum = 0;
    for (uint16_t i = 0; i < rx->length - 1; i++)
    {
        calc_checksum += rx->buffer[i];
    }

    if (calc_checksum != rx->buffer[rx->length - 1])
        return 7;

    return 0; // 验证通过
}

/**
 * @brief 处理接收到的电机数据包
 * @param rx: 电机数据包接收结构体指针
 */
void motor_packet_process(MotorPacketRx *rx)
{
    if (rx == NULL || !rx->is_complete)
        return;

    // 验证数据包
    if (motor_packet_validate(rx) != 0)
    {
        Printf("Motor packet validation failed!\r\n");
        return;
    }

    // 打印接收到的数据包（调试用）
    Printf("Motor packet received, length: %d\r\n", rx->length);
    for (uint16_t i = 0; i < rx->length; i++)
    {
        Printf("%02X ", rx->buffer[i]);
    }
    Printf("\r\n");

    // 数据包已经通过motor_packet_validate验证，直接处理
    // 电机返回的数据包按照协议格式：包头2+ID1+长度2+类型1+命令码1+请求ID1+数据50+校验1 = 59字节
    // 将电机返回的完整59字节数据包直接复制到frame中
    // 确保frame中的全部字节数据都与电机返回的完全一致
    memcpy(&frame, rx->buffer, rx->length);

    Printf("Motor telemetry data updated to frame successfully\r\n");

    // 打印完整的59字节数据包内容
    Printf("=== 电机完整数据包内容 (59字节) ===\r\n");
    Printf("包头: 0x%02X 0x%02X\r\n", rx->buffer[0], rx->buffer[1]);
    Printf("ID: 0x%02X\r\n", rx->buffer[2]);
    Printf("数据长度: 0x%02X%02X\r\n", rx->buffer[3], rx->buffer[4]);
    Printf("数据类型: 0x%02X\r\n", rx->buffer[5]);
    Printf("命令码: 0x%02X\r\n", rx->buffer[6]);
    Printf("请求ID: 0x%02X\r\n", rx->buffer[7]);
    Printf("遥测数据: ");
    for (uint16_t i = 8; i < 58; i++)
    {
        Printf("%02X ", rx->buffer[i]);
    }
    Printf("\r\n");
    Printf("校验和: 0x%02X\r\n", rx->buffer[58]);

    // 创建一个新变量，保存从ID字开始到校验和之前的数据（去掉包头）
    uint8_t motor_data_without_header[56]; // 去掉包头后的数据：59-2-1=56字节（不包括校验和）

    // 复制从ID字开始到校验和之前的数据（不包括校验和）
    // 源数据：rx->buffer[2] 到 rx->buffer[57]，共56字节
    memcpy(motor_data_without_header, &rx->buffer[2], 56);

    // 接收到全部电机数据后，通过CANFD发送给上位机（发送去掉包头后的数据）
    canfd_send_all_data0(motor_data_without_header, 56); // 发送去掉包头后的56字节数据

    // 处理完成后重置接收状态
    motor_packet_rx_init(rx);
}

/**
 * @brief 电机串口接收中断处理函数
 * @param uart: 串口外设
 * @param rx: 对应的电机数据包接收结构体
 */
void motor_uart_rx_handler(USART_TypeDef *uart, MotorPacketRx *rx)
{
    if (uart == NULL || rx == NULL)
        return;

    uint8_t received_byte = USART_ReceiveData(uart);

    uint8_t result = motor_packet_rx_byte(rx, received_byte);
    if (result == 1)
    {
        // 数据包接收完成，进行处理
        motor_packet_process(rx);
    }
    else if (result == 2)
    {
        // 接收错误
        Printf("Motor packet receive error\r\n");
    }
}

/**
 * @brief 将指令重新打包后转发到串口， 《电机转发协议中，最后的补数0xff未实现，等电机研发出来后实现》
 * @param data: 待打包的数据内容
 * @param len: 待打包数据的长度(n字节)
 * @return 0:成功, 非0:失败
 */
uint8_t dj_uart_cmd_analyze(uint8_t *data, uint8_t len)
{
    // 参数合法性检查
    if (data == NULL || len == 0)
    {
        Printf("dj_uart_cmd_analyze error\r\n");
        return 1; // 数据为空或长度为0
    }

    // 计算数据包总长度: 固定头部(8字节) + 数据(n字节) + 校验和(1字节)
    uint16_t total_len = 2 + len + 1;

    // 分配内存存储打包后的数据
    uint8_t *packet = (uint8_t *)malloc(total_len);
    if (packet == NULL)
    {
        Printf("dj_uart_cmd_analyze malloc error\r\n");
        return 2; // 内存分配失败
    }

    // 填充包头字段
    packet[0] = PACKET_HEADER_1; // 包头第1字节
    packet[1] = PACKET_HEADER_2; // 包头第2字节
    memcpy(&packet[2], data, len);

    // 计算和校验（从包头到数据部分的所有字节累加）
    uint8_t checksum = 0;
    for (uint16_t i = 0; i < total_len; i++)
    {
        checksum += packet[i];
    }
    packet[total_len - 1] = checksum; // 校验字

    // 发送数据包到串口
    if (uart_send_hex_datas(USART5, packet, total_len) != 0)
    {
        Printf("uart_send_hex_datas USART0 failed!\r\n");
        free(packet);
        return 3; // 发送失败
    }

    // 加入调试
    // uart_send_hex_datas(USART6, packet, total_len);//打印调试信息

    // 释放内存
    free(packet);
    return 0; // 成功
}

/**
 * @brief 电机遥测的回复,进行组包后，通过canfd返回
 *
 * @param data  电机的遥测数据，完整数据没减去头和校验和
 * @param dataLen
 * @return uint8_t
 */
uint8_t dj_uart_cmd_yc_return(uint8_t *data, uint8_t dataLen)
{
    if (data == NULL || dataLen != 59)
    {
        Printf("recv dian ji yao ce error\r\n");
        return 1;
    }

    // 计算数据包总长度: 转发遥测数据需要减去包头和校验和。加上canfd协议的头和校验和5字节。
    uint16_t total_len = dataLen - 3 + 5 + 3; // 还有3个字节的预留数据

    // 分配内存存储打包后的数据
    uint8_t *packet = (uint8_t *)malloc(total_len);
    if (packet == NULL)
    {
        return 2; // 内存分配失败
    }
    memset(packet, 0, total_len);

    // 填充包头字段
    canfdXYHead *p = (canfdXYHead *)packet;
    p->dataLength = dataLen + 4;
    p->dataType = 0x35;
    p->dataNum = 0x02; // 数据编号。

    uint8_t *p_data = &packet[4];
    memcpy(p_data, &data[2], dataLen - 3); // 共56个有效数据

    uint8_t checksum = 0;
    for (uint16_t i = 0; i < total_len; i++)
    {
        checksum += packet[i];
    }
    packet[total_len - 1] = checksum;

    // 发送给
    //  for(int i=0;i<total_len;i++)
    //      Printf(" 0x%x",packet[i]);
    canfd_send_all_data(packet, total_len);

    free(packet);
    return 0;
}