/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"
#include "hpm_adc16_drv.h"

const adc_info_t board_adc_infos[] = {
    { /* PIN_ADC1 */
        .base = HPM_ADC0,
        .ch = 13u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB05,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
    { /* PIN_ADC_A */
        .base = HPM_ADC0,
        .ch = 11u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB08,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
    { /* PIN_ADC_B */
        .base = HPM_ADC0,
        .ch = 1u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB09,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
    { /* PIN_ADC_C */
        .base = HPM_ADC0,
        .ch = 2u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB10,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
    { /* PIN_ADC_D */
        .base = HPM_ADC0,
        .ch = 3u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB11,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
    { /* PIN_ADC_IW */
        .base = HPM_ADC0,
        .ch = 4u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB12,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
    { /* PIN_ADC_IU */
        .base = HPM_ADC0,
        .ch = 5u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB13,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
    { /* PIN_ADC_IV */
        .base = HPM_ADC0,
        .ch = 6u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB14,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
};

