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

// ����8·gpio���Ʊ���ĵ�ǰ״̬
extern uint8_t out_gpio_status;
// ��������ʹ��
extern uint8_t large_electric_status;
// С�������ʹ��
extern uint16_t small_electric_status;
// ��Դ���ʹ�ܿ���
extern uint8_t power_gpio_status;

extern getADCValue ADCValue; // ��ȡ��������ADCֵ�Ļ���

extern uint8_t canfd_sel;
extern uint8_t canfd_M_sel;

canfdYC_all canfd_yc_all;         // ң������
canfdDJ_all frame;                // ң������
canfdDJ_all_t frame_t;                // ���ң�����ݣ�ֱ��ת�����ݲ����е�����ֵ
FiveWireTelemetryFrame wireframe; // ң������

volatile static uint8_t rqu_id;
volatile static uint8_t current_count_id0 = 0;
volatile static uint8_t current_count_id1 = 0;

extern uint8_t Receive_data1[64];
extern uint8_t Receive_data0[64];

/*
volatile static  uint8_t A_CAN_YC_count1 = 1;      // Aͨ��ң���������
volatile static  uint8_t A_CAN_ZQ_count1= 1 ;      // Aͨ����ȷ֡����
volatile static  uint8_t A_CAN_CW_count1= 1;      // Aͨ������֡����
volatile static  uint8_t A_CAN_CUTTENT_CMD1= 1;   // ���ִ��ָ����
volatile static  uint8_t A_CAN_reset_num1= 0;     // ��λ����
volatile static  uint8_t A_CAN_reset1= 0;         // ��λԭ��
volatile static  uint8_t A_CAN_send_errornum1= 0; // ���ʹ������
volatile static  uint8_t A_CAN_recv_errornum1= 0; // ���մ������
volatile static uint8_t B_CAN_YC_count0= 0;      // Bͨ��ң���������
volatile static uint8_t B_CAN_ZQ_count0= 0;      // Bͨ����ȷ֡����
volatile static uint8_t B_CAN_CW_count0= 0;      // Bͨ������֡����
volatile static uint8_t B_CAN_CUTTENT_CMD0= 0;   // ���ִ��ָ����
volatile static uint8_t B_CAN_reset_num0= 0;     // ��λ����
volatile static uint8_t B_CAN_reset0= 0;         // ��λԭ��
volatile static uint8_t B_CAN_send_errornum0= 0; // ���ʹ������
volatile static uint8_t B_CAN_recv_errornum0= 0; // ���մ������
*/

uint8_t A_CAN_YC_count1 = 0;                      // Aͨ��ң���������
uint8_t A_CAN_ZQ_count1 = 0;                      // Aͨ����ȷ֡����
uint8_t A_CAN_CW_count1 = 0;                      // Aͨ������֡����
uint8_t A_CAN_CUTTENT_CMD1 = 0;                   // ���ִ��ָ����
volatile static uint8_t A_CAN_reset_num1 = 0;     // ��λ����
volatile static uint8_t A_CAN_reset1 = 0;         // ��λԭ��
volatile static uint8_t A_CAN_send_errornum1 = 0; // ���ʹ������
volatile static uint8_t A_CAN_recv_errornum1 = 0; // ���մ������
uint8_t B_CAN_YC_count0 = 0;                      // Bͨ��ң���������
uint8_t B_CAN_ZQ_count0 = 0;                      // Bͨ����ȷ֡����
uint8_t B_CAN_CW_count0 = 0;                      // Bͨ������֡����
uint8_t B_CAN_CUTTENT_CMD0 = 0;                   // ���ִ��ָ����
volatile static uint8_t B_CAN_reset_num0 = 0;     // ��λ����
volatile static uint8_t B_CAN_reset0 = 0;         // ��λԭ��
volatile static uint8_t B_CAN_send_errornum0 = 0; // ���ʹ������
volatile static uint8_t B_CAN_recv_errornum0 = 0; // ���մ������

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

// ң���������
void canfd_build_yaoce_pack()
{
    memset(&canfd_yc_all, 0, sizeof(canfd_yc_all)); // ��ʼ��ң�����ݽṹ��

    // ���̶�ͷ�ֶ�
    canfd_yc_all.head.dataLength = swap_byte(sizeof(canfd_yc_all) - sizeof(canfd_yc_all.head.dataType) * 2); // ���ݳ���
    canfd_yc_all.head.dataType = 0x35;                                                                       // ��������
    canfd_yc_all.head.dataNum = 0x01;                                                                        // ���ݱ���

    // ���̶�canfd��Ϣ����

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

    // ���ң������
    canfd_yc_all.ycData.power_ctr = power_gpio_status;              // ��Դ���ʹ�ܿ���
    canfd_yc_all.ycData.out_gpio_ctrl = out_gpio_status;            // ����8·GPIO���״̬
    canfd_yc_all.ycData.large_electric_ctr = large_electric_status; // ��������ʹ��
    canfd_yc_all.ycData.small_electric_ctr = small_electric_status; // С�������ʹ��
    // ���16·����ɼ��¶Ȼ��ѹģ����

    for (int i = 0; i < 16; i++)
    {
        canfd_yc_all.ycData.out_adc_data[i] = ADCValue.outValue[i]; // ʾ�����ݣ��滻Ϊʵ��ֵ
    }
    // 4·�����¶Ȼ��ѹģ����
    for (int i = 0; i < 4; i++)
    {
        canfd_yc_all.ycData.in_adc[i] = ADCValue.inValue[i]; // ʾ�����ݣ��滻Ϊʵ��ֵ
    }

    // ����Ǽ�ģ�鹤������
    canfd_yc_all.xjData.working_status = 0x01;     // ����״̬ 1BYTE
    canfd_yc_all.xjData.working_mode = 0x01;       // ����ģʽ 1BYTE
    canfd_yc_all.xjData.module_address = 0x0200;   // ģ���ַ 2BYTE
    canfd_yc_all.xjData.network_address = 0x03;    // �����ַ 1BYTE
    canfd_yc_all.xjData.serial_baud_rate = 0x01;   // ���ڲ����� 1BYTE
    canfd_yc_all.xjData.parity_bit = 0x02;         // У��λ 1BYTE
    canfd_yc_all.xjData.airspeed_400mhz = 0x03;    // 400M����(1.2K) 1BYTE
    canfd_yc_all.xjData.airspeed_230mhz = 0x04;    // 230M����(1.2K) 1BYTE
    canfd_yc_all.xjData.channel = 0x05;            // �ŵ� 1BYTE
    canfd_yc_all.xjData.packet_length = 0x06;      // ������� 1BYTE
    canfd_yc_all.xjData.wor_role = 0x07;           // WOR ��ɫ 1BYTE
    canfd_yc_all.xjData.wor_cycle = 0x08;          // WOR ���� 1BYTE
    canfd_yc_all.xjData.tx_power = 0x09;           // ���书�� 1BYTE
    canfd_yc_all.xjData.transmission_mode = 0x0A;  // ����ģʽ 1BYTE
    canfd_yc_all.xjData.relay_mode = 0x0B;         // �м�ģʽ 1BYTE
    canfd_yc_all.xjData.listen_before_talk = 0x0C; // listen before talk 1BYTE
    canfd_yc_all.xjData.env_rssi = 0x0D;           // ���� RSSI 1BYTE
    canfd_yc_all.xjData.data_rssi = 0x0E;          // ���� RSSI 1BYTE
    canfd_yc_all.xjData.encryption_key = 0x0F00;   // ��Կ 2BYTE
    canfd_yc_all.xjData.wor_sleep_delay = 0x1000;  // WOR ��ʱ���� 2BYTE

    canfd_yc_all.xj_pierce_DataLen = 0x0011; // �Ǽ�ģ��͸�����ݴ�С 2BYTE

    // ===== ����У��� =====
    canfd_yc_all.checksum = 0;
    uint8_t *data_ptr = (uint8_t *)&canfd_yc_all;

    // �ۼ��ֽ�1-127�ĺ�
    for (int i = 0; i < sizeof(canfdYC_all) - 1; i++)
    {
        canfd_yc_all.checksum += data_ptr[i];
    }
    canfd_yc_all.xjData.module_address = swap_byte(0x0200);  // ģ���ַ 2BYTE
    canfd_yc_all.xjData.encryption_key = swap_byte(0x0F00);  // ��Կ 2BYTE
    canfd_yc_all.xjData.wor_sleep_delay = swap_byte(0x1000); // WOR ��ʱ���� 2BYTE
    canfd_yc_all.xj_pierce_DataLen = swap_byte(0x0011);      // �Ǽ�ģ��͸�����ݴ�С 2BYTE
}

