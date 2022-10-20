/** 
 *******************************************************************************
 * @file    tmpm46b_sio_int.h
 * @brief   the application functions of SIO_Demo
 * @version V0.100
 * @date    2015/03/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIOINT_H
#define __SIOINT_H
/* Includes ------------------------------------------------------------------*/

#include "tmpm46b_uart.h"
#include <stdio.h>


extern volatile uint8_t fSIO0TxOK;
extern volatile uint8_t fSIO1TxOK;
extern volatile uint8_t gSIO1RdIndex;
extern volatile uint8_t gSIO0RdIndex;
extern uint8_t SIO1_RxBuffer[];
extern uint8_t SIO0_RxBuffer[];

void INTTX0_IRQHandler(void);
void INTRX1_IRQHandler(void);
void INTTX1_IRQHandler(void);
void INTRX0_IRQHandler(void);
#endif
