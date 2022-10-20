/**
 *******************************************************************************
 * @file    tmpm46b_wdt.c
 * @brief   This file provides all the functions prototypes for WDT driver.
 * @version V2.0.2.1
 * @date    2015/02/26
 *
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 *
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_wdt.h"

#if defined(__TMPM46B_WDT_H)
/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @defgroup WDT
  * @brief WDT driver modules
  * @{
  */
/** @defgroup WDT_Private_Defines
  * @{
  */

#define WDT_CR_CLR_CODE        ((uint32_t)0x0000004E)
#define WDT_CR_DISABLE_CODE    ((uint32_t)0x000000B1)
#define MOD_WDTP_MASK          ((uint32_t)0x00000086)
#define MOD_I2WDT_SET          ((uint32_t)0x00000004)
#define MOD_I2WDT_CLEAR        ((uint32_t)0xFFFFFFFB)
#define MOD_RESCR_SET          ((uint32_t)0x00000002)
#define MOD_RESCR_CLEAR        ((uint32_t)0xFFFFFFFD)
#define MOD_WDTE_SET           ((uint32_t)0x00000080)
#define MOD_WDTE_CLEAR         ((uint32_t)0xFFFFFF7F)
#define WDT_FLG_CLEAR          ((uint32_t)0x00000000)

/** @} */
/* End of group WDT_Private_Defines */

/** @defgroup WDT_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group WDT_Private_FunctionPrototypes */

/** @defgroup WDT_Private_Functions
  * @{
  */

/** @} */
/* End of group group WDT_Private_Functions */

/** @defgroup WDT_Exported_Functions
  * @{
  */

/**
  * @brief  Set detection time
  * @param  DetectTime: Set the Detection time.
  *   This parameter can be one of the following values:
  *   WDT_DETECT_TIME_EXP_15, WDT_DETECT_TIME_EXP_17, WDT_DETECT_TIME_EXP_19,
  *   WDT_DETECT_TIME_EXP_21, WDT_DETECT_TIME_EXP_23 or WDT_DETECT_TIME_EXP_25.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   WDMOD<WDTP[2:0]>
  */
Result WDT_SetDetectTime(uint32_t DetectTime)
{
    uint32_t tmp = 0U;
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_WDT_DETECT_TIME(DetectTime));

    if (WDT_GetWritingFlg() == ENABLE) {
        /* Set WDT Detection time */
        tmp = TSB_WD->MOD;
        tmp &= MOD_WDTP_MASK;
        tmp |= DetectTime;
        TSB_WD->MOD = tmp;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Run or stop the WDT counter when the system enters IDLE mode.
  * @param  NewState: Select the state of the WDT before enter IDLE mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   WDMOD<I2WDT>
  */
Result WDT_SetIdleMode(FunctionalState NewState)
{
    uint32_t tmp = 0U;
    Result retval = ERROR;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (WDT_GetWritingFlg() == ENABLE) {
        tmp = TSB_WD->MOD;
        if (NewState == ENABLE) {
            /* Set WDMOD<I2WDT> to start the WDT counter before enter IDLE mode */
            tmp |= MOD_I2WDT_SET;
        } else {
            /* Set WDMOD<I2WDT> to stop the WDT counter before enter IDLE mode */
            tmp &= MOD_I2WDT_CLEAR;
        }
        TSB_WD->MOD = tmp;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Set WDT generate NMI interrupt or reset when counter overflow.
  * @param  OverflowOutput: Select function of WDT when counter overflow.
  *   This parameter can be: WDT_WDOUT or WDT_NMIINT.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   WDMOD<RESCR>
  */
Result WDT_SetOverflowOutput(uint32_t OverflowOutput)
{
    uint32_t tmp = 0U;
    Result retval = ERROR;
    /* Check the parameters */
    assert_param(IS_WDT_OUTPUT(OverflowOutput));

    if (WDT_GetWritingFlg() == ENABLE) {
        tmp = TSB_WD->MOD;
        if (OverflowOutput == WDT_WDOUT) {
            /* Set WDMOD<RESCR> to 1 */
            tmp |= MOD_RESCR_SET;
        } else {
            /* Clear WDMOD<RESCR> to 0 */
            tmp &= MOD_RESCR_CLEAR;
        }
        TSB_WD->MOD = tmp;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Initialize WDT.
  * @param  InitStruct: The structure containing basic WD configuration.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   WDMOD<WDTP[2:0]><RESCR>
  */
Result WDT_Init(WDT_InitTypeDef * InitStruct)
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(InitStruct));
    assert_param(IS_WDT_DETECT_TIME(InitStruct->DetectTime));
    assert_param(IS_WDT_OUTPUT(InitStruct->OverflowOutput));

    if (WDT_GetWritingFlg() == ENABLE) {
        /* Set WDT Detection time */
        WDT_SetDetectTime(InitStruct->DetectTime);
        /* Set WDMOD<RESCR> to select function of WDT when counter overflow */
        WDT_SetOverflowOutput(InitStruct->OverflowOutput);
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Enable the WDT.
  * @param  None
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   WDMOD<WDTE>
  */
Result WDT_Enable(void)
{
    Result retval = ERROR;

    if (WDT_GetWritingFlg() == ENABLE) {
        /* Set WDMOD<WDTE> to enable WDT */
        TSB_WD->MOD |= MOD_WDTE_SET;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Disable the WDT.
  * @param  None
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   WDMOD<WDTE>, WDCR<WDCR>
  */
Result WDT_Disable(void)
{
    Result retval = ERROR;

    if (WDT_GetWritingFlg() == ENABLE) {
        /* Clear WDxMOD<WDTE> and (B1H) be written to the WDCR register to disable WDT */
        TSB_WD->MOD &= MOD_WDTE_CLEAR;
        TSB_WD->CR = WDT_CR_DISABLE_CODE;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Write the clear code.
  * @param  None
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   WDCR<WDCR>
  */
Result WDT_WriteClearCode(void)
{
    Result retval = ERROR;

    if (WDT_GetWritingFlg() == ENABLE) {
        /* Set WDTCR to clear the binary counter */
        TSB_WD->CR = WDT_CR_CLR_CODE;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the flag for writing to registers.
  * @param  None
  * @retval The flag for writing to registers.
  *   The value returned can be one of the following values:
  *   ENABLE or DISABLE
  * @note When writing to WDMOD or WDCR, confirm writing flag enable.
  * @register The used register:
  *   WDFLG<FLG>
  */
FunctionalState WDT_GetWritingFlg(void)
{
    FunctionalState retval = DISABLE;

    if (TSB_WD->FLG == WDT_FLG_CLEAR) {
        retval = ENABLE;
    } else {
        /* Do nothing */
    }

    return retval;
}

/** @} */
/* End of group WDT_Exported_Functions */

/** @} */
/* End of group WDT */

/** @} */
/* End of group TX04_Periph_Driver */
#endif                          /* defined(__TMPM46B_WDT_H) */
