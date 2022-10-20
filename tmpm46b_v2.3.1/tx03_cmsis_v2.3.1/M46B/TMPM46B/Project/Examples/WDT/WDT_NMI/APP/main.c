/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of WDT demo for the
 *          TOSHIBA 'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/17
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_wdt_int.h"
#include "led.h"

/* Private define ------------------------------------------------------------*/
/* Uncomment below define for run DEMO2 */
/* #define  DEMO2 */

/* external variables --------------------------------------------------------*/
extern volatile uint8_t fIntNMI;

/* Private function prototypes -----------------------------------------------*/
void Delay(uint32_t time);

/* Private functions ---------------------------------------------------------*/
/* Main function */
int main(void)
{
    WDT_InitTypeDef WDT_InitStruct;
    WDT_InitStruct.DetectTime = WDT_DETECT_TIME_EXP_25;
    WDT_InitStruct.OverflowOutput = WDT_NMIINT;

    LED_Init();
    WDT_Init(&WDT_InitStruct);
    WDT_Enable();

    while (1U) {
        if (fIntNMI == 1U) {
            fIntNMI = 0U;
            WDT_Disable();
            LED_On(LED1);
            Delay(6500U);
            LED_Off(LED1);
            Delay(500U);

        } else {
            /* Do nothing */
        }

#ifdef DEMO2
        Delay(1000U);
        WDT_WriteClearCode();
        LED_On(LED0);
        Delay(1000U);
        LED_Off(LED0);
#endif
    }
}

/**
  * @brief  Delay sometime.
  * @param  time: Set a value to specify the delay time.
  * @retval None.
  */
void Delay(uint32_t time)
{
    volatile uint32_t TimeCounter = 0U;
    uint32_t DelayTime = 0U;

    DelayTime = time * 800U;
    for (TimeCounter = 0U; TimeCounter < DelayTime; TimeCounter++) {
        /* Do nothing */
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
