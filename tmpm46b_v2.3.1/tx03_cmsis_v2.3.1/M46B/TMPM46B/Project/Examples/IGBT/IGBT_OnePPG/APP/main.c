/**
 *******************************************************************************
 * @file    main.c
 * @brief   The application functions of IGBT One PPG for the TOSHIBA 'TMPM46B'
 *          Device Series
 * @version V0.100
 * @date    2015/03/21
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Global variable define ----------------------------------------------------*/
WorkState counter_state = BUSY;
Result cancel_result = ERROR;
IGBT_InitTypeDef myIGBT;
IGBT_EMGStateTypeDef EMGState = { IGBT_EMG_INPUT_LOW, IGBT_EMG_NORMAL };

/**
  * @brief  main function to run IGBT One PPG demo
  * @param  None.
  * @retval result to retun to system.
  */
int main(void)
{
    /* LED initialization */
    LED_Init();
    LED_On(LED0);

    myIGBT.StartMode = IGBT_FALLING_TRG_START;     /* IGBT trigger start: falling edge start and active level is "Low" */
    myIGBT.OperationMode = IGBT_CONTINUOUS_OUTPUT; /* IGBT operation: continuous operation */
    myIGBT.CntStopState = IGBT_OUTPUT_INACTIVE;    /* IGBT stopping status: initial output satus and counter */
    myIGBT.ActiveAcceptTrg = DISABLE;              /* Trigger edge accept mode: Don't accept trigger during active level */
    myIGBT.INTPeriod = IGBT_INT_PERIOD_1;          /* Interrupt cycle: Every one cycle */
    myIGBT.ClkDiv = IGBT_CLK_DIV_2;                /* For M46B: fperiph = fc = 16MHz*4 = 64MHz, T0 = fperiph = 64MHz, figbt = T0/2 = 32MHz */
    myIGBT.Output0Init = IGBT_OUTPUT_HIGH_ACTIVE;  /* MTOUT00 initial state is Low, and active level is High */
    myIGBT.Output1Init = IGBT_OUTPUT_DISABLE;      /* Disable MTOUT10 output */
    myIGBT.TrgDenoiseDiv = IGBT_DENOISE_DIV_240;   /* Trigger input noise elimination time: 240/fsys */
    myIGBT.Output0ActiveTiming = 1U;
    myIGBT.Output0InactiveTiming = 1U + IGBT_PPG_PERIOD_50US / 2;
    myIGBT.Period = IGBT_PPG_PERIOD_50US;          /* Period: 50us */
    myIGBT.EMGFunction = IGBT_EMG_OUTPUT_HIZ;      /* The polarity of MTOUT0x at EMG protection: High-impedance */
    myIGBT.EMGDenoiseDiv = IGBT_DENOISE_DIV_240;   /* EMG input noise elimination time: 240/fsys */

    IGBT_IO_Configuration(IGBT0, &myIGBT);

    IGBT_Enable(IGBT0);
    NVIC_EnableIRQ(INTMTEMG0_IRQn);    /* Enable IGBT and EMG interrupt */

    do {                               /* If the timer is still running, wait until it stops */
        counter_state = IGBT_GetCntState(IGBT0);
    } while (counter_state == BUSY);
    do {                               /* Cancel the EMG protection state */
        cancel_result = IGBT_CancelEMGState(IGBT0);
    } while (cancel_result == ERROR);

    IGBT_Init(IGBT0, &myIGBT);

    IGBT_SetSWRunState(IGBT0, IGBT_RUN);        /* Prepare to run IGBT timer */

    while (1) {

        EMGState = IGBT_GetEMGState(IGBT0);     /* Get EMG protection state to check EMG state */

        if (EMGState.EMGProtectState == IGBT_EMG_PROTECT) {     /* If EMG protection is on going */
            do {
                counter_state = IGBT_GetCntState(IGBT0);
            } while (counter_state == BUSY);
            do {                /* Cancel the EMG protection state */
                cancel_result = IGBT_CancelEMGState(IGBT0);
            } while (cancel_result == ERROR);

            LED_Off(LED1);      /* Turn off the LED and prepare to run again */
            IGBT_Init(IGBT0, &myIGBT);

            IGBT_SetSWRunState(IGBT0, IGBT_RUN);
        } else {
            /* Do nothing */
        }
    }
}

