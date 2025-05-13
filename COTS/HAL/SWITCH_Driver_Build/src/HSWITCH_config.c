
#include "HSWITCH_config.h"

HSWITCH_strSwitchCONFG_t HSWITCH_enuArrSwitchConf[Num_of_Switch] =
{
    [Switch_start] = {
        .PORT = HSWITCH_enuPORTB,
        .PIN = HSWITCH_enuPIN0,
        .MODE = INPUT_PU, 
        .CLOCK_BUS = RCC_AHB1_GPIOB,
        .CLOCK_MODE = RCC_NORMAL_MODE
    },
    [Switch_stop] = {
        .PORT = HSWITCH_enuPORTB,
        .PIN = HSWITCH_enuPIN1,
        .MODE = INPUT_PD, 
        .CLOCK_BUS = RCC_AHB1_GPIOB,
        .CLOCK_MODE = RCC_NORMAL_MODE
    }
};
