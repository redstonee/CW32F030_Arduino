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
#ifndef _PINNAMESTYPES_H
#define _PINNAMESTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  WCH PIN data as used in pin_function is coded on 32 bits as below
 *  [1:0]  MODE Input / Output / Output Speed
 *         00:input
 *         01:output,10MHz
 *         10:output,2MHz
 *         11:output,50MHz
 * 
 *  [3:2]  CNF under input
 *         00:Analog input
 *         01:float input
 *         10:input with PU/PD
 *         11:reserved
 *         CNF under output
 *         00:output PP
 *         01:output OD
 *         10:output AF_PP
 *         11:output AF_OD
 * 
 *  [5:4]  input PUPD config
 *         00:No Pull
 *         01:Pull-up
 *         10:Pull-Down
 *         11:reserved
 *  [7:6]  reserved
 * 
 *  [14:8] AF_NUM 0-0x7F
 * 
 *  [19:15] Channel(Analog/Timer) 0-31
 * 
 *  [31:20] Reserved      
 * 
 * 
 *   
 * */


#define CW_PIN_MODE_MASK 0x03
#define CW_PIN_MODE_SHIFT 0
#define CW_PIN_MODE_BITS (CW_PIN_MODE_MASK << CW_PIN_MODE_SHIFT)

#define CW_PIN_CNF_MASK 0x03
#define CW_PIN_CNF_SHIFT 2
#define CW_PIN_CNF_BITS (CW_PIN_CNF_MASK << CW_PIN_CNF_SHIFT)

#define CW_PIN_PUPD_MASK 0x03
#define CW_PIN_PUPD_SHIFT 4
#define CW_PIN_PUPD_BITS (CW_PIN_PUPD_MASK << CW_PIN_PUPD_SHIFT)

#define CW_PIN_AFNUM_MASK 0x7F
#define CW_PIN_AFNUM_SHIFT 8
#define CW_PIN_AFNUM_BITS (CW_PIN_AFNUM_MASK << CW_PIN_AFNUM_SHIFT)


#define CW_PIN_CHAN_MASK 0x1F
#define CW_PIN_CHAN_SHIFT 15
#define CW_PIN_CHANNEL_BIT (CW_PIN_CHAN_MASK << CW_PIN_CHAN_SHIFT)

/*
#define CW_PIN_FUNCTION_MASK 0x07
#define CW_PIN_FUNCTION_SHIFT 0
#define CW_PIN_FUNCTION_BITS (CW_PIN_FUNCTION_MASK << CW_PIN_FUNCTION_SHIFT)

#define CW_PIN_OD_MASK 0x01
#define CW_PIN_OD_SHIFT 3
#define CW_PIN_OD_BITS (CW_PIN_OD_MASK << CW_PIN_OD_SHIFT)


#define CW_PIN_SPEED_MASK 0x03
#define CW_PIN_SPEED_SHIFT 6
#define CW_PIN_SPEED_BITS (CW_PIN_SPEED_MASK << CW_PIN_SPEED_SHIFT)

#define CW_PIN_INV_MASK 0x01
#define CW_PIN_INV_SHIFT 20
#define CW_PIN_INV_BIT (CW_PIN_INV_MASK << CW_PIN_INV_SHIFT)

#define CW_PIN_AN_CTRL_MASK 0x01
#define CW_PIN_AN_CTRL_SHIFT 21
#define CW_PIN_ANALOG_CONTROL_BIT (CW_PIN_AN_CTRL_MASK << CW_PIN_AN_CTRL_SHIFT)

#define CW_PIN_AN_CHAN_BANK_B_MASK 0x01
#define CW_PIN_AN_CHAN_BANK_B_SHIFT 22
#define CW_PIN_ANALOG_CHAN_BANK_B_BIT (CW_PIN_AN_CHAN_BANK_B_MASK << CW_PIN_AN_CHAN_BANK_B_SHIFT)
*/

