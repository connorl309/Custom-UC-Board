/**
 *******************************************************************************
 * @file    aes.c
 * @brief   The application functions of AES_ECB demo for the TOSHIBA
 *          'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/02/27
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "aes.h"
/* Private define ------------------------------------------------------------*/
#define  TX_NUMBERS   12U
/* Private macro -------------------------------------------------------------*/
/* Reserve 1K RAM area for control data of DMAC unit C. */
/* Each channel use 4 word, 32 channels, primary and alternative */
/* So, unit C need: 4 x 32 x 2 = 256 word = 1024 bytes */
#if defined (  __ICCARM__  )    /* IAR EWARM */
/* uDMAC_CFG_C are defined in file TMPM46BF20XBG_Flash_For_uDMAC.icf */
uint32_t uDMAC_C_Control_Data[256U] @ ".uDMAC_CFG_C";
#elif defined ( __CC_ARM  )     /* Keil MDK */
#define uDMAC_CFG_C     (0x20000C00U)
uint32_t uDMAC_C_Control_Data[256U] __attribute__((at(uDMAC_CFG_C)));
#endif
/* external variables --------------------------------------------------------*/
extern uint32_t PlainText[3][4];
extern uint32_t EncryptedText[3][4];
extern uint32_t DecryptedText[3][4];
extern uint32_t EncryptionKey[6U];
extern uint32_t DecryptionKey[6U];
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the basic AES configuration.
  * @param  OperationMode: Select the operation mode
  *   This parameter can be one of the following values:
  *   AES_ENCRYPTION_MODE, AES_DECRYPTION_MODE.
  * @retval None
  */
void AES_Config(AES_OperationMode OperationMode)
{
    AES_InitTypeDef InitStruct = { AES_ENCRYPTION_MODE };

    /* Check the parameters */
    assert_param(IS_AES_OPERATION_MODE(OperationMode));

    /* Define the init structure */
    InitStruct.AlgorithmMode = AES_ECB_MODE;
    InitStruct.KeyLength = AES_KEY_LENGTH_192;
    if (OperationMode == AES_ENCRYPTION_MODE) {
        InitStruct.OperationMode = AES_ENCRYPTION_MODE;
    } else {
        InitStruct.OperationMode = AES_DECRYPTION_MODE;
    }
    
    /* Confirm calculation completion */
    while (AES_GetArithmeticStatus() != AES_CALCULATION_COMPLETE){}
	
    /* Clear the FIFO. */
    AES_ClrFIFO();
	
    if (OperationMode == AES_ENCRYPTION_MODE) {
        /* Set the encryption key data */
        AES_SetKey(AES_KEY_LENGTH_192, EncryptionKey);
    } else {
        /* Set the decryption key data */
        AES_SetKey(AES_KEY_LENGTH_192, DecryptionKey);
    }
    
    /* Initialize AES to ECB mode, 192-bit key length */
    AES_Init(&InitStruct);
}

/**
  * @brief  Initialize WFIFO DMA channel.
  * @param  OperationMode: Select the operation mode
  *   This parameter can be one of the following values:
  *   AES_ENCRYPTION_MODE, AES_DECRYPTION_MODE.
  * @retval None
  */
void AES_WDMAInit(AES_OperationMode OperationMode)
{
    DMAC_InitTypeDef init = { 0U };   
    uint32_t tmpAddr = 0U;

    /* Check the parameters */
    assert_param(IS_AES_OPERATION_MODE(OperationMode));
    
    DMAC_SetChannel(DMAC_UNIT_C, DMACC_AES_WRITE, ENABLE);
    DMAC_SetMask(DMAC_UNIT_C, DMACC_AES_WRITE, ENABLE);
    DMAC_SetPrimaryAlt(DMAC_UNIT_C, DMACC_AES_WRITE, DMAC_PRIMARY);
    DMAC_SetChannelPriority(DMAC_UNIT_C, DMACC_AES_WRITE, DMAC_PRIORITY_NORMAL);    
    
    DMAC_SetPrimaryBaseAddr(DMAC_UNIT_C, (uint32_t) & uDMAC_C_Control_Data);
    
    /* Set source and destination address according to operation mode */
    if (OperationMode == AES_ENCRYPTION_MODE) {
        /* Set the end address of source */
        tmpAddr = (uint32_t) & PlainText;
        init.SrcEndPointer = tmpAddr + ((TX_NUMBERS - 1U) * sizeof(PlainText[0U][0U]));
        /* Set the end address of destination */
        init.DstEndPointer = (uint32_t) & (TSB_AES->DT);
    } else {
        /* Set the end address of source */
        tmpAddr = (uint32_t) & EncryptedText;
        init.SrcEndPointer = tmpAddr + ((TX_NUMBERS - 1U) * sizeof(EncryptedText[0U][0U]));
        /* Set the end address of destination */
        init.DstEndPointer = (uint32_t) & (TSB_AES->DT);
    }
    
    init.Mode = DMAC_BASIC;
    init.NextUseBurst = DMAC_NEXT_NOT_USE_BURST;
    init.TxNum = TX_NUMBERS;
    init.ArbitrationMoment = DMAC_AFTER_4_TX;
    
    /* Now both src and dst use uint32_t type which is 4bytes long */
    init.SrcWidth = DMAC_WORD;
    init.SrcInc = DMAC_INC_4B;
    init.DstWidth = DMAC_WORD;
    init.DstInc = DMAC_INC_0B;
    
    /* Fill to 'control data' area after all members of structure is set */
    DMAC_FillInitData(DMAC_UNIT_C, DMACC_AES_WRITE, &init);

    /* Enable DMA unit C after all configuration is finished */
    DMAC_Enable(DMAC_UNIT_C);
}

