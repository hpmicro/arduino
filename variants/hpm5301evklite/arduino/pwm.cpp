/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"
#include "hpm_pwm_drv.h"

const pwm_info_t pwm_info[PIN_MAX_NUM] = {
    [0] = { /* PIN_J3_33 */
        .base = HPM_GPTMR0,
        .clock = clock_gptmr0,
        .pin = 0,
        .ch = 2,
        .reload = 200000 - 1,
        .irq_num = IRQn_GPTMR0,
        .ioc_idx = IOC_PAD_PA10,
        .ioc_fun = IOC_PA10_FUNC_CTL_GPTMR0_COMP_2,
        .pioc = false,
        .pioc_idx = 0,
        .pioc_fun = 0,
        .irq_group = 0,
    },
    [1] = { /* PIN_J3_28 */
        .base = HPM_GPTMR1,
        .clock = clock_gptmr1,
        .pin = 0,
        .ch = 3,
        .reload = 200000 - 1,
        .irq_num = IRQn_GPTMR1,
        .ioc_idx = IOC_PAD_PB13,
        .ioc_fun = IOC_PB13_FUNC_CTL_GPTMR1_COMP_3,
        .pioc = false,
        .pioc_idx = 0,
        .pioc_fun = 0,
        .irq_group = 0,
    },
};
