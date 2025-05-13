
#ifndef SYSTICK_H
#define SYSTICK_H

#include "STD_TYPES.h"

typedef void (*SYSTICK_cbf_t)(void);

typedef enum {
    SYSTICK_noErr,
    SYSTICK_NULL_PTR,
    SYSTICK_INVALID_TIME
} SYSTICK_enuErrorStatus_t;

void SYSTICK_vInit(void);
void SYSTICK_enuStart(void);
void SYSTICK_enuStop(void);

SYSTICK_enuErrorStatus_t SYSTICK_enuSetCbf(SYSTICK_cbf_t Copy_ptrCBF, uint32_t Copy_32PeriodMSec);
SYSTICK_enuErrorStatus_t SYSTICK_enuDelayMS(uint32_t Copy_32TimeMS);

#endif
