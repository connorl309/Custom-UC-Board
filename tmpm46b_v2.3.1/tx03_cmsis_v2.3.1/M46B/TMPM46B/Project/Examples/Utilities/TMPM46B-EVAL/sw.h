/** 
 *******************************************************************************
 * @file    sw.h
 * @brief   SW functions prototypes for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/02/09
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SW_H
#define __SW_H

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "TMPM46B.h"
#include "tmpm46b_gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SW0         (0U)
#define SW1         (1U)
#define SW2         (2U)
#define SW3         (3U)
#define SW4         (4U)
#define SW5         (5U)
#define SW6         (6U)
#define SW7         (7U)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SW_Init(void);
uint8_t SW_Get(uint8_t sw);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* SW_H */
