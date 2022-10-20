/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of uDMAC demo for the 
 *          TOSHIBA 'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/02/13
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* This demo is to use uDMAC to transfer RAM data from "src" to "dst" */

#include "tmpm46b_udmac.h"
#include "stdbool.h"
#include "led.h"

/* Select DMA mode */
#define  DMA_DEMOMODE_BASIC
/* #define  DMA_DEMOMODE_AUTOMATIC */

/* Reserve 1K RAM area for control data of each DMAC unit. */
/* Each channel use 4 word, 32 channels, primary and alternative */
/* So, each unit need: 4 x 32 x 2 = 256 word = 1024 bytes */
#if defined (  __ICCARM__  )    /* IAR EWARM */

/* For TMPM46BF10 uDMAC_CFG_A/B are defined in file TMPM46BF10_Flash_For_uDMAC.icf */
uint32_t uDMAC_A_Control_Data[256U] @ ".uDMAC_CFG_A";
uint32_t uDMAC_B_Control_Data[256U] @ ".uDMAC_CFG_B";
#elif defined ( __CC_ARM  )     /* Keil MDK */
#include "TMPM46B.h"                    // Device header
#define uDMAC_CFG_A     (0x20000400U)
#define uDMAC_CFG_B     (uDMAC_CFG_A + 0x400U)
uint32_t uDMAC_A_Control_Data[256U] __attribute__((at(uDMAC_CFG_A)));
uint32_t uDMAC_B_Control_Data[256U] __attribute__((at(uDMAC_CFG_B)));
#endif

#define  TX_NUMBERS   256U
uint16_t src[TX_NUMBERS];
uint16_t dst[TX_NUMBERS];
uint32_t idx = 0U;

bool isSWTransferFinished(TSB_DMA_TypeDef * DMACx, uint8_t Channel);
Result Buffercompare(const uint16_t * Src, const uint16_t * Dst, uint32_t Len);

volatile Result dmaResult = ERROR;

/**
  * @brief  The main function of uDMAC demo
  * @param  None
  * @retval None
  */
int main(void)
{
    DMAC_InitTypeDef init = { 0U };
    uint32_t tmpAddr = 0U;
    bool transferState = true;
       
    /* Initialize LEDs on M46B board before display something */
    LED_Init();
     
    DMACA_SetTransferType(DMACA_DMAREQA, DMAC_BURST);
    DMAC_SetChannel(DMAC_UNIT_A, DMACA_DMAREQA, ENABLE);
    DMAC_SetMask(DMAC_UNIT_A, DMACA_DMAREQA, ENABLE);
    DMAC_SetPrimaryAlt(DMAC_UNIT_A, DMACA_DMAREQA, DMAC_PRIMARY);
    DMAC_SetChannelPriority(DMAC_UNIT_A, DMACA_DMAREQA, DMAC_PRIORITY_NORMAL);

    DMAC_SetPrimaryBaseAddr(DMAC_UNIT_A, (uint32_t) & uDMAC_A_Control_Data);

    for (idx = 0U; idx < TX_NUMBERS; idx++) {
        src[idx] = idx;
    }

    /* Set the end address of source and destination */
    tmpAddr = (uint32_t) & src;
    init.SrcEndPointer = tmpAddr + ((TX_NUMBERS - 1U) * sizeof(src[0U]));
    tmpAddr = (uint32_t) & dst;
    init.DstEndPointer = tmpAddr + ((TX_NUMBERS - 1U) * sizeof(dst[0U]));

#if defined(DMA_DEMOMODE_BASIC )
    init.Mode = DMAC_BASIC;
#elif defined(DMA_DEMOMODE_AUTOMATIC)
    init.Mode = DMAC_AUTOMATIC;
#endif

    init.NextUseBurst = DMAC_NEXT_NOT_USE_BURST;
    init.TxNum = TX_NUMBERS;
    init.ArbitrationMoment = DMAC_AFTER_32_TX;

    /* Now both src and dst use uint16_t type which is 2bytes long */
    init.SrcWidth = DMAC_HALF_WORD;
    init.SrcInc = DMAC_INC_2B;
    init.DstWidth = DMAC_HALF_WORD;
    init.DstInc = DMAC_INC_2B;

    /* Fill to 'control data' area after all members of structure is set */
    DMAC_FillInitData(DMAC_UNIT_A, DMACA_DMAREQA, &init);

    /* Enable DMA unitA after all configuration is finished */
    DMAC_Enable(DMAC_UNIT_A);

    do {
        /* Because of "init.Mode = DMAC_BASIC" above, here need to trigger it until transfer is finished, */
        /* If DMAC_AUTOMATIC is used, only need to trigger it once */
        DMAC_SetSWReq(DMAC_UNIT_A, DMACA_DMAREQA);

        transferState = isSWTransferFinished(DMAC_UNIT_A, DMACA_DMAREQA);

    } while (transferState == false);

    dmaResult = DMAC_GetBusErrState(DMAC_UNIT_A);

    /* Now DMA is finished */
    /* After function Buffercompare() is called, dmaResult == SUCCESS */
    dmaResult = ERROR;
    dmaResult = Buffercompare(src, dst, TX_NUMBERS);

    if  ( dmaResult  == SUCCESS ) {
          LED_On(LED0);
          LED_On(LED1);
    } else {
          LED_On(LED2);
          LED_On(LED3);
    }
    
    while (1U);

}

