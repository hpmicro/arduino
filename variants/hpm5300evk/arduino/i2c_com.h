/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef I2C_COM_H
#define I2C_COM_H
#include "hpm_i2c_drv.h"

#define I2C_SUCCESS              (0U)
#define I2C_DATA_TOO_LONG        (1U)
#define I2C_NACK_ADDR            (2U)
#define I2C_NACK_DATA            (3U)
#define I2C_OTHER_ERROR          (4U)
#define I2C_TIMEOUT              (5U)

#define I2C_STANDARD_SPEED       (100000U)
#define I2C_FAST_SPEED           (400000U)
#define I2C_FAST_PLUS_SPEED      (1000000U)
#endif
