/**
 *******************************************************************************
 * @file    main.c
 * @brief   main function of Flash auto swap demo(Flash_Swp_B)
 * @version V0.100
 * @date    2015/03/18
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
#include "main.h"

#define PAGE0ADDR ((uint32_t)0x00000000)
#define PAGE2ADDR ((uint32_t)0x00002000)
#define PAGE3ADDR ((uint32_t)0x00003000)

void delay(uint32_t DelayTime);
uint8_t Mode_Judgement(void);
FunctionalState FC_GetProtectState(void);

#if defined ( __CC_ARM   )      /* RealView Compiler */
extern uint32_t Load$$FLASH_CODE_RAM$$Base;
extern uint32_t Image$$FLASH_CODE_RAM$$Base;
extern uint32_t Load$$FLASH_CODE_RAM$$Length;
extern uint32_t Image$$FLASH_SWP$$Base;
extern uint32_t Image$$RAM_SWP$$Base;
extern uint32_t Image$$FLASH_SWP$$ZI$$Length;

#elif defined ( __ICCARM__ )    /* IAR Compiler */
#pragma section = "FLASH_CODE_RAM"
#pragma section = "FLASH_CODE_ROM"
#pragma section = "FLASH_SWP"
#pragma section = "RAM_SWP"
#endif

/**
  * @brief  delay some time
  * @param  delay time
  * @retval None.
  */
void delay(uint32_t DelayTime)
{
    uint32_t time;
    for (time = 0U; time < DelayTime; time++) {
        /* Do nothing */
    }
}
/**
  * @brief  judge current mode is USER_BOOT_MODE or NORMAL_MODE
  * @param  None.
  * @retval None.
  */
uint8_t Mode_Judgement(void)
{
    return (SW_Get(SW4) == 1U) ? SWP_BOOT_MODE : NORMAL_MODE;
}
/**
  * @brief  Get the specified page and block protection state.
  * @param  None.
  * @retval DISABLE or ENABLE.
  */
FunctionalState FC_GetProtectState(void)
{
    FunctionalState retval=DISABLE;
    uint32_t i;
    for(i=0U;i<=FC_PAGE_MAX;i++){
        if(FC_GetPageProtectState(i)==ENABLE){
            retval=ENABLE;
        }else{
            /* Do nothing */
        }
    }
    for(i=1U;i<=FC_BLOCK_MAX;i++){
        if(FC_GetBlockProtectState(i)==ENABLE){
            retval=ENABLE;
        }else{
            /* Do nothing */
        }
    }
    return retval;
}

/**
  * @brief  main function to run flash auto swap demo
  * @param  None.
  * @retval None.
  */
int32_t main(void)
{
    LED_Init();
    SW_Init();
    if (Mode_Judgement() == SWP_BOOT_MODE) {   /* if SW4 is turned on, enter SWP boot mode */
        Copy_Routine(FLASH_API_RAM, FLASH_API_ROM, SIZE_FLASH_API);     /* copy flash API to RAM */
        if(FC_GetSecurityBit() == ENABLE){
            FC_SetSecurityBit(DISABLE);
        }else{
            /* Do nothing */
        }
        FC_SetSwpsrBit(FC_SWPSR_BIT_8);          /* set SWP size to 8KB*/
        if (FC_GetSwapState() == FC_SWAP_INITIAL) {     
            if(FC_GetProtectState() == ENABLE){
                FC_EraseProtectState();
            } else {
                /* Do nothing */
            }
            Copy_Routine(SWP_RAM, SWP_FLASH, SIZE_SWP);                   /* copy program to RAM */
            FC_ErasePage(PAGE2ADDR);
            FC_ErasePage(PAGE3ADDR);
            Write_Flash((uint32_t *)PAGE2ADDR, SWP_RAM, SIZE_SWP);        /* write program to PAGE2ADDR */
            FC_SetSwpsrBit(FC_SWPSR_BIT_0);                               /* enable swp function */
        } else {
            FC_EraseProtectState();                                       /* release swp function */
        }
        delay(4000000U);
        LED_On(LED2);
        /* wait for Key SW4 to release */
        while(Mode_Judgement() == SWP_BOOT_MODE){
            /* Do nothing */
        }
        /* software reset */
        NVIC_SystemReset();
    } else {                    /* if SW4 is turned off, enter normal mode, LED flash */
        while(1){
            LED_On(LED1);
            delay(4000000U);
            LED_Off(LED1);
            delay(4000000U);
        }
    }
    return 0U;
}

/**
  * @brief  copy 32-bit data from source to dest
  * @param  the address of source and dest, the data size
  * @retval None.
  */
void Copy_Routine(uint32_t * dest, uint32_t * source, uint32_t size)
{
    uint32_t *dest_addr, *source_addr, tmpsize;
    uint32_t i, tmps, tmpd, mask;

    dest_addr = dest;
    source_addr = source;
    
    tmpsize = size >> 2U;

    for (i = 0U; i < tmpsize; i++) {    /* 32bits copy */
        *dest_addr = *source_addr;
        dest_addr++;
        source_addr++;
    }
    if (size & 0x00000003U) {   /* if the last data size is not 0(maybe 1,2 or 3), copy the last data */
        mask = 0xFFFFFF00U;
        i = size & 0x00000003U;
        tmps = *source_addr;
        tmpd = *dest_addr;
        while (i - 1U) {
            mask = mask << 8U;
            i--;
        }
        tmps = tmps & (~mask);
        tmpd = tmpd & (mask);
        *dest_addr = tmps + tmpd;       /* 32bits copy, but only change the bytes need to be changed */
    } else {
        /* Do nothing */
    }
}

/**
  * @brief  write flash
  * @param  destination address, source address, lenth of data.
  * @retval ERROR or SUCCESS.
  */
#if defined ( __CC_ARM   )      /* RealView Compiler */
#pragma arm section code="FLASH_ROM"
#elif defined ( __ICCARM__ )    /* IAR Compiler */
#pragma location = "FLASH_ROM"
#endif
uint8_t Write_Flash(uint32_t * addr_dest, uint32_t * addr_source, uint32_t len)
{
    uint32_t size;
    uint32_t *source;
    uint32_t *dest;

    dest = addr_dest;
    source = addr_source;
    size = len;
    while (size > PROGRAM_UNIT) {
        if (FC_SUCCESS == FC_WritePage((uint32_t) dest, source)) {      /* write one page every time */
            /* Do nothing */
        } else {
            return ERROR;
        }
        size = size - (PROGRAM_UNIT << 2U);
        dest = dest + PROGRAM_UNIT;
        source = source + PROGRAM_UNIT;
    }
    if (FC_SUCCESS == FC_WritePage((uint32_t) dest, source)) {  /* write the last data, no more than one page */
        /* Do nothing */
    } else {
        return ERROR;
    }
    return SUCCESS;
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1U) {
        __NOP();
    }
}
#endif

/*************************** END OF FILE **************************************/
