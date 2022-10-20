/**
 *******************************************************************************
 * @file    tmpm46b_mla.c
 * @brief   This file provides API functions for MLA driver.
 * @version V2.0.2.1
 * @date    2015/02/28
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_mla.h"

#if defined(__TMPM46B_MLA_H)
/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @defgroup MLA 
  * @brief MLA driver modules
  * @{
  */
/** @defgroup MLA_Private_Defines
  * @{
  */

static volatile uint32_t *const MLA_BLK[32U][8U] = {
    {
     &TSB_MLA->BLK0_0, &TSB_MLA->BLK0_1, &TSB_MLA->BLK0_2, &TSB_MLA->BLK0_3,
     &TSB_MLA->BLK0_4, &TSB_MLA->BLK0_5, &TSB_MLA->BLK0_6, &TSB_MLA->BLK0_7},
    {
     &TSB_MLA->BLK1_0, &TSB_MLA->BLK1_1, &TSB_MLA->BLK1_2, &TSB_MLA->BLK1_3,
     &TSB_MLA->BLK1_4, &TSB_MLA->BLK1_5, &TSB_MLA->BLK1_6, &TSB_MLA->BLK1_7},
    {
     &TSB_MLA->BLK2_0, &TSB_MLA->BLK2_1, &TSB_MLA->BLK2_2, &TSB_MLA->BLK2_3,
     &TSB_MLA->BLK2_4, &TSB_MLA->BLK2_5, &TSB_MLA->BLK2_6, &TSB_MLA->BLK2_7},
    {
     &TSB_MLA->BLK3_0, &TSB_MLA->BLK3_1, &TSB_MLA->BLK3_2, &TSB_MLA->BLK3_3,
     &TSB_MLA->BLK3_4, &TSB_MLA->BLK3_5, &TSB_MLA->BLK3_6, &TSB_MLA->BLK3_7},
    {
     &TSB_MLA->BLK4_0, &TSB_MLA->BLK4_1, &TSB_MLA->BLK4_2, &TSB_MLA->BLK4_3,
     &TSB_MLA->BLK4_4, &TSB_MLA->BLK4_5, &TSB_MLA->BLK4_6, &TSB_MLA->BLK4_7},
    {
     &TSB_MLA->BLK5_0, &TSB_MLA->BLK5_1, &TSB_MLA->BLK5_2, &TSB_MLA->BLK5_3,
     &TSB_MLA->BLK5_4, &TSB_MLA->BLK5_5, &TSB_MLA->BLK5_6, &TSB_MLA->BLK5_7},
    {
     &TSB_MLA->BLK6_0, &TSB_MLA->BLK6_1, &TSB_MLA->BLK6_2, &TSB_MLA->BLK6_3,
     &TSB_MLA->BLK6_4, &TSB_MLA->BLK6_5, &TSB_MLA->BLK6_6, &TSB_MLA->BLK6_7},
    {
     &TSB_MLA->BLK7_0, &TSB_MLA->BLK7_1, &TSB_MLA->BLK7_2, &TSB_MLA->BLK7_3,
     &TSB_MLA->BLK7_4, &TSB_MLA->BLK7_5, &TSB_MLA->BLK7_6, &TSB_MLA->BLK7_7},
    {
     &TSB_MLA->BLK8_0, &TSB_MLA->BLK8_1, &TSB_MLA->BLK8_2, &TSB_MLA->BLK8_3,
     &TSB_MLA->BLK8_4, &TSB_MLA->BLK8_5, &TSB_MLA->BLK8_6, &TSB_MLA->BLK8_7},
    {
     &TSB_MLA->BLK9_0, &TSB_MLA->BLK9_1, &TSB_MLA->BLK9_2, &TSB_MLA->BLK9_3,
     &TSB_MLA->BLK9_4, &TSB_MLA->BLK9_5, &TSB_MLA->BLK9_6, &TSB_MLA->BLK9_7},
    {
     &TSB_MLA->BLK10_0, &TSB_MLA->BLK10_1, &TSB_MLA->BLK10_2, &TSB_MLA->BLK10_3,
     &TSB_MLA->BLK10_4, &TSB_MLA->BLK10_5, &TSB_MLA->BLK10_6, &TSB_MLA->BLK10_7},
    {
     &TSB_MLA->BLK11_0, &TSB_MLA->BLK11_1, &TSB_MLA->BLK11_2, &TSB_MLA->BLK11_3,
     &TSB_MLA->BLK11_4, &TSB_MLA->BLK11_5, &TSB_MLA->BLK11_6, &TSB_MLA->BLK11_7},
    {
     &TSB_MLA->BLK12_0, &TSB_MLA->BLK12_1, &TSB_MLA->BLK12_2, &TSB_MLA->BLK12_3,
     &TSB_MLA->BLK12_4, &TSB_MLA->BLK12_5, &TSB_MLA->BLK12_6, &TSB_MLA->BLK12_7},
    {
     &TSB_MLA->BLK13_0, &TSB_MLA->BLK13_1, &TSB_MLA->BLK13_2, &TSB_MLA->BLK13_3,
     &TSB_MLA->BLK13_4, &TSB_MLA->BLK13_5, &TSB_MLA->BLK13_6, &TSB_MLA->BLK13_7},
    {
     &TSB_MLA->BLK14_0, &TSB_MLA->BLK14_1, &TSB_MLA->BLK14_2, &TSB_MLA->BLK14_3,
     &TSB_MLA->BLK14_4, &TSB_MLA->BLK14_5, &TSB_MLA->BLK14_6, &TSB_MLA->BLK14_7},
    {
     &TSB_MLA->BLK15_0, &TSB_MLA->BLK15_1, &TSB_MLA->BLK15_2, &TSB_MLA->BLK15_3,
     &TSB_MLA->BLK15_4, &TSB_MLA->BLK15_5, &TSB_MLA->BLK15_6, &TSB_MLA->BLK15_7},
    {
     &TSB_MLA->BLK16_0, &TSB_MLA->BLK16_1, &TSB_MLA->BLK16_2, &TSB_MLA->BLK16_3,
     &TSB_MLA->BLK16_4, &TSB_MLA->BLK16_5, &TSB_MLA->BLK16_6, &TSB_MLA->BLK16_7},
    {
     &TSB_MLA->BLK17_0, &TSB_MLA->BLK17_1, &TSB_MLA->BLK17_2, &TSB_MLA->BLK17_3,
     &TSB_MLA->BLK17_4, &TSB_MLA->BLK17_5, &TSB_MLA->BLK17_6, &TSB_MLA->BLK17_7},
    {
     &TSB_MLA->BLK18_0, &TSB_MLA->BLK18_1, &TSB_MLA->BLK18_2, &TSB_MLA->BLK18_3,
     &TSB_MLA->BLK18_4, &TSB_MLA->BLK18_5, &TSB_MLA->BLK18_6, &TSB_MLA->BLK18_7},
    {
     &TSB_MLA->BLK19_0, &TSB_MLA->BLK19_1, &TSB_MLA->BLK19_2, &TSB_MLA->BLK19_3,
     &TSB_MLA->BLK19_4, &TSB_MLA->BLK19_5, &TSB_MLA->BLK19_6, &TSB_MLA->BLK19_7},
    {
     &TSB_MLA->BLK20_0, &TSB_MLA->BLK20_1, &TSB_MLA->BLK20_2, &TSB_MLA->BLK20_3,
     &TSB_MLA->BLK20_4, &TSB_MLA->BLK20_5, &TSB_MLA->BLK20_6, &TSB_MLA->BLK20_7},
    {
     &TSB_MLA->BLK21_0, &TSB_MLA->BLK21_1, &TSB_MLA->BLK21_2, &TSB_MLA->BLK21_3,
     &TSB_MLA->BLK21_4, &TSB_MLA->BLK21_5, &TSB_MLA->BLK21_6, &TSB_MLA->BLK21_7},
    {
     &TSB_MLA->BLK22_0, &TSB_MLA->BLK22_1, &TSB_MLA->BLK22_2, &TSB_MLA->BLK22_3,
     &TSB_MLA->BLK22_4, &TSB_MLA->BLK22_5, &TSB_MLA->BLK22_6, &TSB_MLA->BLK22_7},
    {
     &TSB_MLA->BLK23_0, &TSB_MLA->BLK23_1, &TSB_MLA->BLK23_2, &TSB_MLA->BLK23_3,
     &TSB_MLA->BLK23_4, &TSB_MLA->BLK23_5, &TSB_MLA->BLK23_6, &TSB_MLA->BLK23_7},
    {
     &TSB_MLA->BLK24_0, &TSB_MLA->BLK24_1, &TSB_MLA->BLK24_2, &TSB_MLA->BLK24_3,
     &TSB_MLA->BLK24_4, &TSB_MLA->BLK24_5, &TSB_MLA->BLK24_6, &TSB_MLA->BLK24_7},
    {
     &TSB_MLA->BLK25_0, &TSB_MLA->BLK25_1, &TSB_MLA->BLK25_2, &TSB_MLA->BLK25_3,
     &TSB_MLA->BLK25_4, &TSB_MLA->BLK25_5, &TSB_MLA->BLK25_6, &TSB_MLA->BLK25_7},
    {
     &TSB_MLA->BLK26_0, &TSB_MLA->BLK26_1, &TSB_MLA->BLK26_2, &TSB_MLA->BLK26_3,
     &TSB_MLA->BLK26_4, &TSB_MLA->BLK26_5, &TSB_MLA->BLK26_6, &TSB_MLA->BLK26_7},
    {
     &TSB_MLA->BLK27_0, &TSB_MLA->BLK27_1, &TSB_MLA->BLK27_2, &TSB_MLA->BLK27_3,
     &TSB_MLA->BLK27_4, &TSB_MLA->BLK27_5, &TSB_MLA->BLK27_6, &TSB_MLA->BLK27_7},
    {
     &TSB_MLA->BLK28_0, &TSB_MLA->BLK28_1, &TSB_MLA->BLK28_2, &TSB_MLA->BLK28_3,
     &TSB_MLA->BLK28_4, &TSB_MLA->BLK28_5, &TSB_MLA->BLK28_6, &TSB_MLA->BLK28_7},
    {
     &TSB_MLA->BLK29_0, &TSB_MLA->BLK29_1, &TSB_MLA->BLK29_2, &TSB_MLA->BLK29_3,
     &TSB_MLA->BLK29_4, &TSB_MLA->BLK29_5, &TSB_MLA->BLK29_6, &TSB_MLA->BLK29_7},
    {
     &TSB_MLA->BLK30_0, &TSB_MLA->BLK30_1, &TSB_MLA->BLK30_2, &TSB_MLA->BLK30_3,
     &TSB_MLA->BLK30_4, &TSB_MLA->BLK30_5, &TSB_MLA->BLK30_6, &TSB_MLA->BLK30_7},
    {
     &TSB_MLA->BLK31_0, &TSB_MLA->BLK31_1, &TSB_MLA->BLK31_2, &TSB_MLA->BLK31_3,
     &TSB_MLA->BLK31_4, &TSB_MLA->BLK31_5, &TSB_MLA->BLK31_6, &TSB_MLA->BLK31_7}
};

