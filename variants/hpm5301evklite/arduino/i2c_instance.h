/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef I2C_INSTACNE_H
#define I2C_INSTACNE_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct TwoWire TwoWire;

TwoWire* get_twowire_instance(int idx);
void twowire_callback(TwoWire* obj);

#ifdef __cplusplus
}
#endif
#endif