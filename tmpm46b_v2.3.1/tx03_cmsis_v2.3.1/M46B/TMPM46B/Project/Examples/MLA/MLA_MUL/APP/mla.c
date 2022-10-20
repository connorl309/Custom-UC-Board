/**
 *******************************************************************************
 * @file    mla.c
 * @brief   The application functions of MLA_MUL demo for the TOSHIBA
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
#include "mla.h"
/* external variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the basic MLA configuration.
  * @param  CalculationMode: Select the operation mode
  *   This parameter can be one of the following values:
  *   MLA_COM_MODE_MUL, MLA_COM_MODE_ADD, MLA_COM_MODE_SUB.
  * @param  ABlkNum, BBlkNum and WBlkNum: Data block number.
  *   This parameter can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31.
  * @retval None
  */
void MLA_Config(uint8_t ABlkNum, uint8_t BBlkNum, uint8_t WBlkNum)
{
    /* Check the parameters */
    assert_param(IS_MLA_BLK_NUM(ABlkNum));
    assert_param(IS_MLA_BLK_NUM(BBlkNum));
    assert_param(IS_MLA_BLK_NUM(WBlkNum));
    
    /* Set the data block number */
    MLA_SetADataBlkNum(ABlkNum);
    Delay();
    MLA_SetBDataBlkNum(BBlkNum);
    Delay();
    MLA_SetWDataBlkNum(WBlkNum);
    Delay();
    
    /* Set the calculation mode */
    MLA_SetCalculationMode(MLA_COM_MODE_MUL);
}

/**
  * @brief  To compare two arrays.
  * @param  Src : pointer to point source buffer 
  * @param  Dst : pointer to point destination buffer   
  * @param  Len : how many data will be compared 
  * @retval SUCCESS: two Hash values are the same.
            ERROR: two Hash values are different.  
  */
Result MLAValueCompare(const uint32_t * Src, const uint32_t * Dst, uint32_t Len)
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

/**
  * @brief  Delay.
  * @param  None
  * @retval None
  */
void Delay(void)
{
    uint32_t tmp;
    for (tmp = 0U; tmp < 0x5ffffU; tmp++);

}

/*********************************** END OF FILE ******************************/
