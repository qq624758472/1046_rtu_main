#include "adc.h"
#include "delay.h"
#include "string.h"
#include "myprintf.h"
#include "stdio.h"

getADCValue ADCValue; // 获取到的所有ADC值的缓存

// ADC0-PA4--ADC1_IN5
// ADC1-PA5--ADC1_IN6
// ADC2-PA6--ADC1_IN7
// ADC3-PA7--ADC1_IN8
// ADC4-PC4--ADC1_IN9
// ADC5-PC5--ADC1_IN10
// ADC6-PB0--ADC1_IN11
// ADC7-PB1--ADC1_IN12
// ADC8-PB2--ADC1_IN13
// ADC9-PF11--ADC1_IN14
// ADC10-PF12--ADC1_IN15
// ADC11-PF13--ADC2_IN0
// ADC12-PF14--ADC2_IN1
// ADC13-PF15--ADC2_IN2
// ADC14-PG0--ADC2_IN3
// ADC15-PG1--ADC2_IN4
// ADCVERF-PE7--ADC2_IN5

void User_ADC_All_Init()
{

    ADC1_CLK_ENABLE();
    ADC2_CLK_ENABLE();
    GPIOA_CLK_ENABLE();
    GPIOB_CLK_ENABLE();
    GPIOC_CLK_ENABLE();
    GPIOE_CLK_ENABLE();
    GPIOF_CLK_ENABLE();
    GPIOG_CLK_ENABLE();

    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_ChannelTypeDef ADC_ChannelStructure;

    /* Configure the GPIO pins as analog inputs */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

#ifdef DEBUG
    ADC1_RESET();
    ADC2_RESET();
    delay_ms(100);
    ADC1_SET();
    ADC2_SET();
#endif

    ADC_StructInit(&ADC_InitStructure);

    ADC_InitStructure.ADC_ClockDivide = ADC_CLK_DIVIDE_4;    // ADC时钟分频为4
    ADC_InitStructure.ADC_Resolution = ADC_RESOLUTION_12BIT; // 12位分辨率
    ADC_InitStructure.ADC_Alignment = ADC_DATA_ALIGN_RIGHT;  // 数据右对齐
    ADC_InitStructure.ADC_Symbol = ADC_DATA_SELDO_UNSIGNED;  // 无符号数据格式

    ADC_InitStructure.ADC_RegularTrigger = ADC_TRIGGER_INTERNAL; // 规则组使用内部触发
    ADC_InitStructure.ADC_InjectTrigger = ADC_TRIGGER_INTERNAL;  // 注入组使用内部触发

    ADC_InitStructure.ADC_RegularEnable = ENABLE; // 禁用规则组转换
    ADC_InitStructure.ADC_InjectEnable = DISABLE; // 启用注入组转换

    ADC_InitStructure.ADC_DmaEnable = DISABLE; // 禁用DMA传输

    ADC_InitStructure.ADC_ScanModeEn = ENABLE;                  // 启用扫描模式(多通道)
    ADC_InitStructure.ADC_ContinuousModeEn = ENABLE;            // 启用连续转换模式
    ADC_InitStructure.ADC_RegularDiscontinuousModeEn = DISABLE; // 禁用规则组间断模式
    ADC_InitStructure.ADC_InjectDiscontinuousModeEn = DISABLE;  // 禁用注入组间断模式
    ADC_InitStructure.ADC_InjectAutoModeEn = ENABLE;            // 启用注入组自动模式
    ADC_InitStructure.ADC_IntervalModeEn = DISABLE;             // 禁用间隔模式

    ADC_InitStructure.ADC_RegularSequenceLength = 16; // 规则组序列长度为0(禁用)
    ADC_InitStructure.ADC_InjectSequenceLength = 16;  // 注入组序列长度为4(4个通道)

    ADC_InitStructure.ADC_PowerEn = ENABLE;
    ADC_InitStructure.ADC_PowerRegain = ENABLE;

    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_Init(ADC2, &ADC_InitStructure);

    /* Configure ADC channel 1 */
    ADC_ChannelStructure.ADC_SampleTime = ADC_SPT_CLK_640;
    ADC_ChannelStructure.ADC_InterruptEn = DISABLE;

    ADC_ChannelStructure.ADC_Channel = ADC_CH_6;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_0, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_7;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_1, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_8;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_2, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_9;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_3, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_10;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_4, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_11;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_5, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_12;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_6, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_13;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_7, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_14;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_8, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_15;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_9, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_16;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_10, &ADC_ChannelStructure);

    // ADC2
    ADC_ChannelStructure.ADC_Channel = ADC_CH_1;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_0, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_2;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_1, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_3;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_2, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_4;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_3, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_5;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_4, &ADC_ChannelStructure);

    // 内部温度或电压采集
    ADC_ChannelStructure.ADC_Channel = ADC_CH_6;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_5, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_13;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_6, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_14;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_7, &ADC_ChannelStructure);
    ADC_ChannelStructure.ADC_Channel = ADC_CH_15;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_8, &ADC_ChannelStructure);
}

