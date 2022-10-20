/**
 *******************************************************************************
 * @file    tmpm46b_rtc_int.c
 * @brief   All interrupt request functions definition of RTC
 *          for the TOSHIBA 'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/03/14
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "tmpm46b_rtc_int.h"

volatile uint8_t fRTC_1HZ_INT = 0U;

/**
  * @brief  The RTC interrupt request function.
  * @param  None
  * @retval None
  */
void INTRTC_IRQHandler(void)
{
    fRTC_1HZ_INT = 1U;
    /* Clear RTC interrupt request */
    CG_ClearINTReq(CG_INT_SRC_RTC);
}
