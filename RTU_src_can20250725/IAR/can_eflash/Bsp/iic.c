#include "iic.h"
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_usart.h"
#include "as32x601_canfd.h"
#include "as32x601_plic.h"
#include "delay.h"
#include "myprintf.h"

extern void std_feed_dog();
/*
 * Function:        User_I2C_Init
 * Description:     Configure I2C
 * Param:           None.
 * Return:          None.
 */
void User_I2C_Init()
{
    IIC1_CLK_ENABLE();
    GPIOF_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF_IIC1);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF_IIC1);

    /* GPIO Configure */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_OD;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_OD;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    IIC1_RESET();
    delay_ms(100);
    IIC1_SET();
    /* Initializes the I2Cx */
    I2C_StructInit(&I2C_InitStructure);
    I2C_InitStructure.I2C_ClockScale = I2C_PCLK_960;
    I2C_InitStructure.I2C_EN = ENABLE;
    I2C_InitStructure.I2C_SlaveAddress = 0x01;
    I2C_InitStructure.I2C_Ack = I2C_IICAA_ACK;
    I2C_InitStructure.I2C_ICLKDIVH = 0x02;
    I2C_InitStructure.I2C_ICLKDIVL = 0x20;
    I2C_Init(I2C1, &I2C_InitStructure);
}
// 芯片上的i2c3   PH4,SDA, PH5,SCL
void User_APP1_I2C3_Init()
{
    IIC3_CLK_ENABLE();
    // GPIOH_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOH, GPIO_PinSource4, GPIO_AF_IIC3);
    GPIO_PinAFConfig(GPIOH, GPIO_PinSource5, GPIO_AF_IIC3);

    /* GPIO Configure */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_OD;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOH, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_OD;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOH, &GPIO_InitStructure);

    IIC3_RESET();
    delay_ms(100);
    IIC3_SET();
    /* Initializes the I2Cx */
    I2C_StructInit(&I2C_InitStructure);
    I2C_InitStructure.I2C_ClockScale = I2C_PCLK_960;
    I2C_InitStructure.I2C_EN = ENABLE;
    I2C_InitStructure.I2C_SlaveAddress = 0x01; // 从设备地址
    I2C_InitStructure.I2C_Ack = I2C_IICAA_ACK;
    I2C_InitStructure.I2C_ICLKDIVH = 0x02;
    I2C_InitStructure.I2C_ICLKDIVL = 0x20;
    I2C_Init(I2C3, &I2C_InitStructure);
}

// 芯片上的i2c2   PA13,SDA, PA14,SCL
void User_APP0_I2C2_Init()
{
    IIC2_CLK_ENABLE();
    GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource13, GPIO_AF_IIC2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource14, GPIO_AF_IIC2);

    /* GPIO Configure */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_OD;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_OD;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    IIC2_RESET();
    delay_ms(100);
    IIC2_SET();
    /* Initializes the I2Cx */
    I2C_StructInit(&I2C_InitStructure);
    I2C_InitStructure.I2C_ClockScale = I2C_PCLK_960;
    I2C_InitStructure.I2C_EN = ENABLE;
    I2C_InitStructure.I2C_SlaveAddress = 0x4b; // 从设备地址
    I2C_InitStructure.I2C_Ack = I2C_IICAA_ACK;
    I2C_InitStructure.I2C_ICLKDIVH = 0x02;
    I2C_InitStructure.I2C_ICLKDIVL = 0x20;
    I2C_Init(I2C2, &I2C_InitStructure);
}

// //高使能,iic的两个buffer, PB3,PB4
// void iic_enable_open()
// {
//     GPIO_InitTypeDef GPIO_InitStructure;

//     GPIOB_CLK_ENABLE();

//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 |GPIO_Pin_4;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//     GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
//     GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
//     GPIO_Init(GPIOB, &GPIO_InitStructure);

//     GPIO_WriteBits(GPIOB, GPIO_Pin_3, GPIO_OCtrl_Voh);
//     GPIO_WriteBits(GPIOB, GPIO_Pin_4, GPIO_OCtrl_Voh);
// }

/**
 * @brief 给one wire用的I2C写函数
 * 
 * @return uint8_t 
 */
uint8_t mss_I2c1_wr(uint8_t I2C2_address, uint8_t *data, uint16_t dataLen, uint8_t holdBus)
{
    return I2C_Master_Transmit(I2C3, I2C2_address, data, dataLen, I2C_TIMEOUT);
}

/**
 * @brief 给one wire用的I2C读函数
 * 
 * @return uint8_t 
 */
uint8_t mss_I2c1_rd(uint8_t I2C2_address, uint8_t *data, uint16_t dataLen, uint8_t holdBus)
{
    return I2C_Master_Receive(I2C3, I2C2_address, data, dataLen, I2C_TIMEOUT);  
}


