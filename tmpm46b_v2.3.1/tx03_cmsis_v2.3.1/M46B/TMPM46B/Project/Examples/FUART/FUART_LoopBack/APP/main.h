/** 
 *******************************************************************************
 * @file    main.h
 * @brief   The application functions of FUART_LoopBack demo for the
 *          TOSHIBA 'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/03/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_fuart.h"
#include "tmpm46b_gpio.h"
#include "led.h"
#include "sw.h"
#include "stdio.h"
#include "common_uart.h"

typedef enum {
    DIFF = 0U,
    SAME = 1U
} TestResult;

extern void Delay(uint32_t time);
void LED_TXDataDisplay(uint32_t dat);
TestResult Buffercompare(const uint32_t * Src, const uint32_t * Dst, uint32_t Len);
void FUART_GPIOConfig(void);
void FUART_ChInit(void);

#endif
