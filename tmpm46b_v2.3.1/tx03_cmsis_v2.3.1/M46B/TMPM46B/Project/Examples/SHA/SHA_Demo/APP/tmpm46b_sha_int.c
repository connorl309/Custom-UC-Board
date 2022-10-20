/**
 *******************************************************************************
 * @file    tmpm46b_sha_int.c
 * @brief   all interrupt request functions definition of SHA
 *          for the TOSHIBA 'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/02/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_sha_int.h"
/* external variables --------------------------------------------------------*/
volatile extern uint32_t CompleteFlag;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  SHA completion interrupt.
  * @param  None
  * @retval None
  */
void INTSHA_IRQHandler(void)
{
    CompleteFlag = 1U;
}

/*********************************** END OF FILE ******************************/
