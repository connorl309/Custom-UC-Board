/**
 ******************************************************************************
 * @file     led.c
 * @brief    LED driver for the TOSHIBA 'TMPM46B' Device Series
 * @version  V0.100
 * @date     2015/02/09
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "led.h"

/**
  * @brief  Initialize LED ports.
  *   LED0~3 connect with PB0~3.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
    /* Set PB0 ~ PB3 as output and turn off LED0 ~ LED3 */
    GPIO_SetOutput(GPIO_PF, GPIO_BIT_4 | GPIO_BIT_5 | GPIO_BIT_6 | GPIO_BIT_7);
    GPIO_WriteDataBit(GPIO_PF, GPIO_BIT_4 | GPIO_BIT_5 | GPIO_BIT_6 | GPIO_BIT_7, GPIO_BIT_VALUE_0);
}

/**
  * @brief  Turn on input LED.
  * @param  led: LED number
  *   This parameter can be one of the following values:
  *   LED0, LED1, LED2, LED3 or LED_ALL.
  * @retval None
  */
void LED_On(uint16_t led)
{
    uint16_t tmp;
    tmp = GPIO_ReadData(GPIO_PF);
    tmp |= led;
    GPIO_WriteData(GPIO_PF, tmp);
}

/**
  * @brief  Turn off input LED.
  * @param  led: LED number
  *   This parameter can be one of the following values:
  *   LED0, LED1, LED2, LED3 or LED_ALL.
  * @retval None
  */
void LED_Off(uint16_t led)
{
    uint16_t tmp;
    tmp = GPIO_ReadData(GPIO_PF);
    tmp &= (uint16_t) (~led);
    GPIO_WriteData(GPIO_PF, tmp);
}
