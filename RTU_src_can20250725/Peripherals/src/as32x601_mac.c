/*
 *   __ _   _ __    ___  (_) | | (_)   ___
 *  / _` | | '_ \  / __| | | | | | |  / __|
 * | (_| | | | | | \__ \ | | | | | | | (__
 *  \__,_| |_| |_| |___/ |_| |_| |_|  \___|
 *
 * Copyright (C):  	Xiamen Guoke Anxin Technology Co., LTD
 * FileName:     	  as32x601_mac.c
 * Author:          ANSILIC APPLICATION GROUP
 * Version:         V1.0
 * Date:			      2024/08/19
 * History:
 *               <author>           <time>    <version >      <desc>
 *     ANSILIC APPLICATION GROUP  2024/08/19     1.0     build this module
 * Description:     This file contains all the functions prototypes for the MAC configuration.
 */

#include "as32x601_mac.h"
#include "as32x601_smu.h"
#include "string.h"
#include "as32x601_core.h"



#define MAC_MAX_PACKET_SIZE 1500

static uint32_t get_rx_packet_length( uint32_t descriptor0);
static  uint32_t adjust_tx_pkt_length(uint32_t tx_length);

/*
 * Function:        MAC_DeInit
 * Description:     De-initializes the MAC peripheral registers to their default reset values.
 * Param:           None.   
 * Return:          None.       
 */
void MAC_DeInit(void)
{
    /* Reset MAC */
    SMU->APB0CFGR &= ~SMU_APB0CFGR_MACRST;
    SMU->APB0CFGR |= SMU_APB0CFGR_MACRST;
}

/*
 * Function:        MAC_StructInit
 * Description:     Fills each MAC_InitStruct member with its default value.
 * Param:           MAC_InitStruct: pointer to a MAC_InitTypeDef structure which will be initialized.
 * Return:          None.       
 */
void MAC_StructInit(MAC_InitTypeDef * MAC_InitStruct)
{
    /* Check the parameters */
    MAC_InitStruct->MAC_AutoPollInterval = MAC_AutoPollInterval_Disable;
	MAC_InitStruct->MAC_DescriptorByteEndianMode = MAC_DescriptorEndianMode_Little;
	MAC_InitStruct->MAC_ProgrammablePulseLength = MAC_ProgrammablePulseLength_8;
	MAC_InitStruct->MAC_DataEndianMode = MAC_DataEndianMode_Little;
	MAC_InitStruct->MAC_DescriptorSkipLength = 0x00;
	MAC_InitStruct->MAC_BusArbitrationScheme = MAC_BuArbitrations_EqualPriority;
	MAC_InitStruct->MAC_ReceiveAll = MAC_ReceiveAll_Disable;
	MAC_InitStruct->MAC_TransmitThresholdMode = MAC_FIFOThreshold_10M;
	MAC_InitStruct->MAC_StoreandForward = MAC_StoreandForward_Disable;
	MAC_InitStruct->MAC_ThresholdControlBits = MAC_ThresholdControlBits_Disable;
	MAC_InitStruct->MAC_TransmitMode = MAC_TransmitMode_FullDuplex;
	MAC_InitStruct->MAC_PassAllMulticast = MAC_PassAllMulticasts_Enable;
	MAC_InitStruct->MAC_PromiscuousMode = MAC_PromiscuousMode_Enable;
	MAC_InitStruct->MAC_PassBadFrame = MAC_PassBadFrame_Disable;
	MAC_InitStruct->MAC_ContinuousMode = MAC_TimerWorkMode_OneShot;
	MAC_InitStruct->MAC_CycleSize=0;
	MAC_InitStruct->MAC_TimerValue = 0;
	MAC_InitStruct->MAC_TransmitPacketNumber=0;
	MAC_InitStruct->MAC_ReceiveTimer=0;
	MAC_InitStruct->MAC_ReceivePacketNumber=0;
	MAC_InitStruct->MAC_TransmitTimer=0;
}

/*
 * Function:        MAC_Init
 * Description:     MAC initial configuration.
 * Param:           MAC_InitStruct: pointer to a MAC_InitTypeDef structure which will be initialized.
 * Return:          None.       
 */
