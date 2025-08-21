#include "uart_xingjian.h"
#include "as32x601_usart_regs.h"
#include <string.h>
#include <stdio.h>
#include "print.h"
#include "myprintf.h"
#include "canfd_xieyi.h"
extern void std_feed_dog();
extern uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length);
extern uint8_t canfd_send_all_data0(uint8_t *data, uint16_t data_length);

// 发送遥测数据，这里直接传所有数据和总长度，这个函数进行分包发送
extern uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length);
// 星间模块AT指令响应接收缓冲区
uint8_t xingjian_response_buffer[32] = {0};
uint8_t xingjian_response_ptr = 0;
volatile uint8_t xingjian_config_ok_flag = 0;      // 星间模块配置成功标志位
volatile uint8_t xingjian_mode_config_ok_flag = 0; // 星间模块工作模式配置成功标志位

// 当前串口使用的是 USART0,USART1,USART3,USART5
USART_TypeDef *currentXingjianUart = USART1; // 当前使用的星间模块串口

// 星间模块透传数据接收缓冲区和组包状态
#define XJ_RX_BUFFER_SIZE 2048
uint8_t xj_rx_buffer[XJ_RX_BUFFER_SIZE];
uint16_t xj_rx_write_ptr = 0;
uint16_t xj_rx_read_ptr = 0;
#define XJ_FILE_MAX_SIZE 8192
uint8_t xj_file_buffer[XJ_FILE_MAX_SIZE];
uint32_t xj_file_total_len = 0;
uint32_t xj_file_received_len = 0;
uint8_t xj_file_task_seq = 0xFF;
uint8_t xj_file_data_type = 0;
uint8_t xj_file_data_encoding = 0;
uint8_t xj_file_receiving = 0; // 0:无任务 1:正在接收

// 任务缓存结构体
TransparentFileTask g_transparent_task = {0};
// 全局任务状态变量
uint32_t g_task_total_len = 0;    // 本次任务总长度（可能大于1024）
uint32_t g_task_received_len = 0; // 已累计接收长度
uint8_t g_task_seq = 0xFF;        // 当前任务序号（无效值0xFF）

// 串口0数据的接收， 当前测试电机遥测值的返回
extern uint8_t data[64];
extern uint32_t ptr;
// 串口1
extern uint8_t data1[64];
extern uint32_t ptr1;
// 串口2
extern uint8_t data2[64];
extern uint32_t ptr2;
// 串口3
extern uint8_t data3[1024];
extern uint32_t ptr3;
// 串口4
extern uint8_t data4[64];
extern uint32_t ptr4;
// 串口5
extern uint8_t data5[64];
extern uint32_t ptr5;
#include <string.h>
#include <string.h>

// 功能：将格式为"AT+XXX=%d\r\n"的字符串写入at_buf
// 参数：at_buf-目标缓冲区，buf_size-缓冲区大小，format-格式字符串(含%d)，param-整数参数
// 返回值：写入的字符数（不包括终止符），失败返回-1
int at_command_format(char *at_buf, size_t buf_size, const char *format, int param)
{
    if (at_buf == NULL || buf_size == 0 || format == NULL)
    {
        Printf("at_command_format arg error\r\n");
        return -1;
    }

    int index = 0;
    size_t format_len = strlen(format);
    int has_percent_d = 0; // 标记是否包含%d

    // 先检查格式字符串中是否包含%d
    for (size_t i = 0; i < format_len - 1; i++)
    {
        if (format[i] == '%' && format[i + 1] == 'd')
        {
            has_percent_d = 1;
            break;
        }
    }
    if (!has_percent_d)
    {
        return -1; // 格式字符串必须包含%d
    }

    // 处理格式字符串，遇到%d时插入数字
    for (size_t i = 0; i < format_len; i++)
    {
        // 检查缓冲区是否已满
        if (index >= buf_size - 1)
        { // 留一个位置给终止符
            return -1;
        }

        // 遇到%d时处理数字参数
        if (format[i] == '%' && i + 1 < format_len && format[i + 1] == 'd')
        {
            int temp[20]; // 存储数字的每一位（逆序）
            int temp_len = 0;
            int num = param;
            int is_negative = 0;

            if (num < 0)
            {
                is_negative = 1;
                num = -num;

                // 检查负号空间
                if (index + 1 >= buf_size - 1)
                {
                    return -1;
                }
                at_buf[index++] = '-';
            }

            // 处理0的情况
            if (num == 0)
            {
                if (index + 1 >= buf_size - 1)
                {
                    return -1;
                }
                at_buf[index++] = '0';
            }
            else
            {
                // 提取数字的每一位（逆序）
                while (num > 0)
                {
                    temp[temp_len++] = num % 10;
                    num /= 10;
                }

                // 检查数字部分空间
                if (index + temp_len >= buf_size - 1)
                {
                    return -1;
                }

                // 逆序写入数字（恢复正确顺序）
                for (int j = temp_len - 1; j >= 0; j--)
                {
                    at_buf[index++] = '0' + temp[j];
                }
            }

            i++; // 跳过'd'
        }
        else
        {
            // 普通字符直接复制
            at_buf[index++] = format[i];
        }
    }

    // 添加终止符
    at_buf[index] = '\0';

    return index; // 返回写入的字符数（不包括终止符）
}

// 使用示例：
// char at_buf[32];
// int param = 5;
// at_command_format(at_buf, sizeof(at_buf), "AT+MODE=%d\r\n", param);  // 生成AT+MODE=5\r\n
// at_command_format(at_buf, sizeof(at_buf), "AT+ADDR=%d\r\n", 100);   // 生成AT+ADDR=100\r\n

// 使用示例：
// char at_buf[32];
// int param = 3;
// at_mode_format(at_buf, sizeof(at_buf), param);
// 等价于 snprintf(at_buf, sizeof(at_buf), "AT+MODE=%d\r\n", param);