/**
  * @brief  Initialize RFIFO DMA channel.
  * @param  OperationMode: Select the operation mode
  *   This parameter can be one of the following values:
  *   AES_ENCRYPTION_MODE, AES_DECRYPTION_MODE.
  * @retval None
  */
void AES_RDMAInit(AES_OperationMode OperationMode)
{
    DMAC_InitTypeDef init = { 0U };
    uint32_t tmpAddr = 0U;

    /* Check the parameters */
    assert_param(IS_AES_OPERATION_MODE(OperationMode));
    
    DMAC_SetChannel(DMAC_UNIT_C, DMACC_AES_READ, ENABLE);
    DMAC_SetMask(DMAC_UNIT_C, DMACC_AES_READ, ENABLE);
    DMAC_SetPrimaryAlt(DMAC_UNIT_C, DMACC_AES_READ, DMAC_PRIMARY);
    DMAC_SetChannelPriority(DMAC_UNIT_C, DMACC_AES_READ, DMAC_PRIORITY_NORMAL);

    DMAC_SetPrimaryBaseAddr(DMAC_UNIT_C, (uint32_t) & uDMAC_C_Control_Data);

    /* Set source and destination address according to operation mode */
    if (OperationMode == AES_ENCRYPTION_MODE) {
        /* Set the end address of source and source */
        init.SrcEndPointer = (uint32_t) & (TSB_AES->ODT);
        /* Set the end address of destination */
        tmpAddr = (uint32_t) & EncryptedText;
        init.DstEndPointer = tmpAddr + ((TX_NUMBERS - 1U) * sizeof(EncryptedText[0U][0U]));
    } else {
        /* Set the end address of source and source */
        init.SrcEndPointer = (uint32_t) & (TSB_AES->ODT);
        /* Set the end address of destination */
        tmpAddr = (uint32_t) & DecryptedText;
        init.DstEndPointer = tmpAddr + ((TX_NUMBERS - 1U) * sizeof(DecryptedText[0U][0U]));
    }
    
    init.Mode = DMAC_BASIC;
    
    init.NextUseBurst = DMAC_NEXT_NOT_USE_BURST;
    init.TxNum = TX_NUMBERS;
    init.ArbitrationMoment = DMAC_AFTER_4_TX;
    
    /* Now both src and dst use uint32_t type which is 4bytes long */
    init.SrcWidth = DMAC_WORD;
    init.SrcInc = DMAC_INC_0B;
    init.DstWidth = DMAC_WORD;
    init.DstInc = DMAC_INC_4B;
    
    /* fill to 'control data' area after all members of structure is set */
    DMAC_FillInitData(DMAC_UNIT_C, DMACC_AES_READ, &init);

    /* enable DMA unit B after all configuration is finished */
    DMAC_Enable(DMAC_UNIT_C);
}

/**
  * @brief  Compare the two two-dimensional arrays.
  * @param  PlainText: A two-dimensional array.
  * @param  DecryptedText: A two-dimensional array.
  * @param  Line: Array line.
  * @param  Row: Array row.
  * @retval Result: Compare result.
  *   The value returned can be one of the following values:
  *   SUCCESS: The two two-dimensional arrays are equal.
  *   ERROR: The two two-dimensional arrays are different.
  */
Result TextCompare(uint32_t PlainText[3][4], uint32_t DecryptedText[3][4], uint32_t Line, uint32_t Row)
{
    Result result = SUCCESS;
    uint32_t i = 0U;
    uint32_t j = 0U;

    for (i = 0U; i < Line; i++) {
        for (j = 0U; j < Row; j++){
            if (*(*(PlainText + i) + j) != *(*(DecryptedText + i) + j)) {
                result = ERROR;
                break;
            } else {
                /* Do nothing */
            }
        }
    }

    return result;
}

/*********************************** END OF FILE ******************************/
