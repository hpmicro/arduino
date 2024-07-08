/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "Analog.h"

volatile uint32 tone_count[PIN_MAX_NUM] = { 0 };

int16 analogRead(pin_size_t pinNumber)
{
    uint8 max_retry = 5;
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    const adc_info_t *adc_info = PIN_MAP[pinNumber].adc_device;
    assert(adc_info != NULL);
    adc16_channel_config_t ch_cfg;
    /* get a default channel config */
    adc16_get_channel_default_config(&ch_cfg);
    /* initialize an ADC channel */
    ch_cfg.ch           = adc_info->ch;
    ch_cfg.sample_cycle = adc_info->sample_cycle;

    adc16_init_channel(adc_info->base, &ch_cfg);

    adc16_set_nonblocking_read(adc_info->base);
    /* enable oneshot mode */
    adc16_enable_oneshot_mode(BOARD_APP_ADC16_BASE);
    uint16_t result;
    while (max_retry--) {
        if (adc16_get_oneshot_result(adc_info->base, adc_info->ch, &result) == status_success) {
            if (adc16_is_nonblocking_mode(adc_info->base)) {
                adc16_get_oneshot_result(adc_info->base, adc_info->ch, &result);
                return result >> 6;
            }
            return result >> 6;
        }
    }
    return -1;
}

void analogReference(uint8_t mode)
{
    (void)mode;
}

void analogWrite(pin_size_t pinNumber, int value)
{
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    const pwm_info_t *pwm_info = PIN_MAP[pinNumber].pwm_device;
    assert(pwm_info != NULL);
#if defined (SOC_HAS_PWM)
    pwm_set_reload(pwm_info->base, 0, pwm_info->reload);
    pwm_set_start_count(pwm_info->base, 0, 0);
    pinMode(pinNumber, PWM);

    pwm_update_raw_cmp_edge_aligned(pwm_info->base, pwm_info->cmp_index, 1.0f * (1.0f - value / 255.0f) * pwm_info->reload);
    pwm_issue_shadow_register_lock_event(pwm_info->base);
    pwm_start_counter(pwm_info->base);
#else
    gptmr_channel_config_t config;
    uint32_t gptmr_freq;

    gptmr_channel_get_default_config(pwm_info->base, &config);
    gptmr_freq = clock_get_frequency(pwm_info->clock);
    config.reload = pwm_info->reload;
    config.cmp_initial_polarity_high = false;
    gptmr_stop_counter(pwm_info->base, pwm_info->ch);
    gptmr_channel_config(pwm_info->base, pwm_info->ch, &config, false);
    gptmr_channel_reset_count(pwm_info->base, pwm_info->ch);
    gptmr_update_cmp(pwm_info->base, pwm_info->ch, 0, 1.0f * (value / 255.0f) * pwm_info->reload);
    gptmr_start_counter(pwm_info->base, pwm_info->ch);

#endif
}

void tone(pin_size_t pinNumber, unsigned int frequency, unsigned long duration)
{
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    const pwm_info_t *pwm_info = PIN_MAP[pinNumber].pwm_device;
    assert(pwm_info != NULL);
    pinMode(pinNumber, PWM);
    uint32_t reload = clock_get_frequency(pwm_info->clock) / frequency - 1u;
#if defined (SOC_HAS_PWM)
    pwm_set_reload(pwm_info->base, 0, reload);
    pwm_update_raw_cmp_edge_aligned(pwm_info->base, pwm_info->cmp_index, (reload + 1) >> 1);
    pwm_issue_shadow_register_lock_event(pwm_info->base);
    pwm_start_counter(pwm_info->base);

    if (duration) {
        tone_count[pinNumber] = (duration / 1000.0f) * frequency;
        printf("duration is %lu, tone count %u\n", duration, tone_count[pinNumber]);
        printf("irq num %d\n", pwm_info->irq_num);
        pwm_enable_irq(pwm_info->base, PWM_IRQ_RELOAD);
        intc_m_enable_irq_with_priority(pwm_info->irq_num, 1);
    }
#else
    gptmr_channel_config_t config;
    uint32_t gptmr_freq;

    gptmr_channel_get_default_config(pwm_info->base, &config);
    gptmr_freq = clock_get_frequency(pwm_info->clock);
    config.reload = pwm_info->reload;
    config.cmp_initial_polarity_high = false;
    gptmr_stop_counter(pwm_info->base, pwm_info->ch);
    gptmr_channel_config(pwm_info->base, pwm_info->ch, &config, false);
    gptmr_channel_reset_count(pwm_info->base, pwm_info->ch);
    gptmr_update_cmp(pwm_info->base, pwm_info->ch, 0, reload);
    gptmr_start_counter(pwm_info->base, pwm_info->ch);

    if (duration) {
        tone_count[pinNumber] = (duration / 1000.0f) * frequency;
        printf("duration is %lu, tone count %u\n", duration, tone_count[pinNumber]);
        printf("irq num %d\n", pwm_info->irq_num);
        gptmr_enable_irq(pwm_info->base, GPTMR_CH_RLD_IRQ_MASK(pwm_info->ch));
        intc_m_enable_irq_with_priority(pwm_info->irq_num, 1);
    }

#endif
}

void noTone(pin_size_t pinNumber)
{
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    const pwm_info_t *pwm_info = PIN_MAP[pinNumber].pwm_device;
    assert(pwm_info != NULL);
#if defined (SOC_HAS_PWM)
    pwm_stop_counter(pwm_info->base);
#else
    gptmr_stop_counter(pwm_info->base, pwm_info->ch);
#endif
    intc_m_disable_irq(pwm_info->irq_num);
}
