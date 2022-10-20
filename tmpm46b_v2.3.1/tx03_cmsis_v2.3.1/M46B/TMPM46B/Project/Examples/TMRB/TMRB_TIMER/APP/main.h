/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the header file of TMRB_TIMER demo for the TOSHIBA
 *          'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/03/17
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
#include "tmpm46b_tmrb.h"
#include "led.h"

/* Private define ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
uint16_t Tmrb_Calculator(uint16_t Tmrb_Require_us, uint32_t ClkDiv);
/* External function prototypes ----------------------------------------------*/

#endif
