/**
 *******************************************************************************
 * @file    tmpm46b_uart_int.h
 * @brief   all interrupt request functions prototypes of UART (Serial Channel)
 *          for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_UART_INT_H
#define __TMPM46B_UART_INT_H

/* Includes ------------------------------------------------------------------*/
#include "TMPM46B.h"
#include "tmpm46b_uart.h"


void INTTX0_IRQHandler(void);
void INTRX3_IRQHandler(void);

void INTRX0_IRQHandler(void);
void INTTX3_IRQHandler(void);
#endif                          /* __TMPM46B_UART_INT_H */
