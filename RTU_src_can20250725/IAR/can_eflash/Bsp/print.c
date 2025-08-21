#include "print.h"
#include "as32x601_usart_regs.h"
#include "delay.h"
// #include "uart_dianji.h"
#include "delay.h"
#include "print.h"
#include "myprintf.h"

extern void std_feed_dog();
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


/**
 * @brief 向指定USART外设发送十六进制数据，并打印发送的内容
 * @param uart: 目标USART外设（如USART0、USART1等宏定义）
 * @param data: 待发送的数据缓冲区
 * @param len: 待发送数据的长度
 * @return 0: 成功
 */
uint8_t uart_send_hex_datas(USART_TypeDef *uart, uint8_t *data, uint32_t len)
{
    // 参数合法性检查
    if (uart == NULL || data == NULL || len == 0)
    {
        Printf("uart_send_hex_datas arg error\r\n");
        return 1; // 无效参数
    }
// C0 05 01 09
#if 0
    uint8_t tmp[] = {0xc0, 0x05, 0x01, 0x09};
    len = 4;
#endif
    uint32_t i = 0;
    for (i = 0; i < len; i++)
    {
        // 向指定的USART外设发送数据
        USART_SendData(uart, data[i]);
        while (USART_GetFlagStatus(uart, USART_FLAG_TC) == RESET)
        {
        }
        // USART_SendData(uart, tmp[i]);
        // delay_ms(1);
        // delay_us(800);
        // Printf("0x%x ", data[i]); // 打印每个字节的十六进制表示
    }
    Printf("len=%d\r\n", len); // 换行 - 注释掉自动打印，避免干扰
    return 0;
}

//=======================原理图上的uart调试   芯片的uart6======
void User_appTS_uart6_Init(uint32_t BaudRate)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    PLIC_InitTypeDef PLIC_InitStructure;

    GPIOE_CLK_ENABLE();
    USART6_CLK_ENABLE();

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_USART6); /* USART0_TX */
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_USART6); /* USART0_RX */
    /* GPIO Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    USART6_RESET();
    delay_ms(100);
    USART6_SET();
    USART_DeInit(USART6);

    USART_StructInit(&USART_InitStructure);

    /* Initializes the USART6 */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_OverSampling = USART_OverSampling_16;
    USART_Init(USART6, &USART_InitStructure);

    USART_Cmd(USART6, ENABLE);

    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);

    /* Configer the USART6 interrupt */
    PLIC_InitStructure.PLIC_IRQChannel = USART6_IRQn;
    PLIC_InitStructure.PLIC_IRQPriority = 1;
    PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
    PLIC_Init(&PLIC_InitStructure);
}

//=======================原理图上的uart1   芯片的uart5======
void User_app1_uart5_Init(uint32_t BaudRate)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    PLIC_InitTypeDef PLIC_InitStructure;

    GPIOG_CLK_ENABLE();
    USART5_CLK_ENABLE();

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_USART5); /* USART5_TX */
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource13, GPIO_AF_USART5); /* USART5_RX */
    /* GPIO Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    USART5_RESET();
    delay_ms(100);
    USART5_SET();
    USART_DeInit(USART5);

    USART_StructInit(&USART_InitStructure);

    /* Initializes the USART5 */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_OverSampling = USART_OverSampling_16;
    ClearCache();
    USART_Init(USART5, &USART_InitStructure);
    USART_ClearITPendingBit(USART5, USART_IT_RXNE);
    USART_Cmd(USART5, ENABLE);

    USART_ITConfig(USART5, USART_IT_RXNE, ENABLE);

    /* Configer the USART5 interrupt */
    PLIC_InitStructure.PLIC_IRQChannel = USART5_IRQn;
    PLIC_InitStructure.PLIC_IRQPriority = 1;
    PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
    ClearCache();
    PLIC_Init(&PLIC_InitStructure);
}

//=======================原理图上的uart2   芯片的uart3======
void User_app2_uart3_Init(uint32_t BaudRate)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    PLIC_InitTypeDef PLIC_InitStructure;

    GPIOA_CLK_ENABLE();
    USART3_CLK_ENABLE();

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_USART3); /* USART0_TX */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_USART3); /* USART0_RX */
    /* GPIO Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART3_RESET();
    delay_ms(200);
    USART3_SET();
    USART_DeInit(USART3);

    USART_StructInit(&USART_InitStructure);

    /* Initializes the USART3 */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_OverSampling = USART_OverSampling_16;
    USART_Init(USART3, &USART_InitStructure);

    USART_Cmd(USART3, ENABLE);

    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    /* Configer the USART3 interrupt */
    PLIC_InitStructure.PLIC_IRQChannel = USART3_IRQn;
    PLIC_InitStructure.PLIC_IRQPriority = 1;
    PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
    PLIC_Init(&PLIC_InitStructure);
}

