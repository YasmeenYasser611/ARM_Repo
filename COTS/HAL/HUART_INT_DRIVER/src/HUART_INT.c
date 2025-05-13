#include "HUART_INT.h"
#include "HUART_INT_cfg.h"
#include "NVIC.h"
#include "gpio_private.h"

#define UART_INT_NO_OF_USARTS           3
#define LOW 0

#define RCC_USART1              0x400000010ULL
#define RCC_USART2              0x200020000ULL
#define RCC_USART6              0x400000020ULL
void UartInt_vOnTC_CallBack(void);
void UartInt_vOnRXNE_CallBack(void);

static volatile uint8_t UartInt_arrTxBuffer[UART_INT_MAX_BUFF_SIZE] = {0};
static volatile uint8_t* volatile UartInt_pRxBuffer = NULL;

static volatile uint8_t UartInt_u8TxBufferSize = 0;
static volatile uint8_t UartInt_u8RxBufferSize = 0;

static volatile uint8_t UartInt_u8TxIndex = 0;
static volatile uint8_t UartInt_u8RxIndex = 0;

static volatile Usart_enuUsarts_t UartInt_enuUart = Usart_enu_USART2;

static const uint64_t UartInt_arrUsartClkMap[UART_INT_NO_OF_USARTS] = {
    RCC_USART1,
    RCC_USART2,
    RCC_USART6
};

static const IRQn_t UartInt_arrUsartIrqMap[UART_INT_NO_OF_USARTS] = {
    NVIC_enuUSART1,
    NVIC_enuUSART2,
    NVIC_enuUSART6
};

void UsartInt_vInit(void)
{
    uint8_t i = 0;
    IRQn_t Loc_enuIrqn = 0;
    
    for (i = 0; i < UART_INT_NO_OF_UARTS; i++) {
        Loc_enuIrqn = UartInt_arrUsartIrqMap[UartInt_arrCfgs[i].UART];

        /* Configure TX Pin as Alternate Function */
        GPIO_voidSetPinDirection(
            UartInt_arrCfgs[i].TxPin.Port,
            UartInt_arrCfgs[i].TxPin.Pin,
            AF_PP
        );

        /* Configure RX Pin as Alternate Function */
        GPIO_voidSetPinDirection(
            UartInt_arrCfgs[i].RxPin.Port,
            UartInt_arrCfgs[i].RxPin.Pin,
            AF_PP
        );

        Usart_stCfg_t Loc_stUsartCfg;
        Loc_stUsartCfg.Mode = UartInt_arrCfgs[i].Mode;
        Loc_stUsartCfg.BaudRate = UartInt_arrCfgs[i].baudRate;
        Loc_stUsartCfg.ParityMode = UartInt_arrCfgs[i].ParityMode;
        Loc_stUsartCfg.StopBit = UartInt_arrCfgs[i].StopBit;
        Loc_stUsartCfg.WordLength = UartInt_arrCfgs[i].wordLength;
        Loc_stUsartCfg.Usart = UartInt_arrCfgs[i].UART;
        Loc_stUsartCfg.clkType = Usart_enu_sync;

        Usart_enuInit(&Loc_stUsartCfg);
        USART_enuSetTCVal(UartInt_arrCfgs[i].UART, LOW);
        USART_enuSetRXNEval(UartInt_arrCfgs[i].UART, LOW);
        NVIC_enuClearPendingIRQn(Loc_enuIrqn);
        NVIC_enuEnableIRQn(Loc_enuIrqn);
    }
}


UartInt_enuErrorStatus_t UartInt_enuSendBuffer(uint8_t Copy_u8Uart,
uint8_t* Add_u8Buff,uint8_t Copy_u8BuffSize){
    
    UartInt_enuErrorStatus_t Loc_enuStatus = UartInt_enu_OK;
    uint8_t i=0;

    if(Add_u8Buff == NULL){
        Loc_enuStatus = UartInt_enu_NULL_POINTER;
    }
    else if(Copy_u8Uart > MAX_UART_INDEX){
        Loc_enuStatus = UartInt_enu_INVALID_UART;
    }
    else if(Copy_u8BuffSize > UART_INT_MAX_BUFF_SIZE){
        Loc_enuStatus = UartInt_enu_INVALID_BUFF_SIZE;
    }
    else{
        UartInt_u8TxBufferSize = Copy_u8BuffSize;
        UartInt_enuUart = UartInt_arrCfgs[Copy_u8Uart].UART;
        for(;i<Copy_u8BuffSize;i++){
            UartInt_arrTxBuffer[i] = Add_u8Buff[i];
        }
        Usart_enuSendByte(UartInt_enuUart,UartInt_arrTxBuffer[UartInt_u8TxIndex++]);
    }

    return Loc_enuStatus;
}


UartInt_enuErrorStatus_t UartInt_enuReceiveBuffer(uint8_t Copy_u8Uart,
uint8_t* Add_u8Buff,uint8_t Copy_u8BuffSize){

    UartInt_enuErrorStatus_t Loc_enuStatus = UartInt_enu_OK;
    uint8_t i=0;

    if(Add_u8Buff == NULL){
        Loc_enuStatus = UartInt_enu_NULL_POINTER;
    }
    else if(Copy_u8Uart > MAX_UART_INDEX){
        Loc_enuStatus = UartInt_enu_INVALID_UART;
    }
    else{
        UartInt_pRxBuffer = Add_u8Buff;
        UartInt_u8RxBufferSize = Add_u8Buff;
    }
}


UartInt_enuErrorStatus_t UartInt_enuSendString(uint8_t Copy_u8Uart,
const uint8_t* Add_u8Str){
    
    UartInt_enuErrorStatus_t Loc_enuStatus = UartInt_enu_OK;
    volatile uint8_t i = 0;

    for(;(Add_u8Str[i]) && (i < UART_INT_MAX_BUFF_SIZE);i++){}

    Loc_enuStatus = UartInt_enuSendBuffer(Copy_u8Uart,Add_u8Str,i);

    return Loc_enuStatus;
}



void UartInt_vOnTC_CallBack(void){
    if(UartInt_u8TxIndex < UartInt_u8TxBufferSize){
        Usart_enuSendByte(UartInt_enuUart,UartInt_arrTxBuffer[UartInt_u8TxIndex++]);
    }
    else{
        UartInt_u8TxIndex = 0;
    }
}

void UartInt_vOnRXNE_CallBack(void){
    if(UartInt_pRxBuffer == NULL){}
    else{
        if(UartInt_u8RxIndex < UartInt_u8RxBufferSize){
            Usart_enuGetByte(UartInt_enuUart,&UartInt_arrTxBuffer[UartInt_u8RxIndex++]);
        }
        else{
            UartInt_pRxBuffer = NULL;
            UartInt_u8RxIndex = 0;
        }
    }
}