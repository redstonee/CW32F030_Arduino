/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 Modified 1 may 2023 by TempersLee
 */
#include "PortNames.h"

GPIO_TypeDef *GPIOPort[MAX_NB_PORT] = {
    CW_GPIOA
#if defined GPIOB_BASE
    ,
    CW_GPIOB
#endif
#if defined GPIOC_BASE
    ,
    CW_GPIOC
#endif
#if defined GPIOD_BASE
    ,
    CW_GPIOD
#endif
#if defined GPIOE_BASE
    ,
    CW_GPIOE
#endif
#if defined GPIOF_BASE
    ,
    CW_GPIOF
#endif

};

/* Enable GPIO clock and return GPIO base address */
GPIO_TypeDef *set_GPIO_Port_Clock(uint32_t port_idx)
{
  GPIO_TypeDef *gpioPort = 0;
  switch (port_idx)
  {
  case PortA:
    gpioPort = CW_GPIOA;
    __RCC_GPIOA_CLK_ENABLE();

    break;
#if defined GPIOB_BASE
  case PortB:
    gpioPort = CW_GPIOB;
    __RCC_GPIOB_CLK_ENABLE();

    break;
#endif
#if defined GPIOC_BASE
  case PortC:
    gpioPort = CW_GPIOC;
    __RCC_GPIOC_CLK_ENABLE();

    break;
#endif
#if defined GPIOD_BASE
  case PortD:
    gpioPort = CW_GPIOD;
        __RCC_GPIOD_CLK_ENABLE();

    break;
#endif
#if defined GPIOE_BASE
  case PortE:
    gpioPort = CW_GPIOE;
        __RCC_GPIOE_CLK_ENABLE();

    break;
#endif
#if defined GPIOF_BASE
  case PortF:
    gpioPort = CW_GPIOF;
        __RCC_GPIOF_CLK_ENABLE();

    break;
#endif
  default:
    // wrong port number
    // TBD: error management
    gpioPort = 0;
    break;
  }
  return gpioPort;
}
