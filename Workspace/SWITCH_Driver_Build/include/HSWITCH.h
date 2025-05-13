#ifndef HSWITCH_H_
#define HSWITCH_H_

#include "HSWITCH_config.h"
#include "STD_TYPES.h"

void HSWITCH_vSwitch_init(void);

HSWITCH_enuErrorStatus_t HSWITCH_enuGetSwitchState(uint8_t Copy_u8SwitchName, uint8_t* Add_pu8State);

void HSWITCH_RUNNABLE(void);

HSWITCH_enuErrorStatus_t HSWITCH_Read(uint8_t Copy_u8SwitchName , uint8_t* Add_pu8State);

#endif /* HSWITCH_H_ */





