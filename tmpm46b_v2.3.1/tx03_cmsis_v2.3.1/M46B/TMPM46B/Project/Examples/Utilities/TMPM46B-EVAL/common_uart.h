/** 
 *******************************************************************************
 * @file    common_uart.h
 * @brief   UART functions prototypes for the TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/02/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_UART_H
#define __COMMON_UART_H

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus*/

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_uart.h"

/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE     (16U  )
#define SET             (0x01U)           /* flag is set */
#define CLEAR           (0x00U)           /* flag is cleared */
#define NO              (0x00U)           /* Send finish NG */
#define YES             (0x01U)           /* Send finish OK */
#define UART_RETARGET   (UART0)

/* external variables --------------------------------------------------------*/
extern char gSIOTxBuffer[];
extern volatile uint8_t gSIORdIndex;
extern volatile uint8_t gSIOWrIndex;
extern volatile uint8_t fSIO_INT;
extern volatile uint8_t fSIOTxOK;

/* Exported functions ------------------------------------------------------- */
void SIO_Configuration(TSB_SC_TypeDef * SCx);
void SIO_ChInit(void);
void send_char(TSB_SC_TypeDef * USART, char ch);
void send_str(TSB_SC_TypeDef * USART, char *ch);
void common_uart_disp(char *pstr);
void hardware_init(TSB_SC_TypeDef * SCx);
void INTTX0_IRQHandler(void);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __COMMON_UART_H */
