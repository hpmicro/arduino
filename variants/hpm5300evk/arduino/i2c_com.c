/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"
#include "arduino/i2c_instance.h"

i2c_dev_t i2c0_dev = {
    .i2c = HPM_I2C0,
    .clock_name = clock_i2c0,
    .irq_num = IRQn_I2C0,
    .scl_ioc_func = IOC_PB02_FUNC_CTL_I2C0_SCL | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK,
    .scl_ioc_pad = IOC_PAD_PB02,
    .scl_ioc_pad_ctrl = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1),
    .sda_ioc_func = IOC_PB03_FUNC_CTL_I2C0_SDA | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK,
    .sda_ioc_pad = IOC_PAD_PB03,
    .sda_ioc_pad_ctrl = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1),
};

i2c_dev_t i2c1_dev = {
    .i2c = HPM_I2C1,
    .clock_name = clock_i2c1,
    .irq_num = IRQn_I2C1,
    .scl_ioc_func = IOC_PB07_FUNC_CTL_I2C1_SCL | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK,
    .scl_ioc_pad = IOC_PAD_PB07,
    .scl_ioc_pad_ctrl = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1),
    .sda_ioc_func = IOC_PB06_FUNC_CTL_I2C1_SDA | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK,
    .sda_ioc_pad = IOC_PAD_PB06,
    .sda_ioc_pad_ctrl = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1),
};

void i2c0_isr(void)
{
    TwoWire *instance = get_twowire_instance(0);
    if (instance != NULL) {
        twowire_callback(instance);
    }
}
SDK_DECLARE_EXT_ISR_M(IRQn_I2C0, i2c0_isr)

void i2c1_isr(void)
{
    TwoWire *instance = get_twowire_instance(1);
    if (instance != NULL) {
        twowire_callback(instance);
    }
}
SDK_DECLARE_EXT_ISR_M(IRQn_I2C1, i2c1_isr)

