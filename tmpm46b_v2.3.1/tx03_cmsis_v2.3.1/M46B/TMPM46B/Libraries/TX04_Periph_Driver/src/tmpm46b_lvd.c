/**
 *******************************************************************************
 * @file    tmpm46b_lvd.c
 * @brief   This file provides API functions for LVD driver. 
 * @version V2.0.2.1
 * @date    2015/02/25
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_lvd.h"

#if defined(__TMPM46B_LVD_H)
/** @addtogroup TX04_Periph_Driver
  * @{
  */
/** @defgroup LVD
  * @brief LVD driver modules
  * @{
  */

/** @defgroup LVD_Private_Defines
  * @{
  */
#define LVD_EN_SET              ((uint32_t)0x00000001)
#define LVD_EN_CLEAR            ((uint32_t)0xFFFFFFFE)

#define LVD_VDLVL_CLEAR        ((uint32_t)0xFFFFFFF1)

#define LVD_VDST_MASK          ((uint32_t)0x00000080)

#define LVD_VDRSTEN_SET        ((uint32_t)0x00000040)
#define LVD_VDRSTEN_CLEAR      ((uint32_t)0xFFFFFFBF)
#define LVD_VDINTEN_SET        ((uint32_t)0x00000020)
#define LVD_VDINTEN_CLEAR      ((uint32_t)0xFFFFFFDF)

/** @} */
/* End of group LVD_Private_Defines */

/** @defgroup LVD_Exported_Functions
  * @{
  */

/**
  * @brief  Enable the operation of voltage detection.
  * @param  None
  * @retval None
  */
void LVD_EnableVD(void)
{
    /* Set LVDCR1<EN> to enable voltage detection */
    TSB_LVD->CR1 |= LVD_EN_SET;
}

/**
  * @brief  Disable the operation of voltage detection.
  * @param  None
  * @retval None
  */
void LVD_DisableVD(void)
{
    /* Clear LVDCR1<EN> to disable voltage detection */
    TSB_LVD->CR1 &= LVD_EN_CLEAR;
}

/**
  * @brief  Select detection voltage level.
  * @param  VDLevel : voltage detection level, which can be:
  *             LVD_VDLVL_280, LVD_VDLVL_285, LVD_VDLVL_290,
  *             LVD_VDLVL_295, LVD_VDLVL_300, LVD_VDLVL_305,
  *             LVD_VDLVL_310, LVD_VDLVL_315.
  * @retval None
  */
void LVD_SetVDLevel(uint32_t VDLevel)
{
    uint32_t regval = TSB_LVD->CR1;

    /* Check the parameter */
    assert_param(IS_LVD_VD_LEVEL(VDLevel));

    regval &= LVD_VDLVL_CLEAR;
    regval |= VDLevel;
    TSB_LVD->CR1 = regval;
}

/**
  * @brief  Get voltage detection interrupt status.
  * @param  None
  * @retval LVD_VD_UPPER, LVD_VD_LOWER.
  */
LVD_VDStatus LVD_GetVDStatus(void)
{
    LVD_VDStatus result = LVD_VD_UPPER;
    uint32_t regval = TSB_LVD->CR1;
    regval &= LVD_VDST_MASK;

    if (regval) {
        result = LVD_VD_LOWER;
    } else {
        /* Do nothing */
    }
    return result;
}

/**
  * @brief  Enable or disable LVD reset output of voltage detection.
  * @param  ENABLE or DISABLE
  * @retval None
  */
void LVD_SetVDResetOutput(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set LVDCR1<RSTEN> to 1 */
        TSB_LVD->CR1 |= LVD_VDRSTEN_SET;
    } else {
        /* Clear LVDCR1<RSTEN> to 0 */
        TSB_LVD->CR1 &= LVD_VDRSTEN_CLEAR;
    }
}

/**
  * @brief  Enable or disable LVD interrupt output of voltage detection.
  * @param  ENABLE or DISABLE
  * @retval None
  */
void LVD_SetVDINTOutput(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set LVDCR1<INTEN> to 1 */
        TSB_LVD->CR1 |= LVD_VDINTEN_SET;
    } else {
        /* Clear LVDCR1<INTEN> to 0 */
        TSB_LVD->CR1 &= LVD_VDINTEN_CLEAR;
    }
}

/** @} */
/* End of group LVD_Exported_Functions */
/** @} */
/* End of group LVD */
/** @} */
/* End of group TX04_Periph_Driver */
#endif                          /* defined(__TMPM46B_LVD_H) */