// 功能：将格式为"AT+XXX=%d,%d\r\n"的字符串写入at_buf
// 参数：at_buf-目标缓冲区，buf_size-缓冲区大小，format-格式字符串(含两个%d)，
//       param1-第一个整数参数，param2-第二个整数参数
// 返回值：写入的字符数（不包括终止符），失败返回-1
int at_command_format2(char *at_buf, size_t buf_size, const char *format, int param1, int param2)
{
    if (at_buf == NULL || buf_size == 0 || format == NULL)
    {
        return -1;
    }

    int index = 0;
    size_t format_len = strlen(format);
    int percent_d_count = 0; // 统计%d出现的次数

    // 检查格式字符串中是否包含两个%d
    for (size_t i = 0; i < format_len - 1; i++)
    {
        if (format[i] == '%' && format[i + 1] == 'd')
        {
            percent_d_count++;
            i++; // 跳过'd'，避免重复计数
        }
    }
    if (percent_d_count != 2)
    {
        return -1; // 格式字符串必须包含两个%d
    }

    // 用于跟踪当前需要处理的参数
    int current_param = param1;
    int param_used = 0; // 标记第一个参数是否已使用

    // 处理格式字符串，替换%d
    for (size_t i = 0; i < format_len; i++)
    {
        // 检查缓冲区是否已满（预留终止符空间）
        if (index >= buf_size - 1)
        {
            return -1;
        }

        // 遇到%d时处理参数
        if (format[i] == '%' && i + 1 < format_len && format[i + 1] == 'd')
        {
            int temp[20]; // 存储数字的每一位（逆序）
            int temp_len = 0;
            int num = current_param;
            int is_negative = 0;

            if (num < 0)
            {
                is_negative = 1;
                num = -num;

                // 检查负号空间
                if (index + 1 >= buf_size - 1)
                {
                    return -1;
                }
                at_buf[index++] = '-';
            }

            // 处理0的情况
            if (num == 0)
            {
                if (index + 1 >= buf_size - 1)
                {
                    return -1;
                }
                at_buf[index++] = '0';
            }
            else
            {
                // 提取数字的每一位（逆序）
                while (num > 0)
                {
                    temp[temp_len++] = num % 10;
                    num /= 10;
                }

                // 检查数字部分空间
                if (index + temp_len >= buf_size - 1)
                {
                    return -1;
                }

                // 逆序写入数字（恢复正确顺序）
                for (int j = temp_len - 1; j >= 0; j--)
                {
                    at_buf[index++] = '0' + temp[j];
                }
            }

            // 切换到第二个参数
            if (!param_used)
            {
                param_used = 1;
                current_param = param2;
            }

            i++; // 跳过'd'
        }
        else
        {
            // 普通字符直接复制
            at_buf[index++] = format[i];
        }
    }

    // 添加终止符
    at_buf[index] = '\0';

    return index; // 返回写入的字符数（不包括终止符）
}

// 使用示例：
// char at_buf[64];
// at_command_format(at_buf, sizeof(at_buf), "AT+UART=%d,%d\r\n", 115200, 8);
// 生成: "AT+UART=115200,8\r\n"

/**
 * @brief 发送无参数的AT指令
 * @param cmd 无参数AT指令类型（AT_CMD_NONE_xxx枚举）
 * @return 0:发送成功 -1:无效指令 -2:串口发送失败
 */
uint8_t at_send_0param(AtCommandType cmd)
{
    char at_buf[32]; // 存储AT指令字符串（包含结束符）
    uint8_t ret;     // 发送结果返回值

    // 根据指令类型生成对应的AT指令字符串
    switch (cmd)
    {
    case AT_CMD_NONE_IAP:
        strcpy(at_buf, "AT+IAP\r\n");
        // 进入IAP升级模式（谨慎使用，详情参考8.3节串口升级固件注意事项）
        break;
    case AT_CMD_NONE_RESET:
        strcpy(at_buf, "AT+RESET\r\n");
        // 设备重启指令，发送后模块将重启
        break;
    case AT_CMD_NONE_DEFAULT:
        strcpy(at_buf, "AT+DEFAULT\r\n");
        // 配置参数恢复默认值，且设备会自动重启
        break;
    case AT_CMD_NONE_HELP_QUERY:
        strcpy(at_buf, "AT+HELP=?\r\n");
        // 查询AT指令表，返回所有支持的AT指令及说明
        break;
    case AT_CMD_NONE_DEVTYPE_QUERY:
        strcpy(at_buf, "AT+DEVTYPE=?\r\n");
        // 查询模块型号，返回示例：DEVTYPE=E22-400T30D/D
        break;
    case AT_CMD_NONE_FWCODE_QUERY:
        strcpy(at_buf, "AT+FWCODE=?\r\n");
        // 查询固件编码，返回示例：FWCODE=7432-0-10
        break;
    case AT_CMD_NONE_UART_QUERY:
        strcpy(at_buf, "AT+UART=?\r\n");
        // 查询当前波特率和校验位配置，返回示例：AT+UART=3,0（表示9600,8N1）
        break;
    case AT_CMD_NONE_RATE_QUERY:
        strcpy(at_buf, "AT+RATE=?\r\n");
        // 查询当前空中速率配置，返回示例：AT+RATE=7（表示62.5K/15.6K）
        break;
    case AT_CMD_NONE_PACKET_QUERY:
        strcpy(at_buf, "AT+PACKET=?\r\n");
        // 查询当前封包长度配置，返回示例：AT+PACKET=0（表示240字节）
        break;
    case AT_CMD_NONE_WOR_QUERY:
        strcpy(at_buf, "AT+WOR=?\r\n");
        // 查询当前WOR角色配置，返回示例：AT+WOR=0（表示WOR接收）
        break;
    case AT_CMD_NONE_POWER_QUERY:
        strcpy(at_buf, "AT+POWER=?\r\n");
        // 查询当前发送功率配置，返回示例：AT+POWER=0（表示30dBm）
        break;
    case AT_CMD_NONE_TRANS_QUERY:
        strcpy(at_buf, "AT+TRANS=?\r\n");
        // 查询当前发送模式配置，返回示例：AT+TRANS=1（表示定点模式）
        break;
    case AT_CMD_NONE_ROUTER_QUERY:
        strcpy(at_buf, "AT+ROUTER=?\r\n");
        // 查询当前中继模式配置，返回示例：AT+ROUTER=1（表示中继模式开启）
        break;
    case AT_CMD_NONE_LBT_QUERY:
        strcpy(at_buf, "AT+LBT=?\r\n");
        // 查询Listen Before Talk功能开关状态，返回示例：AT+LBT=1（表示开启）
        break;
    case AT_CMD_NONE_ERSSI_QUERY:
        strcpy(at_buf, "AT+ERSSI=?\r\n");
        // 查询环境噪声RSSI开关状态，返回示例：AT+ERSSI=1（表示开启）
        break;
    case AT_CMD_NONE_DRSSI_QUERY:
        strcpy(at_buf, "AT+DRSSI=?\r\n");
        // 查询接收数据RSSI开关状态，返回示例：AT+DRSSI=1（表示开启）
        break;
    case AT_CMD_NONE_ADDR_QUERY:
        strcpy(at_buf, "AT+ADDR=?\r\n");
        // 查询当前模块地址，返回示例：AT+ADDR=1234（表示模块地址为1234）
        break;
    case AT_CMD_NONE_CHANNEL_QUERY:
        strcpy(at_buf, "AT+CHANNEL=?\r\n");
        // 查询当前模块工作信道，返回示例：AT+CHANNEL=23（表示频率为433.125M）
        break;
    case AT_CMD_NONE_NETID_QUERY:
        strcpy(at_buf, "AT+NETID=?\r\n");
        // 查询当前网络ID，返回示例：AT+NETID=2（表示网络ID为2）
        break;
    case AT_CMD_NONE_KEY_QUERY:
        strcpy(at_buf, "AT+KEY=?\r\n");
        // 查询模块密钥（出于安全考虑，不支持读取，返回ERR）
        break;
    case AT_CMD_NONE_DELAY_QUERY:
        strcpy(at_buf, "AT+DELAY=?\r\n");
        // 查询WOR延迟休眠时间，返回示例：AT+DELAY=1000（表示1000ms）
        break;
    case AT_CMD_NONE_SWITCH_QUERY:
        strcpy(at_buf, "AT+SWITCH=?\r\n");
        // 查询软件切换模式开关状态，返回示例：AT+SWITCH=0（表示关闭）
        break;
    case AT_CMD_NONE_MODE_QUERY:
        strcpy(at_buf, "AT+MODE=?\r\n");
        // 查询当前工作模式（所有模式下均可查询），返回示例：AT+MODE=0（表示透传模式）
        break;
    default:
        return -1; // 无效指令类型
    }

    // 通过串口发送AT指令
    ret = uart_send_hex_datas(currentXingjianUart, (uint8_t *)at_buf, strlen(at_buf));
    // 返回发送结果（0表示成功，-2表示串口发送失败）
    return (ret == 0) ? 0 : -2;
}

