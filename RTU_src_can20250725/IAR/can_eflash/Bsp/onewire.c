/*
 * OneWire.c
 *
 *  Created on: 2018-11-21
 *      Author: yangl
 */

#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_usart.h"
#include "as32x601_canfd.h"
#include "as32x601_plic.h"
#include "onewire.h"
#include "as32x601_i2c.h"
#include "as32x601.h"
#include "delay.h"
#include "myprintf.h"
// DS2482 state
uint8_t I2C2_address = 0;
uint8_t c1WS, cSPU, cPPM, cAPU = 0;
uint8_t temp[5] = {0};
uint8_t temp2[8] = {0};
uint8_t onewire_status = 0;

// Search state
unsigned char ROM_NO[8];
int LastDiscrepancy = 0;
int LastFamilyDiscrepancy = 0;
int LastDeviceFlag = 0;
unsigned char crc8 = 0;
union ROM_CHANGE_ZD rom_change_zd;
union ROM_CHANGE_OW rom_change_ow;
// extern szlgc yaoce;
// extern compare_value comp_value;
onewire_t stOneWire = {0};

static int8_t DS2482_set_rom(uint8_t DS2482num, uint8_t channel, uint8_t num, uint8_t *pROM);
static int8_t DS2482_get_rom(uint8_t DS2482num, uint8_t channel, uint8_t num, uint8_t *pROM);
static int8_t DS2482_set_addr(uint8_t addr);
static int8_t DS2482_detect(void);
static int8_t DS2482_reset(void);
static int8_t DS2482_write_config(uint8_t config);
static uint8_t DS2482_channel_select(uint8_t channel);
static int8_t OWReset(void);

static void OWWriteByte(uint8_t sendbyte);
static uint8_t OWReadByte(void);

static int OWFirst(void);
static int OWNext(void);
static int OWSearch(void);
static unsigned char DS2482_search_triplet(int search_direction);
static void OWGetNextChannel(uint8_t *pDS2482num, uint8_t *pchannel);

uint16_t sw16(uint16_t tmp)
{
    return (tmp >> 8) | (tmp << 8);
}

/*********************************************************************************************
函数名称:获取DS18B20ROM
函数功能:
作者	:     赵双锋
编写日期:2020.06.01
使用说明: 入口参数  :
          出口参数  :
          返回值     :
其他说明:
*********************************************************************************************/
static int8_t DS2482_set_rom(uint8_t DS2482num, uint8_t channel, uint8_t num, uint8_t *pROM)
{
    if ((DS2482num > 2U) || (channel > 8U) || (num > 10U) || (pROM == NULL)) // 判断DS2482、通道号、DS18B20编号、是否在正常范围内
    {
        Printf("Check 18b20 value BU ZHENG  QUE\r\n");
        return FALSE; // 若不对则直接返回
    }
    else
    {
        if (0U == DS2482num) // 第一片DS2482
        {
            memcpy(&stOneWire.ucROMTabl0[channel][num * 8], pROM, 8); // 拷贝DS18B20ROM
            stOneWire.DS1820Active0[channel][num] = 0x01;             // 将当前DS18B20置位
        }
        else if (1U == DS2482num)// 第二片DS2482
        {
            memcpy(&stOneWire.ucROMTabl1[channel][num * 8], pROM, 8); // 拷贝DS18B20ROM
            stOneWire.DS1820Active1[channel][num] = 0x01;             // 将当前DS18B20置位
        }
        else    // 第3片DS2482
        {
            memcpy(&stOneWire.ucROMTabl2[channel][num * 8], pROM, 8); // 拷贝DS18B20ROM
            stOneWire.DS1820Active2[channel][num] = 0x01;             // 将当前DS18B20置位
        }

        stOneWire.channelActive[DS2482num][channel] = 0x01; // 将当前通道置位
        stOneWire.DS2482Active[DS2482num] = 0x01;           // 将当前DS2482通道置位
    }
    return TRUE;
}

/*********************************************************************************************
函数名称:获取DS18B20ROM
函数功能:
作者	:     赵双锋
编写日期:2020.06.01
使用说明: 入口参数  :
          出口参数  :
          返回值     :
其他说明:
*********************************************************************************************/
static int8_t DS2482_get_rom(uint8_t DS2482num, uint8_t channel, uint8_t num, uint8_t *pROM)
{
    int8_t ret = FALSE;

    if ((DS2482num > 2U) || (channel > 8U) || (num > 10U) || (pROM == NULL)) // 判断DS2482、通道号、DS18B20编号、是否在正常范围内
    {
        //print_string((uint8_t*)"DS2482_get_rom ERR\n");
        Printf("DS2482_get_rom arg error\r\n");
    }
    else
    {
        if ((0x01 == stOneWire.DS2482Active[DS2482num]) && (0x01 == stOneWire.channelActive[DS2482num][channel])) // 判断DS2482是否置位
        {
            if (0U == DS2482num) // 第1片DS2482
            {
                if (0x01 == stOneWire.DS1820Active0[channel][num]) // 判断DS18B20是否置位
                {
                    memcpy(pROM, &stOneWire.ucROMTabl0[channel][num * 8], 8); // 拷贝DS18B20ROM
                    ret = TRUE;
                }
            }
            else if (1U == DS2482num)
            {
                if (0x01 == stOneWire.DS1820Active1[channel][num])
                {
                    memcpy(pROM, &stOneWire.ucROMTabl1[channel][num * 8], 8); // 拷贝DS18B20ROM
                    ret = TRUE;
                }
            }
            else
            {
                if (0x01 == stOneWire.DS1820Active2[channel][num])
                {
                    memcpy(pROM, &stOneWire.ucROMTabl2[channel][num * 8], 8); // 拷贝DS18B20ROM
                    ret = TRUE;
                }
            }
        }
    }

    return ret;
}

