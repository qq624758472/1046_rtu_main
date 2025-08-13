/*
 * @Description:
 * @Version: 2.0
 * @Autor: ruog__
 * @Date: 2025-07-17 13:49:15
 * @LastEditors: ruog__
 * @LastEditTime: 2025-04-30 12:50:53
 */
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "gpio.h"
#include "myprintf.h"

uint8_t flag1_b15 = 0;
uint8_t flag2_d10 = 0;
uint8_t flag3_d11 = 0;
uint8_t flag4_d12 = 0;

// 对外8路gpio控制保存的当前状态
uint8_t out_gpio_status = 0;
uint8_t large_electric_status = 0;
uint16_t small_electric_status = 0;
uint8_t power_gpio_status = 0;
// /*
//  * Function:        User_LED_Init
//  * Description:     Configure LED GPIO.
//  * Param:           None.
//  * Return:          None.
//  */
// void User_LED_Init()
// {
//     GPIO_InitTypeDef GPIO_InitStructure;

//     GPIOG_CLK_ENABLE();

//     /* GPIOB Configure */
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//     GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
//     GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;

//     GPIO_Init(GPIOG, &GPIO_InitStructure);
// }

void User_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructureOut;

    GPIOB_CLK_ENABLE();
    // 对外GPIO输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_IType = GPIO_IPU;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIOD_CLK_ENABLE();
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // 对外GPIO输出
    GPIO_InitStructureOut.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructureOut.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructureOut.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructureOut.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOB, &GPIO_InitStructureOut);
    GPIO_InitStructureOut.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_Init(GPIOD, &GPIO_InitStructureOut);

    // 大电流配电使能-高有效  PG8  PC6   小电流配电使能  PA0-PA3, PC0-PC3, PE8-PE13  PF10, PG7
    GPIOA_CLK_ENABLE();
    GPIO_InitStructureOut.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructureOut);

    GPIOC_CLK_ENABLE();
    GPIO_InitStructureOut.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6; // PC1不能拉高
    GPIO_Init(GPIOC, &GPIO_InitStructureOut);

    GPIOE_CLK_ENABLE();
    GPIO_InitStructureOut.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOE, &GPIO_InitStructureOut);

    GPIOF_CLK_ENABLE();
    GPIO_InitStructureOut.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOF, &GPIO_InitStructureOut);

    GPIOG_CLK_ENABLE();
    GPIO_InitStructureOut.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
    GPIO_Init(GPIOG, &GPIO_InitStructureOut);

    GPIO_InitStructureOut.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6;
    GPIO_Init(GPIOH, &GPIO_InitStructureOut);
}

void user_gpio_out(unsigned char group, uint16_t pinNum, int8_t value)
{
    switch (group)
    {
    case 'A':
        /* code */
        GPIO_WriteBits(GPIOA, pinNum, value);
        break;
    case 'B':
        /* code */
        GPIO_WriteBits(GPIOB, pinNum, value);
        break;
    case 'C':
        /* code */
        GPIO_WriteBits(GPIOC, pinNum, value);
        break;
    case 'D':
        /* code */
        GPIO_WriteBits(GPIOD, pinNum, value);
        break;
    case 'E':
        /* code */
        GPIO_WriteBits(GPIOE, pinNum, value);
        break;
    case 'F':
        /* code */
        GPIO_WriteBits(GPIOF, pinNum, value);
        break;
    case 'G':
        /* code */
        GPIO_WriteBits(GPIOG, pinNum, value);
        break;
    default:
        break;
    }
}

void GPIOB_IRQ_Handler()
{
    if (GPIO_GetITStatus(GPIOB, GPIO_Pin_15) == SET)
    {
        flag1_b15 = 1;
        /*Clear Interrupt start state*/
        GPIO_ClearITPendingBit(GPIOB, GPIO_Pin_15);
    }
}

void GPIOD_IRQ_Handler()
{
    if (GPIO_GetITStatus(GPIOD, GPIO_Pin_10) == SET)
    {
        flag2_d10 = 1;
        /*Clear Interrupt start state*/
        GPIO_ClearITPendingBit(GPIOB, GPIO_Pin_10);
    }
    if (GPIO_GetITStatus(GPIOD, GPIO_Pin_11) == SET)
    {
        flag3_d11 = 1;
        /*Clear Interrupt start state*/
        GPIO_ClearITPendingBit(GPIOB, GPIO_Pin_11);
    }
    if (GPIO_GetITStatus(GPIOD, GPIO_Pin_12) == SET)
    {
        flag4_d12 = 1;
        /*Clear Interrupt start state*/
        GPIO_ClearITPendingBit(GPIOB, GPIO_Pin_12);
    }
}