/**
 * 单参数AT指令发送
 * @param cmd 单参数指令类型（AT_CMD_1PARAM_xxx）
 * @param param 指令参数（整数）
 * @return 0:成功 -1:指令错误 -2:发送失败
 */
uint8_t at_send_1param(AtCommandType cmd, int param)
{
    char at_buf[32]; // 存储带参数的AT指令字符串
    uint8_t ret;     // 发送结果返回值

    // 根据指令类型生成带参数的AT指令字符串
    switch (cmd)
    {
    case AT_CMD_1PARAM_RATE:
        at_command_format(at_buf, sizeof(at_buf), "AT+RATE=%d\r\n", param);
        // 设定空中速率：param为速率编码
        // 400MHz频段：0-2.4K, 3-4.8K, ..., 7-62.5K
        // 230MHz频段：0-3均为2.4K, 4-4.8K, ..., 7-15.6K
        break;
    case AT_CMD_1PARAM_PACKET:
        at_command_format(at_buf, sizeof(at_buf), "AT+PACKET=%d\r\n", param);
        // 设定封包长度：param为长度编码
        // 0-240字节, 1-128字节, 2-64字节, 3-32字节
        break;
    case AT_CMD_1PARAM_WOR:
        at_command_format(at_buf, sizeof(at_buf), "AT+WOR=%d\r\n", param);
        // 设定WOR角色：param为角色类型
        // 0-接收, 1-发送
        break;
    case AT_CMD_1PARAM_POWER:
        at_command_format(at_buf, sizeof(at_buf), "AT+POWER=%d\r\n", param);
        // 设定发送功率：param为功率等级
        // 0-30dBm, 1-27dBm, 2-24dBm, 3-21dBm
        break;
    case AT_CMD_1PARAM_TRANS:
        at_command_format(at_buf, sizeof(at_buf), "AT+TRANS=%d\r\n", param);
        // 设定发送模式：param为模式类型
        // 0-透明模式, 1-定点模式
        break;
    case AT_CMD_1PARAM_ROUTER:
        at_command_format(at_buf, sizeof(at_buf), "AT+ROUTER=%d\r\n", param);
        // 设定中继模式：param为开关状态
        // 0-关闭, 1-开启
        break;
    case AT_CMD_1PARAM_LBT:
        at_command_format(at_buf, sizeof(at_buf), "AT+LBT=%d\r\n", param);
        // 设定LBT功能开关：param为开关状态
        // 0-关闭, 1-开启（Listen Before Talk功能）
        break;
    case AT_CMD_1PARAM_ERSSI:
        at_command_format(at_buf, sizeof(at_buf), "AT+ERSSI=%d\r\n", param);
        // 设定环境噪声RSSI开关：param为开关状态
        // 0-关闭, 1-开启（环境噪声检测功能）
        break;
    case AT_CMD_1PARAM_DRSSI:
        at_command_format(at_buf, sizeof(at_buf), "AT+DRSSI=%d\r\n", param);
        // 设定接收数据RSSI开关：param为开关状态
        // 0-关闭, 1-开启（接收数据的RSSI值输出功能）
        break;
    case AT_CMD_1PARAM_ADDR:
        at_command_format(at_buf, sizeof(at_buf), "AT+ADDR=%d\r\n", param);
        // 设定模块地址：param为地址值（0~65535，十进制）
        break;
    case AT_CMD_1PARAM_CHANNEL:
        at_command_format(at_buf, sizeof(at_buf), "AT+CHANNEL=%d\r\n", param);
        // 设定工作信道：param为信道号（0~83，十进制，对应不同频率）
        break;
    case AT_CMD_1PARAM_NETID:
        at_command_format(at_buf, sizeof(at_buf), "AT+NETID=%d\r\n", param);
        // 设定网络ID：param为网络标识（0~255，十进制）
        break;
    case AT_CMD_1PARAM_KEY:
        at_command_format(at_buf, sizeof(at_buf), "AT+KEY=%d\r\n", param);
        // 设定模块密钥：param为密钥值（0~65535，十进制）
        break;
    case AT_CMD_1PARAM_DELAY:
        at_command_format(at_buf, sizeof(at_buf), "AT+DELAY=%d\r\n", param);
        // 设定WOR延迟休眠时间：param为时间值（0~65535，单位ms）
        break;
    case AT_CMD_1PARAM_SWITCH:
        at_command_format(at_buf, sizeof(at_buf), "AT+SWITCH=%d\r\n", param);
        // 设定软件切换模式开关：param为开关状态
        // 0-关闭, 1-开启（允许软件切换模式）
        break;
    case AT_CMD_1PARAM_MODE:
        at_command_format(at_buf, sizeof(at_buf), "AT+MODE=%d\r\n", param);

        // 切换工作模式：param为模式类型
        // 0-透传模式, 1-WOR模式, 2-配置模式
        break;
    default:
        return -1; // 无效指令
    }
    // 使用示例：
    // char at_buf[32];
    // int param = 5;
    // at_command_format(at_buf, sizeof(at_buf), "AT+MODE=%d\r\n", param);  // 生成AT+MODE=5\r\n
    // at_command_format(at_buf, sizeof(at_buf), "AT+ADDR=%d\r\n", 100);   // 生成AT+ADDR=100\r\n
    // 通过串口发送AT指令
    ret = uart_send_hex_datas(currentXingjianUart, (uint8_t *)at_buf, strlen(at_buf));
    Printf("cmd==%s\r\n", at_buf);
    // 返回发送结果（0表示成功，-2表示串口发送失败）
    return (ret == 0) ? 0 : -2;
}