// ����������
void canfd_build_dianji_pack()
{
    memset(&frame, 0, sizeof(frame)); // ��ʼ��ң�����ݽṹ��

    // ===== 1. ֡ͷ���� ===== [Э��Ҫ��]
    // frame.preamble = 0xEB90;      // �̶���ͷ\n ,
    // frame.preamble = 0x90EB;      // �̶���ͷ\n ,
    // frame.preamble = swap_byte(0xEB90);      // �̶���ͷ\n ,
    // frame.device_id = 0x01;       // �����豸IDΪ1\n
    // frame.data_length = 0x0035;   // ���ݳ��ȹ̶�53�ֽ�\n
    // frame.data_length = swap_byte(0x0035);   // ���ݳ��ȹ̶�53�ֽ�\n
    // frame.data_length = swap_byte(sizeof(frame) - sizeof(frame.device_id)*5); // ���ݳ���
    frame.data_type = 0x35;     // ң���������ͱ�ʶ\n
    frame.data_encoding = 0x03; // Ӧ����� 0x0b (1�ֽ�)
    // frame.request_id = 0xAA;      // ����ID��ʾ��ֵ��\n

    // ===== 2. ң�������� =====
    // ---- ָ����� ----
    frame.req_count = 128;       // D0 ң��������� 128\n
    frame.valid_cmd_count = 120; // D1 ��Чָ�����\n
    frame.error_cmd_count = 8;   // D2 ����ָ�����\n
    frame.last_cmd_code = 0xC3;  // D3 ���ִ��ָ����\n
    frame.backup_count = 5;      // D4 �������ݽ��մ���\n
    frame.sade_id = 0x55;        // D5 ����SADE��0x55:���ݣ�\n

    // ---- ������� ----
    frame.pulse_z_count = 100; // D6 Z�����������\n
    frame.pulse_bq_count = 85; // D10 BQ�����������\n

    // ---- ��Դ������ԭʼADCֵ��----
    frame.ps_12v = 42;         // D7 12V��ѹADCֵ����ת����42 * 69.3 / 255 �� 11.6V��\n
    frame.ps_5v = 128;         // D8 5V��ѹADCֵ\n ����ת����128 * 9.9 / 255 �� 5V��\n
    frame.ps_1v9 = 146;        // D9 1.9V��ѹADCֵ\n ����ת����146 * 3.3 / 255 �� 1.9V��\n
    frame.ps_12v_current = 30; // D11 12V����ADCֵ\n ����ת����146 * 3.3 / 255 �� 1.9V��\n
    frame.ps_5v_current = 77;  // D12 5V����ADCֵ\n
    frame.ps_3v3_current = 57; // D13 3.3V����ADCֵ\n
    frame.ps_1v9_current = 57; // D14 1.9V����ADCֵ\n
    frame.motor_current = 45;  // D15 �������ADCֵ\n

    // ---- ״̬��־��λ��ֵ��----
    // D16 ͨ��״̬ [Э�鶨��]
    frame.comm_status.valid = 0;    // ָ����ȷ\n
    frame.comm_status.data = 0;     // ���ݺϷ�\n
    frame.comm_status.checksum = 0; // У����ȷ\n
    frame.comm_status.reserved = 0; // ����λ��0\n

    // D17 ����ģʽ [Э�鶨��]
    frame.mode.mode = 0x11; // 0x11: ����ģʽ\n

    // D18 ����״̬ [Э�鶨��]
    frame.status.moving = 1;       // �˶���\n
    frame.status.thermal_ctrl = 0; // �¿ؿ���\n
    frame.status.heater = 0;       // �������ر�\n
    frame.status.encoder = 0;      // ��������Ч\n
    frame.status.track_a = 1;      // ���A����\n
    frame.status.track_b = 1;      // ���B����\n
    frame.status.track_ab = 1;     // ���AB����\n
    frame.status.track_bq = 1;     // ���BQ����\n

    // D19 ����״̬ [Э�鶨��]
    memset(&frame.faults, 0, sizeof(SADMFaultStatus)); // ���й���λ���㣨�޹��ϣ�\n

    // ===== 3. ���ֽ����� =====

    frame.motor_position = 8500;   // D20-D21 ���λ�ã���ת����\n
    frame.motor_speed = 1200;      // D22-D23 ����ٶȣ�RPM��\n
    frame.encoder_ab_pos = 8400;   // D24-D25 AB������λ��\n
    frame.encoder_ab_speed = 1180; // D26-D27 AB�������ٶ�\n
    frame.encoder_a_pos = 8450;    // D28-D29 A������λ��\n
    frame.encoder_a_speed = 1190;  // D30-D31 A�������ٶ�\n
    frame.encoder_b_pos = 8350;    // D32-D33 B������λ��\n
    frame.encoder_b_speed = 1170;  // D34-D35 B�������ٶ�\n
    frame.cmd_position = 8600;     // D36-D37 ָ��λ��\n
    frame.cmd_speed = 1300;        // D38-D39 ָ���ٶ�\n

    /*
    frame.motor_position = swap_byte(0x0035);     // D20-D21 ���λ�ã���ת����\n
    frame.motor_speed = swap_byte(0x0035);        // D22-D23 ����ٶȣ�RPM��\n
    frame.encoder_ab_pos = swap_byte(0x0035);     // D24-D25 AB������λ��\n
    frame.encoder_ab_speed = swap_byte(0x0035);    // D26-D27 AB�������ٶ�\n
    frame.encoder_a_pos = swap_byte(0x0035); // D28-D29 A������λ��\n
    frame.encoder_a_speed = swap_byte(0x0035);     // D30-D31 A�������ٶ�\n
    frame.encoder_b_pos = 8350;      // D32-D33 B������λ��\n
    frame.encoder_b_speed = 1170;    // D34-D35 B�������ٶ�\n
    frame.cmd_position = 8600;       // D36-D37 ָ��λ��\n
    frame.cmd_speed = 1300;          // D38-D39 ָ���ٶ�\n
    */

    // ===== 4. �������� =====
    frame.accel_level = 8; // D40 ���ٶȵ�λ��1-20��\n
    frame.sade_temp = 40;  // D41 SADE�¶ȣ���ת����\n
    frame.sadm_temp = 35;  // D42 SADM�¶ȣ���ת����\n

    // D43 ����״̬ [Э�鶨��]
    frame.anglestatus.moving = 0;       // �˶���\n
    frame.anglestatus.thermal_ctrl = 0; // �¿ؿ���\n
    frame.anglestatus.heater = 0;       // �������ر�\n
    frame.anglestatus.encoder = 0;      // ��������Ч\n
    frame.anglestatus.track_a = 0;      // ���A����\n
    frame.anglestatus.track_b = 0;      // ���B����\n
    frame.anglestatus.track_ab = 0;     // ���AB����\n
    frame.anglestatus.track_bq = 0;     // ���BQ����\n

    frame.motion_current = 50;  // D44 �˶�����ADCֵ\n
    frame.holding_current = 20; // D45 ���ֵ���ADCֵ\n
    frame.product_id = 0x10;    // D46 ��Ʒ���\n
    frame.comm_reset_count = 2; // D47 ͨ�Ÿ�λ����\n
    frame.yuliu = 0;            // D48 Ԥ��\n
    // ===== 5. У��ͼ��� =====
    frame.checksum = 0;                        // ������\n
    uint8_t *data_ptr = (uint8_t *)&frame + 7; // ��D0��ʼ������7�ֽ�֡ͷ��\n
    for (int i = 0; i < 49; i++)
    {                                  // D0-D48��49�ֽ�
        frame.checksum += data_ptr[i]; // D49 �ۼӺ�У��\n
    }
    frame.motor_position = swap_byte(frame.motor_position);     // D20-D21 ���λ�ã���ת����\n
    frame.motor_speed = swap_byte(frame.motor_speed);           // D22-D23 ����ٶȣ�RPM��\n
    frame.encoder_ab_pos = swap_byte(frame.encoder_ab_pos);     // D24-D25 AB������λ��\n
    frame.encoder_ab_speed = swap_byte(frame.encoder_ab_speed); // D26-D27 AB�������ٶ�\n
    frame.encoder_a_pos = swap_byte(frame.encoder_a_pos);       // D28-D29 A������λ��\n
    frame.encoder_a_speed = swap_byte(frame.encoder_a_speed);   // D30-D31 A�������ٶ�\n
    frame.encoder_b_pos = swap_byte(frame.encoder_b_pos);       // D32-D33 B������λ��\n
    frame.encoder_b_speed = swap_byte(frame.encoder_b_speed);   // D34-D35 B�������ٶ�\n
    frame.cmd_position = swap_byte(frame.cmd_position);         // D36-D37 ָ��λ��\n
    frame.cmd_speed = swap_byte(frame.cmd_speed);               // D38-D39 ָ���ٶ�\n
}



