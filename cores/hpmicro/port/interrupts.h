/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_
#include "hpm_common.h"
#include "hpm_interrupt.h"

inline void interrupts() {
    enable_global_irq(CSR_MSTATUS_MIE_MASK);
}
inline void noInterrupts() {
    disable_global_irq(CSR_MSTATUS_MIE_MASK);
}
#endif