/**
 * 双参数AT指令发送
 * @param cmd 双参数指令类型（目前仅AT_CMD_2PARAM_UART）
 * @param param1 第一个参数（如波特率）
 * @param param2 第二个参数（如校验位）
 * @return 0:成功 -1:指令错误 -2:发送失败
 */
uint8_t at_send_2param(AtCommandType cmd, int param1, int param2)
{
    char at_buf[32]; // 存储双参数AT指令字符串
    int ret;         // 发送结果返回值

    // 处理双参数指令
    switch (cmd)
    {
    case AT_CMD_2PARAM_UART:
        at_command_format2(at_buf, sizeof(at_buf), "AT+UART=%d,%d\r\n", param1, param2);
        // 设定波特率和校验位：
        // param1为波特率编码（0-1200, 1-2400, ..., 7-115200）
        // param2为校验位编码（0-8N1, 1-8O1, 2-8E1, 3-8N1）
        break;
    default:
        return -1; // 无效指令
    }

    // 通过串口发送AT指令
    ret = uart_send_hex_datas(currentXingjianUart, (uint8_t *)at_buf, strlen(at_buf));
    // 返回发送结果（0表示成功，-2表示串口发送失败）
    return (ret == 0) ? 0 : -2;
}

uint8_t at_send_cmd(AtCommandType cmd, int param1, int param2)
{
    // 检查指令类型并调用对应发送函数
    // 无参数指令：枚举以AT_CMD_NONE_开头，且param1和param2必须为-1
    if (cmd >= AT_CMD_NONE_IAP && cmd <= AT_CMD_NONE_MODE_QUERY)
    {
        // 无参数指令不允许传入有效参数
        if (param1 != -1 || param2 != -1)
        {
            return -1; // 参数错误
        }
        return at_send_0param(cmd);
    }
    // 单参数指令：枚举以AT_CMD_1PARAM_开头，且param2必须为-1
    else if (cmd >= AT_CMD_1PARAM_RATE && cmd <= AT_CMD_1PARAM_MODE)
    {
        // 单参数指令的第二个参数必须为-1
        if (param2 != -1)
        {
            return -1; // 参数错误
        }
        return at_send_1param(cmd, param1);
    }
    // 双参数指令：仅AT_CMD_2PARAM_UART
    else if (cmd == AT_CMD_2PARAM_UART)
    {
        // 双参数指令需传入有效参数（param1和param2不为-1）
        if (param1 == -1 || param2 == -1)
        {
            return -1; // 参数错误
        }
        return at_send_2param(cmd, param1, param2);
    }
    // 无效指令类型
    else
    {
        return -1; // 指令错误
    }
}

/**
 * @brief 星间模块复位
 *
 * @return int
 */
