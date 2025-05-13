
#include"STD_TYPES.h"
#include"NVIC_private.h"

#ifndef NVIC_H
#define NVIC_H



NVIC_errStatus_t NVIC_EnableIRQ(IRQn_t IRQn );


NVIC_errStatus_t NVIC_DisableIRQ(IRQn_t IRQn);



NVIC_errStatus_t NVIC_SetPendingIRQ (IRQn_t IRQn);

NVIC_errStatus_t NVIC_ClearPendingIRQ (IRQn_t IRQn);



NVIC_errStatus_t NVIC_SetPriority (IRQn_t IRQn, uint32_t priority);


NVIC_errStatus_t NVIC_GetPriority (IRQn_t IRQn , uint32_t* Add_pu32Priority);



NVIC_errStatus_t NVIC_GetPendingIRQ (IRQn_t IRQn , uint32_t* Add_pu32PendingIRQ);


NVIC_errStatus_t NVIC_GetActive (IRQn_t IRQn , uint32_t* Add_pu32Active);

NVIC_errStatus_t NVIC_SetSoftwareInterrupt(IRQn_t IRQn);

NVIC_errStatus_t NVIC_SetPriorityGrouping(NVIC_enuPriority_Grouping priority_grouping);

NVIC_errStatus_t NVIC_GetPriorityGrouping(NVIC_enuPriority_Grouping priority_grouping ,uint32_t * Add_pu8PriorityGrouping );

void NVIC_SystemReset(void);

#endif
