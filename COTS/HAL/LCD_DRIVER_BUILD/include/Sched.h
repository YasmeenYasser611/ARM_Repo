#ifndef SCHED_H
#define SCHED_H

#include "STD_TYPES.h"

#define MAX_RUNNS 7

typedef void (*SCHED_cbf_t)(void);

typedef struct
{
    SCHED_cbf_t CBF;
    uint32_t Priority;
    uint32_t First_Delay;
    uint32_t Cyclic_Time;
} Sched_Runnable_t;

typedef enum {
    HSCHED_noErr,
    HSCED_NULL_PTR,
    HSCED_PRIORITY_RESERVED
} HSCHED_enuErrorStatus_t;


void HSCHED_Init(void);

void HSCHED_Start(void);

void HSCHED_Stop(void);


HSCHED_enuErrorStatus_t HSCHED_Register_Runnable(Sched_Runnable_t *Copy_ptr_Func);

void HSCHED_Runnable_Manger(void);

#endif
