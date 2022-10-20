/**
 *******************************************************************************
 * @file    tmpm46b_udmac.c
 * @brief   This file provides API functions for uDMAC driver.
 * @version V2.0.2.1
 * @date    2015/02/11
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_udmac.h"

#if defined(__TMPM46B_uDMAC_H)
/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @defgroup uDMAC
  * @brief uDMAC driver modules
  * @{
  */

/** @defgroup uDMAC_Private_Defines
  * @{
  */

/** @} */
/* End of group uDMAC_Private_Defines */

/** @defgroup uDMAC_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group uDMAC_Private_FunctionPrototypes */

/** @defgroup uDMAC_Private_Functions
  * @{
  */

/** @} */
/* End of group uDMAC_Private_Functions */

/** @defgroup uDMAC_Exported_Functions
  * @{
  */

/**
  * @brief  Get the state of specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @retval The state of DMAC operation.
  *   This parameter can be one of the following values:
  *   DISABLE :  The DMAC unit is disabled.
  *   ENABLE  :  The DMAC unit is enabled.
  */
FunctionalState DMAC_GetDMACState(TSB_DMA_TypeDef * DMACx)
{
    FunctionalState state = DISABLE;

    assert_param(IS_DMAC_UNIT(DMACx));

    /* Read DMAxStatus<master_enable> */
    if ((DMACx->STATUS & 0x00000001U) == 0x00000001U) {
        state = ENABLE;
    } else {
        state = DISABLE;
    }
    
    return state;
}

/**
  * @brief  Enable the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @retval None
  */
void DMAC_Enable(TSB_DMA_TypeDef * DMACx)
{
    assert_param(IS_DMAC_UNIT(DMACx));

    /* Set DMAxCfg<master_enable> */
    DMACx->CFG = 0x00000001U;
}

/**
  * @brief  Disable the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @retval None
  */
void DMAC_Disable(TSB_DMA_TypeDef * DMACx)
{
    assert_param(IS_DMAC_UNIT(DMACx));

    /* Clear DMAxCfg<master_enable> */
    DMACx->CFG = 0x00000000U;
}

/** 
  * @brief  Set the base address of the primary data of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Addr: The base address of the primary data, bit0 to bit9 must be 0.
  * @retval None
  */
void DMAC_SetPrimaryBaseAddr(TSB_DMA_TypeDef * DMACx, uint32_t Addr)
{
    assert_param(IS_DMAC_UNIT(DMACx));
    assert_param(IS_DMAC_CTRL_BASE(Addr));

    DMACx->CTRLBASEPTR = Addr;
}

/**
  * @brief  Get the primary/alternative base address of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  PriAlt: Select base address type.
  *   This parameter can be one of the following values:
  *   DMAC_PRIMARY :  Get primary base address
  *   DMAC_ALTERNATE: Get alternative base address
  * @retval The base address of primary/alternative data.
  */
uint32_t DMAC_GetBaseAddr(TSB_DMA_TypeDef * DMACx, DMAC_PrimaryAlt PriAlt)
{
    uint32_t tmp = 0U;

    assert_param(IS_DMAC_UNIT(DMACx));
    assert_param(IS_DMAC_PRIMARYALT(PriAlt));

    if (PriAlt == DMAC_PRIMARY) {
        tmp = DMACx->CTRLBASEPTR;
    } else {
        tmp = DMACx->ALTCTRLBASEPTR;
    }

    return tmp;
}

/**
  * @brief  Set software transfer request to the specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC   
  * @retval None
  */
void DMAC_SetSWReq(TSB_DMA_TypeDef * DMACx, uint8_t Channel)
{
    uint32_t tmp = 0U;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));

    /* Set DMAxChnlSwRequest<chnl_sw_request> to requests a transfer */
    tmp = DMACx->CHNLSWREQUEST;
    tmp |= (0x01UL << ((uint32_t) Channel));
    DMACx->CHNLSWREQUEST = tmp;
}

