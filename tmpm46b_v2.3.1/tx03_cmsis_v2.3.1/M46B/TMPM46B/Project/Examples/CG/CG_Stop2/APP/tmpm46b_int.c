/**
 *******************************************************************************
 * @file    tmpm46b_int.c
 * @brief   all interrupt request functions definition of CG Demo
 *          for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
  * @brief  ExtINTSrc_IRQHandler
  * @param  None
  * @retval None
  */
void ExtINTSrc_IRQHandler(void)
{
    uint8_t ledval;
    CG_ClearINTReq(CG_ExtINTSrc);
    ledval = LED_EXT | LED_OTHER;
    LED_On(ledval);
    LED_Off(~ledval);
}
