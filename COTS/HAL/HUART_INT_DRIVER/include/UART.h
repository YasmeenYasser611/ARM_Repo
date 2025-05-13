#ifndef USART_H_
#define USART_H_

#include"UART_Private.h"
#include "STD_TYPES.h"




extern Usart_enuErrorStatus_t Usart_enuInit(Usart_stCfg_t* Add_stCfg);

extern Usart_enuErrorStatus_t Usart_enuRegisterCallBack(Usart_enuUsarts_t Copy_enuUsart,
Usart_pCallBack Add_pCB,Usart_enuEvent_t Copy_enuEvent);

extern Usart_enuErrorStatus_t Usart_enuSendByte(Usart_enuUsarts_t Copy_enuUsart,
uint8_t Copy_u8Byte);

extern Usart_enuErrorStatus_t  Usart_sendByteBlocking(Usart_enuUsarts_t Copy_enuUsart,
uint8_t Copy_u8Byte);

extern Usart_enuErrorStatus_t Usart_enuGetByte(Usart_enuUsarts_t Copy_enuUsart,
uint8_t* Add_u8Byte);

extern Usart_enuErrorStatus_t USART_enuEnableInt(Usart_enuUsarts_t Copy_enuUart,
USART_enuInterrupts_t Copy_enuInt);

extern Usart_enuErrorStatus_t USART_enuDisableInt(Usart_enuUsarts_t Copy_enuUart,
USART_enuInterrupts_t Copy_enuInt);

extern Usart_enuErrorStatus_t USART_enuGetTXCVal(Usart_enuUsarts_t Copy_enuUsart,
uint8_t* Add_u8State);

extern Usart_enuErrorStatus_t USART_enuGetTXEVal(Usart_enuUsarts_t Copy_enuUsart,
uint8_t* Add_u8State);

extern Usart_enuErrorStatus_t USART_enuGetRXNEval(Usart_enuUsarts_t Copy_enuUsart,
uint8_t* Add_u8State);

extern Usart_enuErrorStatus_t USART_enuSetTCVal(Usart_enuUsarts_t Copy_enuUsart,
uint8_t Add_u8State);

extern Usart_enuErrorStatus_t USART_enuSetRXNEval(Usart_enuUsarts_t Copy_enuUsart,
uint8_t Add_u8State);

#endif

