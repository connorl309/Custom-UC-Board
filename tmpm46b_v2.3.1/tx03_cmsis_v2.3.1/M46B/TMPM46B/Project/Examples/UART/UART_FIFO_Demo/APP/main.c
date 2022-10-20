/** 
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of UART_FIFO_Demo for the TOSHIBA
 *          'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/03/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
#include "main.h"
#include "tmpm46b_uart.h"

#include <stdio.h>

#define BufSize (sizeof(TxBuffer) / sizeof(*(TxBuffer)))
#define BufSize1 (sizeof(TxBuffer1) / sizeof(*(TxBuffer1)))

uint8_t TxBuffer[] = "TMPM46B1";
uint8_t RxBuffer[BufSize] = { 0U };
uint8_t TxBuffer1[] = "TMPM46B2";
uint8_t RxBuffer1[BufSize1] = { 0U };

const uint8_t NumToBeTx = BufSize - 1U;
const uint8_t NumToBeTx1 = BufSize1 - 1U;

uint8_t TxCounter = 0U;
uint8_t RxCounter = 0U;

uint8_t TxCounter1 = 0U;
uint8_t RxCounter1 = 0U;

UART_InitTypeDef myUART;

void SIO_Configuration(TSB_SC_TypeDef * SCx);
void ResetIdx(void);

int main(void)
{
    /* Initialize system */

    SIO_Configuration(UART0);
    SIO_Configuration(UART3);

    myUART.BaudRate = (uint32_t)115200;
    myUART.DataBits = UART_DATA_BITS_8;
    myUART.StopBits = UART_STOP_BITS_1;
    myUART.Parity = UART_NO_PARITY;
    myUART.Mode =  UART_ENABLE_TX|UART_ENABLE_RX;
    myUART.FlowCtrl = UART_NONE_FLOW_CTRL;

    UART_Enable(UART0);
    UART_Init(UART0, &myUART);

    UART_Enable(UART3);
    UART_Init(UART3, &myUART);   

    UART_RxFIFOByteSel(UART0,UART_RXFIFO_RXFLEVEL);
    UART_RxFIFOByteSel(UART3,UART_RXFIFO_RXFLEVEL);

    UART_TxFIFOINTCtrl(UART0,ENABLE);
    UART_TxFIFOINTCtrl(UART3,ENABLE);

    UART_RxFIFOINTCtrl(UART0,ENABLE);
    UART_RxFIFOINTCtrl(UART3,ENABLE);

    UART_TRxAutoDisable(UART0,UART_RXTXCNT_AUTODISABLE);
    UART_TRxAutoDisable(UART3,UART_RXTXCNT_AUTODISABLE);

    UART_FIFOConfig(UART0,ENABLE); 
    UART_FIFOConfig(UART3,ENABLE); 

    UART_RxFIFOFillLevel(UART0,UART_RXFIFO4B_FLEVLE_4_2B);
    UART_RxFIFOFillLevel(UART3,UART_RXFIFO4B_FLEVLE_4_2B);

    UART_RxFIFOINTSel(UART0,UART_RFIS_REACH_EXCEED_FLEVEL);
    UART_RxFIFOINTSel(UART3,UART_RFIS_REACH_EXCEED_FLEVEL);

    UART_RxFIFOClear(UART0);
    UART_RxFIFOClear(UART3);    

    UART_TxFIFOFillLevel(UART0,UART_TXFIFO4B_FLEVLE_0_0B);
    UART_TxFIFOFillLevel(UART3,UART_TXFIFO4B_FLEVLE_0_0B);

    UART_TxFIFOINTSel(UART0,UART_TFIS_REACH_NOREACH_FLEVEL);
    UART_TxFIFOINTSel(UART3,UART_TFIS_REACH_NOREACH_FLEVEL);

    UART_TxFIFOClear(UART0); 
    UART_TxFIFOClear(UART3);

    NVIC_EnableIRQ(INTTX0_IRQn);
    NVIC_EnableIRQ(INTRX3_IRQn);

    NVIC_EnableIRQ(INTTX3_IRQn);
    NVIC_EnableIRQ(INTRX0_IRQn);
    while (1) {
        UART_SetTxData(UART0, (uint32_t) (TxBuffer[TxCounter++])); 
        UART_SetTxData(UART3, (uint32_t) (TxBuffer1[TxCounter1++]));
        while (RxCounter < NumToBeTx) {
            /* Do nothing */
        }

        while (RxCounter1 < NumToBeTx1) {
            /* Do nothing */
        }
#ifdef DEBUG
        printf("%s\n", RxBuffer1);
        printf("%s\n", RxBuffer);
#endif
        ResetIdx();
    }
}

void ResetIdx(void)
{
    uint8_t i = 0U;

    for (i = 0U; i <= RxCounter; i++) {
        RxBuffer[i] = 0U;
    }
    for (i = 0U; i <= RxCounter1; i++) {
        RxBuffer1[i] = 0U;
    }  
    TxCounter = 0U;
    RxCounter = 0U;
    
    TxCounter1 = 0U;
    RxCounter1 = 0U;
}

void SIO_Configuration(TSB_SC_TypeDef * SCx)
{
    if (SCx == TSB_SC0) {
        GPIO_SetOutputEnableReg(GPIO_PE, GPIO_BIT_2, ENABLE);
        GPIO_SetInputEnableReg(GPIO_PE, GPIO_BIT_2, DISABLE);
        GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_1, GPIO_BIT_2);
        GPIO_SetOutputEnableReg(GPIO_PE, GPIO_BIT_1, DISABLE);
        GPIO_SetInputEnableReg(GPIO_PE, GPIO_BIT_1, ENABLE);
        GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_1, GPIO_BIT_1);
    } else if (SCx == TSB_SC1) {
        GPIO_SetOutputEnableReg(GPIO_PE, GPIO_BIT_5, ENABLE);
        GPIO_SetInputEnableReg(GPIO_PE, GPIO_BIT_5, DISABLE);
        GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_1, GPIO_BIT_5);
        GPIO_SetOutputEnableReg(GPIO_PE, GPIO_BIT_6, DISABLE);
        GPIO_SetInputEnableReg(GPIO_PE, GPIO_BIT_6, ENABLE);
        GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_1, GPIO_BIT_6);
    } else if (SCx == TSB_SC2) {
        GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_2, ENABLE);
        GPIO_SetInputEnableReg(GPIO_PL, GPIO_BIT_2, DISABLE);
        GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_5, GPIO_BIT_2);
        GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_1, DISABLE);
        GPIO_SetInputEnableReg(GPIO_PL, GPIO_BIT_1, ENABLE);
        GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_5, GPIO_BIT_1);
    } else if (SCx == TSB_SC3) {
        GPIO_SetOutputEnableReg(GPIO_PB, GPIO_BIT_0, ENABLE);
        GPIO_SetInputEnableReg(GPIO_PB, GPIO_BIT_0, DISABLE);
        GPIO_EnableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_0);
        GPIO_SetOutputEnableReg(GPIO_PB, GPIO_BIT_1, DISABLE);
        GPIO_SetInputEnableReg(GPIO_PB, GPIO_BIT_1, ENABLE);
        GPIO_EnableFuncReg(GPIO_PB, GPIO_FUNC_REG_3, GPIO_BIT_1);
    }
}


/**
  * @brief  Delay some time
  * @param  None
  * @retval None
  */
void delay(void)
{
    uint32_t i = 0U;
    for(i = 0U; i<0xFFFFU; i++){
      /* Do nothing */
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    printf("Err!");
    while (1) {
        __NOP();
    }
}
#endif
