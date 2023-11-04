#ifndef _CW32_DEF_BUILD_
#define _CW32_DEF_BUILD_

#if !defined(COM_STARTUP_FILE)

  #if defined(CW32F030)
     #define  COM_STARTUP_FILE "startup_cw32f030.S"
  #else
    #error "Unknow chip!"
  #endif
#else
  #warning "No startup file defined !"
#endif /* CHIP Define */
#endif /* _CW32_DEF_BUILD_ */

