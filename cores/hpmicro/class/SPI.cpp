/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "SPI.h"

SPIClass SPI1(&spi1_dev);

SPIClass::SPIClass(spi_dev_t *dev, uint8_t role, uint8_t io_mode)
{
    this->spi_dev = dev;
    this->role = role;
    this->io_mode = io_mode;
    this->rxdma_complete = false;
    this->txdma_complete = false;
}

void SPIClass::spi1_rxdma_complete_callback(uint32_t channel)
{
    (void)channel;
    SPI1.rxdma_complete = true;
}

void SPIClass::spi1_txdma_complete_callback(uint32_t channel)
{
    (void)channel;
    SPI1.txdma_complete = true;
}

void SPIClass::begin(uint8 role, uint8_t io_mode)
{
    clock_add_to_group(this->spi_dev->clock_name, 0);
    clock_set_source_divider(this->spi_dev->clock_name, clk_src_pll1_clk0, 10U);
    HPM_IOC->PAD[this->spi_dev->clk_ioc_pad].FUNC_CTL = this->spi_dev->clk_ioc_func;
    HPM_IOC->PAD[this->spi_dev->clk_ioc_pad].PAD_CTL = this->spi_dev->spi_pins_ioc_ctl;
    hpm_spi_get_default_init_config(&this->spi_config);
    HPM_IOC->PAD[this->spi_dev->miso_ioc_pad].FUNC_CTL = this->spi_dev->miso_ioc_func;
    HPM_IOC->PAD[this->spi_dev->miso_ioc_pad].PAD_CTL = this->spi_dev->spi_pins_ioc_ctl;
    HPM_IOC->PAD[this->spi_dev->mosi_ioc_pad].FUNC_CTL = this->spi_dev->mosi_ioc_func;
    HPM_IOC->PAD[this->spi_dev->mosi_ioc_pad].PAD_CTL = this->spi_dev->spi_pins_ioc_ctl;
    if (role == SPI_SLAVE_ROLE) {
        HPM_IOC->PAD[this->spi_dev->cs_ioc_pad].FUNC_CTL = this->spi_dev->cs_ioc_func;
        HPM_IOC->PAD[this->spi_dev->cs_ioc_pad].PAD_CTL = this->spi_dev->spi_pins_ioc_ctl;
        this->spi_config.mode = spi_slave_mode;
    }
    if (io_mode == SPI_QUAD_IO_MODE) {
        HPM_IOC->PAD[this->spi_dev->io2_ioc_pad].FUNC_CTL = this->spi_dev->io2_ioc_func;
        HPM_IOC->PAD[this->spi_dev->io3_ioc_pad].FUNC_CTL = this->spi_dev->io3_ioc_func;
        HPM_IOC->PAD[this->spi_dev->io2_ioc_pad].PAD_CTL = this->spi_dev->spi_pins_ioc_ctl;
        HPM_IOC->PAD[this->spi_dev->io3_ioc_pad].PAD_CTL = this->spi_dev->spi_pins_ioc_ctl;
    }
    this->spi_config.io_mode = (spi_data_phase_format_t)io_mode;
    hpm_spi_initialize(this->spi_dev->spi, &this->spi_config);
    if (role == SPI_MASTER_ROLE) {
        hpm_spi_set_sclk_frequency(this->spi_dev->spi, SPI_DEFAULT_SCLK_FREQENCY);
    }
    hpm_spi_dma_install_callback(SPI.spi_dev->spi, spi1_txdma_complete_callback, spi1_rxdma_complete_callback);
    intc_m_enable_irq_with_priority(spi_dev->irq_num, 1);
}

void SPIClass::end(void)
{
    clock_remove_from_group(this->spi_dev->clock_name, 0);
}

void SPIClass::beginTransaction(SPISettings settings, uint8 role)
{
    if ((role == SPI_MASTER_ROLE) && (settings.clk > 0)) {
        hpm_spi_set_sclk_frequency(this->spi_dev->spi, settings.clk);
    }
    if (settings.order == LSBFIRST) {
        spi_set_shift_direction(this->spi_dev->spi, lsb_first);
    } else {
        spi_set_shift_direction(this->spi_dev->spi, msb_first);
    }
    if (settings.data_mode == SPI_MODE0) {
        spi_set_clock_polarity(this->spi_dev->spi, spi_sclk_low_idle);
        spi_set_clock_phase(this->spi_dev->spi, spi_sclk_sampling_odd_clk_edges);
    } else if (settings.data_mode == SPI_MODE1) {
        spi_set_clock_polarity(this->spi_dev->spi, spi_sclk_low_idle);
        spi_set_clock_phase(this->spi_dev->spi, spi_sclk_sampling_even_clk_edges);
    } else if (settings.data_mode == SPI_MODE2) {
        spi_set_clock_polarity(this->spi_dev->spi, spi_sclk_high_idle);
        spi_set_clock_phase(this->spi_dev->spi, spi_sclk_sampling_odd_clk_edges);
    } else {
        spi_set_clock_polarity(this->spi_dev->spi, spi_sclk_high_idle);
        spi_set_clock_phase(this->spi_dev->spi, spi_sclk_sampling_even_clk_edges);
    }
}

void SPIClass::endTransaction(void)
{

}

void SPIClass::setBitOrder(BitOrder _bitOrder)
{
    if (_bitOrder == LSBFIRST) {
        spi_set_shift_direction(this->spi_dev->spi, lsb_first);
    } else {
        spi_set_shift_direction(this->spi_dev->spi, msb_first);
    }
}