#define MLA_CR_COM_CLEAR                 ((uint32_t)0xF8FFFFFF)
#define MLA_CR_COM_SET                   ((uint32_t)0x07000000)
#define MLA_CR_SRC1_CLEAR                ((uint32_t)0xFFE0FFFF)
#define MLA_CR_SRC1_SET                  ((uint32_t)0x001F0000)
#define MLA_CR_SRC2_CLEAR                ((uint32_t)0xFFFFE0FF)
#define MLA_CR_SRC2_SET                  ((uint32_t)0x00001F00)
#define MLA_CR_RDB_CLEAR                 ((uint32_t)0xFFFFFFE0)
#define MLA_CR_RDB_SET                   ((uint32_t)0x0000001F)
#define MLA_ST_CABO_CLEAR                ((uint32_t)0xFFFFFFFE)
#define MLA_ST_CABO_SET                  ((uint32_t)0x00000001)
#define MLA_ST_BUSY_CLEAR                ((uint32_t)0xFFFFFFFD)
#define MLA_ST_BUSY_SET                  ((uint32_t)0x00000002)

#define INT_IPRST_IPRST_2_SET            ((uint32_t)0x00000004)
#define INT_IPRST_IPRST_2_CLEAR          ((uint32_t)0xFFFFFFFB)