/*********************************************************************************************
函数名称:设置DS2482的IIC地址
函数功能:
作者	:     赵双锋
编写日期:2020.06.01
使用说明: 入口参数  :
          出口参数  :
          返回值     :
其他说明:
*********************************************************************************************/
static int8_t DS2482_set_addr(uint8_t addr)
{
    if ((DS2482_0 == addr) || (DS2482_1 == addr) ||  (DS2482_2 == addr))
    {
        I2C2_address = addr;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

//--------------------------------------------------------------------------
// DS2428 Detect routine that sets the I2C address and then performs a
// device reset followed by writing the configuration byte to default values:
//   1-Wire speed (c1WS) = standard (0)
//   Strong pullup (cSPU) = off (0)
//   Presence pulse masking (cPPM) = off (0)
//   Active pullup (cAPU) = on (CONFIG_APU = 0x01)
//
// Returns: TRUE if device was detected and written
//          FALSE device not detected or failure to write configuration byte
//
static int8_t DS2482_detect(void)
{

    // reset the DS2482 ON selected address
    if (!DS2482_reset())
    {
        Printf("DS2482_reset error\r\n");
        return FALSE;
    }

    // default configuration
    c1WS = 0x00;
    cSPU = 0x00;
    cPPM = 0x00;
    cAPU = CONFIG_APU;
    delay_ms(20);
    // write the default configuration setup
    if (!DS2482_write_config(c1WS | cSPU | cPPM | cAPU))
    {
        Printf("DS2482_write_config error\r\n");
        return FALSE;
    }

    return TRUE;
}

//--------------------------------------------------------------------------
// Perform a device reset on the DS2482
//
// Returns: TRUE if device was reset
//          FALSE device not detected or failure to perform reset
//
// static int8_t DS2482_reset(void)
static int8_t DS2482_reset(void)
{

    // Device Reset
    //   S AD,0 [A] DRST [A] Sr AD,1 [A] [SS] A\ P
    //  [] indicates from slave
    //  SS status byte to read to verify state

    temp[0] = CMD_DRST;
    mss_I2c1_wr(I2C2_address, &temp[0], 1, MSS_I2C_HOLD_BUS);
    delay_ms(20);
    mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_RELEASE_BUS); // 读取复位后状态
    
    // check for failure due to incorrect read back of status
    return ((onewire_status & 0xF7) == 0x10);
}

//--------------------------------------------------------------------------
// Write the configuration register in the DS2482. The configuration
// options are provided in the lower nibble of the provided config byte.
// The uppper nibble in bitwise inverted when written to the DS2482.
//
// Returns:  TRUE: config written and response correct
//           FALSE: response incorrect
//
static int8_t DS2482_write_config(uint8_t config)
{
    uint8_t uiReadCfg = 0;
    // Write configuration (Case A)
    //   S AD,0 [A] WCFG [A] CF [A] Sr AD,1 [A] [CF] A\ P
    //  [] indicates from slave
    //  CF configuration byte to write

    temp[0] = CMD_WCFG;
    temp[1] = config | (~config << 4);
    mss_I2c1_wr(I2C2_address, &temp[0], 2, MSS_I2C_HOLD_BUS);
    delay_ms(20);
    mss_I2c1_rd(I2C2_address, &uiReadCfg, 1, MSS_I2C_RELEASE_BUS); // 回读配置参数

    // check for failure due to incorrect read back
    if (config != uiReadCfg)
    {
        // handle error
        // ...
        Printf("config != uiReadCfg error\r\n");
        DS2482_reset();
        return FALSE;
    }
    Printf("DS2482_write_config success\r\n");
    return TRUE;
}

//--------------------------------------------------------------------------
// Select the 1-Wire channel on a DS2482-800.
//
// Returns: TRUE if channel selected
//          FALSE device not detected or failure to perform select
//
static uint8_t DS2482_channel_select(uint8_t channel)
{
    uint8_t ch = 0;
    uint8_t ch_read = 0;
    uint8_t check = 0;

    temp[0] = CMD_CHSL; // 通道选择命令
    switch (channel)    // 通道选择
    {
    case 0:
        ch = 0xF0;
        ch_read = 0xB8;
        break;
    case 1:
        ch = 0xE1;
        ch_read = 0xB1;
        break;
    case 2:
        ch = 0xD2;
        ch_read = 0xAA;
        break;
    case 3:
        ch = 0xC3;
        ch_read = 0xA3;
        break;
    case 4:
        ch = 0xB4;
        ch_read = 0x9C;
        break;
    case 5:
        ch = 0xA5;
        ch_read = 0x95;
        break;
    case 6:
        ch = 0x96;
        ch_read = 0x8E;
        break;
    case 7:
        ch = 0x87;
        ch_read = 0x87;
        break;
    default:
        break;
    }
    temp[1] = ch;                                              // 通道选择命令
    mss_I2c1_wr(I2C2_address, &temp[0], 2, MSS_I2C_HOLD_BUS);  // 向读通写命令
    delay_ms(20);
    mss_I2c1_rd(I2C2_address, &check, 1, MSS_I2C_RELEASE_BUS); // 回读通道选择

    return (check != ch_read); // 返回比较值
}

//--------------------------------------------------------------------------
// Reset all of the devices on the 1-Wire Net and return the result.
//
// Returns: TRUE(1):  presence pulse(s) detected, device(s) reset
//          FALSE(0): no presence pulses detected
//
static int8_t OWReset(void)
{
    int8_t poll_count = 0;

    // 1-Wire reset (Case B)
    //   S AD,0 [A] 1WRS [A] Sr AD,1 [A] [Status] A [Status] A\ P
    //                                   \--------/
    //                       Repeat until 1WB bit has changed to 0
    //  [] indicates from slave

    temp[0] = CMD_1WRS;
    mss_I2c1_wr(I2C2_address, &temp[0], 1, MSS_I2C_HOLD_BUS);
    delay_ms(20);
    mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_HOLD_BUS); // 读状态寄存器
    do
    {
        delay_ms(3);
        mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_HOLD_BUS);
    } while ((onewire_status & STATUS_1WB) && (poll_count++ < POLL_LIMIT)); // 判断1-wire是否busy

    //mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_RELEASE_BUS); // 为了发送stop位

    // check for failure due to poll limit reached
    if (poll_count >= POLL_LIMIT)
    {
        // handle error
        // ...
        delay_ms(10);
        DS2482_reset();
        delay_ms(10);
        Printf("OWReset error1\r\n");
        return FALSE;
    }
    delay_ms(10);
    // check for presence detect
    if (onewire_status & STATUS_PPD)
    {
        Printf("OWReset success\r\n");
        return TRUE;
    }
    else
    {
        Printf("OWReset error onewire_status not STATUS_PPD\r\n");
        return FALSE;
    }
}

