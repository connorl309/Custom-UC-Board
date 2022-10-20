/**
 *******************************************************************************
 * @file    tmpm46b_wdt_int.c
 * @brief   All interrupt request functions definition of WDT
 *          for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/17
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_wdt_int.h"
/* Global variables ----------------------------------------------------------*/
volatile uint8_t fIntNMI = 0U;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  The NMI interrupt request function.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
    fIntNMI = 1U;
}

/*********************************** END OF FILE ******************************/
