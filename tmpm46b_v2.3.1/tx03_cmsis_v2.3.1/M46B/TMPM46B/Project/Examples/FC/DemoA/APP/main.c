/**
 *******************************************************************************
 * @file    main.c
 * @brief   main function of Flash demo(DemoA)
 * @version V0.100
 * @date    2015/03/17
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

#include "led.h"

void delay(uint32_t DelayTime)
{
    uint32_t time;
    for (time = 0U; time < DelayTime; time++) {
    }
}

int main(void)
{
    LED_Init();
    LED_On(LED2);
    delay(400000U);

    while (1U) {
        LED_On(LED0);
        delay(4000000U);
        LED_Off(LED0);
        delay(4000000U);
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
