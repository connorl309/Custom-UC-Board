/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of CG_ModeSwitch demo for the TOSHIBA
 *          'TMPM46B' Device Series
 * @version V0.100
 * @date    2015/03/20
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************

 EHCLKIN : Clock input from the X1 pins
 EHOSC   : Output clock from the external high-speed oscillator
 ELOSC   : Output clock from the external Low-speed oscillator
 IHOSC   : Output clock from the internal high-speed oscillator.(for SYS)
 FOSCHI  : Clock specified by CGOSCCR<HOSCON>
 fosc    : Clock specified by CGOSCCR<OSCSEL>
 fpll    : Clock multiplied by PLL
 fc      : Clock specified by CGPLLSEL<PLLSEL> (high-speed clock)
 fgear   : Clock specified by CGSYSCR<GEAR[2:0]>
 fsys    : Clock specified by CGSYSCR<GEAR[2:0]>.(system clock)
 fperiph : Clock specified by CGSYSCR<FPSEL[2:0]>
 ¦µT0    : Clock specified by CGSYSCR<PRCK[2:0]> (prescaler clock)
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "common_uart.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define NORMAL_MODE             ((uint8_t)0x00)
#define STOP_MODE               ((uint8_t)0x01)
#define CG_PLLSEL_PLLON_CLEAR   ((uint32_t)0xFFFEFFFF)
#define CG_PLLSEL_PLLSEL_CLEAR  ((uint32_t)0xFFFDFFFF)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
uint8_t gCurrentMode = NORMAL_MODE;
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Mode_Judgement(void);
void System_Init(void);

/* Main function */
int main(void)
{
    System_Init();
    /* Disable interrupts */
    __disable_irq();
    CG_ClearINTReq(CG_INT_SRC_F);
    /* Set external interrupt to wake up system */
    CG_SetSTBYReleaseINTSrc(CG_INT_SRC_F, CG_INT_ACTIVE_STATE_RISING, ENABLE);
    NVIC_ClearPendingIRQ(INTF_IRQn);
    NVIC_EnableIRQ(INTF_IRQn);
    __enable_irq();

    /* Initialize Variables */
    gCurrentMode = NORMAL_MODE;

    while (1) {
        Mode_Judgement();       /* Push SW1 to change Mode */

        switch (gCurrentMode) {
        case NORMAL_MODE:
            LED_On(LED_ALL);
            common_uart_disp("NORMAL MODE\r\n");
            break;
        case STOP_MODE:
            LED_Off(LED_ALL);
            common_uart_disp("STOP MODE\r\n");

            /* Switch from normal mode to stop1 mode */
            CG_NormalToStop();

            System_Init();
            gCurrentMode = NORMAL_MODE;
            break;
        default:
            gCurrentMode = NORMAL_MODE;
            break;
        }
    }

}

/**
  * @brief  Judge whether go to STOP_MODE
  * @param  None.
  * @retval None.
  */
void Mode_Judgement(void)
{
    uint8_t SW1_info = 0U;
    SW1_info = SW_Get(SW1);

    if ((1U == SW1_info) && (gCurrentMode == NORMAL_MODE)) {
        gCurrentMode = STOP_MODE;
    } else {
        /* Do nothing */
    }
}

/**
  * @brief  Initialize system
  * @param  None.
  * @retval None.
  */
void System_Init(void)
{
    /* Initialize system */
    SystemInit();
    CG_SetSystem();

    /* Configure GPIO to switch */
    GPIO_SetInput(GPIO_PC, GPIO_BIT_1); /* Set port C pin1 to input and port C pin1 is used as INTF */
    SW_Init();

    /* Configure GPIO to LED */
    LED_Init();

    /* Configure UART */
    hardware_init(UART_RETARGET);
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