#define CW_PIN_MODE(x)                   (((x) >> CW_PIN_MODE_SHIFT) & CW_PIN_MODE_MASK)
#define CW_PIN_CNF(x)                    (((x) >> CW_PIN_CNF_SHIFT) & CW_PIN_CNF_MASK)
#define CW_PIN_PUPD(x)                   (((x) >> CW_PIN_PUPD_SHIFT) & CW_PIN_PUPD_MASK)
#define CW_PIN_AFNUM(x)                  (((x) >> CW_PIN_AFNUM_SHIFT) & CW_PIN_AFNUM_MASK) 
#define CW_PIN_CHANNEL(X)                (((X) >> CW_PIN_CHAN_SHIFT) & CW_PIN_CHAN_MASK)

/*
#define CW_PIN_FUNCTION(X)               (((X) >> CW_PIN_FUNCTION_SHIFT) & CW_PIN_FUNCTION_MASK)
#define CW_PIN_OD(X)                     (((X) >> CW_PIN_OD_SHIFT) & CW_PIN_OD_MASK)
#define CW_PIN_PUPD(X)                   (((X) >> CW_PIN_PUPD_SHIFT) & CW_PIN_PUPD_MASK)
#define CW_PIN_SPEED(X)                  (((X) >> CW_PIN_SPEED_SHIFT) & CW_PIN_SPEED_MASK)
#define CW_PIN_AFNUM(X)                  (((X) >> CW_PIN_AFNUM_SHIFT) & CW_PIN_AFNUM_MASK)
#define CW_PIN_CHANNEL(X)                (((X) >> CW_PIN_CHAN_SHIFT) & CW_PIN_CHAN_MASK)
#define CW_PIN_INVERTED(X)               (((X) >> CW_PIN_INV_SHIFT) & CW_PIN_INV_MASK)
#define CW_PIN_ANALOG_CONTROL(X)         (((X) >> CW_PIN_AN_CTRL_SHIFT) & CW_PIN_AN_CTRL_MASK)
#define CW_PIN_ANALOG_CHANNEL_BANK_B(X)  (((X) >> CW_PIN_AN_CHAN_BANK_B_SHIFT) & CW_PIN_AN_CHAN_BANK_B_MASK)
#define CW_PIN_MODE(X)                   ((CW_PIN_OD((X)) << 4) | \
                                           (CW_PIN_FUNCTION((X)) & (~CW_PIN_OD_BITS)))
*/


#define CW_PIN_DEFINE(MODE, CNF, PUPD, AFNUM) ((int)(MODE) |\
                             ((CNF & CW_PIN_CNF_MASK) << CW_PIN_CNF_SHIFT)       |\
                             ((PUPD & CW_PIN_PUPD_MASK) << CW_PIN_PUPD_SHIFT)    |\
                             ((AFNUM & CW_PIN_AFNUM_MASK) << CW_PIN_AFNUM_SHIFT))


#define CW_PIN_DEFINE_EXT(MODE, CNF, PUPD, AFNUM, CWAN)  ((int)(MODE) |\
                             ((CNF & CW_PIN_CNF_MASK) << CW_PIN_CNF_SHIFT)       |\
                             ((PUPD & CW_PIN_PUPD_MASK) << CW_PIN_PUPD_SHIFT)    |\
                             ((AFNUM & CW_PIN_AFNUM_MASK) << CW_PIN_AFNUM_SHIFT) |\
                             ((CWAN & CW_PIN_CHAN_MASK) << CW_PIN_CHAN_SHIFT))




