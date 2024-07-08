/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"
#include "hpm_gpio_drv.h"

#define MAKE_GPIO_INFO_FOR_10_31(name, ctr, port, pin_idx, irq)   const gpio_desc_t name = { \
                                                                                        .ctrl = HPM_GPIO##ctr,\
                                                                                        .oe = GPIO_OE_GPIO##port,\
                                                                                        .do_idx = GPIO_DO_GPIO##port,\
                                                                                        .di_idx = GPIO_DI_GPIO##port,\
                                                                                        .pin = pin_idx,\
                                                                                        .ioc_idx = IOC_PAD_P##port##pin_idx,\
                                                                                        .ioc_fun = IOC_P##port##pin_idx##_FUNC_CTL_GPIO_##port##_##pin_idx,\
                                                                                        .irq_num = irq,\
                                                                                        .pioc = false,\
                                                                                        .bioc = false,\
                                                                                        .irq_group = GPIO##ctr##_##port##_IRQ_GROUP,\
                                                                                    }
#define MAKE_GPIO_INFO_FOR_0_9(name, ctr, port, pin_idx, irq)   const gpio_desc_t name =  { \
                                                                                        .ctrl = HPM_GPIO##ctr,\
                                                                                        .oe = GPIO_OE_GPIO##port,\
                                                                                        .do_idx = GPIO_DO_GPIO##port,\
                                                                                        .di_idx = GPIO_DI_GPIO##port,\
                                                                                        .pin = pin_idx,\
                                                                                        .ioc_idx = IOC_PAD_P##port##0##pin_idx,\
                                                                                        .ioc_fun = IOC_P##port##0##pin_idx##_FUNC_CTL_GPIO_##port##_##0##pin_idx,\
                                                                                        .irq_num = irq,\
                                                                                        .pioc = false,\
                                                                                        .bioc = false,\
                                                                                        .irq_group = GPIO##ctr##_##port##_IRQ_GROUP,\
                                                                                    }


#define MAKE_ALT_INFO_0_9(ctrl, port, pin, alt)     ctrl,\
                                                    GPIO_OE_GPIO##port,\
                                                    GPIO_DO_GPIO##port,\
                                                    GPIO_DI_GPIO##port,\
                                                    pin,\
                                                    IOC_PAD_P##port##0##pin,\
                                                    IOC_P##port##0##pin##_FUNC_CTL_##alt
                                   
#define MAKE_ALT_INFO_10_31(ctrl, port, pin, alt)       ctrl,\
                                                        GPIO_OE_GPIO##port,\
                                                        GPIO_DO_GPIO##port,\
                                                        GPIO_DI_GPIO##port,\
                                                        pin,\
                                                        IOC_PAD_P##port##pin,\
                                                        IOC_P##port##pin##_FUNC_CTL_##alt

