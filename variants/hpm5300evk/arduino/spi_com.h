/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/
#ifndef SPI_COM_H
#define SPI_COM_H

#include "components/spi/hpm_spi.h"
#include "components/dma_mgr/hpm_dma_mgr.h"
// SPI mode parameters for SPISettings
#define SPI_MODE0                   (0x00U)
#define SPI_MODE1                   (0x01U)
#define SPI_MODE2                   (0x02U)
#define SPI_MODE3                   (0x03U)

#define SPI_END_OF_TRANSFER_FLAG    (0x00U)
#define SPI_VALID_RX_FLAG           (0x01U)
#define SPI_EMPTY_TX_FLAG           (0x02U)

#define SPI_MASTER_ROLE             (0x00U)
#define SPI_SLAVE_ROLE              (0x01U)

#define SPI_CLOCK_DIV4              (0x00U)
#define SPI_CLOCK_DIV16             (0x01U)
#define SPI_CLOCK_DIV64             (0x02U)
#define SPI_CLOCK_DIV128            (0x03U)
#define SPI_CLOCK_DIV2              (0x04U)
#define SPI_CLOCK_DIV8              (0x05U)
#define SPI_CLOCK_DIV32             (0x06U)

#define SPI_SINGLE_IO_MODE          (0x00U)
#define SPI_DUAL_IO_MODE            (0x01U)
#define SPI_QUAD_IO_MODE            (0x02U)

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif
