/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of AES_CBC demo for the TOSHIBA
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
uint32_t PlainText[3U][4U] = {
    {0x11111111U, 0x22222222U, 0x33333333U, 0x44444444U},
    {0x55555555U, 0x66666666U, 0x77777777U, 0x88888888U},
    {0x11223344U, 0x55667788U, 0x12123434U, 0x56567878U}
};
uint32_t EncryptedText[3U][4U] = {
    {0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},
    {0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},
    {0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}
};
uint32_t DecryptedText[3U][4U] = {
    {0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},
    {0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U},
    {0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}
};
uint32_t EncryptionKey[6U] = {
    0x11223344U, 0x44332211U, 0x55667788U,
    0x12123434U, 0x43432121U, 0x56567878U
};
uint32_t DecryptionKey[6U] = {
    0x00000000U, 0x00000000U, 0x00000000U,
    0x00000000U, 0x00000000U, 0x00000000U
};
uint32_t InitVector[4U] = {
    0x12345678U, 0x87654321U, 12348765U, 0x43215678U
};
volatile uint32_t CompleteFlag = 0U;
/* Private functions ---------------------------------------------------------*/
/* Main function */
int main(void)
{
    Result AESResult = ERROR;
    uint32_t i = 0U, j = 0U, k = 0U;

    /* Configure UART */
    hardware_init(UART_RETARGET);

    /* Enable AES calculation completion interrupt */
    NVIC_ClearPendingIRQ(INTAES_IRQn);
    NVIC_EnableIRQ(INTAES_IRQn);
    __enable_irq();

    /* Initialize AES to encryption mode */
    AES_Config(AES_ENCRYPTION_MODE);
    /* Encrypt 3 units plaintext. */
    for (i = 0U; i < 3U; i++) {
        CompleteFlag = 0U;
        /* If 128-bit data is stored in the AESDT register, calculation automatically starts */
        for (j = 0U; j < 4U; j++) {
            AES_SetData(PlainText[i][j]);
        }
        /* Wait for calculation completion */
        while (CompleteFlag != 1U) {
            /* Do nothing */
        }
        /*The CPU reads the value from AESODT<ODT[31:0]>(four times) */
        for (k = 0U; k < 4U; k++) {
            EncryptedText[i][k] = AES_GetResult();
        }
    }
    /* Get the output key */
    for (i = 0U; i < 6U; i++) {
        DecryptionKey[i] = AES_GetKey(i + 2U);
    }

    /* Initialize AES to decryption mode */
    AES_Config(AES_DECRYPTION_MODE);
    /* Decrypt the 3 units encrypted text. */
    for (i = 0U; i < 3U; i++) {
        CompleteFlag = 0U;
        /* If 128-bit data is stored in the AESDT register, calculation automatically starts */
        for (j = 0U; j < 4U; j++) {
            AES_SetData(EncryptedText[i][j]);
        }
        /* Wait for calculation completion */
        while (CompleteFlag != 1U) {
            /* Do nothing */
        }
        /* The CPU reads the value from AESODT<ODT[31:0]>(four times) */
        for (k = 0U; k < 4U; k++) {
            DecryptedText[i][k] = AES_GetResult();
        }
    }

    /* Compare plaintext with decrypted text to verify the AES CBC function. */
    AESResult = TextCompare(PlainText, DecryptedText, 3U, 4U);

    if (AESResult == SUCCESS) {
        common_uart_disp("AES CBC mode processed successfully !\n");
    } else {
        common_uart_disp("AES CBC mode processed with error !\n");
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
