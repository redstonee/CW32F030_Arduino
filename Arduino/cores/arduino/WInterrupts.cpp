/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "WInterrupts.h"
#include "Arduino.h"
#include "PinAF.h"

#include "interrupt.h"


#if !defined(EXTI_MODULE_DISABLED)

void attachInterrupt(uint32_t pin, void (*callback)(void),uint32_t trigger_mode)
{
  PinName p = digitalPinToPinName(pin);
  GPIO_TypeDef* port = set_GPIO_Port_Clock(CW_PORT(p));
  if (!port) return ;

  cw32_interrupt_enable(port,  CW_GPIO_PIN(p), callback, trigger_mode);
}


void detachInterrupt(uint32_t pin)
{
  PinName p = digitalPinToPinName(pin);
  GPIO_TypeDef* port = get_GPIO_Port(CW_PORT(p));
  if (!port)
	  return;
  cw32_interrupt_disable(port, CW_GPIO_PIN(p));
}

#endif