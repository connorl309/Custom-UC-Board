/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of GPIO demo for the
 *          TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/06 
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* include file */
#include "main.h"

/*  Function declaration */

/* main function */
int main(void)
{
    LED_Init(); 
    SW_Init();
    for (;;) {
        if (SW_Get(SW0) || SW_Get(SW4)) {
            LED_On(LED4);
        } else {
            LED_Off(LED4);
        }
        if (SW_Get(SW1) || SW_Get(SW5)) {
            LED_On(LED5);
        } else {
            LED_Off(LED5);
        }
        if (SW_Get(SW2) || SW_Get(SW6)) {
            LED_On(LED6);
        } else {
            LED_Off(LED6);
        }
        if (SW_Get(SW3) || SW_Get(SW7)) {
            LED_On(LED7);
        } else {
            LED_Off(LED7);
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