// ����������  ֱ��ת����
void canfd_build_dianji_pack_T()
{
    memset(&frame_t, 0, sizeof(frame_t)); // ��ʼ��ң�����ݽṹ��

    // ===== 1. ֡ͷ���� ===== [Э��Ҫ��]
    // frame_t.preamble = 0xEB90;      // �̶���ͷ\n ,
    // frame_t.preamble = 0x90EB;      // �̶���ͷ\n ,
    // frame_t.preamble = swap_byte(0xEB90);      // �̶���ͷ\n ,
    // frame_t.device_id = 0x01;       // �����豸IDΪ1\n
    // frame_t.data_length = 0x0035;   // ���ݳ��ȹ̶�53�ֽ�\n
    // frame_t.data_length = swap_byte(0x0035);   // ���ݳ��ȹ̶�53�ֽ�\n
    // frame_t.data_length = swap_byte(sizeof(frame_t) - sizeof(frame_t.device_id)*5); // ���ݳ���
    frame_t.data_type = 0x35;     // ң���������ͱ�ʶ\n
    frame_t.data_encoding = 0x03; // Ӧ����� 0x0b (1�ֽ�)
    // frame_t.request_id = 0xAA;      // ����ID��ʾ��ֵ��\n

    // ===== 2. ң�������� =====
    // ---- ָ����� ----
    frame_t.req_count = 128;       // D0 ң��������� 128\n
    frame_t.valid_cmd_count = 120; // D1 ��Чָ�����\n
    frame_t.error_cmd_count = 8;   // D2 ����ָ�����\n
    frame_t.last_cmd_code = 0xC3;  // D3 ���ִ��ָ����\n
    frame_t.backup_count = 5;      // D4 �������ݽ��մ���\n
    frame_t.sade_id = 0x55;        // D5 ����SADE��0x55:���ݣ�\n

    // ===== 3. ���ң�������� =====
    
    // ===== 5. У��ͼ��� =====
    frame_t.checksum = 0;                        // ������\n
    uint8_t *data_ptr = (uint8_t *)&frame_t + 7; // ��D0��ʼ������7�ֽ�֡ͷ��\n
    for (int i = 0; i < 49; i++)
    {                                  // D0-D48��49�ֽ�
        frame_t.checksum += data_ptr[i]; // D49 �ۼӺ�У��\n
    }
}