void User_ADC1_Init(void)
{

    ADC1_CLK_ENABLE();
    GPIOA_CLK_ENABLE();

    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_ChannelTypeDef ADC_ChannelStructure;

    /* Configure the GPIO pins as analog inputs */
    // GPIO_InitStructure.GPIO_Pin       = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

#ifdef DEBUG
    ADC1_RESET();
    delay_ms(100);
    ADC1_SET();

#endif

    ADC_StructInit(&ADC_InitStructure);

    ADC_InitStructure.ADC_ClockDivide = ADC_CLK_DIVIDE_4;    // ADC时钟分频为4
    ADC_InitStructure.ADC_Resolution = ADC_RESOLUTION_12BIT; // 12位分辨率
    ADC_InitStructure.ADC_Alignment = ADC_DATA_ALIGN_RIGHT;  // 数据右对齐
    ADC_InitStructure.ADC_Symbol = ADC_DATA_SELDO_UNSIGNED;  // 无符号数据格式

    ADC_InitStructure.ADC_RegularTrigger = ADC_TRIGGER_INTERNAL; // 规则组使用内部触发
    ADC_InitStructure.ADC_InjectTrigger = ADC_TRIGGER_INTERNAL;  // 注入组使用内部触发

    ADC_InitStructure.ADC_RegularEnable = ENABLE; // 禁用规则组转换
    ADC_InitStructure.ADC_InjectEnable = DISABLE; // 启用注入组转换

    ADC_InitStructure.ADC_DmaEnable = DISABLE; // 禁用DMA传输

    ADC_InitStructure.ADC_ScanModeEn = DISABLE;                 // 启用扫描模式(多通道)
    ADC_InitStructure.ADC_ContinuousModeEn = ENABLE;            // 启用连续转换模式
    ADC_InitStructure.ADC_RegularDiscontinuousModeEn = DISABLE; // 禁用规则组间断模式
    ADC_InitStructure.ADC_InjectDiscontinuousModeEn = DISABLE;  // 禁用注入组间断模式
    ADC_InitStructure.ADC_InjectAutoModeEn = ENABLE;            // 启用注入组自动模式
    ADC_InitStructure.ADC_IntervalModeEn = DISABLE;             // 禁用间隔模式

    ADC_InitStructure.ADC_RegularSequenceLength = 1; // 规则组序列长度为0(禁用)
    ADC_InitStructure.ADC_InjectSequenceLength = 0;  // 注入组序列长度为4(4个通道)

    ADC_InitStructure.ADC_PowerEn = ENABLE;
    ADC_InitStructure.ADC_PowerRegain = ENABLE;

    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_ChannelStructure.ADC_Channel = ADC_CH_7;
    ADC_ChannelStructure.ADC_SampleTime = ADC_SPT_CLK_640;
    ADC_ChannelStructure.ADC_InterruptEn = DISABLE;
    ADC_ConfigChannel(ADC1, ADC_RSEQ_0, &ADC_ChannelStructure);

    /* Configure ADC channel 1 */
    // ADC_ChannelStructure.ADC_Channel = ADC_CH_1;
    // ADC_ChannelStructure.ADC_SampleTime = ADC_SPT_CLK_3;
    // ADC_ChannelStructure.ADC_InterruptEn = DISABLE;
    // ADC_ConfigChannel(ADC1, ADC_RSEQ_0, &ADC_ChannelStructure);
    // ADC_ChannelStructure.ADC_Channel = ADC_CH_7;
    // ADC_ConfigChannel(ADC1, ADC_RSEQ_1, &ADC_ChannelStructure);
}

void User_ADC2_Init(void)
{

    ADC2_CLK_ENABLE();
    GPIOE_CLK_ENABLE();

    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_ChannelTypeDef ADC_ChannelStructure;

    /* Configure the GPIO pins as analog inputs */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_IType = GPIO_IN_FLOATING;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_4_5mA;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

#ifdef DEBUG
    ADC2_RESET();
    delay_ms(100);
    ADC2_SET();

#endif

    ADC_StructInit(&ADC_InitStructure);

    ADC_InitStructure.ADC_ClockDivide = ADC_CLK_DIVIDE_4;    // ADC时钟分频为4
    ADC_InitStructure.ADC_Resolution = ADC_RESOLUTION_12BIT; // 12位分辨率
    ADC_InitStructure.ADC_Alignment = ADC_DATA_ALIGN_RIGHT;  // 数据右对齐
    ADC_InitStructure.ADC_Symbol = ADC_DATA_SELDO_UNSIGNED;  // 无符号数据格式

    ADC_InitStructure.ADC_RegularTrigger = ADC_TRIGGER_INTERNAL; // 规则组使用内部触发
    ADC_InitStructure.ADC_InjectTrigger = ADC_TRIGGER_INTERNAL;  // 注入组使用内部触发

    ADC_InitStructure.ADC_RegularEnable = ENABLE; // 禁用规则组转换
    ADC_InitStructure.ADC_InjectEnable = DISABLE; // 启用注入组转换

    ADC_InitStructure.ADC_DmaEnable = DISABLE; // 禁用DMA传输

    ADC_InitStructure.ADC_ScanModeEn = ENABLE;                  // 启用扫描模式(多通道)
    ADC_InitStructure.ADC_ContinuousModeEn = ENABLE;            // 启用连续转换模式
    ADC_InitStructure.ADC_RegularDiscontinuousModeEn = DISABLE; // 禁用规则组间断模式
    ADC_InitStructure.ADC_InjectDiscontinuousModeEn = DISABLE;  // 禁用注入组间断模式
    ADC_InitStructure.ADC_InjectAutoModeEn = ENABLE;            // 启用注入组自动模式
    ADC_InitStructure.ADC_IntervalModeEn = DISABLE;             // 禁用间隔模式

    ADC_InitStructure.ADC_RegularSequenceLength = 2; // 规则组序列长度为0(禁用)
    ADC_InitStructure.ADC_InjectSequenceLength = 0;  // 注入组序列长度为4(4个通道)

    ADC_InitStructure.ADC_PowerEn = ENABLE;
    ADC_InitStructure.ADC_PowerRegain = ENABLE;

    ADC_Init(ADC2, &ADC_InitStructure);

    /* Configure ADC channel 1 */
    ADC_ChannelStructure.ADC_Channel = ADC_CH_7;
    ADC_ChannelStructure.ADC_SampleTime = ADC_SPT_CLK_3;
    ADC_ChannelStructure.ADC_InterruptEn = DISABLE;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_0, &ADC_ChannelStructure);

    ADC_ChannelStructure.ADC_Channel = ADC_CH_10;
    ADC_ConfigChannel(ADC2, ADC_RSEQ_1, &ADC_ChannelStructure);
}

