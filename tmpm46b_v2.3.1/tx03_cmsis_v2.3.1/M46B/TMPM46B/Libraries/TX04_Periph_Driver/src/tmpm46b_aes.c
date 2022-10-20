/**
 *******************************************************************************
 * @file    tmpm46b_aes.c
 * @brief   This file provides API functions for AES driver.
 * @version V2.0.2.1
 * @date    2015/02/29
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_aes.h"

#if defined(__TMPM46B_AES_H)
/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @defgroup AES 
  * @brief AES driver modules
  * @{
  */
/** @defgroup AES_Private_Defines
  * @{
  */

static volatile uint32_t *const AES_Key[8U] = {
    &TSB_AES->KEY0, &TSB_AES->KEY1, &TSB_AES->KEY2, &TSB_AES->KEY3,
    &TSB_AES->KEY4, &TSB_AES->KEY5, &TSB_AES->KEY6, &TSB_AES->KEY7
};

static const volatile uint32_t *const AES_RKey[8U] = {
    &TSB_AES->RKEY0, &TSB_AES->RKEY1, &TSB_AES->RKEY2, &TSB_AES->RKEY3,
    &TSB_AES->RKEY4, &TSB_AES->RKEY5, &TSB_AES->RKEY6, &TSB_AES->RKEY7
};

static volatile uint32_t *const AES_CNT[4U] = {
    &TSB_AES->CNT0, &TSB_AES->CNT1, &TSB_AES->CNT2, &TSB_AES->CNT3
};

static volatile uint32_t *const AES_IV[4U] = {
    &TSB_AES->IV0, &TSB_AES->IV1, &TSB_AES->IV2, &TSB_AES->IV3
};

#define AES_CLR_FIFOCLR_SET              ((uint32_t)0x00000001)

#define AES_MOD_OP_CLEAR                 ((uint32_t)0xFFFFFFFE)
#define AES_MOD_OP_SET                   ((uint32_t)0x00000001)
#define AES_MOD_DMAEN_CLEAR              ((uint32_t)0xFFFFFFFD)
#define AES_MOD_DMAEN_SET                ((uint32_t)0x00000002)
#define AES_MOD_KEYLEN_CLEAR             ((uint32_t)0xFFFFFFF3)
#define AES_MOD_KEYLEN_SET               ((uint32_t)0x0000000C)
#define AES_MOD_KEYLEN_128               ((uint32_t)0x00000000)
#define AES_MOD_KEYLEN_192               ((uint32_t)0x00000004)
#define AES_MOD_KEYLEN_256               ((uint32_t)0x00000008)
#define AES_MOD_ALGO_CLEAR               ((uint32_t)0xFFFFFFCF)
#define AES_MOD_ALGO_SET                 ((uint32_t)0x00000030)
#define AES_MOD_ALGO_ECB                 ((uint32_t)0x00000000)
#define AES_MOD_ALGO_CBC                 ((uint32_t)0x00000010)
#define AES_MOD_ALGO_CTR                 ((uint32_t)0x00000020)

#define AES_STATUS_BUSY_SET              ((uint32_t)0x00000001)
#define AES_STATUS_WFIFOST_SET           ((uint32_t)0x00000002)
#define AES_STATUS_RFIFOST_SET           ((uint32_t)0x00000004)

#define INT_IPRST_IPRST_0_SET            ((uint32_t)0x00000001)
#define INT_IPRST_IPRST_0_CLEAR          ((uint32_t)0xFFFFFFFE)

#define SRST_PROTECT_DISABLE             0x6bU

/** @} */
/* End of group AES_Private_Defines */

/** @defgroup AES_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group AES_Private_FunctionPrototypes */

/** @defgroup AES_Private_Functions
  * @{
  */

/** @} */
/* End of group AES_Private_Functions */

/** @defgroup AES_Exported_Functions
  * @{
  */

/**
  * @brief  Set plaintext/encrypted data.
  * @param  Data: Plaintext/encrypted data.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   AESDT<DT[31:0]>
  */
