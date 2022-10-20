/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of ESG demo for the TOSHIBA
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
volatile uint32_t CompleteFlag = 0U;
/* Private functions ---------------------------------------------------------*/
/* Main function */
uint32_t Data[16] = {0};

int main(void)
{
    uint32_t i = 0U;
    static char buffer[30];

    /* Configure UART */
    hardware_init(UART_RETARGET);

    /* enable interrupts */
    NVIC_ClearPendingIRQ(INTESG_IRQn);
    NVIC_EnableIRQ(INTESG_IRQn);
    __enable_irq();

    /* Initialize ESG to calculate original message. */
    ESG_Config(ESG_LATCH_TIMING_1, 560);
    /* Start up the ESG core. */
    ESG_Startup();

    while(1){
        if ((CompleteFlag == 1U)) {
            CompleteFlag = 0;
            /* Get the calculation result */
            ESG_GetResult(Data);
            for(i = 0U; i < 16U; i++) {
#ifdef DEBUG
                printf("0x%08x \r\n", Data[i]);
#endif
                sprintf((char *)buffer, "%lu", Data[i]);
                common_uart_disp(buffer);
                common_uart_disp("\n");
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

/*********************************** END OF FILE ******************************/
