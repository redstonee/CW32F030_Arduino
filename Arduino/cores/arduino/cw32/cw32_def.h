#ifndef _CW32_DEF_
#define _CW32_DEF_


/**
 * @brief CW32 core version number
 */
#define CW32_CORE_VERSION_MAJOR    (0x00U) /*!< [31:24] major version */
#define CW32_CORE_VERSION_MINOR    (0x00U) /*!< [23:16] minor version */
#define CW32_CORE_VERSION_PATCH    (0x01U) /*!< [15:8]  patch version */
/*
 * Extra label for development:
 * 0: official release
 * [1-9]: release candidate
 * F[0-9]: development
 */
#define CH32_CORE_VERSION_EXTRA    (0x00U) /*!< [7:0]  extra version */
#define CW32_CORE_VERSION          ((CW32_CORE_VERSION_MAJOR << 24U)\
                                        |(CW32_CORE_VERSION_MINOR << 16U)\
                                        |(CW32_CORE_VERSION_PATCH << 8U )\
                                        |(CW32_CORE_VERSION_EXTRA))


/*
 *All defined 
 */
#if defined(CW32F030)
  #include "cw32f030.h"
#else 
  #error "CW32YYXX chip series is not defined in boards.txt."
#endif

#ifndef F_CPU
  #define F_CPU SystemCoreClock
#endif

// Here define some compatibility
#ifndef ADC1
  #define ADC1 ADC
#endif
#ifndef CAN1
  #define CAN1 CAN
#endif
#ifndef DAC1           
  #define DAC1 DAC   //two independent channels
#endif


/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
  #define WEAK __attribute__ ((weak))
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#if defined(NDEBUG)
#if !defined(_Error_Handler)
#define _Error_Handler(str, value) \
  while (1) {\
  }
#endif
#if !defined(Error_Handler)
#define Error_Handler() \
  while (1) {\
  }
#endif
#else
void _Error_Handler(const char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#endif

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif //_CW32_DEF_
