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
#include "pinmap.h"
#include "pinconfig.h"
#include "cw32yyxx_gpio.h"
#include "system_cw32yyxx.h"

typedef struct
{
  PinName pin;
  uint32_t LL_AnalogSwitch;
} PinAnalogSwitch;

#if defined(CW32F030)
const uint32_t pin_map[16] = {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8, 
    GPIO_PIN_9, 
    GPIO_PIN_10, 
    GPIO_PIN_11, 
    GPIO_PIN_12, 
    GPIO_PIN_13, 
    GPIO_PIN_14, 
    GPIO_PIN_15

};

#endif

bool pin_in_pinmap(PinName pin, const PinMap *map)
{
  if (pin != (PinName)NC)
  {
    while (map->pin != NC)
    {
      if (map->pin == pin)
      {
        return true;
      }
      map++;
    }
  }
  return false;
}

/**
 * Configure pin (mode, speed, output type and pull-up/pull-down)
 */
void pin_function(PinName pin, int function)
{
  /* Get the pin information */
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  uint32_t mode = CW_PIN_MODE(function);
  uint32_t cnf = CW_PIN_CNF(function);
  uint32_t pupd = CW_PIN_PUPD(function);
  uint32_t afnum = CW_PIN_AFNUM(function);
  uint32_t port = CW_PORT(pin);
  uint32_t cw_pinx = CW_MAP_GPIO_PIN(pin);

  if (pin == (PinName)NC)
  {
    return;
  }

  /* Enable GPIO clock */
  GPIO_TypeDef *gpio = set_GPIO_Port_Clock(port);
  /* if have afnum, initial */
  if (afnum)
    pin_SetCWAFPin(afnum);

  if (mode) // output with speed seting
  {
    GPIO_InitStructure.Speed = mode;
    switch (cnf)
    {
    case CW_CNF_OUTPUT_PP:
      GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
      break;
    case CW_CNF_OUTPUT_OD:
      GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
      break;
    case CW_CNF_OUTPUT_AFPP:
      GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
      break;
    case CW_CNF_OUTPUT_AFOD:
      GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
      break;
    default:
      GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
      break;
    }
  }
  else // input
  {
    switch (cnf)
    {
    case CW_CNF_INPUT_ANALOG:
      GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
      break;
    case CW_CNF_INPUT_FLOAT:
      GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
      break;
    case CW_CNF_INPUT_PUPD:
      if (pupd == PULLUP)
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
      else if (pupd == PILLDOWN)
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLDOWN;
      else
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLDOWN;
      break;
    default:
      GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLDOWN;
      break;
    }
  }


  GPIO_InitStructure.Pins = (uint16_t)cw_pinx;
  GPIO_Init(gpio, &GPIO_InitStructure);
}

void pinmap_pinout(PinName pin, const PinMap *map)
{
  if (pin == NC)
  {
    return;
  }

  while (map->pin != NC)
  {
    if (map->pin == pin)
    {
      pin_function(pin, map->function);
      return;
    }
    map++;
  }
  // Error_Handler();
}

void *pinmap_find_peripheral(PinName pin, const PinMap *map)
{
  while (map->pin != NC)
  {
    if (map->pin == pin)
    {
      return map->peripheral;
    }
    map++;
  }
  return NP;
}

void *pinmap_peripheral(PinName pin, const PinMap *map)
{
  void *peripheral = NP;

  if (pin != (PinName)NC)
  {
    peripheral = pinmap_find_peripheral(pin, map);
  }
  return peripheral;
}

PinName pinmap_find_pin(void *peripheral, const PinMap *map)
{
  while (map->peripheral != NP)
  {
    if (map->peripheral == peripheral)
    {
      return map->pin;
    }
    map++;
  }
  return NC;
}

PinName pinmap_pin(void *peripheral, const PinMap *map)
{
  PinName pin = NC;

  if (peripheral != NP)
  {
    pin = pinmap_find_pin(peripheral, map);
  }
  return pin;
}

uint32_t pinmap_find_function(PinName pin, const PinMap *map)
{
  while (map->pin != NC)
  {
    if (map->pin == pin)
    {
      return map->function;
    }
    map++;
  }
  return (uint32_t)NC;
}

uint32_t pinmap_function(PinName pin, const PinMap *map)
{
  uint32_t function = (uint32_t)NC;

  if (pin != (PinName)NC)
  {
    function = pinmap_find_function(pin, map);
  }
  return function;
}

// Merge peripherals
void *pinmap_merge_peripheral(void *a, void *b)
{
  // both are the same (inc both NP)
  if (a == b)
  {
    return a;
  }

  // one (or both) is not set
  if (a == NP)
  {
    return b;
  }
  if (b == NP)
  {
    return a;
  }

  // mismatch error case
  return NP;
}
