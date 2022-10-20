/**
 *******************************************************************************
 * @file    tmpm46b_udmac.h
 * @brief   This file provides all the functions prototypes for uDMAC driver.
 * @version V2.0.2.1
 * @date    2015/02/11
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TMPM46B_uDMAC_H
#define __TMPM46B_uDMAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "TMPM46B.h"
#include "TX04_common.h"

/** @addtogroup TX04_Periph_Driver
  * @{
  */

/** @addtogroup uDMAC
  * @{
  */

/** @defgroup uDMAC_Exported_Constants
  * @{
  */
#define DMAC_UNIT_A  TSB_DMAA   /* redefine the name in m46b.h */
#define DMAC_UNIT_B  TSB_DMAB
#define DMAC_UNIT_C  TSB_DMAC
#define IS_DMAC_UNIT(param)              (((param) == DMAC_UNIT_A) || \
                                          ((param) == DMAC_UNIT_B) || \
                                          ((param) == DMAC_UNIT_C))

/** @} */
/* End of group uDMAC_Exported_Constants */

/** @defgroup uDMAC_Exported_Types
  * @{
  */

/*-------------------------DMACA  channels----------------------------------*/
#define DMACA_SNFC_PRD11                   ((uint8_t)0x00)
#define DMACA_SNFC_PRD12                   ((uint8_t)0x01)
#define DMACA_SNFC_PRD21                   ((uint8_t)0x02)
#define DMACA_SNFC_PRD22                   ((uint8_t)0x03)
#define DMACA_ADC_COMPLETION               ((uint8_t)0x04)
#define DMACA_UART0_RX                     ((uint8_t)0x05)
#define DMACA_UART0_TX                     ((uint8_t)0x06)
#define DMACA_UART1_RX                     ((uint8_t)0x07)
#define DMACA_UART1_TX                     ((uint8_t)0x08)
#define DMACA_SIO0_UART0_RX                ((uint8_t)0x09)
#define DMACA_SIO0_UART0_TX                ((uint8_t)0x0A)
#define DMACA_SIO1_UART1_RX                ((uint8_t)0x0B)
#define DMACA_SIO1_UART1_TX                ((uint8_t)0x0C)
#define DMACA_SIO2_UART2_RX                ((uint8_t)0x0D)
#define DMACA_SIO2_UART2_TX                ((uint8_t)0x0E)
#define DMACA_SIO3_UART3_RX                ((uint8_t)0x0F)
#define DMACA_SIO3_UART3_TX                ((uint8_t)0x10)
#define DMACA_TMRB0_CMP_MATCH              ((uint8_t)0x11)
#define DMACA_TMRB1_CMP_MATCH              ((uint8_t)0x12)
#define DMACA_TMRB2_CMP_MATCH              ((uint8_t)0x13)
#define DMACA_TMRB3_CMP_MATCH              ((uint8_t)0x14)
#define DMACA_TMRB4_CMP_MATCH              ((uint8_t)0x15)
#define DMACA_TMRB5_CMP_MATCH              ((uint8_t)0x16)
#define DMACA_TMRB6_CMP_MATCH              ((uint8_t)0x17)
#define DMACA_TMRB7_CMP_MATCH              ((uint8_t)0x18)
#define DMACA_TMRB0_INPUT_CAP0             ((uint8_t)0x19)
#define DMACA_TMRB0_INPUT_CAP1             ((uint8_t)0x1A)
#define DMACA_TMRB1_INPUT_CAP0             ((uint8_t)0x1B)
#define DMACA_TMRB1_INPUT_CAP1             ((uint8_t)0x1C)
#define DMACA_TMRB2_INPUT_CAP0             ((uint8_t)0x1D)
#define DMACA_TMRB2_INPUT_CAP1             ((uint8_t)0x1E)
#define DMACA_DMAREQA                      ((uint8_t)0x1F)
#define IS_DMACA_CHANNEL_ALL(param)        ((param) <= DMACA_DMAREQA)
#define IS_DMACA_CHANNEL_SINGLE(param)    (((param) >= DMACA_UART0_RX) && ((param) <= DMACA_UART1_TX))

