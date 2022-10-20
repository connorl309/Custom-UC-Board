/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of SHA demo for the TOSHIBA
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
uint32_t OriginalMessage[2U][16U] = {
    { 0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
      0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U,0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U },
    { 0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
      0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U,0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U }
};
uint32_t TrueMessage[2U][16U] = {
    { 0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
      0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U,0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U },
    { 0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
      0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U,0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U }
};
uint32_t FalseMessage[2U][16U] = {
    { 0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
      0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U,0x11223344U, 0x55667788U, 0x12123434U, 0x56567877U },
    { 0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U,0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U,
      0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U,0x11223344U, 0x55667788U, 0x12123434U, 0x56567877U }
};
uint32_t HashInit[8U] = {
    0x11223344U, 0x44332211U, 0x55667788U, 0x12345678U,
    0x12123434U, 0x43432121U, 0x56567878U, 0x12345678U
};
uint32_t MsgLen[2U] = { 0x00000000U, 0x00000100U };
uint32_t RmnMsgLen[2U] = { 0x00000000U, 0x00000100U };
volatile uint32_t CompleteFlag = 0U;
/* Private functions ---------------------------------------------------------*/
/* Main function */
int main(void)
{
    Result TrueResult = ERROR;
    Result FalseResult = ERROR;

    uint32_t* OHashValue = (uint32_t*)malloc(32);
    uint32_t* THashValue = (uint32_t*)malloc(32);
    uint32_t* FHashValue = (uint32_t*)malloc(32);
    uint32_t i = 0U;

    /* Configure UART */
    hardware_init(UART_RETARGET);

    /* Enable interrupts */
    NVIC_ClearPendingIRQ(INTSHA_IRQn);
    NVIC_EnableIRQ(INTSHA_IRQn);
    __enable_irq();

    /* Initialize SHA to calculate original message. */
    SHA_Config();
    /* SHA generates 256-bit Hash value from original message. */
    for (i = 0U; i < 2U; i++) {
        CompleteFlag = 0U;
        /* Set a 512-bit message. */
        SHA_SetMessage(OriginalMessage[i]);
        /* Start the SHA processor. */
        SHA_SetRunState(SHA_START);
        /* Wait for calculation completion */
        while (CompleteFlag != 1U) {
            /* Do nothing */
        }
    }
    /* Get 256-bit original message Hash value. */
    SHA_GetResult(OHashValue);

    /* Initialize SHA to calculate true message. */
    SHA_Config();
    /* SHA generates 256-bit Hash value from true message. */
    for (i = 0U; i < 2U; i++) {
        CompleteFlag = 0U;
        /* Set a 512-bit message. */
        SHA_SetMessage(TrueMessage[i]);
        /* Start the SHA processor. */
        SHA_SetRunState(SHA_START);
        /* Wait for calculation completion */
        while (CompleteFlag != 1U) {
            /* Do nothing */
        }
    }
    /* Get 256-bit true message Hash value. */
    SHA_GetResult(THashValue);

    /* Initialize SHA to calculate false message. */
    SHA_Config();
    /* SHA generates 256-bit Hash value from false message. */
    for (i = 0U; i < 2U; i++) {
        CompleteFlag = 0U;
        /* Set a 512-bit message. */
        SHA_SetMessage(FalseMessage[i]);
        /* Start the SHA processor. */
        SHA_SetRunState(SHA_START);
        /* Wait for calculation completion */
        while (CompleteFlag != 1U) {
            /* Do nothing */
        }
    }
    /* Get 256-bit false message Hash value. */
    SHA_GetResult(FHashValue);

    /* Compare original message Hash value with true message Hash value. */
    TrueResult = HashValueCompare(OHashValue, THashValue, 8U);
    /* Compare original message Hash value with false message Hash value. */
    FalseResult = HashValueCompare(OHashValue, FHashValue, 8U);

    if ((TrueResult == SUCCESS) && (FalseResult == ERROR)) {
        common_uart_disp("SHA processed successfully !\n");
    } else {
        common_uart_disp("SHA processed with error !\n");
    }

    free(OHashValue);
    free(THashValue);
    free(FHashValue);
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
