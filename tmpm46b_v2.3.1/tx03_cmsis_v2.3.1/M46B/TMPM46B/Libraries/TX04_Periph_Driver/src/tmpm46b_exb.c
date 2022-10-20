/**
 *******************************************************************************
 * @file    tmpm46b_exb.c
 * @brief   This file provides API functions for EXB driver.
 * @version V2.0.2.1
 * @date    2015/02/05
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_exb.h"

#if defined(__TMPM46B_EXB_H)
/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @defgroup EXB 
  * @brief EXB driver modules
  * @{
  */
/** @defgroup EXB_Private_Defines
  * @{
  */
#define MODE_EXBWAIT_MASK    ((uint32_t)0x00000001)
#define EXB_CS_MASK          ((uint32_t)0x00000001)
#define EXB_AS_FIXED_BITS    ((uint32_t)0x60000000)
#define CSX_CSW_CLEAR        ((uint32_t)0xFFFFFFF1)

/** @} */
/* End of group EXB_Private_Defines */

/** @defgroup EXB_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group EXB_Private_FunctionPrototypes */

/** @defgroup EXB_Private_Functions
  * @{
  */

/** @} */
/* End of group group EXB_Private_Functions */

/** @defgroup EXB_Exported_Functions
  * @{
  */

/**
  * @brief  Set EXB bus mode
  * @param  BusMode: Select EXB mode.
  *   This parameter can be: EXB_BUS_MULTIPLEX.
  * @retval None
  */
void EXB_SetBusMode(uint8_t BusMode)
{
    /* Check the parameters */
    assert_param(IS_EXB_BUS_MODE(BusMode));

    /* Set EXBMOD<EXBSEL> to select bus mode. */
    if (BusMode == EXB_BUS_MULTIPLEX) {
        TSB_EXB_MOD_EXBSEL = 0U;
    } else {
        /* Do nothing */
    }
}

/**
  * @brief  Set the setup, wait and recovery of the bus cycle to be double or quadruple
  * @param  Cycle: Set the bus cycle to be double or quadruple.
  *   This parameter can be:
  *   EXB_CYCLE_NONE, EXB_CYCLE_DOUBLE or EXB_CYCLE_QUADRUPLE
  * @retval None
  */
void EXB_SetBusCycleExtension(uint8_t Cycle)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_EXB_BUS_CYCLE_EXTENSION(Cycle));

    tmp = TSB_EXB->MOD;
    tmp &= MODE_EXBWAIT_MASK;
    tmp |= (uint32_t) Cycle;
    /* Set EXBMOD<EXBWAIT1:0> to set bus cycle extension. */
    TSB_EXB->MOD = tmp;
}

/**
  * @brief  Enable the specified chip
  * @param  ChipSelect: Select Chip
  *   This parameter can be one of the following values:
  *   EXB_CS0, EXB_CS1,EXB_CS2, EXB_CS3
  * @retval None
  */
void EXB_Enable(uint8_t ChipSelect)
{
    /* Check the parameters */
    assert_param(IS_EXB_CHIP_SELECT(ChipSelect));

    switch (ChipSelect) {
    case EXB_CS0:
        TSB_EXB_CS0_CSW0 = 1U;
        break;

    case EXB_CS1:
        TSB_EXB_CS1_CSW0 = 1U;
        break;

    case EXB_CS2:
        TSB_EXB_CS2_CSW0 = 1U;
        break;

    case EXB_CS3:
        TSB_EXB_CS3_CSW0 = 1U;
        break;

    default:
        /* Do nothing */
        break;
    }
}

/**
  * @brief  Disable the specified chip
  * @param  ChipSelect: Select Chip
  *   This parameter can be one of the following values:
  *   EXB_CS0, EXB_CS1,EXB_CS2, EXB_CS3
  * @retval None
  */
void EXB_Disable(uint8_t ChipSelect)
{
    /* Check the parameters */
    assert_param(IS_EXB_CHIP_SELECT(ChipSelect));

    switch (ChipSelect) {
    case EXB_CS0:
        TSB_EXB_CS0_CSW0 = 0U;
        break;

    case EXB_CS1:
        TSB_EXB_CS1_CSW0 = 0U;
        break;

    case EXB_CS2:
        TSB_EXB_CS2_CSW0 = 0U;
        break;

    case EXB_CS3:
        TSB_EXB_CS3_CSW0 = 0U;
        break;

    default:
        /* Do nothing */
        break;
    }
}

/**
  * @brief  Initialize the specified chip
  * @param  ChipSelect: Select Chip
  *   This parameter can be one of the following values:
  *   EXB_CS0, EXB_CS1,EXB_CS2, EXB_CS3
  * @param  InitStruct: The structure containing basic EXB configuration.
  *   This parameter is structure pointer which consists of following members:
  *   AddrSpaceSize, StartAddr, BusWidth and Cycles
  * @retval None
  */