/**  按照下面的顺序进行采集
ADC0-PA4--ADC1_IN5
ADC1-PA5--ADC1_IN6
ADC2-PA6--ADC1_IN7
ADC3-PA7--ADC1_IN8
ADC4-PC4--ADC1_IN9
ADC5-PC5--ADC1_IN10
ADC6-PB0--ADC1_IN11
ADC7-PB1--ADC1_IN12
ADC8-PB2--ADC1_IN13
ADC9-PF11--ADC1_IN14
ADC10-PF12--ADC1_IN15
ADC11-PF13--ADC2_IN0
ADC12-PF14--ADC2_IN1
ADC13-PF15--ADC2_IN2
ADC14-PG0--ADC2_IN3
ADC15-PG1--ADC2_IN4
内部电压采集
ADCVERF-PE7--ADC2_IN5
ADC_3V3_1   PE14
CW                PE15
ADC_3V3       PB10
 */
uint8_t User_ADC_GetAllValue()
{
    uint16_t adc_value = 0;
    // 数据不用初始化，保持保存最后一次的数据
    memset(&ADCValue, 0, sizeof(ADCValue));
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_0) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_0, &adc_value);
    Printf("ADC ADC_RSEQ_0  PA4  value is %d\r\n", adc_value);
    ADCValue.outValue[0] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_1) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_1, &adc_value);
    Printf("ADC ADC_RSEQ_1  PA5  value is %d\r\n", adc_value);
    ADCValue.outValue[1] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_2) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_2, &adc_value);
    Printf("ADC ADC_RSEQ_2  PA6  value is %d\r\n", adc_value);
    ADCValue.outValue[2] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_3) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_3, &adc_value);
    Printf("ADC ADC_RSEQ_3  PA7  value is %d\r\n", adc_value);
    ADCValue.outValue[3] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_4) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_4, &adc_value);
    Printf("ADC ADC_RSEQ_4  PC4  value is %d\r\n", adc_value);
    ADCValue.outValue[4] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_5) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_5, &adc_value);
    Printf("ADC ADC_RSEQ_5  PC5  value is %d\r\n", adc_value);
    ADCValue.outValue[5] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_6) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_6, &adc_value);
    Printf("ADC ADC_RSEQ_6  PB0  value is %d\r\n", adc_value);
    ADCValue.outValue[6] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_7) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_7, &adc_value);
    Printf("ADC ADC_RSEQ_7  PB1  value is %d\r\n", adc_value);
    ADCValue.outValue[7] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_8) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_8, &adc_value);
    Printf("ADC ADC_RSEQ_8  PB2  value is %d\r\n", adc_value);
    ADCValue.outValue[8] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_9) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_9, &adc_value);
    Printf("ADC ADC_RSEQ_9  PF11  value is %d\r\n", adc_value);
    ADCValue.outValue[9] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC, ADC_RSEQ_10) == RESET)
    {
    }
    ADC_GetSeqResult(ADC1, ADC_RSEQ_10, &adc_value);
    Printf("ADC ADC_RSEQ_10  PF12  value is %d\r\n", adc_value);
    ADCValue.outValue[10] = adc_value;
    delay_ms(500);
