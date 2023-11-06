#define ARDUINO_MAIN

#include "Arduino.h"
#include "cw32f030_systick.h"

/*
 * \brief Main entry point of Arduino application
 */
int main(void)
{
    SystemClock_Config();
    InitTick(RCC_Sysctrl_GetHClkFreq());

    setup();

    do
    {
        loop();

    } while (1);

    return 0;
}