void EXB_Init(uint8_t ChipSelect, EXB_InitTypeDef * InitStruct)
{
    uint32_t tmp_AS = 0U;
    uint32_t tmp_CS = 0U;

    /* Check the parameters */
    assert_param(IS_EXB_CHIP_SELECT(ChipSelect));
    assert_param(IS_POINTER_NOT_NULL(InitStruct));
    assert_param(IS_EXB_ADDR_SPACE_SIZE(InitStruct->AddrSpaceSize));
    assert_param(IS_EXB_DATA_BUS_WIDTH(InitStruct->BusWidth));
    assert_param(IS_EXB_INTERNAL_WAIT(InitStruct->Cycles.InternalWait));
    assert_param(IS_EXB_RW_SETUP_CYCLE(InitStruct->Cycles.ReadSetupCycle));
    assert_param(IS_EXB_RW_SETUP_CYCLE(InitStruct->Cycles.WriteSetupCycle));
    assert_param(IS_EXB_ALE_WAIT_CYCLE(InitStruct->Cycles.ALEWaitCycle));
    assert_param(IS_EXB_RW_RECOVERY_CYCLE(InitStruct->Cycles.ReadRecoveryCycle));
    assert_param(IS_EXB_RW_RECOVERY_CYCLE(InitStruct->Cycles.WriteRecoveryCycle));
    assert_param(IS_EXB_CS_RECOVERY_CYCLE(InitStruct->Cycles.ChipSelectRecoveryCycle));

    /* Initialize EXB ASx */
    tmp_AS = (uint32_t) InitStruct->AddrSpaceSize | ((uint32_t) InitStruct->StartAddr << 16U);
    tmp_AS |= EXB_AS_FIXED_BITS;

    /* Initialize EXB CSx */
    tmp_CS = ((uint32_t) InitStruct->Cycles.InternalWait << 8U) |
        ((uint32_t) InitStruct->Cycles.ReadRecoveryCycle << 24U) |
        ((uint32_t) InitStruct->Cycles.WriteRecoveryCycle << 27U);
    tmp_CS |= (InitStruct->Cycles.ReadSetupCycle == EXB_CYCLE_4) ?
        ((uint32_t) (InitStruct->Cycles.ReadSetupCycle - 1UL) << 16U) :
        ((uint32_t) InitStruct->Cycles.ReadSetupCycle << 16U);
    tmp_CS |= (InitStruct->Cycles.WriteSetupCycle == EXB_CYCLE_4) ?
        ((uint32_t) (InitStruct->Cycles.WriteSetupCycle - 1UL) << 18U) :
        ((uint32_t) InitStruct->Cycles.WriteSetupCycle << 18U);

    if (TSB_EXB_MOD_EXBSEL == 0U) {
        /* Set ALE wait cycle for multiplex bus */
        tmp_CS |= (InitStruct->Cycles.ALEWaitCycle == EXB_CYCLE_4) ?
            ((uint32_t) (InitStruct->Cycles.ALEWaitCycle - 1UL) << 20U) :
            ((uint32_t) InitStruct->Cycles.ALEWaitCycle << 20U);
    } else {
        /* Do nothing */
    }

    tmp_CS |= (InitStruct->Cycles.ChipSelectRecoveryCycle == EXB_CYCLE_4) ?
        ((uint32_t) (InitStruct->Cycles.ChipSelectRecoveryCycle - 1UL) << 30U) :
        ((uint32_t) InitStruct->Cycles.ChipSelectRecoveryCycle << 30U);
    tmp_CS |= (uint32_t) InitStruct->BusWidth;

    switch (ChipSelect) {
    case EXB_CS0:
        TSB_EXB->AS0 = tmp_AS;
        TSB_EXB->CS0 = tmp_CS;
        break;

    case EXB_CS1:
        TSB_EXB->AS1 = tmp_AS;
        TSB_EXB->CS1 = tmp_CS;
        break;

    case EXB_CS2:
        TSB_EXB->AS2 = tmp_AS;
        TSB_EXB->CS2 = tmp_CS;
        break;

    case EXB_CS3:
        TSB_EXB->AS3 = tmp_AS;
        TSB_EXB->CS3 = tmp_CS;
        break;

    default:
        /* Do nothing */
        break;
    }
}

/** @} */
/* End of group EXB_Exported_Functions */

/** @} */
/* End of group EXB */

/** @} */
/* End of group TX04_Periph_Driver */
#endif                          /* defined(__TMPM46B_EXB_H) */