#if 1
    // ADC2
    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_0) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_0, &adc_value);
    Printf("ADC2 ADC_RSEQ_0  PF13 value is %d\r\n", adc_value);
    ADCValue.outValue[11] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_1) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_1, &adc_value);
    Printf("ADC2 ADC_RSEQ_1  PF14 value is %d\r\n", adc_value);
    ADCValue.outValue[12] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_2) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_2, &adc_value);
    Printf("ADC2 ADC_RSEQ_2  PF15 value is %d\r\n", adc_value);
    ADCValue.outValue[13] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_3) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_3, &adc_value);
    Printf("ADC2 ADC_RSEQ_3  PG0 value is %d\r\n", adc_value);
    ADCValue.outValue[14] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_4) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_4, &adc_value);
    Printf("ADC2 ADC_RSEQ_4  PG1 value is %d\r\n", adc_value);
    ADCValue.outValue[15] = adc_value;
    delay_ms(500);
    //============内部电压采集开始
    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_5) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_5, &adc_value);
    Printf("ADC2 ADC_RSEQ_5  PE7 value is %d\r\n", adc_value);
    ADCValue.inValue[0] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_6) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_6, &adc_value);
    Printf("ADC2 ADC_RSEQ_6  PE14 value is %d\r\n", adc_value);
    ADCValue.inValue[1] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_7) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_7, &adc_value);
    Printf("ADC2 ADC_RSEQ_7  PE15 value is %d\r\n", adc_value);
    ADCValue.inValue[2] = adc_value;
    delay_ms(500);

    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC, ADC_RSEQ_8) == RESET)
    {
    }
    ADC_GetSeqResult(ADC2, ADC_RSEQ_8, &adc_value);
    Printf("ADC2 ADC_RSEQ_8  PB10 value is %d\r\n", adc_value);
    ADCValue.inValue[3] = adc_value;
    delay_ms(500);
#endif

    return 0;
}

/**
 * @brief Print all ADC analog values
 * @param adcData - Pointer to getADCValue structure
 * @return 0 on success, -1 on failure
 */
uint8_t PrintAllADCValues()
{
    // if (adcData == NULL)
    // {
    //     Printf("Error: ADC data pointer is NULL!\r\n");
    //     return -1;
    // }

    // Print 16-channel output voltage analog values
    Printf("===== 16-channel Output Voltage Analog Values =====\r\n");
    Printf("Channel 0 (PA4): %d\r\n", ADCValue.outValue[0]);
    Printf("Channel 1 (PA5): %d\r\n", ADCValue.outValue[1]);
    Printf("Channel 2 (PA6): %d\r\n", ADCValue.outValue[2]);
    Printf("Channel 3 (PA7): %d\r\n", ADCValue.outValue[3]);
    Printf("Channel 4 (PC4): %d\r\n", ADCValue.outValue[4]);
    Printf("Channel 5 (PC5): %d\r\n", ADCValue.outValue[5]);
    Printf("Channel 6 (PB0): %d\r\n", ADCValue.outValue[6]);
    Printf("Channel 7 (PB1): %d\r\n", ADCValue.outValue[7]);
    Printf("Channel 8 (PB2): %d\r\n", ADCValue.outValue[8]);
    Printf("Channel 9 (PF11): %d\r\n", ADCValue.outValue[9]);
    Printf("Channel 10 (PF12): %d\r\n", ADCValue.outValue[10]);
    Printf("Channel 11 (PF13): %d\r\n", ADCValue.outValue[11]);
    Printf("Channel 12 (PF14): %d\r\n", ADCValue.outValue[12]);
    Printf("Channel 13 (PF15): %d\r\n", ADCValue.outValue[13]);
    Printf("Channel 14 (PG0): %d\r\n", ADCValue.outValue[14]);
    Printf("Channel 15 (PG1): %d\r\n", ADCValue.outValue[15]);

    // Print 4-channel input voltage analog values
    Printf("===== 4-channel Input Voltage Analog Values =====\r\n");
    Printf("Internal Channel 0 (PE7): %d\r\n", ADCValue.inValue[0]);
    Printf("Internal Channel 1 (PE14): %d\r\n", ADCValue.inValue[1]);
    Printf("Internal Channel 2 (PE15): %d\r\n", ADCValue.inValue[2]);
    Printf("Internal Channel 3 (PB10): %d\r\n", ADCValue.inValue[3]);

    return 0;
}