/*
 * @Description:
 * @Version: 2.0
 * @Autor: ruog__
 * @Date: 2025-07-23 16:26:18
 * @LastEditors: ruog__
 * @LastEditTime: 2025-05-04 12:40:40
 */
#include "main.h"
#include "print.h"
#include "canfd.h"
#include "myprintf.h"
#include "canfd_xieyi.h"
#include "iic.h"
#include "adc.h"
#include "print.h"
#include "gpio.h"
#include "uart_dianji.h"
#include "uart_xingjian.h"
#include "onewire.h"
/* Private typedef -----------------------------------------------------------*/

void Systemclock_Init();
// �����ⲿframe�ṹ�壬����ֱ�Ӹ��µ������
extern canfdDJ_all frame;
extern canfdDJ_all_t frame_t;                // ���ң�����ݣ�ֱ��ת�����ݲ����е�����ֵ
extern canfdYC_all canfd_yc_all;         // ң������
// ���Ե�����ݰ����չ���
void test_motor_packet_receive(void);

// ����0���ݵĽ��գ� ��ǰ���Ե��ң��ֵ�ķ���
uint8_t data[64] = {0};
uint32_t ptr = 0;
// ����1
uint8_t data1[64] = {0};
uint32_t ptr1 = 0;
// ����2
uint8_t data2[64] = {0};
uint32_t ptr2 = 0;
// ����3
uint8_t data3[64] = {0};
uint32_t ptr3 = 0;
// ����4
uint8_t data4[64] = {0};
uint32_t ptr4 = 0;
// ����5
uint8_t data5[64] = {0};
uint32_t ptr5 = 0;

uint8_t receive_flag = 0;

uint8_t canfd_sel;
uint8_t canfd_M_sel;

uint8_t run = 0;
uint8_t Canfd0rx_flags = 0;
uint32_t Canfd0rx_bytes = 0;
uint8_t Canfd1rx_flags = 0;
uint8_t Canfd2rx_flags = 0;
uint8_t Canfd3rx_flags = 0;
uint32_t Canfd1rx_bytes = 0;
uint32_t Canfd2rx_bytes = 0;

uint32_t err_status0;
uint32_t err_status1;
/* Exported define -----------------------------------------------------------*/
/*uint8_t Send_data1[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
                        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
                        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
                        0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
                        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
                        0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
                        0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88};
*/

uint8_t Send_data1[] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};

uint8_t Receive_data1[64] = {0};
uint8_t Receive_data0[64] = {0};