/*-------------------------DMACB  channels----------------------------------*/
#define DMACB_SNFC_GIE1                    ((uint8_t)0x00)
#define DMACB_SNFC_GIE2                    ((uint8_t)0x01)
#define DMACB_SNFC_GIE3                    ((uint8_t)0x02)
#define DMACB_SNFC_GIE4                    ((uint8_t)0x03)
#define DMACB_SNFC_GIE5                    ((uint8_t)0x04)
#define DMACB_SNFC_GIE6                    ((uint8_t)0x05)
#define DMACB_SNFC_GIE7                    ((uint8_t)0x06)
#define DMACB_SNFC_GIE8                    ((uint8_t)0x07)
#define DMACB_SNFC_GID11                   ((uint8_t)0x08)
#define DMACB_SNFC_GID12                   ((uint8_t)0x09)
#define DMACB_SNFC_GID13                   ((uint8_t)0x0A)
#define DMACB_SNFC_GID14                   ((uint8_t)0x0B)
#define DMACB_SNFC_GID15                   ((uint8_t)0x0C)
#define DMACB_SNFC_GID16                   ((uint8_t)0x0D)
#define DMACB_SNFC_GID17                   ((uint8_t)0x0E)
#define DMACB_SNFC_GID18                   ((uint8_t)0x0F)
#define DMACB_SNFC_GID21                   ((uint8_t)0x10)
#define DMACB_SNFC_GID22                   ((uint8_t)0x11)
#define DMACB_SNFC_GID23                   ((uint8_t)0x12)
#define DMACB_SNFC_GID24                   ((uint8_t)0x13)
#define DMACB_SNFC_GID25                   ((uint8_t)0x14)
#define DMACB_SNFC_GID26                   ((uint8_t)0x15)
#define DMACB_SNFC_GID27                   ((uint8_t)0x16)
#define DMACB_SNFC_GID28                   ((uint8_t)0x17)
#define DMACB_ADC_COMPLETION               ((uint8_t)0x18)
#define DMACB_SSP0_RX                      ((uint8_t)0x19)
#define DMACB_SSP0_TX                      ((uint8_t)0x1A)
#define DMACB_SSP1_RX                      ((uint8_t)0x1B)
#define DMACB_SSP1_TX                      ((uint8_t)0x1C)
#define DMACB_SSP2_RX                      ((uint8_t)0x1D)
#define DMACB_SSP2_TX                      ((uint8_t)0x1E)
#define DMACB_DMAREQB                      ((uint8_t)0x1F)
#define IS_DMACB_CHANNEL_ALL(param)        ((param) <= DMACB_DMAREQB)
#define IS_DMACB_CHANNEL_SINGLE(param)    (((param) >= DMACB_SSP0_RX) && ((param) <= DMACB_SSP2_TX))

/*-------------------------DMACC  channels----------------------------------*/
#define DMACC_SNFC_RD1                     ((uint8_t)0x00)
#define DMACC_SNFC_RD2                     ((uint8_t)0x01)
#define DMACC_SNFC_RD3                     ((uint8_t)0x02)
#define DMACC_SNFC_RD4                     ((uint8_t)0x03)
#define DMACC_SNFC_RD5                     ((uint8_t)0x04)
#define DMACC_SNFC_RD6                     ((uint8_t)0x05)
#define DMACC_SNFC_RD7                     ((uint8_t)0x06)
#define DMACC_SNFC_RD8                     ((uint8_t)0x07)
#define DMACC_AES_READ                     ((uint8_t)0x08)
#define DMACC_AES_WRITE                    ((uint8_t)0x09)
#define DMACC_SHA_WRITE                    ((uint8_t)0x0A)
#define DMACC_DMA_COMPLETION               ((uint8_t)0x0B)
#define DMACC_I2C0_TX_RX                   ((uint8_t)0x0C)
#define DMACC_I2C1_TX_RX                   ((uint8_t)0x0D)
#define DMACC_I2C2_TX_RX                   ((uint8_t)0x0E)
#define DMACC_MTP0_CMP_MATCH0              ((uint8_t)0x0F)
#define DMACC_MTP0_CMP_MATCH1              ((uint8_t)0x10)
#define DMACC_MTP1_CMP_MATCH0              ((uint8_t)0x11)
#define DMACC_MTP1_CMP_MATCH1              ((uint8_t)0x12)
#define DMACC_MTP2_CMP_MATCH0              ((uint8_t)0x13)
#define DMACC_MTP2_CMP_MATCH1              ((uint8_t)0x14)
#define DMACC_MTP3_CMP_MATCH0              ((uint8_t)0x15)
#define DMACC_MTP3_CMP_MATCH1              ((uint8_t)0x16)
#define DMACC_TMRB3_INPUT_CAP0             ((uint8_t)0x17)
#define DMACC_TMRB3_INPUT_CAP1             ((uint8_t)0x18)
#define DMACC_TMRB4_INPUT_CAP0             ((uint8_t)0x19)
#define DMACC_TMRB4_INPUT_CAP1             ((uint8_t)0x1A)
#define DMACC_TMRB5_INPUT_CAP0             ((uint8_t)0x1B)
#define DMACC_TMRB5_INPUT_CAP1             ((uint8_t)0x1C)
#define DMACC_TMRB6_INPUT_CAP0             ((uint8_t)0x1D)
#define DMACC_TMRB6_INPUT_CAP1             ((uint8_t)0x1E)
#define DMACC_DMAREQC                      ((uint8_t)0x1F)

