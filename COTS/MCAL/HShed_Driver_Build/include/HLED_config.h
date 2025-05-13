
#ifndef HLED_CONFIG_H_
#define HLED_CONFIG_H_

#include "STD_TYPES.h"
#include"gpio_private.h"

#define INPUT_FLOATING        (GPIO_MODE_INPUT | GPIO_NO_PUPD)  // Input mode with floating (no pull-up/down)
#define INPUT_PU              (GPIO_MODE_INPUT | GPIO_PULLUP)   // Input mode with pull-up
#define INPUT_PD              (GPIO_MODE_INPUT | GPIO_PULLDOWN) // Input mode with pull-down

#define OUTPUT_PP             (GPIO_MODE_OUTPUT | GPIO_OUTPUT_PP | GPIO_NO_PUPD)  // Output mode, push-pull, no pull-up/down
#define OUTPUT_PP_PU          (GPIO_MODE_OUTPUT | GPIO_OUTPUT_PP | GPIO_PULLUP)   // Output mode, push-pull, pull-up
#define OUTPUT_PP_PD          (GPIO_MODE_OUTPUT | GPIO_OUTPUT_PP | GPIO_PULLDOWN) // Output mode, push-pull, pull-down

#define OUTPUT_OD             (GPIO_MODE_OUTPUT | GPIO_OUTPUT_OD | GPIO_NO_PUPD)  // Output mode, open-drain, no pull-up/down
#define OUTPUT_OD_PU          (GPIO_MODE_OUTPUT | GPIO_OUTPUT_OD | GPIO_PULLUP)   // Output mode, open-drain, pull-up
#define OUTPUT_OD_PD          (GPIO_MODE_OUTPUT | GPIO_OUTPUT_OD | GPIO_PULLDOWN) // Output mode, open-drain, pull-down

#define AF_PP                 (GPIO_MODE_AF | GPIO_OUTPUT_PP | GPIO_NO_PUPD)  // Alternate function mode, push-pull, no pull-up/down
#define AF_PP_PU              (GPIO_MODE_AF | GPIO_OUTPUT_PP | GPIO_PULLUP)   // Alternate function mode, push-pull, pull-up
#define AF_PP_PD              (GPIO_MODE_AF | GPIO_OUTPUT_PP | GPIO_PULLDOWN) // Alternate function mode, push-pull, pull-down

#define AF_OD                 (GPIO_MODE_AF | GPIO_OUTPUT_OD | GPIO_NO_PUPD)  // Alternate function mode, open-drain, no pull-up/down
#define AF_OD_PU              (GPIO_MODE_AF | GPIO_OUTPUT_OD | GPIO_PULLUP)   // Alternate function mode, open-drain, pull-up
#define AF_OD_PD              (GPIO_MODE_AF | GPIO_OUTPUT_OD | GPIO_PULLDOWN) // Alternate function mode, open-drain, pull-down



#define RCC_AHB1_GPIOA          ((uint64_t)0x0000000000000000) // AHB1, Peripheral ID: 0
#define RCC_AHB1_GPIOB          ((uint64_t)0x0000000000000001) // AHB1, Peripheral ID: 1
#define RCC_AHB1_GPIOC          ((uint64_t)0x0000000000000002) // AHB1, Peripheral ID: 2
#define RCC_AHB1_GPIOD          ((uint64_t)0x0000000000000003) // AHB1, Peripheral ID: 3
#define RCC_AHB1_GPIOE          ((uint64_t)0x0000000000000004) // AHB1, Peripheral ID: 4
#define RCC_AHB1_GPIOH          ((uint64_t)0x0000000000000007) // AHB1, Peripheral ID: 7

typedef enum
{
	HLED_enuForward =0 ,
	HLED_enuReverse
	
}HLED_enuLed_ConnectionOptions_t;

typedef enum
{
   HLED_enuPORTA =0 ,
   HLED_enuPORTB ,
   HLED_enuPORTC ,
   HLED_enuPORTD ,
   HLED_enuPORTE ,
   HLED_enuPORTH 
} HLED_enuPortNum_t;

typedef enum
{
	HLED_enuOK = 0,
	HLED_enuNOK,
	HLED_enuINVALID_PortNum,
	HLED_enuINVALID_PinNum,
	HLED_enuINVALID_PinStatus,
	HLED_enuINVALID_LEDName ,
	HLED_enuINVALID_LEDValue ,
	HLED_enuINVALID_LEDConnection
	
	
} HLED_enuErrorStatus_t;


typedef enum
{
	HLED_enuPIN0=0 ,
    HLED_enuPIN1 ,  
    HLED_enuPIN2    ,
    HLED_enuPIN3,
    HLED_enuPIN4,
    HLED_enuPIN5,
    HLED_enuPIN6,
    HLED_enuPIN7,
    HLED_enuPIN8,
    HLED_enuPIN9,
    HLED_enuPIN10,
    HLED_enuPIN11,
    HLED_enuPIN12,
    HLED_enuPIN13,
    HLED_enuPIN14,
    HLED_enuPIN15
} HLED_enuPinNum_t;


typedef enum
{
	HLED_enuON = 0,
	HLED_enuOFF
	
} HLED_enuState_t;

#define RCC_NORMAL_MODE   0
#define RCC_SLEEP_MODE    1

typedef struct
{
	uint8_t PORT;  
	uint8_t PIN;  
	uint8_t MODE ; 
	uint8_t CLOCK_BUS;
	uint8_t CLOCK_MODE;
	HLED_enuLed_ConnectionOptions_t CONNECTION; 
} HLED_strLedCONFG_t;

#define Num_of_Led 3


#define  Led1 0
#define  Led2 1
#define  Led3 1


#endif /* HLED_CONFIG_H_ */