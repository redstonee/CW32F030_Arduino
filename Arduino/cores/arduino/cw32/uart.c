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
#include "core_debug.h"
#include "uart.h"
#include "Arduino.h"
#include "PinAF.h"
#include "cw32yyxx_rcc.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(UART_MODULE_ENABLED) && !defined(UART_MODULE_ONLY)

/* If DEBUG_UART is not defined assume this is the one linked to PIN_SERIAL_TX */
#if !defined(DEBUG_UART)
#if defined(PIN_SERIAL_TX)
#define DEBUG_UART pinmap_peripheral(digitalPinToPinName(PIN_SERIAL_TX), PinMap_UART_TX)
#define DEBUG_PINNAME_TX digitalPinToPinName(PIN_SERIAL_TX)
#else
/* No debug UART defined */
#define DEBUG_UART NP
#define DEBUG_PINNAME_TX NC
#endif
#endif
#if !defined(DEBUG_UART_BAUDRATE)
#define DEBUG_UART_BAUDRATE 115200
#endif
#if !defined(UART_WORDLENGTH_8B)
#define UART_WORDLENGTH_8B USART_WordLength_8b
#endif
#if !defined(UART_PARITY_NONE)
#define UART_PARITY_NONE USART_Parity_No
#endif
#if !defined(UART_STOPBITS_1)
#define UART_STOPBITS_1 USART_StopBits_1
#endif

  /* @brief uart caracteristics */
  typedef enum
  {
#if defined(UART1_BASE)
    UART1_INDEX,
#endif
#if defined(UART2_BASE)
    UART2_INDEX,
#endif
#if defined(UART3_BASE)
    UART3_INDEX,
#endif
#if defined(UART4_BASE)
    UART4_INDEX,
#endif
#if defined(UART5_BASE)
    UART5_INDEX,
#endif
#if defined(UART6_BASE)
    UART6_INDEX,
#endif
#if defined(UART7_BASE)
    UART7_INDEX,
#endif
#if defined(UART8_BASE)
    UART8_INDEX,
#endif
    UART_NUM
  } uart_index_t;

  static UART_HandleTypeDef *uart_handlers[UART_NUM] = {NULL};

  static serial_t serial_debug =
      {
          .uart = NP,
          .pin_tx = NC,
          .pin_rx = NC,
          .pin_rts = NC,
          .pin_cts = NC,
          .index = UART_NUM,
  };

  extern uint64_t GetTick(void);

  /* Aim of the function is to get serial_s pointer using huart pointer */
  /* Highly inspired from magical linux kernel's "container_of" */
  serial_t *get_serial_obj(UART_HandleTypeDef *huart)
  {
    struct serial_s *obj_s;
    serial_t *obj;

    obj_s = (struct serial_s *)((char *)huart - offsetof(struct serial_s, handle));
    obj = (serial_t *)((char *)obj_s - offsetof(serial_t, uart));

    return (obj);
  }

  /**
   * @brief  Function called to initialize the uart interface
   * @param  obj : pointer to serial_t structure
   * @retval None
   */
  void uart_init(serial_t *obj, uint32_t baudrate, uint32_t databits, uint32_t parity, uint32_t stopbits)
  {
    if (obj == NULL)
    {
      return;
    }
    UART_HandleTypeDef *huart = &(obj->handle);

    /* Determine the U(S)ART peripheral to use (USART1, USART2, ...) */
    USART_TypeDef *uart_tx = pinmap_peripheral(obj->pin_tx, PinMap_UART_TX);
    USART_TypeDef *uart_rx = pinmap_peripheral(obj->pin_rx, PinMap_UART_RX);
    USART_TypeDef *uart_rts = pinmap_peripheral(obj->pin_rts, PinMap_UART_RTS);
    USART_TypeDef *uart_cts = pinmap_peripheral(obj->pin_cts, PinMap_UART_CTS);

    /* Pin Tx must not be NP */
    if (uart_tx == NP)
    {
      if (obj != &serial_debug)
      {
        core_debug("ERROR: [U(S)ART] Tx pin has no peripheral!\n");
      }
      return;
    }
    /* Pin Rx must not be NP if not half-duplex */
    if ((obj->pin_rx != NC) && (uart_rx == NP))
    {
      if (obj != &serial_debug)
      {
        core_debug("ERROR: [U(S)ART] Rx pin has no peripheral!\n");
      }
      return;
    }
    /* Pin RTS must not be NP if flow control is enabled */
    if ((obj->pin_rts != NC) && (uart_rts == NP))
    {
      if (obj != &serial_debug)
      {
        core_debug("ERROR: [U(S)ART] RTS pin has no peripheral!\n");
      }
      return;
    }
    /* Pin CTS must not be NP if flow control is enabled */
    if ((obj->pin_cts != NC) && (uart_cts == NP))
    {
      if (obj != &serial_debug)
      {
        core_debug("ERROR: [U(S)ART] CTS pin has no peripheral!\n");
      }
      return;
    }

    /*
     * Get the peripheral name (USART1, USART2, ...) from the pin
     * and assign it to the object
     */
    obj->uart = pinmap_merge_peripheral(uart_tx, uart_rx);
    /* We also merge RTS/CTS and assert all pins belong to the same instance */
    obj->uart = pinmap_merge_peripheral(obj->uart, uart_rts);
    obj->uart = pinmap_merge_peripheral(obj->uart, uart_cts);

    if (obj->uart == NP)
    {
      if (obj != &serial_debug)
      {
        core_debug("ERROR: [U(S)ART] Rx/Tx/RTS/CTS pins peripherals mismatch!\n");
      }
      return;
    }

    /* Enable USART clock */
#if defined(UART1_BASE)
    else if (obj->uart == CW_UART1)
    {
      RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_UART1, ENABLE);
      obj->index = UART1_INDEX;
      obj->irq = UART1_IRQn;
    }
