/** 
 *******************************************************************************
 * @file    led.h
 * @brief   LED functions prototypes for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/02/09
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "TMPM46B.h"
#include "tmpm46b_gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LED0         (0x0001U)
#define LED1         (0x0002U)
#define LED2         (0x0004U)
#define LED3         (0x0008U)
#define LED4         (0x0010U)
#define LED5         (0x0020U)
#define LED6         (0x0040U)
#define LED7         (0x0080U)
#define LED_ALL      (0x00FFU)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void LED_Init(void);
void LED_On(uint16_t led);
void LED_Off(uint16_t led);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* LED_H */
