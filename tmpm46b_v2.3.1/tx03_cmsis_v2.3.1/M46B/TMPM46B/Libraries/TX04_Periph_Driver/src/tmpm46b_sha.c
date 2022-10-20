/**
 *******************************************************************************
 * @file    tmpm46b_sha.c
 * @brief   This file provides API functions for SHA driver.
 * @version V2.0.2.1
 * @date    2015/02/29
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_sha.h"

#if defined(__TMPM46B_SHA_H)
/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @defgroup SHA 
  * @brief SHA driver modules
  * @{
  */
/** @defgroup SHA_Private_Defines
  * @{
  */

static volatile uint32_t *const SHA_INIT[8U] = {
    &TSB_SHA->INIT0, &TSB_SHA->INIT1, &TSB_SHA->INIT2, &TSB_SHA->INIT3,
    &TSB_SHA->INIT4, &TSB_SHA->INIT5, &TSB_SHA->INIT6, &TSB_SHA->INIT7
};

static volatile uint32_t *const SHA_MSG[16] = {
    &TSB_SHA->MSG00, &TSB_SHA->MSG01, &TSB_SHA->MSG02, &TSB_SHA->MSG03,
    &TSB_SHA->MSG04, &TSB_SHA->MSG05, &TSB_SHA->MSG06, &TSB_SHA->MSG07,
    &TSB_SHA->MSG08, &TSB_SHA->MSG09, &TSB_SHA->MSG10, &TSB_SHA->MSG11,
    &TSB_SHA->MSG12, &TSB_SHA->MSG13, &TSB_SHA->MSG14, &TSB_SHA->MSG15
};

static const volatile uint32_t *const SHA_RESULT[8U] = {
    &TSB_SHA->RESULT0, &TSB_SHA->RESULT1, &TSB_SHA->RESULT2, &TSB_SHA->RESULT3,
    &TSB_SHA->RESULT4, &TSB_SHA->RESULT5, &TSB_SHA->RESULT6, &TSB_SHA->RESULT7
};

#define SHA_START_START_SET              ((uint32_t)0x00000001)
#define SHA_START_START_CLEAR            ((uint32_t)0x00000000)

#define SHA_CR_INTEN_CLEAR               ((uint32_t)0xFFFFFFF7)
#define SHA_CR_INTEN_SET                 ((uint32_t)0x00000008)

#define SHA_CR_HASHINIT_CLEAR            ((uint32_t)0xFFFFFFF8)
#define SHA_CR_HASHINIT_PREVIOUS         ((uint32_t)0x00000000)
#define SHA_CR_HASHINIT_REG              ((uint32_t)0x00000003)
#define SHA_CR_HASHINIT_256_BIT          ((uint32_t)0x00000004)
#define SHA_CR_HASHINIT_224_BIT          ((uint32_t)0x00000007)

#define SHA_DMAEN_DMAEN_CLEAR            ((uint32_t)0x00000000)
#define SHA_DMAEN_DMAEN_SET              ((uint32_t)0x00000001)

#define SHA_STATUS_BUSY_SET              ((uint32_t)0x00000001)

#define INT_IPRST_IPRST_1_SET            ((uint32_t)0x00000002)
#define INT_IPRST_IPRST_1_CLEAR          ((uint32_t)0xFFFFFFFD)

#define SRST_PROTECT_DISABLE             0x6bU

/** @} */
/* End of group SHA_Private_Defines */

/** @defgroup SHA_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group SHA_Private_FunctionPrototypes */

/** @defgroup SHA_Private_Functions
  * @{
  */

/** @} */
/* End of group SHA_Private_Functions */

/** @defgroup SHA_Exported_Functions
  * @{
  */

/**
  * @brief  Start or stop the SHA processor.
  * @param  Cmd: The command for the SHA processor.
  *   This parameter can be one of the following values:
  *   SHA_START, SHA_STOP.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @note  This function setting is ignored when SHADMAEN<DMAEN>=1.
  * @register The used register:
  *   SHASTART<START>
  */
