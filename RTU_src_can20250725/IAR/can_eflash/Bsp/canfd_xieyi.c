/* Includes ------------------------------------------------------------------*/
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_usart.h"
#include "as32x601_canfd.h"
#include "as32x601_plic.h"
#include "canfd_xieyi.h"
#include "gpio.h"
#include "myprintf.h"
#include "adc.h"
#include "uart_xingjian.h"
#include "uart_dianji.h"
#include "print.h"

// 对外8路gpio控制保存的当前状态
extern uint8_t out_gpio_status;
// 大电流配电使能
extern uint8_t large_electric_status;
// 小电流配电使能
extern uint16_t small_electric_status;
// 电源输出使能控制
extern uint8_t power_gpio_status;

extern getADCValue ADCValue; // 获取到的所有ADC值的缓存

extern uint8_t canfd_sel;
extern uint8_t canfd_M_sel;

canfdYC_all canfd_yc_all;         // 遥测数据
canfdDJ_all frame;                // 遥测数据
canfdDJ_all_t frame_t;                // 电机遥测数据，直接转发数据不进行单个赋值
FiveWireTelemetryFrame wireframe; // 遥测数据

volatile static uint8_t rqu_id;
volatile static uint8_t current_count_id0 = 0;
volatile static uint8_t current_count_id1 = 0;

extern uint8_t Receive_data1[64];
extern uint8_t Receive_data0[64];

/*
volatile static  uint8_t A_CAN_YC_count1 = 1;      // A通道遥测请求计数
volatile static  uint8_t A_CAN_ZQ_count1= 1 ;      // A通道正确帧计数
volatile static  uint8_t A_CAN_CW_count1= 1;      // A通道错误帧计数
volatile static  uint8_t A_CAN_CUTTENT_CMD1= 1;   // 最近执行指令码
volatile static  uint8_t A_CAN_reset_num1= 0;     // 复位计数
volatile static  uint8_t A_CAN_reset1= 0;         // 复位原因
volatile static  uint8_t A_CAN_send_errornum1= 0; // 发送错误计数
volatile static  uint8_t A_CAN_recv_errornum1= 0; // 接收错误计数
volatile static uint8_t B_CAN_YC_count0= 0;      // B通道遥测请求计数
volatile static uint8_t B_CAN_ZQ_count0= 0;      // B通道正确帧计数
volatile static uint8_t B_CAN_CW_count0= 0;      // B通道错误帧计数
volatile static uint8_t B_CAN_CUTTENT_CMD0= 0;   // 最近执行指令码
volatile static uint8_t B_CAN_reset_num0= 0;     // 复位计数
volatile static uint8_t B_CAN_reset0= 0;         // 复位原因
volatile static uint8_t B_CAN_send_errornum0= 0; // 发送错误计数
volatile static uint8_t B_CAN_recv_errornum0= 0; // 接收错误计数
*/

uint8_t A_CAN_YC_count1 = 0;                      // A通道遥测请求计数
uint8_t A_CAN_ZQ_count1 = 0;                      // A通道正确帧计数
uint8_t A_CAN_CW_count1 = 0;                      // A通道错误帧计数
uint8_t A_CAN_CUTTENT_CMD1 = 0;                   // 最近执行指令码
volatile static uint8_t A_CAN_reset_num1 = 0;     // 复位计数
volatile static uint8_t A_CAN_reset1 = 0;         // 复位原因
volatile static uint8_t A_CAN_send_errornum1 = 0; // 发送错误计数
volatile static uint8_t A_CAN_recv_errornum1 = 0; // 接收错误计数
uint8_t B_CAN_YC_count0 = 0;                      // B通道遥测请求计数
uint8_t B_CAN_ZQ_count0 = 0;                      // B通道正确帧计数
uint8_t B_CAN_CW_count0 = 0;                      // B通道错误帧计数
uint8_t B_CAN_CUTTENT_CMD0 = 0;                   // 最近执行指令码
volatile static uint8_t B_CAN_reset_num0 = 0;     // 复位计数
volatile static uint8_t B_CAN_reset0 = 0;         // 复位原因
volatile static uint8_t B_CAN_send_errornum0 = 0; // 发送错误计数
volatile static uint8_t B_CAN_recv_errornum0 = 0; // 接收错误计数

uint16_t swap_byte(uint16_t value)
{
    return (((value & 0xff) << 8) | ((value) >> 8) & 0xff);
}

volatile uint8_t g_frame_type0;
volatile uint8_t g_frame_count0;
volatile uint8_t g_frame_type1;
volatile uint8_t g_frame_count1;

void g_CANFD1_Frame_rev(void)
{
    uint32_t can_id = 0;
    uint8_t frame_type = g_frame_type1;
    uint8_t frame_count = g_frame_count1;
    can_id |= ((uint32_t)(0x17) << 21);
    can_id |= ((uint32_t)(0x00) << 13);
    can_id |= ((uint32_t)(frame_type & 0x0f) << 9);
    can_id |= ((uint32_t)(0x00) << 8);
    can_id |= (frame_count & 0xff);

    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;

    /* Set the setting ID and setting mode */
    if (canfd_sel)
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;
    }
    else
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = can_id;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_64B;
    CANFD_FrameInit(CANFD1, TB1, &CANFD_TXFrameStruct);

    if (canfd_sel)
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;
    }
    else
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = can_id;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_32B;
    CANFD_FrameInit(CANFD1, TB0, &CANFD_TXFrameStruct);
}

void g_CANFD0_Frame_rev(void)
{

    uint32_t can_id = 0;
    uint8_t frame_type = g_frame_type0;
    uint8_t frame_count = g_frame_count0;
    can_id |= ((uint32_t)(0x17) << 21);
    can_id |= ((uint32_t)(0x00) << 13);
    can_id |= ((uint32_t)(frame_type & 0x0f) << 9);
    can_id |= ((uint32_t)(0x00) << 8);
    can_id |= (frame_count & 0xff);

    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;

    /* Set the setting ID and setting mode */
    if (canfd_sel)
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;
    }
    else
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = can_id;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_64B;
    CANFD_FrameInit(CANFD0, TB1, &CANFD_TXFrameStruct);

    if (canfd_sel)
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;
    }
    else
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = can_id;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_32B;
    CANFD_FrameInit(CANFD0, TB0, &CANFD_TXFrameStruct);
}

void CANFD0_Frame_rev(uint8_t frame_type, uint8_t frame_count)
{
    uint32_t can_id = 0;
    can_id |= ((uint32_t)(0x17) << 21);
    can_id |= ((uint32_t)(0x00) << 13);
    can_id |= ((uint32_t)(frame_type & 0x0f) << 9);
    can_id |= ((uint32_t)(0x00) << 8);
    can_id |= (frame_count & 0xff);

    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;

    /* Set the setting ID and setting mode */
    if (canfd_sel)
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;
    }
    else
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = can_id;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_64B;
    CANFD_FrameInit(CANFD0, TB1, &CANFD_TXFrameStruct);

    if (canfd_sel)
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;
    }
    else
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = can_id;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_32B;
    CANFD_FrameInit(CANFD0, TB0, &CANFD_TXFrameStruct);
}
void CANFD1_Frame_rev(uint8_t frame_type, uint8_t frame_count)
{
    uint32_t can_id = 0;
    can_id |= ((uint32_t)(0x17) << 21);
    can_id |= ((uint32_t)(0x00) << 13);
    can_id |= ((uint32_t)(frame_type & 0x0f) << 9);
    can_id |= ((uint32_t)(0x00) << 8);
    can_id |= (frame_count & 0xff);

    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;

    /* Set the setting ID and setting mode */
    if (canfd_sel)
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;
    }
    else
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = can_id;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_64B;
    CANFD_FrameInit(CANFD1, TB1, &CANFD_TXFrameStruct);

    if (canfd_sel)
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;
    }
    else
    {
        CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = can_id;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_32B;
    CANFD_FrameInit(CANFD1, TB0, &CANFD_TXFrameStruct);
}

