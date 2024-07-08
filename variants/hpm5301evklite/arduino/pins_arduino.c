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

MAKE_GPIO_INFO_FOR_10_31(led_pin_info, 0, A, 10, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_0_9(pushbutton_pin_info, 0, A, 3, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_0_9(pin_j3_7_info, 0, A, 2, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_8_info, 0, B, 15, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_10_info, 0, B, 14, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_11_info, 0, A, 31, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_13_info, 0, B, 11, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_19_info, 0, A, 29, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_21_info, 0, A, 28, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_23_info, 0, A, 27, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_24_info, 0, A, 26, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_26_info, 0, B, 10, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_27_info, 0, B, 12, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_28_info, 0, B, 13, IRQn_GPIO0_B);
MAKE_GPIO_INFO_FOR_0_9(pin_j3_29_info, 0, Y, 0, IRQn_GPIO0_Y);
MAKE_GPIO_INFO_FOR_0_9(pin_j3_31_info, 0, Y, 1, IRQn_GPIO0_Y);
MAKE_GPIO_INFO_FOR_0_9(pin_j3_32_info, 0, A, 9, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_33_info, 0, A, 10, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_0_9(pin_j3_36_info, 0, A, 0, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_10_31(pin_j3_37_info, 0, A, 30, IRQn_GPIO0_A);
MAKE_GPIO_INFO_FOR_0_9(pin_j3_38_info, 0, A, 1, IRQn_GPIO0_A);

const hpm_pin_info_t PIN_MAP[BOARD_NR_GPIO_PINS] = {
    [LED_BUILTIN] = { .gpio_device = &led_pin_info, .pwm_device = &pwm_info[0], .adc_device = NULL, },
    [PIN_PUSH_BUTTON] = { .gpio_device = &pushbutton_pin_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_7] = { .gpio_device = &pin_j3_7_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_8] = { .gpio_device = &pin_j3_8_info, .pwm_device = NULL, .adc_device = &board_adc_infos[5], },
    [PIN_J3_10] = { .gpio_device = &pin_j3_10_info, .pwm_device = NULL, .adc_device = &board_adc_infos[4], },
    [PIN_J3_11] = { .gpio_device = &pin_j3_11_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_13] = { .gpio_device = &pin_j3_13_info, .pwm_device = NULL, .adc_device = &board_adc_infos[1], },
    [PIN_J3_19] = { .gpio_device = &pin_j3_19_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_21] = { .gpio_device = &pin_j3_21_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_23] = { .gpio_device = &pin_j3_23_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_24] = { .gpio_device = &pin_j3_24_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_26] = { .gpio_device = &pin_j3_26_info, .pwm_device = NULL, .adc_device = &board_adc_infos[0], },
    [PIN_J3_27] = { .gpio_device = &pin_j3_27_info, .pwm_device = NULL, .adc_device = &board_adc_infos[2], },
    [PIN_J3_28] = { .gpio_device = &pin_j3_28_info, .pwm_device = &pwm_info[1], .adc_device = &board_adc_infos[3], },
    [PIN_J3_29] = { .gpio_device = &pin_j3_29_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_31] = { .gpio_device = &pin_j3_31_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_32] = { .gpio_device = &pin_j3_32_info, .pwm_device = NULL, .adc_device = NULL, },
    [PIN_J3_33] = { .gpio_device = &pin_j3_33_info, .pwm_device = &pwm_info[0], .adc_device = NULL, },
};

// Array of pins you can use for pwmWrite(). Keep it in Flash because
// it doesn't change, and so we don't waste RAM.
const uint8 boardPWMPins[BOARD_NR_PWM_PINS] = {
    LED_BUILTIN, /* PA10, GPTMR0.COM2 */
    PIN_J3_33, /* PA10, GPTMR0.COM2 */
    PIN_J3_28,/* PB13, GPTMR1.COMP3 */
};

// Array of pins you can use for analogRead().
const uint8 boardADCPins[BOARD_NR_ADC_PINS] = {
    PIN_J3_26, /* PB10, ADC0.IN2 */
    PIN_J3_13, /* PB11, ADC0.IN3 */
    PIN_J3_27, /* PB12, ADC0.IN4 */
    PIN_J3_28, /* PB13, ADC0.IN5 */
    PIN_J3_10, /* PB14, ADC0.IN6 */
    PIN_J3_8,/* PB15, ADC0.IN7 */
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

