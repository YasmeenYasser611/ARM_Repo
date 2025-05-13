#include "HSWITCH_config.h"
#include "RCC.h"
#include "gpio.h"
#include "Sched.h"

extern HSWITCH_strSwitchCONFG_t HSWITCH_enuArrSwitchConf[Num_of_Switch];

static uint8_t gSwitchState[Num_of_Switch] = {0}; 
static uint8_t lastState[Num_of_Switch] = {0};
static uint8_t counter[Num_of_Switch] = {0};

void HSWITCH_vSwitch_init(void)
{
    uint8_t Local_u8_i = 0;
    
    // Initialize each switch by configuring the GPIO pin and enabling clock
    for (Local_u8_i = 0; Local_u8_i < Num_of_Switch; Local_u8_i++)
    {
        RCC_ControlPerClock(HSWITCH_enuArrSwitchConf[Local_u8_i].CLOCK_BUS, RCC_ON, HSWITCH_enuArrSwitchConf[Local_u8_i].CLOCK_MODE);
        GPIO_voidSetPinDirection(HSWITCH_enuArrSwitchConf[Local_u8_i].PORT, HSWITCH_enuArrSwitchConf[Local_u8_i].PIN, HSWITCH_enuArrSwitchConf[Local_u8_i].MODE);
    }
}

HSWITCH_enuErrorStatus_t HSWITCH_enuGetSwitchState(uint8_t Copy_u8SwitchName, uint8_t* Add_pu8State)
{
    HSWITCH_enuErrorStatus_t Ret_enuError = HSWITCH_enuOK;
    
    // Validate input parameters
    if (Copy_u8SwitchName >= Num_of_Switch || Add_pu8State == NULL)
    {
        Ret_enuError = HSWITCH_enuNOK;
    }
    else
    {
        GPIO_enuErrorStatus_t gpioStatus = GPIO_enuGetPinValue(HSWITCH_enuArrSwitchConf[Copy_u8SwitchName].PORT, HSWITCH_enuArrSwitchConf[Copy_u8SwitchName].PIN, Add_pu8State);
        
        if (gpioStatus != GPIO_enuOK)
        {
            Ret_enuError = HSWITCH_enuNOK;  
        }
    }
    
    return Ret_enuError;
}

void HSWITCH_RUNNABLE(void)
{
    uint8_t currentState;
    
    for (uint8_t i = 0; i < Num_of_Switch; i++) {
        if (HSWITCH_enuGetSwitchState(i, &currentState) == HSWITCH_enuOK) {
            if (currentState == lastState[i]) {
                if (counter[i] < 5) {
                    counter[i]++;
                } else {
                    gSwitchState[i] = currentState;
                    counter[i] = 0;  
                }
            } else {
                counter[i] = 0;  
            }

            lastState[i] = currentState;  
        }
    }
}

HSWITCH_enuErrorStatus_t HSWITCH_Read(uint8_t Copy_u8SwitchName, uint8_t* Add_pu8State)
{
    HSWITCH_enuErrorStatus_t Ret_enuError = HSWITCH_enuOK;
    
    if (Copy_u8SwitchName >= Num_of_Switch)
    {
        Ret_enuError = HSWITCH_enuNOK;  // Invalid switch name
    }
    else
    {
        *Add_pu8State = gSwitchState[Copy_u8SwitchName];  // Return the debounced state
    }
    
    return Ret_enuError;
}