// 遥测数据组包
void canfd_build_yaoce_pack()
{
    memset(&canfd_yc_all, 0, sizeof(canfd_yc_all)); // 初始化遥测数据结构体

    // 填充固定头字段
    canfd_yc_all.head.dataLength = swap_byte(sizeof(canfd_yc_all) - sizeof(canfd_yc_all.head.dataType) * 2); // 数据长度
    canfd_yc_all.head.dataType = 0x35;                                                                       // 数据类型
    canfd_yc_all.head.dataNum = 0x01;                                                                        // 数据编码

    // 填充固定canfd信息数据

    canfd_yc_all.gdCanInfo.A_CAN_YC_count = A_CAN_YC_count1;
    canfd_yc_all.gdCanInfo.A_CAN_ZQ_count = A_CAN_ZQ_count1;
    canfd_yc_all.gdCanInfo.A_CAN_CW_count = A_CAN_CW_count1;
    canfd_yc_all.gdCanInfo.A_CAN_CUTTENT_CMD = A_CAN_CUTTENT_CMD1;
    canfd_yc_all.gdCanInfo.A_CAN_reset_num = A_CAN_reset_num1;
    canfd_yc_all.gdCanInfo.A_CAN_reset = 0;
    canfd_yc_all.gdCanInfo.A_CAN_send_errornum = 0;
    canfd_yc_all.gdCanInfo.A_CAN_recv_errornum = 0;

    canfd_yc_all.gdCanInfo.B_CAN_YC_count = B_CAN_YC_count0;
    canfd_yc_all.gdCanInfo.B_CAN_ZQ_count = B_CAN_ZQ_count0;
    canfd_yc_all.gdCanInfo.B_CAN_CW_count = B_CAN_CW_count0;
    canfd_yc_all.gdCanInfo.B_CAN_CUTTENT_CMD = B_CAN_CUTTENT_CMD0;
    canfd_yc_all.gdCanInfo.B_CAN_reset_num = A_CAN_reset_num1;
    canfd_yc_all.gdCanInfo.B_CAN_reset = 0;
    canfd_yc_all.gdCanInfo.B_CAN_send_errornum = 0;
    canfd_yc_all.gdCanInfo.B_CAN_recv_errornum = 0;

    // 填充遥测数据
    canfd_yc_all.ycData.power_ctr = power_gpio_status;              // 电源输出使能控制
    canfd_yc_all.ycData.out_gpio_ctrl = out_gpio_status;            // 对外8路GPIO输出状态
    canfd_yc_all.ycData.large_electric_ctr = large_electric_status; // 大电流配电使能
    canfd_yc_all.ycData.small_electric_ctr = small_electric_status; // 小电流配电使能
    // 填充16路对外采集温度或电压模拟量

    for (int i = 0; i < 16; i++)
    {
        canfd_yc_all.ycData.out_adc_data[i] = ADCValue.outValue[i]; // 示例数据，替换为实际值
    }
    // 4路对内温度或电压模拟量
    for (int i = 0; i < 4; i++)
    {
        canfd_yc_all.ycData.in_adc[i] = ADCValue.inValue[i]; // 示例数据，替换为实际值
    }

    // 填充星间模块工作参数
    canfd_yc_all.xjData.working_status = 0x01;     // 工作状态 1BYTE
    canfd_yc_all.xjData.working_mode = 0x01;       // 工作模式 1BYTE
    canfd_yc_all.xjData.module_address = 0x0200;   // 模块地址 2BYTE
    canfd_yc_all.xjData.network_address = 0x03;    // 网络地址 1BYTE
    canfd_yc_all.xjData.serial_baud_rate = 0x01;   // 串口波特率 1BYTE
    canfd_yc_all.xjData.parity_bit = 0x02;         // 校验位 1BYTE
    canfd_yc_all.xjData.airspeed_400mhz = 0x03;    // 400M空速(1.2K) 1BYTE
    canfd_yc_all.xjData.airspeed_230mhz = 0x04;    // 230M空速(1.2K) 1BYTE
    canfd_yc_all.xjData.channel = 0x05;            // 信道 1BYTE
    canfd_yc_all.xjData.packet_length = 0x06;      // 封包长度 1BYTE
    canfd_yc_all.xjData.wor_role = 0x07;           // WOR 角色 1BYTE
    canfd_yc_all.xjData.wor_cycle = 0x08;          // WOR 周期 1BYTE
    canfd_yc_all.xjData.tx_power = 0x09;           // 发射功率 1BYTE
    canfd_yc_all.xjData.transmission_mode = 0x0A;  // 传输模式 1BYTE
    canfd_yc_all.xjData.relay_mode = 0x0B;         // 中继模式 1BYTE
    canfd_yc_all.xjData.listen_before_talk = 0x0C; // listen before talk 1BYTE
    canfd_yc_all.xjData.env_rssi = 0x0D;           // 环境 RSSI 1BYTE
    canfd_yc_all.xjData.data_rssi = 0x0E;          // 数据 RSSI 1BYTE
    canfd_yc_all.xjData.encryption_key = 0x0F00;   // 密钥 2BYTE
    canfd_yc_all.xjData.wor_sleep_delay = 0x1000;  // WOR 延时休眠 2BYTE

    canfd_yc_all.xj_pierce_DataLen = 0x0011; // 星间模块透穿数据大小 2BYTE

    // ===== 计算校验和 =====
    canfd_yc_all.checksum = 0;
    uint8_t *data_ptr = (uint8_t *)&canfd_yc_all;

    // 累加字节1-127的和
    for (int i = 0; i < sizeof(canfdYC_all) - 1; i++)
    {
        canfd_yc_all.checksum += data_ptr[i];
    }
    canfd_yc_all.xjData.module_address = swap_byte(0x0200);  // 模块地址 2BYTE
    canfd_yc_all.xjData.encryption_key = swap_byte(0x0F00);  // 密钥 2BYTE
    canfd_yc_all.xjData.wor_sleep_delay = swap_byte(0x1000); // WOR 延时休眠 2BYTE
    canfd_yc_all.xj_pierce_DataLen = swap_byte(0x0011);      // 星间模块透穿数据大小 2BYTE
}

