/**
 *******************************************************************************
 * @file    tmpm46b_tmrb_int.c
 * @brief   all interrupt request functions definition of TMRB_TIMER demo
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
#include "tmpm46b_tmrb_int.h"
#include "main.h"

/**
  * @brief  TMRB0 interrupt service routine (1ms)
  * @param  None
  * @retval None
  */
void INTTB0_IRQHandler(void)
{
    static uint16_t tbcount = 0U;
    static uint8_t ledon = 1U;

    tbcount++;
    if (tbcount >= 500U) {
        tbcount = 0U;
        /* reverse LED output */
        ledon = (ledon == 0U) ? 1U : 0U;
        if (0U == ledon) {
            LED_Off(LED_ALL);
        } else {
            LED_On(LED_ALL);
        }
    } else {
        /* Do nothing */
    }
}

/*********************************** END OF FILE ******************************/