void main_iic_test()
{
    // User_appTS_uart6_Init(115200);//���Դ�������

    /* Set GPIO multiplex mapping */

    // User_APP0_I2C2_Init();
    // User_APP1_I2C3_Init();

    Printf("The IIC has init success!\r\n");

#if 1 // ���ɼ�����
    uint8_t addr = 0x48;
    uint16_t adc_value = 0;
    float voltage = 0;
    float tmp2 = 0;
    float tmp = 0;
    // while(1)
    {
        Printf("addr=0x%x\r\n", addr);
        // ѭ����ȡ0~7ͨ��
        for (uint8_t channel = 0; channel < 8; channel++)
        {
            int32_t ret = ads7828_read_channel(I2C2, channel, &adc_value, addr);
            if (ret < 0)
            {
                Printf("Error reading ADC channel %d\n", channel);
                return;
            }

            // ת��Ϊ��ѹֵ��12λADC��0~4095��Ӧ0~VREF��
            if (channel < 4)
            {
                // ��������ż��cpu��ס
                tmp = adc_value / 4095.0f;
                voltage = tmp * 2.5f;
                voltage = voltage / 20.0f;
                voltage = voltage / 0.0279f;
            }
            else
            {
                tmp = adc_value / 4095.0f;
                tmp2 = tmp * 2.5f;
                voltage = tmp2 / 5.6f * 80.6f;
            }

            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // ���Դ�ӡ��ֵ���ԣ��ڴ�������ȷ�ģ���ӡ�����ͱ���
            delay_ms(20);
        }
        delay_ms(20);

        addr = 0x49;
        Printf("addr=0x%x\r\n", addr);
        // ѭ����ȡ0~7ͨ��
        for (uint8_t channel = 0; channel < 8; channel++)
        {
            int32_t ret = ads7828_read_channel(I2C2, channel, &adc_value, addr);
            if (ret < 0)
            {
                Printf("Error reading ADC channel %d\n", channel);
                return;
            }

            // ת��Ϊ��ѹֵ��12λADC��0~4095��Ӧ0~VREF��
            if (channel < 4)
            {
                tmp = adc_value / 4095.0f;
                voltage = tmp * 2.5f;
                voltage = voltage / 20.0f;
                voltage = voltage / 0.0279f;
            }
            else
            {
                tmp = adc_value / 4095.0f;
                tmp2 = tmp * 2.5f;
                voltage = tmp2 / 5.6f * 80.6f;
            }
            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // ���Դ�ӡ��ֵ���ԣ��ڴ�������ȷ�ģ���ӡ�����ͱ���
            delay_ms(20);
        }
        delay_ms(20);

        addr = 0x4a;
        Printf("addr=0x%x\r\n", addr);
        // ѭ����ȡ0~7ͨ��
        for (uint8_t channel = 0; channel < 8; channel++)
        {
            int32_t ret = ads7828_read_channel(I2C2, channel, &adc_value, addr);
            if (ret < 0)
            {
                Printf("Error reading ADC channel %d\n", channel);
                return;
            }

            if (channel < 4)
            {
                tmp = adc_value / 4095.0f;
                voltage = tmp * 2.5f;
                voltage = voltage / 20.0f;
                voltage = voltage / 0.0279f;
            }
            else
            {
                tmp = adc_value / 4095.0f;
                tmp2 = tmp * 2.5f;
                voltage = tmp2 / 5.6f * 80.6f;
            }
            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // ���Դ�ӡ��ֵ���ԣ��ڴ�������ȷ�ģ���ӡ�����ͱ���
            delay_ms(20);
        }
        delay_ms(20);

        addr = 0x4b;
        Printf("addr=0x%x\r\n", addr);
        // ѭ����ȡ0~7ͨ��
        for (uint8_t channel = 0; channel < 8; channel++)
        {
            int32_t ret = ads7828_read_channel(I2C2, channel, &adc_value, addr);
            if (ret < 0)
            {
                Printf("Error reading ADC channel %d\n", channel);
                return;
            }

            if (channel < 4)
            {
                tmp = adc_value / 4095.0f;
                voltage = tmp * 2.5f;
                voltage = voltage / 20.0f;
                voltage = voltage / 0.0279f;
            }
            else
            {
                tmp = adc_value / 4095.0f;
                tmp2 = tmp * 2.5f;
                voltage = tmp2 / 5.6f * 80.6f;
            }
            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // ���Դ�ӡ��ֵ���ԣ��ڴ�������ȷ�ģ���ӡ�����ͱ���
            delay_ms(20);
        }
        delay_ms(20);

        // I2C3�Ĳɼ�
        addr = 0x4b;
        Printf("I2C1: addr=0x%x\r\n", addr);
        // ѭ����ȡ0~7ͨ��
        for (uint8_t channel = 0; channel < 8; channel++)
        {
            int32_t ret = ads7828_read_channel(I2C3, channel, &adc_value, addr);
            if (ret < 0)
            {
                Printf("Error reading ADC channel %d\n", channel);
                return;
            }

            if (channel < 4)
            {
                tmp = adc_value / 4095.0f;
                voltage = tmp * 2.5f;
                voltage = voltage / 20.0f;
                voltage = voltage / 0.0279f;
            }
            else
            {
                tmp = adc_value / 4095.0f;
                tmp2 = tmp * 2.5f;
                voltage = tmp2 / 5.6f * 80.6f;
            }
            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // ���Դ�ӡ��ֵ���ԣ��ڴ�������ȷ�ģ���ӡ�����ͱ���
            delay_ms(20);
        }
        delay_ms(20);
    }
#endif
#if 1 // 18b20����

    OWGetRom();
    while (1)
    {
        
        Read_Temperature();
        delay_ms(200);
        Printf("start check\r\n");
    }
#endif
}

void uart_send_loop_test()
{
    uint8_t data = 0x5a;

    USART_SendData(USART0, data);
    USART_SendData(USART1, data);
    USART_SendData(USART3, data);
    USART_SendData(USART5, data);
    USART_SendData(USART6, data);
}
/**
 * @brief  Recover CANFD from Bus-Off state
 * @param  CANFDx: where x can be (0..3) to select the CANFD peripheral.
 * @retval None
 */
