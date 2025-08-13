
#ifndef __CANFD_XIEYI_H__
#define __CANFD_XIEYI_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义指令类型枚举
typedef enum
{
    CMD_TELEMETRY_REQ = 0x01,        // 遥测请求
    CMD_5WIRE_TEMP_REQ = 0x02,       // 5路1-wire温度遥测采集请求
    CMD_DIANJI_REQ = 0x03,            // 电机遥测请求指令
    CMD_POWER_CONTROL = 0x04,        // 电源输出使能控制请求
    CMD_GPIO_CONTROL = 0x05,         // 对外8路GPIO输出控制
    CMD_HIGH_CURRENT_CONTROL = 0x06, // 大电流配电使能控制请求
    CMD_LOW_CURRENT_SETTING = 0x07,  // 小电流配电使能设置遥控指令
    CMD_INTERSTELLAR_CONFIG = 0x08,  // 星间模块配置指令
    CMD_INTERSTELLAR_RESET = 0x09,   // 星间模块复位
    CMD_TRANSPARENT_DATA = 0x0a,     // 透传模式数据发送到星间模块
    CMD_DIANJI_CTL = 0x0b,          // 电机控制指令转发

} CommandType;
#pragma pack(1)
// 定义电源控制结构体
typedef struct
{
    uint8_t channel; // 通道号
    uint8_t state;   // 状态(0=关闭, 1=打开)
} PowerControl;

// 定义GPIO控制结构体
typedef struct
{
    uint8_t channel; // 通道号
    uint8_t state;   // 状态(0=关闭, 1=打开)
} GPIOCtrl;

// 定义星间模块配置结构体
typedef struct
{
    uint8_t work_mode;        // 工作模式
    uint16_t module_addr;     // 模块地址
    uint8_t network_addr;     // 网络地址
    uint8_t baud_rate;        // 串口波特率
    uint8_t parity;           // 校验位
    uint8_t freq_400_speed;   // 400MHz频段空速
    uint8_t freq_230_speed;   // 230MHz频段空速
    uint8_t channel;          // 信道
    uint8_t packet_length;    // 封包长度
    uint8_t wor_role;         // WOR角色
    uint8_t wor_cycle;        // WOR周期
    uint8_t tx_power;         // 发射功率
    uint8_t tx_mode;          // 传输模式
    uint8_t relay_mode;       // 中继模式
    uint8_t lbt;              // listen before talk
    uint8_t env_rssi;         // 环境RSSI
    uint8_t data_rssi;        // 数据RSSI
    uint16_t key;             // 密钥
    uint16_t wor_sleep_delay; // WOR延时休眠
} InterstellarConfig;

// 解析函数返回状态
typedef enum
{
    PARSE_SUCCESS = 0,                  // 解析成功
    PARSE_ERROR_INVALID_CMD = -1,       // 无效指令类型
    PARSE_ERROR_INSUFFICIENT_DATA = -2, // 数据不足
    PARSE_ERROR_INVALID_LENGTH = -3,    // 长度不匹配
} ParseStatus;

//======协议包头========遥测数据结构体========
typedef struct
{
    uint16_t dataLength;
    uint8_t dataType; // 数据类型 0x05，单帧发送，  0x35返回的帧
    uint8_t dataNum;  // 数据编号
} canfdXYHead;

typedef struct
{
    uint8_t A_CAN_YC_count;      // A通道遥测请求计数
    uint8_t A_CAN_ZQ_count;      // A通道正确帧计数
    uint8_t A_CAN_CW_count;      // A通道错误帧计数
    uint8_t A_CAN_CUTTENT_CMD;   // 最近执行指令码
    uint8_t A_CAN_reset_num;     // 复位计数
    uint8_t A_CAN_reset;         // 复位原因
    uint8_t A_CAN_send_errornum; // 发送错误计数
    uint8_t A_CAN_recv_errornum; // 接收错误计数
    uint8_t B_CAN_YC_count;      // B通道遥测请求计数
    uint8_t B_CAN_ZQ_count;      // B通道正确帧计数
    uint8_t B_CAN_CW_count;      // B通道错误帧计数
    uint8_t B_CAN_CUTTENT_CMD;   // 最近执行指令码
    uint8_t B_CAN_reset_num;     // 复位计数
    uint8_t B_CAN_reset;         // 复位原因
    uint8_t B_CAN_send_errornum; // 发送错误计数
    uint8_t B_CAN_recv_errornum; // 接收错误计数
} canfdXYData_guding;            // 固定要发送的数据