// wire�������
void canfd_build_wire_pack()
{
    memset(&wireframe, 0, sizeof(wireframe)); // ��ʼ��ң�����ݽṹ��

    // ===== ��һ֡���� =====
    wireframe.data_type = 0x35;                // �̶���������ֵ
    wireframe.data_encoding = 0x02;            // �̶����ݱ���ֵ
    wireframe.data_length = swap_byte(0x007D); // ���ֽ�3��127���ܳ���,7D
    // wireframe.data_length = swap_byte(sizeof(wireframe) - sizeof(wireframe.data_type)*4); // ���ݳ���

    // ���ǰ5·�¶����� (ʵ��ֵ����16������Э���ʾ����)
    wireframe.first_5wires.temp1 = 25 * 100; // 25.0��C (250 = 25.0 * 10)
    wireframe.first_5wires.temp2 = 25 * 100; // 25.5��C
    wireframe.first_5wires.temp3 = 0 * 100;  // 0.0��C (��·�����)
    wireframe.first_5wires.temp4 = 30 * 100; // 30.0��C
    wireframe.first_5wires.temp5 = 30 * 100; // 25.0��C

    // ���Ԥ������
    memset(wireframe.reserved1, 0, sizeof(wireframe.reserved1));

    // ===== �ڶ�֡���� =====
    // ireframe.frame_seq = 0x01;         // �ڶ�֡��Ź̶�Ϊ1

    // ����5·�¶�����
    wireframe.second_5wires.temp6 = 25 * 100;  //  // 28.0��C
    wireframe.second_5wires.temp7 = 30 * 100;  // 9.0��C
    wireframe.second_5wires.temp8 = 25 * 100;  //  // 26.0��C
    wireframe.second_5wires.temp9 = 30 * 100;  // 25.5��C
    wireframe.second_5wires.temp10 = 18 * 100; // 31.0��C

    // ���Ԥ������
    memset(wireframe.reserved2, 0, sizeof(wireframe.reserved2));

    // ===== ����У��� =====
    wireframe.checksum = 0;
    uint8_t *data_ptr = (uint8_t *)&wireframe;

    // �ۼ��ֽ�1-127�ĺ�
    for (int i = 0; i < sizeof(FiveWireTelemetryFrame) - 1; i++)
    {
        wireframe.checksum += data_ptr[i];
    }

    // ���ǰ5·�¶����� (ʵ��ֵ����16������Э���ʾ����)
    wireframe.first_5wires.temp1 = swap_byte(wireframe.first_5wires.temp1);
    wireframe.first_5wires.temp2 = swap_byte(wireframe.first_5wires.temp2);
    wireframe.first_5wires.temp3 = swap_byte(wireframe.first_5wires.temp3);
    wireframe.first_5wires.temp4 = swap_byte(wireframe.first_5wires.temp4);
    wireframe.first_5wires.temp5 = swap_byte(wireframe.first_5wires.temp5);

    // ����5·�¶�����
    wireframe.second_5wires.temp6 = swap_byte(wireframe.second_5wires.temp6);
    wireframe.second_5wires.temp7 = swap_byte(wireframe.second_5wires.temp7);
    wireframe.second_5wires.temp8 = swap_byte(wireframe.second_5wires.temp8);
    wireframe.second_5wires.temp9 = swap_byte(wireframe.second_5wires.temp9);
    wireframe.second_5wires.temp10 = swap_byte(wireframe.second_5wires.temp10);
}

