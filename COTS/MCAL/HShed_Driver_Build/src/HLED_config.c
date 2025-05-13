/*
 * HLED_config.c
 *
 * Created: 1/2/2025 3:07:35 PM
 *  Author: TUF
 */ 

#include "STD_TYPES.h"
#include "HLED_config.h"


HLED_strLedCONFG_t HLED_enuArrLedCongf[Num_of_Led] =
{
	[Led1] = {
		.PORT = HLED_enuPORTA,
		.PIN = HLED_enuPIN0,
		.MODE= OUTPUT_PP_PU, 
		.CLOCK_BUS = RCC_AHB1_GPIOA,
		.CLOCK_MODE = RCC_NORMAL_MODE,
		.CONNECTION = HLED_enuForward
	},
	[Led2] = {
		.PORT = HLED_enuPORTA,
		.PIN = HLED_enuPIN1,
		.MODE= OUTPUT_PP_PU, 
		.CLOCK_BUS = RCC_AHB1_GPIOA,
		.CLOCK_MODE = RCC_NORMAL_MODE,
		.CONNECTION = HLED_enuForward
	},
	[Led3] = {
		.PORT = HLED_enuPORTA,
		.PIN = HLED_enuPIN2,
		.MODE= OUTPUT_PP_PU, 
		.CLOCK_BUS = RCC_AHB1_GPIOA,
		.CLOCK_MODE = RCC_NORMAL_MODE,
		.CONNECTION = HLED_enuForward
	}
};
