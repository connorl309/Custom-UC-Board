/**
 *******************************************************************************
 * @file    tmpm46b_sha.h
 * @brief   This file provides all the functions prototypes for SHA driver.
 * @version V2.0.2.1
 * @date    2015/02/29
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_SHA_H
#define __TMPM46B_SHA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM46B.h"
#include "tx04_common.h"

/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @addtogroup SHA
  * @{
  */

/** @defgroup SHA_Exported_Constants
  * @{
  */

/** @} */
/* End of SHA_Exported_Constants */

/** @defgroup SHA_Exported_Types 
  * @{
  */

    typedef enum {
        SHA_START = 0U,
        SHA_STOP = 1U
    } SHA_RunCmd;

#define IS_SHA_RUN_CMD(param)                   (((param) == SHA_START) || \
                                                 ((param) == SHA_STOP))

    typedef enum {
        SHA_INT_LAST_CALCULATION = 0U,
        SHA_INT_EACH_CALCULATION = 1U
    } SHA_CalculationInt;

#define IS_SHA_CALCULATION_INT(param)           (((param) == SHA_INT_LAST_CALCULATION) || \
                                                 ((param) == SHA_INT_EACH_CALCULATION))

    typedef enum {
        SHA_INIT_VALUE_PREVIOUS = 0U,
        SHA_INIT_VALUE_REG = 1U,
        SHA_INIT_VALUE_256_BIT = 2U,
        SHA_INIT_VALUE_224_BIT = 3U,
        SHA_INIT_VALUE_UNKNOWN = 4U
    } SHA_InitMode;

#define IS_SHA_INIT_MODE(param)                 (((param) == SHA_INIT_VALUE_PREVIOUS) || \
                                                 ((param) == SHA_INIT_VALUE_REG) || \
                                                 ((param) == SHA_INIT_VALUE_256_BIT) || \
                                                 ((param) == SHA_INIT_VALUE_224_BIT))

    typedef enum {
        SHA_CALCULATION_COMPLETE = 0U,
        SHA_CALCULATION_PROCESS = 1U
    } SHA_CalculationStatus;

/** @} */
/* End of SHA_Exported_types */

/** @defgroup SHA_Exported_FunctionPrototypes
  * @{
  */

    Result SHA_SetRunState(SHA_RunCmd Cmd);
    Result SHA_SetCalculationInt(SHA_CalculationInt CalculationInt);
    Result SHA_SetInitMode(SHA_InitMode InitMode);
    Result SHA_SetInitValue(uint32_t INIT[8U]);
    Result SHA_SetDMAState(FunctionalState DMATransfer);
    FunctionalState SHA_GetDMAState(void);
    Result SHA_SetMsgLen(uint32_t MSGLEN[2U]);
    Result SHA_SetRmnMsgLen(uint32_t REMAIN[2U]);
    void SHA_GetRmnMsgLen(uint32_t RmnMsgLen[2U]);
    Result SHA_SetMessage(uint32_t MSG[16U]);
    void SHA_GetResult(uint32_t HashRes[8U]);
    SHA_CalculationStatus SHA_GetCalculationStatus(void);
    void SHA_IPReset(void);

/** @} */
/* End of SHA_Exported_FunctionPrototypes */

/** @} */
/* End of group SHA */

/** @} */
/* End of group TX04_Periph_Driver */

#ifdef __cplusplus
}
#endif
#endif                          /* __TMPM46B_SHA_H */
