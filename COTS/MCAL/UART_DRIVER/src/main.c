#include "UART.h"
#include "STD_TYPES.h"


int main(void) {
    // USART Configuration
    Usart_stCfg_t uartConfig = {
        .Usart = Usart_enu_USART1,
        .clkType = Usart_enu_async,
        .WordLength = Usart_enu_word8,
        .StopBit = Usart_enu_1StopBit,
        .Mode = Usart_enu_Tx_Rx,
        .ParityMode = Usart_enu_noParity,
        .BaudRate = 9600
    };

    // Initialize USART1
    Usart_enuErrorStatus_t status = Usart_enuInit(&uartConfig);
    if (status != Usart_enu_OK) {
        // Handle error
        while (1);
    }

    // Send a test character 'A'
    Usart_enuSendByte(Usart_enu_USART1, 'A');

    // Wait for a byte to be received
    uint8_t receivedData;
    Usart_enuGetByte(Usart_enu_USART1, &receivedData);

    // Echo received byte back
    Usart_enuSendByte(Usart_enu_USART1, receivedData);

    // Check if transmission is complete
    uint8_t txComplete;
    USART_enuGetTXCVal(Usart_enu_USART1, &txComplete);
    if (txComplete == HIGH) 
    {

        // Indicate successful transmission 
    }

    while (1) {
        
    }

    return 0;
}
