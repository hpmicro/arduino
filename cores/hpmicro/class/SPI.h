/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "Arduino.h"
#include <stdio.h>
extern "C" {
#include "arduino/spi_com.h"
}

#define SPI_DEFAULT_SCLK_FREQENCY                  (20000000U)
#define SPI_MAX_SCLK_FREQENCY                      (80000000U)

/* The SPISettings object is used to configure the SPI port for your SPI device. */
class SPISettings {
public:
    SPISettings(uint32_t speedMaximum, BitOrder dataOrder, uint8_t dataMoede)
    {
        clk = speedMaximum;
        order = dataOrder;
        data_mode = dataMoede;
    };
    SPISettings()
    {
        clk = 20000000;
        order = MSBFIRST;
        data_mode = SPI_MODE0;
    };

private:
    uint32_t clk;
    BitOrder order;
    uint8_t data_mode;
    friend class SPIClass;
};

class SPIClass
{
public:
    SPIClass(spi_dev_t *dev, uint8 role = SPI_MASTER_ROLE, uint8_t io_mode = SPI_SINGLE_IO_MODE);
    void begin(uint8 role = SPI_MASTER_ROLE, uint8_t io_mode = SPI_SINGLE_IO_MODE);
    void beginTransaction(SPISettings settings, uint8 role = SPI_MASTER_ROLE);
    void endTransaction(void);
    void end(void);
    void setBitOrder(BitOrder _bitOrder);
    void setClockDivider(uint8_t _divider);
    void setDataMode(uint8_t _mode);
    byte transfer(uint8_t data);
    void transfer(void *buf, size_t count);
    uint16_t transfer16(uint16_t data);
    void receive(uint8_t *data, uint32_t len);
    void transmit(uint8_t *data, uint32_t len);
    uint8_t read_byte(void); /* Used for reading in interrupts */
    void write_byte(uint8_t byte); /* Used for writing in interrupts */
    void usingInterrupt(uint8_t interruptNumber);
    void attachInterruptParam(voidFuncPtrParam callback, void *param);
    void detachInterrupt(uint8_t interruptNumber);
private:
    static void spi1_rxdma_complete_callback(uint32_t channel);
    static void spi1_txdma_complete_callback(uint32_t channel);

private:
    spi_dev_t *spi_dev;
    spi_initialize_config_t spi_config;
    uint8_t role;
    uint8_t io_mode;
    bool txdma_complete;
    bool rxdma_complete;
};

extern SPIClass SPI1;

#define SPI          SPI1

#endif
