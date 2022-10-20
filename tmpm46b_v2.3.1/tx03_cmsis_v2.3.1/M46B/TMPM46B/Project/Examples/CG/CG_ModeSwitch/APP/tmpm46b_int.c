/**
 *******************************************************************************
 * @file    tmpm46b_int.c
 * @brief   all interrupt request functions definition of CG_ModeSwitch
 *          for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/20
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_int.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  INTF_IRQHandler
  * @param  None
  * @retval None
  */
void INTF_IRQHandler(void)
{
    CG_ClearINTReq(CG_INT_SRC_F);
}