void MAC_Init(MAC_InitTypeDef* MAC_InitStruct)
{
	uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_VALID_MAC_AutoPollInterval(MAC_InitStruct->MAC_AutoPollInterval));
    assert_param(IS_VALID_MAC_DESCRIPTOR_BYTE_ENDIAN(MAC_InitStruct->MAC_DescriptorByteEndianMode));
    assert_param(IS_VALID_MAC_PROGRAMMABLE_PULSE_LENGTH(MAC_InitStruct->MAC_ProgrammablePulseLength));
    assert_param(IS_VALID_MAC_DATA_ENDIAN(MAC_InitStruct->MAC_DataEndianMode));
    assert_param(IS_VALID_MAC_DESCRIPTOR_SKIP_LENGTH(MAC_InitStruct->MAC_DescriptorSkipLength));
    assert_param(IS_VALID_MAC_BUS_ARBITRATION_SCHEME(MAC_InitStruct->MAC_BusArbitrationScheme));
    assert_param(IS_VALID_MAC_RECEIVE_ALL(MAC_InitStruct->MAC_ReceiveAll));
    assert_param(IS_VALID_MAC_FIFO_THRESHOLD_MODE(MAC_InitStruct->MAC_TransmitThresholdMode));
	assert_param(IS_VALID_MAC_THRESHOLD_CONTROL_BITS(MAC_InitStruct->MAC_ThresholdControlBits));
	assert_param(IS_VALID_MAC_STORE_AND_FORWARD(MAC_InitStruct->MAC_StoreandForward));
	assert_param(IS_VALID_MAC_TRANSMIT_MODE(MAC_InitStruct->MAC_TransmitMode));
	assert_param(IS_VALID_MAC_PASSALL_MULTICASTS(MAC_InitStruct->MAC_PassAllMulticast));
	assert_param(IS_VALID_MAC_PROMISCUOUS_MODE(MAC_InitStruct->MAC_PromiscuousMode));
	assert_param(IS_VALID_MAC_PASS_BAD_FRAME(MAC_InitStruct->MAC_PassBadFrame));
	assert_param(IS_VALID_MAC_TIMERWORK_MODE(MAC_InitStruct->MAC_ContinuousMode));
	assert_param(IS_VALID_MAC_TIMER_VALUE(MAC_InitStruct->MAC_TimerValue));

	/* Reset all internal triggers */
	MAC_SoftwareReset();
	/*Wait for reset to commplete */
	while((MAC->BUS_MODE & MAC_BUS_MODE_SWR) !=RESET)
	{}

	/* Configure MAC BUS MODE */
	/* Set Descriptor byte sort mode. */
	/* Set Transmit auto poll interval.*/
	/* Set Programmable pulse length */
	/* Set Data byte sort mode. */
	/* Set Descriptor skip length. */
	/* Set Bus arbitration scheme. */
	tmpreg = MAC->BUS_MODE;
	tmpreg &= ~((uint32_t)(MAC_BUS_MODE_BAR|MAC_BUS_MODE_DSL|
						   MAC_BUS_MODE_BLE|MAC_BUS_MODE_PBL|
						   MAC_BUS_MODE_TAP|MAC_BUS_MODE_DBO));
	tmpreg |=  (((uint32_t)MAC_InitStruct->MAC_DescriptorByteEndianMode << 20)	|
				((uint32_t)MAC_InitStruct->MAC_AutoPollInterval << 17)			|
				((uint32_t)MAC_InitStruct->MAC_ProgrammablePulseLength << 8)	|
				((uint32_t)MAC_InitStruct->MAC_DataEndianMode << 7)				|
				((uint32_t)MAC_InitStruct->MAC_DescriptorSkipLength << 2)		|
				((uint32_t)MAC_InitStruct->MAC_BusArbitrationScheme << 1));
	MAC->BUS_MODE = tmpreg;

	/* Configure General Timer and Interrupt Suppression Control register */
	/* Set Transmitting and receiving Period Indicates the period*/
	/* Set Transmit Timer*/
	/* Set Transmit Packet Number */
	/* Set Receive Timer */
	/* Set Receive Pack packet number */
	/* Set Timer Continuous mode */
	/* Set Timer value */
	tmpreg =MAC->TIMER_CTRL;
	tmpreg &= ~((uint32_t)(MAC_TIMER_CTRL_TIM|MAC_TIMER_CTRL_CON|
						   MAC_TIMER_CTRL_NRP|MAC_TIMER_CTRL_RT|
						   MAC_TIMER_CTRL_TT|MAC_TIMER_CTRL_CS)); 
	tmpreg |=  (((uint32_t)MAC_InitStruct->MAC_CycleSize << 31) |
				((uint32_t)MAC_InitStruct->MAC_TransmitTimer << 27) |
				((uint32_t)MAC_InitStruct->MAC_TransmitPacketNumber << 24) |
				((uint32_t)MAC_InitStruct->MAC_ReceiveTimer << 20) |
				((uint32_t)MAC_InitStruct->MAC_ReceivePacketNumber << 17) |
				((uint32_t)MAC_InitStruct->MAC_ContinuousMode << 16) |
				((uint32_t)MAC_InitStruct->MAC_TimerValue << 0));
	MAC->TIMER_CTRL = tmpreg;

	/* Configure Operation Mode register*/
	/* Set Transmitting and receiving Period Indicates the period*/
	/* Set Transmit Timer*/
	/* Set Transmit Packet Number */
	/* Set Receive Timer */
	/* Set Receive Pack packet number */
	/* Set Timer Continuous mode */
	/* Set Timer value */
	tmpreg = MAC->OPT_MODE;
	tmpreg &= ~((uint32_t)(MAC_OPT_MODE_PB|MAC_OPT_MODE_PR|
						   MAC_OPT_MODE_PM|MAC_OPT_MODE_FD|
						   MAC_OPT_MODE_TR|MAC_OPT_MODE_SF|
						   MAC_OPT_MODE_TTM|MAC_OPT_MODE_RA));
	tmpreg |= ((uint32_t)MAC_InitStruct->MAC_ReceiveAll << 30) |
				((uint32_t)MAC_InitStruct->MAC_TransmitThresholdMode << 22) |
				((uint32_t)MAC_InitStruct->MAC_StoreandForward << 21) |
				((uint32_t)MAC_InitStruct->MAC_ThresholdControlBits << 15) |
				((uint32_t)MAC_InitStruct->MAC_TransmitMode << 9) |
				((uint32_t)MAC_InitStruct->MAC_PassAllMulticast << 7) |
				((uint32_t)MAC_InitStruct->MAC_PromiscuousMode << 6) |
				((uint32_t)MAC_InitStruct->MAC_PassBadFrame << 3);
	MAC->OPT_MODE = tmpreg;
}