// I2C写函数实现
uint8_t i2c_write(uint8_t i2cChan, uint8_t addr, uint8_t *data, uint8_t len)
{
    if (i2cChan == 0)
        return (I2C_Master_Transmit(I2C0, addr, data, len, I2C_TIMEOUT) == SET);
    if (i2cChan == 1)
        return (I2C_Master_Transmit(I2C1, addr, data, len, I2C_TIMEOUT) == SET);
    if (i2cChan == 2)
        return (I2C_Master_Transmit(I2C2, addr, data, len, I2C_TIMEOUT) == SET);
    if (i2cChan == 3)
        return (I2C_Master_Transmit(I2C3, addr, data, len, I2C_TIMEOUT) == SET);
    return 1;
}

// I2C读函数实现
uint8_t i2c_read(uint8_t i2cChan, uint8_t addr, uint8_t *data, uint8_t len)
{
    // return (I2C_Master_Receive(i2cChan, addr, data, len, I2C_TIMEOUT) == SET);
    if (i2cChan == 0)
        return (I2C_Master_Receive(I2C0, addr, data, len, I2C_TIMEOUT) == SET);
    if (i2cChan == 1)
        return (I2C_Master_Receive(I2C1, addr, data, len, I2C_TIMEOUT) == SET);
    if (i2cChan == 2)
        return (I2C_Master_Receive(I2C2, addr, data, len, I2C_TIMEOUT) == SET);
    if (i2cChan == 3)
        return (I2C_Master_Receive(I2C3, addr, data, len, I2C_TIMEOUT) == SET);
    return 1;
}

// 以下代码挂到i2c3上了，DS2482S都在iic3上
//  初始化 DS2482
uint8_t ds2482_init(void)
{
    uint8_t config = 0x18; // SPU=0, APU=1, 1WS=0, SBR=1
    return i2c_write(3, DS2482_I2C0_ADDR, &config, 1);
}

// 发送 1-Wire 复位脉冲
uint8_t ow_reset(void)
{
    uint8_t cmd = OW_RESET;
    uint8_t status;

    if (!i2c_write(3, DS2482_I2C0_ADDR, &cmd, 1))
        return 1;

    // 等待命令完成并读取状态
    do
    {
        if (!i2c_read(3, DS2482_I2C0_ADDR, &status, 1))
            return 1;
    } while (!(status & 0x01)); // 等待 SB 位（命令完成）

    return (status & 0x04); // 返回 PRESENCE 位
}

// 向 1-Wire 总线写一个字节
uint8_t ow_write_byte(uint8_t data)
{
    uint8_t cmd[2] = {OW_WRITE_BYTE, data};
    uint8_t status;

    if (!i2c_write(3, DS2482_I2C0_ADDR, cmd, 2)) // 先默认写第一个2482
        return 1;

    // 等待命令完成
    do
    {
        if (!i2c_read(3, DS2482_I2C0_ADDR, &status, 1))
            return 1;
    } while (!(status & 0x01));

    return 0;
}

// 从 1-Wire 总线读一个字节
uint8_t ow_read_byte(uint8_t *data)
{
    uint8_t cmd = OW_READ_BYTE;
    uint8_t status;

    if (!i2c_write(3, DS2482_I2C0_ADDR, &cmd, 1))
        return 1;

    // 等待命令完成
    do
    {
        if (!i2c_read(3, DS2482_I2C0_ADDR, &status, 1))
            return 1;
    } while (!(status & 0x01));

    // 读取数据
    if (!i2c_read(3, DS2482_I2C0_ADDR, data, 1))
        return 1;
    return 0;
}

// 读取 DS18B20 温度
uint8_t read_ds18b20_temperature(float *temp)
{
    uint8_t scratchpad[9];

    // 复位并检查 presence
    if (!ow_reset())
        return 1;

    // 跳过 ROM（单设备）
    ow_write_byte(0xCC);

    // 发送温度转换命令
    ow_write_byte(CONVERT_T);

    // 等待转换完成（需根据分辨率调整延时）
    delay_ms(750); // 最大转换时间

    // 复位并开始读取
    ow_reset();
    ow_write_byte(0xCC);            // 跳过 ROM
    ow_write_byte(READ_SCRATCHPAD); // 读暂存器

    // 读取 9 字节数据
    for (int i = 0; i < 9; i++)
    {
        if (!ow_read_byte(&scratchpad[i]))
            return 1;
    }

    // 计算温度值
    int16_t raw_temp = (scratchpad[1] << 8) | scratchpad[0];
    *temp = raw_temp / 16.0f;

    return 0;
}