// 电机数据组包
void canfd_build_dianji_pack()
{
    memset(&frame, 0, sizeof(frame)); // 初始化遥测数据结构体

    // ===== 1. 帧头数据 ===== [协议要求]
    // frame.preamble = 0xEB90;      // 固定包头\n ,
    // frame.preamble = 0x90EB;      // 固定包头\n ,
    // frame.preamble = swap_byte(0xEB90);      // 固定包头\n ,
    // frame.device_id = 0x01;       // 假设设备ID为1\n
    // frame.data_length = 0x0035;   // 数据长度固定53字节\n
    // frame.data_length = swap_byte(0x0035);   // 数据长度固定53字节\n
    // frame.data_length = swap_byte(sizeof(frame) - sizeof(frame.device_id)*5); // 数据长度
    frame.data_type = 0x35;     // 遥测数据类型标识\n
    frame.data_encoding = 0x03; // 应答编码 0x0b (1字节)
    // frame.request_id = 0xAA;      // 请求ID（示例值）\n

    // ===== 2. 遥测数据区 =====
    // ---- 指令计数 ----
    frame.req_count = 128;       // D0 遥测请求计数 128\n
    frame.valid_cmd_count = 120; // D1 有效指令计数\n
    frame.error_cmd_count = 8;   // D2 错误指令计数\n
    frame.last_cmd_code = 0xC3;  // D3 最后执行指令码\n
    frame.backup_count = 5;      // D4 备份数据接收次数\n
    frame.sade_id = 0x55;        // D5 主份SADE（0x55:主份）\n

    // ---- 脉冲计数 ----
    frame.pulse_z_count = 100; // D6 Z过零脉冲次数\n
    frame.pulse_bq_count = 85; // D10 BQ过零脉冲次数\n

    // ---- 电源参数（原始ADC值）----
    frame.ps_12v = 42;         // D7 12V电压ADC值（需转换：42 * 69.3 / 255 ≈ 11.6V）\n
    frame.ps_5v = 128;         // D8 5V电压ADC值\n （需转换：128 * 9.9 / 255 ≈ 5V）\n
    frame.ps_1v9 = 146;        // D9 1.9V电压ADC值\n （需转换：146 * 3.3 / 255 ≈ 1.9V）\n
    frame.ps_12v_current = 30; // D11 12V电流ADC值\n （需转换：146 * 3.3 / 255 ≈ 1.9V）\n
    frame.ps_5v_current = 77;  // D12 5V电流ADC值\n
    frame.ps_3v3_current = 57; // D13 3.3V电流ADC值\n
    frame.ps_1v9_current = 57; // D14 1.9V电流ADC值\n
    frame.motor_current = 45;  // D15 电机电流ADC值\n

    // ---- 状态标志（位域赋值）----
    // D16 通信状态 [协议定义]
    frame.comm_status.valid = 0;    // 指令正确\n
    frame.comm_status.data = 0;     // 数据合法\n
    frame.comm_status.checksum = 0; // 校验正确\n
    frame.comm_status.reserved = 0; // 保留位填0\n

    // D17 工作模式 [协议定义]
    frame.mode.mode = 0x11; // 0x11: 跟踪模式\n

    // D18 工作状态 [协议定义]
    frame.status.moving = 1;       // 运动中\n
    frame.status.thermal_ctrl = 0; // 温控开启\n
    frame.status.heater = 0;       // 加热器关闭\n
    frame.status.encoder = 0;      // 编码器有效\n
    frame.status.track_a = 1;      // 码道A正常\n
    frame.status.track_b = 1;      // 码道B正常\n
    frame.status.track_ab = 1;     // 码道AB正常\n
    frame.status.track_bq = 1;     // 码道BQ正常\n

    // D19 故障状态 [协议定义]
    memset(&frame.faults, 0, sizeof(SADMFaultStatus)); // 所有故障位清零（无故障）\n

    // ===== 3. 多字节数据 =====

    frame.motor_position = 8500;   // D20-D21 电机位置（需转换）\n
    frame.motor_speed = 1200;      // D22-D23 电机速度（RPM）\n
    frame.encoder_ab_pos = 8400;   // D24-D25 AB编码器位置\n
    frame.encoder_ab_speed = 1180; // D26-D27 AB编码器速度\n
    frame.encoder_a_pos = 8450;    // D28-D29 A编码器位置\n
    frame.encoder_a_speed = 1190;  // D30-D31 A编码器速度\n
    frame.encoder_b_pos = 8350;    // D32-D33 B编码器位置\n
    frame.encoder_b_speed = 1170;  // D34-D35 B编码器速度\n
    frame.cmd_position = 8600;     // D36-D37 指令位置\n
    frame.cmd_speed = 1300;        // D38-D39 指令速度\n

    /*
    frame.motor_position = swap_byte(0x0035);     // D20-D21 电机位置（需转换）\n
    frame.motor_speed = swap_byte(0x0035);        // D22-D23 电机速度（RPM）\n
    frame.encoder_ab_pos = swap_byte(0x0035);     // D24-D25 AB编码器位置\n
    frame.encoder_ab_speed = swap_byte(0x0035);    // D26-D27 AB编码器速度\n
    frame.encoder_a_pos = swap_byte(0x0035); // D28-D29 A编码器位置\n
    frame.encoder_a_speed = swap_byte(0x0035);     // D30-D31 A编码器速度\n
    frame.encoder_b_pos = 8350;      // D32-D33 B编码器位置\n
    frame.encoder_b_speed = 1170;    // D34-D35 B编码器速度\n
    frame.cmd_position = 8600;       // D36-D37 指令位置\n
    frame.cmd_speed = 1300;          // D38-D39 指令速度\n
    */

    // ===== 4. 独立参数 =====
    frame.accel_level = 8; // D40 加速度档位（1-20）\n
    frame.sade_temp = 40;  // D41 SADE温度（需转换）\n
    frame.sadm_temp = 35;  // D42 SADM温度（需转换）\n

    // D43 工作状态 [协议定义]
    frame.anglestatus.moving = 0;       // 运动中\n
    frame.anglestatus.thermal_ctrl = 0; // 温控开启\n
    frame.anglestatus.heater = 0;       // 加热器关闭\n
    frame.anglestatus.encoder = 0;      // 编码器有效\n
    frame.anglestatus.track_a = 0;      // 码道A正常\n
    frame.anglestatus.track_b = 0;      // 码道B正常\n
    frame.anglestatus.track_ab = 0;     // 码道AB正常\n
    frame.anglestatus.track_bq = 0;     // 码道BQ正常\n

    frame.motion_current = 50;  // D44 运动电流ADC值\n
    frame.holding_current = 20; // D45 保持电流ADC值\n
    frame.product_id = 0x10;    // D46 产品编号\n
    frame.comm_reset_count = 2; // D47 通信复位次数\n
    frame.yuliu = 0;            // D48 预留\n
    // ===== 5. 校验和计算 =====
    frame.checksum = 0;                        // 先清零\n
    uint8_t *data_ptr = (uint8_t *)&frame + 7; // 从D0开始（跳过7字节帧头）\n
    for (int i = 0; i < 49; i++)
    {                                  // D0-D48共49字节
        frame.checksum += data_ptr[i]; // D49 累加和校验\n
    }
    frame.motor_position = swap_byte(frame.motor_position);     // D20-D21 电机位置（需转换）\n
    frame.motor_speed = swap_byte(frame.motor_speed);           // D22-D23 电机速度（RPM）\n
    frame.encoder_ab_pos = swap_byte(frame.encoder_ab_pos);     // D24-D25 AB编码器位置\n
    frame.encoder_ab_speed = swap_byte(frame.encoder_ab_speed); // D26-D27 AB编码器速度\n
    frame.encoder_a_pos = swap_byte(frame.encoder_a_pos);       // D28-D29 A编码器位置\n
    frame.encoder_a_speed = swap_byte(frame.encoder_a_speed);   // D30-D31 A编码器速度\n
    frame.encoder_b_pos = swap_byte(frame.encoder_b_pos);       // D32-D33 B编码器位置\n
    frame.encoder_b_speed = swap_byte(frame.encoder_b_speed);   // D34-D35 B编码器速度\n
    frame.cmd_position = swap_byte(frame.cmd_position);         // D36-D37 指令位置\n
    frame.cmd_speed = swap_byte(frame.cmd_speed);               // D38-D39 指令速度\n
}