// Э���������
ParseStatus parse_can_message(const uint8_t *data, size_t data_length, CommandType *cmd_type, void **cmd_data)
{
    if (data == NULL || cmd_type == NULL || cmd_data == NULL || data_length < 3)
    {
        Printf("parse_can_message arg error\r\n");
        return PARSE_ERROR_INSUFFICIENT_DATA;
    }

    // ��ȡָ������
    uint8_t cmd = data[1]; // ���ݱ��(D3)�ֶ�
    *cmd_type = cmd;

    // ����ָ�����ͽ�������
    switch (*cmd_type)
    {
    case CMD_TELEMETRY_REQ:
    case CMD_5WIRE_TEMP_REQ:
    case CMD_INTERSTELLAR_RESET:
    case CMD_DIANJI_REQ:
        // ��Щָ��û�в�����ֻ����֤����   ���������͵����ֽ�У���֮ǰ���������ݳ���
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
        // ��Щָ����2�ֽڲ��� (ͨ����+״̬)
        if (data_length < 3)
        { // 3�ֽ�ͷ�� + 2�ֽ�����
            return PARSE_ERROR_INVALID_LENGTH;
        }
        {
            GPIOCtrl *ctrl = (GPIOCtrl *)malloc(sizeof(GPIOCtrl));
            if (ctrl == NULL)
            {
                return PARSE_ERROR_INSUFFICIENT_DATA;
            }
            // rl->channel = data[4]; // ��1�������ֽ�
            // rl->state = data[5];   // ��2�������ֽ�
            ctrl->channel = data[2]; // ��1�������ֽ�
            ctrl->state = data[3];   // ��2�������ֽ�
            *cmd_data = ctrl;
        }
        break;

    case CMD_LOW_CURRENT_SETTING:
        A_CAN_reset_num1 = 1;
        // С�������ʹ�����ã�2�ֽڲ���
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
            // ctrl->channel = data[4]; // ��1�������ֽ�
            // ctrl->state = data[5];   // ��2�������ֽ�
            ctrl->channel = data[2]; // ��1�������ֽ�
            ctrl->state = data[3];   // ��2�������ֽ�
            *cmd_data = ctrl;
        }
        break;

    case CMD_INTERSTELLAR_CONFIG:
        A_CAN_reset_num1 = 1;
        // �Ǽ�ģ������ָ�22�ֽڲ���
        // if (data_length != 24)
        // wj
        if (data_length != 24)
        { // 3�ֽ�ͷ�� + 22�ֽ�����
            Printf("xing jian config data length error\r\n");
            return PARSE_ERROR_INVALID_LENGTH;
        }
        {
            InterstellarConfig *config = (InterstellarConfig *)malloc(sizeof(InterstellarConfig));
            if (config == NULL)
            {
                return PARSE_ERROR_INSUFFICIENT_DATA;
            }
            // ����22�ֽ���������
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
        // ͸��ģʽ���ݣ����ȿɱ�
        if (data_length < 3)
        {
            return PARSE_ERROR_INSUFFICIENT_DATA;
        }
        {
            // Ϊ���ݷ����ڴ沢����
            uint8_t *transparent_data = (uint8_t *)malloc(data_length - 2);
            if (transparent_data == NULL)
            {
                return PARSE_ERROR_INSUFFICIENT_DATA;
            }
            memcpy(transparent_data, &data[2], data_length - 2);
            *cmd_data = transparent_data;
        }
        break;
    case CMD_DIANJI_CTL: // ���ָ��ת��
        A_CAN_reset_num1 = 1;
        // ���ָ��ת�����ݣ����ȿɱ�
        if (data_length < 3)
        {
            return PARSE_ERROR_INSUFFICIENT_DATA;
        }
        {
            // Ϊ���ݷ����ڴ沢����
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

// �ͷŽ�������������ڴ�
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
        // �����������Ͳ������ڴ�
        break;
    }
}
#if 1
// ����ң�����ݣ�����ֱ�Ӵ��������ݺ��ܳ��ȣ�����������зְ�����
uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length)
{
    uint8_t Send_data1[64] = {0};                     // ÿ�����ݰ��Ĵ�СΪ64�ֽ�
    uint16_t total_packets = (data_length + 63) / 64; // ���������ݰ���������ȡ��
    uint8_t packet_number = 0;                        // ��ǰ���ݰ����
    uint16_t actual_len;
    volatile uint8_t status1 = 0;
    // CANFD1_Frame_Config(0x147, Byte_64);
    current_count_id1 = (current_count_id0 == 0xff) ? 0 : current_count_id1 + 1;
    // A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 +1;
    //  CANFD1_Frame_Config(0x147, Byte_64);

    // ��������64�ֽ�����
    while (data_length >= 64)
    {
        if (status1 == 0)
        {
            CANFD1_Frame_rev(0x08, current_count_id0); // ����֡ ,��֡
            status1++;
        }
        else
        {
            status1++;
            CANFD1_Frame_rev(0x09, current_count_id0); // ����֡ ,�м�֡
        }

        memcpy(Send_data1, data, 64); // ����ǰ64�ֽ�
        CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_64);

        data += 64;        // �ƶ�����ָ��
        data_length -= 64; // ����ʣ�����ݳ���
        packet_number++;
    }
    // ����ʣ�����ݣ�С��64�ֽڣ�
    if (data_length > 0)
    {

        actual_len = data_length;
        if (packet_number > 0) // �������
        {
            Send_data1[0] = packet_number;             // ֡���
            memcpy(&Send_data1[1], data, data_length); // ����ʣ�����ݣ����ݴ�1��ʼ
            CANFD1_Frame_rev(0x9, current_count_id0);  // ��֡��β֡ 0x9
            actual_len += 1;
        }
        else // ��������
        {
            memcpy(&Send_data1, data, data_length);    // �����
            CANFD1_Frame_rev(0x07, current_count_id0); // ��֡��0x7
        }

        // ѡ����ӽ��ı�׼DLC
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
            dlc = Byte_64; // 33-64�ֽ�

        // �����������ݰ�
        if (dlc == Byte_64)
        {
            CANFD_Transmit(CANFD1, TB1, Send_data1, dlc); // 64�ֽ���TB1
        }
        else
        {
            CANFD_Transmit(CANFD1, TB0, Send_data1, dlc); // ������TB0
        }
    }
    return 0;
}

#else
uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length)
{
    uint8_t Send_data1[64] = {0};                     // ÿ�����ݰ��Ĵ�СΪ64�ֽ�
    uint16_t total_packets = (data_length + 63) / 64; // ���������ݰ���������ȡ��
    uint8_t packet_number = 0;                        // ��ǰ���ݰ����
    uint16_t actual_len;
    volatile uint8_t status1 = 0;
    uint8_t error_count = 0;
    current_count_id1 = (current_count_id0 == 0xff) ? 0 : current_count_id1 + 1;

    // ��������64�ֽ�����
    while (data_length >= 64)
    {
        if (status1 == 0)
        {
            CANFD1_Frame_rev(0x08, current_count_id0); // ����֡ ,��֡
            status1++;
        }
        else
        {
            status1++;
            CANFD1_Frame_rev(0x09, current_count_id0); // ����֡ ,�м�֡
        }

        memcpy(Send_data1, data, 64); // ����ǰ64�ֽ�
        if (CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_64) != 0)
        {
            error_count++; // ��¼ʧ��֡
            Printf("Frame %d/%d failed\r\n", packet_number + 1, total_packets);
        }
    }

    data += 64;        // �ƶ�����ָ��
    data_length -= 64; // ����ʣ�����ݳ���
    packet_number++;
}
// ����ʣ�����ݣ�С��64�ֽڣ�
if (data_length > 0)
{

    actual_len = data_length;
    if (packet_number > 0) // �������
    {
        Send_data1[0] = packet_number;             // ֡���
        memcpy(&Send_data1[1], data, data_length); // ����ʣ�����ݣ����ݴ�1��ʼ
        CANFD1_Frame_rev(0x9, current_count_id0);  // ��֡��β֡ 0x9
        actual_len += 1;
    }
    else // ��������
    {
        memcpy(&Send_data1, data, data_length);    // �����
        CANFD1_Frame_rev(0x07, current_count_id0); // ��֡��0x7
    }

    // ѡ����ӽ��ı�׼DLC
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
        dlc = Byte_64; // 33-64�ֽ�

    // �����������ݰ�
    if (dlc == Byte_64)
    {
        CANFD_Transmit(CANFD1, TB1, Send_data1, dlc); // 64�ֽ���TB1
    }
    else
    {
        CANFD_Transmit(CANFD1, TB0, Send_data1, dlc); // ������TB0
    }
}
return 0;
}
#endif