void CANFD_RecoverFromBusOff(CANFD_TypeDef *CANFDx)
{
    uint8_t tec = CANFDx->ECR & 0xFF;
    uint8_t rec = (CANFDx->ECR >> 8) & 0xFF;
    /* 1. Check if in Bus-Off state (ESTAT = 0x2) */
    // Printf("*** CANFD%c TEC=%d ***\r\n", (CANFDx == CANFD0) ? '0' : '1', tec);
    uint32_t estat = (CANFDx->SR >> 7) & 0x3; // ESTAT is bits [8:7] of SR
    if (estat != 0x2)
    {
        return; // Not in Bus-Off state, no action needed
    }
    // CANFD_SetBusOff(CANFDx);
    Printf("Bus-Off recovery successful\r\n");
#if 0    
   uint32_t timeout = 1000; // 1s timeout
    while(((CANFDx->SR >> 7) & 0x3) == 0x2) { // Check ESTAT
        if(--timeout == 0) {
            Printf("Bus-Off recovery timeout!\r\n");
            break;
        }
        delay_ms(1);
    }
    
    if(timeout > 0) {
        Printf("Bus-Off recovery successful\r\n");
    }
#endif
#if 1

    // Printf("CANFD%c in Bus-Off state! TEC=%d, REC=%d\n", (CANFDx == CANFD0) ? '0' : '1', CANFDx->ECR & 0xFF, (CANFDx->ECR >> 8) & 0xFF);

    /* 2. Disable controller */
    CANFDx->SRR &= ~CANFD_SRR_CEN;

    /* 3. Clear Bus-Off flag and errors */
    CANFDx->ICR = CANFD_CLEAR_BSOFF | CANFD_CLEAR_ERROE;
    CANFDx->ESR = 0; // Clear error status

    /* 4. Start Bus-Off recovery */
    CANFDx->MSR |= CANFD_MSR_SBR; // Set Start Bus-Off Recovery

    /* 5. Enable controller */
    CANFDx->SRR |= CANFD_SRR_CEN;

    /* 6. Reset error counters */
    // Note: ECR may be read-only, but attempt to reset
    // CANFDx->ECR = 0;

    /* 7. Wait for recovery */
    uint32_t timeout = 1000; // 1s timeout
    while (((CANFDx->SR >> 7) & 0x3) == 0x2)
    { // Check ESTAT
        if (--timeout == 0)
        {
            Printf("Bus-Off recovery timeout!\r\n");
            break;
        }
        delay_ms(1);
    }

    if (timeout > 0)
    {
        Printf("Bus-Off recovery successful\r\n");
    }
    delay_ms(200);
    User_CANFD0_Init();
    CANFD0_Frame_Init();

    User_CANFD1_Init();
    CANFD1_Frame_Init();
#endif
}