// 电机数据组包  直接转发的
void canfd_build_dianji_pack_T()
{
    memset(&frame_t, 0, sizeof(frame_t)); // 初始化遥测数据结构体

    // ===== 1. 帧头数据 ===== [协议要求]
    // frame_t.preamble = 0xEB90;      // 固定包头\n ,
    // frame_t.preamble = 0x90EB;      // 固定包头\n ,
    // frame_t.preamble = swap_byte(0xEB90);      // 固定包头\n ,
    // frame_t.device_id = 0x01;       // 假设设备ID为1\n
    // frame_t.data_length = 0x0035;   // 数据长度固定53字节\n
    // frame_t.data_length = swap_byte(0x0035);   // 数据长度固定53字节\n
    // frame_t.data_length = swap_byte(sizeof(frame_t) - sizeof(frame_t.device_id)*5); // 数据长度
    frame_t.data_type = 0x35;     // 遥测数据类型标识\n
    frame_t.data_encoding = 0x03; // 应答编码 0x0b (1字节)
    // frame_t.request_id = 0xAA;      // 请求ID（示例值）\n

    // ===== 2. 遥测数据区 =====
    // ---- 指令计数 ----
    frame_t.req_count = 128;       // D0 遥测请求计数 128\n
    frame_t.valid_cmd_count = 120; // D1 有效指令计数\n
    frame_t.error_cmd_count = 8;   // D2 错误指令计数\n
    frame_t.last_cmd_code = 0xC3;  // D3 最后执行指令码\n
    frame_t.backup_count = 5;      // D4 备份数据接收次数\n
    frame_t.sade_id = 0x55;        // D5 主份SADE（0x55:主份）\n

    // ===== 3. 电机遥测数据区 =====
    
    // ===== 5. 校验和计算 =====
    frame_t.checksum = 0;                        // 先清零\n
    uint8_t *data_ptr = (uint8_t *)&frame_t + 7; // 从D0开始（跳过7字节帧头）\n
    for (int i = 0; i < 49; i++)
    {                                  // D0-D48共49字节
        frame_t.checksum += data_ptr[i]; // D49 累加和校验\n
    }
}

// wire数据组包
void canfd_build_wire_pack()
{
    memset(&wireframe, 0, sizeof(wireframe)); // 初始化遥测数据结构体

    // ===== 第一帧数据 =====
    wireframe.data_type = 0x35;                // 固定数据类型值
    wireframe.data_encoding = 0x02;            // 固定数据编码值
    wireframe.data_length = swap_byte(0x007D); // 从字节3到127的总长度,7D
    // wireframe.data_length = swap_byte(sizeof(wireframe) - sizeof(wireframe.data_type)*4); // 数据长度

    // 填充前5路温度数据 (实际值乘以16，符合协议表示方法)
    wireframe.first_5wires.temp1 = 25 * 100; // 25.0°C (250 = 25.0 * 10)
    wireframe.first_5wires.temp2 = 25 * 100; // 25.5°C
    wireframe.first_5wires.temp3 = 0 * 100;  // 0.0°C (开路或故障)
    wireframe.first_5wires.temp4 = 30 * 100; // 30.0°C
    wireframe.first_5wires.temp5 = 30 * 100; // 25.0°C

    // 清空预留区域
    memset(wireframe.reserved1, 0, sizeof(wireframe.reserved1));

    // ===== 第二帧数据 =====
    // ireframe.frame_seq = 0x01;         // 第二帧序号固定为1

    // 填充后5路温度数据
    wireframe.second_5wires.temp6 = 25 * 100;  //  // 28.0°C
    wireframe.second_5wires.temp7 = 30 * 100;  // 9.0°C
    wireframe.second_5wires.temp8 = 25 * 100;  //  // 26.0°C
    wireframe.second_5wires.temp9 = 30 * 100;  // 25.5°C
    wireframe.second_5wires.temp10 = 18 * 100; // 31.0°C

    // 清空预留区域
    memset(wireframe.reserved2, 0, sizeof(wireframe.reserved2));

    // ===== 计算校验和 =====
    wireframe.checksum = 0;
    uint8_t *data_ptr = (uint8_t *)&wireframe;

    // 累加字节1-127的和
    for (int i = 0; i < sizeof(FiveWireTelemetryFrame) - 1; i++)
    {
        wireframe.checksum += data_ptr[i];
    }

    // 填充前5路温度数据 (实际值乘以16，符合协议表示方法)
    wireframe.first_5wires.temp1 = swap_byte(wireframe.first_5wires.temp1);
    wireframe.first_5wires.temp2 = swap_byte(wireframe.first_5wires.temp2);
    wireframe.first_5wires.temp3 = swap_byte(wireframe.first_5wires.temp3);
    wireframe.first_5wires.temp4 = swap_byte(wireframe.first_5wires.temp4);
    wireframe.first_5wires.temp5 = swap_byte(wireframe.first_5wires.temp5);

    // 填充后5路温度数据
    wireframe.second_5wires.temp6 = swap_byte(wireframe.second_5wires.temp6);
    wireframe.second_5wires.temp7 = swap_byte(wireframe.second_5wires.temp7);
    wireframe.second_5wires.temp8 = swap_byte(wireframe.second_5wires.temp8);
    wireframe.second_5wires.temp9 = swap_byte(wireframe.second_5wires.temp9);
    wireframe.second_5wires.temp10 = swap_byte(wireframe.second_5wires.temp10);
}

// 协议解析函数
ParseStatus parse_can_message(const uint8_t *data, size_t data_length, CommandType *cmd_type, void **cmd_data)
{
    if (data == NULL || cmd_type == NULL || cmd_data == NULL || data_length < 3)
    {
        Printf("parse_can_message arg error\r\n");
        return PARSE_ERROR_INSUFFICIENT_DATA;
    }

    // 提取指令类型
    uint8_t cmd = data[1]; // 数据编号(D3)字段
    *cmd_type = cmd;

    // 根据指令类型解析数据
    switch (*cmd_type)
    {
    case CMD_TELEMETRY_REQ:
    case CMD_5WIRE_TEMP_REQ:
    case CMD_INTERSTELLAR_RESET:
    case CMD_DIANJI_REQ:
        // 这些指令没有参数，只需验证长度   从数据类型到单字节校验和之前的所有数据长度
        if (data_length < 6)
        {
            Printf("data_length arg error\r\n");
            return PARSE_ERROR_INVALID_LENGTH;
        }
        *cmd_data = NULL;
        break;

    case CMD_POWER_CONTROL:
    case CMD_GPIO_CONTROL:
    case CMD_HIGH_CURRENT_CONTROL:
        A_CAN_reset_num1 = 1;
        // 这些指令有2字节参数 (通道号+状态)
        if (data_length < 3)
        { // 3字节头部 + 2字节数据
            return PARSE_ERROR_INVALID_LENGTH;
        }
        {
            GPIOCtrl *ctrl = (GPIOCtrl *)malloc(sizeof(GPIOCtrl));
            if (ctrl == NULL)
            {
                return PARSE_ERROR_INSUFFICIENT_DATA;
            }
            // rl->channel = data[4]; // 第1个数据字节
            // rl->state = data[5];   // 第2个数据字节
            ctrl->channel = data[2]; // 第1个数据字节
            ctrl->state = data[3];   // 第2个数据字节
            *cmd_data = ctrl;
        }
        break;

    case CMD_LOW_CURRENT_SETTING:
        A_CAN_reset_num1 = 1;
        // 小电流配电使能设置，2字节参数
        if (data_length < 3)
        {
            return PARSE_ERROR_INVALID_LENGTH;
        }
        {
            GPIOCtrl *ctrl = (GPIOCtrl *)malloc(sizeof(GPIOCtrl));
            if (ctrl == NULL)
            {
                return PARSE_ERROR_INSUFFICIENT_DATA;
            }
            // ctrl->channel = data[4]; // 第1个数据字节
            // ctrl->state = data[5];   // 第2个数据字节
            ctrl->channel = data[2]; // 第1个数据字节
            ctrl->state = data[3];   // 第2个数据字节
            *cmd_data = ctrl;
        }
        break;

    case CMD_INTERSTELLAR_CONFIG:
        A_CAN_reset_num1 = 1;
        // 星间模块配置指令，22字节参数
        // if (data_length != 24)
        // wj
        if (data_length != 24)
        { // 3字节头部 + 22字节数据
            Printf("xing jian config data length error\r\n");
            return PARSE_ERROR_INVALID_LENGTH;
        }
        {
            InterstellarConfig *config = (InterstellarConfig *)malloc(sizeof(InterstellarConfig));
            if (config == NULL)
            {
                return PARSE_ERROR_INSUFFICIENT_DATA;
            }
            // 解析22字节配置数据
            const uint8_t *p = &data[2];
            config->work_mode = p[0];
            config->module_addr = (p[1] << 8) | p[2];
            config->network_addr = p[3];
            config->baud_rate = p[4];
            config->parity = p[5];
            config->freq_400_speed = p[6];
            config->freq_230_speed = p[7];
            config->channel = p[8];
            config->packet_length = p[9];
            config->wor_role = p[10];
            config->wor_cycle = p[11];
            config->tx_power = p[12];
            config->tx_mode = p[13];
            config->relay_mode = p[14];
            config->lbt = p[15];
            config->env_rssi = p[16];
            config->data_rssi = p[17];
            config->key = (p[18] << 8) | p[19];
            config->wor_sleep_delay = (p[20] << 8) | p[21];
            *cmd_data = config;
        }
        break;

    case CMD_TRANSPARENT_DATA:
        A_CAN_reset_num1 = 1;
        // 透传模式数据，长度可变
        if (data_length < 3)
        {
            return PARSE_ERROR_INSUFFICIENT_DATA;
        }
        {
            // 为数据分配内存并复制
            uint8_t *transparent_data = (uint8_t *)malloc(data_length - 2);
            if (transparent_data == NULL)
            {
                return PARSE_ERROR_INSUFFICIENT_DATA;
            }
            memcpy(transparent_data, &data[2], data_length - 2);
            *cmd_data = transparent_data;
        }
        break;
    case CMD_DIANJI_CTL: // 电机指令转发
        A_CAN_reset_num1 = 1;
        // 电机指令转发数据，长度可变
        if (data_length < 3)
        {
            return PARSE_ERROR_INSUFFICIENT_DATA;
        }
        {
            // 为数据分配内存并复制
            uint8_t *transparent_data = (uint8_t *)malloc(data_length - 2);
            if (transparent_data == NULL)
            {
                return PARSE_ERROR_INSUFFICIENT_DATA;
            }
            memcpy(transparent_data, &data[2], data_length - 2);
            *cmd_data = transparent_data;
        }
        break;
    default:
        return PARSE_ERROR_INVALID_CMD;
    }

    return PARSE_SUCCESS;
}