Result AES_SetData(uint32_t Data)
{
    Result retval = ERROR;

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        TSB_AES->DT = Data;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the calculation result. 
  * @param  None
  * @retval The calculation result.
  * @register The used register:
  *   AESODT<ODT[31:0]>
  */
uint32_t AES_GetResult(void)
{
    uint32_t retval = 0U;

    retval = TSB_AES->ODT;

    return retval;
}

/**
  * @brief  Set key data.
  * @param  KeyLength: The key length. 
  *   This parameter can be one of the following values:
  *   AES_KEY_LENGTH_128, AES_KEY_LENGTH_192, AES_KEY_LENGTH_256.
  * @param  Key[]: The key data that varies depending on the key length. 
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   AESKEYn<KEY[31:0]> (n can be 0,1,2,3,4,5,6,7)
  */
Result AES_SetKey(AES_KeyLength KeyLength, uint32_t Key[])
{
    uint8_t KeyNum = 0U;
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_AES_KEY_LENGTH(KeyLength));
    assert_param(IS_POINTER_NOT_NULL(Key));

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        switch (KeyLength) {
        case AES_KEY_LENGTH_128:
            for (KeyNum = 0U; KeyNum < 4U; KeyNum++) {
                *AES_Key[4U + KeyNum] = Key[KeyNum];
            }
            break;
        case AES_KEY_LENGTH_192:
            for (KeyNum = 0U; KeyNum < 6U; KeyNum++) {
                *AES_Key[2U + KeyNum] = Key[KeyNum];
            }
            break;
        case AES_KEY_LENGTH_256:
            for (KeyNum = 0U; KeyNum < 8U; KeyNum++) {
                *AES_Key[0U + KeyNum] = Key[KeyNum];
            }
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
  * @brief  Get the output key data.
  * @param  KeyNum: Specify the key to be got.
  *   This parameter can be one of the following values:
  *   AES_KEY_NUM_0, AES_KEY_NUM_1, AES_KEY_NUM_2, AES_KEY_NUM_3,
  *   AES_KEY_NUM_4, AES_KEY_NUM_5, AES_KEY_NUM_6, AES_KEY_NUM_7.
  * @retval Output key data.
  * @register The used registers:
  *   AESRKEYn<RKEY[31:0]> (n can be 0,1,2,3,4,5,6,7)
  */
uint32_t AES_GetKey(uint32_t KeyNum)
{
    uint32_t retval = 0U;

    /* Check the parameters */
    assert_param(IS_AES_KEY_NUM(KeyNum));

    retval = *AES_RKey[KeyNum];

    return retval;
}

/**
  * @brief  Set the counter initial value in CTR mode.
  * @param  CNT[4U]: The counter initial value.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   AESCNTn<CNT[31:0]> (n can be 0,1,2,3)
  */
Result AES_SetCntInit(uint32_t CNT[4U])
{
    uint32_t i = 0U;
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(CNT));

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        for (i = 0U; i < 4U; i++) {
            *AES_CNT[i] = CNT[i];
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Set the initial vector in CBC mode.
  * @param  IV[4U]: The initial vector.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used registers:
  *   AESIVn<IV[31:0]> (n can be 0,1,2,3)
  */
Result AES_SetVectorInit(uint32_t IV[4U])
{
    uint32_t i = 0U;
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(IV));

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        for (i = 0U; i < 4U; i++) {
            *AES_IV[i] = IV[i];
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Clear both the write FIFO and the read FIFO.
  * @param  None
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   AESCLR<FIFOCLR>
  */
Result AES_ClrFIFO(void)
{
    Result retval = ERROR;

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        TSB_AES->CLR = AES_CLR_FIFOCLR_SET;
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Initialize the AES.
  * @param  InitStruct: The structure containing basic AES configuration.
  * @retval None
  * @register The used register:
  *   AESMOD<OP><KEYLEN[1:0]><ALGO[1:0]>
  */
void AES_Init(AES_InitTypeDef * InitStruct)
{
    /* Check the parameters */
    assert_param(IS_POINTER_NOT_NULL(InitStruct));
    assert_param(IS_AES_ALGORITHM_MODE(InitStruct->AlgorithmMode));
    assert_param(IS_AES_KEY_LENGTH(InitStruct->KeyLength));

    if (InitStruct->AlgorithmMode == AES_CTR_MODE) {
        /* In CTR mode, set "0" for both encryption and decryption. */
        TSB_AES->MOD &= AES_MOD_OP_CLEAR;
    } else {
        assert_param(IS_AES_OPERATION_MODE(InitStruct->OperationMode));
        AES_SetOperationMode(InitStruct->OperationMode);
    }

    AES_SetKeyLength(InitStruct->KeyLength);

    AES_SetAlgorithmMode(InitStruct->AlgorithmMode);
}

/**
  * @brief  Set the operation mode
  * @param  OperationMode: Specify the operation mode.
  *   This parameter can be one of the following values:
  *   AES_ENCRYPTION_MODE, AES_DECRYPTION_MODE.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   AESMOD<OP>
  */
Result AES_SetOperationMode(AES_OperationMode OperationMode)
{
    Result retval = ERROR;
    /* Check the parameters */
    assert_param(IS_AES_OPERATION_MODE(OperationMode));

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        if (OperationMode == AES_ENCRYPTION_MODE) {
            TSB_AES->MOD &= AES_MOD_OP_CLEAR;
        } else {
            TSB_AES->MOD |= AES_MOD_OP_SET;
        }
        retval = SUCCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the operation mode.
  * @param  None
  * @retval The operation mode.
  *   The value returned can be one of the following values:
  *   AES_ENCRYPTION_MODE, AES_DECRYPTION_MODE.
  * @register The used register:
  *   AESMOD<OP>
  */
AES_OperationMode AES_GetOperationMode(void)
{
    uint32_t mod = TSB_AES->MOD;
    AES_OperationMode retval = AES_ENCRYPTION_MODE;

    mod &= AES_MOD_OP_SET;

    if (mod == AES_MOD_OP_SET) {
        retval = AES_DECRYPTION_MODE;
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
  *   AESMOD<DMAEN>
  */
Result AES_SetDMAState(FunctionalState DMATransfer)
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(DMATransfer));

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        if (DMATransfer == DISABLE) {
            TSB_AES->MOD &= AES_MOD_DMAEN_CLEAR;
        } else {
            TSB_AES->MOD |= AES_MOD_DMAEN_SET;
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
  *   AESMOD<DMAEN>
  */
FunctionalState AES_GetDMAState(void)
{
    uint32_t mod = TSB_AES->MOD;
    FunctionalState retval = DISABLE;

    mod &= AES_MOD_DMAEN_SET;

    if (mod == AES_MOD_DMAEN_SET) {
        retval = ENABLE;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Set the key length.
  * @param  KeyLength: Specify the key length.
  *   This parameter can be one of the following values:
  *   AES_KEY_LENGTH_128, AES_KEY_LENGTH_192, AES_KEY_LENGTH_256.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   AESMOD<KEYLEN[1:0]>
  */
Result AES_SetKeyLength(AES_KeyLength KeyLength)
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_AES_KEY_LENGTH(KeyLength));

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        TSB_AES->MOD &= AES_MOD_KEYLEN_CLEAR;

        switch (KeyLength) {
        case AES_KEY_LENGTH_128:
            TSB_AES->MOD |= AES_MOD_KEYLEN_128;
            break;
        case AES_KEY_LENGTH_192:
            TSB_AES->MOD |= AES_MOD_KEYLEN_192;
            break;
        case AES_KEY_LENGTH_256:
            TSB_AES->MOD |= AES_MOD_KEYLEN_256;
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
  * @brief  Get the key length.
  * @param  None
  * @retval The key length.
  *   The value returned can be one of the following values:
  *   AES_KEY_LENGTH_128, AES_KEY_LENGTH_192, AES_KEY_LENGTH_256, AES_KEY_UNKNOWN_LENGTH
  * @register The used register:
  *   AESMOD<KEYLEN[1:0]>
  */
AES_KeyLength AES_GetKeyLength(void)
{
    uint32_t mod = TSB_AES->MOD;
    AES_KeyLength retval = AES_KEY_UNKNOWN_LENGTH;

    mod &= AES_MOD_KEYLEN_SET;

    switch (mod) {
    case AES_MOD_KEYLEN_128:
        retval = AES_KEY_LENGTH_128;
        break;
    case AES_MOD_KEYLEN_192:
        retval = AES_KEY_LENGTH_192;
        break;
    case AES_MOD_KEYLEN_256:
        retval = AES_KEY_LENGTH_256;
        break;
    default:
        /* Do nothing */
        break;
    }

    return retval;
}

/**
  * @brief  Set the algorithm mode.
  * @param  AlgorithmMode: Specify the algorithm mode.
  *   This parameter can be one of the following values:
  *   AES_ECB_MODE, AES_CBC_MODE, AES_CTR_MODE.
  * @retval The value returned can be one of the following values:
  *   SUCCESS or ERROR
  * @register The used register:
  *   AESMOD<ALGO[1:0]>
  */
Result AES_SetAlgorithmMode(AES_AlgorithmMode AlgorithmMode)
{
    Result retval = ERROR;

    /* Check the parameters */
    assert_param(IS_AES_ALGORITHM_MODE(AlgorithmMode));

    if (AES_GetArithmeticStatus() == AES_CALCULATION_COMPLETE) {
        TSB_AES->MOD &= AES_MOD_ALGO_CLEAR;

        switch (AlgorithmMode) {
        case AES_ECB_MODE:
            TSB_AES->MOD |= AES_MOD_ALGO_ECB;
            break;
        case AES_CBC_MODE:
            TSB_AES->MOD |= AES_MOD_ALGO_CBC;
            break;
        case AES_CTR_MODE:
            TSB_AES->MOD |= AES_MOD_ALGO_CTR;
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
  * @brief  Get the algorithm mode.
  * @param  None
  * @retval The algorithm mode.
  *   The value returned can be one of the following values:
  *   AES_ECB_MODE, AES_CBC_MODE, AES_CTR_MODE, AES_UNKNOWN_MODE.
  * @register The used register:
  *   AESMOD<ALGO[1:0]>
  */
AES_AlgorithmMode AES_GetAlgorithmMode(void)
{
    uint32_t mod = TSB_AES->MOD;
    AES_AlgorithmMode retval = AES_UNKNOWN_MODE;

    mod &= AES_MOD_ALGO_SET;

    switch (mod) {
    case AES_MOD_ALGO_ECB:
        retval = AES_ECB_MODE;
        break;
    case AES_MOD_ALGO_CBC:
        retval = AES_CBC_MODE;
        break;
    case AES_MOD_ALGO_CTR:
        retval = AES_CTR_MODE;
        break;
    default:
        /* Do nothing */
        break;
    }

    return retval;
}

/**
  * @brief  Get the arithmetic status.
  * @param  None
  * @retval The arithmetic status.
  *   The value returned can be one of the following values:
  *   AES_CALCULATION_COMPLETE, AES_CALCULATION_PROCESS.
  * @note  Do not write any value to AES registers when calculation is in process.
  * @register The used register:
  *   AESSTATUS<BUSY>
  */
AES_ArithmeticStatus AES_GetArithmeticStatus(void)
{
    uint32_t status = TSB_AES->STATUS;
    AES_ArithmeticStatus retval = AES_CALCULATION_COMPLETE;

    status &= AES_STATUS_BUSY_SET;

    if (status == AES_STATUS_BUSY_SET) {
        retval = AES_CALCULATION_PROCESS;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the writing FIFO status.
  * @param  None
  * @retval The writing FIFO status.
  *   The value returned can be one of the following values:
  *   AES_FIFO_NO_DATA, AES_FIFO_EXIST_DATA.
  * @register The used register:
  *   AESSTATUS<WFIFOST>
  */
AES_FIFOStatus AES_GetWFIFOStatus(void)
{
    uint32_t status = TSB_AES->STATUS;
    AES_FIFOStatus retval = AES_FIFO_NO_DATA;

    status &= AES_STATUS_WFIFOST_SET;

    if (status == AES_STATUS_WFIFOST_SET) {
        retval = AES_FIFO_EXIST_DATA;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Get the reading FIFO status.
  * @param  None
  * @retval The reading FIFO status.
  *   The value returned can be one of the following values:
  *   AES_FIFO_NO_DATA, AES_FIFO_EXIST_DATA.
  * @register The used register:
  *   AESSTATUS<RFIFOST>
  */
AES_FIFOStatus AES_GetRFIFOStatus(void)
{
    uint32_t status = TSB_AES->STATUS;
    AES_FIFOStatus retval = AES_FIFO_NO_DATA;

    status &= AES_STATUS_RFIFOST_SET;

    if (status == AES_STATUS_RFIFOST_SET) {
        retval = AES_FIFO_EXIST_DATA;
    } else {
        /* Do nothing */
    }

    return retval;
}

/**
  * @brief  Reset AES by peripheral function.
  * @param  None
  * @retval None
  * @register The used register:
  *   SRSTPROTECT
  *   SRSTIPRST<IPRST0>
  */
void AES_IPReset(void)
{
    volatile uint32_t iprst0 = 0U;
    volatile uint32_t protect = 0U;
    
    protect = TSB_SRST->PROTECT;

    /* Disable the access protection of SRSTIPRST register */
    TSB_SRST->PROTECT = SRST_PROTECT_DISABLE;

    TSB_SRST->IPRST |= INT_IPRST_IPRST_0_SET;

    /* Confirm SRSTIPRST<IPRST0> = 1 */
    do {
        iprst0 = TSB_SRST->IPRST & INT_IPRST_IPRST_0_SET;
    }
    while (iprst0 != INT_IPRST_IPRST_0_SET);

    /* Release reset state */
    TSB_SRST->IPRST &= INT_IPRST_IPRST_0_CLEAR;

    /* Return previous value to SRSTPROTECT register */
    TSB_SRST->PROTECT = protect;
}

/** @} */
/* End of group AES_Exported_Functions */

/** @} */
/* End of group AES */

/** @} */
/* End of group TX04_Periph_Driver */
#endif                          /* defined(__TMPM46B_AES_H) */