/*
 * Function:        MAC_SoftwareReset
 * Description:     Reset all internal triggers.
 * Param:           None.   
 * Return:          None.       
 */
void MAC_SoftwareReset(void)
{
	/* Reset all internal triggers */
	MAC->BUS_MODE |= MAC_BUS_MODE_SWR;
}

/*
 * Function:        MAC_ReceiveCmd
 * Description:     Start/stop receiving command.
 * Param:           NewState: new state of the MAC. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.        
 */
void MAC_ReceiveCmd(FunctionalState NewState)
{
	assert_param(IS_FunctionalState_STATE(NewState));
	/* Check the parameters */
	assert_param(IS_FunctionalState_STATE(NewState));

	if (NewState != DISABLE)
    {
		/* Enable Receive Command*/
		MAC->OPT_MODE |= MAC_OPT_MODE_SR;
    }
    else
    {
		/* Disable Receive Command*/
		MAC->OPT_MODE &= ~MAC_OPT_MODE_SR;
    }
}

/*
 * Function:        MAC_ReceiveCmd
 * Description:     Start/stop transimit command.
 * Param:           NewState: new state of the MAC. This parameter can be: ENABLE or DISABLE.     
 * Return:          None.        
 */
void MAC_TransmitCmd(FunctionalState NewState)
{
	/* Check the parameters */
    assert_param(IS_FunctionalState_STATE(NewState));

    if (NewState!= DISABLE)
    {
        /* Enable Transimit Command */
        MAC->OPT_MODE |= MAC_OPT_MODE_ST;
    }
    else
    {
		/* Disable Transimit Command */
        MAC->OPT_MODE &= ~MAC_OPT_MODE_ST;
    }
}