void CANFD_RecoverFromBusOff_v2(CANFD_TypeDef *CANFDx)
{
    uint8_t tec = CANFDx->ECR & 0xFF;
    uint8_t rec = (CANFDx->ECR >> 8) & 0xFF;

    /* 1. Check if in Bus-Off state (ESTAT = 0x2) */
    uint32_t estat = (CANFDx->SR >> 7) & 0x3; // ESTAT is bits [8:7] of SR
    if (estat != 0x2)
    {
        return; // Not in Bus-Off state, no action needed
    }

    Printf("CANFD%c in Bus-Off state! TEC=%d, REC=%d\n, ESR = 0x%08X.\r\n", (CANFDx == CANFD0) ? '0' : '1', tec, rec, CANFDx->ESR);

    if (CANFDx->ESR & CANFD_ESR_CRCER_Msk)
        Printf("  CRC Error\n");
    if (CANFDx->ESR & CANFD_ESR_FMER_Msk)
        Printf("  Format Error\n");
    if (CANFDx->ESR & CANFD_ESR_STER_Msk)
        Printf("  Stuff Error\n");
    if (CANFDx->ESR & CANFD_ESR_BERR_Msk)
        Printf("  Bit Error\n");
    if (CANFDx->ESR & CANFD_ESR_ACKER_Msk)
        Printf("  ACK Error\n");
    if (CANFDx->ESR & CANFD_ESR_F_CRCER_Msk)
        Printf("  FD CRC Error\n");
    if (CANFDx->ESR & CANFD_ESR_F_FMER_Msk)
        Printf("  FD Format Error\n");
    if (CANFDx->ESR & CANFD_ESR_F_STER_Msk)
        Printf("  FD Stuff Error\n");
    if (CANFDx->ESR & CANFD_ESR_F_BERR_Msk)
        Printf("  FD Bit Error\n");

    /* 2. Disable controller */
    CANFDx->SRR &= ~CANFD_SRR_CEN;

    /* 3. Clear Bus-Off flag and errors */
    CANFDx->ICR = CANFD_CLEAR_BSOFF | CANFD_CLEAR_ERROE;
    CANFDx->ESR = 0; // Clear error status

    /* 4. Start Bus-Off recovery */
    CANFDx->MSR |= CANFD_MSR_SBR; // Set Start Bus-Off Recovery

    /* 5. Enable controller */
    CANFDx->SRR |= CANFD_SRR_CEN;

    /* 6. Reset error counters */
    // Note: ECR may be read-only, but attempt to reset
    // CANFDx->ECR = 0;

    /* 7. Wait for recovery */
    uint32_t timeout = 1000; // 1s timeout
    while (((CANFDx->SR >> 7) & 0x3) == 0x2)
    { // Check ESTAT
        if (--timeout == 0)
        {
            Printf("Bus-Off recovery timeout!\r\n");
            break;
        }
        delay_ms(1);
    }

    if (((CANFDx->SR >> 7) & 0x3) != 0x2)
    { // Check ESTAT
        Printf("Bus-Off recovery successful.New TEC = %d\r\n", CANFDx->ECR & 0xFF);
    }
    else
    {
        Printf("Bus-Off recovery failed.\r\n");
    }

    /*
    if(timeout > 0) {
        Printf("Bus-Off recovery successful\r\n");
    }
    s*/
}

/*
 * Brief:           Main program
 * Description:
 * Param:           None.
 * Return:          None.
 */

