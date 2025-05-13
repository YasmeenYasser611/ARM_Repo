#include"NVIC_private.h"
#include"NVIC.h"
#include"STD_TYPES.h"

#define IS_PRIORITY_GROUPING(PG) ((PG==Group_priorities_16)||(PG==Group_priorities_8)||(PG==Group_priorities_4)||(PG==Group_priorities_2)||(PG==Group_priorities_NONE))

NVIC_errStatus_t NVIC_EnableIRQ(IRQn_t IRQn )
{

    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type * NVIC_Reg = (volatile NVIC_Type *) NVIC_BASEADDR;

    // Check if the IRQ number is valid (assuming the valid range is 0-239)
    if (IRQn < 0 || IRQn >= 240) {
        Ret_errStatus= NVIC_ERROR_INVALID_IRQ;  // Invalid IRQ number
    }
    else
    {
    // Enable the interrupt by setting the corresponding bit in ISER
    uint32_t registerIndex = IRQn / 32U;   // Determine which ISER register to use
    uint32_t bitIndex = IRQn % 32U;        // Determine the bit index within that register
    
    // Set the appropriate bit in the ISER register
    NVIC_Reg->ISER[registerIndex] = (1U << bitIndex);
    }
    return Ret_errStatus;
}



NVIC_errStatus_t NVIC_DisableIRQ(IRQn_t IRQn)
{

    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type * NVIC_Reg = (volatile NVIC_Type *) NVIC_BASEADDR;

    // Check if the IRQ number is valid (assuming the valid range is 0-239)
    if (IRQn < 0 || IRQn >= 240) {
        Ret_errStatus= NVIC_ERROR_INVALID_IRQ;  // Invalid IRQ number
    }
    else
    {
    // Enable the interrupt by setting the corresponding bit in ISER
    uint32_t registerIndex = IRQn / 32U;   // Determine which ISER register to use
    uint32_t bitIndex = IRQn % 32U;        // Determine the bit index within that register
    
    // Set the appropriate bit in the ISER register
    NVIC_Reg->ICER[registerIndex] = (1U << bitIndex);
    }
    return Ret_errStatus;
}


NVIC_errStatus_t NVIC_SetPendingIRQ (IRQn_t IRQn)
{

    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type * NVIC_Reg = (volatile NVIC_Type *) NVIC_BASEADDR;

    // Check if the IRQ number is valid (assuming the valid range is 0-239)
    if (IRQn < 0 || IRQn >= 240) {
        Ret_errStatus= NVIC_ERROR_INVALID_IRQ;  // Invalid IRQ number
    }
    else
    {
    // Enable the interrupt by setting the corresponding bit in ISER
    uint32_t registerIndex = IRQn / 32U;   // Determine which ISER register to use
    uint32_t bitIndex = IRQn % 32U;        // Determine the bit index within that register
    
    // Set the appropriate bit in the ISER register
    NVIC_Reg->ISPR[registerIndex] = (1U << bitIndex);
    }
    return Ret_errStatus;
}

NVIC_errStatus_t NVIC_ClearPendingIRQ (IRQn_t IRQn)
{

    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type * NVIC_Reg = (volatile NVIC_Type *) NVIC_BASEADDR;

    // Check if the IRQ number is valid (assuming the valid range is 0-239)
    if (IRQn < 0 || IRQn >= 240) {
        Ret_errStatus= NVIC_ERROR_INVALID_IRQ;  // Invalid IRQ number
    }
    else
    {
    // Enable the interrupt by setting the corresponding bit in ISER
    uint32_t registerIndex = IRQn / 32U;   // Determine which ISER register to use
    uint32_t bitIndex = IRQn % 32U;        // Determine the bit index within that register
    
    // Set the appropriate bit in the ISER register
    NVIC_Reg->ICPR[registerIndex] = (1U << bitIndex);
    }
    return Ret_errStatus;
}

NVIC_errStatus_t NVIC_GetPendingIRQ (IRQn_t IRQn , uint32_t* Add_pu32PendingIRQ)
{

    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type * NVIC_Reg = (volatile NVIC_Type *) NVIC_BASEADDR;

    // Check if the IRQ number is valid (assuming the valid range is 0-239)
    if (IRQn < 0 || IRQn >= 240) {
        Ret_errStatus= NVIC_ERROR_INVALID_IRQ;  // Invalid IRQ number
    }
    else if (Add_pu32PendingIRQ == NULL)
    {
        Ret_errStatus= NVIC_ERROR_NULL_POINTER;  // Pointer to return value is NULL
    }
    else
    {
    // Enable the interrupt by setting the corresponding bit in ISER
    uint32_t registerIndex = IRQn / 32U;   // Determine which ISER register to use
    uint32_t bitIndex = IRQn % 32U;        // Determine the bit index within that register
    
    // Set the appropriate bit in the ISER register
    *Add_pu32PendingIRQ = (NVIC_Reg->ISPR[registerIndex] >> bitIndex) & 0x1U;
    }
    return Ret_errStatus;
}

