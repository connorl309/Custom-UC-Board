/**
 *******************************************************************************
 * @file    tmpm46b_i2c_int.c
 * @brief   The I2C ISR of I2C slave demo for the
 *          TOSHIBA 'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/02/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

#include "tmpm46b_i2c_int.h"

/**
  * @brief  Interrupt Service Routine for I2C2
  * @param  None
  * @retval None
  */
void INTI2C2_IRQHandler(void)
{
    TSB_I2C_TypeDef *I2Cx;
    I2C_State I2C_sr;

    I2Cx = TSB_I2C2;
    I2C_sr = I2C_GetState(I2Cx);

    if (I2C_sr.Bit.MasterSlave) {       /* Master mode */
        if (I2C_sr.Bit.TRx) {   /* Tx mode */
            if (I2C_sr.Bit.LastRxBit) { /* LRB=1: the receiver requires no further data. */
                I2C_GenerateStop(I2Cx);
            } else {            /* LRB=0: the receiver requires further data. */
                if (gI2CWCnt <= gI2CTxDataLen) {
                    I2C_SetSendData(I2Cx, gI2CTxData[gI2CWCnt]);        /* Send next data */
                    gI2CWCnt++;
                } else {        /* I2C data send finished. */
                    I2C_GenerateStop(I2Cx);  /* Stop I2C */
                }
            }
        } else {                /* Rx Mode */
            /* Do nothing */
        }
    } else {                    /* Slave mode */
        /* Do nothing */
    }
}

/**
  * @brief  Interrupt Service Routine for I2C0
  * @param  None
  * @retval None
  */
void INTI2C0_IRQHandler(void)
{
    uint32_t tmp = 0U;
    TSB_I2C_TypeDef *I2Cy;
    I2C_State I2C0_sr;

    I2Cy = TSB_I2C0;
    I2C0_sr = I2C_GetState(I2Cy);

    if (!I2C0_sr.Bit.MasterSlave) {     /* Slave mode */
        if (!I2C0_sr.Bit.TRx) { /* Rx Mode */
            if (I2C0_sr.Bit.SlaveAddrMatch) {
                /* First read is dummy read for Slave address recognize */
                tmp = I2C_GetReceiveData(I2Cy);
                gI2CRCnt = 0U;
            } else {
                /* Read I2C received data and save to I2C_RxData buffer */
                tmp = I2C_GetReceiveData(I2Cy);
                gI2CRxData[gI2CRCnt] = tmp;
                gI2CRCnt++;
            }
        } else {                /* Tx Mode */
            /* Do nothing */
        }
    } else {                    /* Master mode */
        /* Do nothing */
    }
}
