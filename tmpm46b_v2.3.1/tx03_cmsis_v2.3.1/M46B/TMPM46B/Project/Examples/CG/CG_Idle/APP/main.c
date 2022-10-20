/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of CG IDLE demo for the TOSHIBA
 *          'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/03/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
#include "main.h"

/* for MCU */
void __WFI_wait()
{
    __WFI();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

/**
  * @brief  The main function of demo
  * @param  None
  * @retval None
  */
int main(void)
{
    SW_Init();
    LED_Init();

    GPIO_ExtIntSrc();
    CG_ClearINTReq(CG_ExtINTSrc);
    NVIC_ClearPendingIRQ(ExtINTSrc_IRQn);
    NVIC_EnableIRQ(ExtINTSrc_IRQn);

    LED_On(LED_EXT);
    while (1U) {

        if (SW_Get(CG_SW) == 1U) {
            LED_On(LED_SW);

            /* LED indicator is off before enter IDLE */
            LED_Off(LED_EXT);

            enter_IDLE();

        } else {
            LED_Off(LED_SW);
        }
    }
}

/**
  * @brief  Enter the IDLE low power mode
  * @param  None
  * @retval None
  */
void enter_IDLE(void)
{

    CG_SetSTBYReleaseINTSrc(CG_ExtINTSrc, CG_INT_ACTIVE_STATE_RISING, ENABLE);

    /* Set standby mode as IDLE */
    CG_SetSTBYMode(CG_STBY_MODE_IDLE);

    __DSB();
    __WFI_wait();

    /* INT release */
    CG_SetSTBYReleaseINTSrc(CG_ExtINTSrc, CG_INT_ACTIVE_STATE_RISING, DISABLE);
}

/**
  * @brief  Set GPIO of External interrupt source
  * @param  None
  * @retval None
  */
void GPIO_ExtIntSrc(void)
{
    GPIO_SetInput(GPIO_ExtINTSrc, Bit_ExtINTSrc);
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
