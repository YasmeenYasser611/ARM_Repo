
#ifndef GPIO_H
#define GPIO_H

#include"STD_TYPES.h"


/*

Register Group	          Start	  Size      Next Address	Reserved Size
ISER (Set Enable)	        0x000	8*4B=32B	0x020 → 0x080	96B (24 × 4)
ICER (Clear Enable)	      0x080	8*4B=32B	0x0A0 → 0x100	96B (24 × 4)
ISPR (Set Pending)	      0x100	8*4B=32B	0x120 → 0x180	96B (24 × 4)
ICPR (Clear Pending)	    0x180	8*4B=32B	0x1A0 → 0x200	96B (24 × 4)
IABR (Active Bit)	        0x200	8*4B=32B	0x220 → 0x300	224B (56 × 4)
IPR (Priority)	          0x300	240*1B=240  0x3F0 → 0xE00	2576B (644 × 4)
STIR (Software Trigger)	  0xE00	1*4B=4B	-	-

*/
typedef struct
{
  volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register , Each ISER bit controls one interrupt , Cortex-M4 supports 240 interrupts ,8 * 32(uint32_t) = 256 bits (more than enough for 240 interrupts)  */
  volatile const uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register ,  used to disable interrupts */
  volatile const uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register , force an interrupt  */
  volatile const uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register , clear a pending interrupt */
  volatile const uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register , Shows whether an interrupt is currently active */
  volatile const uint32_t RESERVED4[56U];
  volatile uint8_t  IPR[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) , so 8bit for each register , so we need 240*8  */
  volatile const uint32_t RESERVED5[644U];
  volatile uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register  , for software-generated interrupts*/
}  NVIC_Type;


#define NVIC_BASEADDR        ((uint32_t *) 0xE000E100)

typedef struct{
    volatile uint32_t ACTLR;
    const uint32_t RESERVED0[829];
    volatile uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint32_t SHPR1; 
    volatile uint32_t SHPR2;
    volatile uint32_t SHPR3;
    volatile uint32_t SHCSR;
    volatile uint32_t CFSR;
    volatile uint32_t MMSR; 
    volatile uint32_t BFSR; 
    volatile uint32_t UFSR;
    volatile uint32_t HFSR;
    volatile uint32_t MMAR;
    volatile uint32_t BFAR; 
    volatile uint32_t AFSR;
}SCB_Type;

#define SCB_BASEADDR        ((uint32_t *) 0xE000E008)


typedef enum {
    NVIC_enuWWDG,
    NVIC_enuEXTI16_PVD,
    NVIC_enuEXTI21_TAMP_STAMP,
    NVIC_enuEXTI22_RTC_WKUP,
    NVIC_enuFLASH,
    NVIC_enuRCC,
    NVIC_enuEXTI0,
    NVIC_enuEXTI1,
    NVIC_enuEXTI2,
    NVIC_enuEXTI3,
    NVIC_enuEXTI4,
    NVIC_enuDMA1_Stream0,
    NVIC_enuDMA1_Stream1,
    NVIC_enuDMA1_Stream2,
    NVIC_enuDMA1_Stream3,
    NVIC_enuDMA1_Stream4,
    NVIC_enuDMA1_Stream5,
    NVIC_enuDMA1_Stream6,
    NVIC_enuADC ,
    NVIC_enuEXTI9_5=23,
    NVIC_enuTIM1_BRK_TIM9,
    NVIC_enuTIM1_UP_TIM10,
    NVIC_enuTIM1_TRG_COM_TIM11,
    NVIC_enuTIM1_CC,
    NVIC_enuTIM2,
    NVIC_enuTIM3,
    NVIC_enuTIM4,
    NVIC_enuI2C1_EV,
    NVIC_enuI2C1_ER,
    NVIC_enuI2C2_EV,
    NVIC_enuI2C2_ER,
    NVIC_enuSPI1,
    NVIC_enuSPI2,
    NVIC_enuUSART1,
    NVIC_enuUSART2,
    NVIC_enuEXTI15_10=40,
    NVIC_enuEXTI17_RTC_Alarm,
    NVIC_enuEXTI18_OTG_FS_WKUP,
    NVIC_enuDMA1_Stream7=47,
    NVIC_enuSDIO=49,
    NVIC_enuTIM5,
    NVIC_enuSPI3,
    NVIC_enuDMA2_Stream0=56,
    NVIC_enuDMA2_Stream1,
    NVIC_enuDMA2_Stream2,
    NVIC_enuDMA2_Stream3,
    NVIC_enuDMA2_Stream4,
    NVIC_enuOTG_FS=67,
    NVIC_enuDMA2_Stream5,
    NVIC_enuDMA2_Stream6,
    NVIC_enuDMA2_Stream7,
    NVIC_enuUSART6,
    NVIC_enuI2C3_EV ,
    NVIC_enuI2C3_ER,
    NVIC_enuFPU=81,
    NVIC_enuSPI4=84 
} IRQn_t;   


typedef enum{
    NVIC_noErr,
    NVIC_ERROR_INVALID_IRQ ,
    NVIC_ERROR_NULL_POINTER ,
    NVIC_ERROR_INVALID_PRIORITY ,
    NVIC_ERORR_INVALID_PRIORITY_GROUPING

}NVIC_errStatus_t; 

typedef enum
{
    Group_priorities_16= 0b000,
    Group_priorities_8= 0b100,
    Group_priorities_4= 0b101,
    Group_priorities_2= 0b110,
    Group_priorities_NONE= 0b111,
}NVIC_enuPriority_Grouping;


#endif