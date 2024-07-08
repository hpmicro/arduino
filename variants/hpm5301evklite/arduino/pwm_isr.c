/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"

extern volatile uint32 tone_count[BOARD_NR_PWM_PINS];

__attribute__((section(".isr_vector")))
void tick_ms_isr(GPTMR_Type *instance)
{
    bool flag[4] = { false, false, false, false };
    if (gptmr_check_status(instance, GPTMR_CH_RLD_STAT_MASK(0))) {
        gptmr_clear_status(instance, GPTMR_CH_RLD_STAT_MASK(0));
        flag[0] = true;
    }
    if (gptmr_check_status(instance, GPTMR_CH_RLD_STAT_MASK(1))) {
        gptmr_clear_status(instance, GPTMR_CH_RLD_STAT_MASK(1));
        flag[1] = true;
    }
    if (gptmr_check_status(instance, GPTMR_CH_RLD_STAT_MASK(2))) {
        gptmr_clear_status(instance, GPTMR_CH_RLD_STAT_MASK(2));
        flag[2] = true;
    }
    if (gptmr_check_status(instance, GPTMR_CH_RLD_STAT_MASK(3))) {
        gptmr_clear_status(instance, GPTMR_CH_RLD_STAT_MASK(3));
        flag[3] = true;
    }

    for (int i = 0; i < BOARD_NR_PWM_PINS; i++) {
        const pwm_info_t *info = PIN_MAP[boardPWMPins[i]].pwm_device;
        if (info == NULL)
            continue;
        if (info->base != instance)
            continue;
        for (int j = 0; j < 4; j++) {
            if ((info->ch == j) && (flag[j] == true)) {
                tone_count[i]--;
                if (!tone_count[i]) {
                    gptmr_stop_counter(instance, pwm_info->ch);
                }
            }
        }
    }
}

void tick_ms_isr0(void)
{
    tick_ms_isr(HPM_GPTMR0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR0, tick_ms_isr0);

void tick_ms_isr1(void)
{
    tick_ms_isr(HPM_GPTMR1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR1, tick_ms_isr1);
