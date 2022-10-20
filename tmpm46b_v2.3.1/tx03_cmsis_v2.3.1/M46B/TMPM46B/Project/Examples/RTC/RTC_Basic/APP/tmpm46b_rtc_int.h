/**
 *******************************************************************************
 * @file    tmpm46b_rtc_int.h
 * @brief   All interrupt request functions prototypes of RTC
 *          for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/14
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_RTC_INT_H
#define __TMPM46B_RTC_INT_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* User ram declaration    */
volatile extern uint8_t fRTC_1HZ_INT;

void INTRTC_IRQHandler(void);

#endif                          /* __TMPM46B_RTC_INT_H */
