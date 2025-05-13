#ifndef RCC_H
#define RCC_H

#include"RCC_PRIVATE.h"
/*

1-Description:The RCC_ControlClock function is used to control the clock sources for a microcontroller's RCC (Reset and Clock Control) module. 
It can enable or disable different clock sources, including HSI (High-Speed Internal), HSE (High-Speed External), HSE Bypass, and PLL (Phase-Locked Loop).
The function also checks for readiness of the clock sources and handles timeout scenarios.
2-Arguments:
    1- uint8_t ClockSource: RCC_HSI , RCC_HSE , RCC_HSE_BYPASS , RCC_PLL .
    2-uint8_t Mode: RCC_ON , RCC_OFF .
3-Return Value:RCC_noErr,RCC_enuInvalidClockSource , RCC_enuInvalidMode , RCC_enuTimeout
*/
RCC_errStatus_t RCC_ControlClock(uint8_t ClockSource, uint8_t Mode);

/*
1-Description:The RCC_SelectSysCLK function is used to select the system clock source for a microcontroller's RCC (Reset and Clock Control) module. 
It allows switching between High-Speed Internal (HSI), High-Speed External (HSE), and Phase-Locked Loop (PLL) as the system clock source. 
The function ensures that the PLL is disabled if it is currently selected, and updates the configuration registers accordingly.
2-Arguments : RCC_HSI_SYSTEMCLK, RCC_HSE_SYSTEMCLK , RCC_PLL_SYSTEMCLK
3-Return Value : RCC_noErr , RCC_enuInvalidClockSource


*****note befote configur pll you chould use RCC_ControlClock(RCC_PLL, RCC_OFF);

*/
RCC_errStatus_t RCC_SelectSysCLK(uint8_t Copy_u8SysClockSource);

/*
1-Description:The RCC_enmCfgPLL function configures the Phase-Locked Loop (PLL) settings for a microcontroller's RCC (Reset and Clock Control) module. 
It performs various validations on the PLL configuration parameters, calculates the VCO (Voltage Controlled Oscillator) frequency based on the selected PLL source, and updates the PLL configuration registers. 
The function also ensures that the PLL is enabled and waits for it to stabilize.
2-Arguments:

    RCC_PLLCfg_t * RCC_PLLCfg: A pointer to a structure containing the PLL configuration parameters. The structure should define the following fields:
        uint8_t PLL_Src: The clock source for the PLL (e.g., HSI or HSE).
        uint8_t M_Prescaler: The division factor for the input clock (must be between 2 and 63).
        uint16_t N_Multiple: The multiplication factor for the VCO output (must be between 192 and 432).
        uint8_t P_Prescaler: The division factor for the PLL output (must be one of the values: 2, 4, 6, or 8).
        uint8_t Q_Prescaler: The division factor for the PLL output used for USB (must be between 2 and 15).

3-Return Value : RCC_noErr,RCC_errNULLPtr,RCC_errPLLON,Invalid_M_Prescaler,Invalid_N_Multiple , Invalid_P_Prescaler,Invalid_Q_Prescaler ,RCC_errPLLSrc ,RCC_enuTimeout
*/
RCC_errStatus_t RCC_enmCfgPLL(RCC_PLLCfg_t * RCC_PLLCfg);


/*

1-Description:The RCC_ControlPerClock function manages the clock for specific peripherals in a microcontroller's RCC (Reset and Clock Control) module. 
It allows enabling or disabling the clock for peripherals based on the specified bus and mode (normal or low-power). 
The function validates input parameters and modifies the appropriate control registers accordingly.
2-Arguments:
    uint64_t Bus_Peripheral_ID: An identifier that combines the bus ID and peripheral ID. ex:RCC_AHB1_GPIOA
    uint32_t Status: RCC_ON , RCC_OFF
    uint32_t Mode: RCC_NORMAL_MODE ,RCC_SLEEP_MODE
3-Return Value:RCC_noErr , RCC_enuInvalidPerId,RCC_enuInvalidBusId,RCC_enuInvalidMode ,RCC_enuInvalidStatus
*/
RCC_errStatus_t RCC_ControlPerClock(uint64_t Bus_Peripheral_ID, uint32_t Status, uint32_t Mode);

/*
RCC_errStatus_t RCC_enuEnableClock(uint8_t Copy_u8BusId, uint8_t Copy_u8PerId, uint8_t Copy_u8Mode);
RCC_errStatus_t RCC_enuDisableClock(uint8_t Copy_u8BusId, uint8_t Copy_u8PerId, uint8_t Copy_u8Mode);
*/

#endif