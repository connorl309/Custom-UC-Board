/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of SIO_Demo for the TOSHIBA
 *          'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/13
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

uint8_t SIO0_TxBuffer[BufSize] = "MasterToSlave";
uint8_t SIO1_RxBuffer[BufSize] = { 0U };

uint8_t SIO1_TxBuffer[BufSize] = "SlaveToMaster";
uint8_t SIO0_RxBuffer[BufSize] = { 0U };

volatile uint8_t fSIO0TxOK = 1U;
volatile uint8_t fSIO1TxOK = 1U;
volatile uint8_t gSIO0WrIndex = 0U;
volatile uint8_t gSIO1RdIndex = 0U;
volatile uint8_t gSIO1WrIndex = 0U;
volatile uint8_t gSIO0RdIndex = 0U;

void SIO_Configure(void);

/**
  * @brief  main  function
  * @param  None
  * @retval int
  */
int main(void)
{
    SIO_InitTypeDef SIO0_Init, SIO1_Init;

    /* configure the IO port of SIO */
    SIO_Configure();
    /* configure the SIO0 channel */
    SIO_Enable(SIO0);

    /* initialize the SIO0 struct */
    SIO0_Init.InputClkEdge = SIO_SCLKS_TXDF_RXDR;
    SIO0_Init.TIDLE = SIO_TIDLE_HIGH;
    SIO0_Init.IntervalTime = SIO_SINT_TIME_SCLK_8;
    SIO0_Init.TransferMode = SIO_TRANSFER_FULLDPX;
    SIO0_Init.TransferDir = SIO_LSB_FRIST;
    SIO0_Init.Mode = SIO_ENABLE_TX | SIO_ENABLE_RX;
    SIO0_Init.DoubleBuffer = SIO_WBUF_ENABLE;
    SIO0_Init.BaudRateClock = SIO_BR_CLOCK_TS2;
    SIO0_Init.Divider = SIO_BR_DIVIDER_2;

    SIO_Init(SIO0, SIO_CLK_SCLKOUTPUT, &SIO0_Init);

    /* configure the SIO1 channel */
    SIO_Enable(SIO1);

    /* initialize the SIO1 struct */
    SIO1_Init.InputClkEdge = SIO_SCLKS_TXDF_RXDR;
    SIO1_Init.TIDLE = SIO_TIDLE_HIGH;
    SIO1_Init.TransferMode = SIO_TRANSFER_FULLDPX;
    SIO1_Init.TransferDir = SIO_LSB_FRIST;
    SIO1_Init.Mode = SIO_ENABLE_TX | SIO_ENABLE_RX;
    SIO1_Init.DoubleBuffer = SIO_WBUF_ENABLE;
    SIO1_Init.TXDEMP = SIO_TXDEMP_HIGH;
    SIO1_Init.EHOLDTime = SIO_EHOLD_FC_64;

    SIO_Init(SIO1, SIO_CLK_SCLKINPUT, &SIO1_Init);

    /* enable SIO0 Channel TX interrupt */
    NVIC_EnableIRQ(INTTX0_IRQn);
    /* enable SIO1 Channel RX interrupt */
    NVIC_EnableIRQ(INTRX1_IRQn);

    /* enable SIO1 Channel TX interrupt */
    NVIC_EnableIRQ(INTTX1_IRQn);
    /* enable SIO0 Channel RX interrupt */
    NVIC_EnableIRQ(INTRX0_IRQn);

    while (1) {
        /* SIO1 send data from TXD1 */
        if (fSIO1TxOK == 1U) {
            fSIO1TxOK = 0U;
            SIO_SetTxData(SIO1, SIO1_TxBuffer[gSIO1WrIndex++]);
        } else {
            /* Do Nothing */
        }

        /* SIO0 send data from TXD0 */
        if (fSIO0TxOK == 1U) {
            fSIO0TxOK = 0U;
            SIO_SetTxData(SIO0, SIO0_TxBuffer[gSIO0WrIndex++]);
        } else {
            /* Do Nothing */
        }

       /*SIO0 receive data end */
        if (gSIO0RdIndex >= BufSize) {
            fSIO1TxOK = 0U;
            SIO_Disable(SIO1);
        } else {
            /* Do Nothing */
        }
        /* SIO1 receive data end */
        if (gSIO1RdIndex >= BufSize) {
            fSIO0TxOK = 0U;
            SIO_Disable(SIO0);
        } else {
            /* Do Nothing */
        }

        /* Print receive buffer */
        if ((gSIO0RdIndex == BufSize) && (gSIO1RdIndex == BufSize)){
#ifdef DEBUG
            printf((char *)SIO0_RxBuffer);
            printf((char *)SIO1_RxBuffer);
#endif
        }
    }
}

/**
  * @brief  configure the IO port of SIO
  * @param  None
  * @retval None
  */
void SIO_Configure(void)
{
    /* Set PE2 as TXD0 */
    TSB_PE->CR |= GPIO_BIT_2;
    TSB_PE->FR1 |= GPIO_BIT_2;

    /* Set PE1 as RXD0 */
    TSB_PE->FR1 |= GPIO_BIT_1;
    TSB_PE->IE |= GPIO_BIT_1;

    /* Set PE5 as TXD1 */
    TSB_PE->CR |= GPIO_BIT_5;
    TSB_PE->FR1 |= GPIO_BIT_5;

    /* Set PE6 as RXD1 */
    TSB_PE->FR1 |= GPIO_BIT_6;
    TSB_PE->IE |= GPIO_BIT_6;

    /* Set PE3 as SCLK0 output */
    TSB_PE->FR1 |= GPIO_BIT_3;
    TSB_PE->CR |= GPIO_BIT_3;

    /* Set PE4 as SCLK1 input */
    TSB_PE->FR1 |= GPIO_BIT_4;
    TSB_PE->IE |= GPIO_BIT_4;
}

/**
  * @brief  Deal with the error parameter
  * @param  file: Pointer to the file where the error parameter locates
  * @param  line: Number of the line in which the error parameter locates
  * @retval None
  */
#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
