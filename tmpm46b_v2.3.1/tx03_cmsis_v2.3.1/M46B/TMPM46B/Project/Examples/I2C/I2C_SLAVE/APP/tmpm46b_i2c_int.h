/**
 *******************************************************************************
 * @file    tmpm46b_i2c_int.h
 * @brief   The header file for I2C ISR of I2C slave demo for the
 *          TOSHIBA 'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/02/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_I2C_INT_H
#define __TMPM46B_I2C_INT_H

#include "main.h"

void INTI2C2_IRQHandler(void);
void INTI2C0_IRQHandler(void);

#endif                          /* __TMPM46B_I2C_INT_H */
