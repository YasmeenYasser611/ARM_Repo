#include "Sched.h"
#include "SYSTICK.h"



Sched_Runnable_t* Sched_Saved_Runnable[MAX_RUNNS] = {NULL};
static uint32_t current_tick = 0;


void HSCHED_Init(void)
{
    SYSTICK_vInit();
    SYSTICK_enuSetCbf(HSCHED_Runnable_Manger, 1); // Set SYSTICK callback to manage runnables every tick
}


void HSCHED_Start(void)
{
    SYSTICK_enuStart(); // Start SYSTICK to enable the scheduler
}


void HSCHED_Stop(void)
{
    SYSTICK_enuStop(); // Stop SYSTICK to disable the scheduler
}


HSCHED_enuErrorStatus_t HSCHED_Register_Runnable(Sched_Runnable_t *Copy_ptr_Func)
{
    if (Copy_ptr_Func == NULL)
    {
        return HSCED_NULL_PTR;
    }

    if (Sched_Saved_Runnable[Copy_ptr_Func->Priority] == NULL)
    {
        Sched_Saved_Runnable[Copy_ptr_Func->Priority] = Copy_ptr_Func;
        return HSCHED_noErr;
    }
    else
    {
        return HSCED_PRIORITY_RESERVED;
    }
}


void HSCHED_Runnable_Manger(void)
{
    current_tick++;

    for (uint8_t i = 0; i < MAX_RUNNS; i++)
    {
        if (Sched_Saved_Runnable[i] != NULL)
        {
            if (Sched_Saved_Runnable[i]->CBF == NULL)
            {
                continue; // Skip NULL function pointers
            }

            // Check if First_Delay is not zero, then decrement it
            if (Sched_Saved_Runnable[i]->First_Delay > 0)
            {
                Sched_Saved_Runnable[i]->First_Delay--;
            }
            else
            {
                // Execute only if it's time
                if ((current_tick % Sched_Saved_Runnable[i]->Cyclic_Time) == 0)
                {
                    Sched_Saved_Runnable[i]->CBF();
                }
            }
        }
    }
}
