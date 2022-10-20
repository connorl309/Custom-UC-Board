/**
 *******************************************************************************
 * @file    main.h
 * @brief   the application functions of CG demo for the TOSHIBA
 *          'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/03/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_gpio.h"
#include "tmpm46b_cg.h"
#include "sw.h"
#include "led.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Set External interrupt pin's PORT/Bit, Interrupt Number */
#define     GPIO_ExtINTSrc          GPIO_PC
#define     Bit_ExtINTSrc           GPIO_BIT_1
#define     CG_ExtINTSrc            CG_INT_SRC_F
#define     ExtINTSrc_IRQn          INTF_IRQn
#define     ExtINTSrc_IRQHandler    INTF_IRQHandler

#define     LED_EXT                 LED3
#define     LED_OTHER               LED0
#define     LED_SW                  LED2

#define     CG_SW                   SW1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void GPIO_ExtIntSrc(void);
void enter_IDLE(void);

#endif
/*********************************** END OF FILE ******************************/
