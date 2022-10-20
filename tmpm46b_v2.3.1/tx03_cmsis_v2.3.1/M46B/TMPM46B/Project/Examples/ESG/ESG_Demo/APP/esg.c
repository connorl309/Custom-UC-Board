/**
 *******************************************************************************
 * @file    esg.c
 * @brief   The application functions of ESG demo for the TOSHIBA
 *          'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/02/27
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "esg.h"
/* external variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the basic ESG configuration.
  * @param Value: The latch timing for ESG.
  *   This parameter can be one of the following values:
  *   ESG_LATCH_TIMING_1, ESG_LATCH_TIMING_2, ESG_LATCH_TIMING_3,
  *   ESG_LATCH_TIMING_4, ESG_LATCH_TIMING_5, ESG_LATCH_TIMING_6,
  *   ESG_LATCH_TIMING_7, ESG_LATCH_TIMING_8, ESG_LATCH_TIMING_9,
  *   ESG_LATCH_TIMING_10, ESG_LATCH_TIMING_11, ESG_LATCH_TIMING_12,
  *   ESG_LATCH_TIMING_13, ESG_LATCH_TIMING_14, ESG_LATCH_TIMING_15,
  *   ESG_LATCH_TIMING_16.
  * @param Fintming: the value of entropy seed output timing
  * @retval None
  */
void ESG_Config(ESG_LatchTiming Value, uint16_t Fintming)
{
    uint16_t latchtiming;
    /* Check the parameters */
    assert_param(IS_ESG_LATCH_TIMING(Value));

    /* Confirm the ESG core stops */
    if (ESG_GetCalculationStatus() == ESG_CALCULATION_COMPLETE) {
        /* Confirm no interrupt generation */
        if (ESG_GetIntStatus() == DISABLE) {
            /* Set the latch timing. */
            ESG_SetLatchTiming(Value);
            /* Get latchtiming value  */
            latchtiming = ESG_GetLatchTiming();
            if (Fintming >= 512U * (latchtiming + 1U) + 3U) {
                /* Set the output timing. */
                ESG_SetFintiming(Fintming);
            } else {
                common_uart_disp("Fintming value input error !\n");
            }
        } else {
            /* Do nothing */
        }
    } else {
        /* Do nothing */
    }
}

/*********************************** END OF FILE ******************************/