// 释放解析函数分配的内存
void free_parsed_data(CommandType cmd_type, void *cmd_data)
{
    if (cmd_data == NULL)
        return;

    switch (cmd_type)
    {
    case CMD_POWER_CONTROL:
    case CMD_GPIO_CONTROL:
    case CMD_HIGH_CURRENT_CONTROL:
    case CMD_LOW_CURRENT_SETTING:
        free(cmd_data);
        break;

    case CMD_INTERSTELLAR_CONFIG:
        free(cmd_data);
        break;

    case CMD_TRANSPARENT_DATA:
        free(cmd_data);
        break;

    default:
        // 其他命令类型不分配内存
        break;
    }
}
#if 1
// 发送遥测数据，这里直接传所有数据和总长度，这个函数进行分包发送
uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length)
{
    uint8_t Send_data1[64] = {0};                     // 每个数据包的大小为64字节
    uint16_t total_packets = (data_length + 63) / 64; // 计算总数据包数，向上取整
    uint8_t packet_number = 0;                        // 当前数据包编号
    uint16_t actual_len;
    volatile uint8_t status1 = 0;
    // CANFD1_Frame_Config(0x147, Byte_64);
    current_count_id1 = (current_count_id0 == 0xff) ? 0 : current_count_id1 + 1;
    // A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 +1;
    //  CANFD1_Frame_Config(0x147, Byte_64);

    // 发送完整64字节数据
    while (data_length >= 64)
    {
        if (status1 == 0)
        {
            CANFD1_Frame_rev(0x08, current_count_id0); // 复合帧 ,首帧
            status1++;
        }
        else
        {
            status1++;
            CANFD1_Frame_rev(0x09, current_count_id0); // 复合帧 ,中间帧
        }

        memcpy(Send_data1, data, 64); // 复制前64字节
        CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_64);

        data += 64;        // 移动数据指针
        data_length -= 64; // 减少剩余数据长度
        packet_number++;
    }
    // 发送剩余数据（小于64字节）
    if (data_length > 0)
    {

        actual_len = data_length;
        if (packet_number > 0) // 多包传输
        {
            Send_data1[0] = packet_number;             // 帧序号
            memcpy(&Send_data1[1], data, data_length); // 复制剩余数据，数据从1开始
            CANFD1_Frame_rev(0x9, current_count_id0);  // 复帧，尾帧 0x9
            actual_len += 1;
        }
        else // 单包传输
        {
            memcpy(&Send_data1, data, data_length);    // 无序号
            CANFD1_Frame_rev(0x07, current_count_id0); // 单帧，0x7
        }

        // 选择最接近的标准DLC
        uint8_t dlc;
        if (actual_len <= 8)
            dlc = Byte_8;
        else if (actual_len <= 12)
            dlc = Byte_12;
        else if (actual_len <= 16)
            dlc = Byte_16;
        else if (actual_len <= 20)
            dlc = Byte_20;
        else if (actual_len <= 24)
            dlc = Byte_24;
        else if (actual_len <= 32)
            dlc = Byte_32;
        else if (actual_len <= 48)
            dlc = Byte_48;
        else
            dlc = Byte_64; // 33-64字节

        // 发送最后的数据包
        if (dlc == Byte_64)
        {
            CANFD_Transmit(CANFD1, TB1, Send_data1, dlc); // 64字节用TB1
        }
        else
        {
            CANFD_Transmit(CANFD1, TB0, Send_data1, dlc); // 其他用TB0
        }
    }
    return 0;
}

#else
uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length)
{
    uint8_t Send_data1[64] = {0};                     // 每个数据包的大小为64字节
    uint16_t total_packets = (data_length + 63) / 64; // 计算总数据包数，向上取整
    uint8_t packet_number = 0;                        // 当前数据包编号
    uint16_t actual_len;
    volatile uint8_t status1 = 0;
    uint8_t error_count = 0;
    current_count_id1 = (current_count_id0 == 0xff) ? 0 : current_count_id1 + 1;

    // 发送完整64字节数据
    while (data_length >= 64)
    {
        if (status1 == 0)
        {
            CANFD1_Frame_rev(0x08, current_count_id0); // 复合帧 ,首帧
            status1++;
        }
        else
        {
            status1++;
            CANFD1_Frame_rev(0x09, current_count_id0); // 复合帧 ,中间帧
        }

        memcpy(Send_data1, data, 64); // 复制前64字节
        if (CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_64) != 0)
        {
            error_count++; // 记录失败帧
            Printf("Frame %d/%d failed\r\n", packet_number + 1, total_packets);
        }
    }

    data += 64;        // 移动数据指针
    data_length -= 64; // 减少剩余数据长度
    packet_number++;
}
// 发送剩余数据（小于64字节）
if (data_length > 0)
{

    actual_len = data_length;
    if (packet_number > 0) // 多包传输
    {
        Send_data1[0] = packet_number;             // 帧序号
        memcpy(&Send_data1[1], data, data_length); // 复制剩余数据，数据从1开始
        CANFD1_Frame_rev(0x9, current_count_id0);  // 复帧，尾帧 0x9
        actual_len += 1;
    }
    else // 单包传输
    {
        memcpy(&Send_data1, data, data_length);    // 无序号
        CANFD1_Frame_rev(0x07, current_count_id0); // 单帧，0x7
    }

    // 选择最接近的标准DLC
    uint8_t dlc;
    if (actual_len <= 8)
        dlc = Byte_8;
    else if (actual_len <= 12)
        dlc = Byte_12;
    else if (actual_len <= 16)
        dlc = Byte_16;
    else if (actual_len <= 20)
        dlc = Byte_20;
    else if (actual_len <= 24)
        dlc = Byte_24;
    else if (actual_len <= 32)
        dlc = Byte_32;
    else if (actual_len <= 48)
        dlc = Byte_48;
    else
        dlc = Byte_64; // 33-64字节

    // 发送最后的数据包
    if (dlc == Byte_64)
    {
        CANFD_Transmit(CANFD1, TB1, Send_data1, dlc); // 64字节用TB1
    }
    else
    {
        CANFD_Transmit(CANFD1, TB0, Send_data1, dlc); // 其他用TB0
    }
}
return 0;
}
#endif