int xingjian_reset(uint8_t xingjianNum)
{
    uint8_t ret;
    if (xingjianNum == 0)
    {
        currentXingjianUart = USART1;                 // 选择星间模块0对应的串口
        ret = at_send_cmd(AT_CMD_NONE_RESET, -1, -1); // 发送复位指令
        Printf("xingjian_reset: currentXingjianUart = USART1.\r\n");
        if (ret != 0)
        {
            Printf("xingjian_reset: currentXingjianUart = USART1 error.\r\n");
            return ret;
        }
    }
    else if (xingjianNum == 1)
    {
        currentXingjianUart = USART3;                 // 选择星间模块1对应的串口
        ret = at_send_cmd(AT_CMD_NONE_RESET, -1, -1); // 发送复位指令
        Printf("xingjian_reset: currentXingjianUart = USART3.\r\n");
        if (ret != 0)
        {
            Printf("xingjian_reset: currentXingjianUart = USART3 error.\r\n");
            return ret;
        }
    }
    else
    {
        printf("xingjian_reset error, xingjianNum=%d\r\n", xingjianNum);
        return -1; // 无效的星间模块编号
    }
}

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
int xingjian_change_config_mode(uint8_t xingjianNum, uint8_t mode)
{
    if (xingjianNum == 0)
    {
        // PB11,PB12
        switch (mode)
        {
        case 0:
            GPIO_WriteBits(GPIOB, GPIO_Pin_11, GPIO_OCtrl_Vol);
            GPIO_WriteBits(GPIOB, GPIO_Pin_12, GPIO_OCtrl_Vol);
            break;
        case 1:
            GPIO_WriteBits(GPIOB, GPIO_Pin_11, GPIO_OCtrl_Vol);
            GPIO_WriteBits(GPIOB, GPIO_Pin_12, GPIO_OCtrl_Voh);
            break;
        case 2:
            GPIO_WriteBits(GPIOB, GPIO_Pin_11, GPIO_OCtrl_Voh);
            GPIO_WriteBits(GPIOB, GPIO_Pin_12, GPIO_OCtrl_Vol);
            break;
        case 3:
            GPIO_WriteBits(GPIOB, GPIO_Pin_11, GPIO_OCtrl_Voh);
            GPIO_WriteBits(GPIOB, GPIO_Pin_12, GPIO_OCtrl_Voh);
            break;

        default:
            printf("xingjian_change_config_mode error, mode=%d\r\n", mode);
            return -1;
        }
    }
    else if (xingjianNum == 1)
    {
        // PB13,PB14
        switch (mode)
        {
        case 0:
            GPIO_WriteBits(GPIOB, GPIO_Pin_13, GPIO_OCtrl_Vol);
            GPIO_WriteBits(GPIOB, GPIO_Pin_14, GPIO_OCtrl_Vol);
            break;
        case 1:
            GPIO_WriteBits(GPIOB, GPIO_Pin_13, GPIO_OCtrl_Vol);
            GPIO_WriteBits(GPIOB, GPIO_Pin_14, GPIO_OCtrl_Voh);
            break;
        case 2:
            GPIO_WriteBits(GPIOB, GPIO_Pin_13, GPIO_OCtrl_Voh);
            GPIO_WriteBits(GPIOB, GPIO_Pin_14, GPIO_OCtrl_Vol);
            break;
        case 3:
            GPIO_WriteBits(GPIOB, GPIO_Pin_13, GPIO_OCtrl_Voh);
            GPIO_WriteBits(GPIOB, GPIO_Pin_14, GPIO_OCtrl_Voh);
            break;

        default:
            printf("xingjian_change_config_mode error, mode=%d\r\n", mode);
            return -1;
        }
    }
    else
    {

        printf("xingjian_change_config_mode error, xingjianNum=%d\r\n", xingjianNum);
        return -1; // 无效的星间模块编号
    }
}

/**
 * @brief Parse AT command response and fill configuration struct
 * @param config Pointer to canfdInterstellarModuleConfig struct
 * @param response Raw response string from module
 * @param cmd Corresponding AT command type
 */
void parse_config_response(canfdInterstellarModuleConfig *config, char *response, AtCommandType cmd)
{
    if (!config || !response)
    {
        Printf("parse_config_response arg error\r\n");
        return;
    }
    // Parse response based on command type
    switch (cmd)
    {
    case AT_CMD_NONE_MODE_QUERY:
        // Response format: "AT+MODE=0" (0-透传模式, 1-WOR模式, 2-配置模式)
        config->working_mode = *response; // 1字节数据
        break;

    case AT_CMD_NONE_ADDR_QUERY:
        // 对应AT+ADDR=?：查询当前模块地址，返回示例：AT+ADDR=1234
        memcpy(&config->module_address, response, 2); // 2字节数据
        break;

    case AT_CMD_NONE_NETID_QUERY:
        // 对应AT+NETID=?：查询当前网络ID，返回示例：AT+NETID=2
        config->network_address = *response; // 1字节数据
        break;

    case AT_CMD_NONE_UART_QUERY:
        // Response format: "AT+UART=3,0" (3=115200, 0=8N1)
        config->serial_baud_rate = *response; // 第一个1字节数据
        config->parity_bit = *(response + 2); // 跳过逗号，第二个1字节数据
        break;

    case AT_CMD_NONE_RATE_QUERY:
        // Response format: "AT+RATE=7" (7=62.5K for 400MHz, 15.6K for 230MHz)
        config->airspeed_400mhz = *response; // 1字节数据
        config->airspeed_230mhz = *response; // 1字节数据（保持一致）
        break;

    case AT_CMD_NONE_CHANNEL_QUERY:
        // Response format: "AT+CHANNEL=23" (0~83)
        config->channel = *response; // 1字节数据
        break;

    case AT_CMD_NONE_PACKET_QUERY:
        // Response format: "AT+PACKET=0" (0=240B, 1=128B, etc.)
        config->packet_length = *response; // 1字节数据
        break;

    case AT_CMD_NONE_WOR_QUERY:
        // Response format: "AT+WOR=0" (0=receive, 1=transmit)
        config->wor_role = *response; // 1字节数据
        break;

    case AT_CMD_NONE_POWER_QUERY:
        // Response format: "AT+POWER=0" (0=30dBm, 1=27dBm, etc.)
        config->tx_power = *response; // 1字节数据
        break;

    case AT_CMD_NONE_TRANS_QUERY:
        // Response format: "AT+TRANS=1" (0=transparent, 1=fixed-point)
        config->transmission_mode = *response; // 1字节数据
        break;

    case AT_CMD_NONE_ROUTER_QUERY:
        // Response format: "AT+ROUTER=1" (0=disable, 1=enable)
        config->relay_mode = *response; // 1字节数据
        break;

    case AT_CMD_NONE_LBT_QUERY:
        // Response format: "AT+LBT=1" (0=disable, 1=enable)
        config->listen_before_talk = *response; // 1字节数据
        break;

    case AT_CMD_NONE_ERSSI_QUERY:
        // Response format: "AT+ERSSI=1" (0=disable, 1=enable)
        config->env_rssi = *response; // 1字节数据
        break;

    case AT_CMD_NONE_DRSSI_QUERY:
        // Response format: "AT+DRSSI=1" (0=disable, 1=enable)
        config->data_rssi = *response; // 1字节数据
        break;

    case AT_CMD_NONE_KEY_QUERY:
        // Response format: "AT+KEY=1234" (0~65535)
        memcpy(&config->encryption_key, response, 2); // 2字节数据
        break;

    case AT_CMD_NONE_DELAY_QUERY:
        // Response format: "AT+DELAY=1000" (0~65535 ms)
        memcpy(&config->wor_sleep_delay, response, 2); // 2字节数据
        break;

    default:
        break;
    }
}

