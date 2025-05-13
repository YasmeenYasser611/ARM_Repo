
#include "RCC.h"
#include "gpio.h"
#include "HLED_config.h"
#include "STD_TYPES.h"

#define IS_INVALID_LED_NAME(X)			((((uint8_t)X) > Num_of_Led) || (((uint8_t)X) < 0))
#define IS_INVALID_LED_VALUE(X)			((((HLED_enuState_t)X) > HLED_enuOFF) || (((HLED_enuState_t)X) < HLED_enuON))

extern HLED_strLedCONFG_t HLED_enuArrLedCongf[Num_of_Led];


void HLED_vLED_init(void)
{
	uint8_t Local_u8_i=0;
	for(Local_u8_i =0 ; Local_u8_i < Num_of_Led ; Local_u8_i++)
	{
		RCC_ControlPerClock(HLED_enuArrLedCongf[Local_u8_i].CLOCK_BUS , RCC_ON , HLED_enuArrLedCongf[Local_u8_i].CLOCK_MODE);
		GPIO_voidSetPinDirection(HLED_enuArrLedCongf[Local_u8_i].PORT , HLED_enuArrLedCongf[Local_u8_i].PIN , HLED_enuArrLedCongf[Local_u8_i].MODE);
	}
}


HLED_enuErrorStatus_t HLED_enuSetLedState( uint8_t Copy_u8LedName, HLED_enuState_t Copy_enuState)
{
	GPIO_enuErrorStatus_t Ret_enuError = HLED_enuNOK;
	
	// Validate input parameters
	if (IS_INVALID_LED_NAME(Copy_u8LedName))
	{
		Ret_enuError =HLED_enuINVALID_LEDName ;
		
	}
	else if (IS_INVALID_LED_VALUE(Copy_enuState))
	{
		Ret_enuError = HLED_enuINVALID_LEDValue;
	}
	else
	{
		Ret_enuError = HLED_enuOK;
		if(HLED_enuArrLedCongf[Copy_u8LedName].CONNECTION == HLED_enuForward)
		{
			if(Copy_enuState == HLED_enuON)
			{
				 Ret_enuError = GPIO_voidSetPinValue(HLED_enuArrLedCongf[Copy_u8LedName].PORT ,HLED_enuArrLedCongf[Copy_u8LedName].PIN , GPIO_HIGH);
			}
			else if(Copy_enuState == HLED_enuOFF)
			{
				Ret_enuError = GPIO_voidSetPinValue(HLED_enuArrLedCongf[Copy_u8LedName].PORT ,HLED_enuArrLedCongf[Copy_u8LedName].PIN , GPIO_LOW);
			}
		}
		else if(HLED_enuArrLedCongf[Copy_u8LedName].CONNECTION == HLED_enuReverse)
		{
			if(Copy_enuState == HLED_enuON)
			{
				Ret_enuError = GPIO_voidSetPinValue(HLED_enuArrLedCongf[Copy_u8LedName].PORT ,HLED_enuArrLedCongf[Copy_u8LedName].PIN , GPIO_LOW);
			}
			else if(Copy_enuState == HLED_enuOFF)
			{
				Ret_enuError = GPIO_voidSetPinValue(HLED_enuArrLedCongf[Copy_u8LedName].PORT ,HLED_enuArrLedCongf[Copy_u8LedName].PIN , GPIO_HIGH);
			}
		}
		else
		{
			Ret_enuError = HLED_enuINVALID_LEDConnection;
		}
		
	   

	}
	return Ret_enuError;
}