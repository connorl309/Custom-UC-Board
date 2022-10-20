/** 
 *******************************************************************************
 * @file    main.h
 * @brief   the header file of TMRB_PPG demo for the TOSHIBA
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
#include "tmrb_leadingtimingdisplay.h"
#include "common_uart.h"
#include "sw.h"
/* Private define ------------------------------------------------------------*/

#define LEADINGMAX         0x05U   /* LEADING RATE COUNTER MAX */
#define LEADINGINIT        0U      /* LEADING RATE COUNTER Initialize */
#define KEYPORT            GPIO_PJ /* KEY input port, according to board */

/* External function prototypes ----------------------------------------------*/
#endif
