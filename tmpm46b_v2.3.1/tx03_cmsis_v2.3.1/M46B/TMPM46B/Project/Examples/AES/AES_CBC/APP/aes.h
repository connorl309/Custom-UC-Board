/**
 *******************************************************************************
 * @file    aes.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AES_H
#define __AES_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* External function prototypes ----------------------------------------------*/
void AES_Config(AES_OperationMode OperationMode);
Result TextCompare(uint32_t PlainText[3][4], uint32_t DecryptedText[3][4], uint32_t Line, uint32_t Row);

#endif                          /* __AES_H */
/*********************************** END OF FILE ******************************/
