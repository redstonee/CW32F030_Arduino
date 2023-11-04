/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup cw32f0xx
  * @{
  */
    
#ifndef __CW32F0xx_H
#define __CW32F0xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
   
/** @addtogroup Library_configuration_section
  * @{
  */
  
/**
  * @brief CW32 Family
  */
#if !defined  (CW32F0)
#define CW32F0
#endif /* CW32F0 */

/** Uncomment the line below according to the target CW32 device used in your application.
  * CW32f0xxxx.h file contains:
  * - All the peripheral register's definitions, bits definitions and memory mapping for CW32F0xxxx devices
  * - IRQ channel definition
  * - Peripheral memory mapping and physical registers address definition
  * - Peripheral pointer declaration and driver header file inclusion
  * - Product miscellaneous configuration: assert macros�
  * Note: These CMSIS drivers (CW32f0xxxx.h) are always supporting features of the sub-family�s superset.
  */

#if !defined (CW32F030x6) && !defined (CW32F030x8) &&                           \
    !defined (CW32F031x6) && !defined (CW32F038xx) &&                           \
    !defined (CW32F042x6) && !defined (CW32F048xx) && !defined (CW32F070x6) && \
    !defined (CW32F051x8) && !defined (CW32F058xx) &&                           \
    !defined (CW32F071xB) && !defined (CW32F072xB) && !defined (CW32F078xx) && !defined (CW32F070xB) && \
    !defined (CW32F091xC) && !defined (CW32F098xx) && !defined (CW32F030xC)
  /* #define CW32F030x6 */  /*!< CW32F030x4, CW32F030x6 Devices (CW32F030xx microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)              */
  /* #define CW32F030x8 */  /*!< CW32F030x8 Devices (CW32F030xx microcontrollers where the Flash memory is 64 Kbytes)                                              */
  /* #define CW32F031x6 */  /*!< CW32F031x4, CW32F031x6 Devices (CW32F031xx microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)              */
  /* #define CW32F038xx */  /*!< CW32F038xx Devices (CW32F038xx microcontrollers where the Flash memory is 32 Kbytes)                                              */
  /* #define CW32F042x6 */  /*!< CW32F042x4, CW32F042x6 Devices (CW32F042xx microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)              */
  /* #define CW32F048xx */  /*!< CW32F048xx Devices (CW32F048xx microcontrollers where the Flash memory is 32 Kbytes)                                              */
  /* #define CW32F051x8 */  /*!< CW32F051x4, CW32F051x6, CW32F051x8 Devices (CW32F051xx microcontrollers where the Flash memory ranges between 16 and 64 Kbytes) */
  /* #define CW32F058xx */  /*!< CW32F058xx Devices (CW32F058xx microcontrollers where the Flash memory is 64 Kbytes)                                              */
  /* #define CW32F070x6 */  /*!< CW32F070x6 Devices (CW32F070x6 microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)                           */
  /* #define CW32F070xB */  /*!< CW32F070xB Devices (CW32F070xB microcontrollers where the Flash memory ranges between 64 and 128 Kbytes)                          */
  /* #define CW32F071xB */  /*!< CW32F071x8, CW32F071xB Devices (CW32F071xx microcontrollers where the Flash memory ranges between 64 and 128 Kbytes)             */
  /* #define CW32F072xB */  /*!< CW32F072x8, CW32F072xB Devices (CW32F072xx microcontrollers where the Flash memory ranges between 64 and 128 Kbytes)             */
  /* #define CW32F078xx */  /*!< CW32F078xx Devices (CW32F078xx microcontrollers where the Flash memory is 128 Kbytes)                                             */
  /* #define CW32F030xC */  /*!< CW32F030xC Devices (CW32F030xC microcontrollers where the Flash memory is 256 Kbytes)                                             */  
  /* #define CW32F091xC */  /*!< CW32F091xB, CW32F091xC Devices (CW32F091xx microcontrollers where the Flash memory ranges between 128 and 256 Kbytes)            */
  /* #define CW32F098xx */  /*!< CW32F098xx Devices (CW32F098xx microcontrollers where the Flash memory is 256 Kbytes)                                             */
#endif
/* Legacy aliases */
#if defined (CW32F048x6)
 #define CW32F048xx
#endif /* CW32F048x6 */

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */

/**
  * @brief CMSIS Device version number V2.3.6
  */
#define __CW32F0_DEVICE_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __CW32F0_DEVICE_VERSION_SUB1   (0x03) /*!< [23:16] sub1 version */
#define __CW32F0_DEVICE_VERSION_SUB2   (0x06) /*!< [15:8]  sub2 version */
#define __CW32F0_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __CW32F0_DEVICE_VERSION        ((__CW32F0_DEVICE_VERSION_MAIN << 24)\
                                        |(__CW32F0_DEVICE_VERSION_SUB1 << 16)\
                                        |(__CW32F0_DEVICE_VERSION_SUB2 << 8 )\
                                        |(__CW32F0_DEVICE_VERSION_RC))
                                             
/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(CW32F030)
  #include "CW32f030.h"
#elif defined(CW32F042)
  #include "CW32f042.h"
#else
 #error "Please select first the target CW32F0xx device used in your application (in CW32f0xx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */ 
typedef enum 
{
  RESET = 0U, 
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum 
{
  DISABLE = 0U, 
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum 
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/* Use of interrupt control for register exclusive access */
/* Atomic 32-bit register access macro to set one or several bits */
#define ATOMIC_SET_BIT(REG, BIT)                             \
  do {                                                       \
    uint32_t primask;                                        \
    primask = __get_PRIMASK();                               \
    __set_PRIMASK(1);                                        \
    SET_BIT((REG), (BIT));                                   \
    __set_PRIMASK(primask);                                  \
  } while(0)

/* Atomic 32-bit register access macro to clear one or several bits */
#define ATOMIC_CLEAR_BIT(REG, BIT)                           \
  do {                                                       \
    uint32_t primask;                                        \
    primask = __get_PRIMASK();                               \
    __set_PRIMASK(1);                                        \
    CLEAR_BIT((REG), (BIT));                                 \
    __set_PRIMASK(primask);                                  \
  } while(0)

/* Atomic 32-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFY_REG(REG, CLEARMSK, SETMASK)            \
  do {                                                       \
    uint32_t primask;                                        \
    primask = __get_PRIMASK();                               \
    __set_PRIMASK(1);                                        \
    MODIFY_REG((REG), (CLEARMSK), (SETMASK));                \
    __set_PRIMASK(primask);                                  \
  } while(0)

/* Atomic 16-bit register access macro to set one or several bits */
#define ATOMIC_SETH_BIT(REG, BIT) ATOMIC_SET_BIT(REG, BIT)                                   \

/* Atomic 16-bit register access macro to clear one or several bits */
#define ATOMIC_CLEARH_BIT(REG, BIT) ATOMIC_CLEAR_BIT(REG, BIT)                               \

/* Atomic 16-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFYH_REG(REG, CLEARMSK, SETMASK) ATOMIC_MODIFY_REG(REG, CLEARMSK, SETMASK) \

/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "CW32f0xx_hal.h"
#endif /* USE_HAL_DRIVER */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CW32F0xx_H */
/**
  * @}
  */

/**
  * @}
  */
  



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