#define SRST_PROTECT_DISABLE             0x6bU

/** @} */
/* End of group MLA_Private_Defines */

/** @defgroup MLA_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group MLA_Private_FunctionPrototypes */

/** @defgroup MLA_Private_Functions
  * @{
  */

/** @} */
/* End of group MLA_Private_Functions */

/** @defgroup MLA_Exported_Functions
  * @{
  */

/**
  * @brief  Set the calculation mode.
  * @param  CalculationMode: Specify the calculation mode.
  *   This parameter can be one of the following values:
  *   MLA_COM_MODE_MUL, MLA_COM_MODE_ADD, MLA_COM_MODE_SUB.
  * @retval None
  * @register The used register:
  *   MLACR<COM[2:0]>
  */
void MLA_SetCalculationMode(uint32_t CalculationMode)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_MLA_COM_MODE(CalculationMode));

    tmp = TSB_MLA->CR & MLA_CR_COM_CLEAR;

    if (MLA_GetCalculationStatus() == MLA_CALCULATION_STOP) {
        tmp |= CalculationMode;
    } else {
        /* Do nothing */
    }

    TSB_MLA->CR = tmp;
}

/**
  * @brief  Get the calculation mode.
  * @param  None
  * @retval Get the calculation mode.
  *   The value returned can be one of the following values:
  *   MLA_CalculationMode_MUL, MLA_CalculationMode_ADD, MLA_CalculationMode_SUB.
  * @register The used register:
  *   MLACR<COM[2:0]>
  */