/**
  * @brief  Set transfer type to the specified channel of DMAC UNITA.
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   when Type == DMAC_BURST:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA  
  *
  *   when Type == DMAC_SINGLE:
  *   DMACA_UART0_RX, DMACA_UART0_TX,
  *   DMACA_UART1_RX, DMACA_UART1_TX
  *
  * @param  Type: Select transfer type
  *   This parameter can be one of the following values:
  *   DMAC_BURST  : Single transfer is disabled, only burst transfer request can be used.
  *   DMAC_SINGLE : Single transfer is enabled.
  * @retval None.
  */
void DMACA_SetTransferType(uint8_t Channel, DMAC_TransferType Type)
{
    uint32_t tmp = 0U;

    assert_param(IS_DMACA_CHANNEL_ALL(Channel));
    assert_param(IS_DMAC_TRANSFERTYPE(Type));

    if (Type == DMAC_BURST) {
        /* Set DMAxChnlUseburstSet<chnl_useburst_set> to disable the single,
           transfer to the channel, and only burst transfer request is valid */
        tmp = DMAC_UNIT_A->CHNLUSEBURSTSET;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMAC_UNIT_A->CHNLUSEBURSTSET = tmp;
    } else {
        assert_param(IS_DMACA_CHANNEL_SINGLE(Channel));
        /* Set DMAxChnlUseburstClr<chnl_useburst_clr> to enable the single,
           transfer to the corresponding channel */
        tmp = DMAC_UNIT_A->CHNLUSEBURSTCLR;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMAC_UNIT_A->CHNLUSEBURSTCLR = tmp;
    }
}

/**
  * @brief  Get transfer type setting for the specified channel of the DMAC UNITA.
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  * @retval The transfer type.
  *   DMAC_BURST  : Only burst transfer request can be used.
  *   DMAC_SINGLE : Single transfer is enabled.
  */
DMAC_TransferType DMACA_GetTransferType(uint8_t Channel)
{
    uint32_t tmp = 0U;
    DMAC_TransferType Type = DMAC_SINGLE;

    assert_param(IS_DMACA_CHANNEL_ALL(Channel));

    tmp = DMAC_UNIT_A->CHNLUSEBURSTSET & (0x01UL << ((uint32_t) Channel));
    if (tmp != 0U) {
        /* Read DMAxChnlUseburstSet<chnl_useburst_set >, Only burst transfer request can be used */
        Type = DMAC_BURST;
    } else {
        Type = DMAC_SINGLE;
    }
    
    return Type;
}

/**
  * @brief  Set transfer type to the specified channel of DMAC UNITB.
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   when Type == DMAC_BURST:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,         DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,         DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,         DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,        DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,        DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,        DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,        DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,        DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,           DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,           DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB  
  *  
  *   when Type == DMAC_SINGLE:
  *   DMACB_SSP0_RX, DMACB_SSP0_TX,
  *   DMACB_SSP1_RX, DMACB_SSP1_TX,
  *   DMACB_SSP2_RX, DMACB_SSP2_TX,
  *
  * @param  Type: Select transfer type
  *   This parameter can be one of the following values:
  *   DMAC_BURST  : Single transfer is disabled, only burst transfer request can be used.
  *   DMAC_SINGLE : Single transfer is enabled.
  * @retval None.
  */
void DMACB_SetTransferType(uint8_t Channel, DMAC_TransferType Type)
{
    uint32_t tmp = 0U;

    assert_param(IS_DMACB_CHANNEL_ALL(Channel));
    assert_param(IS_DMAC_TRANSFERTYPE(Type));

    if (Type == DMAC_BURST) {
        /* Set DMAxChnlUseburstSet<chnl_useburst_set> to disable the single,
           transfer to the channel, and only burst transfer request is valid */
        tmp = DMAC_UNIT_B->CHNLUSEBURSTSET;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMAC_UNIT_B->CHNLUSEBURSTSET = tmp;
    } else {
        assert_param(IS_DMACB_CHANNEL_SINGLE(Channel));
        /* Set DMAxChnlUseburstClr<chnl_useburst_clr> to enable the single,
           transfer to the corresponding channel */
        tmp = DMAC_UNIT_B->CHNLUSEBURSTCLR;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMAC_UNIT_B->CHNLUSEBURSTCLR = tmp;
    }
}

