#include "HUART_INT.h"
#include "HUART_INT_cfg.h"
#include "gpio.h"
#include "NVIC.h"



volatile uint8_t receivedData[UART_INT_MAX_BUFF_SIZE] = {0};

int main(void) {
  

    // Initialize UART Interrupt driver
    UsartInt_vInit();

    // Test sending a string
    const uint8_t testMessage[] = "Hello, UART Interrupt!\r\n";
    UartInt_enuSendString(UART_1, testMessage);

    // Test receiving buffer
    UartInt_enuReceiveBuffer(UART_1, receivedData, UART_INT_MAX_BUFF_SIZE);

    while (1) {
        

    return 0;
}
}