MLA_CalculationMode MLA_GetCalculationMode(void)
{
    uint32_t tmp = 0U;
    MLA_CalculationMode retval = MLA_CalculationMode_UNKNOWN;

    tmp = TSB_MLA->CR;
    tmp &= MLA_CR_COM_SET;
    switch (tmp) {
    case MLA_COM_MODE_MUL:
        retval = MLA_CalculationMode_MUL;
        break;
    case MLA_COM_MODE_ADD:
        retval = MLA_CalculationMode_ADD;
        break;
    case MLA_COM_MODE_SUB:
        retval = MLA_CalculationMode_SUB;
        break;
    default:
        /* Do nothing */
        break;
    }

    return retval;
}

/**
  * @brief  Set a data block number that is substituted into "a".
  * @param  BlkNum: Data block number. 
  *   This parameter can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31.             
  * @retval None
  * @register The used registers:
  *   MLACR<SRC1[4:0]>  
  *   MLABLKm_n<BLK[31:0]> (m can be 0 to 31, n can be 0 to 7)
  */
void MLA_SetADataBlkNum(uint8_t BlkNum)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_MLA_BLK_NUM(BlkNum));

    tmp = TSB_MLA->CR & MLA_CR_SRC1_CLEAR;

    if (MLA_GetCalculationStatus() == MLA_CALCULATION_STOP) {
        tmp |= ((uint32_t) BlkNum << 16);
    } else {
        /* Do nothing */
    }

    TSB_MLA->CR = tmp;
}

/**
  * @brief  Get the data block number that is substituted into "a".
  * @param  None             
  * @retval Get the data block number that is substituted into "a".
  *   The value returned can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31, or other unknown value. 
  * @register The used registers:
  *   MLACR<SRC1[4:0]>  
  *   MLABLKm_n<BLK[31:0]> (m can be 0 to 31, n can be 0 to 7)
  */
uint8_t MLA_GetADataBlkNum(void)
{
    uint32_t tmp = 0U;
    uint8_t pllset = 0U;

    tmp = TSB_MLA->CR & MLA_CR_SRC1_SET;
    tmp |= (tmp >> 16);

    pllset = (uint8_t) tmp;

    return pllset;
}

/**
  * @brief  Set a data block number that is substituted into "b".
  * @param  BlkNum: Data block number. 
  *   This parameter can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31.             
  * @retval None
  * @register The used registers:
  *   MLACR<SRC2[4:0]>  
  *   MLABLKm_n<BLK[31:0]> (m can be 0 to 31, n can be 0 to 7)
  */
