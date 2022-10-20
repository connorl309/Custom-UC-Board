/**
 *******************************************************************************
 * @file    tmpm46b_aes.h
 * @brief   This file provides all the functions prototypes for AES driver.
 * @version V2.0.2.1
 * @date    2015/02/29
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_AES_H
#define __TMPM46B_AES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM46B.h"
#include "tx04_common.h"

/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @addtogroup AES
  * @{
  */

/** @defgroup AES_Exported_Constants
  * @{
  */

/** @} */
/* End of AES_Exported_Constants */

/** @defgroup AES_Exported_Types 
  * @{
  */

#define AES_KEY_NUM_0                           ((uint32_t)0x00000000)
#define AES_KEY_NUM_1                           ((uint32_t)0x00000001)
#define AES_KEY_NUM_2                           ((uint32_t)0x00000002)
#define AES_KEY_NUM_3                           ((uint32_t)0x00000003)
#define AES_KEY_NUM_4                           ((uint32_t)0x00000004)
#define AES_KEY_NUM_5                           ((uint32_t)0x00000005)
#define AES_KEY_NUM_6                           ((uint32_t)0x00000006)
#define AES_KEY_NUM_7                           ((uint32_t)0x00000007)

#define IS_AES_KEY_NUM(param)                   ((param) <= AES_KEY_NUM_7)

    typedef enum {
        AES_ECB_MODE = 0U,
        AES_CBC_MODE = 1U,
        AES_CTR_MODE = 2U,
        AES_UNKNOWN_MODE = 3U
    } AES_AlgorithmMode;

#define IS_AES_ALGORITHM_MODE(param)            (((param) == AES_ECB_MODE) || \
                                                 ((param) == AES_CBC_MODE) || \
                                                 ((param) == AES_CTR_MODE))

    typedef enum {
        AES_KEY_LENGTH_128 = 0U,
        AES_KEY_LENGTH_192 = 1U,
        AES_KEY_LENGTH_256 = 2U,
        AES_KEY_UNKNOWN_LENGTH = 3U
    } AES_KeyLength;

#define IS_AES_KEY_LENGTH(param)                (((param) == AES_KEY_LENGTH_128) || \
                                                 ((param) == AES_KEY_LENGTH_192) || \
                                                 ((param) == AES_KEY_LENGTH_256))

    typedef enum {
        AES_ENCRYPTION_MODE = 0U,
        AES_DECRYPTION_MODE = 1U
    } AES_OperationMode;

#define IS_AES_OPERATION_MODE(param)            (((param) == AES_ENCRYPTION_MODE) || \
                                                 ((param) == AES_DECRYPTION_MODE))

    typedef enum {
        AES_CALCULATION_COMPLETE = 0U,
        AES_CALCULATION_PROCESS = 1U
    } AES_ArithmeticStatus;

    typedef enum {
        AES_FIFO_NO_DATA = 0U,
        AES_FIFO_EXIST_DATA = 1U
    } AES_FIFOStatus;

/** @} */
/* End of AES_Exported_types */

/** @addtogroup AES_Exported_Types
  * @{
  */

/**
  * @brief AES Init Structure definition
  */
    typedef struct {
        AES_OperationMode OperationMode;        /*!< Set AES operation to encryption or decryption */
        AES_KeyLength KeyLength;                /*!< Set key length */
        AES_AlgorithmMode AlgorithmMode;        /*!< Set algorithm mode */
    } AES_InitTypeDef;

/** @} */
/* End of group AES_Exported_Types */

/** @defgroup AES_Exported_FunctionPrototypes
  * @{
  */

    Result AES_SetData(uint32_t Data);
    uint32_t AES_GetResult(void);
    Result AES_SetKey(AES_KeyLength KeyLength, uint32_t Key[]);
    uint32_t AES_GetKey(uint32_t KeyNum);
    Result AES_SetCntInit(uint32_t CNT[4U]);
    Result AES_SetVectorInit(uint32_t IV[4U]);
    Result AES_ClrFIFO(void);
    void AES_Init(AES_InitTypeDef * InitStruct);
    Result AES_SetOperationMode(AES_OperationMode OperationMode);
    AES_OperationMode AES_GetOperationMode(void);
    Result AES_SetDMAState(FunctionalState DMATransfer);
    FunctionalState AES_GetDMAState(void);
    Result AES_SetKeyLength(AES_KeyLength KeyLength);
    AES_KeyLength AES_GetKeyLength(void);
    Result AES_SetAlgorithmMode(AES_AlgorithmMode AlgorithmMode);
    AES_AlgorithmMode AES_GetAlgorithmMode(void);
    AES_ArithmeticStatus AES_GetArithmeticStatus(void);
    AES_FIFOStatus AES_GetWFIFOStatus(void);
    AES_FIFOStatus AES_GetRFIFOStatus(void);
    void AES_IPReset(void);

/** @} */
/* End of AES_Exported_FunctionPrototypes */

/** @} */
/* End of group AES */

/** @} */
/* End of group TX04_Periph_Driver */

#ifdef __cplusplus
}
#endif
#endif                          /* __TMPM46B_AES_H */