#define IS_DMAC_CHANNEL_ALL(param1,param2) ((((param1) == DMAC_UNIT_A) && ((param2) <= DMACA_DMAREQA)) || \
                                            (((param1) == DMAC_UNIT_B) && ((param2) <= DMACB_DMAREQB)) || \
                                            (((param1) == DMAC_UNIT_C) && ((param2) <= DMACC_DMAREQC)))

    typedef enum {
        DMAC_PRIMARY = 0U,
        DMAC_ALTERNATE = 1U
    } DMAC_PrimaryAlt;
#define IS_DMAC_PRIMARYALT(param)         ((param) <= DMAC_ALTERNATE)
#define IS_DMAC_CTRL_BASE(param)          (((param) & (uint32_t)0x000003FF) == (uint32_t)0x00000000)

    typedef enum {
        DMAC_SINGLE = 0U,
        DMAC_BURST = 1U
    } DMAC_TransferType;
#define IS_DMAC_TRANSFERTYPE(param)       ((param) <= DMAC_BURST)

    typedef enum {
        DMAC_PRIORITY_NORMAL = 0U,
        DMAC_PRIORITY_HIGH = 1U
    } DMAC_Priority;
#define IS_DMAC_PRIORITY(param)           ((param) <= DMAC_PRIORITY_HIGH)

    typedef enum {
        DMAC_BYTE = 0U,         /* Data size of transfer is 1 byte */
        DMAC_HALF_WORD = 1U,    /* Data size of transfer is 2 bytes */
        DMAC_WORD = 2U          /* Data size of transfer is 4 bytes */
    } DMAC_BitWidth;
#define IS_DMAC_BIT_WIDTH(param)          ((param) <= DMAC_WORD)

    typedef enum {
        DMAC_INC_1B = 0U,       /* Address increment 1 byte */
        DMAC_INC_2B = 1U,       /* Address increment 2 bytes */
        DMAC_INC_4B = 2U,       /* Address increment 4 bytes */
        DMAC_INC_0B = 3U        /* Address does not increase */
    } DMAC_IncWidth;
#define IS_DMAC_INCWIDTH(param)           ((param) <= DMAC_INC_0B)
#define IS_DMAC_INCWIDTH_VALID(bitwidth, incwidth)     ((bitwidth) <= (incwidth))

    typedef enum {
        DMAC_INVALID = 0U,
        DMAC_BASIC = 1U,
        DMAC_AUTOMATIC = 2U,
        DMAC_PINGPONG = 3U,
        DMAC_MEM_SCATTER_GATHER_PRI = 4U,       /* Memory scatter/gather mode (primary data) */
        DMAC_MEM_SCATTER_GATHER_ALT = 5U,       /* Memory scatter/gather mode (alternative data) */
        DMAC_PERI_SCATTER_GATHER_PRI = 6U,      /* Peripheral scatter/gather mode (primary data) */
        DMAC_PERI_SCATTER_GATHER_ALT = 7U       /* Peripheral scatter/gather mode (alternative data) */
    } DMAC_CycleCtrl;
#define IS_DMAC_CYCLECTRL(param)          ((param) <= DMAC_PERI_SCATTER_GATHER_ALT)

    typedef enum {
        DMAC_NEXT_NOT_USE_BURST = 0U,
        DMAC_NEXT_USE_BURST = 1U
    } DMAC_Next_UseBurst;
