/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of MLA_SUB demo for the TOSHIBA
 *          'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/02/27
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Global variables ----------------------------------------------------------*/
uint32_t OriginaAData[8U] = {
    0x88888888U, 0x22222222U, 0x33333333U, 0x44444444U,
    0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U
};
uint32_t TrueAData[8U] = {
    0x88888888U, 0x22222222U, 0x33333333U, 0x44444444U,
    0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U
};
uint32_t FalseAData[8U] = {
    0x77777777U, 0x22222222U, 0x33333333U, 0x44444444U,
    0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U
};

uint32_t OriginaBData[8U] = {
    0x33333333U, 0x77777777U, 0x66666666U, 0x55555555U,
    0x44444444U, 0x33333333U, 0x22222222U, 0x11111111U
};
uint32_t TrueBData[8U] = {
    0x33333333U, 0x77777777U, 0x66666666U, 0x55555555U,
    0x44444444U, 0x33333333U, 0x22222222U, 0x11111111U
};
uint32_t FalseBData[8U] = {
    0x11111111U, 0x77777777U, 0x66666666U, 0x55555555U,
    0x44444444U, 0x33333333U, 0x22222222U, 0x11111111U
};

volatile uint32_t CompleteFlag = 0U;
/* Private functions ---------------------------------------------------------*/
/* Main function */
int main(void)
{
    Result TrueResult = ERROR;
    Result FalseResult = ERROR;
    static uint32_t OriginaData[8];
    static uint32_t TrueData[8];
    static uint32_t FalseData[8];

    /* Configure UART */
    hardware_init(UART_RETARGET);

    /* enable MLA calculation completion interrupt */
    NVIC_ClearPendingIRQ(INTMLA_IRQn);
    NVIC_EnableIRQ(INTMLA_IRQn);
    __enable_irq();

    /* Initialize MLA to calculate original message. */
    if(MLA_GetCalculationStatus() != MLA_CALCULATION_PROGRESS) {
        /* Sets calculation input data. */
        MLA_WriteDataBlkNum(MLA_BLK_2, OriginaAData);
        MLA_WriteDataBlkNum(MLA_BLK_5, OriginaBData);

        /* Initialize MLA calculation mode */
        MLA_Config(MLA_BLK_2, MLA_BLK_5, MLA_BLK_0);

        /* Wait for calculation completion */
        while (CompleteFlag != 1U) {
            /* Do nothing */
        }
        /* Get the calculation result */
        Delay();
        MLA_ReadDataBlkNum(MLA_BLK_0, OriginaData);
    }

    /* Initialize MLA to calculate true message. */
    if(MLA_GetCalculationStatus() != MLA_CALCULATION_PROGRESS) {
        /* Sets calculation input data. */
        MLA_WriteDataBlkNum(MLA_BLK_20, TrueAData);
        MLA_WriteDataBlkNum(MLA_BLK_22, TrueBData);

        /* Initialize MLA calculation mode */
        MLA_Config(MLA_BLK_20, MLA_BLK_22, MLA_BLK_26);

        /* Wait for calculation completion */
        while (CompleteFlag != 1U) {
            /* Do nothing */
        }
        /* Get the calculation result */
        Delay();
        MLA_ReadDataBlkNum(MLA_BLK_26, TrueData);
    }

    /* Initialize MLA to calculate false message. */
    if(MLA_GetCalculationStatus() != MLA_CALCULATION_PROGRESS) {
        /* Sets calculation input data. */
        MLA_WriteDataBlkNum(MLA_BLK_2, FalseAData);
        MLA_WriteDataBlkNum(MLA_BLK_5, FalseBData);

        /* Initialize MLA calculation mode */
        MLA_Config(MLA_BLK_2, MLA_BLK_5, MLA_BLK_0);

        /* Wait for calculation completion */
        while (CompleteFlag != 1U) {
            /* Do nothing */
        }
        /* Get the calculation result */
        Delay();
        MLA_ReadDataBlkNum(MLA_BLK_0, FalseData);

  }

    /* Compare original data calculation results with true data calculation results. */
    TrueResult = MLAValueCompare(OriginaData, TrueData, 8U);
    /* Compare original data calculation results with false data calculation results. */
    FalseResult = MLAValueCompare(OriginaData, FalseData, 8U);

    if ((TrueResult == SUCCESS) && (FalseResult == ERROR)) {
        common_uart_disp("MLA SUB processed successfully !\n");
    } else {
        common_uart_disp("MLA SUB processed with error !\n");
    }

    while(1);
}


#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif

/*********************************** END OF FILE ******************************/
