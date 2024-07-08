/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"
#include "hpm_spi_drv.h"
#include "spi_com.h"

spi_dev_t spi1_dev = {
    .spi = HPM_SPI1,
    .clock_name = clock_spi1,
    .irq_num = IRQn_SPI1,
    .cs_ioc_pad = IOC_PAD_PA26,
    .cs_ioc_func = IOC_PA26_FUNC_CTL_SPI1_CS_0,
    .clk_ioc_pad = IOC_PAD_PA27,
    .clk_ioc_func = IOC_PA27_FUNC_CTL_SPI1_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1),
    .mosi_ioc_pad = IOC_PAD_PA29,
    .mosi_ioc_func = IOC_PA29_FUNC_CTL_SPI1_MOSI,
    .miso_ioc_pad = IOC_PAD_PA28,
    .miso_ioc_func = IOC_PA28_FUNC_CTL_SPI1_MISO,
    .io2_ioc_pad = IOC_PAD_PA30,
    .io2_ioc_func = IOC_PA30_FUNC_CTL_SPI1_DAT2,
    .io3_ioc_pad = IOC_PAD_PA31,
    .io3_ioc_func = IOC_PA31_FUNC_CTL_SPI1_DAT3,
    .spi_pins_ioc_ctl = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3),
};


void spi1_isr(void)
{
    volatile uint32_t irq_status;
    irq_status = spi_get_interrupt_status(HPM_SPI1);
    if (irq_status & spi_end_int) {
        spi_clear_interrupt_status(HPM_SPI1, spi_end_int);
        spi1_dev.status = SPI_END_OF_TRANSFER_FLAG;
        if (spi1_dev.isr_handler) {
            spi1_dev.isr_handler((void *)&spi1_dev.status);
        }
    }
    if (irq_status & spi_rx_fifo_threshold_int) {
        spi_clear_interrupt_status(HPM_SPI1, spi_rx_fifo_threshold_int);
        spi1_dev.status = SPI_VALID_RX_FLAG;
        if (spi1_dev.isr_handler) {
            spi1_dev.isr_handler((void *)&spi1_dev.status);
        }
    }
    if (irq_status & spi_tx_fifo_threshold_int) {
        spi_clear_interrupt_status(HPM_SPI1, spi_tx_fifo_threshold_int);
        spi1_dev.status = SPI_EMPTY_TX_FLAG;
        if (spi1_dev.isr_handler) {
            spi1_dev.isr_handler((void *)&spi1_dev.status);
        }
    }
}
SDK_DECLARE_EXT_ISR_M(IRQn_SPI1, spi1_isr)

