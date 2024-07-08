/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <class/Wire.h>

extern i2c_dev_t i2c0_dev;
extern i2c_dev_t i2c1_dev;

TwoWire I2C0(&i2c0_dev);
TwoWire I2C1(&i2c1_dev);
extern "C" {
    void twowire_callback(TwoWire* obj)
    {
        if (obj != nullptr) {
            obj->isr_handler();
        }
    }
    TwoWire* get_twowire_instance(int idx)
    {
        if (idx == 0)
            return &I2C0;
        if (idx == 1)
            return &I2C1;
        return nullptr;
    }
}
