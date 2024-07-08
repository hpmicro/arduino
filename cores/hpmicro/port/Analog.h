/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef _ANALOG_H
#define _ANALOG_H
#include "Common.h"
#include "hpm_adc16_drv.h"
#if defined (SOC_HAS_PWM)
#include "hpm_pwm_drv.h"
#else
#include "hpm_gptmr_drv.h"
#endif

int16 analogRead(pin_size_t pinNumber);
void analogReference(uint8_t mode);
void analogWrite(pin_size_t pinNumber, int value);
void tone(pin_size_t _pin, unsigned int frequency, unsigned long duration = 0);
void noTone(pin_size_t _pin);
#endif