/**
 * @brief Query module config via AT commands and fill into struct
 * @param xingjianNum Module number (0 or 1)
 * @param config Pointer to canfdInterstellarModuleConfig struct to fill
 * @return 0: success -1: invalid number -2: UART error
 */
int xingjian_get_config(uint8_t xingjianNum, canfdInterstellarModuleConfig *config)
{
    if (!config)
    {
        Printf("Invalid config struct pointer\r\n");
        return -1;
    }

    uint16_t count = 0;

    // Initialize struct to default values
    // memset(config, 0, sizeof(canfdInterstellarModuleConfig));
    config->working_status = 1; // Assume normal working status (customize as needed)

    // Save current UART and switch to target module
    USART_TypeDef *prevUart = currentXingjianUart;
    if (xingjianNum == 0)
    {
        currentXingjianUart = USART1;
    }
    else if (xingjianNum == 1)
    {
        currentXingjianUart = USART3;
    }
    else
    {
        Printf("Invalid module number: %d\r\n", xingjianNum);
        return -1;
    }

    Printf("\n===== Querying module %d full config =====\r\n", xingjianNum);

    // Define query commands and their types (all =?结尾的查询指令)
    AtCommandType query_cmds[] = {
        AT_CMD_NONE_MODE_QUERY,    // 工作模式
        AT_CMD_NONE_ADDR_QUERY,    // 模块地址
        AT_CMD_NONE_NETID_QUERY,   // 网络地址
        AT_CMD_NONE_UART_QUERY,    // 串口波特率+校验位
        AT_CMD_NONE_RATE_QUERY,    // 空速
        AT_CMD_NONE_CHANNEL_QUERY, // 信道
        AT_CMD_NONE_PACKET_QUERY,  // 封包长度
        AT_CMD_NONE_WOR_QUERY,     // WOR角色
        AT_CMD_NONE_POWER_QUERY,   // 发射功率
        AT_CMD_NONE_TRANS_QUERY,   // 传输模式
        AT_CMD_NONE_ROUTER_QUERY,  // 中继模式
        AT_CMD_NONE_LBT_QUERY,     // LBT功能
        AT_CMD_NONE_ERSSI_QUERY,   // 环境RSSI
        AT_CMD_NONE_DRSSI_QUERY,   // 数据RSSI
        AT_CMD_NONE_KEY_QUERY,     // 加密密钥
        AT_CMD_NONE_DELAY_QUERY    // WOR休眠延迟
    };
    uint8_t cmd_count = sizeof(query_cmds) / sizeof(AtCommandType);

    // Send each query command and parse response
    for (uint8_t i = 0; i < cmd_count; i++)
    {
        // Clear response buffer
        xingjian_response_ptr = 0;
        memset(xingjian_response_buffer, 0, sizeof(xingjian_response_buffer));

        // Send query command (all are 0-parameter commands with =?)
        Printf("Sending query: %d... ", query_cmds[i]);
        if (at_send_cmd(query_cmds[i], -1, -1) != 0)
        {
            Printf("send failed\r\n");
            continue;
        }

        // Wait for response and process
        delay_ms(200); // Adjust delay based on module response speed
        count = 0;
        while (1)
        {
            // 星间模块
            if (ptr3 >= 1)
            {
                Printf("ptr3 recv data! len=%d\r\n", ptr3);
                for (int i = 0; i < ptr3; i++)
                    Printf(" 0x%x", data3[i]);
                Printf("\r\n");
                // 保存数据到响应缓冲区
                memcpy(xingjian_response_buffer, data3, ptr3);
                ptr3 = 0;
                break;
            }
            delay_ms(20);
            if (count++ >= 0xa0)
            {
                Printf("not recv xingjian yaoce\r\n", ptr3);
                break;
            }
        }

        // Parse response and fill struct
        parse_config_response(config, (char *)xingjian_response_buffer, query_cmds[i]);
        Printf("parsed\r\n");
    }

    // Restore UART and complete
    // currentXingjianUart = prevUart;
    Printf("===== Module %d config query finished =====\r\n", xingjianNum);
    return 0;
}

// 透传 将数据转发到星间模块
uint8_t obc_tran_data_xingjian(uint8_t *data, uint16_t dataLen)
{
    uint8_t ret = uart_send_hex_datas(currentXingjianUart, data, dataLen);
    return ret;
}

// 透传 将数据转发到OBC
uint8_t xingjian_tran_data_obc(uint8_t canChan, uint8_t *data, uint16_t dataLen)
{
    uint8_t *tmp = (uint8_t *)malloc(dataLen + 4);
    // memset(tmp,0,dataLen);
    
    uint16_t *p = (uint16_t *)&tmp[0];
    tmp[2] = 0x35;
    tmp[3] = 0x0a;
    if(dataLen > 62) //就是复合帧
    {
        *p = dataLen;
        memcpy(&tmp[4], data, dataLen);
        dataLen += 4;
    }
    else
    {
        memcpy(&tmp[2], data, dataLen);
        dataLen += 2;
    }

    uint8_t ret = 0;
    
    if (canChan == 0)
        ret = canfd_send_all_data0(tmp, dataLen);
    else
        ret = canfd_send_all_data(tmp, dataLen );

    free(tmp);
    return ret;
}

