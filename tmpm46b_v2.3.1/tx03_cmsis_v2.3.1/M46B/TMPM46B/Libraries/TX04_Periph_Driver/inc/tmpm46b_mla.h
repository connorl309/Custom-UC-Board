/**
 *******************************************************************************
 * @file    tmpm46b_mla.h
 * @brief   This file provides all the functions prototypes for MLA driver.
 * @version V2.0.2.1
 * @date    2015/02/28
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_MLA_H
#define __TMPM46B_MLA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b.h"
#include "tx04_common.h"

/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @addtogroup MLA
  * @{
  */

/** @defgroup MLA_Exported_Constants
  * @{
  */

/** @} */
/* End of MLA_Exported_Constants */

/** @defgroup MLA_Exported_Types 
  * @{
  */

#define MLA_BLK_0                      ((uint8_t)0x00)
#define MLA_BLK_1                      ((uint8_t)0x01)
#define MLA_BLK_2                      ((uint8_t)0x02)
#define MLA_BLK_3                      ((uint8_t)0x03)
#define MLA_BLK_4                      ((uint8_t)0x04)
#define MLA_BLK_5                      ((uint8_t)0x05)
#define MLA_BLK_6                      ((uint8_t)0x06)
#define MLA_BLK_7                      ((uint8_t)0x07)
#define MLA_BLK_8                      ((uint8_t)0x08)
#define MLA_BLK_9                      ((uint8_t)0x09)
#define MLA_BLK_10                     ((uint8_t)0x0A)
#define MLA_BLK_11                     ((uint8_t)0x0B)
#define MLA_BLK_12                     ((uint8_t)0x0C)
#define MLA_BLK_13                     ((uint8_t)0x0D)
#define MLA_BLK_14                     ((uint8_t)0x0E)
#define MLA_BLK_15                     ((uint8_t)0x0F)
#define MLA_BLK_16                     ((uint8_t)0x10)
#define MLA_BLK_17                     ((uint8_t)0x11)
#define MLA_BLK_18                     ((uint8_t)0x12)
#define MLA_BLK_19                     ((uint8_t)0x13)
#define MLA_BLK_20                     ((uint8_t)0x14)
#define MLA_BLK_21                     ((uint8_t)0x15)
#define MLA_BLK_22                     ((uint8_t)0x16)
#define MLA_BLK_23                     ((uint8_t)0x17)
#define MLA_BLK_24                     ((uint8_t)0x18)
#define MLA_BLK_25                     ((uint8_t)0x19)
#define MLA_BLK_26                     ((uint8_t)0x1A)
#define MLA_BLK_27                     ((uint8_t)0x1B)
#define MLA_BLK_28                     ((uint8_t)0x1C)
#define MLA_BLK_29                     ((uint8_t)0x1D)
#define MLA_BLK_30                     ((uint8_t)0x1E)
#define MLA_BLK_31                     ((uint8_t)0x1F)
#define IS_MLA_BLK_NUM(param)          ((param) <= MLA_BLK_31)

#define MLA_COM_MODE_MUL               ((uint32_t)0x01000000)
#define MLA_COM_MODE_ADD               ((uint32_t)0x02000000)
#define MLA_COM_MODE_SUB               ((uint32_t)0x04000000)
#define IS_MLA_COM_MODE(param)      (((param) == MLA_COM_MODE_MUL) || \
                                     ((param) == MLA_COM_MODE_ADD) || \
                                     ((param) == MLA_COM_MODE_SUB))

    typedef enum {
        MLA_CALCULATION_STOP = 0U,
        MLA_CALCULATION_PROGRESS = 1U
    } MLA_CalculationStatus;

    typedef enum {
        MLA_CARRYBORROW_NO = 0U,
        MLA_CARRYBORROW_OCCURS = 1U
    } MLA_CarryBorrowFlag;

    typedef enum {
        MLA_CalculationMode_MUL = 0U,
        MLA_CalculationMode_ADD = 1U,
        MLA_CalculationMode_SUB = 2U,
        MLA_CalculationMode_UNKNOWN = 3U
    } MLA_CalculationMode;

#define IS_MLA_CalculationMode(param)           (((param) == MLA_CalculationMode_MUL) || \
                                                 ((param) == MLA_CalculationMode_ADD) || \
                                                 ((param) == MLA_CalculationMode_SUB))
/** @} */
/* End of MLA_Exported_types */

/** @defgroup MLA_Exported_FunctionPrototypes
  * @{
  */

    void MLA_SetCalculationMode(uint32_t CalculationMode);
    MLA_CalculationMode MLA_GetCalculationMode(void);
    void MLA_SetADataBlkNum(uint8_t BlkNum);
    uint8_t MLA_GetADataBlkNum(void);
    void MLA_SetBDataBlkNum(uint8_t BlkNum);
    uint8_t MLA_GetBDataBlkNum(void);
    void MLA_SetWDataBlkNum(uint8_t BlkNum);
    uint8_t MLA_GetWDataBlkNum(void);
    MLA_CarryBorrowFlag MLA_GetCarryBorrowFlag(void);
    MLA_CalculationStatus MLA_GetCalculationStatus(void);
    Result MLA_SetMontgomeryParameter(uint32_t Data);
    uint32_t MLA_GetMontgomeryParameter(void);
    Result MLA_WriteDataBlkNum(uint8_t BlkNum, uint32_t Data[8U]);
    void MLA_ReadDataBlkNum(uint8_t BlkNum, uint32_t Data[8U]);
    void MLA_IPReset(void);

/** @} */
/* End of MLA_Exported_FunctionPrototypes */

/** @} */
/* End of group MLA */

/** @} */
/* End of group TX04_Periph_Driver */

#ifdef __cplusplus
}
#endif
#endif                          /* __TMPM46B_MLA_H */
