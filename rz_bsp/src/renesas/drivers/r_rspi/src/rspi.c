/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name     : rspi.c
* Device(s)     : RZ/A1H (R7S721001)
* Tool-Chain    : GNUARM-RZv13.01-EABI
* H/W Platform  : RSK+RZA1H CPU Board
* Description   : This file implements device driver for RSPI module.
*******************************************************************************/
/*******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 18.06.2013 1.00
*               : 21.03.2014 2.00
*******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
/* Default  type definition header */
#include "r_typedefs.h"
/* I/O Register root header */
#include "iodefine_cfg.h"
/* INTC Driver Header */
#include "r_intc.h"
/* Device driver for RSPI header */
#include "rspi.h"
/* Low level register read/write header */
#include "rza_io_regrw.h"
/* Interchangeable compiler specific header */
#include "compiler_settings.h"
#include "Renesas_RZ_A1.h"
#include "r_port_sc_cfg.h"
#include "r_gpio_if.h"

/******************************************************************************
Global variables and functions
******************************************************************************/
/* RSPI1 transmit buffer address */
uint32_t * gp_rspi1_tx_address;
/* RSPI1 transmit data number */
uint16_t   g_rspi1_tx_count;
/* RSPI1 receive buffer address */
uint32_t * gp_rspi1_rx_address;
/* RSPI1 receive data number */
uint16_t   g_rspi1_rx_count;
/* RSPI1 receive data length */
uint16_t   g_rspi1_rx_length;

/* SCI5 transmit buffer address */
uint8_t * gp_spi_tx_address;
/* SCI5 transmit data number */
uint16_t  g_spi_tx_count;

static void port_settings(void)
{
    set_pins_function(&GPIO_SC_INIT_rspi0);

    set_pin_function(&GPIO_SC_TABLE_intc[0]);

    gpio_init(P3_15); gpio_dir(P3_15, PIN_OUTPUT); gpio_write(P3_15, 1);
    gpio_init(P9_5);  gpio_dir(P9_5,  PIN_OUTPUT);
    gpio_init(P6_13); gpio_dir(P6_13, PIN_OUTPUT);


}

static void power_perhiperial(void)
{
    uint32_t  u32val;
    uint32_t was_masked;
    volatile uint8_t dummy_buf;

#if defined (__ICCARM__)
    was_masked = __disable_irq_iar();
#else
    was_masked = __disable_irq();
#endif

    u32val = CPG.STBCR10;
    CPG.STBCR10 = (uint8_t)(u32val & ~((uint32_t)CPG_STBCR10_MSTP106));

    /* dummy read */
    dummy_buf = CPG.STBCR10;

    if (0 == was_masked)
    {
        __enable_irq();
    }
}

/*******************************************************************************
* Function Name: R_RSPI1_Create
* Description  : This function initialises the RSPI1 module.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RSPI1_Create(void)
{
    uint16_t dummy_word  = 0u;
    uint8_t  dummy_byte  = 0u;

    UNUSED_VARIABLE(dummy_word);
    UNUSED_VARIABLE(dummy_byte);

    dummy_byte = ADC_PRI_SPTI1;

    /* Configure and disable SPI1 transmit interrupts */
    R_INTC_Disable(INTC_ID_SPTI1);
    R_INTC_RegistIntFunc(INTC_ID_SPTI1, &r_rspi1_transmit_interrupt);
    R_INTC_SetPriority(INTC_ID_SPTI1, dummy_byte);

    port_settings();

    power_perhiperial();

    RSPI1.SPPCR = 0u;
    dummy_byte = RSPI1.SPPCR;
    /* SPBR 2, P1 clock = 66.67MHz, SPI bit rate = 11.11Mbits/s Check Table 16.3 */
    /* SPBR 1, P1 clock = 66.67MHz, SPI bit rate = 16.67Mbits/s Check Table 16.3 */
    /* SPBR 0, P1 clock = 66.67MHz, SPI bit rate = 33.33Mbits/s Check Table 16.3 */
    RSPI1.SPBR  = 0x02u;
    dummy_byte = RSPI1.SPBR;
    RSPI1.SPDCR = 0x20u;
    dummy_byte = RSPI1.SPDCR;
    RSPI1.SPSCR = 0u;
    dummy_byte = RSPI1.SPSCR;
    RSPI1.SPCKD = 0;
    dummy_byte = RSPI1.SPCKD;
    RSPI1.SSLND = 0u;
    dummy_byte =  RSPI1.SSLND;
    RSPI1.SPND  = 0u;
    dummy_byte = RSPI1.SPND;
    RSPI1.SSLP  = 0u;
    dummy_byte = RSPI1.SSLP;
    RSPI1.SPSSR  = 0u;
    dummy_byte = RSPI1.SPSSR;
    RSPI1.SPBFCR  |= 0x30u;
    dummy_byte = RSPI1.SPBFCR;
    /* LSB first, use 16 bit data length */
    RSPI1.SPCMD0 = 0x0703u;
    dummy_word = RSPI1.SPCMD0;

       /* Enable master mode */
    RSPI1.SPCR |= 0x28u;
    dummy_byte = RSPI1.SPCR;
}