void MLA_SetBDataBlkNum(uint8_t BlkNum)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_MLA_BLK_NUM(BlkNum));

    tmp = TSB_MLA->CR & MLA_CR_SRC2_CLEAR;

    if (MLA_GetCalculationStatus() == MLA_CALCULATION_STOP) {
        tmp |= ((uint32_t) BlkNum << 8);
    } else {
        /* Do nothing */
    }

    TSB_MLA->CR = tmp;
}

/**
  * @brief  Get the data block number that is substituted into "b".
  * @param  None             
  * @retval Get the data block number that is substituted into "b".
  *   The value returned can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31, or other unknown value. 
  * @register The used registers:
  *   MLACR<SRC2[4:0]>  
  *   MLABLKm_n<BLK[31:0]> (m can be 0 to 31, n can be 0 to 7)
  */
uint8_t MLA_GetBDataBlkNum(void)
{
    uint32_t tmp = 0U;
    uint8_t pllset = 0U;

    tmp = TSB_MLA->CR & MLA_CR_SRC2_SET;
    tmp |= (tmp >> 8);

    pllset = (uint8_t) tmp;

    return pllset;
}

/**
  * @brief  Set a data block number that is substituted into "w".
  * @param  BlkNum: Data block number. 
  *   This parameter can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31.             
  * @retval None
  * @register The used registers:
  *   MLACR<RDB[4:0]>  
  *   MLABLKm_n<BLK[31:0]> (m can be 0 to 31, n can be 0 to 7)
  */
void MLA_SetWDataBlkNum(uint8_t BlkNum)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_MLA_BLK_NUM(BlkNum));

    tmp = TSB_MLA->CR & MLA_CR_RDB_CLEAR;

    if (MLA_GetCalculationStatus() == MLA_CALCULATION_STOP) {
        tmp |= (uint32_t) BlkNum;
    } else {
        /* Do nothing */
    }

    TSB_MLA->CR = tmp;
}

/**
  * @brief  Get the data block number that is substituted into "w".
  * @param  None             
  * @retval Get the data block number that is substituted into "w".
  *   The value returned can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31, or other unknown value. 
  * @register The used registers:
  *   MLACR<RDB[4:0]>
  *   MLABLKm_n<BLK[31:0]> (m can be 0 to 31, n can be 0 to 7)
  */
uint8_t MLA_GetWDataBlkNum(void)
{
    uint32_t tmp = 0U;
    uint8_t pllset = 0U;

    tmp = TSB_MLA->CR & MLA_CR_RDB_SET;

    pllset = (uint8_t) tmp;

    return pllset;
}

/**
  * @brief  Get carry and borrow flag status.
  * @param  None
  * @retval Carry and borrow flag status.
  *   The value returned can be one of the following values:
  *   MLA_CARRYBORROW_NO, MLA_CARRYBORROW_OCCURS.
  * @register The used register:
  *   MLAST<CABO>
  */
