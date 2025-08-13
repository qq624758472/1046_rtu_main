#include "canfd.h"
#include "myprintf.h"
#include "delay.h"

extern uint8_t Canfd0rx_flags;
extern uint32_t Canfd0rx_bytes;
extern uint8_t Canfd1rx_flags;
extern uint32_t Canfd1rx_bytes;
extern uint8_t Canfd2rx_flags;
extern uint32_t Canfd2rx_bytes;

extern uint8_t Canfd3rx_flags;
extern uint32_t Canfd3rx_bytes;
extern uint8_t Receive_data1[64];

extern uint8_t canfd_sel;

void User_CANFD0_Init()
{

    CANFD0_CLK_ENABLE();
    GPIOD_CLK_ENABLE();
    GPIOC_CLK_ENABLE();
   
    GPIO_InitTypeDef  GPIO_InitStructure;
    CANFD_InitTypeDef CANFD_InitStructure;
    PLIC_InitTypeDef  PLIC_InitStructure;

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_CAN0_M3);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN0_M3);

    /* GPIO Configure */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_IType = GPIO_IPU;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
#ifdef DEBUG 
    CANFD0_RESET();
    delay_ms(200);
    CANFD0_SET();
#endif
    
    /* Initializes the CANFD0 */
    /* Arbitration Phase (Nominal) Baud Rate 500KHz */
    /* Data Phase Baud Rate 2MHz */
    /* 77.5% is 4,30,9；75% is 4,29,10 */
    CANFD_StructInit(&CANFD_InitStructure);
    CANFD_InitStructure.CANFD_SRR = CANFD_SRR_RESET;
    CANFD_InitStructure.CANFD_APBRPR = CANFD_APBRPR_4tp;
    CANFD_InitStructure.CANFD_APBTR_APTS1 = CANFD_APBTR_TS1_30tp;//30  29
    CANFD_InitStructure.CANFD_APBTR_APTS2 = CANFD_APBTR_TS2_9tp;
    CANFD_InitStructure.CANFD_APBTR_APSJW = CANFD_APBTR_SJW_2tp;

     if(canfd_sel)
    {
      //canfd_brs
       //5M      
      Printf("The CANFD is 5M.\r\n");
      CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_4tp;
      CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_2tp;
      CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_1tp;
      CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
      CANFD_Init(CANFD0, &CANFD_InitStructure);      
      /*
      //5M
      CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_1tp;
      CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_13tp;
      CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_2tp;
      CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
      CANFD_Init(CANFD0, &CANFD_InitStructure);    
      */
      /*
      Printf("The CANFD is 2M.\r\n");
      CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_4tp;
      CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_7tp;
      CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_2tp;
      CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
      CANFD_Init(CANFD0, &CANFD_InitStructure);  
      */  
    }
    else
    {
      //canfd
      Printf("The CANFD is 500K.\r\n");
      CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_4tp;
      CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_30tp;
      CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_9tp;
      CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
      CANFD_Init(CANFD0, &CANFD_InitStructure);
    }   
    
    /* CANFD receive filter configure */
    // CANFD_FilterInit(CANFD0, TB0, 0xFFE00000, 0x28E00000);
    // CANFD_FilterInit(CANFD0, TB1, 0xFFE00000, 0x4B000000);
    // CANFD_FilterInit(CANFD0, TB2, 0xFFE00000, 0x6D200000);
    
        CANFD_FilterInit(CANFD0,TB0,
                     ((0xffe00000)|(((0xff << 13)<<1)&0x0007fffe)|0x00080000),
                     /* 滤ID = 0x00， 目的ID = 0x17 */                     
                     ((((0x17 << 13)<<3)&0xffe00000)|(((0x17 << 13)<<1)&0x0007fffe))|0x00080000
                       );    
    CANFD_FilterInit(CANFD0,TB1,
                     ((0xffe00000)|(((0xff << 13)<<1)&0x0007fffe)|0x00080000),
                     /* 滤ID = 0x00， 目的ID = 0x17 */                     
                     ((((0x17 << 13)<<3)&0xffe00000)|(((0x17 << 13)<<1)&0x0007fffe))|0x00080000
                       );       
    
    //CANFD_ReceiveALL(CANFD0, ENABLE);
    

    CANFD_AutoBusOffRecoConfig(CANFD0,ENABLE);
    CANFD_AutoRetransConfig(CANFD0,ENABLE);
    /* Enable new message received interrupt */
    CANFD_ITConfig(CANFD0, CANFD_IT_ERXOK, ENABLE);
    /* CANFD Enable */
    CANFD_Enable(CANFD0);

    PLIC_StructInit(&PLIC_InitStructure);

    /* Configer the CANFD0 interrupt */
    PLIC_InitStructure.PLIC_IRQChannel = CANFD0_IRQn;
    PLIC_InitStructure.PLIC_IRQPriority = 1;
    PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
    PLIC_Init(&PLIC_InitStructure);
    CANFD_ClearITPendingBit(CANFD0, CANFD_CLEAR_ALL);
}