MAKE_GPIO_INFO_FOR_10_31(led_pin_info, 0, A, 23, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_0_9(pushbutton_pin_info, 0, A, 9, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_3_info, 0, B, 6, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_5_info, 0, B, 7, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_7_info, 0, B, 15, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_8_info, 0, B, 8, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_10_info, 0, B, 9, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_11_info, 0, A, 12, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_12_info, 0, A, 10, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_13_info, 0, A, 31, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_15_info, 0, A, 30, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_16_info, 0, A, 11, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_19_info, 0, A, 29, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_21_info, 0, A, 28, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_23_info, 0, A, 27, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_24_info, 0, A, 26, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_26_info, 0, A, 25, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_qeo_a_info, 0, A, 20, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_qeo_b_info, 0, A, 21, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_qeo_z_info, 0, A, 22, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_27_info, 0, B, 3, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_28_info, 0, B, 2, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_29_info, 0, B, 1, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_31_info, 0, B, 4, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_0_9(pin_p1_32_info, 0, B, 5, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_33_info, 0, B, 14, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_35_info, 0, B, 13, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_37_info, 0, B, 12, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_38_info, 0, B, 10, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_p1_40_info, 0, B, 11, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_board_id_info, 0, B, 15, IRQn_GPIO0_B);

const hpm_pin_info_t PIN_MAP[BOARD_NR_GPIO_PINS] = {
    [LED_BUILTIN] = { .gpio_device = &led_pin_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_PUSH_BUTTON] = { .gpio_device = &pushbutton_pin_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_PWM_WH] = { .gpio_device = NULL, .pwm_device = &pwm_info[0], .adc_device = NULL, },
    [PIN_PWM_WL] = { .gpio_device = NULL, .pwm_device = &pwm_info[1], .adc_device = NULL, },
    [PIN_PWM_VH] = { .gpio_device = NULL, .pwm_device = &pwm_info[2], .adc_device = NULL, },
    [PIN_PWM_VL] = { .gpio_device = NULL, .pwm_device = &pwm_info[3], .adc_device = NULL, },
    [PIN_PWM_UH] = { .gpio_device = NULL, .pwm_device = &pwm_info[4], .adc_device = NULL, },
    [PIN_PWM_UL] = { .gpio_device = NULL, .pwm_device = &pwm_info[5], .adc_device = NULL, },
    [PIN_P1_3] = { .gpio_device = &pin_p1_3_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_ADC1] = { .gpio_device = NULL, .pwm_device = NULL, &board_adc_infos[0], },
    [PIN_ADC_A] = { .gpio_device = NULL, .pwm_device = NULL, &board_adc_infos[1], },
    [PIN_ADC_B] = { .gpio_device = NULL, .pwm_device = NULL, &board_adc_infos[2], },
    [PIN_ADC_C] = { .gpio_device = NULL, .pwm_device = NULL, &board_adc_infos[3], },
    [PIN_ADC_D] = { .gpio_device = NULL, .pwm_device = NULL, &board_adc_infos[4], },
    [PIN_ADC_IW] = { .gpio_device = NULL, .pwm_device = NULL, &board_adc_infos[5], },
    [PIN_ADC_IU] = { .gpio_device = NULL, .pwm_device = NULL, &board_adc_infos[6], },
    [PIN_ADC_IV] = { .gpio_device = NULL, .pwm_device = NULL, &board_adc_infos[7], },
    [PIN_P1_5] = { .gpio_device = &pin_p1_5_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_7] = { .gpio_device = &pin_p1_7_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_8] = { .gpio_device = &pin_p1_8_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_10] = { .gpio_device = &pin_p1_10_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_11] = { .gpio_device = &pin_p1_11_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_12] = { .gpio_device = &pin_p1_12_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_13] = { .gpio_device = &pin_p1_13_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_15] = { .gpio_device = &pin_p1_15_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_16] = { .gpio_device = &pin_p1_16_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_18] = { .gpio_device = NULL, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_19] = { .gpio_device = &pin_p1_19_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_21] = { .gpio_device = &pin_p1_21_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_22] = { .gpio_device = NULL, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_23] = { .gpio_device = &pin_p1_23_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_24] = { .gpio_device = &pin_p1_24_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_26] = { .gpio_device = &pin_p1_26_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_27] = { .gpio_device = &pin_p1_27_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_28] = { .gpio_device = &pin_p1_28_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_29] = { .gpio_device = &pin_p1_29_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_31] = { .gpio_device = &pin_p1_31_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_32] = { .gpio_device = &pin_p1_32_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_33] = { .gpio_device = &pin_p1_33_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_35] = { .gpio_device = &pin_p1_35_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_36] = { .gpio_device = NULL, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_37] = { .gpio_device = &pin_p1_37_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_38] = { .gpio_device = &pin_p1_38_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_P1_40] = { .gpio_device = &pin_p1_40_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_BOARD_ID] = { .gpio_device = &pin_board_id_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_ADC_BUS] = { .gpio_device = &pin_p1_29_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_QEI_A] = { .gpio_device = &pin_p1_12_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_QEI_B] = { .gpio_device = &pin_p1_16_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_QEI_Z] = { .gpio_device = &pin_p1_11_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_QEO_A] = { .gpio_device = &pin_qeo_a_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_QEO_B] = { .gpio_device = &pin_qeo_b_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_QEO_Z] = { .gpio_device = &pin_qeo_z_info, .pwm_device = NULL, .adc_device = NULL, },
};

// Array of pins you can use for pwmWrite(). Keep it in Flash because
// it doesn't change, and so we don't waste RAM.
const uint8 boardPWMPins[BOARD_NR_PWM_PINS] = {
    PIN_PWM_WH, PIN_PWM_WL, PIN_PWM_VH, PIN_PWM_VL, PIN_PWM_UH, PIN_PWM_UL,
};

// Array of pins you can use for analogRead().
const uint8 boardADCPins[BOARD_NR_ADC_PINS] = {
    PIN_ADC1, PIN_ADC_A, PIN_ADC_B, PIN_ADC_C, PIN_ADC_D, PIN_ADC_IW, PIN_ADC_IU, PIN_ADC_IV,
};
gpio_isr_info_t gpio_handlers[8][32] = { 0 }; 

static void isr_gpio(GPIO_Type *base, unsigned char port_index, unsigned char group)
{
    for (int i = 0; i < 32; i++) {
        if (gpio_check_pin_interrupt_flag(base, port_index, i)) {
            gpio_clear_pin_interrupt_flag(base, port_index, i);
            if (gpio_handlers[group][i].handler != NULL) {
                gpio_handlers[group][i].handler(gpio_handlers[group][i].arg);
            }
        }
    }
}

void isr_gpioa(void)
{
    isr_gpio(HPM_GPIO0, GPIO_DI_GPIOA, 0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_A, isr_gpioa)
void isr_gpiob(void)
{
    isr_gpio(HPM_GPIO0, GPIO_DI_GPIOB, 0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_B , isr_gpiob)
void isr_gpiox(void)
{
    isr_gpio(HPM_GPIO0, GPIO_DI_GPIOX, 5);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_X, isr_gpiox)
void isr_gpioy(void)
{
    isr_gpio(HPM_GPIO0, GPIO_DI_GPIOY, 6);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_Y, isr_gpioy)

