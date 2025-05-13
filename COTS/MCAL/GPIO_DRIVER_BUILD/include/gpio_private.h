#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#include"STD_TYPES.h"



#define GPIOA_BASE 0x40020000U
#define GPIOB_BASE 0x40020400U
#define GPIOC_BASE 0x40020800U
#define GPIOD_BASE 0x40020C00U
#define GPIOE_BASE 0x40021000U
#define GPIOH_BASE 0x40021C00U

// Mode options
#define GPIO_MODE_INPUT       (0x0U)  // Input mode
#define GPIO_MODE_OUTPUT      (0x1U)  // Output mode
#define GPIO_MODE_AF          (0x2U)  // Alternate function mode
#define GPIO_MODE_ANALOG      (0x3U)  // Analog mode


// Output type options (only for output and AF modes)
#define GPIO_OUTPUT_PP        (0x0U << 2)  // Push-pull output
#define GPIO_OUTPUT_OD        (0x1U << 2)  // Open-drain output


// Pull-up/down options
#define GPIO_NO_PUPD          (0x0U << 3)  // No pull-up/down
#define GPIO_PULLUP           (0x1U << 3)  // Pull-up resistor enabled
#define GPIO_PULLDOWN         (0x2U << 3)  // Pull-down resistor enabled

// Speed options (only for output and AF modes)
#define GPIO_SPEED_LOW        (0x0U)  // Low speed
#define GPIO_SPEED_MEDIUM     (0x1U)  // Medium speed
#define GPIO_SPEED_HIGH       (0x2U)  // High speed
#define GPIO_SPEED_VERY_HIGH  (0x3U)  // Very high speed

// Configuration macros (these are combinations of mode, output type, pull-up/down, and speed)

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

#define IOAnalog              (GPIO_MODE_ANALOG | GPIO_NO_PUPD)  // Analog mode, no pull-up/down

#define GPIO_HIGH 1
#define GPIO_LOW 0

#define GPIO_PORT(port) ((GPIO_Reg_t *)(0x40020000U + ((port) * 0x400U)))


typedef struct
{
    uint32_t MODER;     // 0x00: GPIO port mode register
    uint32_t OTYPER;    // 0x04: GPIO port output type register
    uint32_t OSPEEDR;   // 0x08: GPIO port output speed register
    uint32_t PUPDR;     // 0x0C: GPIO port pull-up/pull-down register
    uint32_t IDR;       // 0x10: GPIO port input data register
    uint32_t ODR;       // 0x14: GPIO port output data register
    uint32_t BSRR;      // 0x18: GPIO port bit set/reset register
    uint32_t LCKR;      // 0x1C: GPIO port configuration lock register
    uint32_t AFRL;      // 0x20: GPIO alternate function low register
    uint32_t AFRH;      // 0x24: GPIO alternate function high register
} GPIO_Reg_t;



typedef enum
{
	GPIO_enuOK = 0,
    GPIO_enuINVALIDPORT ,
    GPIO_enuINVALIDPIN ,
    GPIO_enuINVALIDMODE ,
    GPIO_enuINVALIDPINVALUE ,
    GPIO_enuNULLPTR
	
} GPIO_enuErrorStatus_t;

#endif