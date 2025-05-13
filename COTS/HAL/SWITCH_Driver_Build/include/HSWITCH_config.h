#ifndef CONFIG_H_
#define CONFIG_H_

#include "STD_TYPES.h"
#include "gpio_private.h"

// Pin modes for switches
#define INPUT_FLOATING        (GPIO_MODE_INPUT | GPIO_NO_PUPD)  // Input mode with floating (no pull-up/down)
#define INPUT_PU              (GPIO_MODE_INPUT | GPIO_PULLUP)   // Input mode with pull-up
#define INPUT_PD              (GPIO_MODE_INPUT | GPIO_PULLDOWN) // Input mode with pull-down

// Clock definitions for GPIO ports
#define RCC_AHB1_GPIOA          ((uint64_t)0x0000000000000000) // AHB1, Peripheral ID: 0
#define RCC_AHB1_GPIOB          ((uint64_t)0x0000000000000001) // AHB1, Peripheral ID: 1
#define RCC_AHB1_GPIOC          ((uint64_t)0x0000000000000002) // AHB1, Peripheral ID: 2
#define RCC_AHB1_GPIOD          ((uint64_t)0x0000000000000003) // AHB1, Peripheral ID: 3
#define RCC_AHB1_GPIOE          ((uint64_t)0x0000000000000004) // AHB1, Peripheral ID: 4
#define RCC_AHB1_GPIOH          ((uint64_t)0x0000000000000007) // AHB1, Peripheral ID: 7

// Clock modes
#define RCC_NORMAL_MODE   0
#define RCC_SLEEP_MODE    1

// Enumeration for GPIO ports
typedef enum
{
   HSWITCH_enuPORTA = 0,
   HSWITCH_enuPORTB,
   HSWITCH_enuPORTC,
   HSWITCH_enuPORTD,
   HSWITCH_enuPORTE,
   HSWITCH_enuPORTH 
} HSWITCH_enuPortNum_t;

// Enumeration for error statuses
typedef enum
{
   HSWITCH_enuOK = 0,
   HSWITCH_enuNOK,
   HSWITCH_enuINVALID_PortNum,
   HSWITCH_enuINVALID_PinNum,
   HSWITCH_enuINVALID_SwitchState
} HSWITCH_enuErrorStatus_t;

// Enumeration for GPIO pin numbers
typedef enum
{
   HSWITCH_enuPIN0 = 0 ,
   HSWITCH_enuPIN1 ,  
   HSWITCH_enuPIN2 ,
   HSWITCH_enuPIN3,
   HSWITCH_enuPIN4,
   HSWITCH_enuPIN5,
   HSWITCH_enuPIN6,
   HSWITCH_enuPIN7,
   HSWITCH_enuPIN8,
   HSWITCH_enuPIN9,
   HSWITCH_enuPIN10,
   HSWITCH_enuPIN11,
   HSWITCH_enuPIN12,
   HSWITCH_enuPIN13,
   HSWITCH_enuPIN14,
   HSWITCH_enuPIN15
} HSWITCH_enuPinNum_t;

// Structure to hold the configuration of each switch
typedef struct
{
   uint8_t PORT;  
   uint8_t PIN;  
   uint8_t MODE; 
   uint8_t CLOCK_BUS;
   uint8_t CLOCK_MODE;
} HSWITCH_strSwitchCONFG_t;

// Define the number of switches and their identifiers
#define Num_of_Switch 2

#define Switch_start 0
#define Switch_stop 1

#endif /* CONFIG_H_ */
