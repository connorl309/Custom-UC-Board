/** 
 *******************************************************************************
 * @file    uart.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE 16U
#define SET     0x01U           /* flag is set */
#define CLEAR   0x00U           /* flag is cleared */
#define NO      0x00U           /* Send finish NG */
#define YES     0x01U           /* Send finish OK */

/* external variables --------------------------------------------------------*/
extern volatile char gSIOTxBuffer[];
extern uint8_t gSIORdIndex;
extern volatile uint8_t gSIOWrIndex;
extern volatile uint8_t fSIO_INT;
extern volatile uint8_t fSIOTxOK;

/* Exported functions ------------------------------------------------------- */
void SIO_Configuration(TSB_SC_TypeDef * SCx);
void SIO_ChInit(void);
uint8_t send_char(uint8_t ch);
#endif