// 发送遥测数据，这里直接传所有数据和总长度，这个函数进行分包发送
uint8_t canfd_send_all_data0(uint8_t *data, uint16_t data_length)
{
    uint8_t Send_data0[64] = {0};                     // 每个数据包的大小为64字节
    uint16_t total_packets = (data_length + 63) / 64; // 计算总数据包数，向上取整
    uint8_t packet_number = 0;                        // 当前数据包编号
    // Printf("data_length(canfd_send_all_data0)is %d\r\n", data_length);
    uint16_t actual_len;
    volatile uint8_t status = 0;
    volatile uint8_t status_dan = 0;
    // B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 +1;
    //  CANFD1_Frame_Config(0x147, Byte_64);
    current_count_id0 = (current_count_id0 == 0xff) ? 0 : current_count_id0 + 1;
    // 发送完整64字节数据
    while (data_length >= 64)
    {
        if (status == 0)
        {
            CANFD0_Frame_rev(0x08, current_count_id0); // 复合帧 ,首帧
            status++;
        }
        else
        {
            status++;
            CANFD0_Frame_rev(0x09, current_count_id0); // 复合帧 ,中间帧
        }

        memcpy(Send_data0, data, 64); // 复制前64字节
        CANFD_Transmit(CANFD0, TB1, Send_data0, Byte_64);

        data += 64;        // 移动数据指针
        data_length -= 64; // 减少剩余数据长度
        packet_number++;
        // Printf("CANFD_Transmit(CANFD0) 0. \r\n");
    }
    // 发送剩余数据（小于64字节）
    if (data_length > 0)
    {
        actual_len = data_length;
        if (packet_number > 0) // 多包传输
        {
            Send_data0[0] = packet_number;             // 帧序号
            memcpy(&Send_data0[1], data, data_length); // 复制剩余数据，数据从1开始
            CANFD0_Frame_rev(0x9, current_count_id0);  // 复帧，尾帧 0x9
            actual_len += 1;
        }
        else // 单包传输
        {
            CANFD0_Frame_rev(0x07, current_count_id0); // 单帧，0x7
            memcpy(&Send_data0, data, data_length);    // 无序号
        }

        // 选择最接近的标准DLC
        uint8_t dlc;
        if (actual_len <= 8)
            dlc = Byte_8;
        else if (actual_len <= 12)
            dlc = Byte_12;
        else if (actual_len <= 16)
            dlc = Byte_16;
        else if (actual_len <= 20)
            dlc = Byte_20;
        else if (actual_len <= 24)
            dlc = Byte_24;
        else if (actual_len <= 32)
            dlc = Byte_32;
        else if (actual_len <= 48)
            dlc = Byte_48;
        else
            dlc = Byte_64; // 33-64字节

        // 发送最后的数据包
        if (dlc == Byte_64)
        {
            CANFD_Transmit(CANFD0, TB1, Send_data0, dlc); // 64字节用TB1
        }
        else
        {
            CANFD_Transmit(CANFD0, TB0, Send_data0, dlc); // 其他用TB0
        }
    }
    return 0;
}

/*
uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length)
{
    uint8_t Send_data1[64];                           // 每个数据包的大小为64字节
    uint16_t total_packets = (data_length + 63) / 64; // 计算总数据包数，向上取整
    uint8_t packet_number = -1;                       // 当前数据包编号
    Printf("data_length(canfd_send_all_data)is %d\r\n", data_length);
    // CANFD1_Frame_Config(0x147, Byte_64);

    // 发送剩余数据包
    while (data_length > 0)
    {
        packet_number++; // 增加数据包编号
        if (data_length > 64)
        {
            memcpy(Send_data1, data, 64); // 复制前64字节
            data += 64;                   // 移动数据指针
            data_length -= 64;            // 减少剩余数据长度
            CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_64);
        }
        else
        {
            if (packet_number > 0) // 不是第一个数据包时，收字节是帧序号
            {
                Send_data1[0] = packet_number; // 帧序号
                data_length += 1;              // 因为多加了1个字节，所以发送的时候补上
                memcpy(&Send_data1[1], data, data_length); // 复制剩余数据
            }
            else // 是第一个数据包时，直接拷贝数据
                memcpy(Send_data1, data, data_length);


            if (data_length != Byte_64  && data_length != Byte_32 && data_length != Byte_64 && data_length != Byte_8 && data_length != Byte_16)
            {
                Printf("canfd_send_all_data error data_length=%d\r\n", data_length);
                return -1;
            }
            // CANFD1_Frame_Config(0x147, data_length);
            if(data_length == Byte_64)
                CANFD_Transmit(CANFD1, TB1, Send_data1, data_length); // TB1通道设置的是64字节
            else if(data_length == Byte_32)
                CANFD_Transmit(CANFD1, TB0, Send_data1, data_length); // TB0通道设置的是32字节
            else
                Printf("not support send other Byte\r\n");
            data_length = 0;                                      // 数据长度为0，结束循环
        }
    }
    return 0;
}
*/

/**
 * @brief 根据配置结构体发送AT指令配置星间模块
 * @param config 星间模块配置结构体指针
 * @return 0:所有指令发送成功 非0:发送失败（返回第一个失败指令的错误码）
 */
