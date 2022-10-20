/**
 *******************************************************************************
 * @file    main.h
 * @brief   The header file of IGBT Two PPG for the TOSHIBA 'TMPM46B'
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
#include "sw.h"

/* For M46B: fperiph = fc = 16MHz*4 = 64MHz, T0 = fperiph = 64MHz, figbt = T0/2 = 32MHz */
#define IGBT_DEAD_TIME_5US      ((uint16_t)160)
#define IGBT_ACTIVE_PERIOD_20US ((uint16_t)640)
#define IGBT_PPG_PERIOD_50US    ((uint16_t)1600)

#define SWITCH_ON               (SW_Get(SW7) == 1U)

void IGBT_IO_Configuration(TSB_MT_TypeDef * IGBTx, IGBT_InitTypeDef * InitTypeDef);

#endif                          /* __MAIN_H */