/**
  * @brief  Get transfer type setting for the specified channel of the DMAC UNITB.
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   DMACB_SNFC_GIE1,         DMACB_SNFC_GIE2,         DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,         DMACB_SNFC_GIE5,         DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,         DMACB_SNFC_GIE8,         DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,        DMACB_SNFC_GID13,        DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,        DMACB_SNFC_GID16,        DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,        DMACB_SNFC_GID21,        DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,        DMACB_SNFC_GID24,        DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,        DMACB_SNFC_GID27,        DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,    DMACB_SSP0_RX,           DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,           DMACB_SSP1_TX,           DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,           DMACB_DMAREQB 
  * @retval The transfer type.
  *   DMAC_BURST  : Only burst transfer request can be used.
  *   DMAC_SINGLE : Single transfer is enabled.
  */
DMAC_TransferType DMACB_GetTransferType(uint8_t Channel)
{
    uint32_t tmp = 0U;
    DMAC_TransferType Type = DMAC_SINGLE;

    assert_param(IS_DMACB_CHANNEL_ALL(Channel));

    tmp = DMAC_UNIT_B->CHNLUSEBURSTSET & (0x01UL << ((uint32_t) Channel));
    if (tmp != 0U) {
        /* Read DMAxChnlUseburstSet<chnl_useburst_set >, Only burst transfer request can be used */
        Type = DMAC_BURST;
    } else {
        Type = DMAC_SINGLE;
    }
    
    return Type;
}

/**
  * @brief  Set mask for the specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC   
  * @param  NewState: Clear or set the mask to enable or disable the DMA channel
  *   This parameter can be one of the following values:
  *   ENABLE  : The DMA channel mask is cleared, DMA request is enable(valid)
  *   DISABLE : The DMA channel is masked, DMA request is disable(invalid)
  * @retval None
  */
void DMAC_SetMask(TSB_DMA_TypeDef * DMACx, uint8_t Channel, FunctionalState NewState)
{
    uint32_t tmp = 0U;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set DMAxChnlReqMaskClr<chnl_req_mask_clr>, clear mask to enable DMA channel,(valid) */
        tmp = DMACx->CHNLREQMASKCLR;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMACx->CHNLREQMASKCLR = tmp;
    } else {
        /* Set DMAxChnlReqMaskSet<chnl_req_mask_set>, set mask to disable DMA channel,(invalid) */
        tmp = DMACx->CHNLREQMASKSET;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMACx->CHNLREQMASKSET = tmp;
    }
}

/**
  * @brief  Get mask setting for the specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC   
  * @retval The inverted mask setting.
  *   ENABLE  : The DMA channel mask is cleared, DMA request is enable(valid)
  *   DISABLE : The DMA channel is masked, DMA request is disable(invalid)
  */
FunctionalState DMAC_GetMask(TSB_DMA_TypeDef * DMACx, uint8_t Channel)
{
    uint32_t tmp = 0U;
    FunctionalState state = DISABLE;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));

    /* Read DMAxChnlReqMaskSet<chnl_req_mask_set> */
    tmp = DMACx->CHNLREQMASKSET & (uint32_t) (0x01UL << ((uint32_t) Channel));
    if (tmp != 0U) {                  
        state = DISABLE;
    } else {                    
        state = ENABLE;
    }

    return state;
}

/**
  * @brief  Enable or disable the specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC   
  * @param  NewState: Enable or disable the DMA channel
  *   This parameter can be one of the following values:
  *   ENABLE  : The DMA channel will be enabled
  *   DISABLE : The DMA channel will be disabled
  * @retval None
  */