uint8_t interstellar_config_send(InterstellarConfig *config)
{
    uint8_t ret;

    // 参数合法性检查
    if (config == NULL)
    {
        return -1; // 配置结构体为空
    }

    // 在开始配置前，先清理串口缓冲区，避免之前的响应数据干扰
    delay_ms(100); // 等待串口稳定

    // 1. 设置工作模式 (AT+MODE=work_mode)
    ret = at_send_cmd(AT_CMD_1PARAM_MODE, config->work_mode, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_MODE.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_MODE error.\r\n");
        return ret;
    }
    delay_ms(50); // 等待星间模块处理指令

    // 2. 设置模块地址 (AT+ADDR=module_addr)
    ret = at_send_cmd(AT_CMD_1PARAM_ADDR, config->module_addr, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_ADDR.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_ADDR error.\r\n");
        return ret;
    }

    // 3. 设置网络ID (AT+NETID=network_addr)
    ret = at_send_cmd(AT_CMD_1PARAM_NETID, config->network_addr, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_NETID.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_NETID error.\r\n");
        return ret;
    }

    // 4. 设置串口波特率和校验位 (AT+UART=baud_rate,parity)
    ret = at_send_cmd(AT_CMD_2PARAM_UART, config->baud_rate, config->parity);
    // Printf("cat_send_cmd: AT_CMD_2PARAM_UART.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_2PARAM_UART error.\r\n");
        return ret;
    }

    // 5. 设置400MHz频段空中速率 (AT+RATE=freq_400_speed)
    // 注：根据硬件实际频段选择对应参数，这里假设使用400MHz频段
    ret = at_send_cmd(AT_CMD_1PARAM_RATE, config->freq_400_speed, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_RATE.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_RATE error.\r\n");
        return ret;
    }

    // 6. 设置信道 (AT+CHANNEL=channel)
    ret = at_send_cmd(AT_CMD_1PARAM_CHANNEL, config->channel, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_CHANNEL.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_CHANNEL error.\r\n");
        return ret;
    }

    // 7. 设置封包长度 (AT+PACKET=packet_length)
    ret = at_send_cmd(AT_CMD_1PARAM_PACKET, config->packet_length, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_PACKET.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_PACKET error.\r\n");
        return ret;
    }

    // 8. 设置WOR角色 (AT+WOR=wor_role)
    ret = at_send_cmd(AT_CMD_1PARAM_WOR, config->wor_role, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_WOR.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_WOR error.\r\n");
        return ret;
    }

    // 9. 设置发射功率 (AT+POWER=tx_power)
    ret = at_send_cmd(AT_CMD_1PARAM_POWER, config->tx_power, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_POWER.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_POWER error.\r\n");
        return ret;
    }

    // 10. 设置传输模式 (AT+TRANS=tx_mode)
    ret = at_send_cmd(AT_CMD_1PARAM_TRANS, config->tx_mode, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_TRANS.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_TRANS error.\r\n");
        return ret;
    }

    // 11. 设置中继模式 (AT+ROUTER=relay_mode)
    ret = at_send_cmd(AT_CMD_1PARAM_ROUTER, config->relay_mode, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_ROUTER.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_ROUTER error.\r\n");
        return ret;
    }

    // 12. 设置LBT功能 (AT+LBT=lbt)
    ret = at_send_cmd(AT_CMD_1PARAM_LBT, config->lbt, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_LBT.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_LBT error.\r\n");
        return ret;
    }

    // 13. 设置环境噪声RSSI (AT+ERSSI=env_rssi)
    ret = at_send_cmd(AT_CMD_1PARAM_ERSSI, config->env_rssi, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_ERSSI.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_ERSSI error.\r\n");
        return ret;
    }

    // 14. 设置数据RSSI (AT+DRSSI=data_rssi)
    ret = at_send_cmd(AT_CMD_1PARAM_DRSSI, config->data_rssi, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_DRSSI.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_DRSSI error.\r\n");
        return ret;
    }

    // 15. 设置密钥 (AT+KEY=key)
    ret = at_send_cmd(AT_CMD_1PARAM_KEY, config->key, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_KEY.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_KEY error.\r\n");
        return ret;
    }

    // 16. 设置WOR延迟休眠时间 (AT+DELAY=wor_sleep_delay)
    ret = at_send_cmd(AT_CMD_1PARAM_DELAY, config->wor_sleep_delay, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_DELAY.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_DELAY error.\r\n");
        return ret;
    }

    // 所有配置发送完成后，可选择发送重启指令使配置生效
    ret = at_send_cmd(AT_CMD_NONE_RESET, -1, -1);
    return ret;
}

/**
 * @brief 将遥测请求指令发到串口， 《电机转发协议中，按照遥测请求指令》
 * @return 0:成功, 非0:失败
 */
uint8_t dj_uart_cmd_rqu()
{
    uint8_t packet[9];
    uint8_t total_len = 9;

    if (rqu_id == 255)
    {
        rqu_id = 0;
        Printf("rqu_id is overflow.\r\n");
    }
    else
    {
        rqu_id++;
    }

    // 填充包头字段
    packet[0] = 0xEB; // 包头第1字节
    packet[1] = 0x90; // 包头第2字节
    packet[2] = 0x00; // ID字
    packet[3] = 0x00; // 数据长度高八位
    packet[4] = 0x03; // 数据长度底八位
    packet[5] = 0x05; // 数据类型
    packet[6] = 0xff; // 命令码字
    // packet[7] = rqu_id; // 请求ID
    packet[7] = 1; // 请求ID

    // 计算和校验（从包头到数据部分的所有字节累加）
    // uint8_t checksum = 0;
    // for (uint16_t i = 0; i < total_len-1; i++)
    //{
    //    checksum += packet[i];
    //}
    // packet[total_len-1] = checksum; // 校验字
    packet[total_len - 1] = 0x08; // 校验字
    // 发送数据包到串口
    if (uart_send_hex_datas(USART5, packet, total_len) != 0)
    {
        Printf("uart_send_hex_datas USART0 failed!\r\n");
        free(packet);
        return 3; // 发送失败
    }
#if 0
    if (uart_send_hex_datas(USART1, packet, total_len) != 0)
    {
        Printf("uart_send_hex_datas USART1 failed!\r\n");
        free(packet);
        return 3; // 发送失败
    }
#endif
    // 加入调试
    // uart_send_hex_datas(USART6, packet, total_len);//打印调试信息

    // 释放内存
    free(packet);
    return 0; // 成功
}

// CMD_TELEMETRY_REQ = 0x01,        // 遥测请求
// CMD_5WIRE_TEMP_REQ = 0x02,       // 5路1-wire温度遥测采集请求
// CMD_POWER_CONTROL = 0x03,        // 电源输出使能控制请求
// CMD_GPIO_CONTROL = 0x04,         // 对外8路GPIO输出控制
// CMD_HIGH_CURRENT_CONTROL = 0x05, // 大电流配电使能控制请求
// CMD_LOW_CURRENT_SETTING = 0x06,  // 小电流配电使能设置遥控指令
// CMD_INTERSTELLAR_CONFIG = 0x07,  // 星间模块配置指令
// CMD_INTERSTELLAR_RESET = 0x08,   // 星间模块复位
// CMD_TRANSPARENT_DATA = 0x09      // 透传模式数据发送到星间模块

