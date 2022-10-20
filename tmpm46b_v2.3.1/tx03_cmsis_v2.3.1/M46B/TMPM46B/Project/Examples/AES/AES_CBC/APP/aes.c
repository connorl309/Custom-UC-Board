/**
 *******************************************************************************
 * @file    aes.c
 * @brief   The application functions of AES_CBC demo for the TOSHIBA
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
extern uint32_t EncryptionKey[6U];
extern uint32_t DecryptionKey[6U];
extern uint32_t InitVector[4U];
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the basic AES configuration.
  * @param  OperationMode: Select the operation mode
  *   This parameter can be one of the following values:
  *   AES_ENCRYPTION_MODE, AES_DECRYPTION_MODE.
  * @retval None
  */
void AES_Config(AES_OperationMode OperationMode)
{
    AES_InitTypeDef InitStruct = { AES_ENCRYPTION_MODE };

    /* Check the parameters */
    assert_param(IS_AES_OPERATION_MODE(OperationMode));

    /* Define the init structure */
    InitStruct.AlgorithmMode = AES_CBC_MODE;
    InitStruct.KeyLength = AES_KEY_LENGTH_192;
    if (OperationMode == AES_ENCRYPTION_MODE) {
        InitStruct.OperationMode = AES_ENCRYPTION_MODE;
    } else {
        InitStruct.OperationMode = AES_DECRYPTION_MODE;
    }

    /* Confirm calculation completion */
    while (AES_GetArithmeticStatus() != AES_CALCULATION_COMPLETE){}
    /* Clear the FIFO. */
    AES_ClrFIFO();
    if (OperationMode == AES_ENCRYPTION_MODE) {
        /* Set the encryption key data */
        AES_SetKey(AES_KEY_LENGTH_192, EncryptionKey);
    } else {
        /* Set the decryption key data */
        AES_SetKey(AES_KEY_LENGTH_192, DecryptionKey);
    }
    /* Input initial vector */
    AES_SetVectorInit(InitVector);
    
    /* Initialize AES to CBC mode, 192-bit key length */
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