#define IS_DMAC_NEXT_USEBURST(param)      ((param) <= DMAC_NEXT_USE_BURST)

    typedef enum {
        DMAC_AFTER_1_TX = 0U,   /* Arbitration after one transfer */
        DMAC_AFTER_2_TX = 1U,   /* Arbitration after two transfer */
        DMAC_AFTER_4_TX = 2U,
        DMAC_AFTER_8_TX = 3U,
        DMAC_AFTER_16_TX = 4U,
        DMAC_AFTER_32_TX = 5U,
        DMAC_AFTER_64_TX = 6U,
        DMAC_AFTER_128_TX = 7U,
        DMAC_AFTER_256_TX = 8U,
        DMAC_AFTER_512_TX = 9U, /* Arbitration after 512 transfer */
        DMAC_NEVER = 10U        /* Do not arbitration */
    } DMAC_Arbitration;
#define IS_DMAC_ARBITRATION(param)        ((param) <= DMAC_NEVER)

#define IS_DMAC_TXNUM(param)              ((param) <= 1024U)

/** 
  * @brief  Union to store DMA UINTA interrupt
  */
    typedef union {
        uint32_t All;
        struct {
            uint32_t SNFC_PRD11:1;              /*!< Bit0, the flag of SNFC_PRD11 occurs an interrupt */
            uint32_t SNFC_PRD12:1;              /*!< Bit1, the flag of SNFC_PRD12 occurs an interrupt */
            uint32_t SNFC_PRD21:1;              /*!< Bit2, the flag of SNFC_PRD21 occurs an interrupt */
            uint32_t SNFC_PRD22:1;              /*!< Bit3, the flag of SNFC_PRD22 occurs an interrupt */
            uint32_t ADCCompletion:1;           /*!< Bit4, the flag of ADC completion occurs an interrupt */
            uint32_t UART0Reception:1;          /*!< Bit5, the flag of UART0 reception occurs an interrupt */
            uint32_t UART0Transmission:1;       /*!< Bit6, the flag of UART0 transmission occurs an interrupt */
            uint32_t UART1Reception:1;          /*!< Bit7, the flag of UART1 reception occurs an interrupt */
            uint32_t UART1Transmission:1;       /*!< Bit8, the flag of UART1 transmission occurs an interrupt */
            uint32_t SIO_UART0Reception:1;      /*!< Bit9, the flag of SIO/UART0 reception occurs an interrupt */
            uint32_t SIO_UART0Transmission:1;   /*!< Bit10, the flag of SIO/UART0 transmission occurs an interrupt */
            uint32_t SIO_UART1Reception:1;      /*!< Bit11, the flag of SIO/UART1 reception occurs an interrupt */
            uint32_t SIO_UART1Transmission:1;   /*!< Bit12, the flag of SIO/UART1 transmission occurs an interrupt */
            uint32_t SIO_UART2Reception:1;      /*!< Bit13, the flag of SIO/UART2 reception occurs an interrupt */
            uint32_t SIO_UART2Transmission:1;   /*!< Bit14, the flag of SIO/UART2 transmission occurs an interrupt */
            uint32_t SIO_UART3Reception:1;      /*!< Bit15, the flag of SIO/UART3 reception occurs an interrupt */
            uint32_t SIO_UART3Transmission:1;   /*!< Bit16, the flag of SIO/UART3 transmission occurs an interrupt */
            uint32_t TMRB0CompareMatch:1;       /*!< Bit17, the flag of TMRB0 compare match occurs an interrupt */
            uint32_t TMRB1CompareMatch:1;       /*!< Bit18, the flag of TMRB1 compare match occurs an interrupt */
            uint32_t TMRB2CompareMatch:1;       /*!< Bit19, the flag of TMRB2 compare match occurs an interrupt */
            uint32_t TMRB3CompareMatch:1;       /*!< Bit20, the flag of TMRB3 compare match occurs an interrupt */
            uint32_t TMRB4CompareMatch:1;       /*!< Bit21, the flag of TMRB4 compare match occurs an interrupt */
            uint32_t TMRB5CompareMatch:1;       /*!< Bit22, the flag of TMRB5 compare match occurs an interrupt */
            uint32_t TMRB6CompareMatch:1;       /*!< Bit23, the flag of TMRB6 compare match occurs an interrupt */
            uint32_t TMRB7CompareMatch:1;       /*!< Bit24, the flag of TMRB7 compare match occurs an interrupt */
            uint32_t TMRB0InputCapture0:1;      /*!< Bit25, the flag of TMRB0 input capture 0 occurs an interrupt */
            uint32_t TMRB0InputCapture1:1;      /*!< Bit26, the flag of TMRB0 input capture 1 occurs an interrupt */
            uint32_t TMRB1InputCapture0:1;      /*!< Bit27, the flag of TMRB1 input capture 0 occurs an interrupt */
            uint32_t TMRB1InputCapture1:1;      /*!< Bit28, the flag of TMRB1 input capture 1 occurs an interrupt */
            uint32_t TMRB2InputCapture0:1;      /*!< Bit29, the flag of TMRB2 input capture 0 occurs an interrupt */
            uint32_t TMRB2InputCapture1:1;      /*!< Bit30, the flag of TMRB2 input capture 1 occurs an interrupt */
            uint32_t DMAREQA:1;                 /*!< Bit31, the flag of pin DMAREQA occurs an interrupt */
        } Bit;
    } DMACA_Flag;