void main()
{
    Systemclock_Init();

    delay_init(SMU_ClocksStruct.AXIBus0_Frequency / 1000000);
    uint16_t clock_adc_get = 0;
    User_all_enable();

    User_APP0_I2C2_Init();
    User_APP1_I2C3_Init();


#if 0 // 4·���ڷ��ͽ��ղ���
    //uint8_t data1 = 0x4a;
    User_appTS_uart6_Init(115200);
    User_app1_uart5_Init(115200);       //���
    User_app2_uart3_Init(115200);       //�ڶ���
    User_app3_uart1_Init(9600);         //�Ǽ�ģ��  //��3��
    User_app4_uart0_Init(115200);
    Printf("test123123123\r\n");
    User_GPIO_Init(); // �����Ƶ�GPIO
    int sendLen = 0;
    sendLen = strlen("AT+UART=3,0");
    xingjian_change_config_mode(0,3);
    xingjian_change_config_mode(1,3);
    memset(data,0,64);
    memcpy(data,"AT+UART=3,0",sendLen);
    while (1)
    {
        
        for(int i=0; i<sendLen; i++)
        {
          
            //Printf("%c",data[i]);
            //USART_SendData(USART0, data[i]);//��������
            //delay_ms(10);
            USART_SendData(USART5, data[i]);//��������
            //USART_SendData(USART1, data[i]);
            //USART_SendData(USART0, data[i]);
            //delay_us(20);
            delay_ms(10);

        }
        Printf("\r\n");
        delay_ms(200);

        if (ptr4 >= 63)
        {
            receive_flag = 0;
            Printf("uart recv data! len=%d\r\n", ptr4);
            for (int i = 0; i < ptr4; i++)
                Printf(" 0x%x", data4[i]);
            Printf("-------->\r\n");
            //dj_uart_cmd_yc_return(data4, ptr4);

            ptr4 = 0;
        }
        if (ptr1 >= 63)
        {
            receive_flag = 0;
            Printf("app1_uart5 recv data! len=%d\r\n", ptr1);
            for (int i = 0; i < ptr1; i++)
                Printf(" 0x%x", data1[i]);
            Printf("-------->\r\n");
            //dj_uart_cmd_yc_return(data4, ptr4);

            ptr1 = 0;
        }
        
        if (ptr3 >= 63)//�Ǽ�ģ�����
        {
            Printf("app3_uart1 recv data! len=%d\r\n", ptr3);
            for (int i = 0; i < ptr3; i++)
                Printf(" 0x%x", data3[i]);
            Printf("-------->\r\n");
            ptr3 = 0;
        }
#if 0
        delay_ms(500);
        for(int i=0;i<11;i++)
        {
            USART_SendData(USART0, 0x4a);
            delay_ms(10);
        }
#endif
    }
#endif

#if 0 //i2c����, �����i2c��ADC�ɼ����Ժ�one-wire����
    User_appTS_uart6_Init(115200);//���Դ�������
    main_iic_test();
#endif

#if 1 // canf7����
    /*------canfd_v7_TEC_OK-------*/
    User_appTS_uart6_Init(115200); // ���Դ�������
    User_app1_uart5_Init(115200);
    User_app2_uart3_Init(115200);
    User_app3_uart1_Init(9600);
    User_app4_uart0_Init(115200);
    User_ADC_All_Init(); // adc��gpio��ʼ��
    User_canfd_enable(); //  PG4,PH8, User_all_enable���Ѿ�ʹ����
    ADC_SoftRegularConvert(ADC1);
    ADC_SoftRegularConvert(ADC2);
    Printf("CANFD V7_TEC_OK.\r\n");
    Printf("The CAN FD has init.\r\n");

    //one-wire init
    OWGetRom();
    Printf("The OWGetRom init success\r\n");
    /* Initialize print usart */
    User_GPIO_Init(); // �����Ƶ�GPIO
    // canfd_sel = 1 : canfd_brs
    // canfd_sel = 0 : canfd
    canfd_sel = 1;
    canfd_M_sel = 2;
    User_CANFD0_Init();
    CANFD0_Frame_Init();

    // CANFD_Transmit(CANFD0, TB1, Send_data1, Byte_8);
    User_CANFD1_Init();
    CANFD1_Frame_Init(); // 5M

#endif
#if 0
    uint16_t count = 0;
    uint8_t yctest[] = {0xEB, 0x90, 0x00, 0x00, 0x03, 0x05, 0xFF, 0x01, 0x08};
    while (1)
    {
        if (count++ >= 0xf0)
        {
            for (int i = 0; i < 9; i++)
            {
                USART_SendData(USART5, yctest[i]);
                delay_ms(10);
            }
            count = 0;
            Printf("send dianji all success\r\n");
        }
        
        delay_ms(10);
        if (ptr1 >= 63)
        {
            receive_flag = 0;
            Printf("uart recv data! len=%d\r\n", ptr1);
            for (int i = 0; i < ptr1; i++)
                Printf(" 0x%x", data1[i]);
            Printf("-------->\r\n");
            ptr1 = 0;
        }
    }

    if (0)
    {
        //      CANFD_Transmit(CANFD0, TB1, Send_data1, Byte_64);
        delay_ms(100);
        //       CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_64);
        delay_ms(100);
    }
#endif
    /* Write send data */

    // User_ADC_GetAllValue();
    // PrintAllADCValues();

    while (1)
    {
        // CANFD_Transmit(CANFD0, TB1, Send_data1, Byte_64);
        // CANFD_Transmit(CANFD0, TB1, Send_data1, Byte_8);
        // delay_ms(100);
        // CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_64);
        // CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_8);
        // delay_ms(100);
        /* wj-20250728-v1 */
        /* Write send data */
        // CANFD_Transmit(CANFD1, TB1, Send_data1, Byte_8);

        if (Canfd1rx_flags == 1)
        {
            Printf("Canfd1rx_flags vaule is %d \r\n ", Canfd1rx_flags); // wj
            Canfd1rx_flags = 0;
            memset(Receive_data1, 0, 64);
            Canfd1rx_bytes = CANFD_GetReceiveData(CANFD1, Receive_data1);
            // CANFD_Transmit(CANFD1, TB1, Receive_data1, Byte_8);
            // Printf("Canfd1rx_bytes vaule is %d \r\n ", Canfd1rx_bytes);  //wj
            // Printf("canfd1 rx: ");
            if (can_xieyi_test(Receive_data1, Canfd1rx_bytes) < 0)
            {
                Printf("cmd parse error,cmd not support\r\n");
            }
        }

        if (Canfd0rx_flags == 1)
        {
            Printf("Canfd0rx_flags vaule is %d \r\n ", Canfd0rx_flags); // wj
            Canfd0rx_flags = 0;
            memset(Receive_data0, 0, 64);
            Canfd0rx_bytes = CANFD_GetReceiveData(CANFD0, Receive_data0);
            // CANFD_Transmit(CANFD1, TB1, Receive_data1, Byte_8);
            // Printf("Canfd0rx_bytes vaule is %d \r\n ", Canfd0rx_bytes);  //wj
            // Printf("canfd0 rx: ");
            if (can_xieyi_test0(Receive_data0, Canfd0rx_bytes) < 0)
            {
                Printf("cmd parse error,cmd not support\r\n");
            }
        }
        // delay_ms(200);
        delay_ms(50);

        CANFD_RecoverFromBusOff(CANFD0);
        CANFD_RecoverFromBusOff(CANFD1);

#if 1
        //��ʱѭ��ִ��һ�εĳ���ŵ�����
        if (clock_adc_get++ > 100)
        {
#if 1
            User_ADC_GetAllValue();
            PrintAllADCValues();
#endif

#if 1
            //�¶Ȳɼ�
            Read_Temperature();
            clock_adc_get = 0;
            delay_ms(200);
            Printf("Read_Temperature complay!\r\n");
#endif

#if 1
            //�Ǽ�ģ�鵱ǰ״̬��ȡ
            xingjian_get_config(1,&canfd_yc_all.xjData); // ��ȡ�Ǽ�ģ������ò���
#endif
        }
#endif
#if 1
        // ����4���յ��ң��ظ����ݵĴ���
        if (ptr4 >= 63)
        {
            receive_flag = 0;
            Printf("uart recv data! len=%d\r\n", ptr4);
            for (int i = 0; i < ptr4; i++)
                Printf(" 0x%x", data4[i]);
            Printf("-------->\r\n");
            dj_uart_cmd_yc_return(data4, ptr4);

            ptr4 = 0;
        }
        if (ptr1 >= 63)//���ң������
        {
            receive_flag = 0;
            Printf("uart recv data! len=%d\r\n", ptr1);
            memcpy(frame_t.DJ_data, &data1[2], 60);
            for (int i = 0; i < ptr1; i++)
                Printf(" 0x%x", data1[i]);
            Printf("-------->\r\n");
            ptr1 = 0;
        }
        // //�Ǽ�ģ��
        // if (ptr3 >= 1)
        // {
        //     receive_flag = 0;
        //     Printf("ptr3 recv data! len=%d\r\n", ptr3);
        //     for (int i = 0; i < ptr3; i++)
        //         Printf(" 0x%x", data3[i]);
        //     Printf("-------->\r\n");
        //     dj_uart_cmd_yc_return(data3, ptr3);

        //     ptr3 = 0;
        // }
#endif
    }
}

