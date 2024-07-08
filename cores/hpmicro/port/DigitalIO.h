/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef _DIGITAL_IO_H
#define _DIGITAL_IO_H
#include "Common.h"
#include "hpm_gpio_drv.h"

#define pulseInLong pulseIn

void digitalWrite(pin_size_t pinNumber, uint8 status);
uint8 digitalRead(pin_size_t pinNumber);
unsigned long pulseIn(pin_size_t pin, uint8_t state, unsigned long timeout);
void shiftOut(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder, uint8_t val);
uint8_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder);

void attachInterrupt(pin_size_t pin, voidFuncPtr callback, uint8 mode);
void attachInterruptParam(pin_size_t pin, voidFuncPtrParam callback, uint8 mode, void* param);
void detachInterrupt(pin_size_t pin);
#endif