/*
 * Function:        CANFD1_Config
 * Description:     Configure CANFD1.
 * Param:           None.                 
 * Return:          None.
 */
void User_CANFD1_Init()
{
    CANFD1_CLK_ENABLE();
    GPIOD_CLK_ENABLE();
   
    GPIO_InitTypeDef  GPIO_InitStructure;
    CANFD_InitTypeDef CANFD_InitStructure;
    PLIC_InitTypeDef  PLIC_InitStructure;

	/* Set GPIO multiplex mapping */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_CAN1);

	/* GPIO Configure */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
	GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_IType = GPIO_IPU;
	GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
    
#ifdef DEBUG 
    CANFD1_RESET();
    delay_ms(200);
    CANFD1_SET();
#endif
    
	/* Initializes the CANFD1 */
	/* Arbitration Phase (Nominal) Baud Rate 500KHz */
	/* Data Phase Baud Rate 2MHz */
        /* 77.5% is 4,30,9；75% is 4,29,10 */
	CANFD_StructInit(&CANFD_InitStructure);
	CANFD_InitStructure.CANFD_SRR = CANFD_SRR_RESET;
	CANFD_InitStructure.CANFD_APBRPR = CANFD_APBRPR_4tp;
	CANFD_InitStructure.CANFD_APBTR_APTS1 = CANFD_APBTR_TS1_30tp;
	CANFD_InitStructure.CANFD_APBTR_APTS2 = CANFD_APBTR_TS2_9tp;
	CANFD_InitStructure.CANFD_APBTR_APSJW = CANFD_APBTR_SJW_2tp;

        if(canfd_sel)    
        {
          
          CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_4tp;
          CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_2tp;
          CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_1tp;
          CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
          CANFD_Init(CANFD1, &CANFD_InitStructure);  
          
          /*
          CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_4tp;
          CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_7tp;
          CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_2tp;
          CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
          CANFD_Init(CANFD1, &CANFD_InitStructure); 
          */
        }
        else
        {
          CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_4tp;
          CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_30tp;
          CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_9tp;
          CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
          CANFD_Init(CANFD1, &CANFD_InitStructure);          
        }

        
	/* CANFD receive filter configure */
	// CANFD_FilterInit(CANFD1, TB0, 0xFFE00000, 0x28E00000);
	// CANFD_FilterInit(CANFD1, TB1, 0xFFE00000, 0x4B000000);
	// CANFD_FilterInit(CANFD1, TB2, 0xFFE00000, 0x6D200000);

    CANFD_FilterInit(CANFD1,TB0,
                     ((0xffe00000)|(((0xff << 13)<<1)&0x0007fffe)|0x00080000),
                     /* 滤ID = 0x00， 目的ID = 0x17 */                     
                     ((((0x17 << 13)<<3)&0xffe00000)|(((0x17 << 13)<<1)&0x0007fffe))|0x00080000
                       );    
    CANFD_FilterInit(CANFD1,TB1,
                     ((0xffe00000)|(((0xff << 13)<<1)&0x0007fffe)|0x00080000),
                     /* 滤ID = 0x00， 目的ID = 0x17 */                     
                     ((((0x17 << 13)<<3)&0xffe00000)|(((0x17 << 13)<<1)&0x0007fffe))|0x00080000
                       );        
        
    //CANFD_ReceiveALL(CANFD1, ENABLE);

    CANFD_AutoBusOffRecoConfig(CANFD1,ENABLE);
    CANFD_AutoRetransConfig(CANFD1,ENABLE);
    /* Enable new message received interrupt */
	CANFD_ITConfig(CANFD1, CANFD_IT_ERXOK, ENABLE);
	/* CANFD Enable */
	CANFD_Enable(CANFD1);
    
    PLIC_StructInit(&PLIC_InitStructure);

	/* Configer the CANFD1 interrupt */
	PLIC_InitStructure.PLIC_IRQChannel = CANFD1_IRQn;
	PLIC_InitStructure.PLIC_IRQPriority = 2;
	PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
	PLIC_Init(&PLIC_InitStructure);
    CANFD_ClearITPendingBit(CANFD1, CANFD_CLEAR_ALL);
}