/*********************************************************************************************
函数名称:1-wire写字节
函数功能:
作者	:     赵双锋
编写日期:2020.06.01
使用说明: 入口参数  :命令
          出口参数  :
          返回值     :无
其他说明:
*********************************************************************************************/
static void OWWriteByte(uint8_t sendbyte)
{
    int8_t poll_count = 0;
    temp[0] = CMD_1WWB;
    temp[1] = sendbyte;
    mss_I2c1_wr(I2C2_address, &temp[0], 2, MSS_I2C_HOLD_BUS); // 发送命令
    delay_ms(20);
    // I2C_Master_Transmit(I2C2, I2C2_address, &temp[0], 2, 1000);
    mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_HOLD_BUS); // 读取状态寄存器
    // I2C_Master_Receive(I2C2, I2C2_address, &temp[0], 2, 1000);
    do
    {
        mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_HOLD_BUS); // 读取状态寄存器
    } while ((onewire_status & STATUS_1WB) && (poll_count++ < POLL_LIMIT));
    delay_ms(10);
    //mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_RELEASE_BUS); // 读取状态寄存器，为了发送stop位

    // check for failure due to poll limit reached
    if (poll_count >= POLL_LIMIT)
    {
        DS2482_reset(); // DS2482重启
        Printf("OWWriteByte error\r\n");
    }
    else
      Printf("OWWriteByte success\r\n");
    return;
}

//--------------------------------------------------------------------------
// Send 8 bits of read communication to the 1-Wire Net and return the
// result 8 bits read from the 1-Wire Net.
//
// Returns:  8 bits read from 1-Wire Net
//
static uint8_t OWReadByte(void)
{
    int8_t poll_count = 0;
    uint8_t data = 0Xff;

    temp[0] = CMD_1WRB;
    mss_I2c1_wr(I2C2_address, &temp[0], 1, MSS_I2C_HOLD_BUS);
    delay_ms(20);
    mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_HOLD_BUS); // 读取状态寄存器

    do
    {
        mss_I2c1_rd(I2C2_address, &onewire_status, 1, MSS_I2C_HOLD_BUS); // 读取状态寄存器
    } while ((onewire_status & STATUS_1WB) && (poll_count++ < POLL_LIMIT));

    // check for failure due to poll limit reached
    if (poll_count >= POLL_LIMIT)
    {
        // handle error
        // ...
        DS2482_reset();
        return 0;
    }

    temp[0] = CMD_SRP;
    temp[1] = 0xE1; // 设置参数为读取数据
    mss_I2c1_wr(I2C2_address, &temp[0], 2, MSS_I2C_HOLD_BUS);
    delay_ms(20);
    mss_I2c1_rd(I2C2_address, &data, 1, MSS_I2C_RELEASE_BUS);

    return data;
}