void SPIClass::setClockDivider(uint8_t _divider)
{
    uint32_t clk;
    if (_divider == SPI_CLOCK_DIV2) {
        clk = SPI_MAX_SCLK_FREQENCY / 2;
    } else if (_divider == SPI_CLOCK_DIV4) {
        clk = SPI_MAX_SCLK_FREQENCY / 4;
    } else if (_divider == SPI_CLOCK_DIV8) {
        clk = SPI_MAX_SCLK_FREQENCY / 8;
    } else if (_divider == SPI_CLOCK_DIV16) {
        clk = SPI_MAX_SCLK_FREQENCY / 16;
    } else if (_divider == SPI_CLOCK_DIV32) {
        clk = SPI_MAX_SCLK_FREQENCY / 32;
    } else if (_divider == SPI_CLOCK_DIV64) {
        clk = SPI_MAX_SCLK_FREQENCY / 64;
    } else {
        clk = SPI_MAX_SCLK_FREQENCY / 128;
    }
    hpm_spi_set_sclk_frequency(this->spi_dev->spi, clk);
}

void SPIClass::setDataMode(uint8_t _mode)
{
    if (_mode == SPI_MODE0) {
        spi_set_clock_polarity(this->spi_dev->spi, spi_sclk_low_idle);
        spi_set_clock_phase(this->spi_dev->spi, spi_sclk_sampling_odd_clk_edges);
    } else if (_mode == SPI_MODE1) {
        spi_set_clock_polarity(this->spi_dev->spi, spi_sclk_low_idle);
        spi_set_clock_phase(this->spi_dev->spi, spi_sclk_sampling_even_clk_edges);
    } else if (_mode == SPI_MODE2) {
        spi_set_clock_polarity(this->spi_dev->spi, spi_sclk_high_idle);
        spi_set_clock_phase(this->spi_dev->spi, spi_sclk_sampling_odd_clk_edges);
    } else {
        spi_set_clock_polarity(this->spi_dev->spi, spi_sclk_high_idle);
        spi_set_clock_phase(this->spi_dev->spi, spi_sclk_sampling_even_clk_edges);
    }
}

byte SPIClass::transfer(uint8_t data)
{
    uint8_t read_byte;
    spi_set_data_bits(this->spi_dev->spi, 8);
    hpm_spi_transmit_receive_blocking(this->spi_dev->spi, &data, &read_byte, 1, 0xFFFFFFFF);
    return read_byte;
}

void SPIClass::transfer(void *buf, size_t count)
{
    if (count > spi_get_tx_fifo_size(this->spi_dev->spi)) {
        this->txdma_complete = false;
        hpm_spi_transmit_nonblocking(this->spi_dev->spi, (uint8_t *)buf, count);
        while (this->txdma_complete == false) {
        };
    } else {
        hpm_spi_transmit_blocking(this->spi_dev->spi, (uint8_t *)buf, count, 0xFFFFFFFF);
    }
}

uint16_t SPIClass::transfer16(uint16_t data)
{
    uint16_t read_byte;
    spi_set_data_bits(this->spi_dev->spi, 16);
    hpm_spi_transmit_receive_blocking(this->spi_dev->spi, (uint8_t *)&data, (uint8_t *)&read_byte, 2, 0xFFFFFFFF);
    spi_set_data_bits(this->spi_dev->spi, 8);
    return read_byte;
}

void SPIClass::receive(uint8_t *data, uint32_t len)
{
    if (len > spi_get_rx_fifo_size(this->spi_dev->spi)) {
        this->rxdma_complete = false;
        hpm_spi_receive_nonblocking(this->spi_dev->spi, data, len);
        while (this->rxdma_complete == false) {
        };
    } else {
        hpm_spi_receive_blocking(this->spi_dev->spi, data, len, 0xFFFFFFFF);
    }
}

void SPIClass::transmit(uint8_t *data, uint32_t len)
{
    if (len > spi_get_tx_fifo_size(this->spi_dev->spi)) {
        this->txdma_complete = false;
        hpm_spi_transmit_nonblocking(this->spi_dev->spi, (uint8_t *)data, len);
        while (this->txdma_complete == false) {
        };
    } else {
        hpm_spi_transmit_blocking(this->spi_dev->spi, (uint8_t *)data, len, 0xFFFFFFFF);
    }
}

void SPIClass::usingInterrupt(uint8_t interruptNumber)
{
    if (interruptNumber == this->spi_dev->irq_num) {
        spi_set_tx_fifo_threshold(this->spi_dev->spi, SPI_SOC_FIFO_DEPTH - 1U);
        spi_set_rx_fifo_threshold(this->spi_dev->spi, 1U);
        spi_enable_interrupt(this->spi_dev->spi, spi_tx_fifo_threshold_int | spi_rx_fifo_threshold_int | spi_end_int);
    }
}

void SPIClass::attachInterruptParam(voidFuncPtrParam callback, void *param)
{
    this->spi_dev->isr_handler = callback;
    this->spi_dev->isr_arg = param;
}

void SPIClass::detachInterrupt(uint8_t interruptNumber)
{
    if (interruptNumber == this->spi_dev->irq_num) {
        spi_disable_interrupt(this->spi_dev->spi, spi_tx_fifo_threshold_int | spi_rx_fifo_threshold_int | spi_end_int);
        this->spi_dev->isr_arg = NULL;
        this->spi_dev->isr_handler = NULL;
    }
}

uint8_t SPIClass::read_byte(void)
{
    return (uint8_t)this->spi_dev->spi->DATA;
}

void SPIClass::write_byte(uint8_t byte)
{
    this->spi_dev->spi->DATA = byte;
}
