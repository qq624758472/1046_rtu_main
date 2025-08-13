/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CANFD_H
#define CANFD_H

/* Includes ------------------------------------------------------------------*/
#include "as32x601.h"
#include "as32x601_gpio.h"
#include "as32x601_smu.h"
#include "as32x601_usart.h"
#include "as32x601_canfd.h"
#include "as32x601_plic.h"

/* Exported define -----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

extern void User_CANFD0_Init();
extern void CANFD0_Frame_Init();

extern void User_CANFD2_Init();
extern void CANFD2_Frame_Init();

extern void User_CANFD1_Init();
extern void CANFD1_Frame_Init();
extern void User_CANFD3_Init();
extern void CANFD3_Frame_Init();
extern void User_Uart_enable();

extern void User_canfd_enable();
extern uint32_t CANFD_GetReceiveData(CANFD_TypeDef* CANFDx, uint8_t* Data);
extern void CANFD1_Frame_Config(uint16_t CANFD_Frame_ID, uint8_t num);
#endif

/*****END OF FILE*****/
