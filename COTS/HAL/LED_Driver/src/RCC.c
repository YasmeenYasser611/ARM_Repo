#include "STD_TYPES.h"
#include "RCC.h"
#include "RCC_Cfg.h"
#include"RCC_PRIVATE.h"



/*
Description:

    •f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
    •f(PLL general clock output) = f(VCO clock) / PLLP
    •f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ

Parameters:


Return:

*/



/* note befote configur pll you chould use RCC_ControlClock(RCC_PLL, RCC_OFF);*/
RCC_errStatus_t RCC_enmCfgPLL(RCC_PLLCfg_t * RCC_PLLCfg)
{
    RCC_errStatus_t RCC_errStatus = RCC_noErr;
    volatile RCC_Reg_t * RCC_Reg = (volatile RCC_Reg_t *) RCC_BASEADDR;
    uint32_t VCO = 0;
    uint32_t tmp = 0;

    // Check for NULL pointer
    if (RCC_PLLCfg == NULL)
    {
        RCC_errStatus= RCC_errNULLPtr;
        
    }
    // Check if the PLL is already enabled
    else if (RCC_Reg->CR & RCC_PLL_EN_MSK)
    {
        RCC_errStatus = RCC_errPLLON;

    }

    // Validate M_Prescaler (2 ≤ M ≤ 63)
    else if (RCC_PLLCfg->M_Prescaler < 2 || RCC_PLLCfg->M_Prescaler > 63)
    {
        RCC_errStatus= Invalid_M_Prescaler; // Invalid M_Prescaler
    }

    // Validate N_Multiple (192 ≤ N ≤ 432)
    else if (RCC_PLLCfg->N_Multiple < 192 || RCC_PLLCfg->N_Multiple > 432)
    {
        RCC_errStatus = Invalid_N_Multiple; // Invalid N_Multiple
    }

    // Validate P_Prescaler (2, 4, 6, or 8)
    else if (RCC_PLLCfg->P_Prescaler != 2 &&
        RCC_PLLCfg->P_Prescaler != 4 &&
        RCC_PLLCfg->P_Prescaler != 6 &&
        RCC_PLLCfg->P_Prescaler != 8)
    {
        RCC_errStatus= Invalid_P_Prescaler; // Invalid P_Prescaler
    }

    // Validate Q_Prescaler (2 ≤ Q ≤ 15)
    else if (RCC_PLLCfg->Q_Prescaler < 2 || RCC_PLLCfg->Q_Prescaler > 15)
    {
        RCC_errStatus= Invalid_Q_Prescaler; // Invalid Q_Prescaler
    }
    else
    {

    // Calculate VCO input frequency based on PLL source
    if (RCC_PLLCfg->PLL_Src == RCC_PLLCFG_PLLSRC_HSI)
    {
        VCO = RCC_HSI_CLK_HZ / RCC_PLLCfg->M_Prescaler;
    }
    else if (RCC_PLLCfg->PLL_Src == RCC_PLLCFG_PLLSRC_HSE)
    {
        VCO = RCC_HSE_CLK_HZ / RCC_PLLCfg->M_Prescaler;
    }
    else
    {
        return RCC_errPLLSrc; // Invalid PLL source
    }

    // Validate VCO input frequency (1 MHz ≤ VCO ≤ 2 MHz)
    if (VCO < 1000000 || VCO > 2000000)
    {
        RCC_errStatus= RCC_errPLLSrc; // Invalid VCO input frequency
    }
    else
    {
    // Configure PLLCFGR with valid parameters
    tmp = (RCC_PLLCfg->PLL_Src) |
          (RCC_PLLCfg->M_Prescaler) |
          (RCC_PLLCfg->N_Multiple << 6) |
          (RCC_PLLCfg->P_Prescaler << 16) |
          (RCC_PLLCfg->Q_Prescaler << 24);

    RCC_Reg->PLLCFGR = tmp;

    /*// Enable PLL
    RCC_Reg->CR |= RCC_PLLON_BIT; // Set PLLON bit

    // Wait for PLL to stabilize with a timeout mechanism
    uint32_t timeout = 1000; // Timeout value 
    while (!(RCC_Reg->CR & RCC_PLLRDY_BIT))
    {
        if (timeout == 0)
        {
            return RCC_enuTimeout; // Return error if timeout occurs
        }
        timeout--;
    }*/
    RCC_errStatus =RCC_noErr ;

    }

 

    }
    return RCC_errStatus;
}