/** 
  * @brief  Union to store DMA UINTB interrupt
  */
    typedef union {
        uint32_t All;
        struct {
            uint32_t SNFC_GIE1:1;               /*!< Bit0, the flag of SNFC_GIE1 occurs an interrupt */
            uint32_t SNFC_GIE2:1;               /*!< Bit1, the flag of SNFC_GIE2 occurs an interrupt */
            uint32_t SNFC_GIE3:1;               /*!< Bit2, the flag of SNFC_GIE3 occurs an interrupt */
            uint32_t SNFC_GIE4:1;               /*!< Bit3, the flag of SNFC_GIE4 occurs an interrupt */
            uint32_t SNFC_GIE5:1;               /*!< Bit4, the flag of SNFC_GIE5 occurs an interrupt */
            uint32_t SNFC_GIE6:1;               /*!< Bit5, the flag of SNFC_GIE6 occurs an interrupt */
            uint32_t SNFC_GIE7:1;               /*!< Bit6, the flag of SNFC_GIE7 occurs an interrupt */
            uint32_t SNFC_GIE8:1;               /*!< Bit7, the flag of SNFC_GIE8 occurs an interrupt */
            uint32_t SNFC_GID11:1;              /*!< Bit8, the flag of SNFC_GID11 occurs an interrupt */
            uint32_t SNFC_GID12:1;              /*!< Bit9, the flag of SNFC_GID12 occurs an interrupt */
            uint32_t SNFC_GID13:1;              /*!< Bit10, the flag of SNFC_GID13 occurs an interrupt */
            uint32_t SNFC_GID14:1;              /*!< Bit11, the flag of SNFC_GID14 occurs an interrupt */
            uint32_t SNFC_GID15:1;              /*!< Bit12, the flag of SNFC_GID15 occurs an interrupt */
            uint32_t SNFC_GID16:1;              /*!< Bit13, the flag of SNFC_GID16 occurs an interrupt */
            uint32_t SNFC_GID17:1;              /*!< Bit14, the flag of SNFC_GID17 occurs an interrupt */
            uint32_t SNFC_GID18:1;              /*!< Bit15, the flag of SNFC_GID18 occurs an interrupt */
            uint32_t SNFC_GID21:1;              /*!< Bit16, the flag of SNFC_GID21 occurs an interrupt */
            uint32_t SNFC_GID22:1;              /*!< Bit17, the flag of SNFC_GID22 occurs an interrupt */
            uint32_t SNFC_GID23:1;              /*!< Bit18, the flag of SNFC_GID23 occurs an interrupt */
            uint32_t SNFC_GID24:1;              /*!< Bit19, the flag of SNFC_GID24 occurs an interrupt */
            uint32_t SNFC_GID25:1;              /*!< Bit20, the flag of SNFC_GID25 occurs an interrupt */
            uint32_t SNFC_GID26:1;              /*!< Bit21, the flag of SNFC_GID26 occurs an interrupt */
            uint32_t SNFC_GID27:1;              /*!< Bit22, the flag of SNFC_GID27 occurs an interrupt */
            uint32_t SNFC_GID28:1;              /*!< Bit23, the flag of SNFC_GID28 occurs an interrupt */
            uint32_t ADCCompletion:1;           /*!< Bit24, the flag of ADC completion occurs an interrupt */
            uint32_t SSP0Reception:1;           /*!< Bit25, the flag of SSP0 reception occurs an interrupt */
            uint32_t SSP0Transmission:1;        /*!< Bit26, the flag of SSP0 transmission occurs an interrupt */
            uint32_t SSP1Reception:1;           /*!< Bit27, the flag of SSP1 reception occurs an interrupt */
            uint32_t SSP1Transmission:1;        /*!< Bit28, the flag of SSP1 transmission occurs an interrupt */
            uint32_t SSP2Reception:1;           /*!< Bit29, the flag of SSP2 reception occurs an interrupt */
            uint32_t SSP2Transmission:1;        /*!< Bit30, the flag of SSP2 transmission occurs an interrupt */
            uint32_t DMAREQB:1;                 /*!< Bit31, the flag of pin DMAREQB occurs an interrupt */
        } Bit;
    } DMACB_Flag;