void DMAC_SetChannel(TSB_DMA_TypeDef * DMACx, uint8_t Channel, FunctionalState NewState)
{
    uint32_t tmp = 0U;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        /* Set DMAxChnlEnableSet<chnl_enable_set> */
        tmp = DMACx->CHNLENABLESET;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMACx->CHNLENABLESET = tmp;
    } else {
        /* Set DMAxChnlEnableClr<chnl_enable_clr> */
        tmp = DMACx->CHNLENABLECLR;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMACx->CHNLENABLECLR = tmp;
    }
}

/**
  * @brief  Get the enable/disable setting for specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC   
  * @retval  The enable/disable setting for channel
  *   ENABLE  : The DMA channel is enabled
  *   DISABLE : The DMA channel is disabled  
  */
FunctionalState DMAC_GetChannelState(TSB_DMA_TypeDef * DMACx, uint8_t Channel)
{
    uint32_t tmp = 0U;
    FunctionalState state = DISABLE;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));

    /* Read DMAxChnlEnableSet<chnl_enable_set> */
    tmp = DMACx->CHNLENABLESET & (uint32_t) (0x01UL << ((uint32_t) Channel));
    if (tmp != 0U) {                  
        state = ENABLE;
    } else {                    
        state = DISABLE;
    }
    
    return state;
}

/**
  * @brief  Set to use primary data or alternative data for specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC   
  * @param  PriAlt: Select primary data or alternative data for channel specified by 'Channel' above
  *   This parameter can be one of the following values:
  *   DMAC_PRIMARY   : Channel will use primary data
  *   DMAC_ALTERNATE : Channel will use alternative data
  * @retval None
  */
void DMAC_SetPrimaryAlt(TSB_DMA_TypeDef * DMACx, uint8_t Channel, DMAC_PrimaryAlt PriAlt)
{
    uint32_t tmp = 0U;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));
    assert_param(IS_DMAC_PRIMARYALT(PriAlt));

    if (PriAlt == DMAC_PRIMARY) {
        /* PRIMARY: Set DMAxChnlPriAltClr<chnl_pri_alt_clr> to clear */
        tmp = DMACx->CHNLPRIALTCLR;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMACx->CHNLPRIALTCLR = tmp;
    } else {
        /* ALTERNATE: Set DMAxChnlPriAltSet<chnl_pri_alt_set> */
        tmp = DMACx->CHNLPRIALTSET;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMACx->CHNLPRIALTSET = tmp;
    }
}

/**
  * @brief  Get the setting of the using of primary data or alternative data for specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC   
  * @retval The setting of the using of primary data or alternative data
  *   DMAC_PRIMARY   : Channel is using primary data 
  *   DMAC_ALTERNATE : Channel is using alternative data
  */
DMAC_PrimaryAlt DMAC_GetPrimaryAlt(TSB_DMA_TypeDef * DMACx, uint8_t Channel)
{
    uint32_t tmp = 0U;
    DMAC_PrimaryAlt PriAlt = DMAC_PRIMARY;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));

    /* Read DMAxChnlPriAltSet<chnl_pri_alt_set> */
    tmp = DMACx->CHNLPRIALTSET & (uint32_t) (0x01UL << (uint32_t) Channel);
    if (tmp != 0U) {                  
        PriAlt = DMAC_ALTERNATE;
    } else {                    
        PriAlt = DMAC_PRIMARY;
    }
    
    return PriAlt;
}

/**
  * @brief  Set the priority for specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC   
  * @param  Priority: Select Priority.
  *   This parameter can be one of the following values:
  *   DMAC_PRIORITY_NORMAL : Normal priority
  *   DMAC_PRIORITY_HIGH   : High priority
  * @retval None
  */