RCC_errStatus_t RCC_SelectSysCLK(uint8_t Copy_u8SysClockSource)
{
    RCC_errStatus_t Ret_enuError = RCC_noErr;
    volatile RCC_Reg_t * RCC_Reg = (volatile RCC_Reg_t *) RCC_BASEADDR;

    // Validate input (acceptable values: 0 for HSI, 1 for HSE, 2 for PLL)
    if (Copy_u8SysClockSource > 2)
    {
        Ret_enuError = RCC_enuInvalidClockSource;
    }
    else
    {
        // Disable PLL if it's the current clock source
        if (Copy_u8SysClockSource == 2)
        {
            // Disable PLL by clearing the PLLON bit
            RCC_Reg->CR &= ~RCC_CR_PLLON;  // Use the mask to clear PLL enable
        }

        // Set System Clock Source
        switch (Copy_u8SysClockSource)
        {
            case RCC_HSI_SYSTEMCLK:  // HSI as System Clock
                // Set the SW bits to select HSI
                RCC_Reg->CFGR &= ~RCC_CFGR_SWS_MSK;    // Clear existing SW bits
                RCC_Reg->CFGR |= RCC_CFGR_SW_HSI;      // Set HSI
                break;

            case RCC_HSE_SYSTEMCLK:  // HSE as System Clock
                // Set the SW bits to select HSE
                RCC_Reg->CFGR &= ~RCC_CFGR_SWS_MSK;    // Clear existing SW bits
                RCC_Reg->CFGR |= RCC_CFGR_SW_HSE;      // Set HSE
                break;

            case RCC_PLL_SYSTEMCLK:  // PLL as System Clock
                // Set the SW bits to select PLL
                RCC_Reg->CFGR &= ~RCC_CFGR_SWS_MSK;    // Clear existing SW bits
                RCC_Reg->CFGR |= RCC_CFGR_SW_PLL;      // Set PLL
                break;

            default:
                Ret_enuError = RCC_enuInvalidClockSource;
                break;
        }
    }
    return Ret_enuError;
}