void CANFD1_Frame_Init()
{
    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;
    
    /* Set the setting ID and setting mode */
    if(canfd_sel)
    {
      CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;        
    }
    else
    {
      CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;      
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = 0x147;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_64B;
    CANFD_FrameInit(CANFD1, TB1, &CANFD_TXFrameStruct);
    
    
    if(canfd_sel)
    {
      CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;        
    }
    else
    {
      CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;      
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = 0x147;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_32B;
    CANFD_FrameInit(CANFD1, TB0, &CANFD_TXFrameStruct);

}

void CANFD1_Frame_Config(uint16_t CANFD_Frame_ID, uint8_t num)
{
    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;
    
    /* Set the setting ID and setting mode */
    CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = CANFD_Frame_ID;
    CANFD_TXFrameStruct.CANFD_TX_DLC = num;
    CANFD_FrameInit(CANFD1, TB1, &CANFD_TXFrameStruct);

}

void CANFD0_Frame_Init()
{
    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;
    
    /* Set the setting ID and setting mode */
    if(canfd_sel)
    {
      CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD_BRS;      
      Printf("The CANFD is CANFD_BRS.\r\n");
    }
    else
    {
      CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;    
      Printf("The CANFD is CANFD.\r\n");
    }
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = 0x147;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_64B;
    CANFD_FrameInit(CANFD0, TB1, &CANFD_TXFrameStruct);
    
    CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = 0x147;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_32B;
    CANFD_FrameInit(CANFD0, TB0, &CANFD_TXFrameStruct);    

}



/*
 * Function:        CANFD1_IRQ_Handler
 * Description:     CANFD1 interrupt handler function.
 * Param:           None.                 
 * Return:          None.
 */
void CANFD1_IRQ_Handler()
{
	if(CANFD_GetITStatus(CANFD1, CANFD_FLAG_RXOK) != RESET)
	{
            /* get the receive data */
                  
            Canfd1rx_flags = 1;
            /* Clear the interrupt pending bits */
            CANFD_ClearITPendingBit(CANFD1, CANFD_CLEAR_RXOK);
	}
}

void CANFD0_IRQ_Handler()
{
	if(CANFD_GetITStatus(CANFD0, CANFD_FLAG_RXOK) != RESET)
	{
            /* get the receive data */
                  
            Canfd0rx_flags = 1;
            /* Clear the interrupt pending bits */
            CANFD_ClearITPendingBit(CANFD0, CANFD_CLEAR_RXOK);
	}
}

/*
 * Function:        CANFD1_Config
 * Description:     Configure CANFD1.
 * Param:           None.                 
 * Return:          None.
 */
void User_CANFD3_Init()
{
    CANFD3_CLK_ENABLE();
    GPIOC_CLK_ENABLE();
   
    GPIO_InitTypeDef  GPIO_InitStructure;
    CANFD_InitTypeDef CANFD_InitStructure;
    PLIC_InitTypeDef  PLIC_InitStructure;

	/* Set GPIO multiplex mapping */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_CAN3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_CAN3);

	/* GPIO Configure */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
	GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_IType = GPIO_IPU;
	GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
#ifdef DEBUG 
    CANFD3_RESET();
    CANFD3_SET();
#endif
    
	/* Initializes the CANFD1 */
	/* Arbitration Phase (Nominal) Baud Rate 500KHz */
	/* Data Phase Baud Rate 2MHz */
	CANFD_StructInit(&CANFD_InitStructure);
	CANFD_InitStructure.CANFD_SRR = CANFD_SRR_RESET;
	CANFD_InitStructure.CANFD_APBRPR = CANFD_APBRPR_4tp;
	CANFD_InitStructure.CANFD_APBTR_APTS1 = CANFD_APBTR_TS1_30tp;
	CANFD_InitStructure.CANFD_APBTR_APTS2 = CANFD_APBTR_TS2_9tp;
	CANFD_InitStructure.CANFD_APBTR_APSJW = CANFD_APBTR_SJW_2tp;
    
	CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_4tp;
	CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_30tp;
	CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_9tp;
	CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
	CANFD_Init(CANFD3, &CANFD_InitStructure);
        
	/* CANFD receive filter configure */
	CANFD_FilterInit(CANFD3, TB0, 0xFFE00000, 0x28E00000);
	CANFD_FilterInit(CANFD3, TB1, 0xFFE00000, 0x4B000000);
	CANFD_FilterInit(CANFD3, TB2, 0xFFE00000, 0x6D200000);

    CANFD_AutoRetransConfig(CANFD3,ENABLE);
    /* Enable new message received interrupt */
	CANFD_ITConfig(CANFD3, CANFD_IT_ERXOK, ENABLE);
	/* CANFD Enable */
	CANFD_Enable(CANFD3);
    
    PLIC_StructInit(&PLIC_InitStructure);

	/* Configer the CANFD1 interrupt */
	PLIC_InitStructure.PLIC_IRQChannel = CANFD1_IRQn;
	PLIC_InitStructure.PLIC_IRQPriority = 2;
	PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
	PLIC_Init(&PLIC_InitStructure);
    CANFD_ClearITPendingBit(CANFD3, CANFD_CLEAR_ALL);
}

void CANFD3_Frame_Init()
{
    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;
    
    /* Set the setting ID and setting mode */
    CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = 0x147;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_8B;
    CANFD_FrameInit(CANFD3, TB1, &CANFD_TXFrameStruct);

}

/*
 * Function:        CANFD2_Config
 * Description:     Configure CANFD1.
 * Param:           None.                 
 * Return:          None.
 */
void User_CANFD2_Init()
{
    CANFD3_CLK_ENABLE();
    GPIOC_CLK_ENABLE();
   
    GPIO_InitTypeDef  GPIO_InitStructure;
    CANFD_InitTypeDef CANFD_InitStructure;
    PLIC_InitTypeDef  PLIC_InitStructure;

    /* Set GPIO multiplex mapping */
    GPIO_PinAFConfig(GPIOH, GPIO_PinSource6, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOH, GPIO_PinSource7, GPIO_AF_CAN2);

    /* GPIO Configure */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;

    GPIO_Init(GPIOH, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_IType = GPIO_IPU;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    GPIO_Init(GPIOH, &GPIO_InitStructure);
    
#ifdef DEBUG 
    CANFD2_RESET();
    CANFD2_SET();
#endif
    
    /* Initializes the CANFD1 */
    /* Arbitration Phase (Nominal) Baud Rate 500KHz */
    /* Data Phase Baud Rate 2MHz */
    CANFD_StructInit(&CANFD_InitStructure);
    CANFD_InitStructure.CANFD_SRR = CANFD_SRR_RESET;
    CANFD_InitStructure.CANFD_APBRPR = CANFD_APBRPR_4tp;
    CANFD_InitStructure.CANFD_APBTR_APTS1 = CANFD_APBTR_TS1_30tp;
    CANFD_InitStructure.CANFD_APBTR_APTS2 = CANFD_APBTR_TS2_9tp;
    CANFD_InitStructure.CANFD_APBTR_APSJW = CANFD_APBTR_SJW_2tp;

    CANFD_InitStructure.CANFD_DPBRPR = CANFD_DPBRPR_4tp;
    CANFD_InitStructure.CANFD_DPBTR_DPTS1 = CANFD_DPBTR_TS1_30tp;
    CANFD_InitStructure.CANFD_DPBTR_DPTS2 = CANFD_DPBTR_TS2_9tp;
    CANFD_InitStructure.CANFD_DPBTR_DPSJW = CANFD_DPBTR_SJW_1tp;
    CANFD_Init(CANFD2, &CANFD_InitStructure);
    
    /* CANFD receive filter configure */
    CANFD_FilterInit(CANFD2, TB0, 0xFFE00000, 0x28E00000);
    CANFD_FilterInit(CANFD2, TB1, 0xFFE00000, 0x4B000000);
    CANFD_FilterInit(CANFD2, TB2, 0xFFE00000, 0x6D200000);

    CANFD_AutoRetransConfig(CANFD3,ENABLE);
    /* Enable new message received interrupt */
    CANFD_ITConfig(CANFD2, CANFD_IT_ERXOK, ENABLE);
    /* CANFD Enable */
    CANFD_Enable(CANFD2);
    
    PLIC_StructInit(&PLIC_InitStructure);

    /* Configer the CANFD1 interrupt */
    PLIC_InitStructure.PLIC_IRQChannel = CANFD2_IRQn;
    PLIC_InitStructure.PLIC_IRQPriority = 2;
    PLIC_InitStructure.PLIC_IRQChannelCmd = ENABLE;
    PLIC_Init(&PLIC_InitStructure);
    CANFD_ClearITPendingBit(CANFD2, CANFD_CLEAR_ALL);
}
void CANFD2_Frame_Init()
{
    CANFD_TXFrameTypeDef CANFD_TXFrameStruct;
    
    /* Set the setting ID and setting mode */
    CANFD_TXFrameStruct.CANFD_TX_PROTOCOL = CANFD;
    CANFD_TXFrameStruct.CANFD_TX_FORMAT = EXTENDED;
    CANFD_TXFrameStruct.CANFD_TX_TYPE = DATA;
    CANFD_TXFrameStruct.CANFD_Frame_ID = 0x147;
    CANFD_TXFrameStruct.CANFD_TX_DLC = CANFD_DLC_8B;
    CANFD_FrameInit(CANFD2, TB1, &CANFD_TXFrameStruct);

}
/*
 * Function:        CANFD1_IRQ_Handler
 * Description:     CANFD1 interrupt handler function.
 * Param:           None.                 
 * Return:          None.
 */
void CANFD3_IRQ_Handler()
{
	if(CANFD_GetITStatus(CANFD3, CANFD_FLAG_RXOK) != RESET)
	{
        /* get the receive data */
		
		Canfd3rx_flags = 1;
		/* Clear the interrupt pending bits */
		CANFD_ClearITPendingBit(CANFD3, CANFD_CLEAR_RXOK);
	}
}

void CANFD2_IRQ_Handler()
{
	if(CANFD_GetITStatus(CANFD2, CANFD_FLAG_RXOK) != RESET)
	{
        /* get the receive data */
		
		Canfd2rx_flags = 1;
		/* Clear the interrupt pending bits */
		CANFD_ClearITPendingBit(CANFD2, CANFD_CLEAR_RXOK);
	}
}


void User_canfd_enable()
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    GPIOG_CLK_ENABLE();
    GPIOC_CLK_ENABLE();
   // GPIOH_CLK_ENABLE();
   
    /* GPIOB Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType     = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    
    GPIO_Init(GPIOG, &GPIO_InitStructure);  
    
    /* GPIOB Configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType     = GPIO_Out_PP;
    GPIO_InitStructure.GPIO_OStrength = GPIO_OStrength_9mA;
    
    GPIO_Init(GPIOH, &GPIO_InitStructure);
    
    
    GPIO_WriteBits(GPIOG, GPIO_Pin_4, GPIO_OCtrl_Vol);
    GPIO_WriteBits(GPIOH, GPIO_Pin_8, GPIO_OCtrl_Vol);

}