/*********************************************************************************************
函数名称:读取DS18B20温度
函数功能:
作者	:     赵双锋
编写日期:2020.06.01
使用说明: 入口参数  :
          出口参数  :
          返回值     :
其他说明:
*********************************************************************************************/
void Read_Temperature(void)
{
    uint8_t i = 0U;
    uint8_t Cir = 0U;
    uint16_t Temp = 0U;
    uint8_t num = 0U;              // DS18B20序号
    static uint8_t DS2482num = 0U; // DS2482序号
    static uint8_t channel = 0U;   // 通道序号
    static enum OneWireOpt emOneWireOpt = ONEWIRE_FREE;
    // static uint64_t cpu_time = 0U;
    // uint64_t cpu_time1 = 0U;
    // uint64_t cpu_time2 = 0U;
    uint32_t test = 0;

    // cpu_time1 = Get_cpu_Time(); // 获取系统时间

    switch (emOneWireOpt)
    {
    case ONEWIRE_FREE: // 1-wire初始化
    {
        if ((0x01 == stOneWire.DS2482Active[0]) || (0x01 == stOneWire.DS2482Active[1]) || (0x01 == stOneWire.DS2482Active[2]))
        {
            DS2482num = 0xff;
            channel = 0xff;
            emOneWireOpt = ONEWIRE_CHSL;
        }
        break;
    }
    case ONEWIRE_READTEMP: // 读取温度
    {
        for (num = 0U; num < 8U; num++)
        {
            // CheackGcsqComm(); // 检测工参采集指令
            // 从ROM值列表中取出ds18s20序列号至ROM_NO[]中.
            if (TRUE == DS2482_get_rom(DS2482num, channel, num, &ROM_NO[0]))
            {
                temp2[0] = 0x0F;
                temp2[1] = 0xFF;        // 命令
                OWReset();              // 总线reset
                OWWriteByte(Match_Rom); // 匹配ROM
                for (i = 0; i < 8; i++)
                {
                    OWWriteByte(ROM_NO[i]); // 匹配ROM
                    rom_change_ow.rom_s_ow[i] = ROM_NO[i];
                    delay_ms(2);
                }
                OWWriteByte(Read_Temp); // 读取温度
                delay_ms(2);
                temp2[0] = OWReadByte(); // 写命令
                delay_ms(20);
                temp2[1] = OWReadByte();
                Temp = (temp2[1] << 8) + temp2[0]; // 读取温度
                Printf("DS2482num=%d, channel=%d, Temp=0x%x\r\n",DS2482num,channel, Temp);
                // OwMatchGccs(Temp, rom_change_ow.rom_b_ow, rom_change_zd.rom_b_zd); //lsh 匹配温度值与对应工参位置
                OWReset(); // 1-wire总线重置
            }
        }
        emOneWireOpt = ONEWIRE_CHSL;

        break;
    }
    case ONEWIRE_WAIT: // 等待转换完毕
    {
        // if (Get_cpu_Time() - cpu_time >= 120)
        // {
        // 	emOneWireOpt = ONEWIRE_READTEMP;
        // }
        delay_ms(1000);
        emOneWireOpt = ONEWIRE_READTEMP;
        break;
    }
    case ONEWIRE_CHSL: // 通道选择
    {
        OWGetNextChannel(&DS2482num, &channel); // 获取下一个通道号

        if ((0x01 == stOneWire.DS2482Active[DS2482num]) && (0x01 == stOneWire.channelActive[DS2482num][channel]))
        { // DS2482设备号及通道号都是active，进行通讯选通，否则继续向后轮询DS2482及通道
            if (0U == DS2482num)
            {
                DS2482_set_addr(DS2482_0);
            }
            if (1U == DS2482num)
            {
                DS2482_set_addr(DS2482_1);
            }
            if (2U == DS2482num)
            {
                DS2482_set_addr(DS2482_2);
            }

            for (Cir = 0; Cir < 5; Cir++)
            {
                if (!DS2482_channel_select(channel)) // 进行DS2482-800的通道选择，直到成功。
                {
                    Printf("DS2482_channel_select channel=%d success\r\n",channel);
                    break;
                }
            }
            Printf("OWReset =====>0\r\n");
            OWReset();
            Printf("OWReset =====>1\r\n");
            OWWriteByte(Skip_Rom);    // 跳过ROM匹配
            OWWriteByte(Temp_Change); // 启动所有温度转换
            // cpu_time = Get_cpu_Time(); // 记录当前时间
            emOneWireOpt = ONEWIRE_WAIT;
        }
        break;
    }
    default:
        emOneWireOpt = ONEWIRE_FREE; // 释放总线
        break;
    }
    // cpu_time2 = Get_cpu_Time();
    // test = cpu_time2 - cpu_time1;
    return;
}
//--------------------------------------------------------------------------
// Find the 'first' devices on the 1-Wire network
// Return TRUE  : device found, ROM number in ROM_NO buffer
//        FALSE : no device present
//
static int OWFirst(void)
{
    // reset the search state
    LastDiscrepancy = 0;
    LastDeviceFlag = FALSE;
    LastFamilyDiscrepancy = 0;

    return OWSearch();
}

