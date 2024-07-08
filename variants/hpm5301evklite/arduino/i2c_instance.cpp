/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <class/Wire.h>

extern i2c_dev_t i2c2_dev;

TwoWire I2C2(&i2c2_dev);
extern "C" {
    void twowire_callback(TwoWire* obj)
    {
        if (obj != nullptr) {
            obj->isr_handler();
        }
    }
    TwoWire* get_twowire_instance(int idx)
    {
        if (idx == 2)
            return &I2C2;
        return nullptr;
    }
}
