/**
 *******************************************************************************
 * @file    sha.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SHA_H
#define __SHA_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* External function prototypes ----------------------------------------------*/
void SHA_Config(void);
Result HashValueCompare(const uint32_t * Src, const uint32_t * Dst, uint32_t Len);

#endif                          /* __SHA_H */
/*********************************** END OF FILE ******************************/
