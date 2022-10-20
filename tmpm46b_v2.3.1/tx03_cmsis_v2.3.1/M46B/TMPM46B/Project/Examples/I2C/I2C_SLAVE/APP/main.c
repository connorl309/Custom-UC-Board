/**
 *******************************************************************************
 * @file    main.c
 * @brief   The main functions of I2C slave demo for the
 *          TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/02/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

#include "main.h"

Result gTRxResult;
I2C_InitTypeDef myI2C;
uint32_t gI2CWCnt;
uint32_t gI2CRCnt;
uint32_t gI2CTxDataLen;
char gI2CTxData[16] = { 0 };

uint32_t gI2CRxDataLen;
char gI2CRxData[16] = { 0 };

uint32_t gI2CMode;

/**
  * @brief  The main routine of I2C demo I2C
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t gICnt;
    I2C_State i2c_state;

    SW_Init();
    hardware_init(UART_RETARGET);

    /*  Initialize IO for I2Cs */
    I2C2_IO_Configuration();
    I2C0_IO_Configuration();
    /* Initialize I2C channel 2 */
    myI2C.I2CSelfAddr = SELF_ADDR;
    myI2C.I2CDataLen = I2C_DATA_LEN_8;
    myI2C.I2CACKState = ENABLE;
    myI2C.I2CClkDiv = I2C_SCK_CLK_DIV_32;
    myI2C.PrescalerClkDiv = I2C_PRESCALER_DIV_12;
    I2C_SWReset(TSB_I2C2);
    I2C_Init(TSB_I2C2, &myI2C);
    NVIC_EnableIRQ(INTI2C2_IRQn);
    I2C_SetINTReq(TSB_I2C2,ENABLE);

    /* Initialize I2C channel 0 */
    myI2C.I2CSelfAddr = SLAVE_ADDR;
    myI2C.I2CDataLen = I2C_DATA_LEN_8;
    myI2C.I2CACKState = ENABLE;
    myI2C.I2CClkDiv = I2C_SCK_CLK_DIV_32;
    myI2C.PrescalerClkDiv = I2C_PRESCALER_DIV_12;
    I2C_SWReset(TSB_I2C0);
    I2C_Init(TSB_I2C0, &myI2C);
    NVIC_EnableIRQ(INTI2C0_IRQn);
    I2C_SetINTReq(TSB_I2C0,ENABLE);

    common_uart_disp("K3: I2C2 to I2C0");
    common_uart_disp("\r\n");
    common_uart_disp("\r\n");
    /* Initialize variables for I2Cs */
    gI2CTxDataLen = 0U;
    gI2CWCnt = 0U;
    gI2CRxDataLen = 0U;
    gI2CRCnt = 0U;
    gI2CMode = MODE_I2C_IDLE;

    while (1) {
        switch (gI2CMode) {
            /* SW3 input check */
        case MODE_I2C_IDLE:
            if (SW_Get(SW7)) {
                gI2CMode = MODE_I2C_INITIAL;
            } else {
                /* Do nothing */
            }
            break;
            /* Initialize TRx buffer and Tx length */
        case MODE_I2C_INITIAL:
            gI2CTxDataLen = 8U;
            gI2CTxData[0] = gI2CTxDataLen;
            gI2CTxData[1] = 'T';
            gI2CTxData[2] = 'O';
            gI2CTxData[3] = 'S';
            gI2CTxData[4] = 'H';
            gI2CTxData[5] = 'I';
            gI2CTxData[6] = 'B';
            gI2CTxData[7] = 'A';
            gI2CWCnt = 0U;
            for (gICnt = 0U; gICnt < 8U; gICnt++) {
                gI2CRxData[gICnt] = 0U;
            }
            gI2CMode = MODE_I2C_START;
            break;
            /* Check I2C bus state and start TRx */
        case MODE_I2C_START:
            i2c_state = I2C_GetState(TSB_I2C2);
            if (!i2c_state.Bit.BusState) {
                I2C_SetSendData(TSB_I2C2, SLAVE_ADDR | I2C_SEND);
                I2C_GenerateStart(TSB_I2C2);
                gI2CMode = MODE_I2C_TRX;
            } else {
                /* Do nothing */
            }
            break;
            /* Read I2C bus state to check TRx end */
        case MODE_I2C_TRX:
            if (gI2CRCnt > gI2CRxData[0]) {
                gI2CRxDataLen = gI2CRxData[0];
                gI2CRCnt = 0U;
                gI2CMode = MODE_I2C_FINISHED;
            } else {
                /* Do nothing */
            }
            break;
            /* Check transmission result */
        case MODE_I2C_FINISHED:
            if ((gI2CTxData[gI2CTxDataLen] == gI2CRxData[gI2CRxDataLen])) {
                gTRxResult = SUCCESS;
                common_uart_disp("Write Over");
                common_uart_disp("\r\n");
                common_uart_disp("K1: Show I2C0\n");
                common_uart_disp("\r\n");
                gI2CMode = MODE_I2C_CHECK;
            } else {
                gTRxResult = ERROR;
                common_uart_disp("Write ERROR");
                gI2CMode = MODE_I2C_IDLE;
            }
            break;

        case MODE_I2C_CHECK:
            if (SW_Get(SW4)) {
                for (gICnt = 1U; gICnt <= gI2CRxDataLen; gICnt++) {
                    gI2CRxData[gICnt] = gI2CRxData[gICnt];
                }
                gI2CRxData[gI2CRxDataLen] = 0U;
                common_uart_disp(gI2CRxData);
                common_uart_disp("\r\n");
                common_uart_disp("I2C2 to I2C0 OK");
                common_uart_disp("\r\n");
                gI2CMode = MODE_I2C_IDLE;
            } else {
                /* Do nothing */
            }
            break;

        default:
            gI2CTxDataLen = 0U;
            gI2CWCnt = 0U;
            gI2CRxDataLen = 0U;
            gI2CRCnt = 0U;
            gI2CMode = MODE_I2C_IDLE;
            break;
        }
    }
}