NVIC_errStatus_t NVIC_GetActive (IRQn_t IRQn , uint32_t* Add_pu32Active)
{

    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type * NVIC_Reg = (volatile NVIC_Type *) NVIC_BASEADDR;

    // Check if the IRQ number is valid (assuming the valid range is 0-239)
    if (IRQn < 0 || IRQn >= 240) {
        Ret_errStatus= NVIC_ERROR_INVALID_IRQ;  // Invalid IRQ number
    }
    else if (Add_pu32Active == NULL)
    {
        Ret_errStatus= NVIC_ERROR_NULL_POINTER;  // Pointer to return value is NULL
    }
    else
    {
    // Enable the interrupt by setting the corresponding bit in ISER
    uint32_t registerIndex = IRQn / 32U;   // Determine which ISER register to use
    uint32_t bitIndex = IRQn % 32U;        // Determine the bit index within that register
    
    // Set the appropriate bit in the ISER register
    *Add_pu32Active = (NVIC_Reg->IABR[registerIndex] >> bitIndex) & 0x1U;
    }
    return Ret_errStatus;
}


NVIC_errStatus_t NVIC_SetPriority (IRQn_t IRQn, uint32_t priority)
{

    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type * NVIC_Reg = (volatile NVIC_Type *) NVIC_BASEADDR;

    // Check if the IRQ number is valid (assuming the valid range is 0-239)
    if (IRQn < 0 || IRQn >= 240) {
        Ret_errStatus= NVIC_ERROR_INVALID_IRQ;  // Invalid IRQ number
    }
    else if (priority < 0 || priority > 255)
    {
        return NVIC_ERROR_INVALID_PRIORITY;  // Invalid priority value
    }
    else
    {
        // Each IPR register holds 1 byte (8 bits) for each IRQ priority.
        // The processor only implements bits [7:4], so we shift priority.
        NVIC_Reg->IPR[IRQn] = (uint8_t)(priority << 4);
    }
    return Ret_errStatus;

}

NVIC_errStatus_t NVIC_GetPriority (IRQn_t IRQn , uint32_t* Add_pu32Priority)
{
    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type * NVIC_Reg = (volatile NVIC_Type *) NVIC_BASEADDR;

    // Check if the IRQ number is valid (assuming the valid range is 0-239)
    if (IRQn < 0 || IRQn >= 240) {
        Ret_errStatus= NVIC_ERROR_INVALID_IRQ;  // Invalid IRQ number
    }
    else if (Add_pu32Priority == NULL)
    {
        Ret_errStatus= NVIC_ERROR_NULL_POINTER;  // Pointer to return value is NULL
    }
    else
    {
        
        // Calculate the register index for the IPR array
        uint32_t registerIndex = (uint32_t)IRQn; // Direct index since IPR is byte-addressable

        // Extract only the implemented priority bits [7:4] (upper 4 bits of 8-bit priority field)
        *Add_pu32Priority = (NVIC_Reg->IPR[registerIndex] >> 4) & 0xF;
    }
    return Ret_errStatus;
}


NVIC_errStatus_t NVIC_SetSoftwareInterrupt(IRQn_t IRQn) 
{
    NVIC_errStatus_t Ret_errStatus = NVIC_noErr;
    volatile NVIC_Type *NVIC_Reg = (volatile NVIC_Type *)NVIC_BASEADDR;

    // Check if the IRQ number is valid (0-239) - STIR only supports external interrupts
    if (IRQn < 0 || IRQn >= 240) 
    {
        Ret_errStatus = NVIC_ERROR_INVALID_IRQ;
    }
    else 
    {
        // Writing the IRQ number to STIR triggers a software interrupt
        NVIC_Reg->STIR = (uint32_t)IRQn;
    }
    
    return Ret_errStatus;
}

NVIC_errStatus_t NVIC_SetPriorityGrouping(NVIC_enuPriority_Grouping priority_grouping){
    NVIC_errStatus_t Ret_errStatus=NVIC_noErr;
    volatile SCB_Type *SCB_REG = (volatile SCB_Type *)SCB_BASEADDR;

    if(!IS_PRIORITY_GROUPING(priority_grouping))
    {
        Ret_errStatus = NVIC_ERORR_INVALID_PRIORITY_GROUPING;
    }
    else
    {
        uint32_t Local_uint32AIRCR = SCB_REG->AIRCR;
        Local_uint32AIRCR &= (~0x00000700); //clear first 
        Local_uint32AIRCR |= (priority_grouping << 8); //set priority grouping
        SCB_REG->AIRCR=Local_uint32AIRCR;
    }
    return Ret_errStatus;
}



NVIC_errStatus_t NVIC_GetPriorityGrouping(NVIC_enuPriority_Grouping priority_grouping ,uint32_t * Add_pu8PriorityGrouping ){
    NVIC_errStatus_t Ret_errStatus=NVIC_noErr;
    volatile SCB_Type *SCB_REG = (volatile SCB_Type *)SCB_BASEADDR;

    if(!IS_PRIORITY_GROUPING(priority_grouping))
    {
        Ret_errStatus = NVIC_ERORR_INVALID_PRIORITY_GROUPING;
    }
    else if (Add_pu8PriorityGrouping == NULL)
    {
        Ret_errStatus= NVIC_ERROR_NULL_POINTER;  // Pointer to return value is NULL
    }
    else
    {
        *Add_pu8PriorityGrouping =  ((SCB_REG->AIRCR)>>8)& 0x00000007;
    }
    return Ret_errStatus;
}




void NVIC_SystemReset(void)
{
    volatile SCB_Type *SCB_REG = (volatile SCB_Type *)SCB_BASEADDR;
    SCB_REG->AIRCR |= 0x00000004;
    
}