#endif
#if defined(UART2_BASE)
    else if (obj->uart == CW_UART2)
    {
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART2, ENABLE);
      obj->index = UART2_INDEX;
      obj->irq = UART2_IRQn;
    }
#endif
#if defined(UART3_BASE)
    else if (obj->uart == CW_UART3)
    {
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART3, ENABLE);
      obj->index = UART3_INDEX;
      obj->irq = UART3_IRQn;
    }
#endif

#if defined(UART4_BASE)
    else if (obj->uart == CW_UART4)
    {
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART4, ENABLE);
      obj->index = UART4_INDEX;
      obj->irq = UART4_IRQn;
    }
#endif
    // To be continued

    /* Configure UART GPIO pins */
    pinmap_pinout(obj->pin_tx, PinMap_UART_TX);
    if (uart_rx != NP)
    {
      pinmap_pinout(obj->pin_rx, PinMap_UART_RX);
    }

    /* Configure flow control */
    uint32_t flow_control = USART_HardwareFlowControl_None;
    if (uart_rts != NP)
    {
      flow_control |= USART_HardwareFlowControl_RTS;
      pinmap_pinout(obj->pin_rts, PinMap_UART_RTS);
    }
    if (uart_cts != NP)
    {
      flow_control |= USART_HardwareFlowControl_CTS;
      pinmap_pinout(obj->pin_cts, PinMap_UART_CTS);
    }

    /* Configure uart */
    uart_handlers[obj->index] = huart;
    huart->Instance = obj->uart;
    huart->init.USART_BaudRate = baudrate;
    // huart->init.USART_WordLength = databits;
    huart->init.USART_StopBits = stopbits;
    huart->init.USART_Parity = parity;
    huart->init.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
    huart->init.USART_HardwareFlowControl = flow_control;
    huart->init.USART_UclkFreq = RCC_Sysctrl_GetPClkFreq();

    if (uart_rx == NP)
    {
      USART_HalfDuplexCmd(huart->Instance, ENABLE);
    }

    USART_Init(huart->Instance, &(huart->init));
    // USART_Cmd(huart->Instance, ENABLE);
  }

  /**
   * @brief  Function called to deinitialize the uart interface
   * @param  obj : pointer to serial_t structure
   * @retval None
   */
  void uart_deinit(serial_t *obj)
  {
    /* Reset UART and disable clock */
    switch (obj->index)
    {
#if defined(UART1_BASE)
    case UART1_INDEX:
      RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_UART1, ENABLE);
      RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_UART1, DISABLE);
      break;
#endif
#if defined(UART2_BASE)
    case UART2_INDEX:
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART2, ENABLE);
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART2, DISABLE);
      break;
#endif
#if defined(UART3_BASE)
    case UART3_INDEX:
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART3, ENABLE);
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART3, DISABLE);
      break;
#endif
#if defined(UART4_BASE)
    case UART4_INDEX:
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART4, ENABLE);
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART4, DISABLE);
      break;
#endif

#if defined(UART5_BASE)
    case UART5_INDEX:
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART5, ENABLE);
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART5, DISABLE);
      break;
#endif

#if defined(UART6_BASE)
    case UART6_INDEX:
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART6, ENABLE);
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART6, DISABLE);
      break;