//===============================配电采集=============
/**
 * @brief 读取指定通道的ADC值
 * @param I2Cx I2C外设（如I2C1）
 * @param channel 通道号（0~7）
 * @param adc_value 存储ADC值的指针
 * @return 0:成功 1:失败
 */
uint8_t ads7828_read_channel(I2C_TypeDef *hi2c, uint8_t channel, uint16_t *adc_value, uint8_t ADS7828_ADDR)
{
    uint8_t control_word;
    uint8_t rx_data[2]; // 存储接收的2字节数据
    FlagStatus tx_status, rx_status;

    // 检查通道合法性
    if (channel > 7 || adc_value == NULL || channel < 0)
    {
        Printf("ads7828_read_channel arg error channel=%d\r\n", channel);
        return -1;
    }
    Printf("channel=%d,ADS7828_ADDR=0x%x\r\n", channel,ADS7828_ADDR);
    // 构建控制字：单端输入(SD=1)，内部参考+ADC使能(PD1=1, PD0=1)，通道选择(C2~C0=channel)
    control_word = 0x8c | (channel << 4); // 0x80 = 1000 0000（标准配置）
    // Printf("I2C transmit failed (channel %d)\r\n", channel);
    //  步骤1：发送控制字（启动AD转换）
    tx_status = I2C_Master_Transmit(hi2c, ADS7828_ADDR, &control_word, 1, I2C_TIMEOUT);
    if (tx_status != SET)
    {
        Printf("I2C transmit failed (channel %d)\r\n", channel);
        return -1;
    }
    delay_ms(20); // 不加延迟就读取报错了
    std_feed_dog();
    // 步骤2：读取转换结果（2字节）
    rx_status = I2C_Master_Receive(hi2c, ADS7828_ADDR, rx_data, 2, I2C_TIMEOUT);
    if (rx_status != SET)
    {
        Printf("I2C receive failed (channel %d)\r\n", channel);
        return -1;
    }

    // Printf("rx_data[0] = 0x %x, rx_data[1] = 0x %x\r\n", rx_data[0], rx_data[1]);
    //  组合12位ADC值：高字节低4位 + 低字节8位
    *adc_value = ((rx_data[0] & 0x0F) << 8) | rx_data[1];
    return 0;
}


/**
 * @brief 采集所有i2c上挂载的ADS7828芯片的通道数据
 * 
 */
void iic_adc_get_all_chan()
{
    Printf("main_iic_test start\r\n");

#if 1 // 配电采集所有路电压电流
    uint8_t addr = 0x48;
    uint16_t adc_value = 0;
    float voltage = 0;
    float tmp2 = 0;
    float tmp = 0;
    {
        Printf("addr=0x%x\r\n", addr);
        // 循环读取0~7通道
        for (uint8_t channel = 0; channel < 8; channel++)
        {
            int32_t ret = ads7828_read_channel(I2C2, channel, &adc_value, addr);
            if (ret < 0)
            {
                Printf("Error reading ADC channel %d\n", channel);
                return;
            }

            // 转换为电压值（12位ADC：0~4095对应0~VREF）
            if (channel < 4)
            {
                // 浮点运算偶尔cpu卡住
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

            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // 调试打印的值不对，内存中是正确的，打印出来就变了
            delay_ms(20);
        }
        delay_ms(20);

        addr = 0x49;
        Printf("addr=0x%x\r\n", addr);
        // 循环读取0~7通道
        for (uint8_t channel = 0; channel < 8; channel++)
        {
            int32_t ret = ads7828_read_channel(I2C2, channel, &adc_value, addr);
            if (ret < 0)
            {
                Printf("Error reading ADC channel %d\n", channel);
                return;
            }

            // 转换为电压值（12位ADC：0~4095对应0~VREF）
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
            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // 调试打印的值不对，内存中是正确的，打印出来就变了
            delay_ms(20);
        }
        delay_ms(20);

        addr = 0x4a;
        Printf("addr=0x%x\r\n", addr);
        // 循环读取0~7通道
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
            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // 调试打印的值不对，内存中是正确的，打印出来就变了
            delay_ms(20);
        }
        delay_ms(20);

        addr = 0x4b;
        Printf("addr=0x%x\r\n", addr);
        // 循环读取0~7通道
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
            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // 调试打印的值不对，内存中是正确的，打印出来就变了
            delay_ms(20);
        }
        delay_ms(20);

        // I2C3的采集
        addr = 0x4b;
        Printf("I2C1: addr=0x%x\r\n", addr);
        // 循环读取0~7通道
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
            Printf("Channel %d: ADC=%d, Voltage=%fV\r\n", channel, adc_value, voltage); // 调试打印的值不对，内存中是正确的，打印出来就变了
            delay_ms(20);
        }
        delay_ms(20);
    }
#endif
}