MLA_CarryBorrowFlag MLA_GetCarryBorrowFlag(void)
{
    uint32_t mod = TSB_MLA->ST;
    MLA_CarryBorrowFlag retval = MLA_CARRYBORROW_NO;

    mod &= MLA_ST_CABO_SET;

    if (mod == MLA_ST_CABO_SET) {
        retval = MLA_CARRYBORROW_OCCURS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the status of the calculation.
  * @param  None
  * @retval Calculation status.
  *   The value returned can be one of the following values:
  *   MLA_CALCULATION_STOP, MLA_CALCULATION_PROGRESS.
  * @register The used register:
  *   MLAST<BUSY>
  */
MLA_CalculationStatus MLA_GetCalculationStatus(void)
{
    uint32_t mod = TSB_MLA->ST;
    MLA_CalculationStatus retval = MLA_CALCULATION_STOP;

    mod &= MLA_ST_BUSY_SET;

    if (mod == MLA_ST_BUSY_SET) {
        retval = MLA_CALCULATION_PROGRESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/** 
  * @brief  Set montgomery parameter.
  * @param  Data: Montgomery parameter, max 0xFFFFFFFF.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   MLAPARA
  */
Result MLA_SetMontgomeryParameter(uint32_t Data)
{
    Result retval = ERROR;

    if (MLA_GetCalculationStatus() == MLA_CALCULATION_STOP) {
        /* Write data into MLAPARA */
        TSB_MLA->PARA = Data;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get montgomery parameter.
  * @param  None
  * @retval Montgomery parameter
  * @register The used register:
  *   MLAPARA
  */
uint32_t MLA_GetMontgomeryParameter(void)
{
    uint32_t retval = 0U;

    /* Get montgomery parameter */
    retval = TSB_MLA->PARA;

    return retval;
}

/**
  * @brief  Write data to the specified data block number.
  * @param  BlkNum: Data block number. 
  *   This parameter can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31.            
  * @param  Data[8U]: Input data. 
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   MLABLKm_n<BLK[31:0]> (m can be 0 to 31, n can be 0 to 7)
  */
Result MLA_WriteDataBlkNum(uint8_t BlkNum, uint32_t Data[8U])
{
    uint32_t Num = 0U;
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_MLA_BLK_NUM(BlkNum));

    if (MLA_GetCalculationStatus() == MLA_CALCULATION_STOP) {
        for (Num = 0U; Num < 8U; Num++) {
            *MLA_BLK[BlkNum][Num] = Data[Num];
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Read data from the specified data block number.
  * @param  BlkNum: Data block number. 
  *   This parameter can be one of the following values:
  *   MLA_BLK_0, MLA_BLK_1, MLA_BLK_2, MLA_BLK_3, MLA_BLK_4,
  *   MLA_BLK_5, MLA_BLK_6, MLA_BLK_7, MLA_BLK_8, MLA_BLK_9,
  *   MLA_BLK_10, MLA_BLK_11, MLA_BLK_12, MLA_BLK_13, MLA_BLK_14,
  *   MLA_BLK_15, MLA_BLK_16, MLA_BLK_17, MLA_BLK_18, MLA_BLK_19,
  *   MLA_BLK_20, MLA_BLK_21, MLA_BLK_22, MLA_BLK_23, MLA_BLK_24,
  *   MLA_BLK_25, MLA_BLK_26, MLA_BLK_27, MLA_BLK_28, MLA_BLK_29,
  *   MLA_BLK_30, MLA_BLK_31.
  * @retval Output data.
  * @register The used registers:
  *   MLABLKm_n<BLK[31:0]> (m can be 0 to 31, n can be 0 to 7)
  */
void MLA_ReadDataBlkNum(uint8_t BlkNum, uint32_t Data[8U])
{
    uint32_t Num = 0U;

    /* Check the parameters */
    assert_param(IS_MLA_BLK_NUM(BlkNum));
    assert_param(IS_POINTER_NOT_NULL(Data));

    if (MLA_GetCalculationStatus() == MLA_CALCULATION_STOP) {
        for (Num = 0U; Num < 8U; Num++) {
            Data[Num] = *MLA_BLK[BlkNum][7U - Num];
        }
    } else {
        /* Do nothing */
    }
}

/**
  * @brief  Reset MLA by peripheral function.
  * @param  None
  * @retval None
  * @register The used register:
  *   SRSTPROTECT
  *   SRSTIPRST<IPRST2>
  */
void MLA_IPReset(void)
{
    volatile uint32_t iprst2 = 0U;
    volatile uint32_t protect = 0U;

    protect = TSB_SRST->PROTECT;

    /* Disable the access protection of SRSTIPRST register */
    TSB_SRST->PROTECT = SRST_PROTECT_DISABLE;

    TSB_SRST->IPRST |= INT_IPRST_IPRST_2_SET;

    /* Confirm INTIPRST<IPRST2> = 1 */
    do {
        iprst2 = TSB_SRST->IPRST & INT_IPRST_IPRST_2_SET;
    }
    while (iprst2 != INT_IPRST_IPRST_2_SET);

    /* Release reset state */
    TSB_SRST->IPRST &= INT_IPRST_IPRST_2_CLEAR;
    
    /* Return previous value to SRSTPROTECT register */
    TSB_SRST->PROTECT = protect;
}

/** @} */
/* End of group MLA_Exported_Functions */

/** @} */
/* End of group MLA */

/** @} */
/* End of group TX04_Periph_Driver */
#endif                          /* defined(__TMPM46B_MLA_H) */