#endif

#if defined(UART7_BASE)
    case UART7_INDEX:
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART7, ENABLE);
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART7, DISABLE);
      break;
#endif

#if defined(UART8_BASE)
    case UART8_INDEX:
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART8, ENABLE);
      RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART8, DISABLE);
      break;
#endif
    }

    /* Release uart debug to ensure init */
    if (serial_debug.index == obj->index)
    {
      serial_debug.index = UART_NUM;
    }
  }

  /**
   * @brief  Function called to initialize the debug uart interface
   * @note   Call only if debug U(S)ART peripheral is not already initialized
   *         by a Serial instance
   *         Default config: 8N1
   * @retval None
   */
  void uart_debug_init(void)
  {
    if (DEBUG_UART != NP)
    {
#if defined(DEBUG_PINNAME_TX)
      serial_debug.pin_tx = DEBUG_PINNAME_TX;
#else
      serial_debug.pin_tx = pinmap_pin(DEBUG_UART, PinMap_UART_TX);
#endif

      /* serial_debug.pin_rx set by default to NC to configure in half duplex mode */
      uart_init(&serial_debug, DEBUG_UART_BAUDRATE, 0, UART_PARITY_NONE, UART_STOPBITS_1);
    }
  }

  /**
   * @brief  write the data on the uart: used by printf for debug only (syscalls)
   * @param  data : bytes to write
   * @param  size : number of data to write
   * @retval The number of bytes written
   */
  // size_t uart_debug_write(uint8_t *data, uint32_t size)
  // {
  //   serial_t *obj = get_serial_obj(uart_handlers[serial_debug.index]);
  //   while (size--)
  //   {
  //     while (serial_tx_active(obj))
  //       ;
  //     USART_SendData_8bit(uart_handlers[serial_debug.index]->Instance, *data++);
  //     // USART_SendData_8bit(CW_UART2, *data++);
  //   }
  //   return size; // it shouled be 0
  // }
  size_t uart_debug_write(uint8_t *data, uint32_t size)
  {
    if (serial_debug.index >= UART_NUM)
    {
      if (DEBUG_UART == NP)
      {
        return 0;
      }

      /* Search if DEBUG_UART already initialized */
      for (serial_debug.index = 0; serial_debug.index < UART_NUM; serial_debug.index++)
      {
        if (uart_handlers[serial_debug.index] != NULL)
        {
          if (DEBUG_UART == serial_debug.uart)
          {
            break;
          }
        }
      }

      if (serial_debug.index >= UART_NUM)
      {
        /* DEBUG_UART not initialized */
        uart_debug_init();
        if (serial_debug.index >= UART_NUM)
        {
          return 0;
        }
      }
    }

    return uart_write(&serial_debug, data, size);
  }

  size_t uart_write(serial_t *obj, uint8_t *data, uint32_t size)
  {
    uint32_t tickstart = GetTick();

    while (serial_tx_active(obj))
    {
      if ((GetTick() - tickstart) >= TX_TIMEOUT)
      {
        return 0;
      }
    }

    while (size--)
    {
      USART_SendData_8bit(obj->uart, *data++);
      while (serial_tx_active(obj))
        ;
    }

    return size; // it shouled be 0
  }

  /**
   * Attempts to determine if the serial peripheral is already in use for RX
   *
   * @param obj The serial object
   * @return Non-zero if the RX transaction is ongoing, 0 otherwise
   */
  uint8_t serial_rx_active(serial_t *obj)
  {
    return (USART_GetFlagStatus(obj->uart, USART_FLAG_RC) == RESET);
  }

  /**
   * Attempts to determine if the serial peripheral is already in use for TX
   *
   * @param obj The serial object
   * @return Non-zero if the TX transaction is ongoing, 0 otherwise
   */
  uint8_t serial_tx_active(serial_t *obj)
  {
    return (USART_GetFlagStatus(obj->uart, USART_FLAG_TXE) == RESET);
  }

  /**
   * @brief  Read receive byte from uart
   * @param  obj : pointer to serial_t structure
   * @retval last character received
   */
  int uart_getc(serial_t *obj, unsigned char *c)
  {
    if (obj == NULL)
    {
      return -1;
    }

    if (serial_rx_active(obj))
    {
      return -1;
    }

    *c = (unsigned char)USART_ReceiveData_8bit(obj->uart);

    return 0;
  }

#endif /* UART_MODULE_ENABLED  && !UART_MODULE_ONLY */
#ifdef __cplusplus
}
#endif