// ����ң�����ݣ�����ֱ�Ӵ��������ݺ��ܳ��ȣ�����������зְ�����
uint8_t canfd_send_all_data0(uint8_t *data, uint16_t data_length)
{
    uint8_t Send_data0[64] = {0};                     // ÿ�����ݰ��Ĵ�СΪ64�ֽ�
    uint16_t total_packets = (data_length + 63) / 64; // ���������ݰ���������ȡ��
    uint8_t packet_number = 0;                        // ��ǰ���ݰ����
    // Printf("data_length(canfd_send_all_data0)is %d\r\n", data_length);
    uint16_t actual_len;
    volatile uint8_t status = 0;
    volatile uint8_t status_dan = 0;
    // B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 +1;
    //  CANFD1_Frame_Config(0x147, Byte_64);
    current_count_id0 = (current_count_id0 == 0xff) ? 0 : current_count_id0 + 1;
    // ��������64�ֽ�����
    while (data_length >= 64)
    {
        if (status == 0)
        {
            CANFD0_Frame_rev(0x08, current_count_id0); // ����֡ ,��֡
            status++;
        }
        else
        {
            status++;
            CANFD0_Frame_rev(0x09, current_count_id0); // ����֡ ,�м�֡
        }

        memcpy(Send_data0, data, 64); // ����ǰ64�ֽ�
        CANFD_Transmit(CANFD0, TB1, Send_data0, Byte_64);

        data += 64;        // �ƶ�����ָ��
        data_length -= 64; // ����ʣ�����ݳ���
        packet_number++;
        // Printf("CANFD_Transmit(CANFD0) 0. \r\n");
    }
    // ����ʣ�����ݣ�С��64�ֽڣ�
    if (data_length > 0)
    {
        actual_len = data_length;
        if (packet_number > 0) // �������
        {
            Send_data0[0] = packet_number;             // ֡���
            memcpy(&Send_data0[1], data, data_length); // ����ʣ�����ݣ����ݴ�1��ʼ
            CANFD0_Frame_rev(0x9, current_count_id0);  // ��֡��β֡ 0x9
            actual_len += 1;
        }
        else // ��������
        {
            CANFD0_Frame_rev(0x07, current_count_id0); // ��֡��0x7
            memcpy(&Send_data0, data, data_length);    // �����
        }

        // ѡ����ӽ��ı�׼DLC
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
            dlc = Byte_64; // 33-64�ֽ�

        // �����������ݰ�
        if (dlc == Byte_64)
        {
            CANFD_Transmit(CANFD0, TB1, Send_data0, dlc); // 64�ֽ���TB1
        }
        else
        {
            CANFD_Transmit(CANFD0, TB0, Send_data0, dlc); // ������TB0
        }
    }
    return 0;
}

/*
uint8_t canfd_send_all_data(uint8_t *data, uint16_t data_length)
{
    uint8_t Send_data1[64];                           // ÿ�����ݰ��Ĵ�СΪ64�ֽ�
    uint16_t total_packets = (data_length + 63) / 64; // ���������ݰ���������ȡ��
    uint8_t packet_number = -1;                       // ��ǰ���ݰ����
    Printf("data_length(canfd_send_all_data)is %d\r\n", data_length);
    // CANFD1_Frame_Config(0x147, Byte_64);

    // ����ʣ�����ݰ�
    while (data_length > 0)
    {
        packet_number++; // �������ݰ����
        if (data_length > 64)
        {
            memcpy(Send_data1, data, 64); // ����ǰ64�ֽ�
            data += 64;                   // �ƶ�����ָ��
            data_length -= 64;            // ����ʣ�����ݳ���
            CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_64);
        }
        else
        {
            if (packet_number > 0) // ���ǵ�һ�����ݰ�ʱ�����ֽ���֡���
            {
                Send_data1[0] = packet_number; // ֡���
                data_length += 1;              // ��Ϊ�����1���ֽڣ����Է��͵�ʱ����
                memcpy(&Send_data1[1], data, data_length); // ����ʣ������
            }
            else // �ǵ�һ�����ݰ�ʱ��ֱ�ӿ�������
                memcpy(Send_data1, data, data_length);


            if (data_length != Byte_64  && data_length != Byte_32 && data_length != Byte_64 && data_length != Byte_8 && data_length != Byte_16)
            {
                Printf("canfd_send_all_data error data_length=%d\r\n", data_length);
                return -1;
            }
            // CANFD1_Frame_Config(0x147, data_length);
            if(data_length == Byte_64)
                CANFD_Transmit(CANFD1, TB1, Send_data1, data_length); // TB1ͨ�����õ���64�ֽ�
            else if(data_length == Byte_32)
                CANFD_Transmit(CANFD1, TB0, Send_data1, data_length); // TB0ͨ�����õ���32�ֽ�
            else
                Printf("not support send other Byte\r\n");
            data_length = 0;                                      // ���ݳ���Ϊ0������ѭ��
        }
    }
    return 0;
}
*/

/**
 * @brief �������ýṹ�巢��ATָ�������Ǽ�ģ��
 * @param config �Ǽ�ģ�����ýṹ��ָ��
 * @return 0:����ָ��ͳɹ� ��0:����ʧ�ܣ����ص�һ��ʧ��ָ��Ĵ����룩
 */