/*
 * Function:        MAC_ReceiveDescriptorAddress
 * Description:     Set Receive Descriptor Address.
 * Param:           Addr:The Receive Descriptor of Address .     
 * Return:          None.        
 */
void MAC_ReceiveDescriptorAddress(uint32_t Addr)
{
    /* Set Receive Descriptor Address */
    MAC->RDES_BASE_ADDR = Addr;
}

/*
 * Function:        MAC_TransmitDescriptorAddress
 * Description:     Set Transmit Descriptor Address.
 * Param:           Addr:The Transmit Descriptor of Address.     
 * Return:          None.
 */
void MAC_TransmitDescriptorAddress(uint32_t Addr)
{
	/* Set Transmit Descriptor Address */
    MAC->TDES_BASE_ADDR = Addr;
}

/*
 * Function:        MAC_GetProcessStatus
 * Description:     Gets the status of the MAC receiving and transmitting process.
 * Param:           Process: Specifies the status is receiving or transmitting process.
 * 					This parameter can be one of the following values:
 *                  MAC_PROCESS_RECEIVE: Receiving process
 * 					MAC_PROCESS_TRANSMIT: Transmitting process
 * Return:          The status of process.
 */
uint8_t MAC_GetProcessStatus(uint32_t Process)
{
	uint8_t status = 0;
	/* Check the parameters */
    assert_param(IS_MAC_PROCESS(Process));

    if (Process == MAC_PROCESS_RECEIVE)
    {
        /* Get Receive Process Status */
        status=(uint8_t)(MAC->STATUS & MAC_STATUS_RS);
    }
    else if (Process == MAC_PROCESS_TRANSMIT)
    {
        /* Get Transmit Process Status */
        status=(uint8_t)(MAC->STATUS & MAC_STATUS_TS);
    }
	return status;
}

/*
 * Function:        MAC_ITConfig
 * Description:     Enable or disable the specified MAC interrupts.
 * Param:           MAC_IT: Specifies the MAC interrupts sources to be enabled or disabled.
 *                  This parameter can be one or a combination of the following values:
 *                   MAC_IT_NIE: Normal Interrupt Summary
 *                   MAC_IT_AIE: Abnormal Interrupt Summary
 *                   MAC_IT_ERE: Early Receive Interrupt
 *                   MAC_IT_GTE: General Timer Interrupt
 *                   MAC_IT_ETE: Early Transmit Interrupt
 *                   MAC_IT_RSE: Receive Process Stopped
 *                   MAC_IT_RUE: Receive Buffer Unavailable
 *                   MAC_IT_RIE: Receive Interrupt
 *                   MAC_IT_UNE: Transmit Underflow
 *                   MAC_IT_TUE: Transmit Buffer Unavailable
 *                   MAC_IT_TSE: Transmit Process Stopped
 *                   MAC_IT_TIE: Transmit Interrupt
 * Param:           NewState: Specifies the new state of the MAC interrupts. 
 *                  This parameter can be: ENABLE or DISABLE.
 * Return:          None
 */
void MAC_ITConfig(uint32_t MAC_IT, FunctionalState NewState)
{
	/* Check the parameters */
    assert_param(IS_MAC_IT(MAC_IT));
	assert_param(IS_FunctionalState_STATE(NewState));
	if (NewState!= DISABLE)
    {
        /* Enable Transimit Command */
        MAC->INT_ENABLE |= MAC_IT;
    }
    else
    {
		/* Disable Transimit Command */
        MAC->INT_ENABLE &= ~MAC_IT;
    }
}

