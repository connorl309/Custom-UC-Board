/**
 *******************************************************************************
 * @file    aes.c
 * @brief   The application functions of AES_CTR demo for the TOSHIBA
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
#include "aes.h"
/* external variables --------------------------------------------------------*/
extern uint32_t Key[6U];
extern uint32_t CounterValue[4U];
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the basic AES configuration.
  * @param  None.
  * @retval None.
  */
void AES_Config(void)
{
    AES_InitTypeDef InitStruct = { AES_ENCRYPTION_MODE };

    /* Define the init structure */
    InitStruct.AlgorithmMode = AES_CTR_MODE;
    InitStruct.KeyLength = AES_KEY_LENGTH_192;
    /* In CTR mode, set "0" for both encryption and decryption. */
    InitStruct.OperationMode = AES_ENCRYPTION_MODE;

    /* Confirm calculation completion */
    while (AES_GetArithmeticStatus() != AES_CALCULATION_COMPLETE){}
    /* Clear the FIFO. */
    AES_ClrFIFO();
    /* Set the decryption key data */
    AES_SetKey(AES_KEY_LENGTH_192, Key);
    /* Input counter value */
    AES_SetCntInit(CounterValue);
    
    /* Initialize AES to CTR mode, 192-bit key length */
    AES_Init(&InitStruct);
}

/**
  * @brief  Compare the two two-dimensional arrays.
  * @param  PlainText: A two-dimensional array.
  * @param  DecryptedText: A two-dimensional array.
  * @param  Line: Array line.
  * @param  Row: Array row.
  * @retval Result: Compare result.
  *   The value returned can be one of the following values:
  *   SUCCESS: The two two-dimensional arrays are equal.
  *   ERROR: The two two-dimensional arrays are different.
  */
Result TextCompare(uint32_t PlainText[3][4], uint32_t DecryptedText[3][4], uint32_t Line, uint32_t Row)
{
    Result result = SUCCESS;
    uint32_t i = 0U;
    uint32_t j = 0U;

    for (i = 0U; i < Line; i++) {
        for (j = 0U; j < Row; j++){
            if (*(*(PlainText + i) + j) != *(*(DecryptedText + i) + j)) {
                result = ERROR;
                break;
            } else {
                /* Do nothing */
            }
        }
    }

    return result;
}

/*********************************** END OF FILE ******************************/