/**
  * @brief  Config the GPIO for I2C2
  * @param  None
  * @retval None
  */
void I2C2_IO_Configuration(void)
{
    GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_4, GPIO_BIT_0);
    GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_4, GPIO_BIT_1);
    GPIO_SetOutputEnableReg(GPIO_PH, GPIO_BIT_0, ENABLE);
    GPIO_SetOutputEnableReg(GPIO_PH, GPIO_BIT_1, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PH, GPIO_BIT_0, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PH, GPIO_BIT_1, ENABLE);
    GPIO_SetOpenDrain(GPIO_PH, GPIO_BIT_0, ENABLE);
    GPIO_SetOpenDrain(GPIO_PH, GPIO_BIT_1, ENABLE);
}

/**
  * @brief  Config the GPIO for I2C0
  * @param  None
  * @retval None
  */
void I2C0_IO_Configuration(void)
{
    GPIO_EnableFuncReg(GPIO_PK, GPIO_FUNC_REG_3, GPIO_BIT_2);
    GPIO_EnableFuncReg(GPIO_PK, GPIO_FUNC_REG_3, GPIO_BIT_3);
    GPIO_SetOutputEnableReg(GPIO_PK, GPIO_BIT_2, ENABLE);
    GPIO_SetOutputEnableReg(GPIO_PK, GPIO_BIT_3, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PK, GPIO_BIT_2, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PK, GPIO_BIT_3, ENABLE);
    GPIO_SetOpenDrain(GPIO_PK, GPIO_BIT_2, ENABLE);
    GPIO_SetOpenDrain(GPIO_PK, GPIO_BIT_3, ENABLE);
}

#ifdef DEBUG
/**
  * @brief  Deal with the error parameter
  * @param  file: Pointer to the file where the error parameter locates
  * @param  line: Number of the line in which the error parameter locates
  * @retval None
  */
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
