/**
 *******************************************************************************
 * @file    main.c
 * @brief   the application functions of EXB demo for the 
 *          TOSHIBA 'TMPM46B' Device Series 
 * @version V0.100
 * @date    2015/03/06
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
#include <stdio.h>
#include <string.h>
#include "tmpm46b_exb.h"
#include "tmpm46b_gpio.h"
#include "common_uart.h"

#define SRAM_RW

#ifdef SRAM_RW
#define TEST_DATA_LEN           ((uint16_t)0x0010)
#define EXB_SRAM_START_ADDR     ((uint32_t)0x60000000)
void EXB_GPIOConfig(void);
Result rw_result = SUCCESS;
#endif

/*******************************************************************************
* Function Name  : main
* Description    : main function:demo for external 16-bit SRAM, multiplex bus mode
* Input          : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
    uint8_t chip = EXB_CS1;
    uint8_t BusMode = EXB_BUS_MULTIPLEX;
    /* Address bus and data bus are multiplexed */
    uint8_t Cycle = EXB_CYCLE_QUADRUPLE;
    /* Initial process demo */

#ifdef SRAM_RW
    uint32_t w_data[TEST_DATA_LEN] = { 0U };
    uint32_t r_data[TEST_DATA_LEN] = { 0U };
    uint32_t *addr = NULL;
    uint16_t i = 0U;
    EXB_InitTypeDef InitStruct = { 0U };
#endif

    /* Configure UART */
    hardware_init(UART_RETARGET);

    InitStruct.AddrSpaceSize = EXB_128K_BYTE;
    InitStruct.StartAddr = 0x00;
    InitStruct.BusWidth = EXB_BUS_WIDTH_BIT_16;
    /* Set cycles time according to AC timing of SRAM datasheet, base clock: EXBCLK(fsys) */
    InitStruct.Cycles.InternalWait = EXB_INTERNAL_WAIT_8;
    InitStruct.Cycles.ReadSetupCycle = EXB_CYCLE_2;
    InitStruct.Cycles.WriteSetupCycle = EXB_CYCLE_2;
    InitStruct.Cycles.ALEWaitCycle = EXB_CYCLE_2;
    InitStruct.Cycles.ReadRecoveryCycle = EXB_CYCLE_2;
    InitStruct.Cycles.WriteRecoveryCycle = EXB_CYCLE_2;
    InitStruct.Cycles.ChipSelectRecoveryCycle = EXB_CYCLE_2;

#ifdef SRAM_RW
    EXB_GPIOConfig();
#endif

    EXB_SetBusMode(BusMode);
    EXB_SetBusCycleExtension(Cycle);
    EXB_Init(chip, &InitStruct);
    EXB_Enable(chip);

#ifdef SRAM_RW
    /* SRAM Read/Write demo */
    addr = (uint32_t *) (((uint32_t) InitStruct.StartAddr) | EXB_SRAM_START_ADDR);
    for (i = 0U; i < TEST_DATA_LEN; i++) {
        w_data[i] = i;
    }

    /* write data from w_data[] to SRAM */
    for (i = 0; i < TEST_DATA_LEN ; i++) {
        addr[i] = w_data[i];
    }

    /* read data from SRAM, store into r_data[] */
    for (i = 0; i < TEST_DATA_LEN ; i++) {
        r_data[i] = addr[i];
    }

    /* check rw_result to see if SRAM write/read is successful or not */
    for (i = 0; i < TEST_DATA_LEN ; i++) {
        if (w_data[i] != r_data[i]) {
            rw_result = ERROR;
            break;
        }
    }

    if (rw_result == SUCCESS){
        common_uart_disp("SRAM read/write successful \n");
    } else {
        common_uart_disp("SRAM read/write failed \n");
    }
#endif
    while (1) {
        /* Do nothing */
    }
}

/**
  * @brief  Configure GPIO to EXB
  * @param  None
  * @retval None
  */

void EXB_GPIOConfig(void)
{
    /* PBFR1 PORT[2] PORT[3] PORT[5] PORT[6] as WR RD ALE BELL */
    GPIO_SetOutputEnableReg(GPIO_PB, 0x6CU , ENABLE);
    GPIO_EnableFuncReg(GPIO_PB, GPIO_FUNC_REG_1, 0x6CU);
    GPIO_SetInputEnableReg(GPIO_PB, 0x2CU, ENABLE);
    GPIO_SetPullUp(GPIO_PB, 0x6CU, DISABLE);

    /* PEFR3 PORT[0:7] as address bus(A16-A23) */
    GPIO_SetOutputEnableReg(GPIO_PE, 0xFFU, ENABLE);
    GPIO_EnableFuncReg(GPIO_PE, GPIO_FUNC_REG_3, 0xFFU);
    GPIO_SetInputEnableReg(GPIO_PE, 0xFFU, ENABLE);

    /* PFFR1 PORT[0:7] as DATA(D0-D7)/AD0-AD7  bus */
    GPIO_SetOutputEnableReg(GPIO_PF, 0xFFU, ENABLE);
    GPIO_EnableFuncReg(GPIO_PF, GPIO_FUNC_REG_1, 0xFFU);
    GPIO_SetInputEnableReg(GPIO_PF, 0xFFU, ENABLE);

    /* PGFR1 PORT[0:7] as DATA(D8-D15)/AD8-AD15  bus */
    GPIO_SetOutputEnableReg(GPIO_PG, 0xFFU, ENABLE);
    GPIO_EnableFuncReg(GPIO_PG, GPIO_FUNC_REG_1, 0xFFU);
    GPIO_SetInputEnableReg(GPIO_PG, 0xFFU, ENABLE);
    
    /* PHFR1 PORT[0] PORT[1] as BELH CS1 */
    GPIO_SetOutputEnableReg(GPIO_PH, 0x03U, ENABLE);
    GPIO_EnableFuncReg(GPIO_PH, GPIO_FUNC_REG_1, 0x03U);
    GPIO_SetInputEnableReg(GPIO_PH, 0x03U, ENABLE);
}

#ifdef DEBUG
void assert_failed(char *file, int32_t line)
{
    while (1) {
        __NOP();
    }
}
#endif
