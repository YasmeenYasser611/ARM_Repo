
#include "HUART_INT.h"
#include"HUART_INT_cfg.h"

UartInt_Cfg_t UartInt_arrCfgs[UART_INT_NO_OF_UARTS] = {
    [UART_1] = {
        .TxPin = { .Port = GPIO_A, .Pin = PIN2 },
        .RxPin = { .Port = GPIO_A, .Pin = PIN3 },
        .baudRate = 9600,
        .Mode = Usart_enu_Tx_Rx,
        .ParityMode = Usart_enu_noParity,
        .StopBit = Usart_enu_1StopBit,
        .UART = Usart_enu_USART2,
        .wordLength = Usart_enu_word8,
    }
};