typedef struct
{
    uint8_t working_status;      // 工作状态 1BYTE
    uint8_t working_mode;        // 工作模式 1BYTE
    uint16_t module_address;     // 模块地址 2BYTE
    uint8_t network_address;     // 网络地址 1BYTE
    uint8_t serial_baud_rate;    // 串口波特率 1BYTE
    uint8_t parity_bit;          // 校验位 1BYTE
    uint8_t airspeed_400mhz;     // 400M空速(1.2K) 1BYTE
    uint8_t airspeed_230mhz;     // 230M空速(1.2K) 1BYTE
    uint8_t channel;             // 信道 1BYTE
    uint8_t packet_length;       // 封包长度 1BYTE
    uint8_t wor_role;            // WOR 角色 1BYTE
    uint8_t wor_cycle;           // WOR 周期 1BYTE
    uint8_t tx_power;            // 发射功率 1BYTE
    uint8_t transmission_mode;   // 传输模式 1BYTE
    uint8_t relay_mode;          // 中继模式 1BYTE
    uint8_t listen_before_talk;  // listen before talk 1BYTE
    uint8_t env_rssi;            // 环境 RSSI 1BYTE
    uint8_t data_rssi;           // 数据 RSSI 1BYTE
    uint16_t encryption_key;     // 密钥 2BYTE
    uint16_t wor_sleep_delay;    // WOR 延时休眠 2BYTE
} canfdInterstellarModuleConfig; // 星间模块工作参数

// 遥测数据
typedef struct
{
    uint8_t power_ctr;                    // 电源输出使能控制遥测
    uint8_t out_gpio_ctrl;                // 对外8路GPIO输出状态
    uint8_t large_electric_ctr;           // 大电流配电使能遥测
    uint16_t small_electric_ctr;          // 小电流配电使能
    uint16_t out_adc_data[16];            // 16路对外采集温度 或者电压模拟量
    uint16_t small_power_peidian;         // 16路小功率配电状态
    uint8_t large_power_peidian;          // 2路大功率配电状态
    uint16_t in_adc[4];                   // 4路对内温度或电压模拟量
} canfdYC;

typedef struct
{
    canfdXYHead head;                           //协议包头
    canfdXYData_guding  gdCanInfo;            // 固定要发送的数据
    canfdYC             ycData;               // 遥测数据
    canfdInterstellarModuleConfig xjData;      // 星间模块工作参数
    uint16_t xj_pierce_DataLen;                // 星间模块透穿数据大小
    uint8_t yuliu;                              //预留
    uint8_t checksum;                          // 校验和
}canfdYC_all;//遥测数据综合

//========one-wire遥测数据===========
/*
typedef struct
{
    uint16_t data_length; // 字节1-2: 数据字节长度（不包含校验和）

    // 固定头字段
    uint8_t data_type;     // 字节3: 数据类型 (0x35)
    uint8_t data_encoding; // 字节4: 数据编码 (0x02)

    // 5路1-WIRE采集数据
    uint16_t wire_data_part[50]; // 100字节

    // 预留字段
    uint8_t reserved[22]; // 字节106-127: 预留
} OneWireDataFrame;
*/

// 5路1-Wire温度遥测数据包结构体（共128字节）
typedef struct {
    // ===== 第一帧 (字节1-64) =====
    uint16_t data_length;    // 字节1-2: 数据字节长度 (从字节3到校验和之前的总长度)
    uint8_t data_type;       // 字节3: 数据类型 (固定为0x35)
    uint8_t data_encoding;   // 字节4: 数据编码 (固定为0x02)
    
    uint8_t tempall[100]; //采集的所有温度值
    
    uint8_t reserved2[22];   // 字节106-127: 预留
    uint8_t checksum;        // 字节128: 累加校验和
} FiveWireTelemetryFrame;

//========电机遥测数据===========
typedef struct {
    uint8_t valid : 1;    // 0:正确 1:错误 (D16 b0)
    uint8_t data : 1;      // 0:正确 1:非法 (D16 b1)
    uint8_t checksum : 1;  // 0:正确 1:错误 (D16 b2)
    uint8_t reserved : 5;  // 填充00000 (D16 b3~7)
} CommStatus;  // D16

