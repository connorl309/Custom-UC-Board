/** 
 *******************************************************************************
 * @file    retarget.c
 * @brief   the application functions of UART_Retarget demo for the TOSHIBA
 *          'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/03/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* External function prototypes ----------------------------------------------*/
extern uint8_t send_char(uint8_t ch);

/**
  * @brief  Retarget printf to uart.
  * @param  IAR:Character to be sent.KEIL:Character to be sent.
  * @retval Character to be sent
  */

#if defined ( __CC_ARM   )      /* RealView Compiler */
struct __FILE {
    int handle;                 /* Add whatever you need here */
};
FILE __stdout;
FILE __stdin;
int fputc(int ch, FILE * f)
#elif defined ( __ICCARM__ )    /*IAR Compiler */
int putchar(int ch)
#endif
{
    return (send_char(ch));
}