void DMAC_SetChannelPriority(TSB_DMA_TypeDef * DMACx, uint8_t Channel, DMAC_Priority Priority)
{
    uint32_t tmp = 0U;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));
    assert_param(IS_DMAC_PRIORITY(Priority));

    if (Priority == DMAC_PRIORITY_NORMAL) {
        /* DMAC_PRIORITY_NORMAL: Set DMAxChnlPriorityClr<chnl_priority_clr> to clear */
        tmp = DMACx->CHNLPRIORITYCLR;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMACx->CHNLPRIORITYCLR = tmp;
    } else {
        /* DMAC_PRIORITY_HIGH: Set DMAxChnlPrioritySet<chnl_priority_set> */
        tmp = DMACx->CHNLPRIORITYSET;
        tmp |= (0x01UL << ((uint32_t) Channel));
        DMACx->CHNLPRIORITYSET = tmp;
    }
}

/**
  * @brief  Get the priority setting for specified channel of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC      
  * @retval  The priority setting of channel
  *   DMAC_PRIORITY_NORMAL : Normal priority
  *   DMAC_PRIORITY_HIGH   : High priority
  */
DMAC_Priority DMAC_GetChannelPriority(TSB_DMA_TypeDef * DMACx, uint8_t Channel)
{
    uint32_t tmp = 0U;
    DMAC_Priority Priority = DMAC_PRIORITY_NORMAL;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));

    /* Read DMAxChnlPrioritySet<chnl_priority_set> */
    tmp = DMACx->CHNLPRIORITYSET & (uint32_t) (0x01UL << (uint32_t) Channel);
    if (tmp != 0U) {                  
        Priority = DMAC_PRIORITY_HIGH;
    } else {                    
        Priority = DMAC_PRIORITY_NORMAL;
    }
    
    return Priority;
}

/**
  * @brief  Clear the bus error of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @retval None
  */
void DMAC_ClearBusErr(TSB_DMA_TypeDef * DMACx)
{
    assert_param(IS_DMAC_UNIT(DMACx));

    /* Set DMAxErrClr<err_clr> */
    DMACx->ERRCLR = 0x00000001U;
}

/**
  * @brief  Get the bus error state of the specified DMAC unit.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @retval The bus error state
  *   SUCCESS :  No bus error
  *   ERROR   :  There is error in bus
  */
Result DMAC_GetBusErrState(TSB_DMA_TypeDef * DMACx)
{
    Result tmp = SUCCESS;
    
    assert_param(IS_DMAC_UNIT(DMACx));
    
    /* Read DMAxErrClr<err_clr> */
    if ((DMACx->ERRCLR & 0x00000001U) == 0x00000001U) {
        tmp = ERROR;
    } else {
        /* Do nothing */
    }
    
    return tmp;
}