/** 
  * @brief  Union to store DMA UINTC interrupt
  */
    typedef union {
        uint32_t All;
        struct {
            uint32_t SNFC_RD1:1;                /*!< Bit0, the flag of SNFC_RD1 occurs an interrupt */
            uint32_t SNFC_RD2:1;                /*!< Bit1, the flag of SNFC_RD2 occurs an interrupt */
            uint32_t SNFC_RD3:1;                /*!< Bit2, the flag of SNFC_RD3 occurs an interrupt */
            uint32_t SNFC_RD4:1;                /*!< Bit3, the flag of SNFC_RD4 occurs an interrupt */
            uint32_t SNFC_RD5:1;                /*!< Bit4, the flag of SNFC_RD5 occurs an interrupt */
            uint32_t SNFC_RD6:1;                /*!< Bit5, the flag of SNFC_RD6 occurs an interrupt */
            uint32_t SNFC_RD7:1;                /*!< Bit6, the flag of SNFC_RD7 occurs an interrupt */
            uint32_t SNFC_RD8:1;                /*!< Bit7, the flag of SNFC_RD8 occurs an interrupt */
            uint32_t AESRead:1;                 /*!< Bit8, the flag of AES read occurs an interrupt */
            uint32_t AESWrite:1;                /*!< Bit9, the flag of AES write occurs an interrupt */
            uint32_t SHAWrite:1;                /*!< Bit10, the flag of SHA write occurs an interrupt */
            uint32_t DMACompletion:1;           /*!< Bit11, the flag of DMA completion occurs an interrupt */
            uint32_t I2C0RxorTx:1;              /*!< Bit12, the flag of I2C0 reception/transmission occurs an interrupt */
            uint32_t I2C1RxorTx:1;              /*!< Bit13, the flag of I2C1 reception/transmission occurs an interrupt */
            uint32_t I2C2RxorTx:1;              /*!< Bit14, the flag of I2C2 reception/transmission occurs an interrupt */
            uint32_t MTP0CompareMatch0:1;       /*!< Bit15, the flag of MTP0 compare match 0 occurs an interrupt */
            uint32_t MTP0CompareMatch1:1;       /*!< Bit16, the flag of MTP0 compare match 1 occurs an interrupt */
            uint32_t MTP1CompareMatch0:1;       /*!< Bit17, the flag of MTP1 compare match 0 occurs an interrupt */
            uint32_t MTP1CompareMatch1:1;       /*!< Bit18, the flag of MTP1 compare match 1 occurs an interrupt */
            uint32_t MTP2CompareMatch0:1;       /*!< Bit19, the flag of MTP2 compare match 0 occurs an interrupt */
            uint32_t MTP2CompareMatch1:1;       /*!< Bit20, the flag of MTP2 compare match 1 occurs an interrupt */
            uint32_t MTP3CompareMatch0:1;       /*!< Bit21, the flag of MTP3 compare match 0 occurs an interrupt */
            uint32_t MTP3CompareMatch1:1;       /*!< Bit22, the flag of MTP3 compare match 1 occurs an interrupt */
            uint32_t TMRB3InputCapture0:1;      /*!< Bit23, the flag of TMRB3 input capture 0 occurs an interrupt */
            uint32_t TMRB3InputCapture1:1;      /*!< Bit24, the flag of TMRB3 input capture 1 occurs an interrupt */
            uint32_t TMRB4InputCapture0:1;      /*!< Bit25, the flag of TMRB4 input capture 0 occurs an interrupt */
            uint32_t TMRB4InputCapture1:1;      /*!< Bit26, the flag of TMRB4 input capture 1 occurs an interrupt */
            uint32_t TMRB5InputCapture0:1;      /*!< Bit27, the flag of TMRB5 input capture 0 occurs an interrupt */
            uint32_t TMRB5InputCapture1:1;      /*!< Bit28, the flag of TMRB5 input capture 1 occurs an interrupt */
            uint32_t TMRB6InputCapture0:1;      /*!< Bit29, the flag of TMRB6 input capture 0 occurs an interrupt */
            uint32_t TMRB6InputCapture1:1;      /*!< Bit30, the flag of TMRB6 input capture 1 occurs an interrupt */
            uint32_t DMAREQC:1;                 /*!< Bit31, the flag of pin DMAREQC occurs an interrupt */
        } Bit;
    } DMACC_Flag;