/**
  * @brief  To compare two half word buffer
  * @param  Src : Pointer to point source buffer 
  * @param  Dst : Pointer to point destination buffer   
  * @param  Len : How many data will be compared 
  * @retval SUCCESS: Two buffer contain same data
            ERROR: Two buffer contain different data  
  */
Result Buffercompare(const uint16_t * Src, const uint16_t * Dst, uint32_t Len)
{
    uint32_t tmp = 0U;
    Result result = SUCCESS;

    for (tmp = 0U; tmp < Len; tmp++) {
        if (Src[tmp] != Dst[tmp]) {
            result = ERROR;
            break;
        } else {
            /* Do nothing */
        }
    }

    return result;
}

/**
  * @brief  Check if DMA transfer by software trigger is finished.
  * @param  DMACx: Select DMA Unit.
  *   This parameter can be one of the following values:
  *   DMAC_UNIT_A :  DMAC unit unit A
  *   DMAC_UNIT_B :  DMAC unit unit B
  *   DMAC_UNIT_C :  DMAC unit unit C
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
  * @retval 
  *   false: Transfer is not finished
  *   true: Transfer is finished
  */
bool isSWTransferFinished(TSB_DMA_TypeDef * DMACx, uint8_t Channel)
{
    DMAC_PrimaryAlt PriAlt = DMAC_PRIMARY;
    uint32_t Addr = 0U;
    uint32_t tmpCtrl = 0U;
    bool ret = false;

    assert_param(IS_DMAC_UNIT(DMACx));
    assert_param(IS_DMAC_CHANNEL_ALL(DMACx, Channel));

    PriAlt = DMAC_GetPrimaryAlt(DMACx, Channel);

    if (PriAlt == DMAC_PRIMARY) {
        Addr = DMAC_GetBaseAddr(DMACx, DMAC_PRIMARY);
    } else {
        Addr = DMAC_GetBaseAddr(DMACx, DMAC_ALTERNATE);
    }

    /* Add offset for channel, each channel use 4 words RAM */
    Addr += (16U * (uint32_t) Channel);

    /* Get 'control data' */
    tmpCtrl = *((uint32_t *) (Addr + 8U));

    /* Low 3bits is 'cycle_ctrl', it becomes 0 when transfer is finished */
    if (tmpCtrl & 0x07U) {
        /* Do nothing */
    } else {
        ret = true;
    }

    return ret;
}


#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif
