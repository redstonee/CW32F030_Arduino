/**
 *******************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * This software component is licensed by WCH under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#include "clock.h"
#include "cw32yyxx_rcc.h"
#include"cw32yyxx_systick.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TICK_FREQ_1KHz    1L
// #define TICK_FREQ_100Hz   10L
// #define TICK_FREQ_10Hz    100L 


/**
  * @brief  Function called wto read the current millisecond
  * @param  None
  * @retval None
  */
uint32_t getCurrentMillis(void)
{
  return GetTick();
}


#if defined(CW32F030) 

uint32_t getCurrentMicros(void)
{
  
  uint64_t m0 = GetTick();
  __IO uint64_t u0 = SysTick->VAL;
  uint64_t m1 = GetTick();
  __IO uint32_t u1 = SysTick->VAL;   //may be a interruption
   uint64_t tms = SysTick->LOAD + 1;

  if (m1 != m0) {
    return (m1 * 1000 + ((tms - u1) * 1000) / tms);
  } else {
    return (m0 * 1000 + ((tms - u0) * 1000) / tms);
  }
}

#endif

#ifdef __cplusplus
}
#endif


