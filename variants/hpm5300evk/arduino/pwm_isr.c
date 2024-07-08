/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"
#include "hpm_pwm_drv.h"
extern volatile uint32 tone_count[BOARD_NR_PWM_PINS];
void isr_pwm_reload(void)
{
    pwm_clear_status(HPM_PWM0, PWM_IRQ_RELOAD);
    for (int i = 0; i < BOARD_NR_PWM_PINS; i++) {
        const pwm_info_t *info = PIN_MAP[boardPWMPins[i]].pwm_device;
        if (info == NULL)
            continue;
        if (info->base != HPM_PWM0)
            continue;
        tone_count[i]--;
        if (!tone_count[i]) {
            pwm_disable_output(HPM_PWM0, info->pin);
        }
    }
}
SDK_DECLARE_EXT_ISR_M(IRQn_PWM0, isr_pwm_reload)
