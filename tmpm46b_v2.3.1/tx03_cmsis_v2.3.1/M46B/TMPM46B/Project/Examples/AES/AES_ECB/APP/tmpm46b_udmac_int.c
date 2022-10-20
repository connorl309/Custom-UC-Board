/**
 *******************************************************************************
 * @file    tmpm46b_udmac_int.c
 * @brief   all interrupt request functions definition of DMA
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
#include "tmpm46b_udmac_int.h"
/* external variables --------------------------------------------------------*/
volatile extern uint32_t CompleteFlag;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  AES FIFO write interrupt.
  * @param  None
  * @retval None
  */
void INTDMACTC9_IRQHandler(void)
{
    /* Wait for AES calculation completed */
    while(AES_GetArithmeticStatus() != AES_CALCULATION_COMPLETE) {
        /* Do nothing */
    }
    /* Clear the AES FIFO write interrupt. */
    AES_SetDMAState(DISABLE);
}

/**
  * @brief  AES FIFO read interrupt.
  * @param  None
  * @retval None
  */
void INTDMACTC8_IRQHandler(void)
{
    CompleteFlag = 1U;
}

/*********************************** END OF FILE ******************************/
