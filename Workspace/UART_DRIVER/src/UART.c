#include "UART.h"
#include"UART_Private.h"
#include"UART_cfg.h"

static Usart_pCallBack Usart_arrCallBacks[USART_NO_OF_USARTS][USART_NO_OF_EVENTS] = {0};

Usart_enuErrorStatus_t Usart_enuInit(Usart_stCfg_t* Add_stCfg){
    
    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Add_stCfg->Usart];
    uint32_t Loc_u32BusFreq = 0;
    uint16_t Loc_u16Div = 0;
    uint8_t Loc_u8frac = 0;
    uint32_t Loc_u32Remainder = 0;
    if(Add_stCfg == NULL){
        Loc_enuStatus = Usart_enu_NULL_POINTER;
    }
    else if(Add_stCfg->Usart>Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else if(Add_stCfg->clkType & USART_CLK_TYPE_VRF_MASK){
        Loc_enuStatus = Usart_enu_INVALID_CLK_TYPE;
    }
    else if(Add_stCfg->WordLength & USART_WORD_LENGTH_VRF_MASK){
        Loc_enuStatus = Usart_enu_INVALID_WORD_LENGTH;
    }
    else if(Add_stCfg->ParityMode & USART_PARITY_MODE_VRF_MASK){
        Loc_enuStatus = Usart_enu_INVALID_PARITY_MODE;
    }
    else if(Add_stCfg->Mode & USART_MODE_VRF_MASK){
        Loc_enuStatus = Usart_enu_INVALID_MODE;
    }
    else if(Add_stCfg->StopBit > Usart_enu_15StopBit){
        Loc_enuStatus = Usart_enu_INVALID_STOP_BIT;
    }
    else{
switch (Add_stCfg->Usart)
{
    case Usart_enu_USART1:
        Loc_u32BusFreq = USART1_BUS_CLOCK;
        break;
    case Usart_enu_USART2:
        Loc_u32BusFreq = USART2_BUS_CLOCK;
        break;
    case Usart_enu_USART6:
        Loc_u32BusFreq = USART6_BUS_CLOCK;
        break;
    default:
        break;
}

        USART->CR1 &= ~USART_EN_MASK;
        USART->CR2 = USART->CR2 & USART_CLK_TYPE_MASK | Add_stCfg->clkType;
        USART->CR1 = USART->CR1 & USART_MODE_MASK | Add_stCfg->Mode;
        USART->CR1 = USART->CR1 & USART_WORD_LENGTH_MASK | Add_stCfg->WordLength;
        USART->CR1 = USART->CR1 & USART_PARITY_MODE_MASK | Add_stCfg->ParityMode;
        USART->CR2 = USART->CR2 & USART_STOP_BIT_MASK | (Add_stCfg->StopBit << 12);
        Loc_u16Div = (Loc_u32BusFreq)/(16 * Add_stCfg->BaudRate);
        Loc_u8frac = ((Loc_u32BusFreq - Loc_u16Div *16)/Add_stCfg->BaudRate 
        + 0.5);  
        USART->BRR &= USART_BRR_MASK;
        USART->BRR |= Loc_u8frac;
        USART->BRR |= Loc_u16Div << 4; 
        USART->SR &= ~USART_TC_MASK;
        USART->SR &= ~USART_RXNE_MASK;
        USART->CR1 |= USART_EN_MASK;
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t Usart_enuRegisterCallBack(Usart_enuUsarts_t Copy_enuUsart,
Usart_pCallBack Add_pCB,Usart_enuEvent_t Copy_enuEvent){

    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;

    if(Add_pCB == NULL){
        Loc_enuStatus = Usart_enu_NULL_POINTER;
    }
    else if(Copy_enuUsart>Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else if(Copy_enuEvent>Usart_enu_onRXN){
        Loc_enuStatus = Usart_enu_INVALID_EVENT;
    }
    else{
        Usart_arrCallBacks[Copy_enuUsart][Copy_enuEvent] = Add_pCB;
    }

    return Loc_enuStatus;
}

Usart_enuErrorStatus_t Usart_enuSendByte(Usart_enuUsarts_t Copy_enuUsart,
uint8_t Copy_u8Byte){
    
    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];

    if(Copy_enuUsart>Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else if(!(USART->SR & USART_TXE_MASK)){
        Loc_enuStatus = Usart_enu_TX_BUSY;
    }
    else{
        USART->DR =  (uint16_t)Copy_u8Byte;      
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t Usart_sendByteBlocking(Usart_enuUsarts_t Copy_enuUsart,
uint8_t Copy_u8Byte){
    
    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];

    if(Copy_enuUsart>Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else{
        while(!(USART->SR & USART_TXE_MASK)){}
        USART->DR =  (uint16_t)Copy_u8Byte;      
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t Usart_enuGetByte(Usart_enuUsarts_t Copy_enuUsart,
uint8_t* Add_u8Byte){

    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];
    if(Add_u8Byte==NULL){
        Loc_enuStatus = Usart_enu_NULL_POINTER;
    }
    else if(Copy_enuUsart>Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else if(!(USART->SR & USART_RXNE_MASK)){
        Loc_enuStatus = Usart_enu_RX_Not_RDY;
    }
    else{
        *Add_u8Byte = (uint8_t)USART->DR;
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t USART_enuEnableInt(Usart_enuUsarts_t Copy_enuUart,
USART_enuInterrupts_t Copy_enuInt){

    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUart];

    if(Copy_enuUart > Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else{
        switch(Copy_enuInt){
            case USART_enuTXE_INT:
            USART->CR1 |= USART_TXE_INT_MASK;
            break;

            case USART_enuTXC_INT:
            USART->CR1 |= USART_TC_INT_MASK;
            break;

            case USART_enuRXNE_INT:
            USART->CR1 |= USART_RXNE_INT_MASK;
            break;

            default :
            Loc_enuStatus = Usart_enu_INVALID_INT;
            break;
        }
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t USART_enuDisableInt(Usart_enuUsarts_t Copy_enuUart,
USART_enuInterrupts_t Copy_enuInt){
   
    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUart];

    if(Copy_enuUart > Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else{
        switch(Copy_enuInt){
            case USART_enuTXE_INT:
            USART->CR1 &= ~USART_TXE_INT_MASK;
            break;

            case USART_enuTXC_INT:
            USART->CR1 &= ~USART_TC_INT_MASK;
            break;

            case USART_enuRXNE_INT:
            USART->CR1 &= ~USART_RXNE_INT_MASK;
            break;

            default :
            Loc_enuStatus = Usart_enu_INVALID_INT;
            break;
        }
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t USART_enuGetTXCVal(Usart_enuUsarts_t Copy_enuUsart,uint8_t* Add_u8State){
    
    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];
    
    if(Add_u8State == NULL){
        Loc_enuStatus = Usart_enu_NULL_POINTER;
    }
    else if(Copy_enuUsart > Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else{
        *Add_u8State = USART->SR & USART_TC_MASK != 0;
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t USART_enuGetTXEVal(Usart_enuUsarts_t Copy_enuUsart,uint8_t* Add_u8State){

    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];
    
    if(Add_u8State == NULL){
        Loc_enuStatus = Usart_enu_NULL_POINTER;
    }
    else if(Copy_enuUsart > Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else{
        *Add_u8State = USART->SR & USART_TXE_MASK != 0;
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t USART_enuGetRXNEval(Usart_enuUsarts_t Copy_enuUsart,uint8_t* Add_u8State){

    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];
    
    if(Add_u8State == NULL){
        Loc_enuStatus = Usart_enu_NULL_POINTER;
    }
    else if(Copy_enuUsart > Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else{
        *Add_u8State = USART->SR & USART_RXNE_MASK != 0;
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t USART_enuSetTCVal(Usart_enuUsarts_t Copy_enuUsart,uint8_t Add_u8State){

    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];

    if(Copy_enuUsart > Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else if(Add_u8State>HIGH){
        Loc_enuStatus = Usart_enu_INVALID_STATE;
    }
    else{
        USART->SR = (USART->SR & (~USART_TC_MASK)) | (Add_u8State << 6);
    }
    return Loc_enuStatus;
}

Usart_enuErrorStatus_t USART_enuSetRXNEval(Usart_enuUsarts_t Copy_enuUsart,uint8_t Add_u8State){

    Usart_enuErrorStatus_t Loc_enuStatus = Usart_enu_OK;
    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];

    if(Copy_enuUsart > Usart_enu_USART6){
        Loc_enuStatus = Usart_enu_INVALID_USART;
    }
    else if(Add_u8State>HIGH){
        Loc_enuStatus = Usart_enu_INVALID_STATE;
    }
    else{
        USART->SR = (USART->SR & (~USART_RXNE_MASK)) | (Add_u8State << 6);
    }
    return Loc_enuStatus;

}

static void inline USART_vInterrupts(Usart_enuUsarts_t Copy_enuUsart){

    Usart_stRegs_t* USART = (Usart_stRegs_t*)Usart_arrUsartBases[Copy_enuUsart];
    
    if(USART->SR&USART_TC_MASK){
        USART->SR &= ~USART_TC_MASK;
        if(Usart_arrCallBacks[Copy_enuUsart][Usart_enu_onTC]!=NULL){
            Usart_arrCallBacks[Copy_enuUsart][Usart_enu_onTC]();
        }
    }

    if(USART->SR&USART_RXNE_MASK){
        USART->SR &= ~USART_RXNE_MASK;
        if(Usart_arrCallBacks[Copy_enuUsart][Usart_enu_onRXN]!=NULL){
            Usart_arrCallBacks[Copy_enuUsart][Usart_enu_onRXN]();
        }
    }
}

void USART1_IRQHandler(void){ 
    USART_vInterrupts(Usart_enu_USART1);
}

void USART2_IRQHandler(void){
    USART_vInterrupts(Usart_enu_USART2);
}

void USART6_IRQHandler(void){
    USART_vInterrupts(Usart_enu_USART6);
}