/*
 * Function:        MAC_GetFlagStatus
 * Description:     Checks whether the specified MAC flag is set or not.
 * Param:           MAC_FLAG: Specifies the flag to check.
 *                  This parameter can be one of the following values:
 *                   MAC_FLAG_NIS: Normal Interrupt Summary
 *                   MAC_FLAG_AIS: Abnormal Interrupt Summary
 *                   MAC_FLAG_ERI: Early Receive Interrupt
 *                   MAC_FLAG_GTE: General Timer Interrupt
 *                   MAC_FLAG_ETI: Early Transmit Interrupt
 *                   MAC_FLAG_RPS: Receive Process Stopped
 *                   MAC_FLAG_RU: Receive Buffer Unavailable
 *                   MAC_FLAG_RI: Receive Interrupt
 *                   MAC_FLAG_UNF: Transmit Underflow
 *                   MAC_FLAG_TU: Transmit Buffer Unavailable
 *                   MAC_FLAG_TPS: Transmit Process Stopped
 *                   MAC_FLAG_TI: Transmit Interrupt
 * Return:          The new state of MAC_FLAG (SET or RESET).
 */
FlagStatus MAC_GetFlagStatus(uint32_t MAC_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_MAC_FLAG(MAC_FLAG));

    if ((MAC->STATUS & MAC_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/*
 * Function:        MAC_ClearITStatus
 * Description:     Clear the interrput of flag.
 * Param:           MAC_IT: Specifies the flag to check.
 *                  This parameter can be one of the following values:
 *                   MAC_IT_NIS: Normal Interrupt Summary
 *                   MAC_IT_AIS: Abnormal Interrupt Summary
 *                   MAC_IT_ERI: Early Receive Interrupt
 *                   MAC_IT_GTE: General Timer Interrupt
 *                   MAC_IT_ETI: Early Transmit Interrupt
 *                   MAC_IT_RPS: Receive Process Stopped
 *                   MAC_IT_RU: Receive Buffer Unavailable
 *                   MAC_IT_RI: Receive Interrupt
 *                   MAC_IT_UNF: Transmit Underflow
 *                   MAC_IT_TU: Transmit Buffer Unavailable
 *                   MAC_IT_TPS: Transmit Process Stopped
 *                   MAC_IT_TI: Transmit Interrupt
 * Return:          None.
 */
void MAC_ClearITStatus(uint32_t MAC_IT)
{
    /* Check the parameters */
    assert_param(IS_MAC_ClearIT(MAC_IT));
	MAC->STATUS|=MAC_IT;
}

/*
 * Function:        MAC_TransmitPack
 * Description:     Transmits a network packet using the provided descriptor. 
 *                  Configures the descriptor and initiates transmission if available.
 * Param:           Frame_length: 
 *                  The length of the frame to be transmitted, adjusted internally.
 *                  P_tx_desc:Pointer to the transmit descriptor structure.
 * Return:          ErrorStatus
 *                  SUCCESS if the packet is scheduled for transmission,
 *                  ERROR if the descriptor is not available.
 */
ErrorStatus MAC_TransmitPack(uint32_t Frame_length,mac_tx_descriptor_t* P_tx_desc)
{
	if((P_tx_desc->descriptor_0&TDES0_OWN)==RESET)
	{
		/* Disable Transimit*/
		MAC_TransmitCmd(DISABLE);
		Frame_length=adjust_tx_pkt_length(Frame_length);
		/* Each buffer can hold a full frame, so they are always the first and last descriptor*/
		P_tx_desc->descriptor_1 = TDES1_TCH | TDES1_LS | TDES1_FS| (Frame_length << 0U);
		/* The descriptors are DMA owned */
		P_tx_desc->descriptor_0 = TDES0_OWN;

		ClearCache();
		// /* Transmit Poll Demand */
		MAC->TX_POLL =1;
		/* Enable Transimit*/
		MAC_TransmitCmd(ENABLE);
		return SUCCESS;
	}
	else
	{
		return ERROR;
	}
}
/*
 * Function:        MAC_ReceivePack
 * Description:     Receives a network packet using the provided receive descriptor.
 *                  Checks if the descriptor is available and valid, retrieves the packet data,
 *                  and resets the descriptor for future use.
 * Param:           rx_buffer:Pointer to the buffer where the received data will be stored. 
 *                  len:Pointer to a variable where the length of the received data will be stored.
 *                  P_rx_desc:Pointer to the receive descriptor structure.
 * Return:          ErrorStatus
 *                  SUCCESS if a packet is successfully received,
 *                  ERROR if the descriptor is still owned by the DMA or the buffer is NULL.
 */

ErrorStatus MAC_ReceivePack( uint8_t* rx_buffer, uint32_t *len,mac_rx_descriptor_t * P_rx_desc)
{
	uint8_t* ReadBuffer;
	if(((P_rx_desc->descriptor_0&RDES0_OWN)==RESET) && (rx_buffer != NULL))
	{
		/* Get the length of data and Buffer Address*/
		*len = get_rx_packet_length(P_rx_desc->descriptor_0);
		ReadBuffer = (uint8_t *)(P_rx_desc->buffer_1);

		/* Get Data*/
		memcpy(rx_buffer, ReadBuffer, *len);

		/* Set Receive descriptor*/
		P_rx_desc->descriptor_1 = RDES1_RCH | (uint32_t)MAC_MAX_PACKET_SIZE;
		P_rx_desc->descriptor_0 = RDES0_OWN|(3u<<8);
		ClearCache();

		MAC_ReceiveCmd(ENABLE);
	
		return SUCCESS;
	}
    else
    {
       	return ERROR;
    }
}
/*
 * Function:        adjust_tx_pkt_length
 * Description:     Adjusts the transmit packet length to ensure it does not exceed 
 *                  the maximum allowable size.
 * Param:           tx_length: The original length of the packet to be transmitted.
 * Return:          uint32_t
 *                  The adjusted packet length, either the original length or the maximum 
 *                  allowable size if the original length exceeds it.
 */

 static uint32_t adjust_tx_pkt_length(uint32_t tx_length)
{
    uint32_t adjusted_tx_pkt_length;

    if (tx_length > MAC_MAX_PACKET_SIZE)
    {
        adjusted_tx_pkt_length = MAC_MAX_PACKET_SIZE;
    }
    else
    {
        adjusted_tx_pkt_length = tx_length;
    }

    return adjusted_tx_pkt_length;
}

/*
 * Function:        get_rx_packet_length
 * Description:     Retrieves the length of the received packet from the descriptor,
 *                  stripping off the CRC if present.
 * Param:           descriptor0: The value of the descriptor's first word, which 
 * 					contains the packet length and status.
 * Return:          uint32_t
 *                  The length of the received packet, with CRC stripped.
 * 				  	Returns 0 if the descriptor is still owned by DMA.
 */
static uint32_t get_rx_packet_length( uint32_t descriptor0)
{
    uint32_t pckt_length;

    if ((descriptor0 & RDES0_OWN) != 0U)
    {
        /* Current descriptor is empty */
        pckt_length = 0U;
    }
    else
    {
        pckt_length = (descriptor0 >> RDES0_FL_OFFSET) & RDES0_FL_MASK;

        /* strip crc */
        if (pckt_length > 4U)
        {
            pckt_length -= 4U;
        }
        else
        {
            pckt_length = 0U;
        }
    }

    return pckt_length;
}

/*
 * Function:        MAC_MDIOClockCmd
 * Description:     Enable or Disable the MDIO Clock.
 * Param:			NewState: Specifies the new state of the MAC MDIO Clock.
 * Return:          None.
 */
void MAC_MDIOClockCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FunctionalState_STATE(NewState));
	if (NewState!= DISABLE)
    {
        /* Enable MDIO Clock */
        MAC->MDIO_CTRL0 |= MAC_MDIO_CTRL0_MDCE;
    }
    else
    {
		/* Disable MDIO Clock */
        MAC->MDIO_CTRL0 &= ~MAC_MDIO_CTRL0_MDCE;
    }
}