/**
  * @brief  IRQ for EMG protection
  * @param  None.
  * @retval None.
  */
void INTMTEMG0_IRQHandler(void)
{
    LED_On(LED1);               /* If EMG protection, turn on the LED and stop the timer */
    IGBT_SetSWRunState(IGBT0, IGBT_STOP);
}

/**
  * @brief  IGBT port initialization
  * @param  IGBTx: IGBT channel.
  *         InitTypeDef: initialization structure.
  * @retval None.
  */
void IGBT_IO_Configuration(TSB_MT_TypeDef * IGBTx, IGBT_InitTypeDef * InitTypeDef)
{
    if (IGBTx == IGBT0) {
        /* Check whether the trigger is used to start */
        if ((InitTypeDef->StartMode != IGBT_CMD_START) ||
            (InitTypeDef->StartMode != IGBT_CMD_START_NO_START_INT)) {
            GPIO_SetInputEnableReg(GPIO_PG, GPIO_BIT_0, ENABLE);        /* Enable PG0 input */
            GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_0);   /* Set PG0 as MT0IN */
        } else {
            GPIO_SetInputEnableReg(GPIO_PG, GPIO_BIT_0, DISABLE);
            GPIO_DisableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_0);
        }
        /* Enable ouput0 or not */
        if (InitTypeDef->Output0Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_3, ENABLE);       /* Enable PG3 output */
            GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_3);   /* Set PG3 as MT0OUT0 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_3, DISABLE);
            GPIO_DisableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_3);
        }
        /* Enable ouput1 or not */
        if (InitTypeDef->Output1Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_2, ENABLE);       /* Enable PG2 output */
            GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_2);   /* Set PG2 as MT0OUT1 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PG, GPIO_BIT_2, DISABLE);
            GPIO_DisableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_2);
        }

        GPIO_SetInputEnableReg(GPIO_PG, GPIO_BIT_1, ENABLE);            /* Enable PG1 input */
        GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_3, GPIO_BIT_1);       /* Set PG1 as GEMG0 */
    }

    if (IGBTx == IGBT1) {
        /* Check whether the trigger is used to start */
        if ((InitTypeDef->StartMode != IGBT_CMD_START) ||
            (InitTypeDef->StartMode != IGBT_CMD_START_NO_START_INT)) {
            GPIO_SetInputEnableReg(GPIO_PL, GPIO_BIT_0, ENABLE);        /* Enable PL0 input */
            GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_0);   /* Set PL0 as MT1IN */
        } else {
            GPIO_SetInputEnableReg(GPIO_PL, GPIO_BIT_0, DISABLE);
            GPIO_DisableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_0);
        }
        /* Enable ouput0 or not */
        if (InitTypeDef->Output0Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_3, ENABLE);       /* Enable PL3 output */
            GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_3);   /* Set PL3 as MT1OUT0 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_3, DISABLE);
            GPIO_DisableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_3);
        }
        /* Enable ouput1 or not */
        if (InitTypeDef->Output1Init != IGBT_OUTPUT_DISABLE) {
            GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_2, ENABLE);       /* Enable PL2 output */
            GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_2);   /* Set PL2 as MT1OUT1 */
        } else {
            GPIO_SetOutputEnableReg(GPIO_PL, GPIO_BIT_2, DISABLE);
            GPIO_DisableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_2);
        }

        GPIO_SetInputEnableReg(GPIO_PL, GPIO_BIT_1, ENABLE);            /* Enable PL1 input */
        GPIO_EnableFuncReg(GPIO_PL, GPIO_FUNC_REG_3, GPIO_BIT_1);       /* Set PL1 as GEMG1 */
    }
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif                          /* DEBUG */
