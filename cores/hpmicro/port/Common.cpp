/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "Common.h"
#include "hpm_rng_drv.h"
#include "hpm_dma_mgr.h"

/* This function will execute before sketch setup function. */
void init(void)
{
#if defined (SOC_HAS_RNG)
    hpm_stat_t stat;
    stat = rng_init(HPM_RNG);
    if (stat) {
        printf("failed to rng_init: 0x%x\n", stat);
    }
#endif
    dma_mgr_init();
}

void initVariant(void)
{

}

void pinMode(pin_size_t pinNumber, PinMode pinMode)
{
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));

    if ((pinMode == OUTPUT) || (pinMode == INPUT_PULLUP) || (pinMode == INPUT_PULLDOWN) || (pinMode == OUTPUT_OPENDRAIN)) {
        const gpio_desc_t* info = PIN_MAP[pinNumber].gpio_device;
        assert(info != NULL);
        uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        if (pinMode == INPUT_PULLUP)
            pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        if (pinMode == INPUT_PULLDOWN)
            pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(0);
        if (pinMode == OUTPUT_OPENDRAIN)
            pad_ctl = IOC_PAD_PAD_CTL_OD_SET(1);

        HPM_IOC->PAD[info->ioc_idx].FUNC_CTL = info->ioc_fun;
        HPM_IOC->PAD[info->ioc_idx].PAD_CTL = pad_ctl;

        if (info->pioc) {
            HPM_PIOC->PAD[info->ioc_idx].FUNC_CTL = info->pioc_fun;
            HPM_PIOC->PAD[info->ioc_idx].PAD_CTL = pad_ctl;
        }
        switch(pinMode) {
            case INPUT:
            case INPUT_PULLUP:
            case INPUT_PULLDOWN:
                gpio_set_pin_input(info->ctrl, info->di_idx, info->pin);
                break;
            case OUTPUT:
            case OUTPUT_OPENDRAIN:
                gpio_set_pin_output(info->ctrl, info->do_idx, info->pin);
                break;
        }
    }
    switch(pinMode) {
        case PWM: {
            const pwm_info_t *pwm_info = PIN_MAP[pinNumber].pwm_device;
            assert(pwm_info != NULL);
            HPM_IOC->PAD[pwm_info->ioc_idx].FUNC_CTL = pwm_info->ioc_fun;
            if (pwm_info->pioc) {
                HPM_PIOC->PAD[pwm_info->ioc_idx].FUNC_CTL = pwm_info->pioc_fun;
            }

#if defined (SOC_HAS_PWM)
            pwm_cmp_config_t cmp_config = {0};
            pwm_config_t pwm_config = {0};
            pwm_get_default_pwm_config(pwm_info->base, &pwm_config);
            pwm_config.enable_output = true;
            pwm_config.dead_zone_in_half_cycle = 0;
            pwm_config.invert_output = false;
            cmp_config.mode = pwm_cmp_mode_output_compare;
            cmp_config.cmp = pwm_info->reload;
            cmp_config.update_trigger = pwm_shadow_register_update_on_modify;
            pwm_stop_counter(pwm_info->base);

            /*
            * config pwm as output driven by cmp
            */
            if (status_success != pwm_setup_waveform(pwm_info->base, pwm_info->pin, &pwm_config, pwm_info->cmp_index, &cmp_config, 1)) {
                printf("failed to setup waveform\n");
                while(1);
            }
            pwm_issue_shadow_register_lock_event(pwm_info->base);
#endif
            clock_add_to_group(pwm_info->clock, 0);
        }
            break;
        case ANOLOG: {
            const adc_info_t *adc_info = PIN_MAP[pinNumber].adc_device;
            adc16_config_t cfg;
            assert(adc_info != NULL);
            HPM_IOC->PAD[adc_info->ioc_idx].FUNC_CTL = adc_info->ioc_fun;
            if (adc_info->pioc) {
                HPM_PIOC->PAD[adc_info->ioc_idx].FUNC_CTL = adc_info->pioc_fun;
            }
            /* Configure the ADC clock from AHB (@200MHz by default)*/
            clock_set_adc_source(adc_info->clock_name, clk_adc_src_ahb0);
            adc16_get_default_config(&cfg);
            cfg.res            = adc16_res_16_bits;
            cfg.conv_mode      = adc16_conv_mode_oneshot;
            cfg.adc_clk_div    = adc16_clock_divider_4;
            cfg.sel_sync_ahb   = true;
            /* adc16 initialization */
            if (adc16_init(adc_info->base, &cfg) == status_success) {
                /* enable irq */
                intc_m_enable_irq_with_priority(adc_info->irq_num, 1);
            } else {
                printf("%s initialization failed!\n", adc_info->name);
            }
        }
            break;
    }
}