uint8_t can_xieyi_test(uint8_t *cmd, uint16_t data_length)
{
    CommandType cmd_type;
    PowerControl *powerctrl = NULL;
    GPIOCtrl *outctrl = NULL;
    GPIOCtrl *largectrl = NULL;
    GPIOCtrl *lowctrl = NULL;
    void *cmd_data;
    int ret = -1;
    ParseStatus status = parse_can_message(Receive_data1, data_length, &cmd_type, &cmd_data);
    unsigned char *data = (unsigned char *)cmd_data;
    // wj:打印cmd_data值，解析22字节配置数据
#if 0
    Printf("cmd_data value is \r\n");
    for (uint32_t i = 0; i < data_length; i++)
    {
        Printf("0x%x ", Receive_data1[i]);
    }
    Printf("\r\n");
#endif
    // Printf("can_xieyi_test:A_CAN_YC_count1. \r\n");
    //    Printf("A_CAN_YC_count1 si %x \r\n ", A_CAN_YC_count1);
    A_CAN_CUTTENT_CMD1 = cmd_type;
    if (status == PARSE_SUCCESS)
    {
        switch (cmd_type)
        {

        case CMD_TELEMETRY_REQ: // 遥测请求
            A_CAN_YC_count1 = (A_CAN_YC_count1 == 0xff) ? 0 : A_CAN_YC_count1 + 1;
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ. \r\n");
            canfd_build_yaoce_pack();
            canfd_send_all_data((uint8_t *)&canfd_yc_all, sizeof(canfd_yc_all));
            break;
        case CMD_5WIRE_TEMP_REQ: // 5路1-wire温度遥测采集请求
            A_CAN_YC_count1 = (A_CAN_YC_count1 == 0xff) ? 0 : A_CAN_YC_count1 + 1;
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ no code. \r\n");
            canfd_build_wire_pack();
            canfd_send_all_data((uint8_t *)&wireframe, sizeof(wireframe));
            /* code */
            break;
        case CMD_POWER_CONTROL: // 电源输出使能控制请求
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ. \r\n");
            powerctrl = (PowerControl *)cmd_data;
            power_gpio_ctr(powerctrl->channel, powerctrl->state);
            break;
        case CMD_GPIO_CONTROL: // 对外8路GPIO输出控制
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_GPIO_CONTROL. \r\n");
            outctrl = (GPIOCtrl *)cmd_data;
            out_gpio_ctr(outctrl->channel, outctrl->state);
            break;
        case CMD_HIGH_CURRENT_CONTROL: // 大电流配电使能控制请求
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_HIGH_CURRENT_CONTROL. \r\n");
            largectrl = (GPIOCtrl *)cmd_data;
            large_electric_gpio_ctr(largectrl->channel, largectrl->state);
            break;
        case CMD_LOW_CURRENT_SETTING: // 小电流配电使能设置遥控指令
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_LOW_CURRENT_SETTING. \r\n");
            lowctrl = (GPIOCtrl *)cmd_data;
            small_electric_gpio_ctr(lowctrl->channel, lowctrl->state);
            break;
        case CMD_INTERSTELLAR_CONFIG: // 星间模块配置指令
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_INTERSTELLAR_CONFIG. \r\n");
            InterstellarConfig *config = (InterstellarConfig *)cmd_data;
            interstellar_config_send(config);
            break;
        case CMD_INTERSTELLAR_RESET: // 星间模块复位
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_INTERSTELLAR_RESET. \r\n");
            xingjian_reset(0); // 0/1 是主备关系?
            break;
        case CMD_TRANSPARENT_DATA: // 透传模式数据发送到星间模块
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_TRANSPARENT_DATA. \r\n");

            break;
        case CMD_DIANJI_CTL: // 电机控制指令转发
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            // Printf("can_xieyi_test:CMD_DIANJI_CTL. \r\n");
            dj_uart_cmd_analyze(cmd_data, data_length - 2); // data_length是数据总长度，减去2个字节的头部就是实际数据长度
            break;
        case CMD_DIANJI_REQ: // 电机遥测请求
            A_CAN_YC_count1 = (A_CAN_YC_count1 == 0xff) ? 0 : A_CAN_YC_count1 + 1;
            // Printf("can_xieyi_test:CMD_DIANJI_REQ. \r\n");
            dj_uart_cmd_rqu();
            canfd_build_dianji_pack_T();
            canfd_send_all_data((uint8_t *)&frame, sizeof(frame));

            break;
        default:
            // Printf("cmd analyze error\r\n");
            A_CAN_CW_count1 = (A_CAN_CW_count1 == 0xff) ? 0 : A_CAN_CW_count1 + 1;
            break;
        }

        free_parsed_data(cmd_type, cmd_data);
        ret = 0;
    }
    else
    {
        Printf("cmd analyze error2 = %d\n", status);
        A_CAN_CW_count1 = (A_CAN_CW_count1 == 0xff) ? 0 : A_CAN_CW_count1 + 1;
    }

    return ret;
}
uint8_t can_xieyi_test0(uint8_t *cmd, uint16_t data_length)
{
    CommandType cmd_type;
    PowerControl *powerctrl = NULL;
    GPIOCtrl *outctrl = NULL;
    GPIOCtrl *largectrl = NULL;
    GPIOCtrl *lowctrl = NULL;
    void *cmd_data;
    int ret = -1;
    ParseStatus status = parse_can_message(cmd, data_length, &cmd_type, &cmd_data);
    unsigned char *data = (unsigned char *)cmd_data;

    // wj:打印cmd_data值，解析22字节配置数据
    /*
    Printf("cmd_data value is \r\n");
    for (uint32_t i = 0; i < data_length; i++)
    {
        Printf("%02x ", data[i]);
    }
    */

    B_CAN_CUTTENT_CMD0 = cmd_type;
    if (status == PARSE_SUCCESS)
    {
        switch (cmd_type)
        {
        case CMD_TELEMETRY_REQ: // 遥测请求
                                // Printf("can_xieyi_test:CMD_TELEMETRY_REQ. \r\n");
            B_CAN_YC_count0 = (B_CAN_YC_count0 == 0xff) ? 0 : B_CAN_YC_count0 + 1;
            canfd_build_yaoce_pack();
            canfd_send_all_data0((uint8_t *)&canfd_yc_all, sizeof(canfd_yc_all));
            break;
        case CMD_5WIRE_TEMP_REQ: // 5路1-wire温度遥测采集请求
            B_CAN_YC_count0 = (B_CAN_YC_count0 == 0xff) ? 0 : B_CAN_YC_count0 + 1;
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ no code. \r\n");
            canfd_build_wire_pack();
            canfd_send_all_data0((uint8_t *)&wireframe, sizeof(wireframe));
            /* code */
            break;
        case CMD_POWER_CONTROL: // 电源输出使能控制请求
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ. \r\n");
            powerctrl = (PowerControl *)cmd_data;
            power_gpio_ctr(powerctrl->channel, powerctrl->state);
            break;
        case CMD_GPIO_CONTROL: // 对外8路GPIO输出控制
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_GPIO_CONTROL. \r\n");
            outctrl = (GPIOCtrl *)cmd_data;
            out_gpio_ctr(outctrl->channel, outctrl->state);
            break;
        case CMD_HIGH_CURRENT_CONTROL: // 大电流配电使能控制请求
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_HIGH_CURRENT_CONTROL. \r\n");
            largectrl = (GPIOCtrl *)cmd_data;
            large_electric_gpio_ctr(largectrl->channel, largectrl->state);
            break;
        case CMD_LOW_CURRENT_SETTING: // 小电流配电使能设置遥控指令
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_LOW_CURRENT_SETTING. \r\n");
            lowctrl = (GPIOCtrl *)cmd_data;
            small_electric_gpio_ctr(lowctrl->channel, lowctrl->state);
            break;
        case CMD_INTERSTELLAR_CONFIG: // 星间模块配置指令
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_INTERSTELLAR_CONFIG. \r\n");
            InterstellarConfig *config = (InterstellarConfig *)cmd_data;
            interstellar_config_send(config);
            break;
        case CMD_INTERSTELLAR_RESET: // 星间模块复位
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_INTERSTELLAR_RESET. \r\n");
            xingjian_reset(0); // 0/1 是主备关系?
            break;
        case CMD_TRANSPARENT_DATA: // 透传模式数据发送到星间模块
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_TRANSPARENT_DATA. \r\n");

            break;
        case CMD_DIANJI_CTL: // 电机控制指令转发
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_DIANJI_CTL. \r\n");
            dj_uart_cmd_analyze(cmd_data, data_length - 2); // data_length是数据总长度，减去2个字节的头部就是实际数据长度
            break;
        case CMD_DIANJI_REQ: // 电机遥测请求
            B_CAN_YC_count0 = (B_CAN_YC_count0 == 0xff) ? 0 : B_CAN_YC_count0 + 1;
            // Printf("can_xieyi_test:CMD_DIANJI_REQ. \r\n");
            dj_uart_cmd_rqu();
            canfd_build_dianji_pack_T();
            canfd_send_all_data0((uint8_t *)&frame, sizeof(frame));

            break;
        default:
            Printf("cmd analyze error\r\n");
            B_CAN_CW_count0 = (B_CAN_CW_count0 == 0xff) ? 0 : B_CAN_CW_count0 + 1;
            break;
        }

        free_parsed_data(cmd_type, cmd_data);
        ret = 0;
    }
    else
    {
        Printf("cmd analyze error2 = %d\n", status);
        B_CAN_CW_count0 = (B_CAN_CW_count0 == 0xff) ? 0 : B_CAN_CW_count0 + 1;
    }

    return ret;
}