/*******************************************************************************
* Function Name: R_RSPI1_Start
* Description  : This function starts the RSPI1 module operation.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RSPI1_Start(void)
{
    volatile uint8_t dummy = 0u;

    UNUSED_VARIABLE(dummy);

    /* Enable RSPI interrupts */
    R_INTC_Enable(INTC_ID_SPTI1);
//    R_INTC_Enable(INTC_ID_SPRI1);

    /* Clear error sources */
    dummy = RSPI1.SPSR;
    RSPI1.SPSR = 0x00U;

    if (0 == rza_io_reg_read_8( &(RSPI1.SPSR),
                               RSPIn_SPSR_MODF_SHIFT,
                               RSPIn_SPSR_MODF))
    {
        /* test */
        RSPI1.SPCR |= 0x40U;
        dummy = RSPI1.SPCR;
    }
    else
    {
        /* clear the MODF flag then set the SPE bit */
        dummy = RSPI1.SPSR;

        RSPI1.SPCR |= 0x40U;
        dummy = RSPI1.SPCR;
    }
}

/*******************************************************************************
* Function Name: R_RSPI1_Stop
* Description  : This function stops the RSPI1 module operation.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RSPI1_Stop(void)
{
    /* Disable RSPI interrupts */
    R_INTC_Disable(INTC_ID_SPTI1);

    /* Disable RSPI function */
    rza_io_reg_write_8( &(RSPI1.SPCR),
                       0,
                       RSPIn_SPCR_SPE_SHIFT,
                       RSPIn_SPCR_SPE);

}
/*******************************************************************************
* Function Name: R_RSPI1_Send_Receive
* Description  : This function sends and receives CSI#n1 data.
* Arguments    : tx_buf -
*                 transfer buffer pointer (not used when data is handled by DTC)
*                tx_num -
*                    buffer size
*                rx_buf -
*                 receive buffer pointer (not used when data is handled by DTC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
*******************************************************************************/
uint8_t R_RSPI1_Send_Receive(uint32_t * const tx_buf,
                                      uint16_t tx_num, uint32_t * const rx_buf)
{
    uint8_t status = 0u;

    if (tx_num < 1U)
    {
        status = 1u;
    }
    else
    {
        gp_rspi1_tx_address = tx_buf;
        g_rspi1_tx_count = tx_num;

        gp_rspi1_rx_address = rx_buf;
        g_rspi1_rx_length = tx_num;
        g_rspi1_rx_count = 0U;

        /* Enable transmit interrupt */
        rza_io_reg_write_8( &(RSPI1.SPCR),
                           1,
                           RSPIn_SPCR_SPTIE_SHIFT,
                           RSPIn_SPCR_SPTIE);

        /* Enable receive interrupt */
        rza_io_reg_write_8( &(RSPI1.SPCR),
                           1,
                           RSPIn_SPCR_SPRIE_SHIFT,
                           RSPIn_SPCR_SPRIE);

        /* Enable RSPI function */
        rza_io_reg_write_8( &(RSPI1.SPCR),
                           1,
                           RSPIn_SPCR_SPE_SHIFT,
                           RSPIn_SPCR_SPE);
    }

    return (status);
}

/*******************************************************************************
* Function Name: R_RSPI1_LoopBackReversed
* Description  : This function .
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RSPI1_LoopBackReversed(void)
{
    rza_io_reg_write_8( &(RSPI1.SPPCR),
                       (uint8_t)1,
                       RSPIn_SPPCR_SPLP_SHIFT,
                       RSPIn_SPPCR_SPLP);
}

/*******************************************************************************
* Function Name: R_RSPI1_LoopBackDisable
* Description  : This function disable loop-back mode.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RSPI1_LoopBackDisable(void)
{
    rza_io_reg_write_8( &(RSPI1.SPPCR),
                       0,
                       RSPIn_SPPCR_SPLP_SHIFT,
                       RSPIn_SPPCR_SPLP);
}
