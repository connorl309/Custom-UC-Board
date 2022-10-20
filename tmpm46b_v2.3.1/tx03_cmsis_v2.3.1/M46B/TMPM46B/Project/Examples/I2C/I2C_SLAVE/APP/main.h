/**
 *******************************************************************************
 * @file    main.h
 * @brief   The header file for main.c of I2C slave demo for the
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
#ifndef __MAIN_H
#define __MAIN_H

#include "sw.h"
#include "common_uart.h"
#include "tmpm46b_gpio.h"
#include "tmpm46b_i2c.h"
#include "tmpm46b_uart.h"

#define SELF_ADDR            ((uint8_t)0xE0)
#define SLAVE_ADDR           ((uint8_t)0xB0)
#define I2C_SEND             ((uint32_t)0x00000000)
#define I2C_RECEIVE          ((uint32_t)0x00000001)

#define MODE_I2C_IDLE        ((uint8_t)0x00)
#define MODE_I2C_INITIAL     ((uint8_t)0x10)
#define MODE_I2C_START       ((uint8_t)0x20)
#define MODE_I2C_TRX         ((uint8_t)0x21)
#define MODE_I2C_FINISHED    ((uint8_t)0x30)
#define MODE_I2C_CHECK       ((uint8_t)0x31)

extern uint32_t gI2CWCnt;
extern uint32_t gI2CRCnt;
extern uint32_t gI2CTxDataLen;
extern char gI2CTxData[16];
extern uint32_t gI2CRxDataLen;
extern char gI2CRxData[16];

void I2C2_IO_Configuration(void);
void I2C0_IO_Configuration(void);

#endif                          /* __MAIN_H */
