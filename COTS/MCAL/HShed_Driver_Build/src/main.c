#include "Sched.h"
#include "HLED.h"  
#include "STD_TYPES.h"

// LED states
static uint8_t currentState1 = HLED_enuOFF;
static uint8_t currentState2 = HLED_enuOFF;
static uint8_t currentState3 = HLED_enuOFF;

// Task functions
void Task1() 
{ 
    currentState1 = (currentState1 == HLED_enuON) ? HLED_enuOFF : HLED_enuON;
    HLED_enuSetLedState(Led1 , currentState1); 
}  

void Task2() 
{     
    currentState2 = (currentState2 == HLED_enuON) ? HLED_enuOFF : HLED_enuON;
    HLED_enuSetLedState(Led2 , currentState2);  
}  

void Task3() 
{     
    currentState3 = (currentState3 == HLED_enuON) ? HLED_enuOFF : HLED_enuON;
    HLED_enuSetLedState(Led3 , currentState3); 
}  

int main()
{
    // Initialize LEDs
    HLED_vLED_init();

    // Initialize scheduler
    HSCHED_Init();

    // Define tasks
    Sched_Runnable_t task1 = {Task1, 0, 0, 2}; // Runs every 2 ticks
    Sched_Runnable_t task2 = {Task2, 1, 1, 3}; // Runs every 3 ticks, starts after 1 tick
    Sched_Runnable_t task3 = {Task3, 2, 2, 4}; // Runs every 4 ticks, starts after 2 ticks

    // Register tasks with the scheduler
    HSCHED_Register_Runnable(&task1);
    HSCHED_Register_Runnable(&task2);
    HSCHED_Register_Runnable(&task3);

    // Start the scheduler
    HSCHED_Start();

    // The main loop will keep running the scheduler
    while (1)
    {
        // In an embedded system, this would usually be an idle loop, with tasks running in the background
        // HSCHED_Runnable_Manger() is called by the SYSTICK interrupt callback (HSCHED_Runnable_Manger) every tick
    }

    return 0;
}
