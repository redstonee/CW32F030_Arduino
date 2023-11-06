

/******************************************************************************
 * Include files                                                              *
 ******************************************************************************/
#include "cw32f030.h"
#include "system_cw32f030.h"
#include "cw32f030_rcc.h"

#define FLASH_MEMORY_BASE 0x00000000UL /*!< FLASH(up to 64 KB) base address in the alias region  */
#define SRAM_MEMORY_BASE 0x20000000UL  /*!< SRAM1(8 KB) base address in the alias region         */
#define VECT_TAB_OFFSET 0x00002000UL

/******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/

uint32_t SystemCoreClock = 8000000;

void SystemCoreClockUpdate(void) // Update SystemCoreClock variable
{
    SystemCoreClock = 8000000;
}

/**
 ******************************************************************************
 ** \brief  Setup the microcontroller system. Initialize the System and update
 ** the SystemCoreClock variable.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemInit(void)
{
    // Load TrimCode in this.
    //...
#ifdef VECT_TAB_REMAP
    SCB->VTOR = FLASH_MEMORY_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif
    SystemCoreClockUpdate();
    CW_SYSCTRL->HSI_f.TRIM = *((volatile uint16_t *)RCC_HSI_TRIMCODEADDR);
    CW_SYSCTRL->LSI_f.TRIM = *((volatile uint16_t *)RCC_LSI_TRIMCODEADDR);
    // Init Hide thing.
    //...

}

/**
 * \brief   clear memory
 *
 * \param   [in]  start addr
 * \param   [in]  memory size(byte)
 * \retval  void
 */
void MemClr(void *pu8Address, uint32_t u32Count)
{
    uint8_t *pu8Addr = (uint8_t *)pu8Address;

    if (NULL == pu8Addr)
    {
        return;
    }

    while (u32Count--)
    {
        *pu8Addr++ = 0;
    }
}
