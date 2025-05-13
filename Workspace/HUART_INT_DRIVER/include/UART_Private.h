#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

#include "STD_TYPES.h"

#define USART_USART1_BASE_ADDR              0x40011000UL
#define USART_USART2_BASE_ADDR              0x40004400UL
#define USART_USART6_BASE_ADDR              0x40011400UL

#define USART_DR_MASK                       0xFFFFFE00UL
#define USART_TXE_MASK                      0x00000080UL
#define USART_TC_MASK                       0x00000040UL
#define USART_RXNE_MASK                     0x00000020UL

#define USART_NO_OF_USARTS                  3
#define USART_NO_OF_EVENTS                  2

#define USART_WORD_LENGTH_VRF_MASK          0xFFFFEFFFUL
#define USART_WORD_LENGTH_MASK              0xFFFFEFFFUL          

#define USART_CLK_TYPE_VRF_MASK             0xFFFFF7FFUL
#define USART_CLK_TYPE_MASK                 0xFFFFF7FFUL  

#define USART_MODE_VRF_MASK                 0xFFFFFFF3UL
#define USART_MODE_MASK                     0xFFFFFFF3UL

#define USART_PARITY_MODE_VRF_MASK          0xFFFFF9FFUL
#define USART_PARITY_MODE_MASK              0xFFFFF9FFUL

#define USART_STOP_BIT_MASK                 0xFFFCFFFUL

#define USART_TC_INT_MASK                   0x00000040UL
#define USART_TXE_INT_MASK                  0x00000080UL
#define USART_RXNE_INT_MASK                 0x00000020UL

#define USART_EN_MASK                       0x00002000UL

#define USART_BRR_MASK                      0xFFFF0000UL
#define HIGH 1
#define HIGH 0

typedef struct{
    volatile uint32_t SR;      
    volatile uint32_t DR; 
    volatile uint32_t BRR; 
    volatile uint32_t CR1; 
    volatile uint32_t CR2; 
    volatile uint32_t CR3; 
    volatile uint32_t GTPR; 
}Usart_stRegs_t;

static Usart_stRegs_t* Usart_arrUsartBases[USART_NO_OF_USARTS] = {
    (Usart_stRegs_t*)USART_USART1_BASE_ADDR,
    (Usart_stRegs_t*)USART_USART2_BASE_ADDR,
    (Usart_stRegs_t*)USART_USART6_BASE_ADDR
};

typedef enum{
    Usart_enu_OK,
    Usart_enu_INVALID_USART,
    Usart_enu_TX_BUSY,
    Usart_enu_RX_Not_RDY,
    Usart_enu_INVALID_CLK_TYPE,
    Usart_enu_INVALID_WORD_LENGTH,
    Usart_enu_INVALID_PARITY_MODE,
    Usart_enu_INVALID_MODE,
    Usart_enu_INVALID_STOP_BIT,
    Usart_enu_INVALID_EVENT,
    Usart_enu_INVALID_INT,
    Usart_enu_INVALID_STATE,
    Usart_enu_NULL_POINTER,
    Usart_enu_NOK
}Usart_enuErrorStatus_t;

typedef enum{   
    Usart_enu_USART1,
    Usart_enu_USART2,
    Usart_enu_USART6    
}Usart_enuUsarts_t;

typedef enum{
    Usart_enu_async,
    Usart_enu_sync = 0x00000800
}Usart_enuClkType_t;

typedef enum{
    Usart_enu_word8,
    Usart_enu_word9 = 0x00001000
}Usart_enuWordLength_t;

typedef enum{
    Usart_enu_1StopBit,
    Usart_enu_05Stopbit,
    Usart_enu_2StopBit,
    Usart_enu_15StopBit
}Usart_enuStopBit_t;

typedef enum{
    Usart_enu_Tx = 0x00000008,
    Usart_enu_Rx = 0x00000004,
    Usart_enu_Tx_Rx = 0x0000000C
}Usart_enuMode_t;

typedef enum{
    Usart_enu_noParity,
    Usart_enu_evenParity=0x00000400,
    Usart_enu_oddParity=0x00000600
}Usart_enuParityMode_t;

typedef enum{
    Usart_enu_onTC,
    Usart_enu_onRXN
}Usart_enuEvent_t;

typedef void (*Usart_pCallBack)(void);

typedef struct{
    Usart_enuUsarts_t Usart;
    Usart_enuClkType_t clkType;
    Usart_enuWordLength_t WordLength;
    Usart_enuStopBit_t StopBit;
    Usart_enuMode_t Mode;
    Usart_enuParityMode_t ParityMode;
    uint32_t BaudRate;
}Usart_stCfg_t;

typedef enum{
    USART_enuTXE_INT,
    USART_enuTXC_INT,
    USART_enuRXNE_INT
}USART_enuInterrupts_t;

#endif /* UART_PRIVATE_H */