//--------------------------------------------------------------------------
// Find the 'next' devices on the 1-Wire network
// Return TRUE  : device found, ROM number in ROM_NO buffer
//        FALSE : device not found, end of search
//
static int OWNext(void)
{
    // leave the search state alone
    return OWSearch();
}

//--------------------------------------------------------------------------
// The 'OWSearch' function does a general search. This function
// continues from the previous search state. The search state
// can be reset by using the 'OWFirst' function.
// This function contains one parameter 'alarm_only'.
// When 'alarm_only' is TRUE (1) the find alarm command
// 0xEC is sent instead of the normal search command 0xF0.
// Using the find alarm command 0xEC will limit the search to only
// 1-Wire devices that are in an 'alarm' state.
//
// Returns:   TRUE (1) : when a 1-Wire device was found and its
//                       Serial Number placed in the global ROM
//            FALSE (0): when no new device was found.  Either the
//                       last search was the last device or there
//                       are no devices on the 1-Wire Net.
//
static int OWSearch(void)
{
    int id_bit_number;
    int last_zero, rom_byte_number, search_result;
    int id_bit, cmp_id_bit;
    unsigned char rom_byte_mask, search_direction, status;

    // initialize for search
    id_bit_number = 1;
    last_zero = 0;
    rom_byte_number = 0;
    rom_byte_mask = 1;
    search_result = FALSE;
    crc8 = 0;

    // if the last call was not the last one
    if (!LastDeviceFlag)
    {
        // 1-Wire reset
        if (!OWReset())
        {
            // reset the search
            LastDiscrepancy = 0;
            LastDeviceFlag = FALSE;
            LastFamilyDiscrepancy = 0;
            Printf("OWReset error2 \r\n");
            return FALSE;
        }

        // issue the search command
        OWWriteByte(Search_Rom);

        // loop to do the search
        do
        {
            // if this discrepancy if before the Last Discrepancy
            // on a previous next then pick the same as last time
            if (id_bit_number < LastDiscrepancy)
            {
                if ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0)
                {
                    search_direction = 1;
                }
                else
                {
                    search_direction = 0;
                }
            }
            else
            {
                // if equal to last pick 1, if not then pick 0
                if (id_bit_number == LastDiscrepancy)
                {
                    search_direction = 1;
                }
                else
                {
                    search_direction = 0;
                }
            }

            // Perform a triple operation on the DS2482 which will perform
            // 2 read bits and 1 write bit
            status = DS2482_search_triplet(search_direction);

            // check bit results in status byte
            id_bit = ((status & STATUS_SBR) == STATUS_SBR);
            cmp_id_bit = ((status & STATUS_TSB) == STATUS_TSB);
            search_direction = ((status & STATUS_DIR) == STATUS_DIR) ? (uint8_t)(1) : (uint8_t)(0);

            // check for no devices on 1-Wire
            if ((id_bit) && (cmp_id_bit))
            {
                break;
            }
            else
            {
                if ((!id_bit) && (!cmp_id_bit) && (search_direction == 0))
                {
                    last_zero = id_bit_number;

                    // check for Last discrepancy in family
                    if (last_zero < 9)
                    {
                        LastFamilyDiscrepancy = last_zero;
                    }
                }

                // set or clear the bit in the ROM byte rom_byte_number
                // with mask rom_byte_mask
                if (search_direction == 1)
                {
                    ROM_NO[rom_byte_number] |= rom_byte_mask;
                }
                else
                {
                    ROM_NO[rom_byte_number] &= (uint8_t)(~rom_byte_mask);
                }

                // increment the byte counter id_bit_number
                // and shift the mask rom_byte_mask
                id_bit_number++;
                rom_byte_mask <<= 1;

                // if the mask is 0 then go to new SerialNum byte rom_byte_number
                // and reset mask
                if (rom_byte_mask == 0)
                {
                    //               calc_crc8(ROM_NO[rom_byte_number]);  // accumulate the CRC
                    rom_byte_number++;
                    rom_byte_mask = 1;
                }
            }
        } while (rom_byte_number < 8); // loop until through all ROM bytes 0-7

        // if the search was successful then
        //      if (!((id_bit_number < 65) || (crc8 != 0)))
        if (!((id_bit_number < 65)))
        {
            // search successful so set LastDiscrepancy,LastDeviceFlag
            // search_result
            LastDiscrepancy = last_zero;

            // check for last device
            if (LastDiscrepancy == 0)
            {
                LastDeviceFlag = TRUE;
            }
            search_result = TRUE;
        }
    }

    // if no device found then reset counters so next
    // 'search' will be like a first

    if (!search_result || (ROM_NO[0] == 0))
    {
        LastDiscrepancy = 0;
        LastDeviceFlag = FALSE;
        LastFamilyDiscrepancy = 0;
        Printf("OWSearch error \r\n");
        search_result = FALSE;
    }

    return search_result;
}

