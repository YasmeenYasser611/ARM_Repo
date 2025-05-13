#include "SYSTICK.h"
#include "SYSTICK_conf.h"
#include "SYSTICK_private.h"
#include "STD_TYPES.h"

static uint32_t Saved_SystemClkHz = 0;
static SYSTICK_cbf_t SYSTICK_Saved_Cbf = NULL;
static uint32_t SYSTICK_PeriodMsCbf = 0;
static uint32_t SYSTICK_passedMs = 0;

void SYSTICK_vInit(void)
{
    volatile SysTick_Reg_t * SysTick_Reg = (volatile SysTick_Reg_t *)SysTick_BaseAddress;
    Saved_SystemClkHz = RCC_AHB_CLK_HZ / 8; // use the AHB/8 MODE

    // To count 1ms = 1/1000 sec
    SysTick_Reg->STK_LOAD = 0;
    SysTick_Reg->STK_LOAD = (Saved_SystemClkHz / 1000) - 1;

    // Clear previous settings and set: AHB/8 clock and enable interrupt
    SysTick_Reg->STK_CTRL &= ~(0x07);  // Clear the control register
    SysTick_Reg->STK_CTRL |= (1 << 2); // Use AHB/8 Clock
    SysTick_Reg->STK_CTRL |= (1 << 1); // Enable SysTick Interrupt

    SysTick_Reg->STK_VAL = 0; // Clear current value register
}

void SYSTICK_enuStart(void)
{
    volatile SysTick_Reg_t * SysTick_Reg = (volatile SysTick_Reg_t *)SysTick_BaseAddress;
    SysTick_Reg->STK_CTRL |= 0x00000001; // Start SysTick
}

void SYSTICK_enuStop(void)
{
    volatile SysTick_Reg_t * SysTick_Reg = (volatile SysTick_Reg_t *)SysTick_BaseAddress;
    SysTick_Reg->STK_CTRL &= ~(0x00000001); // Stop SysTick
}

SYSTICK_enuErrorStatus_t SYSTICK_enuSetCbf(SYSTICK_cbf_t Copy_ptrCBF, uint32_t Copy_32PeriodMSec)
{
    SYSTICK_enuErrorStatus_t Ret_errStatus = SYSTICK_noErr;
    if (Copy_ptrCBF == NULL)
    {
        Ret_errStatus = SYSTICK_NULL_PTR;
    }
    else if (Copy_32PeriodMSec <= 0)
    {
        Ret_errStatus = SYSTICK_INVALID_TIME;
    }
    else
    {
        SYSTICK_Saved_Cbf = Copy_ptrCBF;
        SYSTICK_PeriodMsCbf = Copy_32PeriodMSec;
    }
    return Ret_errStatus;
}

SYSTICK_enuErrorStatus_t SYSTICK_enuDelayMS(uint32_t Copy_32TimeMS)
{
    SYSTICK_enuErrorStatus_t Ret_errStatus = SYSTICK_noErr;

    // Validate input time
    if (Copy_32TimeMS <= 0 || Copy_32TimeMS > 0xFFFFFF)
    {
        Ret_errStatus = SYSTICK_INVALID_TIME;
    }
    else
    {
        uint32_t startMs = SYSTICK_passedMs;
        uint32_t plannedTime = SYSTICK_passedMs + Copy_32TimeMS;
        uint8_t isOverFlowed = 0;
        uint32_t remainingTicksBeforeOverflow = 0;
        uint32_t remainingTicksAfterOverflow = 0;
        uint32_t maxTicks = 0xFFFFFF;  // 24-bit maximum value

        // Check if overflow will occur
        if (plannedTime < startMs)
        {
            isOverFlowed = 1;
            remainingTicksBeforeOverflow = maxTicks - startMs;
            remainingTicksAfterOverflow = Copy_32TimeMS - remainingTicksBeforeOverflow;
        }

        SYSTICK_enuStart(); // Start SysTick

        // Wait until the required time has elapsed
        if (isOverFlowed)
        {
            // Wait for overflow
            while (SYSTICK_passedMs != 0);

            // After overflow, wait for the remaining time
            while (SYSTICK_passedMs < remainingTicksAfterOverflow);
        }
        else
        {
            // Wait without overflow
            while (SYSTICK_passedMs < plannedTime);
        }
    }

    return Ret_errStatus;
}

void SysTick_Handler(void)
{
    SYSTICK_passedMs++; // Increment the passed milliseconds count
    if (SYSTICK_Saved_Cbf != NULL && (SYSTICK_passedMs % SYSTICK_PeriodMsCbf == 0))
    {
        SYSTICK_Saved_Cbf(); // Execute the callback function
    }
}