typedef struct {
    uint8_t mode;  // 0x11:跟踪 0x22:捕获 0x33:复位 0x44:保持 (D17)
} SADMMode;  

typedef struct {
    uint8_t moving : 1;       // 0:停止 1:运动 (D18 b0)
    uint8_t thermal_ctrl : 1; // 0:开启 1:关闭 (D18 b1)
    uint8_t heater : 1;       // 0:关断 1:启动 (D18 b2)
    uint8_t encoder : 1;      // 0:有效 1:无效 (D18 b3)
    uint8_t track_a : 1;      // 码道信状态 (D18 b4)
    uint8_t track_b : 1;      // 码道信状态 (D18 b5)
    uint8_t track_ab : 1;     // 码道信状态 (D18 b6)
    uint8_t track_bq : 1;     // 码道信状态 (D18 b7)
} SADMWorkStatus;  // D18

typedef struct {
    uint8_t moving : 1;       // 0:停止 1:运动 (D18 b0)
    uint8_t thermal_ctrl : 1; // 0:开启 1:关闭 (D18 b1)
    uint8_t heater : 1;       // 0:关断 1:启动 (D18 b2)
    uint8_t encoder : 1;      // 0:有效 1:无效 (D18 b3)
    uint8_t track_a : 1;      // 码道信状态 (D18 b4)
    uint8_t track_b : 1;      // 码道信状态 (D18 b5)
    uint8_t track_ab : 1;     // 码道信状态 (D18 b6)
    uint8_t track_bq : 1;     // 码道信状态 (D18 b7)
} adcangleskStatus;  // D43

typedef struct {
    uint8_t short_circuit : 1;   // 0:正常 1:短路 (D19 b0)
    uint8_t driver_temp : 1;      // 0:正常 1:过温 (D19 b1)
    uint8_t motor_temp : 1;       // 0:正常 1:过温 (D19 b2)
    uint8_t limit_impact : 1;     // 0:正常 1:撞限位 (D19 b3)
    uint8_t track_a_fault : 1;    // 码道故障 (D19 b4)
    uint8_t track_b_fault : 1;    // 码道故障 (D19 b5)
    uint8_t track_z_fault : 1;    // 码道故障 (D19 b6)
    uint8_t track_bq_fault : 1;   // 码道故障 (D19 b7)
} SADMFaultStatus;  // D19

typedef struct {
    uint8_t short_circuit : 1;   // 0:正常 1:短路 (D19 b0)
    uint8_t driver_temp : 1;      // 0:正常 1:过温 (D19 b1)
    uint8_t motor_temp : 1;       // 0:正常 1:过温 (D19 b2)
    uint8_t limit_impact : 1;     // 0:正常 1:撞限位 (D19 b3)
    uint8_t track_a_fault : 1;    // 码道故障 (D19 b4)
    uint8_t track_b_fault : 1;    // 码道故障 (D19 b5)
    uint8_t track_z_fault : 1;    // 码道故障 (D19 b6)
    uint8_t track_bq_fault : 1;   // 码道故障 (D19 b7)
} ADCanglestatus;  // D43

