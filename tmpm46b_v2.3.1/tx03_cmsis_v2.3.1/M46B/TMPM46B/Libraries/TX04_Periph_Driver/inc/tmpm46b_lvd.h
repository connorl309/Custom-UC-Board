/**
 *******************************************************************************
 * @file    tmpm46b_lvd.h
 * @brief   This file provides all the functions prototypes for LVD driver. 
 * @version V2.0.2.1
 * @date    2015/02/25
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_LVD_H
#define __TMPM46B_LVD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM46B.h"
#include "tx04_common.h"

/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @addtogroup LVD
  * @{
  */

/** @defgroup LVD_Exported_Types
  * @{
  */
    typedef enum {
        LVD_VD_UPPER = 0U,
        LVD_VD_LOWER = 1U
    } LVD_VDStatus;

/** @} */
/* End of group LVD_Exported_Types */

/** @defgroup LVD_Exported_Constants
  * @{
  */

#define LVD_VDLVL_280                   ((uint32_t)0x00000000)
#define LVD_VDLVL_285                   ((uint32_t)0x00000002)
#define LVD_VDLVL_290                   ((uint32_t)0x00000004)
#define LVD_VDLVL_295                   ((uint32_t)0x00000006)
#define LVD_VDLVL_300                   ((uint32_t)0x00000008)
#define LVD_VDLVL_305                   ((uint32_t)0x0000000A)
#define LVD_VDLVL_310                   ((uint32_t)0x0000000C)
#define LVD_VDLVL_315                   ((uint32_t)0x0000000E)
#define IS_LVD_VD_LEVEL(param)         (((param) == LVD_VDLVL_280) || \
                                         ((param) == LVD_VDLVL_285) || \
                                         ((param) == LVD_VDLVL_290) || \
                                         ((param) == LVD_VDLVL_295) || \
                                         ((param) == LVD_VDLVL_300) || \
                                         ((param) == LVD_VDLVL_305) || \
                                         ((param) == LVD_VDLVL_300) || \
                                         ((param) == LVD_VDLVL_310) || \
                                         ((param) == LVD_VDLVL_315))


/** @} */
/* End of LVD_Exported_Constants */

/** @defgroup LVD_Exported_FunctionPrototypes
  * @{
  */

    void LVD_EnableVD(void);
    void LVD_DisableVD(void);
    void LVD_SetVDLevel(uint32_t VDLevel);
    LVD_VDStatus LVD_GetVDStatus(void);
    void LVD_SetVDResetOutput(FunctionalState NewState);
    void LVD_SetVDINTOutput(FunctionalState NewState);

/** @} */
/* End of LVD_Exported_FunctionPrototypes */

/** @} */
/* End of group LVD */

/** @} */
/* End of group TX04_Periph_Driver */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM46B_LVD_H */