/*
#define CW_PIN_DEFINE(FUNC_OD, PUPD, AFNUM)  ((int)(FUNC_OD) |\
                          ((PUPD  & CW_PIN_PUPD_MASK) << CW_PIN_PUPD_SHIFT) |\
                          ((AFNUM & CW_PIN_AFNUM_MASK) << CW_PIN_AFNUM_SHIFT))

#define CW_PIN_DEFINE_EXT(FUNC_OD, PUPD, AFNUM, CWAN, INV) \
                                            ((int)(FUNC_OD) |\
                       ((PUPD   & CW_PIN_PUPD_MASK) << CW_PIN_PUPD_SHIFT) |\
                       ((AFNUM  & CW_PIN_AFNUM_MASK) << CW_PIN_AFNUM_SHIFT) |\
                       ((CHAN   & CW_PIN_CHAN_MASK) << CW_PIN_CHAN_SHIFT) |\
                       ((INV    & CW_PIN_INV_MASK) << CW_PIN_INV_SHIFT))
*/


/*
 * MACROS to support the legacy definition of PIN formats
 * The CW_MODE_ defines contain the function and the Push-pull/OpenDrain
 * configuration (legacy inheritance).
 */
#define CW_PIN_DATA(MODE, CNF, PUPD, AFNUM) \
            CW_PIN_DEFINE(MODE, CNF, PUPD, AFNUM)
#define CW_PIN_DATA_EXT(MODE, CNF, PUPD, AFNUM, CHAN) \
            CW_PIN_DEFINE_EXT(MODE, CNF, PUPD, AFNUM, CHAN)


/*
typedef enum {
  CW_PIN_INPUT = 0,
  CW_PIN_OUTPUT = 1,
  CW_PIN_ALTERNATE = 2,
  CW_PIN_ANALOG = 3,
} CWPinFunction;

#define CW_MODE_INPUT                      (CW_PIN_INPUT)
#define CW_MODE_OUTPUT_PP                  (CW_PIN_OUTPUT)
#define CW_MODE_OUTPUT_OD                  (CW_PIN_OUTPUT | CW_PIN_OD_BITS)
#define CW_MODE_AF_PP                      (CW_PIN_ALTERNATE)
#define CW_MODE_AF_OD                      (CW_PIN_ALTERNATE | CW_PIN_OD_BITS)
#define CW_MODE_ANALOG                     (CW_PIN_ANALOG)
#define CW_MODE_ANALOG_ADC_CONTROL         (CW_PIN_ANALOG | CW_PIN_ANALOG_CONTROL_BIT)
#define CW_MODE_ANALOG_ADC_CHANNEL_BANK_B  (CW_PIN_ANALOG | CW_PIN_ANALOG_CHAN_BANK_B_BIT)
*/

/* MODE */
#define CW_MODE_INPUT        (0)
#define CW_MODE_OUTPUT_10MHz (1)
#define CW_MODE_OUTPUT_2MHz  (2)
#define CW_MODE_OUTPUT_50MHz (3)
/* CNF */
#define CW_CNF_INPUT_ANALOG  (0)
#define CW_CNF_INPUT_FLOAT   (1)
#define CW_CNF_INPUT_PUPD    (2)
#define CW_CNF_OUTPUT_PP     (0)
#define CW_CNF_OUTPUT_OD     (1)
#define CW_CNF_OUTPUT_AFPP   (2)
#define CW_CNF_OUTPUT_AFOD   (3)

/* PUPD */
#define NOPULL               (0)
#define PULLUP               (1)
#define PILLDOWN             (2)


// High nibble = port number (FirstPort <= PortName <= LastPort)
// Low nibble  = pin number
#define CW_PORT(X) (((uint32_t)(X) >> 4) & 0xF)
#define CW_PIN(X)  ((uint32_t)(X) & 0xF)

// Check PinName is valid: FirstPort <= PortName <= LastPort
// As FirstPort is equal to 0 and CW_PORT cast as an unsigned
// (CW_PORT(X) >= FirstPort)  is always true
//#define CW_VALID_PINNAME(X) ((CW_PORT(X) >= FirstPort) && (CW_PORT(X) <= LastPort))

#define CW_VALID_PINNAME(X) (CW_PORT(X) <= LastPort)
#define CW_GPIO_PIN(X) ((uint16_t)(1<<CW_PIN(X)))



#ifdef __cplusplus
}
#endif

#endif