/* ===== 主遥测数据结构 ===== */
typedef struct {
    // ----- 帧头数据 -----
    //uint16_t preamble;      // 包头 0xEB90 (2字节)
    //uint8_t device_id;      // ID字 (1字节)
    //uint16_t data_length;   // 数据长度 0x0035 (2字节)
    uint8_t data_type;      // 数据类型 0x35 (1字节)
    uint8_t data_encoding;   // 应答编码 0x03 (1字节)
    //uint8_t request_id;     // 请求ID (1字节)
    
    // ----- 遥测数据区 -----
    uint8_t req_count;       // D0 遥测请求指令计数
    uint8_t valid_cmd_count; // D1 正确指令计数
    uint8_t error_cmd_count; // D2 错误指令计数
    uint8_t last_cmd_code;   // D3 最近指令执行码
    uint8_t backup_count;    // D4 备份数据接收计数
    uint8_t sade_id;         // D5 SADE主备份ID (0x55:主 0xAA:备)
    
    uint8_t pulse_z_count;   // D6 SADM脉冲Z过零次数
    uint8_t ps_12v;          // D7 二次电源12V电压(需转换)
    uint8_t ps_5v;           // D8 二次电源5V电压(需转换)
    uint8_t ps_1v9;          // D9 二次电源1.9V电压(需转换)
    uint8_t pulse_bq_count;  // D10 SADM脉冲BQ过零次数
    uint8_t ps_12v_current; // D11 二次电源12V电流(需转换)
    uint8_t ps_5v_current;  // D12 二次电源5V电流(需转换)
    uint8_t ps_3v3_current; // D13 二次电源3.3V电流(需转换)
    uint8_t ps_1v9_current; // D14 二次电源1.9V电流(需转换)
    uint8_t motor_current;  // D15 SADM电机电流(需转换)
    CommStatus comm_status;  // D16 通讯状态
    
    SADMMode mode;          // D17 工作模式
    SADMWorkStatus status;  // D18 工作状态
    SADMFaultStatus faults; // D19 故障状态
    
    // ----- 多字节数据 -----
    int16_t motor_position;     // D20-D21 电机位置(需转换)
    int16_t motor_speed;        // D22-D23 电机速度(需转换)
    int16_t encoder_ab_pos;     // D24-D25 编码器AB道位置
    int16_t encoder_ab_speed;   // D26-D27 编码器AB道速度
    int16_t encoder_a_pos;      // D28-D29 编码器A道位置
    int16_t encoder_a_speed;    // D30-D31 编码器A道速度
    int16_t encoder_b_pos;      // D32-D33 编码器B道位置
    int16_t encoder_b_speed;    // D34-D35 编码器B道速度
    int16_t cmd_position;       // D36-D37 指令位置
    int16_t cmd_speed;          // D38-D39 指令速度
    
    // ----- 独立参数 -----
    uint8_t accel_level;      // D40 指令加速度档位(1-20)
    uint8_t sade_temp;        // D41 SADE温度(需转换)
    uint8_t sadm_temp;        // D42 SADM温度(需转换)
    adcangleskStatus anglestatus;
    uint8_t motion_current;   // D44 SADM运动电流(需转换)
    uint8_t holding_current;  // D45 SADM保持电流(需转换)
    uint8_t product_id;       // D46 产品编号(1-255)
    uint8_t yuliu; // D47 通讯复位计数
    uint8_t comm_reset_count; // D47 通讯复位计数
    // ----- 校验和 -----
    uint8_t checksum;          // D49 和校验字
} canfdDJ_all;//电机协议综合



typedef struct {
    // ----- 帧头数据 -----
    //uint16_t preamble;      // 包头 0xEB90 (2字节)
    //uint8_t device_id;      // ID字 (1字节)
    //uint16_t data_length;   // 数据长度 0x0035 (2字节)
    uint8_t data_type;      // 数据类型 0x35 (1字节)
    uint8_t data_encoding;   // 应答编码 0x03 (1字节)
    //uint8_t request_id;     // 请求ID (1字节)
    
    // ----- 遥测数据区 -----
    uint8_t req_count;       // D0 遥测请求指令计数
    uint8_t valid_cmd_count; // D1 正确指令计数
    uint8_t error_cmd_count; // D2 错误指令计数
    uint8_t last_cmd_code;   // D3 最近指令执行码
    uint8_t backup_count;    // D4 备份数据接收计数
    uint8_t sade_id;         // D5 SADE主备份ID (0x55:主 0xAA:备)
    
    //电机遥测数据，去掉eb 90 和校验和
    uint8_t DJ_data[60]; //有效数据53Byte, ID字道有效数据之前 6BYTE.

    // ----- 校验和 -----
    uint8_t checksum;          // D49 和校验字
} canfdDJ_all_t;//电机协议综合

#pragma pack()

// 协议解析
extern uint8_t can_xieyi_test(uint8_t *cmd, uint16_t data_length);
extern uint8_t can_xieyi_test0(uint8_t *cmd, uint16_t data_length);

// 遥测数据组包
extern void canfd_build_yaoce_pack();
extern void canfd_build_dianji_pack_T();

// 发送遥测数据，这里直接传所有数据和总长度，这个函数进行分包发送
extern uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length);


/**
 * @brief 根据配置结构体发送AT指令配置星间模块
 * @param config 星间模块配置结构体指针
 * @return 0:所有指令发送成功 非0:发送失败（返回第一个失败指令的错误码）
 */
extern uint8_t interstellar_config_send(InterstellarConfig *config);
#endif