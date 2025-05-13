#include "HLED.h"
//#include"RCC.h"
//#include"gpio.h"

int main(void)
{
	  //RCC_ControlClock(RCC_HSI,RCC_ON);
    //RCC_SelectSysCLK(RCC_HSI_SYSTEMCLK);
    //RCC_ControlPerClock(RCC_AHB1_GPIOA , RCC_ON , RCC_NORMAL_MODE);
	  HLED_vLED_init(); 
    while (1) 
    {
		HLED_enuSetLedState( Led_start, HLED_enuON);
		HLED_enuSetLedState( Led_stop, HLED_enuON);
    //GPIO_voidSetPinDirection(GPIO_A , PIN1 , OUTPUT_PP_PU);
    //GPIO_voidSetPinValue(GPIO_A , PIN1 , GPIO_HIGH);
		
		
    }
}