/**
  * @brief  Fill the DMA setting data of specified channel of the specified DMAC unit to RAM.
  * @param  DMACx: Select DMAC unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A, DMAC_UNIT_B, DMAC_UNIT_C
  * @param  Channel: Select channel.
  *   This parameter can be one of the following values:
  *   For DMAC_UNIT_A:
  *   DMACA_SNFC_PRD11,         DMACA_SNFC_PRD12,         DMACA_SNFC_PRD21,                   
  *   DMACA_SNFC_PRD22,         DMACA_ADC_COMPLETION,     DMACA_UART0_RX,  
  *   DMACA_UART0_TX,           DMACA_UART1_RX,           DMACA_UART1_TX,                     
  *   DMACA_SIO0_UART0_RX,      DMACA_SIO0_UART0_TX,      DMACA_SIO1_UART1_RX,                
  *   DMACA_SIO1_UART1_TX,      DMACA_SIO2_UART2_RX,      DMACA_SIO2_UART2_TX,                             
  *   DMACA_SIO3_UART3_RX,      DMACA_SIO3_UART3_TX,      DMACA_TMRB0_CMP_MATCH,
  *   DMACA_TMRB1_CMP_MATCH,    DMACA_TMRB2_CMP_MATCH,    DMACA_TMRB3_CMP_MATCH,
  *   DMACA_TMRB4_CMP_MATCH,    DMACA_TMRB5_CMP_MATCH,    DMACA_TMRB6_CMP_MATCH,
  *   DMACA_TMRB7_CMP_MATCH,    DMACA_TMRB0_INPUT_CAP0,   DMACA_TMRB0_INPUT_CAP1,
  *   DMACA_TMRB1_INPUT_CAP0,   DMACA_TMRB1_INPUT_CAP1,   DMACA_TMRB2_INPUT_CAP0,
  *   DMACA_TMRB2_INPUT_CAP1,   DMACA_DMAREQA    
  *
  *   For DMAC_UNIT_B:
  *   DMACB_SNFC_GIE1,          DMACB_SNFC_GIE2,          DMACB_SNFC_GIE3,  
  *   DMACB_SNFC_GIE4,          DMACB_SNFC_GIE5,          DMACB_SNFC_GIE6,  
  *   DMACB_SNFC_GIE7,          DMACB_SNFC_GIE8,          DMACB_SNFC_GID11, 
  *   DMACB_SNFC_GID12,         DMACB_SNFC_GID13,         DMACB_SNFC_GID14, 
  *   DMACB_SNFC_GID15,         DMACB_SNFC_GID16,         DMACB_SNFC_GID17, 
  *   DMACB_SNFC_GID18,         DMACB_SNFC_GID21,         DMACB_SNFC_GID22, 
  *   DMACB_SNFC_GID23,         DMACB_SNFC_GID24,         DMACB_SNFC_GID25, 
  *   DMACB_SNFC_GID26,         DMACB_SNFC_GID27,         DMACB_SNFC_GID28, 
  *   DMACB_ADC_COMPLETION,     DMACB_SSP0_RX,            DMACB_SSP0_TX,    
  *   DMACB_SSP1_RX,            DMACB_SSP1_TX,            DMACB_SSP2_RX,    
  *   DMACB_SSP2_TX,            DMACB_DMAREQB   
  *
  *   For DMAC_UNIT_C:
  *   DMACC_SNFC_RD1,           DMACC_SNFC_RD2,           DMACC_SNFC_RD3,           
  *   DMACC_SNFC_RD4,           DMACC_SNFC_RD5,           DMACC_SNFC_RD6,           
  *   DMACC_SNFC_RD7,           DMACC_SNFC_RD8,           DMACC_AES_READ,           
  *   DMACC_AES_WRITE,          DMACC_SHA_WRITE,          DMACC_DMA_COMPLETION,     
  *   DMACC_I2C0_TX_RX,         DMACC_I2C1_TX_RX,         DMACC_I2C2_TX_RX,        
  *   DMACC_MTP0_CMP_MATCH0,    DMACC_MTP0_CMP_MATCH1,    DMACC_MTP1_CMP_MATCH0,    
  *   DMACC_MTP1_CMP_MATCH1,    DMACC_MTP2_CMP_MATCH0,    DMACC_MTP2_CMP_MATCH1,    
  *   DMACC_MTP3_CMP_MATCH0,    DMACC_MTP3_CMP_MATCH1,    DMACC_TMRB3_INPUT_CAP0,   
  *   DMACC_TMRB3_INPUT_CAP1,   DMACC_TMRB4_INPUT_CAP0,   DMACC_TMRB4_INPUT_CAP1,   
  *   DMACC_TMRB5_INPUT_CAP0,   DMACC_TMRB5_INPUT_CAP1,   DMACC_TMRB6_INPUT_CAP0,   
  *   DMACC_TMRB6_INPUT_CAP1,   DMACC_DMAREQC            
  * @param  InitStruct: The structure contain the DMA setting values.
  * @retval None
  */