/*
 * Function:        MAC_SetPrescaler
 * Description:     Sets MAC MDC Prescaler value.
 * Param:           MAC_Prescaler: specifies the MAC Prescaler value.
 * Return:          None.       
 */
void MAC_SetPrescaler(uint16_t MAC_Prescaler)
{
	/* Sets MAC MDC Prescaler value. */
	MAC->MDIO_CTRL0 &= ~MAC_MDIO_CTRL0_MDC_DIV;
	MAC->MDIO_CTRL0 |= MAC_Prescaler;
}

/*
 * Function:        MAC_MDIOConfig
 * Description:     Writes data to a register of the specified external PHY.
 * Param:			PHY_ADDR: PHY address.
 * 					REG_ADDR: PHY register address.
 *                  Data: Data to be written
 * 					timeout:Timeout duration
 * Return:          ErrorStatus
 *                  SUCCESS if a packet is successfully received,
 *                  ERROR if the descriptor is still owned by the DMA or the buffer is NULL.
 */
ErrorStatus MAC_MDIOWriteData(uint32_t PHY_ADDR,uint32_t REG_ADDR,uint32_t Data,uint32_t timeout)
{
	uint32_t tmpreg=0;
	uint32_t flag=0;

	/* Check the parameters */
	assert_param(PHY_ADDR<=0x1F);
	assert_param(REG_ADDR<=1F);
	assert_param(Data<=0xFF);

	/* Configure the register of MDIO_CTRL1*/
	tmpreg=MAC->MDIO_CTRL1;
	tmpreg&=~((uint32_t)(MAC_MDIO_CTRL1_RDATA|MAC_MDIO_CTRL1_TURN|MAC_MDIO_CTRL1_START1|MAC_MDIO_CTRL1_START0|
						MAC_MDIO_CTRL1_PHY_ADDR|MAC_MDIO_CTRL1_RDWR|MAC_MDIO_CTRL1_REG_ADDR));
	tmpreg |=((uint32_t)( PHY_ADDR<<23 )|(uint32_t)( REG_ADDR<<18 )|(uint32_t)(Data<<0)|
						MAC_MDIO_CTRL1_START0|MAC_MDIO_CTRL1_RDWR_0|MAC_MDIO_CTRL1_TURN_1);
	MAC->MDIO_CTRL1=tmpreg;

	while(timeout--)
	{
		if((MAC->MDIO_CTRL1&MAC_MDIO_CTRL1_ACK)!=RESET)
		{
			flag=1;
			break;
		}
		
	}
	if(flag!=0)
	{
		
        return SUCCESS;
    }
	else
	{
		return ERROR;
	}
}

