/**
 *******************************************************************************
 * @file    tmpm46b_exb.h
 * @brief   This file provides all the functions prototypes for EXB driver.
 * @version V2.0.2.1
 * @date   2015/02/05
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_EXB_H
#define __TMPM46B_EXB_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM46B.h"
#include "tx04_common.h"

/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @addtogroup EXB
  * @{
  */

/** @addtogroup EXB_Exported_types
  * @{
  */

#define EXB_BUS_MULTIPLEX       ((uint8_t)0x00)
#define IS_EXB_BUS_MODE(param)  (((param) == EXB_BUS_MULTIPLEX))

#define EXB_CYCLE_NONE                 ((uint8_t)0x00)
#define EXB_CYCLE_DOUBLE               ((uint8_t)0x02)
#define EXB_CYCLE_QUADRUPLE            ((uint8_t)0x04)
#define IS_EXB_BUS_CYCLE_EXTENSION(param)  (((param) == EXB_CYCLE_NONE)   || \
                                            ((param) == EXB_CYCLE_DOUBLE) || \
                                            ((param) == EXB_CYCLE_QUADRUPLE))

#define EXB_16M_BYTE              ((uint8_t)0x00)
#define EXB_8M_BYTE               ((uint8_t)0x01)
#define EXB_4M_BYTE               ((uint8_t)0x02)
#define EXB_2M_BYTE               ((uint8_t)0x03)
#define EXB_1M_BYTE               ((uint8_t)0x04)
#define EXB_512K_BYTE             ((uint8_t)0x05)
#define EXB_256K_BYTE             ((uint8_t)0x06)
#define EXB_128K_BYTE             ((uint8_t)0x07)
#define EXB_64K_BYTE              ((uint8_t)0x08)
#define IS_EXB_ADDR_SPACE_SIZE(param) ((param) < 0x09U)

#define EXB_BUS_WIDTH_BIT_8              ((uint8_t)0x00)
#define EXB_BUS_WIDTH_BIT_16             ((uint8_t)0x02)
#define IS_EXB_DATA_BUS_WIDTH(param)     (((param) == EXB_BUS_WIDTH_BIT_8) || \
                                          ((param) == EXB_BUS_WIDTH_BIT_16))

#define EXB_INTERNAL_WAIT_0             ((uint8_t)0x00)
#define EXB_INTERNAL_WAIT_1             ((uint8_t)0x01)
#define EXB_INTERNAL_WAIT_2             ((uint8_t)0x02)
#define EXB_INTERNAL_WAIT_3             ((uint8_t)0x03)
#define EXB_INTERNAL_WAIT_4             ((uint8_t)0x04)
#define EXB_INTERNAL_WAIT_5             ((uint8_t)0x05)
#define EXB_INTERNAL_WAIT_6             ((uint8_t)0x06)
#define EXB_INTERNAL_WAIT_7             ((uint8_t)0x07)
#define EXB_INTERNAL_WAIT_8             ((uint8_t)0x08)
#define EXB_INTERNAL_WAIT_9             ((uint8_t)0x09)
#define EXB_INTERNAL_WAIT_10            ((uint8_t)0x0A)
#define EXB_INTERNAL_WAIT_11            ((uint8_t)0x0B)
#define EXB_INTERNAL_WAIT_12            ((uint8_t)0x0C)
#define EXB_INTERNAL_WAIT_13            ((uint8_t)0x0D)
#define EXB_INTERNAL_WAIT_14            ((uint8_t)0x0E)
#define EXB_INTERNAL_WAIT_15            ((uint8_t)0x0F)
#define IS_EXB_INTERNAL_WAIT(param)     ((param) <= EXB_INTERNAL_WAIT_15)

#define EXB_CYCLE_0              ((uint8_t)0x00)
#define EXB_CYCLE_1              ((uint8_t)0x01)
#define EXB_CYCLE_2              ((uint8_t)0x02)
#define EXB_CYCLE_3              ((uint8_t)0x03)
#define EXB_CYCLE_4              ((uint8_t)0x04)
#define EXB_CYCLE_5              ((uint8_t)0x05)
#define EXB_CYCLE_6              ((uint8_t)0x06)
#define EXB_CYCLE_8              ((uint8_t)0x07)

#define IS_EXB_RW_SETUP_CYCLE(param)  (((param) <= EXB_CYCLE_2) || ((param) == EXB_CYCLE_4))

#define IS_EXB_ALE_WAIT_CYCLE(param)  (((param) <= EXB_CYCLE_2) || ((param) == EXB_CYCLE_4))
                                  
#define IS_EXB_RW_RECOVERY_CYCLE(param)  ((param) <= EXB_CYCLE_8)

#define IS_EXB_CS_RECOVERY_CYCLE(param)  (((param) <= EXB_CYCLE_2) || ((param) == EXB_CYCLE_4))

#define EXB_CS0              ((uint8_t)0x00)
#define EXB_CS1              ((uint8_t)0x01)
#define EXB_CS2              ((uint8_t)0x02)
#define EXB_CS3              ((uint8_t)0x03)

#define IS_EXB_CHIP_SELECT(param)  (((param) == EXB_CS0) || \
                                    ((param) == EXB_CS1) || \
                                    ((param) == EXB_CS2) || \
                                    ((param) == EXB_CS3))
    typedef struct {
        uint8_t InternalWait;
        uint8_t ReadSetupCycle;
        uint8_t WriteSetupCycle;
        uint8_t ALEWaitCycle;
        uint8_t ReadRecoveryCycle;
        uint8_t WriteRecoveryCycle;
        uint8_t ChipSelectRecoveryCycle;
    } EXB_CyclesTypeDef;

    typedef struct {
        uint8_t AddrSpaceSize;
        uint8_t StartAddr;
        uint8_t BusWidth;
        EXB_CyclesTypeDef Cycles;
    } EXB_InitTypeDef;

/** @} */
/* End of group EXB_Exported_types */

/** @defgroup EXB_Exported_FunctionPrototypes
  * @{
  */

    void EXB_SetBusMode(uint8_t BusMode);
    void EXB_SetBusCycleExtension(uint8_t Cycle);
    void EXB_Enable(uint8_t ChipSelect);
    void EXB_Disable(uint8_t ChipSelect);
    void EXB_Init(uint8_t ChipSelect, EXB_InitTypeDef * InitStruct);

/** @} */
/* End of group EXB_Exported_FunctionPrototypes */

/** @} */
/* End of group EXB */

/** @} */
/* End of group TX04_Periph_Driver */

#ifdef __cplusplus
}
#endif
#endif                          /*__TMPM46B_EXB_H */
