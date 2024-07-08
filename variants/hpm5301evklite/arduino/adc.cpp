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
    { /* PIN_J3_26, PB10, ADC0.IN2 */
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
    { /* PIN_J3_13, PB11, ADC0.IN3 */
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
    { /* PIN_J3_27, PB12, ADC0.IN4 */
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
    { /* PIN_J3_28, PB13, ADC0.IN5 */
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
    { /* PIN_J3_10, PB14, ADC0.IN6 */
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
    { /* PIN_J3_8, PB15, ADC0.IN7 */
        .base = HPM_ADC0,
        .ch = 7u,
        .clock_name = clock_adc0,
        .irq_num = IRQn_ADC0,
        .sample_cycle = 20,
        .name = "ADC0",
        .ioc_idx = IOC_PAD_PB15,
        .ioc_fun = IOC_PAD_FUNC_CTL_ANALOG_MASK,
        .pioc = false,
    },
};

