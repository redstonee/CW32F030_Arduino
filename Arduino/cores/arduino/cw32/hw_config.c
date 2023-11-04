
#include "hw_config.h"
#include "clock.h"

#ifdef __cplusplus
extern "C" {
#endif

void systick_init(void)
{
    SysTick->CTRL= 0;
    SysTick->VAL = 0;
    SysTick->LOAD = SystemCoreClock / 1000 - 1;
    SysTick->CTRL= 0xF;
    NVIC_SetPriority(SysTick_IRQn,0xFF);
    NVIC_EnableIRQ(SysTick_IRQn);
}

/**
  * @brief  This function performs the global init of the system (HAL, IOs...)
  * @param  None
  * @retval None
  */

void hw_config_init(void)
{
  systick_init();
}
#ifdef __cplusplus
}
#endif