RCC_errStatus_t RCC_ControlPerClock(uint64_t Bus_Peripheral_ID, uint32_t Status, uint32_t Mode) {
    RCC_errStatus_t Ret_enuError = RCC_noErr;
    volatile RCC_Reg_t *RCC_Reg = (volatile RCC_Reg_t *) RCC_BASEADDR;

    // Extract the BusId (first 4 bits) and PerId (remaining 6 bits)
    uint8_t Copy_u8BusId = GET_BUS_ID(Bus_Peripheral_ID);
    uint8_t Copy_u8PerId = GET_PER_ID(Bus_Peripheral_ID);

    // Validate input
    if (Copy_u8PerId > 31) {
        Ret_enuError = RCC_enuInvalidPerId;
    }
    else if (Copy_u8BusId < RCC_AHB1 || Copy_u8BusId > RCC_APB2) {
        Ret_enuError = RCC_enuInvalidBusId;
    }
    else if (Mode < RCC_NORMAL_MODE || Mode > RCC_SLEEP_MODE) {
        Ret_enuError = RCC_enuInvalidMode;
    }
    else {
        Ret_enuError = RCC_noErr;

        // Determine the correct register and modify the bit for enabling/disabling the clock
        if (Status == RCC_ON) {
            if (Mode == RCC_NORMAL_MODE) {
                switch (Copy_u8BusId) {
                    case RCC_AHB1:
                        RCC_Reg->AHB1ENR |= (1 << Copy_u8PerId);  // Enable clock
                        break;
                    case RCC_AHB2:
                        RCC_Reg->AHB2ENR |= (1 << Copy_u8PerId);  // Enable clock
                        break;
                    case RCC_APB1:
                        RCC_Reg->APB1ENR |= (1 << Copy_u8PerId);  // Enable clock
                        break;
                    case RCC_APB2:
                        RCC_Reg->APB2ENR |= (1 << Copy_u8PerId);  // Enable clock
                        break;
                    default:
                        Ret_enuError = RCC_enuInvalidBusId;
                        break;
                }
            }
            else { // RCC_SLEEP_MODE
                switch (Copy_u8BusId) {
                    case RCC_AHB1:
                        RCC_Reg->AHB1LPENR |= (1 << Copy_u8PerId);  // Enable low-power clock
                        break;
                    case RCC_AHB2:
                        RCC_Reg->AHB2LPENR |= (1 << Copy_u8PerId);  // Enable low-power clock
                        break;
                    case RCC_APB1:
                        RCC_Reg->APB1LPENR |= (1 << Copy_u8PerId);  // Enable low-power clock
                        break;
                    case RCC_APB2:
                        RCC_Reg->APB2LPENR |= (1 << Copy_u8PerId);  // Enable low-power clock
                        break;
                    default:
                        Ret_enuError = RCC_enuInvalidBusId;
                        break;
                }
            }
        }
        else if (Status == RCC_OFF) {
            if (Mode == RCC_NORMAL_MODE) {
                switch (Copy_u8BusId) {
                    case RCC_AHB1:
                        RCC_Reg->AHB1ENR &= ~(1 << Copy_u8PerId);  // Disable clock
                        break;
                    case RCC_AHB2:
                        RCC_Reg->AHB2ENR &= ~(1 << Copy_u8PerId);  // Disable clock
                        break;
                    case RCC_APB1:
                        RCC_Reg->APB1ENR &= ~(1 << Copy_u8PerId);  // Disable clock
                        break;
                    case RCC_APB2:
                        RCC_Reg->APB2ENR &= ~(1 << Copy_u8PerId);  // Disable clock
                        break;
                    default:
                        Ret_enuError = RCC_enuInvalidBusId;
                        break;
                }
            }
            else { // RCC_SLEEP_MODE
                switch (Copy_u8BusId) {
                    case RCC_AHB1:
                        RCC_Reg->AHB1LPENR &= ~(1 << Copy_u8PerId);  // Disable low-power clock
                        break;
                    case RCC_AHB2:
                        RCC_Reg->AHB2LPENR &= ~(1 << Copy_u8PerId);  // Disable low-power clock
                        break;
                    case RCC_APB1:
                        RCC_Reg->APB1LPENR &= ~(1 << Copy_u8PerId);  // Disable low-power clock
                        break;
                    case RCC_APB2:
                        RCC_Reg->APB2LPENR &= ~(1 << Copy_u8PerId);  // Disable low-power clock
                        break;
                    default:
                        Ret_enuError = RCC_enuInvalidBusId;
                        break;
                }
            }
        }
        else {
            Ret_enuError = RCC_enuInvalidStatus;
        }
    }

    return Ret_enuError;
}



