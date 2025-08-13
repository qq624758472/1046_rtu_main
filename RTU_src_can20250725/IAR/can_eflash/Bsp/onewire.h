/*
 * OneWire.h
 *
 *  Created on: 2018-11-21
 *      Author: yangl
 */
#ifndef ONEWIRE_H_
#define ONEWIRE_H_

//#include "mss_i2c.h"

#define DS2482_0 0x18 // DS2482-800  IIC器件1地址
#define DS2482_1 0x1C // DS2482-800  IIC器件2地址
#define DS2482_2 0x1E // DS2482-800  IIC器件2地址

#define CMD_DRST 0xF0 /*Device Reset*/
#define CMD_CHSL 0xC3 /*Channel Select*/
#define CMD_WCFG 0xD2 /*Write Configuration*/
#define CMD_1WRS 0xB4 /*1-wire Reset*/
#define CMD_1WSB 0x87 /*1-wire single bit*/
#define CMD_SRP 0xE1  /*set read pointer 参数: F0(状态）,E1(数据),C3（配置)*/
#define CMD_1WWB 0xA5 /*1-wire write byte*/
#define CMD_1WRB 0x96 /*1-wire read byte*/
#define CMD_1WT 0x78  /*1-wire Triplet*/

// DS18S20命令字
#define Read_Rom 0x33
#define Match_Rom 0x55
#define Skip_Rom 0xCC
#define Search_Rom 0xF0
#define Alarm_Search 0xEC
#define Temp_Change 0x44
#define Read_Temp 0xBE

#define CONFIG_APU 0x01
#define FALSE 0
#define TRUE 1

#define STATUS_1WB 0x01
#define STATUS_SD 0x04
#define STATUS_PPD 0x02
#define STATUS_SBR 0x20
#define STATUS_TSB 0x40
#define STATUS_DIR 0x80

#define TEMP_CONVER 0.0625
#define POLL_LIMIT 50

#define DS2482_MAX 39 /*每个DS2482上传感器编号最大值*/
#define CHANNEL_MAX 4 /*每个DS2482上channel编号最大值*/
#define DS18B20_MAX 7 /*每个channel上温度传感器编号最大值*/
#define ow_num_rom 8  /*rom值字节数*/


#define MSS_I2C_HOLD_BUS 0//没用
#define MSS_I2C_RELEASE_BUS 0//没用

#define OW_BETWWEN 0xc000
#define DS18B20_NUMBER 79

#define AND_STATE_LOAD(a) ((((u8)a[0]) & ((u8)a[1])) | (((u8)a[2]) & ((u8)a[3])) | (((u8)a[4]) & ((u8)a[5])) | (((u8)a[6]) & ((u8)a[7]))) // 两两相与再相或(用于载荷)
#define AND_STATE_FAN(a) (((u8)a[0]) & ((u8)a[1]))																						  // 两两相与(用于风路)
enum OneWireOpt
{
	ONEWIRE_FREE = 0x00,
	ONEWIRE_READTEMP = 0x01,
	ONEWIRE_WAIT = 0x02,
	ONEWIRE_CHSL = 0x03
};

typedef struct
{
	uint8_t DS2482Active[3];
	uint8_t channelActive[3][8];
	uint8_t DS1820Active0[8][10];
	uint8_t DS1820Active1[8][10];
    uint8_t DS1820Active2[8][10];
	uint8_t ucROMTabl0[8][10 * 8];
	uint8_t ucROMTabl1[8][10 * 8];
    uint8_t ucROMTabl2[8][10 * 8];
	uint16_t ow_temp_alarm[80][3];
	uint8_t ow_alarm_sta[80];
	uint8_t DS18B20_banned[80];
	uint8_t DS18B20_exist[80];
	uint8_t DS18B20_exist_num;
} onewire_t;

union ROM_CHANGE_ZD
{
	u8 rom_s_zd[640];
	u64 rom_b_zd[80];
}; // 装订参数读取rom值

union ROM_CHANGE_OW
{
	u8 rom_s_ow[8];
	u64 rom_b_ow;
}; // one_wire总线读取rom值

void Read_Temperature(void);

void OWGetRom(void);

u8 DS18B20Exist(void);
/*=============================================================*\
* Description     	: DS18B20禁止
* Input             : DS18B20编号
* Output            : None
\*=============================================================*/
void DS18B20Banned(u8 num);

/*=============================================================*\
* Description     	: one-wire匹配温度值与对应工参位置
* Input             : OwTemp当前温度传感器温度值
* Output            : None
\*=============================================================*/
void OwMatchGccs(u16 OwMarTemp, u64 OwRom, u64 *OwRomZdcs);

#endif /* ONEWIRE_H_ */
