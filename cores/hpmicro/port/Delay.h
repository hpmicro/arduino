/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef _DELAY_H
#define _DELAY_H

#include "Common.h"
#include "hpm_mchtmr_drv.h"
#include "hpm_sysctl_drv.h"

unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long);
void delayMicroseconds(unsigned int us);

#endif