RCC_errStatus_t RCC_ControlClock(uint8_t ClockSource, uint8_t Mode)
{
    RCC_errStatus_t Ret_enuError = RCC_noErr; // Initialize return status
    volatile RCC_Reg_t *RCC_Reg = (volatile RCC_Reg_t *)RCC_BASEADDR;

    // Validate input
    if (ClockSource > RCC_PLL )
    {
        Ret_enuError = RCC_enuInvalidClockSource; 
    }
    else if(Mode > RCC_ON)
    {
       Ret_enuError = RCC_enuInvalidMode; 
    }
    else
    {
        // Timeout variable
        uint32_t TimeoutCounter;

        switch (ClockSource)
        {
            case RCC_HSI:
                if (Mode == RCC_ON)
                {
                    RCC_Reg->CR |= (RCC_CR_HSION_MASK); // Enable HSI

                    // Wait until HSI is ready or timeout occurs
                    TimeoutCounter = 1000;
                    while (!(RCC_Reg->CR & RCC_CR_HSIRDY_MASK))
                    {
                        if (--TimeoutCounter == 0)
                        {
                            Ret_enuError = RCC_enuTimeout; // Timeout error
                            break;
                        }
                    }
                }
                else
                {
                    RCC_Reg->CR &= ~(RCC_CR_HSION_MASK); // Disable HSI
                }
                break;

            case RCC_HSE:
                if (Mode == RCC_ON)
                {
                    RCC_Reg->CR |= (RCC_CR_HSEON_MASK); // Enable HSE

                    // Wait until HSE is ready or timeout occurs
                    TimeoutCounter = 1000;
                    while (!(RCC_Reg->CR & RCC_CR_HSERDY_MASK))
                    {
                        if (--TimeoutCounter == 0)
                        {
                            Ret_enuError = RCC_enuTimeout; // Timeout error
                            break;
                        }
                    }
                }
                else
                {
                    RCC_Reg->CR &= ~(RCC_CR_HSEON_MASK); // Disable HSE
                }
                break;

            case RCC_HSE_BYPASS:
                if (Mode == RCC_ON)
                {
                    RCC_Reg->CR |= (RCC_CR_HSEON_MASK | RCC_CR_HSEBYP_MASK); // Enable HSE Bypass and HSE together

                    // Wait until HSE is ready or timeout occurs
                    TimeoutCounter = 1000;
                    while (!(RCC_Reg->CR & RCC_CR_HSERDY_MASK))
                    {
                        if (--TimeoutCounter == 0)
                        {
                            Ret_enuError = RCC_enuTimeout; // Timeout error
                            break;
                        }
                    }
                }
                else
                {
                    RCC_Reg->CR &= ~(RCC_CR_HSEON_MASK | RCC_CR_HSEBYP_MASK); // Disable HSE and HSE Bypass
                }
                break;

            case RCC_PLL:
                if (Mode == RCC_ON)
                {
                    RCC_Reg->CR |= (RCC_CR_PLLON_MASK); // Enable PLL

                    // Wait until PLL is ready or timeout occurs
                    TimeoutCounter = 1000;
                    while (!(RCC_Reg->CR & RCC_CR_PLLRDY_MASK))
                    {
                        if (--TimeoutCounter == 0)
                        {
                            Ret_enuError = RCC_enuTimeout; // Timeout error
                            break;
                        }
                    }
                }
                else
                {
                    RCC_Reg->CR &= ~(RCC_CR_PLLON_MASK); // Disable PLL
                }
                break;

            default:
                Ret_enuError = RCC_enuInvalidClockSource; // Invalid Clock Source
                break;
        }
    }

    return Ret_enuError; // Always return the status here
}


