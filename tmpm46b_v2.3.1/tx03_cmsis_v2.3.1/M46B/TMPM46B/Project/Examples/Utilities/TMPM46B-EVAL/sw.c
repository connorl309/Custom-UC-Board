/**
 ******************************************************************************
 * @file     sw.c
 * @brief    SW driver for the TOSHIBA 'TMPM46B' Device Series
 * @version  V0.100
 * @date     2015/02/09
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "sw.h"

/**
  * @brief  Initialize the GPIO to SW.
  *   SW0/4 connect with PJ0.
  *   SW1/5 connect with PJ1.
  *   SW2/6 connect with PJ2.
  *   SW3/7 connect with PJ3.
  * @param  None
  * @retval None
  */
void SW_Init(void)
{
    GPIO_SetInput(GPIO_PF,  GPIO_BIT_0 | GPIO_BIT_1 | GPIO_BIT_2 | GPIO_BIT_3);
}

/**
  * @brief  Get SW Value.
  * @param  sw: SW number
  *   This parameter can be from SW0 ~ SW7.
  * @retval SW value.
  */
uint8_t SW_Get(uint8_t sw)
{
    uint8_t tmp = 0U;
    switch (sw) {
    case SW0:
    case SW4:
        if (GPIO_ReadDataBit(GPIO_PF, GPIO_BIT_0) == 0U) {
            tmp = 1U;
        } else {
            /*Do nothing */
        }
        break;
    case SW1:
    case SW5:
        if (GPIO_ReadDataBit(GPIO_PF, GPIO_BIT_1) == 0U) {
            tmp = 1U;
        } else {
            /*Do nothing */
        }
        break;
    case SW2:
    case SW6:
        if (GPIO_ReadDataBit(GPIO_PF, GPIO_BIT_2) == 0U) {
            tmp = 1U;
        } else {
            /*Do nothing */
        }
        break;
    case SW3:
    case SW7:
        if (GPIO_ReadDataBit(GPIO_PF, GPIO_BIT_3) == 0U) {
            tmp = 1U;
        } else {
            /*Do nothing */
        }
        break;
    default:
        break;
    }
    
    return tmp;
}