/** 
  * @brief  DMA Structure definition  
  */
    typedef struct {
        uint32_t SrcEndPointer; /*!< The final address of source */
        uint32_t DstEndPointer; /*!< The final address of destination */
        DMAC_CycleCtrl Mode;    /*!< Set operation mode */
        DMAC_Next_UseBurst NextUseBurst;
        uint32_t TxNum;         /*!< Set the actual number of transfers. max is 1024 */
        DMAC_Arbitration ArbitrationMoment;     /*!< Specifies the arbitration moment(R_Power)  */
        DMAC_BitWidth SrcWidth; /*!< Set source bit width */
        DMAC_IncWidth SrcInc;   /*!< Set increment of the source address */
        DMAC_BitWidth DstWidth; /*!< Set destination bit width */
        DMAC_IncWidth DstInc;   /*!< Set increment of the destination address */
    } DMAC_InitTypeDef;

/** @} */
/* End of group uDMAC_Exported_Types */

/** @defgroup uDMAC_Exported_FunctionPrototypes
  * @{
  */
    FunctionalState DMAC_GetDMACState(TSB_DMA_TypeDef * DMACx);
    void DMAC_Enable(TSB_DMA_TypeDef * DMACx);
    void DMAC_Disable(TSB_DMA_TypeDef * DMACx);
    void DMAC_SetPrimaryBaseAddr(TSB_DMA_TypeDef * DMACx, uint32_t Addr);
    uint32_t DMAC_GetBaseAddr(TSB_DMA_TypeDef * DMACx, DMAC_PrimaryAlt PriAlt);
    void DMAC_SetSWReq(TSB_DMA_TypeDef * DMACx, uint8_t Channel);
    void DMACA_SetTransferType(uint8_t Channel, DMAC_TransferType Type);   
    DMAC_TransferType DMACA_GetTransferType(uint8_t Channel);
    void DMACB_SetTransferType(uint8_t Channel, DMAC_TransferType Type);
    DMAC_TransferType DMACB_GetTransferType(uint8_t Channel);
    void DMAC_SetMask(TSB_DMA_TypeDef * DMACx, uint8_t Channel, FunctionalState NewState);
    FunctionalState DMAC_GetMask(TSB_DMA_TypeDef * DMACx, uint8_t Channel);
    void DMAC_SetChannel(TSB_DMA_TypeDef * DMACx, uint8_t Channel, FunctionalState NewState);
    FunctionalState DMAC_GetChannelState(TSB_DMA_TypeDef * DMACx, uint8_t Channel);
    void DMAC_SetPrimaryAlt(TSB_DMA_TypeDef * DMACx, uint8_t Channel, DMAC_PrimaryAlt PriAlt);
    DMAC_PrimaryAlt DMAC_GetPrimaryAlt(TSB_DMA_TypeDef * DMACx, uint8_t Channel);
    void DMAC_SetChannelPriority(TSB_DMA_TypeDef * DMACx, uint8_t Channel, DMAC_Priority Priority);
    DMAC_Priority DMAC_GetChannelPriority(TSB_DMA_TypeDef * DMACx, uint8_t Channel);
    void DMAC_ClearBusErr(TSB_DMA_TypeDef * DMACx);
    Result DMAC_GetBusErrState(TSB_DMA_TypeDef * DMACx);
    void DMAC_FillInitData(TSB_DMA_TypeDef * DMACx, uint8_t Channel, DMAC_InitTypeDef * InitStruct);
    DMACA_Flag DMACA_GetINTFlag(void);
    DMACB_Flag DMACB_GetINTFlag(void);
    DMACC_Flag DMACC_GetINTFlag(void);
/** @} */
/* End of group uDMAC_Exported_FunctionPrototype */

/** @} */
/* End of group uDMAC */

/** @} */
/* End of group TX04_Periph_Driver */

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* __TMPM46B_uDMAC_H */