uint8_t interstellar_config_send(InterstellarConfig *config)
{
    uint8_t ret;

    // �����Ϸ��Լ��
    if (config == NULL)
    {
        return -1; // ���ýṹ��Ϊ��
    }

    // �ڿ�ʼ����ǰ���������ڻ�����������֮ǰ����Ӧ���ݸ���
    delay_ms(100); // �ȴ������ȶ�

    // 1. ���ù���ģʽ (AT+MODE=work_mode)
    ret = at_send_cmd(AT_CMD_1PARAM_MODE, config->work_mode, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_MODE.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_MODE error.\r\n");
        return ret;
    }
    delay_ms(50); // �ȴ��Ǽ�ģ�鴦��ָ��

    // 2. ����ģ���ַ (AT+ADDR=module_addr)
    ret = at_send_cmd(AT_CMD_1PARAM_ADDR, config->module_addr, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_ADDR.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_ADDR error.\r\n");
        return ret;
    }

    // 3. ��������ID (AT+NETID=network_addr)
    ret = at_send_cmd(AT_CMD_1PARAM_NETID, config->network_addr, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_NETID.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_NETID error.\r\n");
        return ret;
    }

    // 4. ���ô��ڲ����ʺ�У��λ (AT+UART=baud_rate,parity)
    ret = at_send_cmd(AT_CMD_2PARAM_UART, config->baud_rate, config->parity);
    // Printf("cat_send_cmd: AT_CMD_2PARAM_UART.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_2PARAM_UART error.\r\n");
        return ret;
    }

    // 5. ����400MHzƵ�ο������� (AT+RATE=freq_400_speed)
    // ע������Ӳ��ʵ��Ƶ��ѡ���Ӧ�������������ʹ��400MHzƵ��
    ret = at_send_cmd(AT_CMD_1PARAM_RATE, config->freq_400_speed, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_RATE.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_RATE error.\r\n");
        return ret;
    }

    // 6. �����ŵ� (AT+CHANNEL=channel)
    ret = at_send_cmd(AT_CMD_1PARAM_CHANNEL, config->channel, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_CHANNEL.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_CHANNEL error.\r\n");
        return ret;
    }

    // 7. ���÷������ (AT+PACKET=packet_length)
    ret = at_send_cmd(AT_CMD_1PARAM_PACKET, config->packet_length, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_PACKET.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_PACKET error.\r\n");
        return ret;
    }

    // 8. ����WOR��ɫ (AT+WOR=wor_role)
    ret = at_send_cmd(AT_CMD_1PARAM_WOR, config->wor_role, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_WOR.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_WOR error.\r\n");
        return ret;
    }

    // 9. ���÷��书�� (AT+POWER=tx_power)
    ret = at_send_cmd(AT_CMD_1PARAM_POWER, config->tx_power, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_POWER.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_POWER error.\r\n");
        return ret;
    }

    // 10. ���ô���ģʽ (AT+TRANS=tx_mode)
    ret = at_send_cmd(AT_CMD_1PARAM_TRANS, config->tx_mode, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_TRANS.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_TRANS error.\r\n");
        return ret;
    }

    // 11. �����м�ģʽ (AT+ROUTER=relay_mode)
    ret = at_send_cmd(AT_CMD_1PARAM_ROUTER, config->relay_mode, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_ROUTER.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_ROUTER error.\r\n");
        return ret;
    }

    // 12. ����LBT���� (AT+LBT=lbt)
    ret = at_send_cmd(AT_CMD_1PARAM_LBT, config->lbt, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_LBT.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_LBT error.\r\n");
        return ret;
    }

    // 13. ���û�������RSSI (AT+ERSSI=env_rssi)
    ret = at_send_cmd(AT_CMD_1PARAM_ERSSI, config->env_rssi, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_ERSSI.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_ERSSI error.\r\n");
        return ret;
    }

    // 14. ��������RSSI (AT+DRSSI=data_rssi)
    ret = at_send_cmd(AT_CMD_1PARAM_DRSSI, config->data_rssi, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_DRSSI.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_DRSSI error.\r\n");
        return ret;
    }

    // 15. ������Կ (AT+KEY=key)
    ret = at_send_cmd(AT_CMD_1PARAM_KEY, config->key, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_KEY.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_KEY error.\r\n");
        return ret;
    }

    // 16. ����WOR�ӳ�����ʱ�� (AT+DELAY=wor_sleep_delay)
    ret = at_send_cmd(AT_CMD_1PARAM_DELAY, config->wor_sleep_delay, -1);
    // Printf("cat_send_cmd: AT_CMD_1PARAM_DELAY.\r\n");
    if (ret != 0)
    {
        Printf("cat_send_cmd: AT_CMD_1PARAM_DELAY error.\r\n");
        return ret;
    }

    // �������÷�����ɺ󣬿�ѡ��������ָ��ʹ������Ч
    ret = at_send_cmd(AT_CMD_NONE_RESET, -1, -1);
    return ret;
}