// 高使能,iic的两个buffer, PB3,PB4
void iic_enable_open()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIOB_CLK_ENABLE();

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_WriteBits(GPIOB, GPIO_Pin_3, GPIO_OCtrl_Voh);
    GPIO_WriteBits(GPIOB, GPIO_Pin_4, GPIO_OCtrl_Voh);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOH, &GPIO_InitStructure);
    GPIO_WriteBits(GPIOH, GPIO_Pin_3, GPIO_OCtrl_Voh);
}

// 使能信号汇总
// PA8,9   PC 7,8,9   PG 2,3,4  PH 8
void User_all_enable()
{
    // iic使能
    iic_enable_open();

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIOG_CLK_ENABLE();
    GPIOA_CLK_ENABLE();
    GPIOC_CLK_ENABLE();
    // GPIOH_CLK_ENABLE();

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_Pin_x);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_Pin_x);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; // PA8  pa9不能拉低，
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;

    GPIO_Init(GPIOG, &GPIO_InitStructure);

    /* GPIOB Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;

    GPIO_Init(GPIOH, &GPIO_InitStructure);

    // pc 789 low
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;

    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_WriteBits(GPIOH, GPIO_Pin_8, GPIO_OCtrl_Vol);

    //串口使能
    GPIO_WriteBits(GPIOC, GPIO_Pin_7, GPIO_OCtrl_Vol);
    GPIO_WriteBits(GPIOC, GPIO_Pin_8, GPIO_OCtrl_Vol);
    GPIO_WriteBits(GPIOC, GPIO_Pin_9, GPIO_OCtrl_Vol);

    GPIO_WriteBits(GPIOA, GPIO_Pin_8, GPIO_OCtrl_Vol);
    GPIO_WriteBits(GPIOA, GPIO_Pin_9, GPIO_OCtrl_Vol);
    GPIO_WriteBits(GPIOG, GPIO_Pin_2, GPIO_OCtrl_Vol);
    GPIO_WriteBits(GPIOG, GPIO_Pin_3, GPIO_OCtrl_Vol);
    GPIO_WriteBits(GPIOG, GPIO_Pin_4, GPIO_OCtrl_Vol);
}

// 按顺序：
// PB11
// PB12
// PB13
// PB14
// PD1
// PD2
// PD3
// PD4
/**
 * @brief 控制对外8路gpio的高电平还是低电平
 *
 * @chan 8路中的哪一路，
 *
 * @ctr  0:1
 *
 */
uint8_t out_gpio_ctr(uint8_t chan, uint8_t ctr)
{
    if (ctr != 0 && ctr != 1)
    {
        Printf("ctr error\r\n");
        return -1;
    }
    Printf("out_gpio_ctr chan=%d, value=%d\r\n", chan, ctr);
    switch (chan)
    {
    case 0:
        GPIO_WriteBits(GPIOB, GPIO_Pin_11, ctr);
        break;
    case 1:
        GPIO_WriteBits(GPIOB, GPIO_Pin_12, ctr);
        break;
    case 2:
        GPIO_WriteBits(GPIOB, GPIO_Pin_13, ctr);
        break;
    case 3:
        GPIO_WriteBits(GPIOB, GPIO_Pin_14, ctr);
        break;
    case 4:
        GPIO_WriteBits(GPIOD, GPIO_Pin_1, ctr);
        break;
    case 5:
        GPIO_WriteBits(GPIOD, GPIO_Pin_2, ctr);
        break;
    case 6:
        GPIO_WriteBits(GPIOD, GPIO_Pin_3, ctr);
        break;
    case 7:
        GPIO_WriteBits(GPIOD, GPIO_Pin_4, ctr);
        break;
    default:
        Printf("chan error\r\n");
        return -1;
        break;
    }
    // 保存状态
    if (ctr == 1)
        out_gpio_status |= 1 << chan;
    else
        out_gpio_status &= ~(1 << chan); // 设置指定通道为低电平
    return 0;
}

// PG8
// PC6
/**
 * @brief 控制大电流配电使能
 *
 * @chan 8路中的哪一路，
 *
 * @ctr  0:1
 *
 */
uint8_t large_electric_gpio_ctr(uint8_t chan, uint8_t ctr)
{
    if (ctr != 0 && ctr != 1)
    {
        Printf("ctr error\r\n");
        return -1;
    }
    Printf("large_electric_gpio_ctr chan=%d, value=%d\r\n", chan, ctr);
    switch (chan)
    {
    case 0:
        GPIO_WriteBits(GPIOG, GPIO_Pin_8, ctr);
        break;
    case 1:
        GPIO_WriteBits(GPIOC, GPIO_Pin_6, ctr);
        break;
    default:
        Printf("chan error\r\n");
        return -1;
        break;
    }
    // 保存状态
    if (ctr == 1)
        large_electric_status |= 1 << chan;
    else
        large_electric_status &= ~(1 << chan); // 设置指定通道为低电平
    return 0;
}