/*
 * Function:        Systemclock_Init
 * Description:     Configure Systemclock_Init.
 * Param:           None
 * Return:          None.
 */
void Systemclock_Init()
{
    // ע�⣺�˴���Ҫ����ϵͳ���߼���ʱ�����ã���������ʱ�����ÿ��ڸ�ģ���ʼ�������о��忪��,������ο�ʱ����������ͼע��
    //       1. ʹ�ô���ʱ�����ڴ��ڹ���APB0�����£���Ҫ�ڴ˴�����AXIBUS3ʱ�ӡ�AXI4TOAPB0ʱ���Լ�APBBUS0ʱ�ӡ�
    //       2. ʹ����ʱ����ʱ����Ҫ����CLINTʱ��
    //       3. ʹ��eflash��qspiʱ����Ҫ����AXIBUS3ʱ�ӡ�AXILITEBUS2ʱ��

    // ע�⣺osc����PLLDIVN��Ƶ֮��Ƶ��Ӧ��0.95-2.1MHz֮��
    //       core_clock          (����ʹ��)          = pll_Q = osc % PLLDIVN x PLLDIVF % PLLDIVQ         (ע���˲���ʱ�Ӽ��㷶ΧӦ��16-180MHz֮��)
    //       AXI4Bus0            (����ʹ��)          = pll_Q = osc % PLLDIVN x PLLDIVF % PLLDIVQ         (ע���˲���ʱ�Ӽ��㷶ΧӦ��16-180MHz֮��)
    //       AXI4Bus1            (����ʹ��)          = pll_Q % 2                                         (ע���˲���ʱ�Ӽ��㷶ΧӦ��8-90MHz֮��)
    //       AXI4Bus2            (����ʹ��)          = pll_Q                                             (ע���˲���ʱ�Ӽ��㷶ΧӦ��16-180MHz֮��)
    //       |__AXILite4Bus0     (����ʹ��)          = AXI4Bus2
    //       AXI4Bus3            (����ʹ��)          = pll_Q % 2 % AXI4Bus3CLKDiv                        (ע���˲���ʱ�Ӽ��㷶ΧӦ��8-90MHz֮��)
    //       |__AXI4TOAPB0_CLK   (����ʹ��)
    //       |  |__APBBus0       (����ʹ��)          = AXI4Bus3 % APBBus0CLKDiv                          (ע���˲���ʱ�Ӽ��㷶ΧӦ��4-45MHz֮��)
    //       |__AXI4TOAPB1_CLK   (����ʹ��)
    //       |  |__APBBus1       (����ʹ��)          = AXI4Bus3 % APBBus1CLKDiv                          (ע���˲���ʱ�Ӽ��㷶ΧӦ��4-45MHz֮��)
    //       |__AXILite4Bus1     (����ʹ��)          = AXI4Bus3
    //       |__AXILite4Bus2     (����ʹ��)          = AXI4Bus3
    //       CANCLK              (�ӿ�ʹ��)          = pll_R % 2 % CANX2CLKDiv = osc % PLLDIVN x PLLDIVF % PLLDIVR  % 2 % CANX2CLKDiv        (ע���˲���ʱ�Ӽ��㷶ΧӦ��8-80MHz֮��)
    //       APBBusS             (����ʹ��)          = 32.768kHz

    /* AXIBus3 clock operation Guide*/
    AXIBUS3_CLK_ENABLE();
    AXI4TOAPB0_CLK_ENABLE();
    APBBUS0_CLK_ENABLE();
    AXI4TOAPB1_CLK_ENABLE();
    APBBUS1_CLK_ENABLE();
    AXILITEBUS1_CLK_ENABLE();
    AXILITEBUS2_CLK_ENABLE();
    EFLASH_CLK_ENABLE();
    PLIC_CLK_ENABLE();
    CLINT_CLK_ENABLE();

    SMU_PLLInitTypeDef SMU_PLLInitStruct;
    SMU_ClockInitTypeDef SMU_ClockInitStruct;

    /* Set PLL parameters values */
    SMU_PLLInitStruct.OscillatorType = SMU_OSCILLATORTYPE_OSC;
    SMU_PLLInitStruct.FIRCOscState = DISABLE;
    SMU_PLLInitStruct.FIRCCalibrationValue = 0x00;
    SMU_PLLInitStruct.PLLConfig.PLLState = ENABLE;
    SMU_PLLInitStruct.PLLConfig.PLLSource = SMU_PLLCLK_OSC;
    SMU_PLLInitStruct.PLLConfig.PLLDivR = 0x01;
    SMU_PLLInitStruct.PLLConfig.PLLDivQ = 0x01;
    SMU_PLLInitStruct.PLLConfig.PLLDivN = 0x14;
    SMU_PLLInitStruct.PLLConfig.PLLDivF = 0xA0;

    SMU_PLLInit(&SMU_PLLInitStruct);

    /* Ensure that the EFLASH is consistent with the system clock */
    FLASH_UnlockCtrl();
    FLASH_SetCLKFreq(0xA0);

    /* Set System Clock parameters values */
    SMU_ClockInitStruct.SYSCLKSelect = SMU_SYSCLK_PLL;
    SMU_ClockInitStruct.AXI4Bus3CLKDiv = AXI4Bus3CLKDiv1;
    SMU_ClockInitStruct.APBBus0CLKDiv = APBBus0CLKDiv1;
    SMU_ClockInitStruct.APBBus1CLKDiv = APBBus1CLKDiv8;
    SMU_ClockInitStruct.CANX2CLKDiv = CANX2CLKDiv1;

    SMU_ClockInit(&SMU_ClockInitStruct);

    EFLASH_CLK_UPDATE_ENABLE();
    EFLASH_CLK_UPDATE_DISABLE();

    FLASH_LockCtrl();

    /* Get System Clock values */
    SMU_GetClocksFreq(&SMU_ClocksStruct);
}
