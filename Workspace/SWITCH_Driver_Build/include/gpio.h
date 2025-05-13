#ifndef GPIO_H
#define GPIO_H

#include"STD_TYPES.h"
#include"gpio_private.h"


#define GPIO_A 0     /*PA0 to PA15*/
#define GPIO_B 1     /*PB0 to PB15*/
#define GPIO_C 2     /*PC0 to PC13*/
#define GPIO_D 3     /*PD0 to PD15*/
#define GPIO_E 4     /*PE0 to PE15*/
#define GPIO_H 5     /*PH0, PH1*/


#define PIN0     0
#define PIN1     1
#define PIN2     2
#define PIN3     3
#define PIN4     4
#define PIN5     5
#define PIN6     6
#define PIN7     7
#define PIN8     8
#define PIN9     9
#define PIN10    10
#define PIN11    11
#define PIN12    12
#define PIN13    13
#define PIN14    14
#define PIN15    15



GPIO_enuErrorStatus_t GPIO_voidSetPinDirection(uint8_t copy_u8PORT, uint8_t copy_u8PIN, uint32_t copy_u32MODE);
GPIO_enuErrorStatus_t GPIO_voidSetPinValue(uint8_t copy_u8PORT , uint8_t copy_u8PIN , uint8_t copy_u8VALUE);
GPIO_enuErrorStatus_t GPIO_enuGetPinValue(uint8_t copy_u8PORT , uint8_t copy_u8PIN , uint8_t* Add_pu8PinValue);


#endif