//--------------------------------------------------------------------------
// Use the DS2482 help command '1-Wire triplet' to perform one bit of a
// 1-Wire search.
// This command does two read bits and one write bit. The write bit
// is either the default direction (all device have same bit) or in case of
// a discrepancy, the 'search_direction' parameter is used.
//
// Returns – The DS2482 status byte result from the triplet command
//
static unsigned char DS2482_search_triplet(int search_direction)
{
    unsigned char status = 0;
    int poll_count = 0;

    // 1-Wire Triplet (Case B)
    //   S AD,0 [A] 1WT [A] SS [A] Sr AD,1 [A] [Status] A [Status] A\ P
    //                                         \--------/
    //                           Repeat until 1WB bit has changed to 0
    //  [] indicates from slave
    //  SS indicates byte containing search direction bit value in msbit

    temp[0] = CMD_1WT;
    temp[1] = search_direction ? 0x80 : 0x00;
    mss_I2c1_wr(I2C2_address, &temp[0], 2, MSS_I2C_HOLD_BUS);
    delay_ms(20);
    mss_I2c1_rd(I2C2_address, &status, 1, MSS_I2C_HOLD_BUS); // 读状态寄存器

    do
    {
        mss_I2c1_rd(I2C2_address, &status, 1, MSS_I2C_HOLD_BUS); // 读状态寄存器
    } while ((status & STATUS_1WB) && (poll_count++ < POLL_LIMIT));

    //mss_I2c1_rd(I2C2_address, &status, 1, MSS_I2C_RELEASE_BUS); // 为了发送stop位

    // check for failure due to poll limit reached
    if (poll_count >= POLL_LIMIT)
    {
        // handle error
        // ...
        DS2482_reset();
        return 0;
    }

    // return status byte
    return status;
}

