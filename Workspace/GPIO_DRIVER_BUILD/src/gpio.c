#include"STD_TYPES.h"

#include"gpio.h"
#include"gpio_private.h"
#include"gpio_confog.h"

GPIO_enuErrorStatus_t GPIO_voidSetPinDirection(uint8_t copy_u8PORT, uint8_t copy_u8PIN, uint32_t copy_u32MODE)
{
    GPIO_enuErrorStatus_t Ret_enuError = GPIO_enuOK;

    // Step 1: Validate inputs
    if (copy_u8PORT < GPIO_A || copy_u8PORT > GPIO_H)
    {
        Ret_enuError = GPIO_enuINVALIDPORT;
    }
    else if (copy_u8PIN < PIN0 || copy_u8PIN > PIN15)
    {
        Ret_enuError = GPIO_enuINVALIDPIN;
    }
    else if ((copy_u32MODE & 0x03) != GPIO_MODE_INPUT && 
             (copy_u32MODE & 0x03) != GPIO_MODE_OUTPUT && 
             (copy_u32MODE & 0x03) != GPIO_MODE_AF && 
             (copy_u32MODE & 0x03) != GPIO_MODE_ANALOG)
    {
        Ret_enuError = GPIO_enuINVALIDMODE;
    }
    else
    {
        // Step 2: Get the port base address
        GPIO_Reg_t* Local_strPtrCurrPort = GPIO_PORT(copy_u8PORT);

        // Step 3: Extract mode, output type, pull-up/down from the input mode
        uint8_t mode   = (copy_u32MODE >> 0) & 0x03;  // Bits 0-1: Mode (00: Input, 01: Output, 10: AF, 11: Analog)
        uint8_t otype  = (copy_u32MODE >> 2) & 0x01;  // Bit 2: Output type (0: Push-pull, 1: Open-drain)
        uint8_t pupd   = (copy_u32MODE >> 3) & 0x03;  // Bits 3-4: Pull-up/pull-down (00: None, 01: Pull-up, 10: Pull-down)

        // Step 4: Configure the MODER register (set pin mode: input, output, alternate function, analog)
        Local_strPtrCurrPort->MODER &= ~(0x3U << (copy_u8PIN * 2));  // Clear mode bits for this pin
        Local_strPtrCurrPort->MODER |= (mode << (copy_u8PIN * 2));   // Set the mode bits

        // Step 5: Configure the OTYPER register (output type: push-pull or open-drain)
        // Step 6: Configure speed (only for output and AF modes)
        if (mode == GPIO_MODE_OUTPUT || mode == GPIO_MODE_AF)
        {
            Local_strPtrCurrPort->OTYPER &= ~(1U << copy_u8PIN);  // Clear the output type for this pin
            Local_strPtrCurrPort->OTYPER |= (otype << copy_u8PIN);  // Set the output type (push-pull or open-drain)

            Local_strPtrCurrPort->OSPEEDR &= ~(0x3U << (copy_u8PIN * 2));  // Clear speed bits for this pin

            // Check if speed is defined in config.h
            #ifdef GPIO_SPEED_SELECTED
                // Use the user-defined speed from config.h
                Local_strPtrCurrPort->OSPEEDR |= (GPIO_SPEED_SELECTED << (copy_u8PIN * 2));  // Set the selected speed
            #else
                // If speed is not defined, default to low speed (0)
                Local_strPtrCurrPort->OSPEEDR |= (0x0U << (copy_u8PIN * 2));  // Low speed by default
            #endif
        }
        // Step 7: Configure the PUPDR register (set pull-up or pull-down)
        Local_strPtrCurrPort->PUPDR &= ~(0x3U << (copy_u8PIN * 2));  // Clear pull-up/pull-down bits for this pin
        Local_strPtrCurrPort->PUPDR |= (pupd << (copy_u8PIN * 2));   // Set pull-up/pull-down configuration
    }

    return Ret_enuError;
}




GPIO_enuErrorStatus_t GPIO_voidSetPinValue(uint8_t copy_u8PORT , uint8_t copy_u8PIN , uint8_t copy_u8VALUE)
{
     GPIO_enuErrorStatus_t Ret_enuError = GPIO_enuOK;

    // Step 1: Validate inputs
    if (copy_u8PORT < GPIO_A || copy_u8PORT > GPIO_H)
    {
        Ret_enuError = GPIO_enuINVALIDPORT;
    }
    else if (copy_u8PIN < PIN0 || copy_u8PIN > PIN15)
    {
        Ret_enuError = GPIO_enuINVALIDPIN;
    }
    else if (copy_u8VALUE < GPIO_LOW|| copy_u8VALUE > GPIO_HIGH)
    {
        Ret_enuError = GPIO_enuINVALIDPINVALUE;
    }
    else
    {
        // Step 1: Get the port base address
        GPIO_Reg_t* Local_strPtrCurrPort = GPIO_PORT(copy_u8PORT);
        // Step 2: Set or reset the pin value
        if (copy_u8VALUE == GPIO_HIGH)
        {
            // Set the pin high
            Local_strPtrCurrPort->BSRR =  (1U << copy_u8PIN);  // Set the bit corresponding to the pin
        }
        else
        {
            // Set the pin low
            Local_strPtrCurrPort->BSRR =  (1U << (copy_u8PIN + 16));  // Reset the bit corresponding to the pin (BSRR reset part)
        }

    }
    return Ret_enuError;

}

GPIO_enuErrorStatus_t GPIO_enuGetPinValue(uint8_t copy_u8PORT , uint8_t copy_u8PIN , uint8_t* Add_pu8PinValue)
{
    GPIO_enuErrorStatus_t Ret_enuError = GPIO_enuOK;

    // Step 1: Validate inputs
    if (copy_u8PORT < GPIO_A || copy_u8PORT > GPIO_H)
    {
        Ret_enuError = GPIO_enuINVALIDPORT;
    }
    else if (copy_u8PIN < PIN0 || copy_u8PIN > PIN15)
    {
        Ret_enuError = GPIO_enuINVALIDPIN;
    }
    else if (Add_pu8PinValue == NULL_PTR)
    {
        Ret_enuError = GPIO_enuNULLPTR;
    }
    else
    {
        // Step 2: Get the port base addres s
        GPIO_Reg_t* Local_strPtrCurrPort = GPIO_PORT(copy_u8PORT);

        // Step 3: Read the pin value from the IDR register
        *Add_pu8PinValue = (Local_strPtrCurrPort->IDR >> copy_u8PIN) & 0x01;  // Mask and shift the pin value
    }

    return Ret_enuError;
}
