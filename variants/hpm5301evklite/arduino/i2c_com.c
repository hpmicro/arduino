/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"
#include "arduino/i2c_instance.h"

i2c_dev_t i2c2_dev = {
    .i2c = HPM_I2C2,
    .clock_name = clock_i2c2,
    .irq_num = IRQn_I2C2,
    .scl_ioc_func = IOC_PB08_FUNC_CTL_I2C2_SCL | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK,
    .scl_ioc_pad = IOC_PAD_PB08,
    .scl_ioc_pad_ctrl = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1),
    .sda_ioc_func = IOC_PB09_FUNC_CTL_I2C2_SDA | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK,
    .sda_ioc_pad = IOC_PAD_PB09,
    .sda_ioc_pad_ctrl = IOC_PAD_PAD_CTL_OD_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1),
};

void i2c2_isr(void)
{
    TwoWire *instance = get_twowire_instance(2);
    if (instance != NULL) {
        twowire_callback(instance);
    }
}
SDK_DECLARE_EXT_ISR_M(IRQn_I2C2, i2c2_isr)


