/**
 *******************************************************************************
 * @file    sha.c
 * @brief   The application functions of SHA demo for the TOSHIBA
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
#include "sha.h"
/* external variables --------------------------------------------------------*/
extern uint32_t HashInit[8U];
extern uint32_t MsgLen[2U];
extern uint32_t RmnMsgLen[2U];
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the basic SHA configuration.
  * @param  None
  * @retval None
  */
void SHA_Config(void)
{
    /* Confirm calculation completion */
    while(SHA_GetCalculationStatus() != SHA_CALCULATION_COMPLETE) {};
    
    /* The Hash value specified with the SHAINITx register */
    SHA_SetInitMode(SHA_INIT_VALUE_REG);
    
    /* An interrupt is output at each calculation */
    SHA_SetCalculationInt(SHA_INT_EACH_CALCULATION);
    
    /* Set the Hash initial value */
    SHA_SetInitValue(HashInit);
    
    /* Set the whole message length and unhandled message length */
    SHA_SetMsgLen(MsgLen);
    SHA_SetRmnMsgLen(RmnMsgLen);
}

/**
  * @brief  To compare two two arrays.
  * @param  Src : pointer to point source buffer 
  * @param  Dst : pointer to point destination buffer   
  * @param  Len : how many data will be compared 
  * @retval SUCCESS: two Hash values are the same.
            ERROR: two Hash values are different.  
  */
Result HashValueCompare(const uint32_t * Src, const uint32_t * Dst, uint32_t Len)
{
    uint32_t tmp = 0U;
    Result result = SUCCESS;

    for (tmp = 0U; tmp < Len; tmp++) {
        if (Src[tmp] != Dst[tmp]) {
            result = ERROR;
            break;
        } else {
            /* Do nothing */
        }
    }

    return result;
}

/*********************************** END OF FILE ******************************/
