/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ADC_H
#define PADC_H

/* Includes ------------------------------------------------------------------*/
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_adc.h"
#include "as32x601_plic.h"
//16路外部温度或电压采集
//4路内部温度或电压采集
typedef struct 
{
    uint16_t outValue[16];
    uint16_t inValue[4];
}getADCValue;

/* Exported define -----------------------------------------------------------*/
extern void User_ADC_All_Init();
/* Exported functions ------------------------------------------------------- */
extern uint8_t User_ADC_GetAllValue();

/**
 * @brief Print all ADC analog values
 * @param adcData - Pointer to getADCValue structure
 * @return 0 on success, -1 on failure
 */
extern uint8_t PrintAllADCValues();
extern void User_ADC_All_Init();
#endif

/*****END OF FILE*****/