void DMAC_FillInitData(TSB_DMA_TypeDef * DMACx, uint8_t Channel, DMAC_InitTypeDef * InitStruct)
{
    DMAC_PrimaryAlt PriAlt = DMAC_PRIMARY;
    uint32_t Addr = 0U;
    uint32_t tmpCtrl = 0U;

    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));

    assert_param(IS_POINTER_NOT_NULL(InitStruct));

    assert_param(IS_DMAC_CYCLECTRL(InitStruct->Mode));
    assert_param(IS_DMAC_NEXT_USEBURST(InitStruct->NextUseBurst));
    assert_param(IS_DMAC_TXNUM(InitStruct->TxNum));
    assert_param(IS_DMAC_ARBITRATION(InitStruct->ArbitrationMoment));
    assert_param(IS_DMAC_BIT_WIDTH(InitStruct->SrcWidth));
    assert_param(IS_DMAC_INCWIDTH(InitStruct->SrcInc));
    assert_param(IS_DMAC_BIT_WIDTH(InitStruct->DstWidth));
    assert_param(IS_DMAC_INCWIDTH(InitStruct->DstInc));

    assert_param(IS_DMAC_INCWIDTH_VALID
                 ((uint32_t) InitStruct->SrcWidth, (uint32_t) InitStruct->SrcInc));
    assert_param(IS_DMAC_INCWIDTH_VALID
                 ((uint32_t) InitStruct->DstWidth, (uint32_t) InitStruct->DstInc));

    PriAlt = DMAC_GetPrimaryAlt(DMACx, Channel);

    if (PriAlt == DMAC_PRIMARY) {
        Addr = DMAC_GetBaseAddr(DMACx, DMAC_PRIMARY);
    } else {
        Addr = DMAC_GetBaseAddr(DMACx, DMAC_ALTERNATE);
    }

    /* Add offset for channel, each channel use (4 x uint32_t) RAM */
    Addr += (16U * (uint32_t) Channel);

    /* Make setting data for 'control data' */
    tmpCtrl |= (uint32_t) InitStruct->Mode;
    tmpCtrl |= ((uint32_t) InitStruct->NextUseBurst << 3U);
    tmpCtrl |= ((uint32_t) (InitStruct->TxNum - 1U) << 4U);
    tmpCtrl |= ((uint32_t) InitStruct->ArbitrationMoment << 14U);
    tmpCtrl |= ((uint32_t) InitStruct->SrcWidth << 24U);
    tmpCtrl |= ((uint32_t) InitStruct->SrcInc << 26U);
    tmpCtrl |= ((uint32_t) InitStruct->DstWidth << 28U);
    tmpCtrl |= ((uint32_t) InitStruct->DstInc << 30U);

    /* Write setting data to right address */
    *((uint32_t *) (Addr)) = InitStruct->SrcEndPointer;
    Addr += 4U;
    *((uint32_t *) (Addr)) = InitStruct->DstEndPointer;
    Addr += 4U;
    *((uint32_t *) (Addr)) = tmpCtrl;
    Addr += 4U;
    *((uint32_t *) (Addr)) = (uint32_t) 0U;
}

/**
  * @brief  Get the DMA factor flag of the DMAC UNITA.
  * @param  None
  * @retval A union with DMA factor flag of DMAC UNITA.
  */
DMACA_Flag DMACA_GetINTFlag(void)
{
    DMACA_Flag flag = { 0U };
    flag.All = TSB_DMAIF->FLGA;
    return flag;
}

/**
  * @brief  Get the DMA factor flag of the DMAC UNITB.
  * @param  None
  * @retval A union with DMA factor flag of DMAC UNITB.
  */
DMACB_Flag DMACB_GetINTFlag(void)
{
    DMACB_Flag flag = { 0U };
    flag.All = TSB_DMAIF->FLGB;
    return flag;
}

/**
  * @brief  Get the DMA factor flag of the DMAC UNITC.
  * @param  None
  * @retval A union with DMA factor flag of DMAC UNITC.
  */
DMACC_Flag DMACC_GetINTFlag(void)
{
    DMACC_Flag flag = { 0U };
    flag.All = TSB_DMAIF->FLGC;
    return flag;
}

/** @} */
/* End of group uDMAC_Exported_Functions */

/** @} */
/* End of group uDMAC */

/** @} */
/* End of group TX04_Periph_Driver */

#endif                          /* defined(__TMPM46B_uDMAC_H) */