//======================金鹏代码===============================================
// 分片透传封装函数
int try_transparent_send()
{
    if (g_transparent_task.received_len == 0)
        return 0;
    // 满1024字节或最后一包
    if (g_transparent_task.received_len == 1024 || (g_task_received_len + g_transparent_task.received_len) == g_task_total_len)
    {
        uint8_t send_buf[1024 + 5];
        send_buf[0] = (g_transparent_task.received_len >> 8) & 0xFF;
        send_buf[1] = g_transparent_task.received_len & 0xFF;
        send_buf[2] = g_transparent_task.data_type;
        send_buf[3] = g_transparent_task.data_encoding;
        send_buf[4] = g_transparent_task.task_seq;
        memcpy(&send_buf[5], g_transparent_task.buffer, g_transparent_task.received_len);
        int ret = uart_send_hex_datas(USART1, &send_buf[5], g_transparent_task.received_len);
        if (ret != 0)
        {
            Printf("透传文件数据转发失败，串口发送错误\r\n");
            return -3;
        }
        g_task_received_len += g_transparent_task.received_len;
        g_transparent_task.received_len = 0;
    }
    return 0;
}

/**
 * @brief 组包并转发透传文件数据到星间模块
 * @param file_data CANFD每帧数据指针
 * @param data_len  CANFD每帧数据长度
 * @return 0:成功, 1:等待更多帧, -1:数据格式错误, -2:数据长度无效, -3:串口发送失败
 */
int8_t forward_transparent_file_data(uint8_t *file_data, uint16_t data_len)
{
    if (file_data == NULL || data_len < 3)
    {
        Printf("透传数据格式错误：数据为空或长度不足\r\n");
        return -1;
    }
    if (file_data[0] != 0x05 || file_data[1] != 0x0a)
    {
        Printf("透传数据格式错误：缺少0x05 0x0a头部\r\n");
        return -1;
    }
    uint8_t frame_type = file_data[2];

    if (frame_type == 0xEA)
    {
        // 起始帧
        if (data_len < 8)
        {
            Printf("起始帧长度不足\r\n");
            return -1;
        }
        uint32_t total_len = (file_data[3] << 8) | file_data[4];
        uint8_t data_type = file_data[5];
        uint8_t data_encoding = file_data[6];
        uint8_t task_seq = file_data[7];
        uint16_t payload_len = data_len - 8;

        // 新任务或分片起始
        if (g_task_seq != task_seq || g_task_total_len == 0 || g_task_received_len == g_task_total_len)
        {
            // 新任务或上次已完成，重置
            g_task_seq = task_seq;
            g_task_total_len = total_len;
            g_task_received_len = 0;
        }

        // 检查本分片最大可缓存数据
        if (payload_len > 0)
        {
            uint16_t copy_len = payload_len;
            if (copy_len > 1024)
                copy_len = 1024;
            memcpy(g_transparent_task.buffer, &file_data[8], copy_len);
            g_transparent_task.data_type = data_type;
            g_transparent_task.data_encoding = data_encoding;
            g_transparent_task.task_seq = task_seq;
            g_transparent_task.total_len = copy_len;
            g_transparent_task.received_len = copy_len;
        }
        else
        {
            g_transparent_task.received_len = 0;
        }

        int ret = try_transparent_send();
        if (ret < 0)
            return ret;
        Printf("起始帧: 任务序号=%d, 总长度=%ld, 首帧数据=%d, 已累计=%ld\r\n",
               task_seq, g_task_total_len, payload_len, g_task_received_len);
    }
    else if (frame_type == 0xED)
    {
        // 续帧
        if (data_len < 5)
        {
            Printf("续帧长度不足\r\n");
            return -1;
        }
        uint8_t task_seq = file_data[3];
        if (g_task_seq != task_seq)
        {
            Printf("续帧任务序号不匹配或无起始帧\r\n");
            return -1;
        }
        uint16_t payload_len = data_len - 4;
        uint16_t remain = 1024 - g_transparent_task.received_len;
        uint16_t copy_len = (payload_len > remain) ? remain : payload_len;
        memcpy(&g_transparent_task.buffer[g_transparent_task.received_len], &file_data[4], copy_len);
        g_transparent_task.received_len += copy_len;

        int ret = try_transparent_send();
        if (ret < 0)
            return ret;
        Printf("续帧: 任务序号=%d, 本帧数据=%d, 已累计=%ld\r\n",
               task_seq, payload_len, g_task_received_len);
    }
    else
    {
        Printf("未知帧类型: 0x%02X\r\n", frame_type);
        return -1;
    }

    // 检查是否全部收齐
    if (g_task_received_len == g_task_total_len)
    {
        Printf("全部数据接收并透传完成，总长度=%ld\r\n", g_task_total_len);
        g_task_total_len = 0;
        g_task_received_len = 0;
        g_task_seq = 0xFF;
        return 0;
    }
    return 1;
}

