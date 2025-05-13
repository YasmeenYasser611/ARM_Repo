#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#include "STD_TYPES.h"


#define GET_BUS_ID(Bus_Peripheral_ID)    ((uint8_t)((Bus_Peripheral_ID >> 60) & 0xF))
#define GET_PER_ID(Bus_Peripheral_ID)    ((uint8_t)(Bus_Peripheral_ID & 0x3F))


#define RCC_BASEADDR        ((uint32_t *) 0x40023800)
#define RCC_PER_ID_MAX    31

// Clock Modes
#define RCC_ON            1   // Enable the clock
#define RCC_OFF           0   // Disable the clock

#define RCC_PLLCFG_PLLSRC_HSI   0x0    
#define RCC_PLLCFG_PLLSRC_HSE   0x400000 
#define RCC_PLLON_BIT       ((uint32_t)0x01000000) // PLL Enable bit (bit 24)
#define RCC_PLLRDY_BIT      ((uint32_t)0x02000000) // PLL Ready bit (bit 25)


#define RCC_AHB1          0
#define RCC_AHB2          1
#define RCC_APB1          2
#define RCC_APB2          3


#define RCC_NORMAL_MODE   0
#define RCC_SLEEP_MODE    1

#define RCC_CFGR_SWS_MSK      ((uint32_t) 0x0000000C)  // Mask for System Clock Switch bits
#define RCC_CFGR_SW_HSI       ((uint32_t) 0x00000000)  // HSI as System Clock
#define RCC_CFGR_SW_HSE       ((uint32_t) 0x00000004)  // HSE as System Clock
#define RCC_CFGR_SW_PLL       ((uint32_t) 0x00000008)  // PLL as System Clock

#define RCC_CR_HSEBYP         ((uint32_t) 0x00010000)  // HSE Bypass
#define RCC_CR_HSEON          ((uint32_t) 0x00020000)  // HSE ON
#define RCC_CR_PLLON          ((uint32_t) 0x01000000)  // PLL ON

#define RCC_PLL_EN_MSK      ((uint32_t) 0x3000000)
#define RCC_PLL_SRC_MSK     ((uint32_t) 0xFFBFFFFF)

// Clock Sources
#define RCC_HSI           0   // Internal high-speed clock
#define RCC_HSE           1   // External high-speed clock
#define RCC_HSE_BYPASS    2   // External high-speed clock in bypass mode
#define RCC_PLL           3   // Phase-locked loop


#define RCC_HSI_SYSTEMCLK 0
#define RCC_HSE_SYSTEMCLK 1
#define RCC_PLL_SYSTEMCLK 2


// RCC Clock Control Register (CR) Bit Positions
#define RCC_CR_HSION       0   // HSI enable bit
#define RCC_CR_HSIRDY      1   // HSI ready flag
#define RCC_CR_HSEON      16   // HSE enable bit
#define RCC_CR_HSERDY     17   // HSE ready flag
#define RCC_CR_HSEBYP     18   // HSE bypass enable bit
#define RCC_CR_PLLON      24   // PLL enable bit
#define RCC_CR_PLLRDY     25   // PLL ready flag

#define RCC_CR_HSION_MASK     (1U << RCC_CR_HSION)
#define RCC_CR_HSIRDY_MASK    (1U << RCC_CR_HSIRDY)
#define RCC_CR_HSEON_MASK     (1U << RCC_CR_HSEON)
#define RCC_CR_HSERDY_MASK    (1U << RCC_CR_HSERDY)
#define RCC_CR_HSEBYP_MASK    (1U << RCC_CR_HSEBYP)
#define RCC_CR_PLLON_MASK     (1U << RCC_CR_PLLON)
#define RCC_CR_PLLRDY_MASK    (1U << RCC_CR_PLLRDY)


#define RCC_AHB1_GPIOA          ((uint64_t)0x0000000000000000) // AHB1, Peripheral ID: 0
#define RCC_AHB1_GPIOB          ((uint64_t)0x0000000000000001) // AHB1, Peripheral ID: 1
#define RCC_AHB1_GPIOC          ((uint64_t)0x0000000000000002) // AHB1, Peripheral ID: 2
#define RCC_AHB1_GPIOD          ((uint64_t)0x0000000000000003) // AHB1, Peripheral ID: 3
#define RCC_AHB1_GPIOE          ((uint64_t)0x0000000000000004) // AHB1, Peripheral ID: 4
#define RCC_AHB1_GPIOH          ((uint64_t)0x0000000000000007) // AHB1, Peripheral ID: 7
#define RCC_AHB1_CRC            ((uint64_t)0x000000000000000C) // AHB1, Peripheral ID: 12
#define RCC_AHB1_DMA1           ((uint64_t)0x0000000000000015) // AHB1, Peripheral ID: 21
#define RCC_AHB1_DMA2           ((uint64_t)0x0000000000000016) // AHB1, Peripheral ID: 22

#define RCC_AHB2_OTGFS          ((uint64_t)0x0000000100000007) // AHB2, Peripheral ID: 7