/*********************************************************************************************
函数名称:读取DS18B20的ROM
函数功能:
作者	:     赵双锋
编写日期:2020.06.01
使用说明: 入口参数  :
          出口参数  :
          返回值     :
其他说明:
*********************************************************************************************/
void OWGetRom(void)
{
    uint8_t DS2482num = 0U; // DS2482序号
    uint8_t num = 0U;       // DS18B20序号
    uint8_t channel = 0U;   // 通道序号
    uint8_t Cir = 0U;

    memset(&stOneWire, 0x00, sizeof(stOneWire));

    for (DS2482num = 0U; DS2482num < 3U; DS2482num++) // 轮询所有DS2482
    {
        Printf("DS2428 select DS2482num=%d\r\n",(int)DS2482num);
        if (0U == DS2482num) // 第一片DS2482
        {
            DS2482_set_addr(DS2482_0);
        }

        if (1U == DS2482num) // 第二片DS2482
        {
            DS2482_set_addr(DS2482_1);
        }

        if (2U == DS2482num) // 第3片DS2482
        {
            DS2482_set_addr(DS2482_2);
        }

        for (Cir = 0; Cir < 5; Cir++)
        {
            if (TRUE == DS2482_detect()) // 进行DS2482选择，直到成功。总设置配置失败，单步调试可以，  DS2428 检测例程，该例程设置12C地址，然后执行设备复位，最后将配置字节写入默认值
            {
                Printf("DS2428 check success, set default setting\r\n");
                break;
            }
        }

        //暂时先设置通道0，目前测试只有通道0有18b20
        //channel = 0;
        for (channel = 0; channel < 8; channel++) // 进行DS2482-800的通道选择，直到成功。
        {
            for (Cir = 0; Cir < 5; Cir++)
            {
                if (!DS2482_channel_select(channel))
                {
                    Printf("channel select success, channel=%d\r\n",(int)channel);
                    break;
                }
            }

            num = 0U;
            //Printf("DS2482num=%d, chan=%d,\r\n",(int)DS2482num,(int)channel);
            if (TRUE == OWFirst()) // 寻找第一个DS18B20
            {
                Printf("DS2482num=%d, chan=%d,alread check DS18B20\r\n",(int)DS2482num,(int)channel);
                DS2482_set_rom(DS2482num, channel, 0, &ROM_NO[0]);
                for (num = 1; num < 10; num++) // 轮询所有DS18B20
                {
                    if (TRUE == OWNext())
                    {
                        Printf("DS2482num=%d, chan=%d,alread check DS18B20\r\n",(int)DS2482num,(int)channel);
                        DS2482_set_rom(DS2482num, channel, num, &ROM_NO[0]);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                Printf("channel =%d ,not check DS18B20\r\n",(int)channel);
            }
        }
    }
    return;
}

/*********************************************************************************************
函数名称:获取下一个Channel
函数功能:
作者	:     赵双锋
编写日期:2020.06.01
使用说明: 入口参数  :
          出口参数  :
          返回值     :
其他说明:
*********************************************************************************************/
static void OWGetNextChannel(uint8_t *pDS2482num, uint8_t *pchannel)
{
    uint8_t DS2482num, channel;
    uint8_t i;

    DS2482num = *pDS2482num; // DS2482序号
    channel = *pchannel;     // DS18B20序号

    if ((DS2482num < 3U) && (channel < 8U)) // 判断序号是否有效
    {
        if (7U == channel) // 若为最后一个通道
        {
            DS2482num = (DS2482num + 1) % 0x03; // 切换一个DS2482
        }
        *pDS2482num = DS2482num;
        channel = (channel + 1) % 0x08; // 通道号向后加一
        for (i = channel; i < 8U; i++)  // 轮询所有通道
        {
            *pchannel = i;
            if (0x01 == stOneWire.channelActive[DS2482num][i])
            {
                break;
            }
        }
    }
    else
    {
        *pDS2482num = 0U;
        *pchannel = 0U;
    }
    return;
}

/*=============================================================*\
* Description     	: DS18B20禁止
* Input             : DS18B20编号
* Output            : None
\*=============================================================*/
void DS18B20Banned(u8 num)
{
    stOneWire.DS18B20_banned[num - 1] = 0x11; // DS18B20禁止状态
    stOneWire.ow_alarm_sta[num - 1] = 1;
    //    PrintU8_HEX("DS18B20_banned[num - 1]: ",num - 1,0);
    //    PrintU8_HEX("ow_alarm_sta: ",stOneWire.ow_alarm_sta[num - 1],1);
    return;
}

/*=============================================================*\
* Description     	: 温度传感器查询
* Input             : None
* Output            : None
\*=============================================================*/
u8 DS18B20Exist(void)
{
    u8 crc = 0;
    if (DS18B20_NUMBER < stOneWire.DS18B20_exist_num)
    {
        stOneWire.DS18B20_exist_num = 0; // 80个都遍历完后将编号置0
    }
    for (crc = stOneWire.DS18B20_exist_num; crc <= DS18B20_NUMBER; crc++)
    {
        if (0x11 == stOneWire.DS18B20_exist[crc]) // 判断当前DS18B20是否存在
        {
            stOneWire.DS18B20_exist_num++;
            return (stOneWire.DS18B20_exist_num - 1);
        }
        stOneWire.DS18B20_exist_num++;
    }
    return 0;
}

/*=============================================================*\
* Description     	: 超限判断
* Input             : LoadNum当前载荷/风路第一个传感器的编号
* Output            : 温度报警状态“ow_statue”
\*=============================================================*/
static u8 AlarmAdjustLoad(u8 *state)
{
    return ((state[0] & state[1]) | (state[2] & state[3]) | (state[4] & state[5]) | (state[6] & state[7])); // 两两相与再相或(用于载荷)
}

/*=============================================================*\
* Description     	: 超限判断
* Input             : LoadNum当前载荷/风路第一个传感器的编号
* Output            : 温度报警状态“ow_statue”
\*=============================================================*/
static u8 AlarmAdjustFan(u8 *state)
{
    return (state[0] & state[1]); // 两两相与(用于风路)
}

/*=============================================================*\
* Description     	: one-wire超限状态
* Input             : LoadNum当前载荷/风路编号; NowAlaSta当前载荷/风路报警状态;loadsta当前载荷/风路超限状态
* Output            : 温度报警状态“ow_statue”
\*=============================================================*/
static u16 AlarmDisplay(u8 LoadNum, u16 NowAlaSta, u8 loadsta)
{
    u16 ow_index = 0;
    u16 ow_nowala_sta = 0; // 当前载荷/风路报警状态

    ow_nowala_sta = NowAlaSta;
    ow_index = (OW_BETWWEN >> (LoadNum * 2));
    if (1 == loadsta)
    {
        ow_nowala_sta |= ow_index;
    }
    else
    {
        ow_nowala_sta &= (~ow_index);
    }
    return ow_nowala_sta;
}

/*=============================================================*\
* Description     	: one-wire温度值超限监测
* Input             : OwNum当前温度传感器序号 ; OwTemp当前温度传感器温度值; OwThre载荷/风管 火情报警阈值;
* Output            : 温度报警状态“ow_statue”
\*=============================================================*/
static void OwTempAlarm(u8 OwNum, u16 OwTemp, u16 OwThre)
{
    u8 crc_ow, ow_num = 0;
    u16 ow_thre = 0; // 火情报警阈值

    ow_num = OwNum;   // 当前温度传感器序号
    ow_thre = OwThre; // 载荷/风管 火情报警阈值

    for (crc_ow = 2; crc_ow > 0; crc_ow--)
    {
        stOneWire.ow_temp_alarm[ow_num][crc_ow] = stOneWire.ow_temp_alarm[ow_num][crc_ow - 1]; // 将队列中的温度值往前滚动
    }
    stOneWire.ow_temp_alarm[ow_num][0] = OwTemp; // 获取最新温度值

    if (0 == (ow_num % 2))
    {
        if ((stOneWire.DS18B20_banned[ow_num] == 0x11) && (stOneWire.DS18B20_banned[ow_num + 1] == 0x11)) // DS18B20禁止状态
        {
            stOneWire.ow_alarm_sta[ow_num] = 0;
            stOneWire.ow_alarm_sta[ow_num + 1] = 0;
            return;
        }
    }
    else
    {
        if ((stOneWire.DS18B20_banned[ow_num] == 0x11) && (stOneWire.DS18B20_banned[ow_num - 1] == 0x11)) // DS18B20禁止状态
        {
            stOneWire.ow_alarm_sta[ow_num] = 0;
            stOneWire.ow_alarm_sta[ow_num - 1] = 0;
            return;
        }
    }

    if (0x11 == stOneWire.DS18B20_banned[ow_num])
    {
        //	    PrintU8_HEX("DS18B20_banned[ow_num]1: ",ow_num,0);
        //	    PrintU8_HEX("ow_alarm_sta1: ",stOneWire.ow_alarm_sta[ow_num],1);
        return;
    }

    if ((stOneWire.ow_temp_alarm[ow_num][0] > ow_thre) && (stOneWire.ow_temp_alarm[ow_num][1] > ow_thre) && (stOneWire.ow_temp_alarm[ow_num][2] > ow_thre))
    {
        //	    PrintU8_HEX("DS18B20_banned[ow_num]2: ",ow_num,0);
        //	    PrintU8_HEX("ow_alarm_sta2: ",stOneWire.ow_alarm_sta[ow_num],1);
        stOneWire.ow_alarm_sta[ow_num] = 1;
    }
    else
    {
        stOneWire.ow_alarm_sta[ow_num] = 0;
    }
    return;
}
/*=============================================================*\
* Description     	: one-wire匹配温度值与对应工参位置
* Input             : OwTemp当前温度传感器温度值
* Output            : None
=============================================================*/
void OwMatchGccs(u16 OwMarTemp, u64 OwRom, u64 *OwRomZdcs)
{
    u8 crc_match = 0;      // DS18B20序号
    u8 load_num = 0;       // 载荷序号
    u16 now_alarm_Sta = 0; // 当前载荷状态
    u16 ow_thre;           // 报警阈值
    u8 ow_nowala_sta = 0;  // 当前载荷/风管报警状态
    u8 load_first_num = 0; // 当前载荷/风管第一个传感器编号

    for (crc_match = 0; crc_match < 80; crc_match++) // 轮询所有DS18B20
    {
        if (OwRom == OwRomZdcs[crc_match])
        {
            if (OwMarTemp == 0xFFFF) // 若读取到的温度是）0xFFFF则说明该DS18B20故障
            {
                // yaoce.szlgccs.ckbgccs.yc_gccs_data.ow_status = (crc_match + 1);		  // 271-271one-wire状态查询
                // yaoce.szlgccs.ckbgccs.yc_gccs_data.Temp[crc_match] = sw16(OwMarTemp); // 上传温度
                Printf("sw16(OwMarTemp)=0x%x\r\n", sw16(OwMarTemp));
                return;
            }

            // if (crc_match <= 63) // 载荷
            // {
            // 	ow_thre = comp_value.load_fire_alarm / 0.0625;																// 载荷火情报警阈值（X ℃）
            // 	load_num = crc_match / 8;																					// 当前载荷标号
            // 	load_first_num = crc_match - (crc_match % 8);																// 当前载荷的第一个传感器编号
            // 	now_alarm_Sta = sw16(yaoce.szlgccs.ckbszl.yc_szl_data.tem_sta_load);										// 当前载荷报警状态
            // 	OwTempAlarm(crc_match, OwMarTemp, ow_thre);																	// 当前温度传感器是否超限
            // 	ow_nowala_sta = AlarmAdjustLoad(&stOneWire.ow_alarm_sta[load_first_num]);									// 当前载荷超限状态
            // 	yaoce.szlgccs.ckbszl.yc_szl_data.tem_sta_load = sw16(AlarmDisplay(load_num, now_alarm_Sta, ow_nowala_sta)); // 载荷温度超限状态
            // }
            // else // 风路
            // {
            // 	ow_thre = comp_value.fan_fire_alarm / 0.0625;															   // 风管火情报警阈值（Y ℃）
            // 	load_num = (crc_match - 64) / 2;																		   // 当前风管标号
            // 	load_first_num = crc_match - (crc_match % 2);															   // 当前风管的第一个传感器编号
            // 	now_alarm_Sta = sw16(yaoce.szlgccs.ckbszl.yc_szl_data.tem_sta_fan);										   // 当前风路报警状态
            // 	OwTempAlarm(crc_match, OwMarTemp, ow_thre);																   // 当前温度传感器是否超限
            // 	ow_nowala_sta = AlarmAdjustFan(&stOneWire.ow_alarm_sta[load_first_num]);								   // 当前载荷超限状态
            // 	yaoce.szlgccs.ckbszl.yc_szl_data.tem_sta_fan = sw16(AlarmDisplay(load_num, now_alarm_Sta, ow_nowala_sta)); // 载荷温度超限状态
            // }
            // stOneWire.DS18B20_exist[crc_match] = 0x11;							  // 当前DS18B20存在标志置位
            // yaoce.szlgccs.ckbgccs.yc_gccs_data.Temp[crc_match] = sw16(OwMarTemp); // 上传温度
            Printf("sw16(OwMarTemp)=0x%x\r\n", sw16(OwMarTemp));
            break;
        }
    }
    return;
}
