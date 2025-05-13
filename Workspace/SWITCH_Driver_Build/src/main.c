#include "HSWITCH.h"
#include "HLED.h"    
#include "Sched.h"

int main(void)
{
    HSWITCH_vSwitch_init();  
    HLED_vLED_init();     
    HSCHED_Init();

    Sched_Runnable_t switchRunnable = {
        .CBF = HSWITCH_RUNNABLE,    
        .Priority = 0,             
        .First_Delay = 0,          
        .Cyclic_Time = 1            
    };

    HSCHED_Register_Runnable(&switchRunnable);
    HSCHED_Start();

    uint8_t switchState;

    // Main loop
    while (1)
    {
        for (uint8_t i = 0; i < Num_of_Switch; i++)
        {
            // Read the debounced state of the switch
            if (HSWITCH_Read(i, &switchState) == HSWITCH_enuOK)
            {
                // Turn on the corresponding LED based on the switch state
                if (switchState)
                {
                    // LED ON when switch is pressed
                    HLED_enuSetLedState(i , HLED_enuON);  
                }
                else
                {
                    // LED OFF when switch is released
                    HLED_enuSetLedState(i , HLED_enuOFF); 
                }
            }
        }
    }
}