/**
 * @brief ��ң������ָ������ڣ� �����ת��Э���У�����ң������ָ�
 * @return 0:�ɹ�, ��0:ʧ��
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

    // ����ͷ�ֶ�
    packet[0] = 0xEB; // ��ͷ��1�ֽ�
    packet[1] = 0x90; // ��ͷ��2�ֽ�
    packet[2] = 0x00; // ID��
    packet[3] = 0x00; // ���ݳ��ȸ߰�λ
    packet[4] = 0x03; // ���ݳ��ȵװ�λ
    packet[5] = 0x05; // ��������
    packet[6] = 0xff; // ��������
    // packet[7] = rqu_id; // ����ID
    packet[7] = 1; // ����ID

    // �����У�飨�Ӱ�ͷ�����ݲ��ֵ������ֽ��ۼӣ�
    // uint8_t checksum = 0;
    // for (uint16_t i = 0; i < total_len-1; i++)
    //{
    //    checksum += packet[i];
    //}
    // packet[total_len-1] = checksum; // У����
    packet[total_len - 1] = 0x08; // У����
    // �������ݰ�������
    if (uart_send_hex_datas(USART5, packet, total_len) != 0)
    {
        Printf("uart_send_hex_datas USART0 failed!\r\n");
        free(packet);
        return 3; // ����ʧ��
    }
#if 0
    if (uart_send_hex_datas(USART1, packet, total_len) != 0)
    {
        Printf("uart_send_hex_datas USART1 failed!\r\n");
        free(packet);
        return 3; // ����ʧ��
    }
#endif
    // �������
    // uart_send_hex_datas(USART6, packet, total_len);//��ӡ������Ϣ

    // �ͷ��ڴ�
    free(packet);
    return 0; // �ɹ�
}

// CMD_TELEMETRY_REQ = 0x01,        // ң������
// CMD_5WIRE_TEMP_REQ = 0x02,       // 5·1-wire�¶�ң��ɼ�����
// CMD_POWER_CONTROL = 0x03,        // ��Դ���ʹ�ܿ�������
// CMD_GPIO_CONTROL = 0x04,         // ����8·GPIO�������
// CMD_HIGH_CURRENT_CONTROL = 0x05, // ��������ʹ�ܿ�������
// CMD_LOW_CURRENT_SETTING = 0x06,  // С�������ʹ������ң��ָ��
// CMD_INTERSTELLAR_CONFIG = 0x07,  // �Ǽ�ģ������ָ��
// CMD_INTERSTELLAR_RESET = 0x08,   // �Ǽ�ģ�鸴λ
// CMD_TRANSPARENT_DATA = 0x09      // ͸��ģʽ���ݷ��͵��Ǽ�ģ��

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
    // wj:��ӡcmd_dataֵ������22�ֽ���������
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

        case CMD_TELEMETRY_REQ: // ң������
            A_CAN_YC_count1 = (A_CAN_YC_count1 == 0xff) ? 0 : A_CAN_YC_count1 + 1;
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ. \r\n");
            canfd_build_yaoce_pack();
            canfd_send_all_data((uint8_t *)&canfd_yc_all, sizeof(canfd_yc_all));
            break;
        case CMD_5WIRE_TEMP_REQ: // 5·1-wire�¶�ң��ɼ�����
            A_CAN_YC_count1 = (A_CAN_YC_count1 == 0xff) ? 0 : A_CAN_YC_count1 + 1;
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ no code. \r\n");
            canfd_build_wire_pack();
            canfd_send_all_data((uint8_t *)&wireframe, sizeof(wireframe));
            /* code */
            break;
        case CMD_POWER_CONTROL: // ��Դ���ʹ�ܿ�������
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ. \r\n");
            powerctrl = (PowerControl *)cmd_data;
            power_gpio_ctr(powerctrl->channel, powerctrl->state);
            break;
        case CMD_GPIO_CONTROL: // ����8·GPIO�������
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_GPIO_CONTROL. \r\n");
            outctrl = (GPIOCtrl *)cmd_data;
            out_gpio_ctr(outctrl->channel, outctrl->state);
            break;
        case CMD_HIGH_CURRENT_CONTROL: // ��������ʹ�ܿ�������
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_HIGH_CURRENT_CONTROL. \r\n");
            largectrl = (GPIOCtrl *)cmd_data;
            large_electric_gpio_ctr(largectrl->channel, largectrl->state);
            break;
        case CMD_LOW_CURRENT_SETTING: // С�������ʹ������ң��ָ��
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_LOW_CURRENT_SETTING. \r\n");
            lowctrl = (GPIOCtrl *)cmd_data;
            small_electric_gpio_ctr(lowctrl->channel, lowctrl->state);
            break;
        case CMD_INTERSTELLAR_CONFIG: // �Ǽ�ģ������ָ��
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_INTERSTELLAR_CONFIG. \r\n");
            InterstellarConfig *config = (InterstellarConfig *)cmd_data;
            interstellar_config_send(config);
            break;
        case CMD_INTERSTELLAR_RESET: // �Ǽ�ģ�鸴λ
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_INTERSTELLAR_RESET. \r\n");
            xingjian_reset(0); // 0/1 ��������ϵ?
            break;
        case CMD_TRANSPARENT_DATA: // ͸��ģʽ���ݷ��͵��Ǽ�ģ��
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data(cmd,data_length);
            // Printf("can_xieyi_test:CMD_TRANSPARENT_DATA. \r\n");

            break;
        case CMD_DIANJI_CTL: // �������ָ��ת��
            A_CAN_ZQ_count1 = (A_CAN_ZQ_count1 == 0xff) ? 0 : A_CAN_ZQ_count1 + 1;
            // Printf("can_xieyi_test:CMD_DIANJI_CTL. \r\n");
            dj_uart_cmd_analyze(cmd_data, data_length - 2); // data_length�������ܳ��ȣ���ȥ2���ֽڵ�ͷ������ʵ�����ݳ���
            break;
        case CMD_DIANJI_REQ: // ���ң������
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

    // wj:��ӡcmd_dataֵ������22�ֽ���������
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
        case CMD_TELEMETRY_REQ: // ң������
                                // Printf("can_xieyi_test:CMD_TELEMETRY_REQ. \r\n");
            B_CAN_YC_count0 = (B_CAN_YC_count0 == 0xff) ? 0 : B_CAN_YC_count0 + 1;
            canfd_build_yaoce_pack();
            canfd_send_all_data0((uint8_t *)&canfd_yc_all, sizeof(canfd_yc_all));
            break;
        case CMD_5WIRE_TEMP_REQ: // 5·1-wire�¶�ң��ɼ�����
            B_CAN_YC_count0 = (B_CAN_YC_count0 == 0xff) ? 0 : B_CAN_YC_count0 + 1;
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ no code. \r\n");
            canfd_build_wire_pack();
            canfd_send_all_data0((uint8_t *)&wireframe, sizeof(wireframe));
            /* code */
            break;
        case CMD_POWER_CONTROL: // ��Դ���ʹ�ܿ�������
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_TELEMETRY_REQ. \r\n");
            powerctrl = (PowerControl *)cmd_data;
            power_gpio_ctr(powerctrl->channel, powerctrl->state);
            break;
        case CMD_GPIO_CONTROL: // ����8·GPIO�������
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_GPIO_CONTROL. \r\n");
            outctrl = (GPIOCtrl *)cmd_data;
            out_gpio_ctr(outctrl->channel, outctrl->state);
            break;
        case CMD_HIGH_CURRENT_CONTROL: // ��������ʹ�ܿ�������
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_HIGH_CURRENT_CONTROL. \r\n");
            largectrl = (GPIOCtrl *)cmd_data;
            large_electric_gpio_ctr(largectrl->channel, largectrl->state);
            break;
        case CMD_LOW_CURRENT_SETTING: // С�������ʹ������ң��ָ��
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_LOW_CURRENT_SETTING. \r\n");
            lowctrl = (GPIOCtrl *)cmd_data;
            small_electric_gpio_ctr(lowctrl->channel, lowctrl->state);
            break;
        case CMD_INTERSTELLAR_CONFIG: // �Ǽ�ģ������ָ��
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_INTERSTELLAR_CONFIG. \r\n");
            InterstellarConfig *config = (InterstellarConfig *)cmd_data;
            interstellar_config_send(config);
            break;
        case CMD_INTERSTELLAR_RESET: // �Ǽ�ģ�鸴λ
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_INTERSTELLAR_RESET. \r\n");
            xingjian_reset(0); // 0/1 ��������ϵ?
            break;
        case CMD_TRANSPARENT_DATA: // ͸��ģʽ���ݷ��͵��Ǽ�ģ��
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_TRANSPARENT_DATA. \r\n");

            break;
        case CMD_DIANJI_CTL: // �������ָ��ת��
            B_CAN_ZQ_count0 = (B_CAN_ZQ_count0 == 0xff) ? 0 : B_CAN_ZQ_count0 + 1;
            cmd[0] = 0x35;
            // canfd_send_all_data0(cmd,data_length);
            // Printf("can_xieyi_test:CMD_DIANJI_CTL. \r\n");
            dj_uart_cmd_analyze(cmd_data, data_length - 2); // data_length�������ܳ��ȣ���ȥ2���ֽڵ�ͷ������ʵ�����ݳ���
            break;
        case CMD_DIANJI_REQ: // ���ң������
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