/*




RCC_errStatus_t RCC_enuEnableClock(uint8_t Copy_u8BusId, uint8_t Copy_u8PerId, uint8_t Copy_u8Mode)
{
    RCC_errStatus_t Ret_enuError = RCC_noErr;
    volatile RCC_Reg_t * RCC_Reg = (volatile RCC_Reg_t *) RCC_BASEADDR;

    // Validate Peripheral ID
    if (Copy_u8PerId > RCC_PER_ID_MAX)
    {
        Ret_enuError= RCC_enuInvalidPerId;
    }

    // Validate Bus ID
    else if (Copy_u8BusId < RCC_AHB1 || Copy_u8BusId > RCC_APB2)
    {
        Ret_enuError= RCC_enuInvalidBusId;
    }

    // Validate Mode
    else if (Copy_u8Mode < RCC_NORMAL_MODE || Copy_u8Mode > RCC_SLEEP_MODE)
    {
        Ret_enuError= RCC_enuInvalidMode;
    }
    else
    {
    Ret_enuError = RCC_noErr;

    // Enable clock based on mode and bus ID using masks
    if (Copy_u8Mode == RCC_NORMAL_MODE)
    {
        switch (Copy_u8BusId)
        {
            case RCC_AHB1: 
                RCC_Reg->AHB1ENR |= (1 << Copy_u8PerId); 
                break;
            case RCC_AHB2: 
                RCC_Reg->AHB2ENR |= (1 << Copy_u8PerId); 
                break;
            case RCC_APB1: 
                RCC_Reg->APB1ENR |= (1 << Copy_u8PerId); 
                break;
            case RCC_APB2: 
                RCC_Reg->APB2ENR |= (1 << Copy_u8PerId); 
                break;
        }
    }
    else // Sleep mode
    {
        switch (Copy_u8BusId)
        {
            case RCC_AHB1: 
                RCC_Reg->AHB1LPENR |= (1 << Copy_u8PerId); 
                break;
            case RCC_AHB2: 
                RCC_Reg->AHB2LPENR |= (1 << Copy_u8PerId); 
                break;
            case RCC_APB1: 
                RCC_Reg->APB1LPENR |= (1 << Copy_u8PerId); 
                break;
            case RCC_APB2: 
                RCC_Reg->APB2LPENR |= (1 << Copy_u8PerId); 
                break;
        }
    }
    }
    return Ret_enuError;
}



RCC_errStatus_t RCC_enuDisableClock(uint8_t Copy_u8BusId, uint8_t Copy_u8PerId, uint8_t Copy_u8Mode)
{
    RCC_errStatus_t Ret_enuError = RCC_noErr;
    volatile RCC_Reg_t * RCC_Reg = (volatile RCC_Reg_t *) RCC_BASEADDR;

    // Validate Peripheral ID
    if (Copy_u8PerId > RCC_PER_ID_MAX)
    {
        Ret_enuError= RCC_enuInvalidPerId;
    }

    // Validate Bus ID
    else if (Copy_u8BusId < RCC_AHB1 || Copy_u8BusId > RCC_APB2)
    {
        Ret_enuError = RCC_enuInvalidBusId;
    }

    // Validate Mode
    else if (Copy_u8Mode < RCC_NORMAL_MODE || Copy_u8Mode > RCC_SLEEP_MODE)
    {
        Ret_enuError = RCC_enuInvalidMode;
    }
    else
    {

    

    Ret_enuError = RCC_noErr;

    // Disable clock based on mode and bus ID using masks
    if (Copy_u8Mode == RCC_NORMAL_MODE)
    {
        switch (Copy_u8BusId)
        {
            case RCC_AHB1: 
                RCC_Reg->AHB1ENR &= ~(1 << Copy_u8PerId); 
                break;
            case RCC_AHB2: 
                RCC_Reg->AHB2ENR &= ~(1 << Copy_u8PerId); 
                break;
            case RCC_APB1: 
                RCC_Reg->APB1ENR &= ~(1 << Copy_u8PerId); 
                break;
            case RCC_APB2: 
                RCC_Reg->APB2ENR &= ~(1 << Copy_u8PerId); 
                break;
        }
    }
    else // Sleep mode
    {
        switch (Copy_u8BusId)
        {
            case RCC_AHB1: 
                RCC_Reg->AHB1LPENR &= ~(1 << Copy_u8PerId); 
                break;
            case RCC_AHB2: 
                RCC_Reg->AHB2LPENR &= ~(1 << Copy_u8PerId); 
                break;
            case RCC_APB1: 
                RCC_Reg->APB1LPENR &= ~(1 << Copy_u8PerId); 
                break;
            case RCC_APB2: 
                RCC_Reg->APB2LPENR &= ~(1 << Copy_u8PerId); 
                break;
        }
    }
    }
    return Ret_enuError;
}


*/