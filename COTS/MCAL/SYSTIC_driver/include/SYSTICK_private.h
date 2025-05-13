#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#include"STD_TYPES.h"

typedef struct 
{
    volatile uint32_t STK_CTRL;
    volatile uint32_t STK_LOAD;
    volatile uint32_t STK_VAL;
    volatile uint32_t STK_CALIB;

} SysTick_Reg_t;

#define SysTick_BaseAddress ((uint32_t * )0xE000E010)

#endif