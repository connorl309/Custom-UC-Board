/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of LVD demo
 *          for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/02/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

#include "main.h"

int main(void)
{
    LVD_EnableVD();
    LVD_SetVDLevel(LVD_VDLVL_315);
    hardware_init(UART_RETARGET);
    while (1) {
        if (LVD_GetVDStatus() == LVD_VD_UPPER) {
            common_uart_disp("UPPER\n");
        } else {
            common_uart_disp("LOWER\n");
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
