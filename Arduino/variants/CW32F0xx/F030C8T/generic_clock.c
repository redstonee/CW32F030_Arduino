/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#include "pins_arduino.h"
#include "cw32yyxx_rcc.h"
#include "cw32yyxx_flash.h"
#include "cw32_def.h"
/**
 * @brief  System Clock Configuration
 * @param  None
 * @retval None
 */
WEAK void SystemClock_Config(void)
{
  RCC_HSI_Enable(RCC_HSIOSC_DIV6);           // HSI = 48MHz, DIV6 -> 8MHz
  RCC_PLL_Enable(RCC_PLLSOURCE_HSI, 8e6, 8); // 8MHz -> 64MHz

  RCC_HCLKPRS_Config(RCC_HCLK_DIV1);
  RCC_PCLKPRS_Config(RCC_PCLK_DIV1);
  RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_FLASH, ENABLE);
  FLASH_SetLatency(FLASH_Latency_3);
  RCC_SysClk_Switch(RCC_SYSCLKSRC_PLL);
  RCC_SystemCoreClockUpdate(64e6);
}
