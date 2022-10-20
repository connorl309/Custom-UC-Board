/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of FUART_LoopBack demo for the
 *          TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/13
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* include file */
#include "main.h"

/* Before running the program, we need to decide whether to use the UT0RTS and UT0CTS flow control
 * If RUN_NONE_FLOW_CONTROL is undefined, UT0RTS and UT0CTS flow control will be enabled in the program.
 * If RUN_NONE_FLOW_CONTROL is defined, there will be no flow control in the program 
 */
#define RUN_NONE_FLOW_CONTROL

#define MAX_BUFSIZE  64U

int main(void)
{
    
    TestResult result = DIFF;
    FUART_StorageStatus FIFOStatus;
    uint32_t cntTx = 0U;
    uint32_t cntRx = 0U;
    uint8_t SW0_last = 0U;
    uint8_t SW0_this = 0U;
    char rxnum[2] = { 0 };

    uint32_t receive = 0U;      /* received data */
    uint32_t rxlast = 0U;       /* received data number after last reception */
    uint32_t rxthis = 0U;       /* received data number after this reception */
    uint32_t Rx_Buf[MAX_BUFSIZE] = { 0U };
    uint32_t Tx_Buf[MAX_BUFSIZE] = { 0U };

    uint32_t i = 0U;
    for (; i < MAX_BUFSIZE; i++) {
        Tx_Buf[i] = i;
    }

    LED_Init();
    SW_Init();
    hardware_init(UART_RETARGET);
    FUART_GPIOConfig();         /* Configure GPIO for FUART0 */
    FUART_ChInit();             /* Initialize FUART0 */

    FUART_Enable(FUART0);
    FUART_EnableFIFO(FUART0);
    FUART_SetINTFIFOLevel(FUART0, FUART_RX_FIFO_LEVEL_16, FUART_TX_FIFO_LEVEL_4);
    SW0_this = SW_Get(SW0);
    while (1) {
        if (cntTx < MAX_BUFSIZE) {
            FIFOStatus = FUART_GetStorageStatus(FUART0, FUART_TX);
            if ((FIFOStatus == FUART_STORAGE_EMPTY)
                || (FIFOStatus == FUART_STORAGE_NORMAL)) {
                FUART_SetTxData(FUART0, Tx_Buf[cntTx]);
                LED_TXDataDisplay(Tx_Buf[cntTx]);
                cntTx++;
                if (64U == cntTx) {
                    LED_On(LED_ALL);    /* sending data is finished */
                }
            }
        }

        SW0_last = SW0_this;
        SW0_this = SW_Get(SW0);
        if (SW0_last != SW0_this) {     /* turn the switch SW0 */
            while (FUART_STORAGE_EMPTY != FUART_GetStorageStatus(FUART0, FUART_RX)) {
                receive = FUART_GetRxData(FUART0);
                Rx_Buf[cntRx] = receive;
                cntRx++;
            }

            rxlast = rxthis;
            rxthis = cntRx;

            if (rxlast != rxthis) {     /* there are some data that has been received  */
                common_uart_disp("\nLAST RX DATA: ");
                rxnum[0] = ('0' + receive / 10U);
                rxnum[1] = ('0' + receive % 10U);
                common_uart_disp(rxnum);
            } else {            /* receiving data is finished */
                common_uart_disp("\nRX FINISH");
                result = Buffercompare(Tx_Buf, Rx_Buf, MAX_BUFSIZE);
                if (result == SAME) {
                    /* received data are same with transmitted data */
                    /* UT0RTS and UT0CTS flow control has worked normally */
                    common_uart_disp("\nRX TX SAME");
                    while (1) {
                    }
                } else {
                    /* received data are different with transmitted data */
                    /* UT0RTS and UT0CTS flow control doesn't work */
                    common_uart_disp("\nRX TX DIFF");
                    while (1) {
                    }
                }
            }
        }
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif

/**
  * @brief  Compare Received data and Transmitted data
  * @param  Src : pointer to point source buffer
  * @param  Dst : pointer to point destination buffer
  * @param  Len : The length of data buffer
  * @retval SAME: received data are same with transmitted data
            DIFF: received data are different with transmitted data
  */
TestResult Buffercompare(const uint32_t * Src, const uint32_t * Dst, uint32_t Len)
{
    uint32_t tmp = 0U;
    TestResult result = SAME;

    for (tmp = 0U; tmp < Len; tmp++) {
        if (Src[tmp] != Dst[tmp]) {
            result = DIFF;
            break;
        } else {
        }
    }

    return result;
}

/**
  * @brief  use LEDs to display the data set to transmit FIFO
  * @param  the data set to transmit FIFO
  * @retval None
  */
void LED_TXDataDisplay(uint32_t dat)
{
    uint16_t tmp = 0U;
    uint16_t portstate = 0U;    /* port B state */

    tmp = (uint16_t) dat;
    tmp = 1 << (dat % 4);
    portstate = GPIO_ReadData(GPIO_PB);
    portstate &= 0xFFF0U;
    portstate |= tmp;
    GPIO_WriteData(GPIO_PB, portstate);
}

/**
  * @brief  Configure GPIO for Full UART pins, UT0TXD, UT0RXD, UT0CTS, UT0RTS
  * @param  None
  * @retval None
  */
void FUART_GPIOConfig(void)
{
    /* Configure port PF1 to be UT0TXD */
    GPIO_SetOutput(GPIO_PF, GPIO_BIT_1);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_3, GPIO_BIT_1);

    /* Configure port PF2 to be UT0RXD */
    GPIO_SetInput(GPIO_PF, GPIO_BIT_2);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_3, GPIO_BIT_2);

    /* Configure port PF0 to be UT0CTS */
    GPIO_SetInput(GPIO_PF, GPIO_BIT_0);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_3, GPIO_BIT_0);

    /* Configure port PF3 to be UT0RTS */
    GPIO_SetOutput(GPIO_PF, GPIO_BIT_3);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_3, GPIO_BIT_3);
}

/**
  * @brief  Initialize Full UART channel 0
  * @param  None
  * @retval None
  */
void FUART_ChInit(void)
{
    FUART_InitTypeDef myFUART;

    myFUART.BaudRate = 300U;
    myFUART.DataBits = FUART_DATA_BITS_8;
    myFUART.StopBits = FUART_STOP_BITS_1;
    myFUART.Parity = FUART_1_PARITY;
    myFUART.Mode = FUART_ENABLE_TX | FUART_ENABLE_RX;

#ifdef RUN_NONE_FLOW_CONTROL
    myFUART.FlowCtrl = FUART_NONE_FLOW_CTRL;
#else
    myFUART.FlowCtrl = FUART_CTS_FLOW_CTRL | FUART_RTS_FLOW_CTRL;
#endif

    FUART_Init(FUART0, &myFUART);
}
