/**
 *******************************************************************************
 * @file    main.h
 * @brief   header file for main.c, included some address definition and
 *          function prototypes
 * @version V0.100
 * @date    2015/03/17
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

#ifndef MAIN_H
#define MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "tmpm46b_fc.h"
#include "led.h"
#include "sw.h"
/* Private define ------------------------------------------------------------*/
#define SWP_BOOT_MODE           ((uint8_t)0x01)
#define NORMAL_MODE             ((uint8_t)0x00)

#if defined ( __CC_ARM   )       /* RealView Compiler */
#define FLASH_API_ROM           (uint32_t *)&Load$$FLASH_CODE_RAM$$Base

#define FLASH_API_RAM           (uint32_t *)&Image$$FLASH_CODE_RAM$$Base
#define SIZE_FLASH_API          (uint32_t)&Load$$FLASH_CODE_RAM$$Length

#define SWP_FLASH               (uint32_t *)&Image$$FLASH_SWP$$Base

#define SWP_RAM                 (uint32_t *)&Image$$RAM_SWP$$Base

#define SIZE_SWP                (uint32_t)&Image$$FLASH_SWP$$ZI$$Length

#elif defined ( __ICCARM__ )     /* IAR Compiler */
#define FLASH_API_ROM           ((uint32_t *)__section_begin("FLASH_CODE_ROM"))
#define FLASH_API_RAM           ((uint32_t *)__section_begin("FLASH_CODE_RAM"))
#define SIZE_FLASH_API          ((uint32_t)__section_size("FLASH_CODE_ROM"))

#define SWP_FLASH               ((uint32_t *)__section_begin("FLASH_SWP"))

#define SWP_RAM                 ((uint32_t *)__section_begin("RAM_SWP"))

#define SIZE_SWP                ((uint32_t)__section_size("FLASH_SWP"))
#endif

/* Private function prototypes -----------------------------------------------*/
void Copy_Routine(uint32_t * dest, uint32_t * source, uint32_t size);
uint8_t Write_Flash(uint32_t * addr_dest, uint32_t * addr_source, uint32_t len);
#endif
/*************************** END OF FILE **************************************/