//=======================原理图上的uart3   芯片的uart1======
void User_app3_uart1_Init(uint32_t BaudRate)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    PLIC_InitTypeDef PLIC_InitStructure;

    // 使能GPIO和USART时钟
    GPIOD_CLK_ENABLE();
    // GPIOH_CLK_ENABLE();
    USART1_CLK_ENABLE();

    /* 设置GPIO复用映射 */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_USART1); /* USART1_RX */
    GPIO_PinAFConfig(GPIOH, GPIO_PinSource2, GPIO_AF_USART1);  /* USART1_TX */

    /* GPIO Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOH, &GPIO_InitStructure);

    USART1_RESET();
    delay_ms(100);
    USART1_SET();
    USART_DeInit(USART1);

    USART_StructInit(&USART_InitStructure);

    /* Initializes the USART1 */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_OverSampling = USART_OverSampling_16;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* Configer the USART1 interrupt */
    PLIC_InitStructure.PLIC_IRQChannel = USART1_IRQn;
    PLIC_InitStructure.PLIC_IRQPriority = 1;
    PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
    PLIC_Init(&PLIC_InitStructure);
}

/*
 * Function:        User_app4_uart0_Init
 * Description:     Configure Print USART.
 * Param:           BaudRate: USART communication baud rate.
 * Return:          None.
 */
void User_app4_uart0_Init(uint32_t BaudRate)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    PLIC_InitTypeDef PLIC_InitStructure;

    GPIOD_CLK_ENABLE();
    USART0_CLK_ENABLE();

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART0); /* USART0_TX */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART0); /* USART0_RX */
    /* GPIO Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART0_RESET();
    USART0_SET();
    USART_DeInit(USART0);

    USART_StructInit(&USART_InitStructure);

    /* Initializes the USART0 */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_OverSampling = USART_OverSampling_16;
    USART_Init(USART0, &USART_InitStructure);

    USART_Cmd(USART0, ENABLE);
    USART_ClearITPendingBit(USART0, USART_IT_RXNE); // 加清中断
    USART_ITConfig(USART0, USART_IT_RXNE, ENABLE);

    /* Configer the USART0 interrupt */
    PLIC_InitStructure.PLIC_IRQChannel = USART0_IRQn;
    PLIC_InitStructure.PLIC_IRQPriority = 1;
    PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
    PLIC_Init(&PLIC_InitStructure);
}

/*
 * Function:        USART0_IRQ_Handler
 * Description:     USART0 interrupt handler function.
 * Param:           None.
 * Return:          None.
 */

void USART0_IRQ_Handler()
{
#if 0
    if(USART_GetFlagStatus(USART0, USART_FLAG_RXNE) != RESET)
    {
        /* Clear the interrupt pending bits */
        USART_ClearITPendingBit(USART0, USART_IT_RXNE);
        USART_SendData(USART0,USART_ReceiveData(USART0));
    }
#endif
    if (USART_GetFlagStatus(USART0, USART_FLAG_RXNE) != RESET)
    {
        USART_ClearITPendingBit(USART0, USART_IT_RXNE);
        data4[ptr4++] = USART_ReceiveData(USART0);
    }
}
#if 0
void USART6_IRQ_Handler()
{
    if(USART_GetFlagStatus(USART6, USART_FLAG_RXNE) != RESET)
    {
        USART_ClearITPendingBit(USART6, USART_IT_RXNE);
        data5[ptr5++] = USART_ReceiveData(USART6);
        USART_ClearITPendingBit(USART6, USART_IT_RXNE);

    }
}
#endif
/*
 * Function:        USART5_IRQ_Handler
 * Description:     USART5 interrupt handler function.
 * Param:           None.
 * Return:          None.
 */

void USART5_IRQ_Handler()
{

    if (USART_GetFlagStatus(USART5, USART_FLAG_RXNE) != RESET)
    {

        data1[ptr1++] = USART_ReceiveData(USART5);
        USART_ClearITPendingBit(USART5, USART_IT_RXNE);
    }
}

/*
 * Function:        USART3_IRQ_Handler
 * Description:     USART0 interrupt handler function.
 * Param:           None.
 * Return:          None.
 */

void USART3_IRQ_Handler()
{
    if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
    {

        data2[ptr2++] = USART_ReceiveData(USART3);
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}

/*
 * Function:        USART1_IRQ_Handler
 * Description:     USART1中断处理函数 (对应原理图上的UART3)
 * Param:           None.
 * Return:          None.
 */
void USART1_IRQ_Handler()
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        data3[ptr3++] = USART_ReceiveData(USART1);
        if (ptr3 >= 1024)
            ptr3 = 0;
    }
}