/*
 * Function:        MAC_MDIOReadData
 * Description:     Reads data from a register of the specified external PHY.
 * Param:           PHY_ADDR: PHY address.
 * 					REG_ADDR: PHY register address.
 * 					timeout:Timeout duration
 * Return:			Read data information.		
 */
int MAC_MDIOReadData(uint8_t PHY_ADDR, uint8_t REG_ADDR,uint32_t timeout)
{
	uint32_t tmpreg=0;
	uint32_t flag=0;
	uint32_t data=0;

	/* Check the parameters */
	assert_param(PHY_ADDR<=0x1F);
	assert_param(REG_ADDR<=0x1F);

	/* Configure the register of MDIO_CTRL1*/
	tmpreg=MAC->MDIO_CTRL1;
	tmpreg&=~((uint32_t)(MAC_MDIO_CTRL1_TURN|MAC_MDIO_CTRL1_START1|MAC_MDIO_CTRL1_START0|
						MAC_MDIO_CTRL1_PHY_ADDR|MAC_MDIO_CTRL1_RDWR|MAC_MDIO_CTRL1_REG_ADDR));
	tmpreg |=((uint32_t)( PHY_ADDR<<23 )|(uint32_t)( REG_ADDR<<18 )|
						MAC_MDIO_CTRL1_START0|MAC_MDIO_CTRL1_RDWR_1);
	MAC->MDIO_CTRL1=tmpreg;
	while(timeout--)
	{
		if((MAC->MDIO_CTRL1&MAC_MDIO_CTRL1_ACK)!=RESET)
		{
			flag=1;
			data=(int)(MAC->MDIO_CTRL1&MAC_MDIO_CTRL1_RDATA);
			break;
		}
	}
	
	if(flag!=0)
	{
		
        return data;
    }
	else
	{
		return -1;
	}
}



/*****END OF FILE*****/