// PF10
// PC0
// PC1
// PC2
// PC3
// PA0
// PA1
// PA2
// PA3
// PE8
// PE9
// PE10
// PE11
// PE12
// PE13
// PG7
/**
 * @brief 控制16路小电流配电使能
 *
 * @param chan 16路中的哪一路 (0-15)
 * @param ctr  控制值: 0=关闭, 1=打开
 *
 * @return 0=成功, -1=参数错误
 */
uint8_t small_electric_gpio_ctr(uint8_t chan, uint8_t ctr)
{
    // 参数检查
    if (ctr > 1)
    {
        Printf("ctr error: must be 0 or 1\r\n");
        return -1;
    }

    if (chan > 15)
    {
        Printf("chan error: must be 0-15\r\n");
        return -1;
    }
    Printf("small_electric_gpio_ctr chan=%d, value=%d\r\n", chan, ctr);
    // 根据通道号选择对应的GPIO
    switch (chan)
    {
    case 0: // PF10
        GPIO_WriteBits(GPIOF, GPIO_Pin_10, ctr);
        break;

    case 1: // PC0
        GPIO_WriteBits(GPIOC, GPIO_Pin_0, ctr);
        break;

    case 2: // PC1
        GPIO_WriteBits(GPIOC, GPIO_Pin_1, ctr);
        break;

    case 3: // PC2
        GPIO_WriteBits(GPIOC, GPIO_Pin_2, ctr);
        break;

    case 4: // PC3
        GPIO_WriteBits(GPIOC, GPIO_Pin_3, ctr);
        break;

    case 5: // PA0
        GPIO_WriteBits(GPIOA, GPIO_Pin_0, ctr);
        break;

    case 6: // PA1
        GPIO_WriteBits(GPIOA, GPIO_Pin_1, ctr);
        break;

    case 7: // PA2
        GPIO_WriteBits(GPIOA, GPIO_Pin_2, ctr);
        break;

    case 8: // PA3
        GPIO_WriteBits(GPIOA, GPIO_Pin_3, ctr);
        break;

    case 9: // PE8
        GPIO_WriteBits(GPIOE, GPIO_Pin_8, ctr);
        break;

    case 10: // PE9
        GPIO_WriteBits(GPIOE, GPIO_Pin_9, ctr);
        break;

    case 11: // PE10
        GPIO_WriteBits(GPIOE, GPIO_Pin_10, ctr);
        break;

    case 12: // PE11
        GPIO_WriteBits(GPIOE, GPIO_Pin_11, ctr);
        break;

    case 13: // PE12
        GPIO_WriteBits(GPIOE, GPIO_Pin_12, ctr);
        break;

    case 14: // PE13
        GPIO_WriteBits(GPIOE, GPIO_Pin_13, ctr);
        break;

    case 15: // PG7
        GPIO_WriteBits(GPIOG, GPIO_Pin_7, ctr);
        break;

    default:
        Printf("chan error: invalid channel %d\r\n", chan);
        return -1;
    }

    // 保存状态（使用正确的状态变量名）
    if (ctr == 1)
        small_electric_status |= (1 << chan); // 设置对应位
    else
        small_electric_status &= ~(1 << chan); // 清除对应位

    return 0; // 操作成功
}

// 按顺序：
// PH6
// PH3
/**
 * @brief 控制电源输出使能
 *
 * @chan 2路中的哪一路，
 *
 * @ctr  0:1
 *
 */
uint8_t power_gpio_ctr(uint8_t chan, uint8_t ctr)
{
    if (ctr != 0 && ctr != 1)
    {
        Printf("ctr error\r\n");
        return -1;
    }
    Printf("power_gpio_ctr chan=%d, value=%d\r\n", chan, ctr);
    switch (chan)
    {
    case 0:
        GPIO_WriteBits(GPIOH, GPIO_Pin_6, ctr);
        break;
    case 1:
        GPIO_WriteBits(GPIOH, GPIO_Pin_3, ctr);
        break;
    default:
        Printf("chan error\r\n");
        return -1;
        break;
    }
    // 保存状态
    if (ctr == 1)
        power_gpio_status |= 1 << chan;
    else
        power_gpio_status &= ~(1 << chan); // 设置指定通道为低电平
    return 0;
}