// 星间模块透传数据协议解析与CANFD分帧发送
void xj_transparent_data_parse_and_send()
{
    while (xj_rx_read_ptr != xj_rx_write_ptr)
    {
        uint16_t remain = (xj_rx_write_ptr >= xj_rx_read_ptr) ? (xj_rx_write_ptr - xj_rx_read_ptr) : (XJ_RX_BUFFER_SIZE - xj_rx_read_ptr + xj_rx_write_ptr);

        // 首帧
        if (!xj_file_receiving && remain >= 8)
        {
            if (xj_rx_buffer[xj_rx_read_ptr] == 0x35 && xj_rx_buffer[(xj_rx_read_ptr + 1) % XJ_RX_BUFFER_SIZE] == 0x09 &&
                xj_rx_buffer[(xj_rx_read_ptr + 2) % XJ_RX_BUFFER_SIZE] == 0xEA)
            {
                uint16_t idx = (xj_rx_read_ptr + 3) % XJ_RX_BUFFER_SIZE;
                uint16_t total_len = (xj_rx_buffer[idx] << 8) | xj_rx_buffer[(idx + 1) % XJ_RX_BUFFER_SIZE];
                uint8_t data_type = xj_rx_buffer[(idx + 2) % XJ_RX_BUFFER_SIZE];
                uint8_t data_encoding = xj_rx_buffer[(idx + 3) % XJ_RX_BUFFER_SIZE];
                uint8_t task_seq = xj_rx_buffer[(idx + 4) % XJ_RX_BUFFER_SIZE];
                uint16_t data_start = (idx + 5) % XJ_RX_BUFFER_SIZE;
                uint16_t data_payload = remain - 8;
                if (data_payload > total_len)
                    data_payload = total_len;
                for (uint16_t i = 0; i < data_payload; ++i)
                    xj_file_buffer[i] = xj_rx_buffer[(data_start + i) % XJ_RX_BUFFER_SIZE];
                xj_file_total_len = total_len;
                xj_file_received_len = data_payload;
                xj_file_task_seq = task_seq;
                xj_file_data_type = data_type;
                xj_file_data_encoding = data_encoding;
                xj_file_receiving = 1;
                xj_rx_read_ptr = (data_start + data_payload) % XJ_RX_BUFFER_SIZE;
                continue;
            }
            else
            {
                xj_rx_read_ptr = (xj_rx_read_ptr + 1) % XJ_RX_BUFFER_SIZE;
                continue;
            }
        }
        // 续帧
        else if (xj_file_receiving && remain >= 4)
        {
            if (xj_rx_buffer[xj_rx_read_ptr] == 0x35 && xj_rx_buffer[(xj_rx_read_ptr + 1) % XJ_RX_BUFFER_SIZE] == 0x02 &&
                xj_rx_buffer[(xj_rx_read_ptr + 2) % XJ_RX_BUFFER_SIZE] == 0xED)
            {
                uint8_t task_seq = xj_rx_buffer[(xj_rx_read_ptr + 3) % XJ_RX_BUFFER_SIZE];
                if (task_seq != xj_file_task_seq)
                {
                    xj_rx_read_ptr = (xj_rx_read_ptr + 1) % XJ_RX_BUFFER_SIZE;
                    continue;
                }
                uint16_t data_start = (xj_rx_read_ptr + 4) % XJ_RX_BUFFER_SIZE;
                uint16_t data_payload = remain - 4;
                uint32_t left = xj_file_total_len - xj_file_received_len;
                if (data_payload > left)
                    data_payload = left;
                for (uint16_t i = 0; i < data_payload; ++i)
                    xj_file_buffer[xj_file_received_len + i] = xj_rx_buffer[(data_start + i) % XJ_RX_BUFFER_SIZE];
                xj_file_received_len += data_payload;
                xj_rx_read_ptr = (data_start + data_payload) % XJ_RX_BUFFER_SIZE;
                continue;
            }
            else
            {
                xj_rx_read_ptr = (xj_rx_read_ptr + 1) % XJ_RX_BUFFER_SIZE;
                continue;
            }
        }
        else
        {
            break;
        }
    }
    // 组包完成，分帧通过CANFD发送给主控
    if (xj_file_receiving && xj_file_received_len == xj_file_total_len)
    {
        uint32_t total = xj_file_total_len;
        uint32_t sent = 0;
        uint8_t canfd_buf[64];
        // 首帧
        canfd_buf[0] = 0x05;
        canfd_buf[1] = 0x0a;
        canfd_buf[2] = 0xEA;
        canfd_buf[3] = (total >> 8) & 0xFF;
        canfd_buf[4] = total & 0xFF;
        canfd_buf[5] = xj_file_data_type;
        canfd_buf[6] = xj_file_data_encoding;
        canfd_buf[7] = xj_file_task_seq;
        uint16_t first_payload = (total > 56) ? 56 : total;
        memcpy(&canfd_buf[8], xj_file_buffer, first_payload);
        canfd_send_all_data(canfd_buf, 8 + first_payload);
        sent += first_payload;
        // 续帧
        while (sent < total)
        {
            canfd_buf[0] = 0x05;
            canfd_buf[1] = 0x0a;
            canfd_buf[2] = 0xED;
            canfd_buf[3] = xj_file_task_seq;
            uint16_t payload = (total - sent > 60) ? 60 : (total - sent);
            memcpy(&canfd_buf[4], &xj_file_buffer[sent], payload);
            canfd_send_all_data(canfd_buf, 4 + payload);
            sent += payload;
        }
        xj_file_receiving = 0;
        xj_file_total_len = 0;
        xj_file_received_len = 0;
        xj_file_task_seq = 0xFF;
    }
}

/*
 * Function:        xingjian_response_process
 * Description:     处理星间模块响应数据
 * Param:           None.
 * Return:          None.
 */
void xingjian_response_process(void)
{
    // 检查是否有数据需要处理

    Printf("USART3 received data, len=%d\r\n", ptr3);

    // 将接收到的数据复制到星间模块响应缓冲区
    for (uint32_t i = 0; i < ptr3; i++)
    {
        if (xingjian_response_ptr < sizeof(xingjian_response_buffer) - 1)
        {
            xingjian_response_buffer[xingjian_response_ptr++] = data3[i];
            xingjian_response_buffer[xingjian_response_ptr] = '\0'; // 添加字符串结束符

            // 检查是否接收到"=OK"响应
            if (strstr((char *)xingjian_response_buffer, "=OK") != NULL)
            {
                xingjian_config_ok_flag = 1; // 设置配置成功标志位
                Printf("星间模块配置成功响应: %s\r\n", xingjian_response_buffer);
                xingjian_response_ptr = 0; // 重置接收指针
                memset(xingjian_response_buffer, 0, sizeof(xingjian_response_buffer));
            }
            // 检查是否接收到"AT+MODE="响应（工作模式配置确认）
            else if (strncmp((char *)xingjian_response_buffer, "AT+MODE=", 8) == 0)
            {
                xingjian_mode_config_ok_flag = 1; // 设置工作模式配置成功标志位
                Printf("星间模块工作模式配置成功响应: %s\r\n", xingjian_response_buffer);
                xingjian_response_ptr = 0; // 重置接收指针
                memset(xingjian_response_buffer, 0, sizeof(xingjian_response_buffer));
            }
        }
        else
        {
            // 缓冲区溢出，重置
            Printf("星间模块响应缓冲区溢出，重置\r\n");
            xingjian_response_ptr = 0;
            memset(xingjian_response_buffer, 0, sizeof(xingjian_response_buffer));
            break;
        }
    }

    // 清空接收缓冲区
    ptr3 = 0;
    memset(data3, 0, sizeof(data3));
}