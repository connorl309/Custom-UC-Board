/**
 *******************************************************************************
 * @file    main.h
 * @brief   The header file of IGBT One PPG for the TOSHIBA 'TMPM46B'
 *          Device Series
 * @version V0.100
 * @date    2015/03/21
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#include "tmpm46b_igbt.h"
#include "tmpm46b_gpio.h"
#include "led.h"

/* For M46B: fperiph = fc = 16MHz*4 = 64MHz, T0 = fperiph = 64MHz, figbt = T0/2 = 32MHz */
#define IGBT_PPG_PERIOD_50US    ((uint16_t)1600)

void IGBT_IO_Configuration(TSB_MT_TypeDef * IGBTx, IGBT_InitTypeDef * InitTypeDef);

#endif                          /* __MAIN_H */