#define RCC_APB1_TIM2           ((uint64_t)0x0000000200000000) // APB1, Peripheral ID: 0
#define RCC_APB1_TIM3           ((uint64_t)0x0000000200000001) // APB1, Peripheral ID: 1
#define RCC_APB1_TIM4           ((uint64_t)0x0000000200000002) // APB1, Peripheral ID: 2
#define RCC_APB1_TIM5           ((uint64_t)0x0000000200000003) // APB1, Peripheral ID: 3
#define RCC_APB1_WWDG           ((uint64_t)0x000000020000000B) // APB1, Peripheral ID: 11
#define RCC_APB1_SPI2           ((uint64_t)0x000000020000000E) // APB1, Peripheral ID: 14
#define RCC_APB1_SPI3           ((uint64_t)0x000000020000000F) // APB1, Peripheral ID: 15
#define RCC_APB1_USART2         ((uint64_t)0x0000000200000011) // APB1, Peripheral ID: 17
#define RCC_APB1_I2C1           ((uint64_t)0x0000000200000015) // APB1, Peripheral ID: 21
#define RCC_APB1_I2C2           ((uint64_t)0x0000000200000016) // APB1, Peripheral ID: 22
#define RCC_APB1_I2C3           ((uint64_t)0x0000000200000017) // APB1, Peripheral ID: 23
#define RCC_APB1_PWR            ((uint64_t)0x000000020000001C) // APB1, Peripheral ID: 28


#define RCC_APB2_TIM1           ((uint64_t)0x0000000300000000) // APB2, Peripheral ID: 0
#define RCC_APB2_USART1         ((uint64_t)0x0000000300000004) // APB2, Peripheral ID: 4
#define RCC_APB2_USART6         ((uint64_t)0x0000000300000005) // APB2, Peripheral ID: 5
#define RCC_APB2_ADC1           ((uint64_t)0x0000000300000008) // APB2, Peripheral ID: 8
#define RCC_APB2_SDIO           ((uint64_t)0x000000030000000B) // APB2, Peripheral ID: 11
#define RCC_APB2_SPI1           ((uint64_t)0x000000030000000C) // APB2, Peripheral ID: 12
#define RCC_APB2_SPI4           ((uint64_t)0x000000030000000D) // APB2, Peripheral ID: 13
#define RCC_APB2_SYSCFG         ((uint64_t)0x000000030000000E) // APB2, Peripheral ID: 14
#define RCC_APB2_TIM9           ((uint64_t)0x0000000300000010) // APB2, Peripheral ID: 16
#define RCC_APB2_TIM10          ((uint64_t)0x0000000300000011) // APB2, Peripheral ID: 17
#define RCC_APB2_TIM11          ((uint64_t)0x0000000300000012) // APB2, Peripheral ID: 18


typedef struct 
{
    uint32_t CR;           // 0x00: Clock control register
    uint32_t PLLCFGR;      // 0x04: PLL configuration register
    uint32_t CFGR;         // 0x08: Clock configuration register
    uint32_t CIR;          // 0x0C: Clock interrupt register
    uint32_t AHB1RSTR;     // 0x10: AHB1 peripheral reset register
    uint32_t AHB2RSTR;     // 0x14: AHB2 peripheral reset register
    uint32_t Reserved[2];  // 0x18-0x1C: Reserved
    uint32_t APB1RSTR;     // 0x20: APB1 peripheral reset register
    uint32_t APB2RSTR;     // 0x24: APB2 peripheral reset register
    uint32_t Reserved1[2]; // 0x28-0x2C: Reserved
    uint32_t AHB1ENR;      // 0x30: AHB1 peripheral clock enable register
    uint32_t AHB2ENR;      // 0x34: AHB2 peripheral clock enable register
    uint32_t Reserved2[2]; // 0x38-0x3C: Reserved
    uint32_t APB1ENR;      // 0x40: APB1 peripheral clock enable register
    uint32_t APB2ENR;      // 0x44: APB2 peripheral clock enable register
    uint32_t Reserved3[2]; // 0x48-0x4C: Reserved
    uint32_t AHB1LPENR;    // 0x50: AHB1 low power enable register
    uint32_t AHB2LPENR;    // 0x54: AHB2 low power enable register
    uint32_t Reserved4[2]; // 0x58-0x5C: Reserved
    uint32_t APB1LPENR;    // 0x60: APB1 low power enable register
    uint32_t APB2LPENR;    // 0x64: APB2 low power enable register
    uint32_t Reserved5[2]; // 0x68-0x6C: Reserved
    uint32_t BDCR;         // 0x70: Backup domain control register
    uint32_t CSR;          // 0x74: Clock control & status register
    uint32_t Reserved6[2]; // 0x78-0x7C: Reserved
    uint32_t SSCGR;        // 0x80: Spread spectrum clock generation register
    uint32_t PLLI2SCFGR;   // 0x84: PLLI2S configuration register
    uint32_t Reserved7[1]; // 0x88: Reserved
    uint32_t DCKCFGR;      // 0x8C: Dedicated clocks configuration register
} RCC_Reg_t;


typedef struct 
{
    /* data */
    uint32_t M_Prescaler;
    uint32_t N_Multiple;
    uint32_t P_Prescaler;
    uint32_t PLL_Src;
    uint32_t Q_Prescaler;
}RCC_PLLCfg_t;

typedef enum{
    RCC_noErr,
    RCC_errNULLPtr,
    RCC_errPLLON,
    RCC_errPLLSrc,
    Invalid_M_Prescaler ,
    Invalid_N_Multiple ,
    Invalid_P_Prescaler,
    Invalid_Q_Prescaler,
    RCC_enuInvalidPerId ,
    RCC_enuInvalidBusId ,
    RCC_enuInvalidMode ,
    RCC_enuInvalidClockSource ,
    RCC_enuInvalidStatus ,
    RCC_enuTimeout 

}RCC_errStatus_t;   

#endif