#include "board.h"
#include "cw32yyxx_systick.h"
#include "cw32yyxx_rcc.h"

#ifdef __cplusplus
extern "C"
{
#endif

  WEAK void pre_init(void)
  {
    SystemClock_Config();
    InitTick(RCC_Sysctrl_GetHClkFreq());
  }

#ifdef __cplusplus
}
#endif
