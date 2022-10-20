/**
 *******************************************************************************
 * @file    mla.h
 * @brief   The application functions of MLA_ADD demo for the TOSHIBA
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
#ifndef __MLA_H
#define __MLA_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* External function prototypes ----------------------------------------------*/
void MLA_Config(uint8_t ABlkNum, uint8_t BBlkNum, uint8_t WBlkNum);
Result MLAValueCompare(const uint32_t * Src, const uint32_t * Dst, uint32_t Len);
void Delay(void);

#endif                          /* __MLA_H */
/*********************************** END OF FILE ******************************/