Result SHA_SetRunState(SHA_RunCmd Cmd)
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_SHA_RUN_CMD(Cmd));

    if (SHA_GetCalculationStatus() == SHA_CALCULATION_COMPLETE) {
        if (Cmd == SHA_START) {
            TSB_SHA->START = SHA_START_START_SET;
        } else {
            TSB_SHA->START = SHA_START_START_CLEAR;
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Set interrupt output after calculation is complete.
  * @param  CalculationInt: Interrupt control. 
  *   This parameter can be one of the following values:
  *   SHA_INT_LAST_CALCULATION, SHA_INT_EACH_CALCULATION.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   SHACR<INTEN>
  */
Result SHA_SetCalculationInt(SHA_CalculationInt CalculationInt)
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_SHA_CALCULATION_INT(CalculationInt));

    if (SHA_GetCalculationStatus() == SHA_CALCULATION_COMPLETE) {
        if (CalculationInt == SHA_INT_LAST_CALCULATION) {
            TSB_SHA->CR &= SHA_CR_INTEN_CLEAR;
        } else {
            TSB_SHA->CR |= SHA_CR_INTEN_SET;
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Set the Hash initial value mode.
  * @param  InitMode: The Hash initial value mode.
  *   This parameter can be one of the following values:
  *   SHA_INIT_VALUE_PREVIOUS, SHA_INIT_VALUE_REG, 
  *   SHA_INIT_VALUE_256_BIT, SHA_INIT_VALUE_224_BIT.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   SHACR<HASHINIT[2:0]>
  */
Result SHA_SetInitMode(SHA_InitMode InitMode)
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_SHA_INIT_MODE(InitMode));

    if (SHA_GetCalculationStatus() == SHA_CALCULATION_COMPLETE) {
        TSB_SHA->CR &= SHA_CR_HASHINIT_CLEAR;

        switch (InitMode) {
        case SHA_INIT_VALUE_PREVIOUS:
            TSB_SHA->CR |= SHA_CR_HASHINIT_PREVIOUS;
            break;
        case SHA_INIT_VALUE_REG:
            TSB_SHA->CR |= SHA_CR_HASHINIT_REG;
            break;
        case SHA_INIT_VALUE_256_BIT:
            TSB_SHA->CR |= SHA_CR_HASHINIT_256_BIT;
            break;
        case SHA_INIT_VALUE_224_BIT:
            TSB_SHA->CR |= SHA_CR_HASHINIT_224_BIT;
            break;
        default:
            /* Do nothing */
            break;
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Set the Hash initial value register.
  * @param  INIT[8U]: An array that contains the Hash initial value.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   SHAINITn<INIT[31:0]> (n can be 0,1,2,3,4,5,6,7)
  */
Result SHA_SetInitValue(uint32_t INIT[8U])
{
    uint32_t i = 0U;
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(INIT));

    if (SHA_GetCalculationStatus() == SHA_CALCULATION_COMPLETE) {
        /* INIT[0] is for SHAINIT7; INIT[7] is for SHAINIT0. So the array looks like an initial value */
        for (i = 0U; i < 8U; i++) {
            *SHA_INIT[7U - i] = INIT[i];
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Enable or disable the DMA transfer.
  * @param  DMATransfer: Specify the DMA transfer.
  *   This parameter can be one of the following values:
  *   ENABLE, DISABLE.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   SHADMAEN<DMAEN>
  */
Result SHA_SetDMAState(FunctionalState DMATransfer)
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(DMATransfer));

    if (SHA_GetCalculationStatus() == SHA_CALCULATION_COMPLETE) {
        if (DMATransfer == DISABLE) {
            TSB_SHA->DMAEN = SHA_DMAEN_DMAEN_CLEAR;
        } else {
            TSB_SHA->DMAEN = SHA_DMAEN_DMAEN_SET;
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the DMA transfer state.
  * @param  None
  * @retval The DMA transfer state.
  *   The value returned can be one of the following values:
  *   ENABLE, DISABLE.
  * @register The used register:
  *   SHADMAEN<DMAEN>
  */
FunctionalState SHA_GetDMAState(void)
{
    FunctionalState retval = DISABLE;

    if (TSB_SHA->DMAEN == SHA_DMAEN_DMAEN_SET) {
        retval = ENABLE;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Set the whole message length in unit of byte.
  * @param  MSGLEN[2U]: An array that contains the whole message length in unit of byte.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   SHAMSGLENn (n can be 0,1)
  */
Result SHA_SetMsgLen(uint32_t MSGLEN[2U])
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(MSGLEN));

    if (SHA_GetCalculationStatus() == SHA_CALCULATION_COMPLETE) {
        /* MSGLEN[0] is for SHAMSGLEN1; MSGLEN[1] is for SHAMSGLEN0. 
           So the array looks like the whole message length value */
        TSB_SHA->MSGLEN1 = MSGLEN[0U];
        TSB_SHA->MSGLEN0 = MSGLEN[1U];
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Set the unhandled message length in unit of byte.
  * @param  REMAIN[2U]: An array that contains the unhandled message length in unit of byte.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   SHAREMAINn (n can be 0,1)
  */
Result SHA_SetRmnMsgLen(uint32_t REMAIN[2U])
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(REMAIN));

    if (SHA_GetCalculationStatus() == SHA_CALCULATION_COMPLETE) {
        /* REMAIN[0] is for SHAREMAIN1; REMAIN[1] is for SHAREMAIN0.
           So the array looks like the whole message length value. */
        TSB_SHA->REMAIN1 = REMAIN[0U];
        TSB_SHA->REMAIN0 = REMAIN[1U];
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the unhandled message length in unit of byte.
  * @param  RmnMsgLen[2U]: A point that points to the value of unhandled message length.
  * @retval None
  * @register The used register:
  *   SHAREMAINn (n can be 0,1)
  */
void SHA_GetRmnMsgLen(uint32_t RmnMsgLen[2U])
{
    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(RmnMsgLen));

    /* RmnMsgLen[0] is for SHAREMAIN1; RmnMsgLen[1] is for SHAREMAIN0.
       So the array looks like the whole message length value. */
    RmnMsgLen[0U] = TSB_SHA->REMAIN1;
    RmnMsgLen[1U] = TSB_SHA->REMAIN0;
}

/**
  * @brief  Set a 512-bit message.
  * @param  MSG[16U]: An array that contains a 512-bit message.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   SHAMSGn<MSG[31:0]> (n can be 00 to 15)
  */
Result SHA_SetMessage(uint32_t MSG[16U])
{
    uint32_t i = 0U;
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(MSG));

    if (SHA_GetCalculationStatus() == SHA_CALCULATION_COMPLETE) {
        /* MSG[0] is for SHAMSG15; MSG[15] is for SHAMSG00. So the array looks like a 512-bit message */
        for (i = 0U; i < 16U; i++) {
            *SHA_MSG[15U - i] = MSG[i];
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the calculation result. 
  * @param  Result[8U]: A point that points to the value of calculation result.
  * @retval None.
  * @register The used register:
  *   SHARESULTn (n can be 0,1,2,3,4,5,6,7)
  */
void SHA_GetResult(uint32_t HashRes[8U])
{
    uint32_t i = 0U;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(HashRes));

    for (i = 0U; i < 8U; i++) {
        HashRes[i] = *SHA_RESULT[7U - i];
    }
}

/**
  * @brief  Get the calculation status.
  * @param  None
  * @retval The calculation status.
  *   The value returned can be one of the following values:
  *   SHA_CALCULATION_COMPLETE, SHA_CALCULATION_PROCESS.
  * @note  Do not write any value to SHA registers when calculation is in process.
  * @register The used register:
  *   SHASTATUS<BUSY>
  */
SHA_CalculationStatus SHA_GetCalculationStatus(void)
{
    SHA_CalculationStatus retval = SHA_CALCULATION_COMPLETE;

    if (TSB_SHA->STATUS == SHA_STATUS_BUSY_SET) {
        retval = SHA_CALCULATION_PROCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Reset SHA by peripheral function.
  * @param  None
  * @retval None
  * @register The used register:
  *   SRSTPROTECT
  *   SRSTIPRST<IPRST1>
  */  
void SHA_IPReset(void)
{
    volatile uint32_t iprst1 = 0U;
    volatile uint32_t protect = 0U;

    protect = TSB_SRST->PROTECT;

    /* Disable the access protection of SRSTIPRST register */
    TSB_SRST->PROTECT = SRST_PROTECT_DISABLE;

    TSB_SRST->IPRST |= INT_IPRST_IPRST_1_SET;

    /* Confirm INT1IPRST<IPRST1> = 1 */
    do {
        iprst1 = TSB_SRST->IPRST & INT_IPRST_IPRST_1_SET;
    }
    while (iprst1 != INT_IPRST_IPRST_1_SET);

    /* Release reset state */
    TSB_SRST->IPRST &= INT_IPRST_IPRST_1_CLEAR;

    /* Return previous value to SRSTPROTECT register */
    TSB_SRST->PROTECT = protect;
}

/** @} */
/* End of group SHA_Exported_Functions */

/** @} */
/* End of group SHA */

/** @} */
/* End of group TX04_Periph_Driver */
#endif                          /* defined(__TMPM46B_SHA_H) */
